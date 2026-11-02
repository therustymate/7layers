#include "7layers.h"
#include "obfuscation.h"

size_t c_wchar_to_char(const WCHAR *src, size_t src_len, char *dst, size_t dst_size) {
    ANTI_DISASM();
    size_t i;

    if (!src || !dst || dst_size == 0) {
        return 0;
    }

    for (i = 0; i < src_len && i < dst_size - 1; i++) {
        WCHAR wc = src[i];

        if (wc > 0x7F)
            dst[i] = '?';
        else
            dst[i] = (char)wc;
    }

    dst[i] = '\0';
    return i;
}

void* c_memcpy(void* dst, const void* src, int len) {
    ANTI_DISASM();
    char* dest = (char*)dst;
    const char* source = (const char*)src;

    for (int i=0; i<len; i++) {
        dest[i] = source[i];
    }

    return dst;
}

int c_memcmp(const void *b, const void *c, size_t len) {
    ANTI_DISASM();
    const unsigned char *p = (const unsigned char *)b;
    const unsigned char *q = (const unsigned char *)c;

    while (len > 0) {
        if (*p != *q)
            return (int)*p - (int)*q;

        p++;
        q++;
        len--;
    }

    return 0;
}

int c_wstrcmp(const WCHAR *a, const WCHAR *b) {
    ANTI_DISASM();
    while (*a && *b) {
        if (*a != *b)
            return (int)*a - (int)*b;

        a++;
        b++;
    }

    return (int)*a - (int)*b;
}

int c_strcmp(const char *str1, const char *str2) {
    // Loop as long as characters match and we haven't hit the end of str1
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    
    // Return the ASCII difference of the first non-matching characters
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

size_t c_strlen(const char *p) {
    ANTI_DISASM();
    size_t i = 0;
    while(p && *p != '\0'){
        p++;
        i++;
    }
    return i;

}

char* c_strrchr(const char *str, int c) {
    const char *last = NULL;
    char ch = (char)c;

    while (*str != '\0') {
        if (*str == ch) {
            last = str;
        }
        str++;
    }

    // Check the null terminator itself, as strrchr includes '\0' in its search
    if (*str == ch) {
        last = str;
    }

    return (char *)last;
}

int c_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    // Return the difference between the remaining characters (handles different lengths)
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

PTEB GetTEB() {
    ANTI_DISASM();
    return (PTEB)__readgsqword(0x30);
}

PPEB GetPEB() {
    ANTI_DISASM();
    return (PPEB)((PTEB)(GetTEB())->ProcessEnvironmentBlock);
}