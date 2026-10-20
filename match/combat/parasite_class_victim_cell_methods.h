// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, slots and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x62AB40: Owner at +0x24 and Victim at +0x28
//   on the parasite, the victim's slots +0x54 (IsInAir, bool) and +0x1BC
//   (GetCell), the owner's slots +0x84 (GetTechnoType) and +0x2C (WhatAmI,
//   1 = unit), the type's Naval byte at +0xCCE, the cell's land type at
//   +0xEC (2, 3, 6 accepted), flags at +0x140 (bit 0x100 = bridge) and
//   overlay index at +0x44 (the 0x4A..0x63 and 0xCD..0xE6 bands), and the
//   cell helpers 0x47C550 (one pushed argument) and 0x47C520. YRpp
//   (consult-only, no LICENSE) names CanExistOnVictimCell; the parasite
//   layout agrees with match/combat/parasite_class_infect_methods.h.
#ifndef GG_MATCH_COMBAT_PARASITE_CLASS_VICTIM_CELL_METHODS_H
#define GG_MATCH_COMBAT_PARASITE_CLASS_VICTIM_CELL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Type_0062AB40
{
    char _pad0000[0xCCE];     // +0x0000
    char Naval;               // +0x0CCE
};
GG_STATIC_ASSERT(offsetof(Type_0062AB40, Naval) == 0xCCE);

struct Obj_0062AB40;

struct Cell_0062AB40
{
    char _pad0000[0x44];      // +0x0000
    int  OverlayTypeIndex;    // +0x0044
    char _pad0048[0xEC - 0x48];   // +0x0048
    int  LandType;            // +0x00EC
    char _pad00F0[0x140 - 0xF0];  // +0x00F0
    int  Flags;               // +0x0140

    // FUNCTION: GAMEMD 0x47C550 (decl; reloc) — object of a kind on the cell.
    Obj_0062AB40* FUN_0047C550(int kind);
    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) — the building on the cell.
    Obj_0062AB40* FUN_0047C520();
};
GG_STATIC_ASSERT(offsetof(Cell_0062AB40, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_0062AB40, LandType) == 0xEC);
GG_STATIC_ASSERT(offsetof(Cell_0062AB40, Flags) == 0x140);

struct Vtbl_0062AB40;

struct Obj_0062AB40
{
    Vtbl_0062AB40* Vptr;      // +0x0000
};

typedef int  (Obj_0062AB40::*Fn2C_0062AB40)();
typedef bool (Obj_0062AB40::*Fn54_0062AB40)();
typedef Type_0062AB40* (Obj_0062AB40::*Fn84_0062AB40)();
typedef Cell_0062AB40* (Obj_0062AB40::*Fn1BC_0062AB40)();

struct Vtbl_0062AB40
{
    char _pad000[0x2C];             // +0x0000
    Fn2C_0062AB40 WhatAmI;          // +0x002C
    char _pad030[0x54 - 0x30];      // +0x0030
    Fn54_0062AB40 IsInAir;          // +0x0054
    char _pad058[0x84 - 0x58];      // +0x0058
    Fn84_0062AB40 GetTechnoType;    // +0x0084
    char _pad088[0x1BC - 0x88];     // +0x0088
    Fn1BC_0062AB40 GetCell;         // +0x01BC
};
GG_STATIC_ASSERT(offsetof(Vtbl_0062AB40, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_0062AB40, IsInAir) == 0x54);
GG_STATIC_ASSERT(offsetof(Vtbl_0062AB40, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_0062AB40, GetCell) == 0x1BC);

struct Parasite_0062AB40
{
    char _pad0000[0x24];      // +0x0000
    Obj_0062AB40* Owner;      // +0x0024
    Obj_0062AB40* Victim;     // +0x0028

    // FUNCTION: GAMEMD 0x62AB40 — ParasiteClass::CanExistOnVictimCell.
    bool CanExistOnVictimCell();
};
GG_STATIC_ASSERT(offsetof(Parasite_0062AB40, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(Parasite_0062AB40, Victim) == 0x28);

#endif  // GG_MATCH_COMBAT_PARASITE_CLASS_VICTIM_CELL_METHODS_H
