// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, globals and the call target read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x449BC0.
//
// An eight-gate predicate with an early *yes*: the settings word at +0x408 must
// be present at all, and if the flag at +0x16B9 is clear that is already enough.
// Everything after it is the extra scrutiny that flag turns on, and any of those
// failing answers no.
//
// The global at 0xA8B238 is read twice - once before the two object checks and
// once after - so it is spelled out at each use rather than held.
#ifndef GG_MATCH_CORE_SMALL_MISC54_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC54_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Settings_00449BC0
{
    char _pad000[0x408];
    int  Mode;      // +0x0408
    char _pad40C[0x16B9 - 0x40C];
    char Strict;    // +0x16B9
};
GG_STATIC_ASSERT(offsetof(Settings_00449BC0, Mode) == 0x408);
GG_STATIC_ASSERT(offsetof(Settings_00449BC0, Strict) == 0x16B9);

// GLOBAL: GAMEMD 0xA8B238 — must be present; 0xA8B320 is a byte gate.
extern void* DAT_00A8B238;
extern char  DAT_00A8B320;

// FUNCTION: GAMEMD 0x50B730 — the owner test, __fastcall, byte result.
bool __fastcall FUN_0050B730(void* owner);

struct Obj_00449BC0
{
    char               _pad000[0x218];
    void*              Subject;    // +0x0218
    void*              Owner;      // +0x021C
    char               _pad220[0x2C0 - 0x220];
    int                Blocker;    // +0x02C0
    char               _pad2C4[0x520 - 0x2C4];
    Settings_00449BC0* Settings;   // +0x0520

    // FUNCTION: GAMEMD 0x449BC0
    bool FUN_00449BC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00449BC0, Subject) == 0x218);
GG_STATIC_ASSERT(offsetof(Obj_00449BC0, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_00449BC0, Blocker) == 0x2C0);
GG_STATIC_ASSERT(offsetof(Obj_00449BC0, Settings) == 0x520);

#endif  // GG_MATCH_CORE_SMALL_MISC54_METHODS_H
