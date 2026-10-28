// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Retail starts both functions with the single byte  c3  (RET), laid over their
// first instruction (`push esi` and `push ecx`) by the no-CD patch, so they are
// no-ops there. The bodies below are the original functions and match retail
// everywhere except that one byte; the patches are recorded in
// scripts/data/distribution_patches.json.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x49F740  CopyProtection::DispatchLauncherMessage (__fastcall)
//   FUNCTION: GAMEMD 0x49F8B0  CopyProtection::ShutDown                (__stdcall)

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "copy_protection_more_methods.h"

void FUN_004068E0(const char*, ...);
extern void* LauncherView;

namespace CopyProtection
{

// Win32 MSG; retail reads only message (+0x4) and lParam (+0xC).
struct MSG
{
    void* hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    long ptx;
    long pty;
};
GG_STATIC_ASSERT(offsetof(MSG, message) == 0x4);
GG_STATIC_ASSERT(offsetof(MSG, lParam) == 0xC);

// FUNCTION: GAMEMD 0x49F740  (__fastcall)
// PARTIAL: the first byte is the patch (see above).
// Handles the launcher's 0xBEEF message: maps the shared view its lParam handle names.
void DispatchLauncherMessage(MSG* pMsg)
{
    if (pMsg->message == 0xBEEF) {
        FUN_004068E0("COPYPROTECTION - Received message from launcher.\n");
        LauncherView = MapViewOfFileEx((HANDLE)pMsg->lParam, 0xF001F, 0, 0, 0, 0);
        if (!LauncherView) {
            FUN_004068E0("***** MapViewOfFileEx() Failed!");
            return;
        }
        FUN_004068E0("The message says: %s\n", LauncherView);
    }
}

// FUNCTION: GAMEMD 0x49F8B0  (__stdcall)
// PARTIAL: the first byte is the patch (see above).
// Unmaps the launcher view and deletes the registry ID value.
void __stdcall ShutDown()
{
    FUN_004068E0("COPYPROTECTION - Shutdown\n");
    if (LauncherView) {
        UnmapViewOfFile(LauncherView);
        LauncherView = 0;
    }
    HKEY key;
    if (RegOpenKeyExA(HKEY_CLASSES_ROOT, "WChat\\SysID", 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS) {
        RegDeleteValueA(key, "ID");
        RegCloseKey(key);
    }
}

}
