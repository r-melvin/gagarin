// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x405AC0. The 0x21 threshold appears twice, once
//   against the descriptor's own value and once against the random value
//   returns, and both comparisons are unsigned (`JNC`).
#ifndef GG_MATCH_AUDIO_TRACK_GATE_METHODS_H
#define GG_MATCH_AUDIO_TRACK_GATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/randomizer.h"

struct Desc_00405AC0
{
    char _pad000[0x10];        // +0x0000
    unsigned int Flags;        // +0x0010  bits 3 and 7 mark it positional
    char _pad014[0x44];        // +0x0014
    int  At_58;                // +0x0058
    unsigned int At_5C;        // +0x005C
};
GG_STATIC_ASSERT(offsetof(Desc_00405AC0, Flags) == 0x10);
GG_STATIC_ASSERT(offsetof(Desc_00405AC0, At_58) == 0x58);
GG_STATIC_ASSERT(offsetof(Desc_00405AC0, At_5C) == 0x5C);

struct Track_00405AC0
{
    char _pad000[0x24];        // +0x0000
    Desc_00405AC0* Desc;       // +0x0024
    char _pad028[0x114];       // +0x0028
    unsigned int At_13C;       // +0x013C
    char _pad140[0x8];         // +0x0140
    void* At_148;              // +0x0148
    char _pad14C[0x11C];       // +0x014C
    int  At_268;               // +0x0268
};
GG_STATIC_ASSERT(offsetof(Track_00405AC0, Desc) == 0x24);
GG_STATIC_ASSERT(offsetof(Track_00405AC0, At_13C) == 0x13C);
GG_STATIC_ASSERT(offsetof(Track_00405AC0, At_148) == 0x148);
GG_STATIC_ASSERT(offsetof(Track_00405AC0, At_268) == 0x268);

struct Owner_00405AC0
{
    char _pad000[0xC0];        // +0x0000
    Track_00405AC0* Track;     // +0x00C0
};
GG_STATIC_ASSERT(offsetof(Owner_00405AC0, Track) == 0xC0);

// FUNCTION: GAMEMD 0x4047B0
void* __fastcall FUN_004047B0(Track_00405AC0* track);
// FUNCTION: GAMEMD 0x402790
void __fastcall FUN_00402790(Owner_00405AC0* owner, void* handle);

// FUNCTION: GAMEMD 0x405AC0
int __fastcall FUN_00405AC0(Owner_00405AC0* self);

#endif  // GG_MATCH_AUDIO_TRACK_GATE_METHODS_H
