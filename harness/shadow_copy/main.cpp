#include <windows.h>
#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h>
#include <cstdio>
#include <string>

#pragma comment(lib, "vssapi.lib")
#pragma comment(lib, "ole32.lib")

static FILE* g_log = nullptr;
static void LOG(const char* fmt, ...) {
    if (!g_log) return;
    va_list ap; va_start(ap, fmt);
    vfprintf(g_log, fmt, ap);
    va_end(ap);
    fflush(g_log);
}

static std::wstring GuidToString(const GUID& g) {
    wchar_t buf[64] = {0};
    StringFromGUID2(g, buf, 64);
    return buf;
}

void ListShadowCopies() {
    HRESULT hr;
    IVssBackupComponents* vssBackup = nullptr;
    IVssEnumObject* enumObject = nullptr;

    LOG("=== START ===\n");

    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    LOG("CoInitializeEx hr=0x%08X\n", (unsigned)hr);
    if (FAILED(hr)) return;

    hr = CreateVssBackupComponents(&vssBackup);
    LOG("CreateVssBackupComponents hr=0x%08X ptr=%p\n", (unsigned)hr, (void*)vssBackup);
    if (FAILED(hr)) { CoUninitialize(); return; }

    hr = vssBackup->InitializeForBackup();
    LOG("InitializeForBackup hr=0x%08X\n", (unsigned)hr);
    if (FAILED(hr)) goto cleanup;

    hr = vssBackup->SetContext(VSS_CTX_ALL);
    LOG("SetContext hr=0x%08X\n", (unsigned)hr);
    if (FAILED(hr)) goto cleanup;

    hr = vssBackup->Query(GUID_NULL, VSS_OBJECT_NONE, VSS_OBJECT_SNAPSHOT, &enumObject);
    LOG("Query hr=0x%08X enumObject=%p\n", (unsigned)hr, (void*)enumObject);
    if (FAILED(hr)) goto cleanup;

    {
        VSS_OBJECT_PROP prop;
        ULONG fetched = 0;
        int i = 0;
        while (true) {
            HRESULT nh = enumObject->Next(1, &prop, &fetched);
            LOG("Next hr=0x%08X fetched=%lu type=%d\n",
                (unsigned)nh, (unsigned long)fetched, (int)prop.Type);
            if (nh != S_OK || fetched != 1) break;

            if (prop.Type == VSS_OBJECT_SNAPSHOT) {
                VSS_SNAPSHOT_PROP& s = prop.Obj.Snap;
                std::wstring id  = GuidToString(s.m_SnapshotId);
                std::wstring vol = s.m_pwszOriginalVolumeName ? s.m_pwszOriginalVolumeName : L"(null)";
                std::wstring dev = s.m_pwszSnapshotDeviceObject ? s.m_pwszSnapshotDeviceObject : L"(null)";
                LOG("[%d] ID=%ls\n    vol=%ls\n    dev=%ls\n    ts=0x%016llX\n",
                    ++i, id.c_str(), vol.c_str(), dev.c_str(),
                    (unsigned long long)s.m_tsCreationTimestamp);
                VssFreeSnapshotProperties(&s);
            }
        }
        LOG("total snapshots = %d\n", i);
    }

cleanup:
    if (enumObject) enumObject->Release();
    if (vssBackup)  vssBackup->Release();
    CoUninitialize();
    LOG("=== END ===\n");
}

int main() {
    g_log = fopen("C:\\vss_log.txt", "w");
    if (!g_log) g_log = fopen("vss_log.txt", "w");
    if (!g_log) {
        MessageBoxA(nullptr, "log open failed", "err", MB_OK);
        return 1;
    }

    MessageBoxA(nullptr, "starting VSS query...", "checkpoint", MB_OK);

    ListShadowCopies();

    if (g_log) { fclose(g_log); g_log = nullptr; }
    MessageBoxA(nullptr, "done. see vss_log.txt", "checkpoint", MB_OK);
    return 0;
}