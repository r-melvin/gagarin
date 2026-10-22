// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Menus cluster view of ProgressScreenClass (UI input/controls module). Read from the retail gamemd.exe
//   v1.001: RTTI .?AVProgressScreenClass@@ (vtable 0x7F0064; second base INoticeSource), the body at
//   0x643E80 (`MOV EAX,[ESP+4]; MOV [ECX+4],EAX; RET 4`), the three constructors 0x6429A0 / 0x6429E0 /
//   0x642A30 that store the vtable, and three direct callers in 0x684620 (`MOV ECX,0xAC4F58; PUSH ESI;
//   CALL 0x643E80`). The vtable holds this one slot (the word after it is padding before 8-byte-aligned
//   data).
//
//   Address-scoped view: the existing match/ui/progress_screen_class.h models the class as a pad plus
//   PlayerSide at +0x80 with no virtual; this view carries the vtable and the word slot 0 stores, and
//   repeats that member so the two views agree on the offset. Offsets only (no allocation site in this
//   cluster; the size 0x84 is modelled).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MENUS_PROGRESS_SCREEN_H
#define GG_MATCH_UI_INPUT_CONTROLS_MENUS_PROGRESS_SCREEN_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7F0064
class ProgressScreenClass
{
public:
    virtual void Slot0(int value);  // 0x643E80

    int Field04;       // +0x04
    char _pad008[0x78];
    int PlayerSide;    // +0x80 (SetSide 0x642B10 / GetSide 0x642B20, exact elsewhere)
};
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Field04) == 0x04);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, PlayerSide) == 0x80);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MENUS_PROGRESS_SCREEN_H
