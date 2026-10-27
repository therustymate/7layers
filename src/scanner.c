#include "7layers.h"
#include "scanner.h"

void* scan_raw_bytes(void* ptr, unsigned char* pattern, size_t pattern_size) {
    ANTI_DISASM();
    if (!ptr || !pattern || pattern_size == 0 || pattern_size > MAX_SCAN_BYTES) {
        FAIL("Invalid parameters for scan_raw_bytes()");
        return NULL;
    }

    unsigned char* raw = (unsigned char*)ptr;

    for (size_t i = 0; i < MAX_SCAN_BYTES - pattern_size; i++) {
        if (c_memcmp(raw + i, pattern, pattern_size) == 0) {
            return (void*)(raw + i); // Return pointer to found pattern
        }
    }

    return NULL; // Pattern not found
}

void* scan_raw_bytes_reverse(void* ptr, unsigned char* pattern, size_t pattern_size) {
    ANTI_DISASM();
    if (!ptr || !pattern || pattern_size == 0 || pattern_size > MAX_SCAN_BYTES) {
        FAIL("Invalid parameters for scan_raw_bytes_reverse()");
        return NULL;
    }

    unsigned char* raw = (unsigned char*)ptr;

    for (size_t i = 0; i < MAX_SCAN_BYTES - pattern_size; i++) {
        if (c_memcmp(raw - i, pattern, pattern_size) == 0) {
            return (void*)(raw - i);
        }
    }

    return NULL;
}

void* scan_address(void* ptr, unsigned char* pattern, size_t pattern_size) {
    ANTI_DISASM();
    if (!ptr || !pattern || pattern_size == 0 || pattern_size > MAX_SCAN_BYTES) {
        FAIL("Invalid parameters for scan_raw_bytes_reverse()");
        return NULL;
    }

    unsigned char* raw = (unsigned char*)ptr;

    if (c_memcmp(raw, pattern, pattern_size) == 0) {
        return (void*)(raw);
    }

    return NULL;
}