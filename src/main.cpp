#include "7layers.h"
#include "filesys.h"
#include "debug.h"
#include "obfuscation.h"

static int check_conflict_ext_scope() {
    ANTI_DISASM();
    size_t size_scope_ext   = (size_t)ARRAYSIZE(SCOPE_EXT_LIST);
    size_t size_deny_ext    = (size_t)ARRAYSIZE(HARD_DENY_EXT);

    for (int i=0; i < (int)size_deny_ext; i++) {
        for (int j=0; j < (int)size_scope_ext; j++) {
            if (c_strcmp(HARD_DENY_EXT[i].extension, SCOPE_EXT_LIST[j].extension) == 0) {
                WARN("Conflict on SCOPE_EXT_LIST:\t%s", HARD_DENY_EXT[i].extension);
                return -1;
            }
        }
    }
    return 0;
}

static int check_conflict_path_scope() {
    ANTI_DISASM();
    size_t size_scope_path  = (size_t)ARRAYSIZE(SCOPE_PATH_LIST);
    size_t size_deny_path   = (size_t)ARRAYSIZE(HARD_DENY_PATH);

    for (int i=0; i < (int)size_deny_path; i++) {
        for (int j=0; j < (int)size_scope_path; j++) {
            if (c_strcmp(HARD_DENY_PATH[i].path, SCOPE_PATH_LIST[j].path) == 0) {
                WARN("Conflict on SCOPE_PATH_LIST:\t%s", HARD_DENY_PATH[i].path);
                return -1;
            }
        }
    }
    return 0;
}

int main() {
    ANTI_DISASM();

    int conflict_on_path = check_conflict_path_scope();
    int conflict_on_ext  = check_conflict_ext_scope();

    if (conflict_on_path != 0 || conflict_on_ext != 0) {
        FAIL("Conflict detected in configuration");
        return -1;
    }

    // -------------------------------------------
    ANTI_DISASM();

    std::vector<std::string> resolved_paths;
    for (const auto& path_scope : SCOPE_PATH_LIST) {
        char resolved_path[MAX_PATH] = {0};
        DWORD len = ExpandEnvironmentStringsA(
            path_scope.path,
            resolved_path,
            MAX_PATH
        );

        if (len == 0 || len > MAX_PATH) {
            FAIL("Failed to resolve path: %s", path_scope.path);
            continue;
        }

        resolved_paths.emplace_back(resolved_path);
    }

    // -------------------------------------------
    ANTI_DISASM();

    for (std::string& path : resolved_paths) {
        if (!std::filesystem::exists(path)) {
            WARN("Path does not exist: %s", path.c_str());
            continue;
        }
        INFO("Found: %s", path.c_str());
    }

    DBUG("-------------------------------------------");

    // -------------------------------------------
    ANTI_DISASM();

    std::vector<std::string> queue;
    for (std::size_t i=0; i < resolved_paths.size(); i++) {
        const auto& path = resolved_paths[(int)i];
        const auto& path_scope = SCOPE_PATH_LIST[(int)i];

        if (enumerate_files(&queue, path, 0, path_scope.max_depth) != 0) {
            FAIL("Failed to enumerate files in: %s", path.c_str());
        }
    }

    for (const auto& file_path : queue) {
        INFO("Found: %s", file_path.c_str());
    }

    return 0;
}