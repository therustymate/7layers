#pragma once

#include "7layers.h"
#include "crypto/crypto.h"

typedef enum _SYSCALL_STATUS {
    SYSCALL_SSN_FOUND,
    SYSCALL_SSN_NOT_FOUND,
    SYSCALL_STUB_NOT_FOUND,
    SYSCALL_FUNCTION_HOOKED,
    SYSCALL_FUNCTION_NOT_HOOKED,
    SYSCALL_FUNCTION_NOT_FOUND,
    SYSCALL_ADDRESS_NOT_FOUND,
    SYSCALL_UNKNOWN_ERROR,
    SYSCALL_INVALID_PARAMETER,
    SYSCALL_INVALID_PE_CONTEXT,
    SYSCALL_MODULE_NOT_FOUND,
} SYSCALL_STATUS;

extern PVOID g_sys_ptr;
extern DWORD g_sys_ssn;

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

int set_syscall_ptr(PVOID ptr);
int set_syscall_ssn(DWORD ssn);


SYSCALL_STATUS get_ssn_halo_gate(DJB2_HASH* hash, DWORD* ssn);
SYSCALL_STATUS get_ssn_hell_gate(DJB2_HASH* hash, DWORD* ssn);