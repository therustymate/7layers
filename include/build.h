#pragma once

#include <cstdint>

#pragma pack(push, 1)

struct BUILD_METADATA_RECORD {
    char magic[8];
    std::uint32_t version;

    char build_id[40];
    char git_commit[41];
    char build_date[32];
    char build_profile[24];
    char authorization_id[64];
    char signing_key_fingerprint[129];
};

#pragma pack(pop)
