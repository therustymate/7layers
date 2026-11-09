#pragma once

#include "obfuscation.h"
#include <stdio.h>

#define LOG(TAG, MSG, ...)                                              \
do {                                                                    \
    if (DEBUG_MODE) {                                                   \
        char _msg[448] = {0};                                           \
        char _buf[512] = {0};                                           \
                                                                        \
        std::snprintf(_msg, sizeof(_msg), OBF(MSG), ##__VA_ARGS__);     \
        std::snprintf(_buf, sizeof(_buf), OBF("[%s] %s"), TAG, _msg);   \
        std::fprintf(stderr, "%s\n", _buf);                             \
    }                                                                   \
} while (0)

#define OKAY(MSG, ...) LOG(OBF("OKAY"), MSG, ##__VA_ARGS__)
#define FAIL(MSG, ...) LOG(OBF("FAIL"), MSG, ##__VA_ARGS__)
#define INFO(MSG, ...) LOG(OBF("INFO"), MSG, ##__VA_ARGS__)
#define WARN(MSG, ...) LOG(OBF("WARN"), MSG, ##__VA_ARGS__)
#define DBUG(MSG, ...) LOG(OBF("DBUG"), MSG, ##__VA_ARGS__)