import pefile
import sys

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} <mpengine.dll> <target_address>")
    sys.exit(1)

pe = pefile.PE(sys.argv[-2])

target = int(sys.argv[-1], 0)

for desc in pe.DIRECTORY_ENTRY_IMPORT:
    dll = desc.dll.decode(errors="replace")

    for imp in desc.imports:
        if imp.address == target:
            print(dll, imp.name, hex(imp.address))