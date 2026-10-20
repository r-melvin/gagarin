// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Case sets read off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x71F680: four /Gy jump tables (index bytes at 0x71F700,
//   0x71F744, 0x71F780 and 0x71F7C0, ranges 0..0x3B, 0..0x31, 3..0x3A and
//   8..0x3D) plus the two direct compares against 8 and 0x18. The name comes
//   from the YRpp method map (TEventClass::GetAttachType, static); the bit
//   values are the retail immediates.
#ifndef GG_MATCH_AI_TEVENT_CLASS_ATTACH_TYPE_METHODS_H
#define GG_MATCH_AI_TEVENT_CLASS_ATTACH_TYPE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Which kinds of object a trigger event of `kind` can be attached to, as a bit
// set: 1 = object, 2 = house, 4 = global/local variable, 8 = cell/map,
// 0x10 = logic/timer. A kind may belong to several sets.
//
// The owning class. No member of TEventClass is touched at this address, so no
// layout is recovered here: the struct exists so the routine is spelled as the
// static member it is rather than as a free function, and so the next TEvent
// address to be matched has a class to attach to.
struct TEventClass_0071F680
{
    // FUNCTION: GAMEMD 0x71F680  (static __fastcall — kind in ECX)
    static unsigned int __fastcall GetAttachType(int kind);
};

#endif  // GG_MATCH_AI_TEVENT_CLASS_ATTACH_TYPE_METHODS_H
