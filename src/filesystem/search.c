#include "filesystem.h"
#include "queue.h"

int scan_and_register(PathQueue* q, const char* path, int depth, int max_depth) {
    if (depth >= max_depth) return 0;

    char search_path[MAX_PATH];
    int n = snprintf(search_path, sizeof(search_path), "%s\\*", path);
    if (n < 0 || n >= (int)sizeof(search_path)) {
        FAIL("Path too long: %s", path);
        return -1;
    }

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        FAIL("Failed to find first file: %s (err=%lu)", search_path, GetLastError());
        return -1;
    }

    do {
        if (c_strcmp(findData.cFileName, ".") == 0 ||
            c_strcmp(findData.cFileName, "..") == 0) {
            continue;
        }

        char subpath[MAX_PATH];
        int m = snprintf(subpath, sizeof(subpath), "%s\\%s", path, findData.cFileName);
        if (m < 0 || m >= (int)sizeof(subpath)) {
            FAIL("Path too long, skipping: %s\\%s", path, findData.cFileName);
            continue;
        }

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
                continue;
            }
            scan_and_register(q, subpath, depth + 1, max_depth);
        } else {
            const char* ext = c_strrchr(findData.cFileName, '.');
            if (ext == NULL || ext == findData.cFileName) {
                continue;
            }
            ext++;

            // scan HARD_DENY_EXT
            int denied = 0;
            for (size_t i = 0; i < ARRAYSIZE(HARD_DENY_EXT); i++) {
                if (c_strcasecmp(ext, HARD_DENY_EXT[i].extension) == 0) {
                    denied = 1;
                    break;
                }
            }

            if (denied) {
                continue;
            }

            int in_scope = 0;
            for (size_t i = 0; i < ARRAYSIZE(SCOPE_EXT_LIST); i++) {
                if (c_strcasecmp(ext, SCOPE_EXT_LIST[i].extension) == 0) {
                    in_scope = 1;
                    break;
                }
            }

            if (in_scope) {
                if (queue_push(q, subpath) != 0) {
                    FAIL("Failed to enqueue: %s", subpath);
                } else {
                    continue;
                }
            }
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return 0;
}