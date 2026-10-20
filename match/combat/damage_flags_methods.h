// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slots and offsets read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x445F00: the vtable slot is `[EAX+0x3F8]`,
//   called four times with a 0/1 selector, and the three stack parameters sit at
//   `[ESP+0xC]`, `[ESP+0x10]` and `[ESP+0x14]` behind two pushes (`RET 0xC`).
#ifndef GG_MATCH_COMBAT_DAMAGE_FLAGS_METHODS_H
#define GG_MATCH_COMBAT_DAMAGE_FLAGS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The slot returns something whose leading word is tested for zero before it is
// used, so only that word is modelled.
struct Slotted_00445F00
{
    int First;    // +0x0000
};

// FUNCTION: GAMEMD 0x772A90 — turn one entry into a flag mask.
unsigned int __fastcall FUN_00772A90(int entry);

// Declaration order per match/_rt/gg_vslot.h: vtable forward-declared, class
// complete, then the member-pointer typedefs, then the vtable.
struct Vtbl_00445F00;

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x445F00 -> BuildingClass slot 241 (byte-off 0x3C4).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00445F00
{
    Vtbl_00445F00* Vtbl;    // +0x0000

    // FUNCTION: GAMEMD 0x6F8DF0 — apply the assembled flags.
    void FUN_006F8DF0(unsigned int flags, int b, int c);

    // FUNCTION: GAMEMD 0x445F00
    void FUN_00445F00(unsigned int incoming, int b, int c);
};

typedef Slotted_00445F00* (BuildingClass_00445F00::*Fn3F8_00445F00)(int which);

struct Vtbl_00445F00
{
    char _pad000[0x3F8];             // +0x0000
    Fn3F8_00445F00 At_3F8;           // +0x03F8
};
GG_STATIC_ASSERT(offsetof(Vtbl_00445F00, At_3F8) == 0x3F8);

#endif  // GG_MATCH_COMBAT_DAMAGE_FLAGS_METHODS_H
