// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets + control flow derived from the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI (member-access disassembly @0x4F9610 and @0x500510),
//   cross-checked against YRpp
//   (every offset reconfirmed
//   below against the user's binary).
//
// HouseClass Tiberium/factory helpers:
//   HouseClass::GiveTiberium      — credit + stat accrual from refined Tiberium
//   HouseClass::GetPrimaryFactory — pick the primary FactoryClass for a kind
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_TIB_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_TIB_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"

// ---------------------------------------------------------------------------
// AbstractType — the engine's RTTI tag. Plain C++98
// enum (VC6 has no `enum class`); only the values the 0x500510 switch tests are
// load-bearing, but the full dense range is declared so the case labels read
// faithfully. Values reconfirmed from the jump/index tables at 0x500574.
// ---------------------------------------------------------------------------
enum AbstractType
{
    abs_None         = 0,
    abs_Unit         = 1,
    abs_Aircraft     = 2,
    abs_AircraftType = 3,
    abs_Building     = 6,
    abs_BuildingType = 7,
    abs_Infantry     = 15,
    abs_InfantryType = 16,
    abs_UnitType     = 40
};

// BuildCat — sidebar build category. Only Combat(==5),
// the value 0x50054C compares against, is load-bearing here.
enum BuildCat
{
    bc_DontCare       = 0,
    bc_Tech           = 1,
    bc_Resource       = 2,
    bc_Power          = 3,
    bc_Infrastructure = 4,
    bc_Combat         = 5
};

// ---------------------------------------------------------------------------
// TiberiumClass (partial) — only Value @0xB8 is touched (`FILD dword[EDX+0xB8]`
// loads it as an int). Same member StorageClass::GetTotalValue uses.
// ---------------------------------------------------------------------------
#include "../_layout/tiberium_class.h"

// VectorClass<TiberiumClass*> head: vtable @0, Items @4. The engine global
// TiberiumClass::Array sits at 0xB0F4E8, so `MOV ECX,[0xB0F4EC]` == &Array.Items.
struct DynamicVectorClass_TiberiumPtr
{
    void*           vtable;   // +0x00
    TiberiumClass** Items;    // +0x04
    int             Capacity; // +0x08
    int             IsAllocated;       // +0x0C
    int             Count;             // +0x10
    int             CapacityIncrement; // +0x14
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_TiberiumPtr, Items) == 0x04);
#endif

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_TIB_METHODS_H
