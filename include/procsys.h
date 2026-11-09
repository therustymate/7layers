#pragma once

#include "7layers.h"
#include "obfuscation.h"

typedef struct _PROC_ENTRY {
    DWORD           pid;
    DWORD           ppid;
    std::wstring    name;
    PROC_TYPE       type;
} PROC_ENTRY;

int enumerate_processes(std::vector<PROC_ENTRY>* queue);
int terminate_by_pid(DWORD pid);