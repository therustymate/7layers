#pragma once

#include "7layers.h"

#define MAX_SCAN_BYTES 64

void* scan_raw_bytes(void* ptr, unsigned char* pattern, size_t pattern_size);
void* scan_raw_bytes_reverse(void* ptr, unsigned char* pattern, size_t pattern_size);