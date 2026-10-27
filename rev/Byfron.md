# Reverse Engineering: Roblox Byfron

## Anti Disassembly
![](../rsrc/re/byfron/func_run.png)

```
0x1802c8a39 jne 0x1802c8a3e

0x1802c8a3b mov dword [rsi+0x78eeb941], 0x8141064f  {0x8141064f}
0x1802c8a46 rcr dword [rbx-0x636fb8f8], 0x48
0x1802c8a4d and dword [rsp {var_8}], 0xfffffeff

0x1802c8a3e mov r9d, 0x64f78ee

```

