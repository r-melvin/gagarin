// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   ProgressScreenClass.h (consult-only, no LICENSE; reconfirmed here).
//
// ProgressScreenClass — the load/progress screen. Only the PlayerSide accessor
// pair (SetSide/GetSide) is modelled in this TU; the full layout is P2.
#ifndef GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H
#define GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ProgressScreenClass
//
// SetSide @0x642B10:  MOV EAX,[ESP+4]; MOV [ECX+0x80],EAX; RET 4
// GetSide @0x642B20:  MOV EAX,[ECX+0x80]; RET
// Both touch only the single dword at +0x80 (YRpp: `PlayerSide`). The base is
// padded to 0x80; the full member set is P2.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7F0064 (RTTI .?AVProgressScreenClass@@; one slot). The
// constructors 0x6429A0 / 0x6429E0 / 0x642A30 store it at +0x00; slot 0 is
// 0x643E80 (`MOV EAX,[ESP+4]; MOV [ECX+4],EAX; RET 4`), called directly three
// times from 0x684620 with ECX = 0xAC4F58.
struct ProgressScreenClass
{
    virtual void Slot0(int value);  // slot 0, 0x643E80: stores +0x04

    void SetSide(int idx);        // GAMEMD 0x642B10 __thiscall
    int  GetSide();               // GAMEMD 0x642B20 __thiscall

    int  Field04;                 // +0x04, slot 0
    char _layout_pad_P2[0x78];    // +0x08 .. full layout = P2
    int  PlayerSide;              // +0x80
};

GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Field04) == 0x04);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, PlayerSide) == 0x80);

#endif  // GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H
