#include "7layers.h"

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

size_t c_strlen(const char *p) {
    ANTI_DISASM();
    size_t i = 0;
    while(p && *p != '\0'){
        p++;
        i++;
    }
    return i;

}

PTEB GetTEB() {
    ANTI_DISASM();
    return (PTEB)__readgsqword(0x30);
}

PPEB GetPEB() {
    ANTI_DISASM();
    return (PPEB)((PTEB)(GetTEB())->ProcessEnvironmentBlock);
}