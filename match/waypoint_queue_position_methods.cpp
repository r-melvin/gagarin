// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "waypoint_queue_position_methods.h"

// FUNCTION: GAMEMD 0x7180A0
//
// Where this source currently is: its own coordinate when it carries one,
// otherwise the coordinate of the owner it is attached to.
//
// PARTIAL, 9.1%. The instruction stream is right in shape and wrong in
// register discipline. Retail saves EDI in the prologue, before it pushes the
// receiver for the virtual call, and holds the destination pointer there
// across the call; it then loads all three source words into three registers
// and stores them through EDI. cl treats the destination as the parameter it
// is and reloads it from the frame after the call, so no callee-saved
// register is needed and the loads and stores interleave.
//
// Ten spellings were measured against this address in two batches: the copy
// written whole in each arm (this one, 9.1%); staged through a local struct
// in each arm; three named component locals per arm; the source selected into
// a pointer before a single copy; staged local plus a re-bound destination;
// components named plus a re-bound destination; the destination bound to a
// local before the call, both as three component stores and as a whole-struct
// copy; the virtual's answer taken into a named bool first; and the owner
// staged behind its own pointer. Everything that binds the destination early
// sits at 9.1% and everything that stages the source sits at 6.1%.
//
// The lever needed is whatever makes cl hold a parameter in a callee-saved
// register across a call rather than reloading it, which none of the banked
// naming or boundary rules reaches.
void __stdcall FUN_007180A0(Source_007180A0* self, Coord_007180A0* out)
{
    if (self->Vtbl->HasOwnPosition(self)) {
        *out = self->Position;
    } else {
        *out = self->Owner->Position;
    }
}
