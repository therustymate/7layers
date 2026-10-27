<div align="center">
    <img src="./rsrc/logo.png" width="30%">
</div>

# 7layers
A controlled ransomware emulation framework for adversary simulation, red team operations, and detection engineering.

## Disclaimer
This project and all associated materials are provided **strictly for authorized red teaming and educational purposes only.**

**Unauthorized engagements using this project and associated materials are strictly prohibited.** 
Unauthorized access on devices using this project and associated materials may cause serious legal consequences.

## MITRE ATT&CK TTPs
* [T1486 - Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486/)
* [T1083 - File and Directory Discovery](https://attack.mitre.org/techniques/T1083/)
* [T1057 - Process Discovery](https://attack.mitre.org/techniques/T1057/)
* [T1491.001 - Defacement: Internal Defacement](https://attack.mitre.org/techniques/T1491/001/)
* [T1490 - Inhibit System Recovery](https://attack.mitre.org/techniques/T1490/)

## Reverse Engineering
* [Reverse Engineering: Windows Defender](./rev/WinDefender.md)
* [Reverse Engineering: Roblox Byfron](./rev/Byfron.md)


## Threat Actors & MITRE ATT&CK TTPs Analysis
| Group ID  | Group Name            | Analysis                                          |
|:----------|:----------------------|:--------------------------------------------------|
| G1058     | The Gentlemen         | [mitre/TheGentlemen](./mitre/TheGentlemen/)       |
| G1050     | Water Galura          | [mitre/WaterGalura](./mitre/WaterGalura/)         |
| G1024     | Akira                 | [mitre/Akira](./mitre/Akira/)                     |
| G1032     | INC Ransom            | [mitre/INCRansom](./mitre/INCRansom/)             |


## References
* Threat Actors & TTP Analysis
    * [https://www.zerofox.com/intelligence/september-2026-ransomware-wrap-up/](https://www.zerofox.com/intelligence/september-2026-ransomware-wrap-up/)
    * [https://www.microsoft.com/en-us/security/blog/2026/05/28/the-gentlemen-ransomware-dissecting-a-self-propagating-go-encryptor/](https://www.microsoft.com/en-us/security/blog/2026/05/28/the-gentlemen-ransomware-dissecting-a-self-propagating-go-encryptor/)
    * [https://www.gendigital.com/blog/insights/research/decrypted-akira-ransomware](https://www.gendigital.com/blog/insights/research/decrypted-akira-ransomware)
    * [https://areteir.com/resources/malware-spotlight-akira-ransomware](https://areteir.com/resources/malware-spotlight-akira-ransomware)
    * [https://medium.com/@venomtechofficial/inside-the-gentlemen-ransomware-reverse-engineering-static-analysis-c1b5585fa93b](https://medium.com/@venomtechofficial/inside-the-gentlemen-ransomware-reverse-engineering-static-analysis-c1b5585fa93b)
* MITRE ATT&CK
    * [https://attack.mitre.org/groups/G1058/](https://attack.mitre.org/groups/G1058/)
    * [https://attack.mitre.org/groups/G1050/](https://attack.mitre.org/groups/G1050/)
    * [https://attack.mitre.org/groups/G1024/](https://attack.mitre.org/groups/G1024/)
    * [https://attack.mitre.org/groups/G1032/](https://attack.mitre.org/groups/G1032/)
* GitHub
    * [https://github.com/MottaSec/akira-ransomware-reverse](https://github.com/MottaSec/akira-ransomware-reverse)
    * [https://github.com/Bedrock-Safeguard/gentlemen-decryptor](https://github.com/Bedrock-Safeguard/gentlemen-decryptor)
    * [https://github.com/LoupVaillant/Monocypher](https://github.com/LoupVaillant/Monocypher)
    * [https://github.com/claudiopizzillo/conti_v3](https://github.com/claudiopizzillo/conti_v3)