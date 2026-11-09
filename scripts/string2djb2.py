#!/usr/bin/env python3
import sys
import secrets


def djb2_hash(string: str, salt: int) -> int:
    hash_value = (5381 ^ salt) & 0xFFFFFFFF

    for c in string.encode("ascii"):
        hash_value = ((hash_value << 5) + hash_value) + c
        hash_value &= 0xFFFFFFFF

    return hash_value


def generate(api_names):
    for api in api_names:
        salt = secrets.randbits(32)
        value = djb2_hash(api, salt)

        print(
            f"[+] {api}: "
            f"SALT[0x{salt:08X}UL] "
            f"HASH[0x{value:08X}UL]"
        )


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <API> [API ...]")
        sys.exit(1)

    generate(sys.argv[1:])