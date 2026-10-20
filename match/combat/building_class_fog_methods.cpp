// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x457A10.

#include "building_class_fog_methods.h"

// FUNCTION: GAMEMD 0x457A10
//
// Is every foundation cell of this building fogged? Walks the type's
// foundation list (terminated by a {0x7FFF,0x7FFF} entry), offsets each entry
// by the building's own map coordinates and tests the fog bit on the cell;
// the first clear cell answers false.
//
// The two coordinate locals are the whole frame (SUB ESP,8): `cell` is first
// the out-parameter of the map-coords slot and then the argument handed to
// GetCellAt, `base` the dereferenced result that VC6 hoists into EDI/BX and
// whose slot the per-cell sum then reuses. Writing them as four locals costs
// a third slot.
//
// MATCHED (100.0%, 50/50). The residual block-order delta (retail lays the
// `XOR AL,AL` block directly after the loop's back-jump and the `MOV AL,1`
// block last, VC6 the reverse) was a flattened function boundary, not a
// compiler difference: retail's source has the foundation walk as its own
// routine, and this method is the wrapper around it. Written as an inline
// helper carrying the loop and both of its returns, with the wrapper spelled
// as an explicit `if (!AllFogged(...)) { return false; } return true;`, the
// failure block gains the second predecessor the earlier passes were hunting
// for and cl places both blocks where retail has them. 92.0% to 100%.
// Variants measured this pass: the same helper forwarded directly
// (`return AllFogged(...)`, 92.0%, the old score); the helper taking `base`
// as a const reference (92.0%); the cell test alone lifted into an inline
// `CellFogged` helper with the loop left in place (63.5%); and the sense
// inverted as an `AnyClear` helper negated by the wrapper (72.0%). Earlier
// passes had tried, all at 92.0% or worse: while-loop with in-loop
// `return false`; `for(;;)` with the terminator `break`ing to `return true`;
// `for(;;)` with the terminator returning true and the clear cell `break`ing
// to `return false`; gotos to labelled returns in retail's textual order;
// `continue`-shaped bodies; a `for` with `++fd` in the header; and a
// `bool fogged` flag set false on the clear cell and returned after the loop
// (90.0%).
//
// The foundation walk itself: offset each entry by the building's map
// coordinates and test the fog bit; the first clear cell answers false.
static inline bool AllFogged_00457A10(CellStruct const* fd, CellStruct base,
                                      CellStruct& cell)
{
    while (fd->X != 0x7FFF || fd->Y != 0x7FFF) {
        CellStruct sum;
        sum.X = fd->X + base.X;
        sum.Y = fd->Y + base.Y;
        cell = sum;
        if (!(MapInstance.GetCellAt(cell)->Flags & 0x400000))
            return false;
        ++fd;
    }
    return true;
}

bool BuildingClass_00457A10::CheckFog()
{
    CellStruct cell;
    CellStruct base = *(this->*this->Vtbl->GetMapCoords)(&cell);
    CellStruct const* fd = (this->Type->*this->Type->Vtbl->GetFoundationData)(false);

    if (!AllFogged_00457A10(fd, base, cell)) {
        return false;
    }
    return true;
}
