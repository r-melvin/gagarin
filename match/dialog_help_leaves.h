// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations of the small window helpers that dialog procedures call: the context-help
//   leaves at 0x776880 and 0x7768A0 and the centring leaf at 0x777060. Bodies and
//   addresses were read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
#ifndef GG_MATCH_PLATFORM_DIALOG_HELP_LEAVES_H
#define GG_MATCH_PLATFORM_DIALOG_HELP_LEAVES_H

#include <stddef.h>
#include <windows.h>
#include "_rt/gg_static_assert.h"

// The help-request record of WM_HELP, as 0x776880 reads it (window handle at +0x0C).
struct Dialog_00776880
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    HWND Window;   // +0x0C
    // FUNCTION: GAMEMD 0x776880 (decl; reloc)
    void FUN_00776880();
};
GG_STATIC_ASSERT(offsetof(Dialog_00776880, Window) == 0xC);

// FUNCTION: GAMEMD 0x7768A0 (decl; reloc)
void __fastcall FUN_007768A0(HWND window);
// FUNCTION: GAMEMD 0x777060 (decl; reloc)
void __fastcall FUN_00777060(HWND window);

#endif  // GG_MATCH_PLATFORM_DIALOG_HELP_LEAVES_H
