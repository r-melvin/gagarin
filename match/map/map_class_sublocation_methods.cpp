// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4ACA10.

#include "map_class_sublocation_methods.h"

// FUNCTION: GAMEMD 0x4ACA10
//
// Pick the infantry sub-cell position nearest a coordinate. Looks up the cell
// under the coordinate on the map singleton (not on `this`, which is never
// read), decides whether the coordinate is on the cell's bridge (the cell
// carries one and Z is at or above four levels over the ground), and hands the
// search to the cell.
//
// Returned by value through the hidden 12-byte result slot; the callee's own
// result lands in a temporary and is copied out through the pointer the callee
// returns (`MOV EDX,EAX` then three dword pairs off EDX), which is what a bare
// `return callee(...)` of a by-value struct produces.
//
// The bridge test is passed as the argument expression itself: bound to a bool
// local first, VC6 spills it to a stack byte and reloads it (51.3%); inline it
// materialises the 0/1 in ECX (`MOV ECX,1 / XOR ECX,ECX`) as retail does.
// The copy-out tail is sensitive to the receiver: as a `static __stdcall`
// function with the same stack shape the two `MOV ECX,EAX` / `POP ESI` slots
// swap with the neighbouring loads (89.7%); as a __thiscall member they match.
// Naming the result (`CoordStruct r = ...; return r;`) copies through a second
// local (10.0%), and a pointer-returning callee dereferenced on return is the
// same 89.7% under __stdcall.
CoordStruct MapClass::PickInfantrySublocation(const CoordStruct& coords, bool ignoreContents)
{
    CellClass* cell = DAT_0087F7E8.GetCellAt(coords);

    return cell->FindInfantrySubposition(coords, ignoreContents,
        (cell->Flags & 0x100) != 0 && coords.Z >= (cell->Level + 4) * DAT_008A0740,
        false);
}
