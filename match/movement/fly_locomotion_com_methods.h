// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   The class was identified from its own runtime type information: the
//   secondary vtable of this cluster starts at 0x7E89F4, its complete object
//   locator sits one dword below at 0x7E89F0 -> 0x800658, whose type
//   descriptor at +0xC is 0x8223E8, and the name eight bytes into that reads
//   ".?AVFlyLocomotionClass@@". The locator's base offset of 4 is what pins
//   the locomotor interface's vptr to +0x04 and the persist vptr to +0x00,
//   which the loader at 0x4CFCC0 re-seats with exactly those two constants
//   (0x7E8AC0 at +0, 0x7E89F4 at +4). YRpp names FlyLocomotionClass and the
//   ILocomotion slot order - name-only cross-check.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001:
//   +0x00 the persist vptr, +0x04 the locomotor vptr, +0x0C LinkedTo (read
//   through the interface as `MOV 0x8(%EAX),%ECX` in 0x4CFCF0 and 0x4CFDA0,
//   and through the object as `MOV 0xC(%ESI),%ECX` in 0x4CFC40), +0x38 the
//   halved FlightLevel in 0x4CFC40, +0x50 and +0x51 its two flag bytes, +0x53
//   the spin flag and +0x54 the spin value the touchdown path at 0x4CFD20
//   writes (as `0x4F(%ESI)` and `0x50(%ESI)` off the interface pointer, four
//   lower), and +0x58 the counter it clears.
//   LinkedTo's vtable slots: +0x84 returns the type object whose byte at
//   +0xD27 gates 0x4CFDA0, and +0x1C8 returns the signed value both 0x4CFC40
//   and 0x4CFCF0 test.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"

// The scenario's random generator; the touchdown spin is drawn from it.
struct RandomClass_004CFD20
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — Randomizer::RandomRanged.
    int RandomRanged(int minval, int maxval);
};

struct ScenarioClass_004CFD20
{
    char _pad000[0x218];                 // +0x0000
    RandomClass_004CFD20 RandomNumber;   // +0x0218
};
GG_STATIC_ASSERT(offsetof(ScenarioClass_004CFD20, RandomNumber) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — the scenario object.
extern ScenarioClass_004CFD20* Scenario_00A8B230;

// GLOBAL: GAMEMD 0x7E9A80 -- the native class identifier.
extern "C" const CLSID CLSID_FlyLocomotion;

#include "../_layout/fly_locomotion_class.h"

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H
