// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the allocation size and both call targets read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4381D0 and
//   0x438300. Neither is bound by YRpp or the seed map.
//
// A lazily-created sink at +0x0C plus a two-argument forward to it. The two
// entry points are the same code twice, down to the call targets - only their
// addresses differ - so each is written out longhand per the family rule.
#ifndef GG_MATCH_CORE_LAZY_SINK_FORWARD_METHODS_H
#define GG_MATCH_CORE_LAZY_SINK_FORWARD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The YR global allocator (operator new @ 0x7C8E17), __cdecl - retail pushes
// the size and adjusts ESP itself.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

struct Sink_00437F50
{
    // FUNCTION: GAMEMD 0x437F50 — constructor, returns `this` in EAX, which is
    // what lets the allocation and the construction share one register.
    Sink_00437F50* FUN_00437F50();
    // FUNCTION: GAMEMD 0x437FD0 — the forward target, __thiscall, two 4-byte
    // arguments pushed in source order (retail reads the second argument slot
    // first, then the first, then pushes them back the other way round).
    void FUN_00437FD0(int first, int second);
};

struct Owner_004381D0
{
    char           _pad000[0xC];
    Sink_00437F50* Sink;   // +0x000C

    // FUNCTION: GAMEMD 0x4381D0
    void FUN_004381D0(int first, int second);
    // FUNCTION: GAMEMD 0x438300
    void FUN_00438300(int first, int second);
};
GG_STATIC_ASSERT(offsetof(Owner_004381D0, Sink) == 0xC);

#endif  // GG_MATCH_CORE_LAZY_SINK_FORWARD_METHODS_H
