// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x6CB7B0. IsPresent @0x6D and IsReady @0x6F match
//   the member run already committed in super_class_methods.h and are
//   reconfirmed here. The vector globals — vptr 0x00A83D50, Items 0x00A83D54,
//   Count 0x00A83D60 — are +0x00/+0x04/+0x10 of one object, which is YRpp's
//   SuperClass::ShowTimers at 0x00A83D50 (consult-only, no LICENSE).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"

struct SuperClass;

// GLOBAL: GAMEMD 0x00A83D50
// DynamicVectorClass<SuperClass*>: vptr +0x00, Items +0x04, Count +0x10.
extern DynamicVectorClass<SuperClass*> ShowTimers;

struct SuperClass
{
    char _pad00[0x6D];   // +0x0000
    bool IsPresent;      // +0x006D
    char _pad6E;         // +0x006E
    bool IsReady;        // +0x006F

    bool Lose();         // GAMEMD 0x6CB7B0
};
GG_STATIC_ASSERT(offsetof(SuperClass, IsPresent) == 0x6D);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady)   == 0x6F);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H
