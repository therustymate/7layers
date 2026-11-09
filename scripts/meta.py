
#!/usr/bin/env python3

import sys
import struct
import pefile

MAGIC = b"7LAYERS\x00"
SECTION_NAME = b".meta"

METADATA_FORMAT = struct.Struct(
    "<8sI40s41s32s24s64s129s"
)

def decode_string(data: bytes) -> str:
    return data.split(b"\x00", 1)[0].decode(
        "utf-8", errors="replace"
    )


def parse_metadata(path: str) -> dict:
    pe = pefile.PE(path, fast_load=True)

    try:
        for section in pe.sections:
            name = section.Name.rstrip(b"\x00")

            if name != SECTION_NAME:
                continue

            data = section.get_data(
                length=METADATA_FORMAT.size
            )

            if len(data) < METADATA_FORMAT.size:
                raise ValueError("Invalid metadata size")

            (
                magic,
                version,
                build_id,
                git_commit,
                build_date,
                build_profile,
                authorization_id,
                signing_key_fingerprint,
            ) = METADATA_FORMAT.unpack_from(data)

            if magic != MAGIC:
                raise ValueError("Invalid metadata signature")

            if version != 1:
                raise ValueError(
                    f"Unsupported metadata version: {version}"
                )

            return {
                "Build ID": decode_string(build_id),
                "Git Commit": decode_string(git_commit),
                "Build Date": decode_string(build_date),
                "Build Profile": decode_string(build_profile),
                "Authorization ID": decode_string(authorization_id),
                "Key Fingerprint": decode_string(signing_key_fingerprint),
            }

        raise ValueError("Metadata section not found")

    finally:
        pe.close()


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <PE file>")
        sys.exit(1)

    try:
        metadata = parse_metadata(sys.argv[1])
    except (OSError, pefile.PEFormatError, ValueError) as exc:
        print(f"[ERROR] {exc}", file=sys.stderr)
        sys.exit(1)

    print("\n[7LAYERS / BUILD METADATA]\n")

    for key, value in metadata.items():
        print(f"{key:<20}: {value}")

    print()


if __name__ == "__main__":
    main()
