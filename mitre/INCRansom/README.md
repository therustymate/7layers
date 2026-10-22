# INC Ransom
[https://attack.mitre.org/groups/G1032/](https://attack.mitre.org/groups/G1032/)

| Item              | Value                     |
|:------------------|:--------------------------|
| ID                | G1032                     |
| Version           | 1.0                       |
| Created           | 06 June 2024              |
| Last Modified     | 31 July 2026              |

## Associated Group Descriptions
* [GOLD IONIC](https://www.secureworks.com/blog/gold-ionic-deploys-inc-ransomware)

## Techniques Used
* [T1087.002 - Account Discovery: Domain Account](https://attack.mitre.org/techniques/T1087/002/)
* [T1071 - Application Layer Protocol](https://attack.mitre.org/techniques/T1071/)
* [T1560.001 - Archive Collected Data: Archive via Utility](https://attack.mitre.org/techniques/T1560/001/)
* [T1059.003 - Command and Scripting Interpreter: Windows Command Shell](https://attack.mitre.org/techniques/T1059/003/)
* [T1486 - Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486/)
* [T1074 - Data Staged](https://attack.mitre.org/techniques/T1074/)
* [T1685 - Disable or Modify Tools](https://attack.mitre.org/techniques/T1685/)
* [T1190 - Exploit Public-Facing Application](https://attack.mitre.org/techniques/T1190/)
* [T1657 - Financial Theft](https://attack.mitre.org/techniques/T1657/)
* [T1070.004 - Indicator Removal: File Deletion](https://attack.mitre.org/techniques/T1070/004/)
* [T1105 - Ingress Tool Transfer](https://attack.mitre.org/techniques/T1105/)
* [T1570 - Lateral Tool Transfer](https://attack.mitre.org/techniques/T1570/)
* [T1036.005 - Masquerading: Match Legitimate Resource Name or Location](https://attack.mitre.org/techniques/T1036/005/)
* [T1046 - Network Service Discovery](https://attack.mitre.org/techniques/T1046/)
* [T1135 - Network Share Discovery](https://attack.mitre.org/techniques/T1135/)
* [T1588.002 - Obtain Capabilities: Tool](https://attack.mitre.org/techniques/T1588/002/)
* [T1069.002 - Permission Groups Discovery: Domain Groups](https://attack.mitre.org/techniques/T1069/002/)
* [T1566 - Phishing](https://attack.mitre.org/techniques/T1566/)
* [T1219 - Remote Access Tools](https://attack.mitre.org/techniques/T1219/)
* [T1021.001 - Remote Services: Remote Desktop Protocol](https://attack.mitre.org/techniques/T1021/001/)
* [T1049 - System Network Connections Discovery](https://attack.mitre.org/techniques/T1049/)
* [T1569.002 - System Services: Service Execution](https://attack.mitre.org/techniques/T1569/002/)
* [T1537 - Transfer Data to Cloud Account](https://attack.mitre.org/techniques/T1537/)
* [T1078 - Valid Accounts](https://attack.mitre.org/techniques/T1078/)
* [T1047 - Windows Management Instrumentation](https://attack.mitre.org/techniques/T1047/)

## INC Ransomware
[https://attack.mitre.org/software/S1139/](https://attack.mitre.org/software/S1139/)

| Domain | ID | Name | Use |
| --- | --- | --- | --- |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | [Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486) | [INC Ransomware](https://attack.mitre.org/software/S1139) can encrypt data on victim systems, including through the use of partial encryption and multi-threading to speed encryption.[[1]](https://www.sentinelone.com/anthology/inc-ransom/)[[2]](https://www.huntress.com/blog/investigating-new-inc-ransom-group-activity)[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf)[[5]](https://socradar.io/dark-web-profile-inc-ransom/)[[1]](https://www.sentinelone.com/anthology/inc-ransom/) |
| Enterprise | [T1491.001](https://attack.mitre.org/techniques/T1491/001/) | [Defacement](https://attack.mitre.org/techniques/T1491): [Internal Defacement](https://attack.mitre.org/techniques/T1491/001) | [INC Ransomware](https://attack.mitre.org/software/S1139) has the ability to change the background wallpaper image to display the ransom note.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf)[[3]](https://www.secureworks.com/blog/gold-ionic-deploys-inc-ransomware) |
| Enterprise | [T1140](https://attack.mitre.org/techniques/T1140/) | [Deobfuscate/Decode Files or Information](https://attack.mitre.org/techniques/T1140) | [INC Ransomware](https://attack.mitre.org/software/S1139) can run `CryptStringToBinaryA` to decrypt base64 content containing its ransom note.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1652](https://attack.mitre.org/techniques/T1652/) | [Device Driver Discovery](https://attack.mitre.org/techniques/T1652) | [INC Ransomware](https://attack.mitre.org/software/S1139) can verify the presence of specific drivers on compromised hosts including Microsoft Print to PDF and Microsoft XPS Document Writer.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | [File and Directory Discovery](https://attack.mitre.org/techniques/T1083) | [INC Ransomware](https://attack.mitre.org/software/S1139) can receive command line arguments to encrypt specific files and directories.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf)[[1]](https://www.sentinelone.com/anthology/inc-ransom/) |
| Enterprise | [T1490](https://attack.mitre.org/techniques/T1490/) | [Inhibit System Recovery](https://attack.mitre.org/techniques/T1490) | [INC Ransomware](https://attack.mitre.org/software/S1139) can delete volume shadow copy backups from victim machines.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1570](https://attack.mitre.org/techniques/T1570/) | [Lateral Tool Transfer](https://attack.mitre.org/techniques/T1570) | [INC Ransomware](https://attack.mitre.org/software/S1139) can push its encryption executable to multiple endpoints within compromised infrastructure.[[2]](https://www.huntress.com/blog/investigating-new-inc-ransom-group-activity) |
| Enterprise | [T1680](https://attack.mitre.org/techniques/T1680/) | [Local Storage Discovery](https://attack.mitre.org/techniques/T1680) | [INC Ransomware](https://attack.mitre.org/software/S1139) can discover and mount hidden drives to encrypt them.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1106](https://attack.mitre.org/techniques/T1106/) | [Native API](https://attack.mitre.org/techniques/T1106) | [INC Ransomware](https://attack.mitre.org/software/S1139) can use the API `DeviceIoControl` to resize the allocated space for and cause the deletion of volume shadow copy snapshots.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1135](https://attack.mitre.org/techniques/T1135/) | [Network Share Discovery](https://attack.mitre.org/techniques/T1135) | [INC Ransomware](https://attack.mitre.org/software/S1139) has the ability to check for shared network drives to encrypt.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1120](https://attack.mitre.org/techniques/T1120/) | [Peripheral Device Discovery](https://attack.mitre.org/techniques/T1120) | [INC Ransomware](https://attack.mitre.org/software/S1139) can identify external USB and hard drives for encryption and printers to print ransom notes.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1566](https://attack.mitre.org/techniques/T1566/) | [Phishing](https://attack.mitre.org/techniques/T1566) | [INC Ransomware](https://attack.mitre.org/software/S1139) campaigns have used spearphishing emails for initial access.[[1]](https://www.sentinelone.com/anthology/inc-ransom/) |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | [Process Discovery](https://attack.mitre.org/techniques/T1057) | [INC Ransomware](https://attack.mitre.org/software/S1139) can use the Microsoft Win32 Restart Manager to kill processes with a specific handle or that are accessing resources it wants to encrypt.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | [Service Stop](https://attack.mitre.org/techniques/T1489) | [INC Ransomware](https://attack.mitre.org/software/S1139) can issue a command to kill a process on compromised hosts.[[4]](https://web.archive.org/web/20231202022946/https://www.cybereason.com/hubfs/dam/collateral/reports/threat-alert-inc-ransomware.pdf) |
| Enterprise | [T1047](https://attack.mitre.org/techniques/T1047/) | [Windows Management Instrumentation](https://attack.mitre.org/techniques/T1047) | [INC Ransomware](https://attack.mitre.org/software/S1139) has the ability to use wmic.exe to spread to multiple endpoints within a compromised environment.[[2]](https://www.huntress.com/blog/investigating-new-inc-ransom-group-activity)[[3]](https://www.secureworks.com/blog/gold-ionic-deploys-inc-ransomware) |