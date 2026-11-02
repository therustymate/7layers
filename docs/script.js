// Side navigation: hero > TTP > actors > GitHub.
const sections = Array.from(document.querySelectorAll('#home, #ttp, #actors, #repository'));
const navigationLinks = Array.from(document.querySelectorAll('.sidebar-nav a[href^="#"]'));

function updateActiveNavigation() {
    const scrollPosition = window.scrollY + window.innerHeight * 0.45;
    let currentSection = 'home';

    for (const section of sections) {
        if (section.offsetTop <= scrollPosition) {
            currentSection = section.id;
        }
    }

    navigationLinks.forEach((link) => {
        const isActive = link.getAttribute('href') === `#${currentSection}`;
        link.classList.toggle('is-active', isActive);
        if (isActive) {
            link.setAttribute('aria-current', 'page');
        } else {
            link.removeAttribute('aria-current');
        }
    });
}

window.addEventListener('scroll', updateActiveNavigation, { passive: true });
window.addEventListener('resize', updateActiveNavigation);
updateActiveNavigation();

// Accordion: exactly one item remains expanded at all times.
const ttpRows = Array.from(document.querySelectorAll('[data-ttp-accordion] .ttp-item'));

function activateTtpRow(activeRow) {
    ttpRows.forEach((row) => {
        const isOpen = row === activeRow;
        const trigger = row.querySelector('.ttp-trigger');
        const panel = row.querySelector('.ttp-panel');

        row.classList.toggle('is-open', isOpen);
        trigger.setAttribute('aria-expanded', String(isOpen));
        panel.inert = !isOpen; // Collapsed links are not keyboard-focusable.
    });

}

ttpRows.forEach((row) => {
    row.querySelector('.ttp-trigger').addEventListener('click', () => activateTtpRow(row));
});


// Group and software mappings sourced from therustymate/7layers/mitre/*/README.md.
// The four technique themes are NOT intended as an attack sequence.
const actorProfiles = {
    akira: {
        name: 'AKIRA', category: 'RANSOMWARE / G1024',
        groupId: 'G1024', softwareId: 'S1129 / S1194 / S1191', alias: 'AKIRA_V2',
        stages: ['Remote access', 'File discovery', 'Recovery disruption', 'Data encryption'],
        techniques: ["T1531","T1560.001","T1059.001","T1486","T1213.002","T1685","T1482","T1567.002","T1133","T1657","T1036.005","T1027.001","T1219","T1021.001","T1018","T1558","T1078","T1083","T1490","T1106","T1135","T1057","T1082","T1047","T1543","T1480","T1654","T1489","T1059.003"],

        sourceUrl: 'https://github.com/therustymate/7layers/blob/main/mitre/Akira/README.md',
        mitreUrl: 'https://attack.mitre.org/groups/G1024/'
    },
    inc: {
        name: 'INC RANSOM', category: 'RANSOMWARE / G1032',
        groupId: 'G1032', softwareId: 'S1139', alias: 'INC RANSOMWARE',
        stages: ['Initial access', 'Remote services', 'Defacement', 'Data encryption'],
        techniques: ["T1087.002","T1071","T1560.001","T1059.003","T1486","T1074","T1685","T1190","T1657","T1070.004","T1105","T1570","T1036.005","T1046","T1135","T1588.002","T1069.002","T1566","T1219","T1021.001","T1049","T1569.002","T1537","T1078","T1047","T1491.001","T1140","T1652","T1083","T1490","T1680","T1106","T1120","T1057","T1489"],

        sourceUrl: 'https://github.com/therustymate/7layers/blob/main/mitre/INCRansom/README.md',
        mitreUrl: 'https://attack.mitre.org/groups/G1032/'
    },
    gentlemen: {
        name: 'THE GENTLEMEN', category: 'RANSOMWARE / G1058',
        groupId: 'G1058', softwareId: 'S9051', alias: 'STORM-2697',
        stages: ['Persistence', 'File discovery', 'Recovery disruption', 'Data encryption'],
        techniques: ["T1583.001","T1486","T1585","T1585.001","T1190","T1068","T1657","T1683.001","T1683.002","T1036","T1036.001","T1036.005","T1027.002","T1588.002","T1219.002","T1018","T1078","T1547.001","T1037.003","T1059.001","T1543.003","T1074.001","T1491.001","T1678","T1686.003","T1685","T1561.001","T1484.001","T1482","T1689","T1675","T1083","T1222.001","T1564.001","T1070.003","T1490","T1680","T1036.004","T1112","T1106","T1135","T1027","T1690","T1090","T1021.001","T1053.003","T1679","T1489","T1569.002","T1529","T1047"],

        sourceUrl: 'https://github.com/therustymate/7layers/blob/main/mitre/TheGentlemen/README.md',
        mitreUrl: 'https://attack.mitre.org/groups/G1058/'
    },
    galura: {
        name: 'WATER GALURA', category: 'QILIN / G1050',
        groupId: 'G1050', softwareId: 'S1242', alias: 'QILIN / AGENDA',
        stages: ['File discovery', 'Defacement', 'Recovery disruption', 'Data encryption'],
        techniques: ["T1486","T1585.001","T1657","T1548.002","T1134","T1087.001","T1071.002","T1547.001","T1059.001","T1491.001","T1678","T1685","T1484.001","T1480","T1190","T1083","T1222","T1070.004","T1490","T1570","T1680","T1036.004","T1112","T1106","T1135","T1027.013","T1003.001","T1069.002","T1566.001","T1057","T1055.001","T1012","T1219.002","T1021.002","T1018","T1688","T1053.005","T1489","T1082","T1016","T1007","T1529","T1204.001","T1673","T1047"],

        sourceUrl: 'https://github.com/therustymate/7layers/blob/main/mitre/WaterGalura/README.md',
        mitreUrl: 'https://attack.mitre.org/groups/G1050/'
    }
};

