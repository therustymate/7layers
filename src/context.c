#include "context.h"

PTEB g_TEB = NULL;
PPEB g_PEB = NULL;
PE_CONTEXT* g_PE_HEAD = NULL;

int initialize_environment_blocks(PPEB* peb, PTEB* teb) {
    ANTI_DISASM();
    if (!peb || !teb) {
        FAIL("Invalid parameters for PEB/TEB");
        return 0;
    }

    *teb = GetTEB();
    *peb = GetPEB();

    if (!*teb || !*peb) {
        *teb = (PTEB)NtCurrentTeb();
        if (*teb) {
            *peb = (PPEB)(*teb)->ProcessEnvironmentBlock;
        }
    }

    if (!*teb || !*peb) {
        FAIL("Invalid TEB/PEB.");
        return 0;
    }

    return 1;
}

void cleanup_pe_context(PE_CONTEXT** head) {
    ANTI_DISASM();
    if (!head) {
        FAIL("Invalid parameters for PE_CONTEXT cleanup");
        return;
    }

    PE_CONTEXT* curr = *head;

    while (curr) {
        PE_CONTEXT* next = curr->NextEntry;
        free(curr);
        curr = next;
    }

    *head = NULL;
}

int initialize_pe_context(PE_CONTEXT** head) {
    ANTI_DISASM();
    if (!head) {
        FAIL("Invalid parameters for PE_CONTEXT initialization");
        return 0;
    }

    *head = NULL;

    PCPEB_LDR_DATA ldr = (CPEB_LDR_DATA*)g_PEB->Ldr;

    if (!ldr) {
        FAIL("Invalid PEB_LDR_DATA.");
        return 0;
    }

    LIST_ENTRY* ldr_head = &ldr->InLoadOrderModuleList;
    LIST_ENTRY* ldr_curr = ldr->InLoadOrderModuleList.Flink;

    PE_CONTEXT *ctx_head = NULL;
    PE_CONTEXT *ctx_tail = NULL;

    while (ldr_curr != ldr_head) {
        CLDR_DATA_TABLE_ENTRY* ldr_data = (CLDR_DATA_TABLE_ENTRY*)ldr_curr;
        LIST_ENTRY *next = ldr_curr->Flink;
        
        char name[MAX_PATH];

        size_t len = c_wchar_to_char(
            ldr_data->BaseDllName.Buffer,
            ldr_data->BaseDllName.Length / sizeof(WCHAR),
            name,
            sizeof(name)
        );

        if (len == 0) {
            FAIL("Invalid char convert request");
            ldr_curr = next;
            continue;
        }
        
        void* base = ldr_data->DllBase;
        void* entry = ldr_data->EntryPoint;
        BYTE* image = (BYTE*)base;

        IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)image;
        if (dos->e_magic != IMAGE_DOS_SIGNATURE) {
            WARN("Invalid PE header: %s", name);
            ldr_curr = next;
            continue;
        }

        IMAGE_NT_HEADERS64* nt = (IMAGE_NT_HEADERS64*)(image + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE) {
            WARN("Invalid NT header: %s", name);
            ldr_curr = next;
            continue;
        }

        int isDLL = (nt->FileHeader.Characteristics & IMAGE_FILE_DLL) != 0;

        DWORD import_rva = (DWORD)nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        DWORD export_rva = (DWORD)nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

        IMAGE_IMPORT_DESCRIPTOR* import = NULL;
        IMAGE_EXPORT_DIRECTORY* export = NULL;

        if (import_rva != 0) {
            import = (IMAGE_IMPORT_DESCRIPTOR*)(image + import_rva);
        }

        if (export_rva != 0) {
            export = (IMAGE_EXPORT_DIRECTORY*)(image + export_rva);
        }

        PE_CONTEXT *new = calloc(1, sizeof(PE_CONTEXT));

        if (!new) {
            FAIL("calloc() failed for %s", name);
            cleanup_pe_context(&ctx_head);
            return 0;
        }

        new->base   = base;
        new->entry  = entry;
        new->image  = image;
        new->isDLL  = isDLL;
        new->dos    = dos;
        new->nt     = nt;
        new->import = import;
        new->export = export;
        new->NextEntry = NULL;

        c_memcpy(new->name, name, len + 1);

        if (ctx_head == NULL) {
            ctx_head = new;
            ctx_tail = new;
        } else {
            ctx_tail->NextEntry = new;
            ctx_tail = new;
        }

        INFO("PE context loaded: %s", name);

        ldr_curr = next;
    }

    *head = ctx_head;

    return 1;
}