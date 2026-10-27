#pragma once

#include "7layers.h"

// https://steve-s.gitbook.io/0xtriboulet/archive/notice/just-malicious/advanced-string-obfuscation

#define KEY                                                     \
    ((((__TIME__[7] - '0') * 1       +                          \
       (__TIME__[6] - '0') * 10      +                          \
       (__TIME__[4] - '0') * 60      +                          \
       (__TIME__[3] - '0') * 600     +                          \
       (__TIME__[1] - '0') * 3600    +                          \
       (__TIME__[0] - '0') * 36000) & 0xFF))

#define STR_MAX 64

#define ENC_CHAR(s, i)                                          \
    ((i) < sizeof(s)                                            \
        ? (unsigned char)((s)[i] ^ (unsigned char)KEY)          \
        : 0)

#define ENC_8(s, b)                                             \
    ENC_CHAR(s, (b) + 0),                                       \
    ENC_CHAR(s, (b) + 1),                                       \
    ENC_CHAR(s, (b) + 2),                                       \
    ENC_CHAR(s, (b) + 3),                                       \
    ENC_CHAR(s, (b) + 4),                                       \
    ENC_CHAR(s, (b) + 5),                                       \
    ENC_CHAR(s, (b) + 6),                                       \
    ENC_CHAR(s, (b) + 7)

#define ENC_16(s, b)                                            \
    ENC_8(s, b),                                                \
    ENC_8(s, (b) + 8)

#define ENC_32(s, b)                                            \
    ENC_16(s, b),                                               \
    ENC_16(s, (b) + 16)

#define ENC_64(s, b)                                            \
    ENC_32(s, b),                                               \
    ENC_32(s, (b) + 32)

static __attribute__((noinline, optimize("O0"), unused)) void str_decrypt(
    const volatile unsigned char *src,
    char *dst,
    size_t size,
    unsigned char key
) {
    size_t i;

    for (i = 0; i < size; ++i) {
        dst[i] = (char)(src[i] ^ key);
    }
}

#define OBF(str)                                                \
    ({                                                          \
        _Static_assert(                                         \
            sizeof(str) <= STR_MAX,                             \
            "OBF(): string too long"                            \
        );                                                      \
                                                                \
        static const unsigned char _enc[STR_MAX] = {            \
            ENC_64(str, 0)                                      \
        };                                                      \
                                                                \
        static char _dec[sizeof(str)] = {0};                    \
                                                                \
        str_decrypt(                                            \
            _enc,                                               \
            _dec,                                               \
            sizeof(str),                                        \
            (unsigned char)KEY                                  \
        );                                                      \
                                                                \
        _dec;                                                   \
    })

// ---

// RobloxPlayerBeta.dll Byfron Anti Disassembly

/*
1802c8a00  50                 push    rax {var_8}
1802c8a01  c7442404d1d10011   mov     dword [rsp+0x4 {var_8+0x4}], 0x1100d1d1
1802c8a09  448b4c2404         mov     r9d, dword [rsp+0x4 {var_8+0x4}]
1802c8a0e  41b894d362c4       mov     r8d, 0xc462d394
1802c8a14  4589cb             mov     r11d, r9d
1802c8a17  4183e301           and     r11d, 0x1
1802c8a1b  41ffc1             inc     r9d
1802c8a1e  4181c0eaa4e65d     add     r8d, 0x5de6a4ea  {0x2249787e}
1802c8a25  b8a2813b5e         mov     eax, 0x5e3b81a2
1802c8a2a  355f813b9e         xor     eax, 0x9e3b815f  {0xc00000fd}
1802c8a2f  4c39c0             cmp     rax, r8  {0x1}
1802c8a32  450f4fcb           cmovg   r9d, r11d
1802c8a36  4585c9             test    r9d, r9d
1802c8a39  7503               jne     0x1802c8a3e

1802c8a3b  42c78641b9ee784f…  mov     dword [rsi+0x78eeb941], 0x8141064f  {0x8141064f}
1802c8a46  c19b0847909c48     rcr     dword [rbx-0x636fb8f8], 0x48
1802c8a4d  812424fffeffff     and     dword [rsp {var_8}], 0xfffffeff

1802c8a3e  41b9ee784f06       mov     r9d, 0x64f78ee
1802c8a44  4181c19b084790     add     r9d, 0x9047089b  {0x64f78ee}  {0x96968189}
1802c8a4b  9c                 pushfq   {var_10}
1802c8a4c  48812424fffeffff   and     qword [rsp {var_10}], 0xfffffffffffffeff

=====================================================================
*  ANTI_DISASM()  —  anti-disassembly inline macro
*
*  Original (linear disassembly):
*      jne  +3           ; short jump over 0x42 0xC7 0x86
*      (dead code)       ; 42 C7 86 ...  (mov [rsi+0x78eeb941], ...)
*                        ; C1 9B ...     (rcr  [rbx-0x636fb8f8], 0x48)
*                        ; 81 24 24 ...  (and  [rsp], 0xFFFFFEFF)
*
*  Actual execution path:
*      jne  1f           ; skip 42 C7 86
*  1:  mov  r9d, 0x064F78EE
*      add  r9d, 0x9047089B
*      pushfq
*      and  qword ptr [rsp], ~0x100      ; clear TF in saved RFLAGS
*
*  WARNING:
*    - push rax  →  RSP -= 8
*    - pushfq    →  RSP -= 8
*    -> This macro does NOT restore RSP!
*       RSP is 16 bytes lower after expansion.
*       You must balance it yourself (see below).
*
*  Clobbers: RAX, R8, R9, R11, flags, memory
* =====================================================================
*/

#define ANTI_DISASM()                                                       \
    __asm__ __volatile__(                                                   \
        "pushq  %%rax                           \n\t"                       \
        "movl   $0x1100d1d1, 4(%%rsp)           \n\t"                       \
        "movl   4(%%rsp), %%r9d                 \n\t"                       \
        "movl   $0xc462d394, %%r8d              \n\t"                       \
        "movl   %%r9d, %%r11d                   \n\t"                       \
        "andl   $1, %%r11d                      \n\t"                       \
        "incl   %%r9d                           \n\t"                       \
        "addl   $0x5de6a4ea, %%r8d              \n\t"                       \
        "movl   $0x5e3b81a2, %%eax              \n\t"                       \
        "xorl   $0x9e3b815f, %%eax              \n\t"                       \
        "cmpq   %%r8, %%rax                     \n\t"                       \
        "cmovgl %%r11d, %%r9d                   \n\t"                       \
        "testl  %%r9d, %%r9d                    \n\t"                       \
        "jne    1f                              \n\t"                       \
        ".byte  0x42, 0xc7, 0x86                \n\t"                       \
        "1:                                     \n\t"                       \
        "addq   $8, %%rsp                       \n\t"                       \
        "movl   $0x064f78ee, %%r9d              \n\t"                       \
        "addl   $0x9047089b, %%r9d              \n\t"                       \
        "pushfq                                 \n\t"                       \
        "andq   $-0x101, (%%rsp)                \n\t"                       \
        "popfq                                  \n\t"                       \
        :                                                                   \
        :                                                                   \
        : "rax", "r8", "r9", "r11", "memory", "cc"                          \
    )

// ---

