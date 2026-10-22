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
#include "../_layout/abstract_type_class.h"

// ---------------------------------------------------------------------------
// SuperWeaponTypeClass. Members appended after the 0x98-byte AbstractTypeClass
// spine, in confirmed retail order (YRpp cross-check):
//   ArrayIndex @0x98, WeaponType @0x9C, RechargeVoice @0xA0, ChargingVoice
//   @0xA4, ImpatientVoice @0xA8, SuspendVoice @0xAC, RechargeTime @0xB0,
//   Type @0xB4, SidebarImage @0xB8, Action @0xBC.
// Only Action @0xBC is touched by FindFirstOfAction:
//   `CMP dword ptr [EBX+0xBC], ECX` — Action compared to the ECX argument.
// ---------------------------------------------------------------------------
struct SuperWeaponTypeClass : AbstractTypeClass
{
    // STATIC: GAMEMD 0x6CEEB0  (__fastcall)
    static SuperWeaponTypeClass* __fastcall FindFirstOfAction(int action);

    char _pad_98[0xBC - 0x98];   // +0x98  ArrayIndex..SidebarImage (P2)
    int  Action;                 // +0xBC
    // remaining Rules fields (P2)
};

GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, Action) == 0xBC);

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
