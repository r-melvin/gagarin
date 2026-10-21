// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and imports read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x622720: the dialog stack at 0xB72D28
//   (8-byte {HWND, id} entries) with its count at 0xB72F50, the current
//   dialog at 0xB72F44 / 0xB72F48, the main window at 0xB73550, the input
//   manager pointer at 0x87F770 (0x54F720 __thiscall, no args), 0x608070
//   (ECX = HWND), CRT memcpy at 0x7CA090 out of line, and the imports
//   DestroyWindow (0x7E13F4), SetForegroundWindow (0x7E14D0), SetFocus
//   (0x7E13CC). YRpp (consult-only, no LICENSE) names EndDialog and
//   InputManagerClass::Instance; BeginDialog at 0x622650 pushes the same
//   stack.
#ifndef GG_MATCH_UI_UI_END_DIALOG_METHODS_H
#define GG_MATCH_UI_UI_END_DIALOG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/input_manager_class_methods.h"

struct DialogEntry_00622720
{
    void* Window;   // +0x00
    int   Id;       // +0x04
};
GG_STATIC_ASSERT(sizeof(DialogEntry_00622720) == 0x8);

// GLOBAL: GAMEMD 0xB72D28 — the open-dialog stack.
extern DialogEntry_00622720 DAT_00B72D28[];
// GLOBAL: GAMEMD 0xB72F50 — how many dialogs are open.
extern int DAT_00B72F50;
// GLOBAL: GAMEMD 0xB72F44 — the current dialog window.
extern void* DAT_00B72F44;
// GLOBAL: GAMEMD 0xB72F48 — the current dialog id.
extern int DAT_00B72F48;
// GLOBAL: GAMEMD 0xB73550 — the main window.
extern void* DAT_00B73550;

// FUNCTION: GAMEMD 0x608070 (decl; reloc) — detach the window's gadget list.
void __fastcall FUN_00608070(void* hWnd);

// FUNCTION: GAMEMD 0x622720 (decl; reloc) — UI::EndDialog.
void __fastcall UI_EndDialog(void* hWnd);

#endif  // GG_MATCH_UI_UI_END_DIALOG_METHODS_H
