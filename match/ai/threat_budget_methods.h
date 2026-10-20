// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the vtable slot 0xAC and both globals are read numerically off the
//   user's retail gamemd.exe v1.001 through the local Ghidra CLI at 0x45ED50.
//   The deep-slot call uses the pointer-to-member-function idiom documented in
//   match/_rt/gg_vslot.h.
#ifndef GG_MATCH_AI_THREAT_BUDGET_METHODS_H
#define GG_MATCH_AI_THREAT_BUDGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Vtbl_0045ED50;

// The receiver, the pair entries and the trailing object are all the same
// class: the comparison at 0x45ED71 tests `this` against a dereferenced
// +0x3EC, and the trailing object at +0xEA0 is called through the same
// vtable slot as the two pair entries.
// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingTypeClass's own vtable is 0x7E4570.
//   0x45ED50 -> BuildingTypeClass slot 43 (byte-off 0xAC).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingTypeClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingTypeClass_0045ED50
{
    Vtbl_0045ED50* Vptr;       // +0x0000
    char _pad0004[0x3E8];      // +0x0004
    BuildingTypeClass_0045ED50** At_3EC;     // +0x03EC
    char _pad03F0[0xAB0];      // +0x03F0
    BuildingTypeClass_0045ED50* At_EA0;      // +0x0EA0

    // FUNCTION: GAMEMD 0x45ED50
    int FUN_0045ED50();
};
GG_STATIC_ASSERT(offsetof(BuildingTypeClass_0045ED50, At_3EC) == 0x3EC);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass_0045ED50, At_EA0) == 0xEA0);

typedef int (BuildingTypeClass_0045ED50::*FnAC_0045ED50)();

struct Vtbl_0045ED50
{
    char _pad000[0xAC];        // +0x0000
    FnAC_0045ED50 At_AC;       // +0x00AC
};
GG_STATIC_ASSERT(offsetof(Vtbl_0045ED50, At_AC) == 0xAC);

struct Host_0045ED50
{
    char _pad0000[0xB5C];      // +0x0000
    // Two entries are read: [0] is the pair the comparison runs against and
    // [1] supplies the second measurement.
    BuildingTypeClass_0045ED50** At_B5C;    // +0x0B5C
    char _pad0B60[0xC88];      // +0x0B60
    char At_17E8;              // +0x17E8
};
GG_STATIC_ASSERT(offsetof(Host_0045ED50, At_B5C) == 0xB5C);
GG_STATIC_ASSERT(offsetof(Host_0045ED50, At_17E8) == 0x17E8);

// GLOBAL: GAMEMD 0x8871E0 — the singleton the pair is read out of.
extern Host_0045ED50* DAT_008871E0;

// FUNCTION: GAMEMD 0x711EB0 — supplies the starting budget.
int FUN_00711EB0();

#endif  // GG_MATCH_AI_THREAT_BUDGET_METHODS_H