const actorTabs = Array.from(document.querySelectorAll('.actor-tab'));
const actorPanel = document.getElementById('actor-panel');
const actorFields = Array.from(document.querySelectorAll('[data-actor-field]'));
const actorStages = Array.from(document.querySelectorAll('[data-actor-stage]'));
const actorTechniques = document.querySelector('[data-actor-techniques]');
const actorTechniqueCount = document.querySelector('[data-actor-technique-count]');
const actorSource = document.querySelector('[data-actor-source]');
const actorMitre = document.querySelector('[data-actor-mitre]');
let activeActor = 'akira';

function activateActor(key, moveFocus = false) {
    const profile = actorProfiles[key];
    if (!profile || !actorPanel) return;
    if (key === activeActor) {
        if (moveFocus) actorTabs.find(tab => tab.dataset.actor === key)?.focus();
        return;
    }
    activeActor = key;
    actorTabs.forEach(tab => {
        const selected = tab.dataset.actor === key;
        tab.classList.toggle('is-active', selected);
        tab.setAttribute('aria-selected', String(selected));
        tab.tabIndex = selected ? 0 : -1;
        if (selected) actorPanel.setAttribute('aria-labelledby', tab.id);
        if (selected && moveFocus) tab.focus();
    });
    actorFields.forEach(element => {
        const field = element.dataset.actorField;
        element.textContent = profile[field] ?? '';
    });
    actorStages.forEach((element, index) => {
        element.textContent = profile.stages[index] || '';
    });
    actorTechniques.replaceChildren(...profile.techniques.map(id => {
        const link = document.createElement('a');
        link.href = `https://attack.mitre.org/techniques/${id.replace('.', '/')}/`;
        link.target = '_blank';
        link.rel = 'noopener noreferrer';
        link.append(document.createTextNode(id));
        const arrow = document.createElement('span');
        arrow.setAttribute('aria-hidden', 'true');
        arrow.textContent = '↗';
        link.append(arrow);
        link.setAttribute('aria-label', `MITRE ATT&CK technique ${id}, opens in new tab`);
        return link;
    }));
    actorTechniqueCount.textContent = `${profile.techniques.length} TECHNIQUES`;
    actorTechniques.scrollTop = 0;
    actorSource.href = profile.sourceUrl;
    actorMitre.href = profile.mitreUrl;
    actorPanel.classList.remove('is-revealed');
    void actorPanel.offsetWidth; // Restart reveal animation on rapid switches.
    actorPanel.classList.add('is-revealed');
}

actorTabs.forEach((tab, index) => {
    tab.addEventListener('click', () => activateActor(tab.dataset.actor));
    tab.addEventListener('keydown', event => {
        let targetIndex;
        switch (event.key) {
            case 'ArrowRight': case 'ArrowDown': targetIndex = (index + 1) % actorTabs.length; break;
            case 'ArrowLeft': case 'ArrowUp': targetIndex = (index - 1 + actorTabs.length) % actorTabs.length; break;
            case 'Home': targetIndex = 0; break;
            case 'End': targetIndex = actorTabs.length - 1; break;
            default: return;
        }
        event.preventDefault();
        activateActor(actorTabs[targetIndex].dataset.actor, true);
    });
});
