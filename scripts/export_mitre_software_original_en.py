#!/usr/bin/env python3
"""Export MITRE ATT&CK Software page tables to English Markdown.

Extracts text directly from the six MITRE pages at runtime. It neither
translates nor summarizes MITRE's source text.

Usage:
    pip install requests beautifulsoup4 markdownify
    python export_mitre_software_original_en.py
    python export_mitre_software_original_en.py --out ./reports
"""
from __future__ import annotations

import argparse
import re
import time
from datetime import datetime, timezone
from pathlib import Path
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup, Tag
from markdownify import markdownify as md

BASE = "https://attack.mitre.org"
SOFTWARE = [
    ("S1129", "Akira"),
    ("S1194", "Akira_v2"),
    ("S1191", "Megazord"),
    ("S1139", "INC Ransomware"),
    ("S9051", "The Gentlemen Ransomware"),
    ("S1242", "Qilin"),
]
ALLOWED_SECTIONS = {
    "Associated Software Descriptions",
    "Techniques Used",
    "Groups That Use This Software",
}
EXPECTED_TECHNIQUES = {
    "S1129": 10,
    "S1194": 6,
    "S1191": 6,
    "S1139": 15,
    "S9051": 45,
    "S1242": 52,
}


def normalize_text(s: str) -> str:
    """Normalize presentation whitespace without rewriting English wording."""
    s = re.sub(r"\r\n?", "\n", s)
    s = re.sub(r"[ \t]+", " ", s)
    s = re.sub(r"\n\s*\n+", "\n", s)
    return s.strip()


def inline_markdown(tag: Tag | None) -> str:
    if tag is None:
        return ""
    html = BeautifulSoup(str(tag), "html.parser")
    for a in html.find_all("a", href=True):
        a["href"] = urljoin(BASE, a["href"])
    # Buttons that make tables interactive are not original table content.
    for n in html.find_all(["button", "svg", "script", "style"]):
        n.decompose()
    root = html.find(True)
    inner_html = "".join(str(piece) for piece in root.contents) if root else ""
    result = md(inner_html, heading_style="ATX", bullets="-")
    result = normalize_text(result)
    # Table cells cannot contain bare newlines.
    result = result.replace("\n", "<br>")
    result = result.replace("|", r"\|")
    return result


def text_only(tag: Tag | None) -> str:
    return normalize_text(tag.get_text(" ", strip=True)) if tag else ""


def expanded_table(table: Tag) -> list[list[Tag | None]]:
    """Resolve HTML rowspan/colspan into rectangular columns."""
    grid: dict[tuple[int, int], Tag] = {}
    rows = table.find_all("tr")
    width = 0
    for r, row in enumerate(rows):
        c = 0
        for cell in row.find_all(["td", "th"], recursive=False):
            while (r, c) in grid:
                c += 1
            try:
                colspan = max(1, int(cell.get("colspan", 1)))
                rowspan = max(1, int(cell.get("rowspan", 1)))
            except ValueError:
                colspan = rowspan = 1
            for rr in range(r, r + rowspan):
                for cc in range(c, c + colspan):
                    grid[(rr, cc)] = cell
            c += colspan
            width = max(width, c)
    return [[grid.get((r, c)) for c in range(width)] for r in range(len(rows))]


def technique_id(left: Tag | None, right: Tag | None) -> str:
    """Join MITRE's technique parent and subtechnique suffix columns."""
    p = text_only(left)
    s = text_only(right)
    base_match = re.search(r"T\d{4}", p)
    suffix_match = re.search(r"\.\d{3}", s)
    full_match = re.search(r"T\d{4}(?:\.\d{3})?", p + " " + s)
    if base_match and suffix_match:
        code = base_match.group(0) + suffix_match.group(0)
    elif full_match:
        code = full_match.group(0)
    else:
        return inline_markdown(left)
    url = f"{BASE}/techniques/{code.replace('.', '/')}/"
    return f"[{code}]({url})"


def render_techniques(table: Tag) -> tuple[str, int]:
    grid = expanded_table(table)
    if not grid:
        return "", 0
    out = ["| Domain | ID | Name | Use |", "| --- | --- | --- | --- |"]
    seen = 0
    for cells in grid[1:]:
        if not any(x is not None for x in cells):
            continue
        # MITRE uses five underlying HTML columns for subtechniques and
        # four semantic columns. Subtechnique ID = Tnnnn + .xxx.
        if len(cells) >= 5:
            domain, parent, suffix, name, usage = cells[:5]
            ident = technique_id(parent, suffix)
        elif len(cells) == 4:
            domain, id_cell, name, usage = cells
            ident = technique_id(id_cell, None)
        else:
            raise ValueError(f"Unexpected Techniques Used row with {len(cells)} cells")
        if not ident:
            continue
        values = [inline_markdown(domain), ident, inline_markdown(name), inline_markdown(usage)]
        out.append("| " + " | ".join(values) + " |")
        seen += 1
    return "\n".join(out), seen


