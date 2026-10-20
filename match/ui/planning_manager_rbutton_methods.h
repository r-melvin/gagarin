// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x63AB00: byte loads/stores at 0xAC4CF4 and 0xAC4CB0,
//   dword compares at 0xA8ECC8 and 0xAC4BF0, and the two anchor dwords at
//   0xAC4C68 / 0xAC4C6C subtracted from the two stack arguments. YRpp names
//   0xAC4CF4 (PlanningModeActive) - name-only cross-check.
#ifndef GG_MATCH_UI_PLANNING_MANAGER_RBUTTON_METHODS_H
#define GG_MATCH_UI_PLANNING_MANAGER_RBUTTON_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xAC4CF4 — planning mode active (YRpp name).
extern bool DAT_00AC4CF4;
// GLOBAL: GAMEMD 0xAC4CB0 — cleared on every right-button release.
extern bool DAT_00AC4CB0;
// GLOBAL: GAMEMD 0xA8ECC8
extern int  DAT_00A8ECC8;
// GLOBAL: GAMEMD 0xAC4BF0 — the pending token; released when the click lands
// on the anchor.
extern int  DAT_00AC4BF0;
// GLOBAL: GAMEMD 0xAC4C68 — anchor X.
extern int  DAT_00AC4C68;
// GLOBAL: GAMEMD 0xAC4C6C — anchor Y.
extern int  DAT_00AC4C6C;

// FUNCTION: GAMEMD 0x63AB00 — YRpp: Unsorted::PlanningManager_WM_RBUTTONUP_63AB00.
void __stdcall FUN_0063AB00(int x, int y);

#endif  // GG_MATCH_UI_PLANNING_MANAGER_RBUTTON_METHODS_H
