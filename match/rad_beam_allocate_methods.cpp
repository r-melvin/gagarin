// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x659110.

#include "rad_beam_allocate_methods.h"

// FUNCTION: GAMEMD 0x659110
//
// Create a beam of the given type, register it in the global beam list, and
// seed its +0x18 value from the type: 10 for type 1, 20 for anything else.
// The list's answer is discarded, and the +0x18 store is made whether or not
// the allocation succeeded (retail dereferences the result unconditionally).
RadBeam* RadBeam::Allocate(int type)
{
    RadBeam* beam = new RadBeam(type);

    DAT_00B04A60.AddItem(beam);

    int amplitude = (type != 1) ? 20 : 10;
    beam->At_18 = amplitude;

    return beam;
}
