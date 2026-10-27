#pragma once

#include "7layers.h"

typedef struct _DJB2_HASH {
    int Id;
    unsigned long hash;
    unsigned long salt;
} DJB2_HASH;

unsigned long djb2_hash(unsigned char* string, unsigned long salt);