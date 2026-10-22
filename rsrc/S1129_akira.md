# Akira — MITRE ATT&CK Software S1129

원본: https://attack.mitre.org/software/S1129/

확인일: 2026-10-23  |  MITRE 버전: 2.0  |  기법 10개

C++ 기반 Windows 랜섬웨어로, 파일 암호화와 다중 스레딩을 활용하는 Akira 계열입니다.

## Software Metadata

| 항목 | 값 |
| --- | --- |
| Software ID | `S1129` |
| Name | Akira |
| Type | MALWARE |
| Platforms | Windows |
| Version | 2.0 |
| Created | 2024-04-04 |
| Last Modified | 2025-03-11 |

## Techniques Used

| Domain | ID | Name | Use (요약) |
| --- | --- | --- | --- |
| Enterprise | [T1059.001](https://attack.mitre.org/techniques/T1059/001/) | Command and Scripting Interpreter: PowerShell | 볼륨 섀도 복사본 제거에 PowerShell 사용 |
| Enterprise | [T1059.003](https://attack.mitre.org/techniques/T1059/003/) | Command and Scripting Interpreter: Windows Command Shell | 명령줄 인수로 실행 제어 |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | Data Encrypted for Impact | ChaCha20/ChaCha8을 사용한 데이터 암호화 |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | File and Directory Discovery | 암호화 대상 파일의 속성 확인 |
| Enterprise | [T1490](https://attack.mitre.org/techniques/T1490/) | Inhibit System Recovery | 볼륨 섀도 복사본 삭제 |
| Enterprise | [T1106](https://attack.mitre.org/techniques/T1106/) | Native API | Windows 기본 API 호출 |
| Enterprise | [T1135](https://attack.mitre.org/techniques/T1135/) | Network Share Discovery | 원격 공유 파일 위치 식별 |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | Process Discovery | 섀도 복사본 제거 프로세스 상태 확인 |
| Enterprise | [T1082](https://attack.mitre.org/techniques/T1082/) | System Information Discovery | CPU 등 시스템 특성 확인 |
| Enterprise | [T1047](https://attack.mitre.org/techniques/T1047/) | Windows Management Instrumentation | 실행 중 WMI/COM 이용 |

## Groups That Use This Software

| ID | Name | References (주요 출처) |
| --- | --- | --- |
| [G1024](https://attack.mitre.org/groups/G1024/) | Akira | Trellix, Cisco Talos |

## References

- [MITRE ATT&CK — Akira (S1129)](https://attack.mitre.org/software/S1129/)
- 증거 자료의 개별 출처와 상세 `Use` 설명은 위 MITRE 원본 페이지의 `References` 및 `Techniques Used` 열을 참조하세요.

> 안내: 모든 Techniques Used 행, Software Metadata 및 관련 그룹 표를 포함합니다. `Use` 열은 원문을 그대로 복제하지 않고 한국어로 간결하게 재서술했습니다.
