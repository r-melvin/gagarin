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

class FactoryClass;   // pointer-only; full layout is P2

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
// HouseTypeClass (partial) — the country blueprint pointed to by HouseClass+0x34.
// 0x4F9610 reads only IncomeMult @0x148 (`FMUL float[EAX+0x148]`). Derives the
// AbstractTypeClass COM/type head (0x00..0x97); members up to 0x148 per YRpp
// (FixedString ParentCountry, the 7 doubles, the Armor/Cost/
// Speed/Buildtime float blocks) collapse to padding (full layout = P2).
// ---------------------------------------------------------------------------
struct HouseTypeClass
{
    char  _pad0[0x148];   // AbstractTypeClass head + multiplier blocks
    float IncomeMult;     // +0x148
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, IncomeMult) == 0x148);

// ---------------------------------------------------------------------------
// TiberiumClass (partial) — only Value @0xB8 is touched (`FILD dword[EDX+0xB8]`
// loads it as an int). Same member StorageClass::GetTotalValue uses.
// ---------------------------------------------------------------------------
struct TiberiumClass
{
    char _pad0[0xB8];   // AbstractTypeClass-derived head = P2
    int  Value;         // +0xB8
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);

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

// ---------------------------------------------------------------------------
// HouseClass (partial) — only the members the two methods touch are modelled;
// everything else is offset-pinned padding (full layout = P2). Offsets:
//   Type            @0x34   (HouseTypeClass*)   — `MOV EAX,[ESI+0x34]`
//   Balance         @0x30C  (int credits)       — `FIADD dword[ESI+0x30C]`
//   Primary_For*    @0x53AC.. (FactoryClass*)   — `MOV EAX,[ECX+0x53xx]`
//   StatAccrued54E8 @0x54E8 (int stat counter)  — `FIADD dword[ESI+0x54E8]`
// 0x53AC follows PowerOutput/PowerDrain (0x53A4/0x53A8) per the matched
// house_class_power layout; the nine Primary_ pointers are contiguous.
// ---------------------------------------------------------------------------
struct HouseClass
{
    char            _pad00[0x34];
    HouseTypeClass* Type;                  // +0x34
    char            _pad38[0x30C - 0x38];
    int             Balance;               // +0x30C
    char            _pad310[0x53AC - 0x310];
    FactoryClass*   Primary_ForAircraft;   // +0x53AC
    FactoryClass*   Primary_ForInfantry;   // +0x53B0
    FactoryClass*   Primary_ForVehicles;   // +0x53B4
    FactoryClass*   Primary_ForShips;      // +0x53B8
    FactoryClass*   Primary_ForBuildings;  // +0x53BC
    FactoryClass*   Primary_Unused1;       // +0x53C0
    FactoryClass*   Primary_Unused2;       // +0x53C4
    FactoryClass*   Primary_Unused3;       // +0x53C8
    FactoryClass*   Primary_ForDefenses;   // +0x53CC
    char            _pad53D0[0x54E8 - 0x53D0];
    int             StatAccrued54E8;       // +0x54E8

    // Ascending by retail address.
    float         GiveTiberium(float amount, int type);                            // GAMEMD 0x4F9610 __thiscall
    FactoryClass* GetPrimaryFactory(AbstractType absID, bool naval, BuildCat buildCat) const;  // GAMEMD 0x500510 __thiscall
};

GG_STATIC_ASSERT(offsetof(HouseClass, Type)                == 0x34);
GG_STATIC_ASSERT(offsetof(HouseClass, Balance)             == 0x30C);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForAircraft) == 0x53AC);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForInfantry) == 0x53B0);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForVehicles) == 0x53B4);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForShips)    == 0x53B8);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForBuildings)== 0x53BC);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForDefenses) == 0x53CC);
GG_STATIC_ASSERT(offsetof(HouseClass, StatAccrued54E8)     == 0x54E8);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_TIB_METHODS_H
