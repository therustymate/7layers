#include "7layers.h"
#include "debug.h"
#include "obfuscation.h"
#include "procsys.h"

#include <tlhelp32.h>

int enumerate_processes(std::vector<PROC_ENTRY>* queue) {
    if (!queue) return -1;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) return -1;

    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);

    if (!Process32FirstW(snapshot, &pe)) {
        CloseHandle(snapshot);

        return -1;
    }
    
    do {
        char proc_name[100] = {};

        const size_t convert_size = c_wchar_to_char(
            pe.szExeFile,
            std::wcslen(pe.szExeFile),
            proc_name,
            sizeof(proc_name) - 1
        );

        if (convert_size == 0) {
            continue;
        }

        proc_name[sizeof(proc_name) - 1] = '\0';

        int is_denied = 0;

        for (const auto& proc_scope : HARD_DENY_PROC) {
            const std::string& name = proc_scope.name;

            if (c_strcmp(proc_name, name.c_str()) == 0) {
                is_denied = 1;
                break;
            }
        }

        if (is_denied) {
            continue;
        }

        for (const auto& proc_scope : SCOPE_PROC_LIST) {
            const std::string& name = proc_scope.name;

            if (c_strcmp(proc_name, name.c_str()) == 0) {
                queue->emplace_back(PROC_ENTRY{
                    pe.th32ProcessID,
                    pe.th32ParentProcessID,
                    pe.szExeFile,
                    proc_scope.type
                });

                break;
            }
        }

    } while (Process32NextW(snapshot, &pe));

    CloseHandle(snapshot);

    return 0;
}