// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and imports read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x622650: the dialog stack at 0xB72D28
//   (8-byte {HWND, id} entries reached as `LEA EDI,[ECX*8+0xB72D28]` /
//   `LEA EBX,[ECX*8+0xB72D2C]`) with its count at 0xB72F50 (INC'd, DEC'd on
//   failure), the current dialog at 0xB72F44 / 0xB72F48, the main window at
//   0xB73550, the module handle at 0xB732F0, the resource lookup 0x4A3B40
//   (__fastcall: ECX = id, EDX = 5 = RT_DIALOG), the post-create hook
//   0x5D4E70 (__fastcall, ECX = HWND) and the import
//   CreateDialogIndirectParamA at IAT 0x7E1450. The id arrives in CX and is
//   widened with `AND EBP,0xFFFF`; the LPARAM is the address of an 8-byte
//   local {WORD id, int param} at [ESP+0x14]. YRpp (consult-only, no
//   LICENSE) names UI::BeginDialog and Unsorted::GetResource; the sibling
//   match/ui/ui_end_dialog_methods.h pins the same stack and pops it.
#ifndef GG_MATCH_UI_UI_BEGIN_DIALOG_METHODS_H
#define GG_MATCH_UI_UI_BEGIN_DIALOG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct DialogEntry_00622650
{
    void* Window;   // +0x00
    int   Id;       // +0x04
};
GG_STATIC_ASSERT(sizeof(DialogEntry_00622650) == 0x8);

// The block handed to the dialog procedure as its LPARAM: the resource id
// and the caller's extra parameter.
struct DialogInit_00622650
{
    unsigned short Id;      // +0x00
    int            Param;   // +0x04
};
GG_STATIC_ASSERT(offsetof(DialogInit_00622650, Param) == 0x4);
GG_STATIC_ASSERT(sizeof(DialogInit_00622650) == 0x8);

// GLOBAL: GAMEMD 0xB72D28 — the open-dialog stack.
extern DialogEntry_00622650 DAT_00B72D28[];
// GLOBAL: GAMEMD 0xB72F50 — how many dialogs are open.
extern int DAT_00B72F50;
// GLOBAL: GAMEMD 0xB72F44 — the current dialog window.
extern void* DAT_00B72F44;
// GLOBAL: GAMEMD 0xB72F48 — the current dialog id.
extern int DAT_00B72F48;
// GLOBAL: GAMEMD 0xB73550 — the main window.
extern void* DAT_00B73550;
// GLOBAL: GAMEMD 0xB732F0 — the module handle (hInstance).
extern void* DAT_00B732F0;

// FUNCTION: GAMEMD 0x4A3B40 (decl; reloc) — Unsorted::GetResource: find, load
// and lock a resource by id and type.
void* __fastcall FUN_004A3B40(int id, const char* type);

// FUNCTION: GAMEMD 0x5D4E70 (decl; reloc) — record the new dialog window.
void __fastcall FUN_005D4E70(void* hWnd);

typedef int (__stdcall* DlgProc_00622650)(void*, unsigned int, unsigned int, long);

// FUNCTION: GAMEMD 0x622650 — UI::BeginDialog.
void* __fastcall UI_BeginDialog(unsigned short id, DlgProc_00622650 proc, int param);

#endif  // GG_MATCH_UI_UI_BEGIN_DIALOG_METHODS_H
