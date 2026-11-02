#pragma once

#include <windows.h>
#include <winternl.h>

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>

#include "config.h"
#include "debug.h"
#include "csymbol.h"

#define MAX_MODULES 64
#define MAX_PATH 260

typedef struct _PE_CONTEXT {
    char                        name[MAX_PATH];
    void*                       base;
    void*                       entry;
    BYTE*                       image;
    int                         isDLL;
    IMAGE_DOS_HEADER*           dos;
    IMAGE_NT_HEADERS64*         nt;
    IMAGE_IMPORT_DESCRIPTOR*    import;
    IMAGE_EXPORT_DIRECTORY*     export;
    struct _PE_CONTEXT*         NextEntry;
} PE_CONTEXT;

extern PTEB g_TEB;
extern PPEB g_PEB;
extern PE_CONTEXT* g_PE_HEAD;

size_t c_wchar_to_char(const WCHAR *src, size_t src_len, char *dst, size_t dst_size);
void* c_memcpy(void* dst, const void* src, int len);
int c_memcmp(const void *b, const void *c, size_t len);
int c_wstrcmp(const WCHAR *a, const WCHAR *b);
int c_strcmp(const char *str1, const char *str2);
size_t c_strlen(const char* p);
char* c_strrchr(const char *str, int c);
int c_strcasecmp(const char *s1, const char *s2);
PTEB GetTEB();
PPEB GetPEB();