// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native window/dialog records and helper ABI: 0x622650, 0x775700,
// 0x775940, 0x7759E0 and 0x5E26C0. SDK handles use one consistent mode.
#ifndef GG_MATCH_UI_WINDOW_CONTRACTS_H
#define GG_MATCH_UI_WINDOW_CONTRACTS_H
#ifndef NO_STRICT
#define NO_STRICT
#endif
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct DialogEntry_00622650
{
    HWND Window;
    int Id;
};
GG_STATIC_ASSERT(offsetof(DialogEntry_00622650, Window) == 0);
GG_STATIC_ASSERT(offsetof(DialogEntry_00622650, Id) == 4);
GG_STATIC_ASSERT(sizeof(DialogEntry_00622650) == 8);

// Precise native four-stack-argument dialog ABI; NO_STRICT's SDK DLGPROC is generic FARPROC.
typedef int (__stdcall* DlgProc_00622650)(HWND, unsigned int, unsigned int, long);
typedef bool (__fastcall* DialogIdleProc_007759E0)();

// GLOBAL: GAMEMD 0x00B72D28
extern DialogEntry_00622650 DAT_00B72D28[];
// GLOBAL: GAMEMD 0x00B72F50
extern int DAT_00B72F50;
// GLOBAL: GAMEMD 0x00B72F44
extern HWND DAT_00B72F44;
// GLOBAL: GAMEMD 0x00B72F48
extern int DAT_00B72F48;
// GLOBAL: GAMEMD 0x00B73550
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x00B732F0
extern HINSTANCE DAT_00B732F0;

// CALLEE: GAMEMD 0x00775700
HWND __fastcall FUN_00775700(HINSTANCE context, int id, HWND parent, DlgProc_00622650 proc, int flags);
// CALLEE: GAMEMD 0x00775940
HWND __fastcall FUN_00775940(int id);
// CALLEE: GAMEMD 0x005E26C0
HWND __fastcall FUN_005E26C0();
// Callback AL is tested; the first stacked int is unread, the last two are byte flags.
// CALLEE: GAMEMD 0x007759E0
int __fastcall FUN_007759E0(HWND window, DialogIdleProc_007759E0 idle, int unknown, bool flag1, bool flag2);
// CALLEE: GAMEMD 0x0077F900
bool __fastcall FUN_0077F900();
#endif // GG_MATCH_UI_WINDOW_CONTRACTS_H
