#pragma once

#include "7layers.h"
#include "obfuscation.h"

typedef struct _FILE_ENTRY {
    std::string path;
    size_t      size;
    FILE_TYPE   type;
} FILE_ENTRY;

int enumerate_files(std::vector<FILE_ENTRY>* queue, std::string path, int depth, int max_depth);