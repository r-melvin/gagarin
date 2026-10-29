// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6CEEB0), cross-checked against
//   YRpp (every offset and
//   address reconfirmed numerically below).
//
// SuperWeaponTypeClass — a superweapon *type* (rules-driven template). Derives
// the shared AbstractTypeClass layout-spine (ID @0x24, sizeof 0x98). Only the
// single member the static scan touches (Action @0xBC) is named here; the rest
// of the class is P2.
#ifndef GG_MATCH_COMBAT_SUPER_WEAPON_TYPE_CLASS_METHODS_H
#define GG_MATCH_COMBAT_SUPER_WEAPON_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/super_weapon_type_class.h"

// VectorClass head for SuperWeaponTypeClass::Array (DynamicVectorClass of
// pointers). Array @0xA8E330  =>  &Items == 0xA8E334, &Count == 0xA8E340 (both
// confirmed by the absolute loads in FindFirstOfAction:
//   MOV ESI,[0x00A8E340]  (Count),  MOV EDI,[0x00A8E334]  (Items)).
struct SuperWeaponTypeVector
{
    void*                  vtable;        // +0x00
    SuperWeaponTypeClass** Items;         // +0x04
    int                    Capacity;      // +0x08
    int                    IsAllocated;   // +0x0C
    int                    Count;         // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeVector, Items) == 0x04);  // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeVector, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA8E330 — SuperWeaponTypeClass::Array.
extern SuperWeaponTypeVector SuperWeaponTypeClass_Array;

#endif  // GG_MATCH_COMBAT_SUPER_WEAPON_TYPE_CLASS_METHODS_H
