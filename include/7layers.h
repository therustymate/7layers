#pragma once

#include <windows.h>
#include <winternl.h>

#include <vector>
#include <string>
#include <filesystem>

#include "config.h"

// -------------------------------------------

typedef struct _MEM_CTX {
    std::string                 name;
    void*                       base;
    void*                       entry;
    BYTE*                       image;
    int                         isDLL;
    IMAGE_DOS_HEADER*           dos;
    IMAGE_NT_HEADERS64*         nt;
    IMAGE_IMPORT_DESCRIPTOR*    import_dir;
    IMAGE_EXPORT_DIRECTORY*     export_dir;
} MEM_CTX;

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