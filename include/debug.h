#pragma once

#include "7layers.h"
#include "obfuscation.h"

#if MP_ENGINE_MODE == 1

#define LOG_ODSA(TAG, MSG, ...) do {                            \
    if (DEBUG_MODE) {                                           \
        char _msg[448];                                         \
        char _buf[512];                                         \
                                                                \
        snprintf(_msg, sizeof(_msg), MSG, ##__VA_ARGS__);       \
        snprintf(                                               \
            _buf, sizeof(_buf),                                 \
            OBF("[%s] %s"),                                     \
            TAG, _msg                                           \
        );                                                      \
                                                                \
        OutputDebugStringA(_buf);                               \
    }                                                           \
} while (0)

#define OKAY(MSG, ...) LOG_ODSA("OKAY", OBF(MSG), ##__VA_ARGS__)
#define FAIL(MSG, ...) LOG_ODSA("FAIL", OBF(MSG), ##__VA_ARGS__)
#define INFO(MSG, ...) LOG_ODSA("INFO", OBF(MSG), ##__VA_ARGS__)
#define WARN(MSG, ...) LOG_ODSA("WARN", OBF(MSG), ##__VA_ARGS__)
#define DBUG(MSG, ...) LOG_ODSA("DBUG", OBF(MSG), ##__VA_ARGS__)

#else

#define OKAY(MSG, ...) do { if (DEBUG_MODE) { printf("[OKAY] "); printf(OBF(MSG), ##__VA_ARGS__); printf("\n"); } } while (0)
#define FAIL(MSG, ...) do { if (DEBUG_MODE) { fprintf(stderr, "[FAIL] "); fprintf(stderr, OBF(MSG), ##__VA_ARGS__); fprintf(stderr, "\n"); } } while (0)
#define INFO(MSG, ...) do { if (DEBUG_MODE) { printf("[INFO] "); printf(OBF(MSG), ##__VA_ARGS__); printf("\n"); } } while (0)
#define WARN(MSG, ...) do { if (DEBUG_MODE) { fprintf(stderr, "[WARN] "); fprintf(stderr, OBF(MSG), ##__VA_ARGS__); fprintf(stderr, "\n"); } } while (0)
#define DBUG(MSG, ...) do { if (DEBUG_MODE) { printf("[DBUG] "); printf(OBF(MSG), ##__VA_ARGS__); printf("\n"); } } while (0)

#endif