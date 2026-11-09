#include "build.h"

extern "C" {
    extern const BUILD_METADATA_RECORD g_7layers_meta
        __attribute__((used, section(".meta"))) = {
            "7LAYERS",
            1,
            BUILD_ID,
            BUILD_GIT_COMMIT,
            BUILD_DATE,
            BUILD_PROFILE,
            BUILD_AUTHORIZATION_ID,
            BUILD_SIGNING_KEY_FINGERPRINT
        };
}
