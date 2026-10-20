// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and the vtable slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x44E7B0: `[ESI+0x520]`
//   (Type), `[EAX+0xEE0]` / `[EAX+0xEE8]` off it (PowerBonus /
//   ExtraPowerBonus), the two type flag bytes `[EAX+0x16AE]` / `[EAX+0x16AF]`,
//   `[ESI+0x668]` (HasExtraPowerBonus), `[ESI+0x114]` (Passengers count),
//   `[ESI+0x702]` (UpgradeLevel), `LEA ECX,[ESI+0x5EC]` with a 3-count
//   (Upgrades[3]), `[ESI+0x660]` (HasPower), and the virtual `CALL
//   [EDX+0x1D4]` (ObjectClass::IsBeingWarpedOut per
//   docs/decomp_spec/vtable_map_techno.md). Names for the method, the
//   members and the health-ratio callee 0x5F5C60 (ObjectClass::
//   GetHealthPercentage, between AttachTrigger 0x5F5B50 and
//   SetHealthPercentage 0x5F5C80 in match/core/object_class_methods.h) are
//   YRpp's (consult-only); every offset is reconfirmed here. The two type
//   flag bytes keep placeholder names: YRpp's adjacent UnitAbsorb /
//   InfantryAbsorb pair is the likely identity but their offsets were not
//   re-derived.
//
// BuildingClass::GetPowerOutput -- the structure's power production.
// Sister of GetPowerDrain (0x44E880, match/economy/building_class_power_methods)
// but written in C++ rather than a naked body.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// BuildingTypeClass -- only the members this method reads.
struct BuildingType_0044E7B0
{
    char _pad0000[0xEE0];              // +0x0000
    int  PowerBonus;                   // +0x0EE0
    int  PowerDrain;                   // +0x0EE4
    int  ExtraPowerBonus;              // +0x0EE8
    char _padEEC[0x16AE - 0xEEC];      // +0x0EEC
    char At_16AE;                      // +0x16AE  (YRpp: UnitAbsorb?)
    char At_16AF;                      // +0x16AF  (YRpp: InfantryAbsorb?)
};
GG_STATIC_ASSERT(offsetof(BuildingType_0044E7B0, PowerBonus)      == 0xEE0);
GG_STATIC_ASSERT(offsetof(BuildingType_0044E7B0, ExtraPowerBonus) == 0xEE8);
GG_STATIC_ASSERT(offsetof(BuildingType_0044E7B0, At_16AE)         == 0x16AE);
GG_STATIC_ASSERT(offsetof(BuildingType_0044E7B0, At_16AF)         == 0x16AF);

// Declaration order matters -- see match/_rt/gg_vslot.h.
struct Vtbl_0044E7B0;

struct Building_0044E7B0
{
    Vtbl_0044E7B0*          Vptr;                        // +0x0000
    char                    _pad0004[0x114 - 0x004];     // +0x0004
    int                     NumPassengers;               // +0x0114  Passengers.NumPassengers
    char                    _pad0118[0x520 - 0x118];     // +0x0118
    BuildingType_0044E7B0*  Type;                        // +0x0520
    char                    _pad0524[0x5EC - 0x524];     // +0x0524
    BuildingType_0044E7B0*  Upgrades[3];                 // +0x05EC
    char                    _pad05F8[0x660 - 0x5F8];     // +0x05F8
    char                    HasPower;                    // +0x0660
    char                    _pad0661[0x668 - 0x661];     // +0x0661
    char                    HasExtraPowerBonus;          // +0x0668
    char                    _pad0669[0x702 - 0x669];     // +0x0669
    char                    UpgradeLevel;                // +0x0702

    // FUNCTION: GAMEMD 0x5F5C60 (decl; reloc) -- ObjectClass::GetHealthPercentage.
    double GetHealthPercentage() const;

    // FUNCTION: GAMEMD 0x44E7B0
    int GetPowerOutput() const;
};
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, NumPassengers)      == 0x114);
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, Type)               == 0x520);
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, Upgrades)           == 0x5EC);
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, HasPower)           == 0x660);
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, HasExtraPowerBonus) == 0x668);
GG_STATIC_ASSERT(offsetof(Building_0044E7B0, UpgradeLevel)       == 0x702);

typedef bool (Building_0044E7B0::*Fn1D4_0044E7B0)() const;

struct Vtbl_0044E7B0
{
    char           _pad000[0x1D4];   // +0x0000
    Fn1D4_0044E7B0 IsBeingWarpedOut; // +0x01D4
};
GG_STATIC_ASSERT(offsetof(Vtbl_0044E7B0, IsBeingWarpedOut) == 0x1D4);

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H
