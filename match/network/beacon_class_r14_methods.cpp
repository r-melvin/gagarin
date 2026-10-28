// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x430210 (TU range of Beacon.CPP, string at 0x818AD8);
//   the default coordinate is the header-initialised global at 0x89C430.
//
// BeaconClass default constructor. Address index: 0x430210.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/header_init_shapes.h"
#include "beacon_class_methods.h"

extern HeaderCoordInit DAT_0089C430;  // GAMEMD 0x0089C430, the "no location" coordinate

// FUNCTION: GAMEMD 0x430210
// Start at the "no location" coordinate with both state bits clear and the label emptied.
BeaconClass::BeaconClass()
{
    Coord = DAT_0089C430;
    Bitfield &= 0xFC;
    for (int i = 0; i < 0x40; i++)
        ((int*)&_gap0D[1])[i] = 0;
}
