# Megazord — MITRE ATT&CK Software S1191

원본: https://attack.mitre.org/software/S1191/

확인일: 2026-10-23  |  MITRE 버전: 1.0  |  기법 6개

Akira와 연결된 Rust 기반 Windows 랜섬웨어 변종입니다.

## Software Metadata

| 항목 | 값 |
| --- | --- |
| Software ID | `S1191` |
| Name | Megazord |
| Type | MALWARE |
| Platforms | Windows |
| Version | 1.0 |
| Created | 2025-01-08 |
| Last Modified | 2025-03-11 |

## Techniques Used

| Domain | ID | Name | Use (요약) |
| --- | --- | --- | --- |
| Enterprise | [T1059.003](https://attack.mitre.org/techniques/T1059/003/) | Command and Scripting Interpreter: Windows Command Shell | cmd.exe로 명령 실행 |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | Data Encrypted for Impact | 암호화 후 .powerranges 확장자 부여 |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | File and Directory Discovery | 지정 디렉터리를 암호화 대상에서 제외 |
| Enterprise | [T1654](https://attack.mitre.org/techniques/T1654/) | Log Enumeration | 로그 수준별 메시지 출력 |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | Process Discovery | 종료 대상 프로세스 파악 |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | Service Stop | 선택한 서비스와 프로세스 종료 |

## Groups That Use This Software

| ID | Name | References (주요 출처) |
| --- | --- | --- |
| [G1024](https://attack.mitre.org/groups/G1024/) | Akira | CISA, Cisco Talos, Unit 42 |

## References

- [MITRE ATT&CK — Megazord (S1191)](https://attack.mitre.org/software/S1191/)
- 증거 자료의 개별 출처와 상세 `Use` 설명은 위 MITRE 원본 페이지의 `References` 및 `Techniques Used` 열을 참조하세요.

> 안내: 모든 Techniques Used 행, Software Metadata 및 관련 그룹 표를 포함합니다. `Use` 열은 원문을 그대로 복제하지 않고 한국어로 간결하게 재서술했습니다.
