// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// IsLauncherRunning and CheckProtectedData are the 3-byte sequence  b0 01 c3
//   MOV AL, 0x1 ; RET            == return true;
// NotifyLauncher starts with the same 3 bytes but they are a patch over the
// original `sub esp,0x1c`; the original handshake body continues to 0x49F733.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x49F5C0  CopyProtection::IsLauncherRunning   (__stdcall)
//   FUNCTION: GAMEMD 0x49F620  CopyProtection::NotifyLauncher      (__stdcall)
//   FUNCTION: GAMEMD 0x49F7A0  CopyProtection::CheckProtectedData  (__stdcall)

#include <windows.h>
#include <mmsystem.h>
#include "copy_protection_methods.h"

void FUN_004068E0(const char*, ...);

LPVOID LauncherView;

namespace CopyProtection
{

// FUNCTION: GAMEMD 0x49F5C0  (__stdcall)
bool __stdcall IsLauncherRunning()
{
    return true;
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
bool __stdcall CheckProtectedData()
{
    return true;
}

}
