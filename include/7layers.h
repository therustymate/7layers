#pragma once

#include <windows.h>
#include <winternl.h>
#include <stdio.h>

#include <filesystem>
#include <vector>
#include <string>

#include "config.h"

// -------------------------------------------

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