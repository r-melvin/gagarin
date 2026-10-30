// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, globals and constants read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x405130 / 0x405140 /
//   0x405160 / 0x405170 / 0x42E6D0. None of these addresses is bound by YRpp,
//   so the types and entry points keep placeholder names.
//
// Four accessors on one object that all return a neutral value unless a shared
// global is set, plus one component-wise short-pair add.
#ifndef GG_MATCH_CORE_GUARDED_GETTER_METHODS_H
#define GG_MATCH_CORE_GUARDED_GETTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/audio_event_type.h"

// GLOBAL: GAMEMD 0x87E2A0 — the gate all four accessors below test first. Until
// it is set they report neutral values rather than reading the object.
extern void* DAT_0087E2A0;

// STRING: GAMEMD 0x816204 — "no events", the placeholder 0x405170 hands back
// while the gate is clear.
extern const char NoEventsString[];


// A pair of shorts passed by value in one four-byte stack slot: retail reads
// the halves separately with `MOV AX,[ESP+4]` and `MOV DX,[ESP+6]`, which is
// one argument split, not two arguments.
struct ShortPair
{
    short x;
    short y;
};

struct Obj_0042E600
{
    char  _pad00[0x4];
    short unknown_04;   // +0x0004
    short unknown_06;   // +0x0006

    // FUNCTION: GAMEMD 0x42E6D0
    void FUN_0042E6D0(ShortPair delta);
};
GG_STATIC_ASSERT(offsetof(Obj_0042E600, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0042E600, unknown_06) == 0x06);

#endif  // GG_MATCH_CORE_GUARDED_GETTER_METHODS_H
