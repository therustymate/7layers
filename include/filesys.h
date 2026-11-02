#pragma once

#include "7layers.h"
#include "obfuscation.h"

int enumerate_files(std::vector<std::string>* queue, std::string path, int depth, int max_depth);