// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below; the
//   source and the light are both reached through the position slot (0x48).
//
// Ordered ascending by retail address.

#include "building_light_class.h"
#include "../core/rules_class.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt.
extern "C" double __cdecl FUN_004CAC40(double value);
// GLOBAL: GAMEMD 0x7E3A98 -- scale applied to the light's range.
extern const double DAT_007E3A98;

// The straight-line distance from `from` to `to`, expanded inline at both users.
static inline int DistanceBetween_00436DA0(const CoordStruct& to, const CoordStruct& from)
{
    int dx = to.X - from.X;
    int dy = to.Y - from.Y;
    int dz = to.Z - from.Z;
    double squared = (double)dy * dy + (double)dz * dz + (double)dx * dx;
    return (int)FUN_004CAC40(squared);
}

// FUNCTION: GAMEMD 0x436DA0
//
// The light's reach: its pulse step (see 0x436E80) scaled and added to the
// rules' base reach. The pulse step is expanded inline here.
//
// PARTIAL: 82.1% (64/78). Retail keeps the pulse step in its own stack slot
// (frame 0x28, cl 12.00 shares it for 0x24) and issues the first FILD ahead of
// the third coordinate difference. Variants tried: differences as locals, as
// inline expressions, and a double temporary for the first term.
int BuildingLightClass::FUN_00436DA0()
{
    int distance = DistanceBetween_00436DA0(vf_18(), source->vf_18());
    int minimum = RulesInstance->unknown_78C;
    int pulse;
    if (distance < minimum)
        pulse = 0;
    else
        pulse = (distance - minimum) / ((RulesInstance->unknown_788 - minimum) / 10);
    return (int)(pulse * DAT_007E3A98) + RulesInstance->unknown_7A8;
}

// FUNCTION: GAMEMD 0x436E80
//
// How far past the minimum the source is, in tenths of the rules' range band;
// 0 when it is inside the minimum.
//
// PARTIAL: 90.4% (66/73). The delta is the order of the first FILD against the
// third coordinate difference and the slot of the first difference; same
// variants as 0x436DA0.
int BuildingLightClass::FUN_00436E80()
{
    int distance = DistanceBetween_00436DA0(vf_18(), source->vf_18());
    int minimum = RulesInstance->unknown_78C;
    if (distance < minimum)
        return 0;
    return (distance - minimum) / ((RulesInstance->unknown_788 - minimum) / 10);
}
