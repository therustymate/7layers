# Akira_v2 — MITRE ATT&CK Software S1194

원본: https://attack.mitre.org/software/S1194/

확인일: 2026-10-23  |  MITRE 버전: 1.0  |  기법 6개

VMware ESXi를 주로 노리는 Rust 기반 Akira 변종입니다.

## Software Metadata

| 항목 | 값 |
| --- | --- |
| Software ID | `S1194` |
| Name | Akira_v2 |
| Type | MALWARE |
| Platforms | MITRE 페이지에 명시되지 않음 (설명상 VMware ESXi 대상) |
| Version | 1.0 |
| Created | 2025-01-09 |
| Last Modified | 2025-03-11 |

## Techniques Used

| Domain | ID | Name | Use (요약) |
| --- | --- | --- | --- |
| Enterprise | [T1543](https://attack.mitre.org/techniques/T1543/) | Create or Modify System Process | 암호화를 위한 자식 프로세스 생성 |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | Data Encrypted for Impact | ESXi 저장소 경로의 파일 암호화 |
| Enterprise | [T1480](https://attack.mitre.org/techniques/T1480/) | Execution Guardrails | 지정 저장소 경로 존재 여부 확인 |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | File and Directory Discovery | 특정 파일·폴더 선택 |
| Enterprise | [T1654](https://attack.mitre.org/techniques/T1654/) | Log Enumeration | 여러 심각도 수준의 로그 열거 |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | Service Stop | 실행 중인 가상 머신 중지 |

## Groups That Use This Software

| ID | Name | References (주요 출처) |
| --- | --- | --- |
| [G1024](https://attack.mitre.org/groups/G1024/) | Akira | CISA, Cisco Talos, Unit 42 |

## References

- [MITRE ATT&CK — Akira_v2 (S1194)](https://attack.mitre.org/software/S1194/)
- 증거 자료의 개별 출처와 상세 `Use` 설명은 위 MITRE 원본 페이지의 `References` 및 `Techniques Used` 열을 참조하세요.

> 안내: 모든 Techniques Used 행, Software Metadata 및 관련 그룹 표를 포함합니다. `Use` 열은 원문을 그대로 복제하지 않고 한국어로 간결하게 재서술했습니다.
