// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x46FB50. Imports from the IAT thunks at 0x7E14A8
//   (GetDlgItem) and 0x7E14A0 (EnableWindow). The byte read is
//   `[ECX + 0x89E000]` with ECX from 0xA8DA8C, so 0x89E000 is a byte array
//   indexed by that global.
#ifndef GG_MATCH_UI_DIALOG_ENABLE_METHODS_H
#define GG_MATCH_UI_DIALOG_ENABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HWND__;
typedef HWND__* HWND_;

// USER32, dllimport so the calls go indirect through the IAT.
extern "C" __declspec(dllimport) HWND_ __stdcall GetDlgItem(HWND_ dlg, int id);
extern "C" __declspec(dllimport) int __stdcall EnableWindow(HWND_ wnd, int enable);

// GLOBAL: GAMEMD 0xA8DA84 — how many are in use.
extern int DAT_00A8DA84;
// GLOBAL: GAMEMD 0xA8D580 — how many there is room for.
extern int DAT_00A8D580;
// GLOBAL: GAMEMD 0xA8DA8C — the current index into the flag array.
extern int DAT_00A8DA8C;
// GLOBAL: GAMEMD 0x89E000 — one flag per slot.
extern char DAT_0089E000[];

// FUNCTION: GAMEMD 0x46FB50
void FUN_0046FB50(HWND_ dlg);

#endif  // GG_MATCH_UI_DIALOG_ENABLE_METHODS_H