def render_other_table(table: Tag) -> tuple[str, int]:
    grid = expanded_table(table)
    if not grid:
        return "", 0
    headers = [inline_markdown(x) for x in grid[0]]
    # Drop duplicate adjacent colspan headers while keeping distinct columns.
    headers = [h or f"Column {i+1}" for i, h in enumerate(headers)]
    output = ["| " + " | ".join(headers) + " |", "| " + " | ".join("---" for _ in headers) + " |"]
    count = 0
    for row in grid[1:]:
        values = [inline_markdown(x) for x in row]
        if not any(values):
            continue
        output.append("| " + " | ".join(values) + " |")
        count += 1
    return "\n".join(output), count


def heading_before(table: Tag) -> str:
    h = table.find_previous(["h2", "h3", "h4"])
    return text_only(h) if h else ""


def extract_page(html: str, software_id: str, name: str, url: str) -> tuple[str, int, list[str]]:
    soup = BeautifulSoup(html, "html.parser")
    # All source data below comes from the official HTML, not from previous summaries.
    candidate_tables = soup.select("table")
    sections: list[str] = []
    found_sections: list[str] = []
    technique_count = 0
    for table in candidate_tables:
        heading = heading_before(table)
        if heading not in ALLOWED_SECTIONS:
            continue
        if heading == "Techniques Used":
            body, technique_count = render_techniques(table)
        else:
            body, _ = render_other_table(table)
        if body:
            sections.append(f"## {heading}\n\n{body}")
            found_sections.append(heading)
    if "Techniques Used" not in found_sections:
        raise RuntimeError(f"Could not locate Techniques Used table for {software_id}: HTML layout may have changed")
    date = datetime.now(timezone.utc).date().isoformat()
    top = [
        f"# {name} — MITRE ATT&CK® Software {software_id}",
        "",
        f"Source: {url}",
        f"Retrieved (UTC): {date}",
        "",
        "Source-language export. Table text is extracted from MITRE ATT&CK HTML without translation or summarization. Markdown formatting and hyperlink rendering are adapted for portability.",
        "",
    ]
    return "\n".join(top) + "\n\n".join(sections) + "\n", technique_count, found_sections


def safe_filename(s: str) -> str:
    return re.sub(r"[^A-Za-z0-9]+", "_", s).strip("_").lower()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", default="mitre_software_original_en", help="Output directory")
    parser.add_argument("--delay", type=float, default=0.5, help="Seconds between requests")
    parser.add_argument("--timeout", type=int, default=30, help="Request timeout")
    args = parser.parse_args()
    dest = Path(args.out)
    dest.mkdir(parents=True, exist_ok=True)
    session = requests.Session()
    session.headers.update({"User-Agent": "MITRE-ATTCK-Markdown-Research-Export/1.0 (+https://attack.mitre.org/)", "Accept": "text/html"})
    combined = ["# MITRE ATT&CK® — Six Ransomware Software Pages (English Source Tables)", ""]
    summary = []
    for index, (software_id, name) in enumerate(SOFTWARE, 1):
        url = f"{BASE}/software/{software_id}/"
        response = session.get(url, timeout=args.timeout)
        response.raise_for_status()
        page, count, section_names = extract_page(response.text, software_id, name, url)
        target = dest / f"{software_id}_{safe_filename(name)}.md"
        target.write_text(page, encoding="utf-8")
        combined.extend([page.rstrip(), "", "---", ""])
        summary.append((software_id, count, section_names, str(target)))
        print(f"[{index}/6] {software_id} — {name}: {count} Techniques; {', '.join(section_names)}")
        expected = EXPECTED_TECHNIQUES[software_id]
        if count != expected:
            print(f"  NOTE: expected {expected} based on 2026-10-23 snapshot; current site yields {count} (MITRE may have updated).")
        if index < len(SOFTWARE):
            time.sleep(args.delay)
    all_path = dest / "MITRE_ATTCK_Software_All_Tables_Original_English.md"
    all_path.write_text("\n".join(combined), encoding="utf-8")
    print(f"\nSaved {len(SOFTWARE)} separate files and combined file: {all_path}")


if __name__ == "__main__":
    main()
