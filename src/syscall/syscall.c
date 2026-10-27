#include "7layers.h"
#include "syscall.h"
#include "scanner.h"

PVOID g_sys_ptr;
DWORD g_sys_ssn;

/*
[ RECOVERED SYSCALL STUB ]
#define ASM_OBF_SYSCALL {                   \
    __asm__ __volatile__(                   \
        "movq %%rcx, %%r10\n\t"             \
        "movl g_sys_ssn(%%rip), %%eax\n\t"  \
        "jmp *g_sys_ptr(%%rip)\n\t"         \
        :                                   \
        :                                   \
        : "rax", "r10"                      \
    );                                      \
}
*/

int set_syscall_ptr(PVOID ptr) {
    ANTI_DISASM();
    if (scan_raw_bytes(ptr, (unsigned char*)"\x0F\x05\xC3", 3) == NULL) {
        return 0;
    }

    g_sys_ptr = ptr;
    return 1;
}

int set_syscall_ssn(DWORD ssn) {
    ANTI_DISASM();
    g_sys_ssn = ssn;
    return 1;
}