// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x489180: the scenario flag byte `TEST byte ptr
//   [EAX],0x20` through `[0xA8B230]`, the warhead fields `[EDI+0x12C]`,
//   `[EDI+0x124]` and the double table `[EDI+EDX*8+0xA0]`, and the rules cap
//   `[ECX+0x16C8]` through `[0x8871E0]`.  Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_MAP_CLASS_TOTAL_DAMAGE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_TOTAL_DAMAGE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Minimal WarheadTypeClass view: the per-armor multiplier table and the
// spread/falloff pair.
struct WarheadType_00489180
{
    char   _pad000[0xA0];            // +0x0000
    double Verses[11];               // +0x00A0
    char   _pad0F8[0x124 - 0xF8];    // +0x00F8
    float  CellSpread;               // +0x0124
    char   _pad128[4];               // +0x0128
    float  PercentAtMax;             // +0x012C
};
GG_STATIC_ASSERT(offsetof(WarheadType_00489180, Verses) == 0xA0);
GG_STATIC_ASSERT(offsetof(WarheadType_00489180, CellSpread) == 0x124);
GG_STATIC_ASSERT(offsetof(WarheadType_00489180, PercentAtMax) == 0x12C);

// Minimal RulesClass view: the damage cap.
struct Rules_00489180
{
    char _pad000[0x16C8];            // +0x0000
    int  MaxDamage;                  // +0x16C8
};
GG_STATIC_ASSERT(offsetof(Rules_00489180, MaxDamage) == 0x16C8);

// Minimal ScenarioClass view: the first flag byte (bit 0x20 = Inert).
struct Scenario_00489180
{
    unsigned char SpecialFlags;      // +0x0000
};
GG_STATIC_ASSERT(offsetof(Scenario_00489180, SpecialFlags) == 0x0);

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00489180* ScenarioInstance;
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00489180* RulesInstance;

// Minimal MapClass view: GetTotalDamage is static (no instance members), so
// the struct only carries the method scope for the mangled name.
class MapClass
{
public:
    // FUNCTION: GAMEMD 0x489180
    static int GetTotalDamage(int damage, WarheadType_00489180* warhead,
                              int armor, int distance);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_TOTAL_DAMAGE_METHODS_H
