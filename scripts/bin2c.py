import sys
from pathlib import Path

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} <input.bin> [variable_name]")
    sys.exit(1)

input_file = sys.argv[1]
var_name = sys.argv[2] if len(sys.argv) >= 3 else "data"

data = Path(input_file).read_bytes()

print(f"unsigned char {var_name}[] = {{")

for i in range(0, len(data), 12):
    chunk = data[i:i + 12]
    print("    " + ", ".join(f"0x{b:02x}" for b in chunk) + ",")

print("};")
print(f"unsigned int {var_name}_len = {len(data)};")
