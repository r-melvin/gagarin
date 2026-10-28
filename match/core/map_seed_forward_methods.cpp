// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x597D50 (pushes its argument and calls 0x559EB0 with this in ECX).
//
// MapSeedClass slot 3: forwards mission deletion to the LoadOptionsClass body.
// Address index: 0x597D50 DeleteMission.

#include "../_layout/map_seed_class.h"

// FUNCTION: GAMEMD 0x597D50
bool MapSeedClass::DeleteMission(char const* filename)
{
    return LoadOptionsClass::DeleteMission(filename);
}
