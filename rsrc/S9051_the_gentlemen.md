# The Gentlemen Ransomware — MITRE ATT&CK Software S9051

원본: https://attack.mitre.org/software/S9051/

확인일: 2026-10-23  |  MITRE 버전: 1.0  |  기법 45개

Go 기반 RaaS 랜섬웨어로 Windows·Linux·ESXi 등 여러 환경에 대응합니다.

## Software Metadata

| 항목 | 값 |
| --- | --- |
| Software ID | `S9051` |
| Name | The Gentlemen Ransomware |
| Type | MALWARE |
| Platforms | macOS, Linux, Windows, IaaS, ESXi, Network Devices |
| Version | 1.0 |
| Created | 2026-09-22 |
| Last Modified | 2026-09-30 |

## Techniques Used

| Domain | ID | Name | Use (요약) |
| --- | --- | --- | --- |
| Enterprise | [T1547.001](https://attack.mitre.org/techniques/T1547/001/) | Boot or Logon Autostart Execution: Registry Run Keys / Startup Folder | Run 레지스트리 키를 통한 지속성 |
| Enterprise | [T1037.003](https://attack.mitre.org/techniques/T1037/003/) | Boot or Logon Initialization Scripts: Network Logon Script | NETLOGON 공유를 통한 배포 |
| Enterprise | [T1037.004](https://attack.mitre.org/techniques/T1037/004/) | Boot or Logon Initialization Scripts: RC Scripts | ESXi에서 RC 스크립트로 지속성 |
| Enterprise | [T1059.001](https://attack.mitre.org/techniques/T1059/001/) | Command and Scripting Interpreter: PowerShell | 명령 실행과 보안 설정 변경 |
| Enterprise | [T1059.003](https://attack.mitre.org/techniques/T1059/003/) | Command and Scripting Interpreter: Windows Command Shell | 명령 실행·내부 이동 지원 |
| Enterprise | [T1059.012](https://attack.mitre.org/techniques/T1059/012/) | Command and Scripting Interpreter: Hypervisor CLI | ESXi 명령줄 도구 사용 |
| Enterprise | [T1543.003](https://attack.mitre.org/techniques/T1543/003/) | Create or Modify System Process: Windows Service | Windows 서비스 설정 조정 |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | Data Encrypted for Impact | XChaCha20 및 Curve25519 기반 암호화 |
| Enterprise | [T1074.001](https://attack.mitre.org/techniques/T1074/001/) | Data Staged: Local Data Staging | 도구·데이터를 로컬 경로에 준비 |
| Enterprise | [T1491.001](https://attack.mitre.org/techniques/T1491/001/) | Defacement: Internal Defacement | 몸값 요구 배경화면 설정 |
| Enterprise | [T1678](https://attack.mitre.org/techniques/T1678/) | Delay Execution | 암호화 시작을 지정 시간만큼 지연 |
| Enterprise | [T1686.003](https://attack.mitre.org/techniques/T1686/003/) | Disable or Modify System Firewall: Windows Host Firewall | Windows 방화벽 규칙 수정 |
| Enterprise | [T1685](https://attack.mitre.org/techniques/T1685/) | Disable or Modify Tools | 보안 및 백업 관련 도구 무력화 |
| Enterprise | [T1685.005](https://attack.mitre.org/techniques/T1685/005/) | Disable or Modify Tools: Clear Windows Event Logs | Windows 이벤트 로그 삭제 |
| Enterprise | [T1561.001](https://attack.mitre.org/techniques/T1561/001/) | Disk Wipe: Disk Content Wipe | 여유 공간 덮어쓰기로 복구 방해 |
| Enterprise | [T1484.001](https://attack.mitre.org/techniques/T1484/001/) | Domain or Tenant Policy Modification: Group Policy Modification | 그룹 정책을 변경해 동시 실행 유도 |
| Enterprise | [T1482](https://attack.mitre.org/techniques/T1482/) | Domain Trust Discovery | AD 도메인 관계·정보 조회 |
| Enterprise | [T1689](https://attack.mitre.org/techniques/T1689/) | Downgrade Attack | 레거시 SMB 기능 활성화 |
| Enterprise | [T1675](https://attack.mitre.org/techniques/T1675/) | ESXi Administration Command | ESXi 관리 명령 수행 |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | File and Directory Discovery | WMI/PowerShell로 파일·폴더 확인 |
| Enterprise | [T1222.001](https://attack.mitre.org/techniques/T1222/001/) | File and Directory Permissions Modification: Windows Permissions | 파일 소유권·접근 권한 수정 |
| Enterprise | [T1564.001](https://attack.mitre.org/techniques/T1564/001/) | Hide Artifacts: Hidden Files and Directories | 숨김 공유 폴더 사용 |
| Enterprise | [T1564.012](https://attack.mitre.org/techniques/T1564/012/) | Hide Artifacts: File/Path Exclusions | 보안 제품 검사 예외 추가 |
| Enterprise | [T1070.003](https://attack.mitre.org/techniques/T1070/003/) | Indicator Removal: Clear Command History | PowerShell 명령 이력 제거 |
| Enterprise | [T1070.004](https://attack.mitre.org/techniques/T1070/004/) | Indicator Removal: File Deletion | 포렌식 흔적과 실행 파일 삭제 |
| Enterprise | [T1070.007](https://attack.mitre.org/techniques/T1070/007/) | Indicator Removal: Clear Network Connection History and Configurations | RDP 관련 기록 제거 |
| Enterprise | [T1490](https://attack.mitre.org/techniques/T1490/) | Inhibit System Recovery | 섀도 복사본 및 백업 기능 방해 |
| Enterprise | [T1680](https://attack.mitre.org/techniques/T1680/) | Local Storage Discovery | 로컬 드라이브 문자 열거 |
| Enterprise | [T1036.004](https://attack.mitre.org/techniques/T1036/004/) | Masquerading: Masquerade Task or Service | 정상 작업·서비스처럼 이름 위장 |
| Enterprise | [T1112](https://attack.mitre.org/techniques/T1112/) | Modify Registry | 레지스트리 보안 설정 변경 |
| Enterprise | [T1106](https://attack.mitre.org/techniques/T1106/) | Native API | Windows API를 이용해 공유 조사 |
| Enterprise | [T1135](https://attack.mitre.org/techniques/T1135/) | Network Share Discovery | 공유 디렉터리·드라이브 검색 |
| Enterprise | [T1027](https://attack.mitre.org/techniques/T1027/) | Obfuscated Files or Information | Go 코드 난독화 |
| Enterprise | [T1027.010](https://attack.mitre.org/techniques/T1027/010/) | Obfuscated Files or Information: Command Obfuscation | 인코딩된 PowerShell 명령 사용 |
| Enterprise | [T1690](https://attack.mitre.org/techniques/T1690/) | Prevent Command History Logging | 명령 출력·로그를 남기지 않음 |
| Enterprise | [T1090](https://attack.mitre.org/techniques/T1090/) | Proxy | SOCKS 프록시를 통해 통신 |
| Enterprise | [T1021.001](https://attack.mitre.org/techniques/T1021/001/) | Remote Services: Remote Desktop Protocol | RDP 원격 접근 활성화 |
| Enterprise | [T1021.002](https://attack.mitre.org/techniques/T1021/002/) | Remote Services: SMB/Windows Admin Shares | SMB를 통한 내부 파일 전달 |
| Enterprise | [T1053.003](https://attack.mitre.org/techniques/T1053/003/) | Scheduled Task/Job: Cron | 부팅 후 cron 기반 실행 |
| Enterprise | [T1053.005](https://attack.mitre.org/techniques/T1053/005/) | Scheduled Task/Job: Scheduled Task | 예약 작업으로 반복 실행 |
| Enterprise | [T1679](https://attack.mitre.org/techniques/T1679/) | Selective Exclusion | 암호화·검사 예외 대상을 선택 |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | Service Stop | 서비스 및 실행 중 프로세스 중지 |
| Enterprise | [T1569.002](https://attack.mitre.org/techniques/T1569/002/) | System Services: Service Execution | 서비스 관리로 실행 환경 수정 |
| Enterprise | [T1529](https://attack.mitre.org/techniques/T1529/) | System Shutdown/Reboot | 가상 머신 종료 또는 재시작 |
| Enterprise | [T1047](https://attack.mitre.org/techniques/T1047/) | Windows Management Instrumentation | WMI를 통한 명령 및 드라이브 조회 |

## Groups That Use This Software

| ID | Name | References (주요 출처) |
| --- | --- | --- |
| [G1058](https://attack.mitre.org/groups/G1058/) | The Gentlemen | Microsoft, Trend AI, Huntress, Check Point |

## References

- [MITRE ATT&CK — The Gentlemen Ransomware (S9051)](https://attack.mitre.org/software/S9051/)
- 증거 자료의 개별 출처와 상세 `Use` 설명은 위 MITRE 원본 페이지의 `References` 및 `Techniques Used` 열을 참조하세요.

> 안내: 모든 Techniques Used 행, Software Metadata 및 관련 그룹 표를 포함합니다. `Use` 열은 원문을 그대로 복제하지 않고 한국어로 간결하게 재서술했습니다.
