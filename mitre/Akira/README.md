# Akira
[https://attack.mitre.org/groups/G1024/](https://attack.mitre.org/groups/G1024/)

| Item              | Value                     |
|:------------------|:--------------------------|
| ID                | G1024                     |
| Version           | 2.0                       |
| Created           | 20 February 2024          |
| Last Modified     | 31 July 2026              |

## Associated Group Descriptions
* [GOLD SAHARA](https://www.secureworks.com/research/threat-profiles/gold-sahara)
* [PUNK SPIDER](https://www.crowdstrike.com/adversaries/punk-spider/)
* [Howling Scorpius](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/)

## Techniques Used
* [T1531 - Account Access Removal](https://attack.mitre.org/techniques/T1531/)
* [T1560.001 - Archive Collected Data: Archive via Utility](https://attack.mitre.org/techniques/T1560/001/)
* [T1059.001 - Command and Scripting Interpreter: PowerShell](https://attack.mitre.org/techniques/T1059/001/)
* [T1486 - Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486/)
* [T1213.002 - Data from Information Repositories: Sharepoint](https://attack.mitre.org/techniques/T1213/002/)
* [T1685 - Disable or Modify Tools](https://attack.mitre.org/techniques/T1685/)
* [T1482 - Domain Trust Discovery](https://attack.mitre.org/techniques/T1482/)
* [T1567.002 - Exfiltration Over Web Service: Exfiltration to Cloud Storage](https://attack.mitre.org/techniques/T1567/002/)
* [T1133 - External Remote Services](https://attack.mitre.org/techniques/T1133/)
* [T1657 - Financial Theft](https://attack.mitre.org/techniques/T1657/)
* [T1036.005 - Masquerading: Match Legitimate Resource Name or Location](https://attack.mitre.org/techniques/T1036/005/)
* [T1027.001 - Obfuscated Files or Information: Binary Padding](https://attack.mitre.org/techniques/T1027/001/)
* [T1219 - Remote Access Tools](https://attack.mitre.org/techniques/T1219/)
* [T1021.001 - Remote Services: Remote Desktop Protocol](https://attack.mitre.org/techniques/T1021/001/)
* [T1018 - Remote System Discovery](https://attack.mitre.org/techniques/T1018/)
* [T1558 - Steal or Forge Kerberos Tickets](https://attack.mitre.org/techniques/T1558/)
* [T1078 - Valid Accounts](https://attack.mitre.org/techniques/T1078/)

## Akira
* [https://attack.mitre.org/software/S1129/](https://attack.mitre.org/software/S1129/)


| Domain | ID | Name | Use |
| --- | --- | --- | --- |
| Enterprise | [T1059.001](https://attack.mitre.org/techniques/T1059/001/) | [Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059): [PowerShell](https://attack.mitre.org/techniques/T1059/001) | [Akira](https://attack.mitre.org/software/S1129) will execute PowerShell commands to delete system volume shadow copies.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/)[[2]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf) |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | [Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486) | [Akira](https://attack.mitre.org/software/S1129) can encrypt victim filesystems for financial extortion purposes including through the use of the ChaCha20 and ChaCha8 stream ciphers.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/)[[2]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf)[[3]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/) |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | [File and Directory Discovery](https://attack.mitre.org/techniques/T1083) | [Akira](https://attack.mitre.org/software/S1129) examines files prior to encryption to determine if they meet requirements for encryption and can be encrypted by the ransomware. These checks are performed through native Windows functions such as `GetFileAttributesW`.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/)[[3]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/) |
| Enterprise | [T1490](https://attack.mitre.org/techniques/T1490/) | [Inhibit System Recovery](https://attack.mitre.org/techniques/T1490) | [Akira](https://attack.mitre.org/software/S1129) will delete system volume shadow copies via PowerShell commands.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/)[[2]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf) |
| Enterprise | [T1106](https://attack.mitre.org/techniques/T1106/) | [Native API](https://attack.mitre.org/techniques/T1106) | [Akira](https://attack.mitre.org/software/S1129) executes native Windows functions such as `GetFileAttributesW` and `GetSystemInfo`.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/) |
| Enterprise | [T1135](https://attack.mitre.org/techniques/T1135/) | [Network Share Discovery](https://attack.mitre.org/techniques/T1135) | [Akira](https://attack.mitre.org/software/S1129) can identify remote file shares for encryption.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/) |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | [Process Discovery](https://attack.mitre.org/techniques/T1057) | [Akira](https://attack.mitre.org/software/S1129) verifies the deletion of volume shadow copies by checking for the existence of the process ID related to the process created to delete these items.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/) |
| Enterprise | [T1082](https://attack.mitre.org/techniques/T1082/) | [System Information Discovery](https://attack.mitre.org/techniques/T1082) | [Akira](https://attack.mitre.org/software/S1129) uses the `GetSystemInfo` Windows function to determine the number of processors on a victim machine.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/) |
| Enterprise | [T1047](https://attack.mitre.org/techniques/T1047/) | [Windows Management Instrumentation](https://attack.mitre.org/techniques/T1047) | [Akira](https://attack.mitre.org/software/S1129) will leverage COM objects accessed through WMI during execution to evade detection.[[1]](https://www.trellix.com/blogs/research/akira-ransomware/) |

## Akira_v2
* [https://attack.mitre.org/software/S1194/](https://attack.mitre.org/software/S1194/)


| Domain | ID | Name | Use |
| --- | --- | --- | --- |
| Enterprise | [T1543](https://attack.mitre.org/techniques/T1543/) | [Create or Modify System Process](https://attack.mitre.org/techniques/T1543) | [Akira \_v2](https://attack.mitre.org/software/S1194) can create a child process for encryption.[[1]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf) |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | [Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486) | The [Akira \_v2](https://attack.mitre.org/software/S1194) encryptor targets the `/vmfs/volumes/` path by default and can use the rust-crypto 0.2.36 library crate for the encryption processes.[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/)[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1480](https://attack.mitre.org/techniques/T1480/) | [Execution Guardrails](https://attack.mitre.org/techniques/T1480) | [Akira \_v2](https://attack.mitre.org/software/S1194) will fail to execute if the targeted `/vmfs/volumes/` path does not exist or is not defined.[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/) |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | [File and Directory Discovery](https://attack.mitre.org/techniques/T1083) | [Akira \_v2](https://attack.mitre.org/software/S1194) can target specific files and folders for encryption.[[1]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf)[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/)[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1654](https://attack.mitre.org/techniques/T1654/) | [Log Enumeration](https://attack.mitre.org/techniques/T1654) | [Akira \_v2](https://attack.mitre.org/software/S1194) can enumerate the trace, debug, error, info, and warning logs on targeted systems.[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/)[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | [Service Stop](https://attack.mitre.org/techniques/T1489) | [Akira \_v2](https://attack.mitre.org/software/S1194) can stop running virtual machines.[[1]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf)[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/)[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |

## Megazord
* [https://attack.mitre.org/software/S1191/](https://attack.mitre.org/software/S1191/)


| Domain | ID | Name | Use |
| --- | --- | --- | --- |
| Enterprise | [T1059.003](https://attack.mitre.org/techniques/T1059/003/) | [Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059): [Windows Command Shell](https://attack.mitre.org/techniques/T1059/003) | [Megazord](https://attack.mitre.org/software/S1191) can execute multiple commands post infection via `cmd.exe`.[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | [Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486) | [Megazord](https://attack.mitre.org/software/S1191) can encrypt files on targeted Windows hosts leaving them with a ".powerranges" file extension.[[1]](https://www.cisa.gov/sites/default/files/2024-04/aa24-109a-stopransomware-akira-ransomware_2.pdf)[[2]](https://blog.talosintelligence.com/akira-ransomware-continues-to-evolve/)[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | [File and Directory Discovery](https://attack.mitre.org/techniques/T1083) | [Megazord](https://attack.mitre.org/software/S1191) can ignore specified directories for encryption.[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1654](https://attack.mitre.org/techniques/T1654/) | [Log Enumeration](https://attack.mitre.org/techniques/T1654) | [Megazord](https://attack.mitre.org/software/S1191) has the ability to print the trace, debug, error, info, and warning logs.[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | [Process Discovery](https://attack.mitre.org/techniques/T1057) | [Megazord](https://attack.mitre.org/software/S1191) can terminate a list of specified services and processes.[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | [Service Stop](https://attack.mitre.org/techniques/T1489) | [Megazord](https://attack.mitre.org/software/S1191) has the ability to terminate a list of services and processes.[[3]](https://unit42.paloaltonetworks.com/threat-assessment-howling-scorpius-akira-ransomware/) |
