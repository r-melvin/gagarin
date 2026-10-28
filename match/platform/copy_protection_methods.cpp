// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// The retail image is the no-CD patched one: IsLauncherRunning, NotifyLauncher and
// CheckProtectedData each start with the 3-byte sequence  b0 01 c3
//   MOV AL, 0x1 ; RET            == return true;
// laid over their original first instructions (`push ecx; push ebx; push esi`,
// `sub esp,0x1c` and `sub esp,0x10`). The bodies below are the original functions:
// each matches retail everywhere except those 3 patched bytes. The patches are
// recorded in scripts/data/distribution_patches.json.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x49F5C0  CopyProtection::IsLauncherRunning   (__stdcall)
//   FUNCTION: GAMEMD 0x49F620  CopyProtection::NotifyLauncher      (__stdcall)
//   FUNCTION: GAMEMD 0x49F7A0  CopyProtection::CheckProtectedData  (__stdcall)

#include <windows.h>
#include <mmsystem.h>
#include "copy_protection_methods.h"
#include "../core/version_class_ctor_methods.h"

extern "C" int __cdecl strcmp(const char* a, const char* b);
#pragma intrinsic(strcmp)

void FUN_004068E0(const char*, ...);
unsigned int __fastcall FUN_0074F760(void* versionRecord);
extern VersionClass DAT_00A8ECE0;

LPVOID LauncherView;

namespace CopyProtection
{

// FUNCTION: GAMEMD 0x49F5C0  (__stdcall)
// PARTIAL: first 3 bytes are the patch (see above).
// True when another process already holds the launcher's named mutex.
bool __stdcall IsLauncherRunning()
{
    FUN_004068E0("COPYPROTECTION - Checking if launcher is running\n");
    HANDLE mutex = CreateMutexA(0, 0, "48BC11BD-C4D7-466b-8A31-C6ABBAD47B3E");
    bool running = GetLastError() == ERROR_ALREADY_EXISTS;
    if (mutex) {
        CloseHandle(mutex);
    }
    FUN_004068E0("result was %d\n", running);
    return running;
}

// FUNCTION: GAMEMD 0x49F620  (__stdcall)
// PARTIAL: the retail image is the patched one. Its first three bytes (the original
// `sub esp,0x1c` frame set-up) were overwritten with `mov al,1 / ret`, so this body is
// the original launcher handshake and matches retail everywhere except those 3 bytes.
// Opens the launcher's event, signals it, then waits for the launcher's 0xBEEF
// message and maps the shared view whose handle it carries.
bool __stdcall NotifyLauncher()
{
    MSG msg;
    FUN_004068E0("COPYPROTECTION - Notify launcher\n");
    PeekMessageA(&msg, 0, 0x400, 0x400, 0);
    DWORD start = timeGetTime();
    DWORD deadline = start + 60000;
    HANDLE ev = 0;
    while (timeGetTime() < deadline) {
        ev = OpenEventA(EVENT_MODIFY_STATE, TRUE, "D6E7FC97-64F9-4d28-B52C-754EDF721C6F");
        if (ev) {
            break;
        }
        Sleep(0);
    }
    if (ev) {
        SetEvent(ev);
        CloseHandle(ev);
        FUN_004068E0("Launcher notified.\n");
        FUN_004068E0("Waiting for message from launcher.\n");
        DWORD limit = timeGetTime() + 10000;
        while (timeGetTime() <= limit) {
            if (PeekMessageA(&msg, 0, 0xBEEF, 0xBEEF, PM_REMOVE) && msg.message == 0xBEEF) {
                LauncherView = MapViewOfFileEx((HANDLE)msg.lParam, 0xF001F, 0, 0, 0, 0);
                if (LauncherView) {
                    return true;
                }
                break;
            }
            Sleep(0);
        }
    }
    FUN_004068E0("***** Failed to notify launcher!\n");
    return false;
}

// FUNCTION: GAMEMD 0x49F7A0  (__stdcall)
// PARTIAL: first 3 bytes are the patch (see above); after the patch 93/95 instructions
// match (97.9%): the final `pop esi` is scheduled before the `cmp ecx,eax` instead of after it.
// Validates the data the launcher shared: its text must be "UIDATA,3DDATA,MAPS"; without
// a launcher view the registry copy of the ID must equal the version record's number.
bool __stdcall CheckProtectedData()
{
    FUN_004068E0("COPYPROTECTION - Validating\n");
    FUN_004068E0("_mProtectedData = %d (%s)\n", LauncherView, LauncherView ? LauncherView : "EEK!");
    if (LauncherView) {
        return strcmp((const char*)LauncherView, "UIDATA,3DDATA,MAPS") == 0;
    }
    HKEY key;
    DWORD size;
    DWORD type;
    DWORD value;
    if (RegOpenKeyExA(HKEY_CLASSES_ROOT, "WChat\\SysID", 0, KEY_READ, &key) == ERROR_SUCCESS) {
        size = 4;
        LONG rc = RegQueryValueExA(key, "ID", 0, &type, (LPBYTE)&value, &size);
        RegCloseKey(key);
        if (rc == ERROR_SUCCESS && type == REG_DWORD) {
            bool same = value == FUN_0074F760(&DAT_00A8ECE0);
            return same;
        }
    }
    return false;
}

}
