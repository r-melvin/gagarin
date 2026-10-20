// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x0041C8B0 (docs/decomp_spec/type_hierarchy_layout.md,
//   "AircraftTypeClass (start 0xDF8, size 0xE10) -- ctor 0x41C8B0"; parent ctor
//   TechnoTypeClass 0x710AF0). Anchored member-access sites ArrayIndex@0xDF8,
//   Trailer@0xE00, SpawnDelay@0xE04, cross-checked vs YRpp AircraftTypeClass.h.
//
// AircraftTypeClass - leaf blueprint for aircraft object types. Derives
// TechnoTypeClass (sizeof 0xDF8) at offset 0 and adds the aircraft-specific
// flags (carryall / rotor / landing behaviour) from 0xDF8 to 0xE0F.
//
// Trailer reads as undefined4 in the decomp (a 64-bit truncation site); modelled
// here as a real 4-byte opaque pointer so every offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_type_class.h"   // TechnoTypeClass (sizeof 0xDF8), AnimTypeClass

// ---------------------------------------------------------------------------
// AircraftTypeClass  (0xDF8..0xE0F, sizeof = 0xE10)
// ---------------------------------------------------------------------------
struct AircraftTypeClass : TechnoTypeClass
{
    int            ArrayIndex;     // +0xDF8
    bool           Carryall;       // +0xDFC
    unsigned char  _pad_DFD[3];    // +0xDFD
    AnimTypeClass* Trailer;        // +0xE00 (AnimTypeClass*, truncation site)
    int            SpawnDelay;     // +0xE04
    bool           Rotors;         // +0xE08
    bool           CustomRotor;    // +0xE09
    bool           Landable;       // +0xE0A
    bool           FlyBy;          // +0xE0B
    bool           FlyBack;        // +0xE0C
    bool           AirportBound;   // +0xE0D
    bool           Fighter;        // +0xE0E
    unsigned char  align_E0F[1];   // +0xE0F
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, ArrayIndex)   == 0xDF8);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Carryall)     == 0xDFC);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Trailer)      == 0xE00);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, SpawnDelay)   == 0xE04);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Rotors)       == 0xE08);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, CustomRotor)  == 0xE09);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Landable)     == 0xE0A);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, AirportBound) == 0xE0D);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Fighter)      == 0xE0E);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, align_E0F)    == 0xE0F);
GG_STATIC_ASSERT(sizeof(AircraftTypeClass)                 == 0xE10);

#endif  // GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H
