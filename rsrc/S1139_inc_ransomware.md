# INC Ransomware — MITRE ATT&CK Software S1139

원본: https://attack.mitre.org/software/S1139/

확인일: 2026-10-23  |  MITRE 버전: 1.0  |  기법 15개

INC Ransom이 운용하는 Windows 랜섬웨어로, 부분 암호화와 멀티스레딩을 사용합니다.

## Software Metadata

| 항목 | 값 |
| --- | --- |
| Software ID | `S1139` |
| Name | INC Ransomware |
| Type | MALWARE |
| Platforms | Windows |
| Version | 1.0 |
| Created | 2024-06-06 |
| Last Modified | 2024-10-28 |

## Techniques Used

| Domain | ID | Name | Use (요약) |
| --- | --- | --- | --- |
| Enterprise | [T1486](https://attack.mitre.org/techniques/T1486/) | Data Encrypted for Impact | 부분 암호화·멀티스레딩 이용 |
| Enterprise | [T1491.001](https://attack.mitre.org/techniques/T1491/001/) | Defacement: Internal Defacement | 몸값 요구 배경화면 표시 |
| Enterprise | [T1140](https://attack.mitre.org/techniques/T1140/) | Deobfuscate/Decode Files or Information | Base64로 인코딩된 메모 해독 |
| Enterprise | [T1652](https://attack.mitre.org/techniques/T1652/) | Device Driver Discovery | 특정 프린터 드라이버 존재 확인 |
| Enterprise | [T1083](https://attack.mitre.org/techniques/T1083/) | File and Directory Discovery | 인수로 암호화 대상 선택 |
| Enterprise | [T1490](https://attack.mitre.org/techniques/T1490/) | Inhibit System Recovery | 섀도 복사본 제거 |
| Enterprise | [T1570](https://attack.mitre.org/techniques/T1570/) | Lateral Tool Transfer | 침해 환경의 다른 단말로 실행 파일 이동 |
| Enterprise | [T1680](https://attack.mitre.org/techniques/T1680/) | Local Storage Discovery | 숨겨진 저장 드라이브 식별·마운트 |
| Enterprise | [T1106](https://attack.mitre.org/techniques/T1106/) | Native API | Windows API로 복구 데이터 처리 |
| Enterprise | [T1135](https://attack.mitre.org/techniques/T1135/) | Network Share Discovery | 네트워크 공유 드라이브 조회 |
| Enterprise | [T1120](https://attack.mitre.org/techniques/T1120/) | Peripheral Device Discovery | 외장 저장장치 및 프린터 확인 |
| Enterprise | [T1566](https://attack.mitre.org/techniques/T1566/) | Phishing | 스피어피싱을 초기 침투에 활용 |
| Enterprise | [T1057](https://attack.mitre.org/techniques/T1057/) | Process Discovery | 자원 점유 프로세스 식별 |
| Enterprise | [T1489](https://attack.mitre.org/techniques/T1489/) | Service Stop | 지정 프로세스 종료 |
| Enterprise | [T1047](https://attack.mitre.org/techniques/T1047/) | Windows Management Instrumentation | WMI로 다른 엔드포인트 접근 |

## Groups That Use This Software

| ID | Name | References (주요 출처) |
| --- | --- | --- |
| [G1032](https://attack.mitre.org/groups/G1032/) | INC Ransom | Secureworks, 보관된 분석 자료 |

## References

- [MITRE ATT&CK — INC Ransomware (S1139)](https://attack.mitre.org/software/S1139/)
- 증거 자료의 개별 출처와 상세 `Use` 설명은 위 MITRE 원본 페이지의 `References` 및 `Techniques Used` 열을 참조하세요.

> 안내: 모든 Techniques Used 행, Software Metadata 및 관련 그룹 표를 포함합니다. `Use` 열은 원문을 그대로 복제하지 않고 한국어로 간결하게 재서술했습니다.
