<div align="center">
    <img src="./rsrc/logo.png" width="30%">
</div>

# 7layers
A controlled ransomware emulation framework for adversary simulation, red team operations, and detection engineering.

## Disclaimer
This project and all associated materials are provided **strictly for authorized red teaming and educational purposes only.**

**Unauthorized engagements using this project and associated materials are strictly prohibited.** 
Unauthorized access on devices using this project and associated materials may cause serious legal consequences.

## Build
```bash
# Compile Commands
make            # Default
make clean      # Cleanup
make strip      # Symbol Removal
make rebuild    # Build After Cleanup

# Build Metadata
make rebuild BUILD_PROFILE=REDTEAM AUTHORIZATION_ID=LAB-2026-001 SIGNING_KEY_FINGERPRINT=AB12CD34
```

## Metadata Parsing
```bash
$ make rebuild BUILD_PROFILE=rusty AUTHORIZATION_ID=win11 SIGNING_KEY_FINGERPRINT=rusty
$ python3 ./scripts/meta.py ./bin/7layers_4.0.0_x64.exe

[7LAYERS / BUILD METADATA]

Build ID            : b94a8e03-50f4-430d-8b32-0e5fb3d1145e
Git Commit          : ffc6558de8ca
Build Date          : 2026-11-09T11:38:54Z
Build Profile       : rusty
Authorization ID    : win11
Key Fingerprint     : rusty

$ make rebuild
$ python3 ./scripts/meta.py ./bin/7layers_4.0.0_x64.exe

Build ID            : 00e5e573-40b0-4ea8-aec7-73f7adf79a4e
Git Commit          : fdf9be01c1ac
Build Date          : 2026-11-09T11:45:22Z
Build Profile       : UNVERIFIED
Authorization ID    : NONE
Key Fingerprint     : UNSIGNED

```

## Configuration
You can configure the file extensions and target directories that 7layers ransomware is allowed to encrypt by modifying `include/config.h`.

Any individual who modifies the HARD_DENY lists (`HARD_DENY_EXT`, `HARD_DENY_PATH`) assumes full responsibility for any consequences resulting from those modifications.

### Scope Setup
This list defines the scope of directory paths that the ransomware is permitted to encrypt. By default, all directories not explicitly included in the defined scope are excluded from encryption, and no configuration option is provided to include them as encryption targets by default.

`{ File Path, Allow Recursive (0 or 1), Max Recursive Search Depth }`

```c
static PATH_SCOPE SCOPE_PATH_LIST[] = {
    { "%USERPROFILE%\\Documents",   1, 5 },
    { "%USERPROFILE%\\Downloads",   1, 1 },
    { "%USERPROFILE%\\Desktop",     1, 3 },
    { "%USERPROFILE%\\Pictures",    1, 3 },
    { "%USERPROFILE%\\Videos",      1, 3 },
};
```

### Target File Extension Setup
This list defines the scope of file extensions that the ransomware is permitted to encrypt. **By default, all file extensions not explicitly included in the defined scope are excluded from encryption, and no configuration option is provided to include them as encryption targets by default**.

Supported File Types:
* Document
* Image
* Video
* Audio
* Text
* General
* Binary
* Dummy
* Script
* Dump
* VDisk

File types are included for classification purposes only and do not affect any functionality.

`{ File Type, File Extension (Lowercase) }`

```c
static FILE_EXTENSION_DATA SCOPE_EXT_LIST[] = {
    // Allowed: Text File
    { TEXT,     "txt"       },      // Plain Text
    { TEXT,     "md"        },      // Markdown
    { TEXT,     "csv"       },      // Comma-Separated Values
    { TEXT,     "tsv"       },      // Tab-Separated Values
    { TEXT,     "json"      },      // JSON Data
    { TEXT,     "xml"       },      // XML Document
    
    // ...

    // Allowed: Test Files
    { DUMMY,    "flag"      },      // Capture The Flag
    { DUMMY,    "target"    },      // Custom Test Target
    { DUMMY,    "dummy"     },      // Dummy Data
};
```


## MITRE ATT&CK TTPs
* [T1083 - File and Directory Discovery](https://attack.mitre.org/techniques/T1083/)
* [T1057 - Process Discovery](https://attack.mitre.org/techniques/T1057/)
* [T1486 - Data Encrypted for Impact](https://attack.mitre.org/techniques/T1486/)
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