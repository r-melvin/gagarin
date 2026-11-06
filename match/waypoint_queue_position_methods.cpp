// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "waypoint_queue_position_methods.h"

// FUNCTION: GAMEMD 0x7180A0
//
// Where this source currently is: its own coordinate when it carries one,
// otherwise the coordinate of the owner it is attached to.
//
// Returns the coordinate by value: a __stdcall member whose hidden return
// pointer follows `this` on the stack and comes back in EAX.
Coord_007180A0 __stdcall Source_007180A0::FUN_007180A0()
{
    Coord_007180A0 result;
    if (Vtbl->HasOwnPosition(this)) {
        result.X = Position.X;
        result.Y = Position.Y;
        result.Z = Position.Z;
    } else {
        result = Owner->Position;
    }
    return result;
}
