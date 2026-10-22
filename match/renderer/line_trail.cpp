// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x556B50,
//   0x556DF0). Every offset/global reconfirmed numerically below; names
//   cross-checked against YRpp (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x556B50   LineTrail::SetDecrement  (__thiscall)
//   FUNCTION: GAMEMD 0x556DF0   LineTrail::DeleteAll     (__stdcall, static)
//   GLOBAL:   GAMEMD 0xA8EB78   <flag: halve-decrement>  (int)
//   GLOBAL:   GAMEMD 0xABCB78   LineTrail::Array         (DynamicVectorClass<LineTrail*>)
//   LIBRARY:  GAMEMD 0x7C8B3D   GameDelete (free/operator delete; excluded)

#include "line_trail.h"

// GLOBAL: GAMEMD 0xA8EB78 — when zero, the requested decrement is doubled
// (`mov eax,[0xA8EB78]; test eax,eax; jnz ...; shl eax,1`). Modelled as int.
extern int dword_A8EB78;

// GLOBAL: GAMEMD 0xABCB78 — the engine's global list of live LineTrails
// (YRpp: LineTrail::Array). vptr @0xABCB78, Items @0xABCB7C, Capacity @0xABCB80,
// IsAllocated @0xABCB85, Count @0xABCB88 — all reconfirmed from the DeleteAll
// absolute loads.
extern LineTrailVector LineTrail_Array;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x556B50  (__thiscall)
// Set the per-frame fade decrement; when the global flag @0xA8EB78 is clear the
// value is doubled before being stored at +0x08.
// ---------------------------------------------------------------------------
void LineTrail::SetDecrement(int val)
{
    if (dword_A8EB78 == 0)
        val <<= 1;
    this->Decrement = val;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x556DF0  (__stdcall, static)
// Destroy every live LineTrail: detach each from its owner (clearing the owner
// back-link @+0xA8 and the trail's Owner @+0x04), remove it from the global
// Array, and free it; then clear the Array (free its backing block when owned).
// ---------------------------------------------------------------------------
void __stdcall LineTrail::DeleteAll()
{
    for (int i = 0; i < LineTrail_Array.Count; ++i)
    {
        LineTrail* trail = LineTrail_Array.Items[i];
        if (trail)
        {
            if (trail->Owner)
            {
                trail->Owner->AttachedTrail = 0;
                trail->Owner = 0;
            }
            LineTrail* removed = trail;
            LineTrail_Array.Remove(removed);
            GameDelete(trail);
        }
    }

    LineTrail_Array.Count = 0;
    if (LineTrail_Array.Items != 0 && LineTrail_Array.IsAllocated)
    {
        GameDelete(LineTrail_Array.Items);
        LineTrail_Array.Items = 0;
    }
    LineTrail_Array.IsAllocated = 0;
    LineTrail_Array.Capacity = 0;
}
