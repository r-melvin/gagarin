// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellView_00481810 shroud / neighbour helpers, ordered ascending by retail address.
#include "cell_class_shroud_methods.h"

// The retail MapClass singleton lives at this fixed address; calling through it
// makes cl emit `mov ecx,0x87F7E8` exactly as retail does.
#define MapInstance (reinterpret_cast<MapClass*>(0x87F7E8))

// FUNCTION: GAMEMD 0x481810  CellView_00481810::GetNeighbourCell (__thiscall)
//   For facing < 8 returns the cell at MapCoords + AdjacentCell[facing&7];
//   otherwise returns this.
CellView_00481810* CellView_00481810::GetNeighbourCell(int facing) const
{
    if ((unsigned int)facing < 8u)
    {
        CellStruct mc = this->MapCoords;
        return MapInstance->GetCellAt(mc + AdjacentCell[facing & 7]);
    }
    return const_cast<CellView_00481810*>(this);
}

// FUNCTION: GAMEMD 0x487630  CellView_00481810::ReduceShroudCounter (__thiscall)
//   Decrements ShroudCounter (snapping a value of 1 to 0 first); once it hits
//   zero either flags the cell shrouded (AltFlags |= 0x18) or, when already
//   shrouded, clears Flags bit 0x20.
//
//   Screened for the inline-assembly signature first and it is absent: the
//   function has no prologue at all, every value lives in EAX/EDX off ECX, and
//   every instruction is one cl emits from a C expression. Retail was compiled
//   from C++.
//
//   The two flag blocks have to be placed by hand. Retail lays the reshroud
//   block as the fallthrough (`TEST AL,8; JZ +2` skips only the second test)
//   and parks the already-shrouded block after it; cl normalises every
//   conjunction to the mirror layout, both tests jumping to the far block with
//   the &&-then falling through. All of `&&`/`||`, the condition inverted,
//   nested ifs, early returns in either arm, `if (cond) goto`, an explicit
//   two-goto skeleton, the decrement written out rather than pre-decremented
//   and the flags word named in the second arm sit at 48.1% with an identical
//   multiset bar one branch polarity. Only the fully spelled-out skeleton below
//   -- each failing test jumping to the reshroud label and an unconditional
//   jump to the shrouded label after them -- makes cl reverse the second test
//   and emit retail's order.
void CellView_00481810::ReduceShroudCounter()
{
    if (ShroudCounter == 1) {
        ShroudCounter = 0;
    }

    int remaining = --ShroudCounter;
    unsigned alt = AltFlags;

    if ((alt & 8) == 0) goto reshroud;
    if ((alt & 0x10) == 0) goto reshroud;
    goto shrouded;

reshroud:
    if (remaining <= 0) AltFlags = alt | 0x18;
    return;

shrouded:
    if (remaining <= 0 && (Flags & 0x20) == 0x20) Flags &= ~0x20;
}

// FUNCTION: GAMEMD 0x4876F0  CellView_00481810::Unshroud (__thiscall)
// Force the cell visible: set the two "revealed" bits in AltFlags, and if the
// cell still carries shroud counters, mark the shroud-redraw bit in Flags too.
// Retail sets all three through the AL byte lane (`OR AL,0x18` / `OR AL,0x20`
// on the loaded dword), which is what VC6 emits for a small-constant OR.
void CellView_00481810::Unshroud()
{
    AltFlags |= 0x18;

    if (ShroudCounter > 0)
        Flags |= 0x20;
}

// FUNCTION: GAMEMD 0x487950  CellView_00481810::IsShrouded (__thiscall)
//   Builds the cell-centre world coord (MapCoords.*256+128, GetFloorHeight) and
//   asks the map whether that location is under shroud.
bool CellView_00481810::IsShrouded() const
{
    // MapCoords (a CellStruct) is materialised into the same stack slot that
    // later serves as the {128,128} sub-cell Point2D handed to GetFloorHeight —
    // retail reuses that slot, so model it with an explicit overlay union.
    union { CellStruct mc; Point2D pt; } u;
    u.mc = this->MapCoords;
    int x = u.mc.X * 256 + 128;
    int y = u.mc.Y * 256 + 128;
    u.pt.X = 128;
    u.pt.Y = 128;
    int z = this->GetFloorHeight(u.pt);

    CoordStruct crd;
    crd.X = x;
    crd.Y = y;
    crd.Z = z;
    return MapInstance->IsLocationShrouded(crd);
}

// FUNCTION: GAMEMD 0x4879B0  (__thiscall)
//   The same cell-centre coordinate as IsShrouded, handed to the map's other
//   location test (0x5865E0).
bool CellView_00481810::FUN_004879B0() const
{
    union { CellStruct mc; Point2D pt; } u;
    u.mc = this->MapCoords;
    int x = u.mc.X * 256 + 128;
    int y = u.mc.Y * 256 + 128;
    u.pt.X = 128;
    u.pt.Y = 128;
    int z = this->GetFloorHeight(u.pt);

    CoordStruct crd;
    crd.X = x;
    crd.Y = y;
    crd.Z = z;
    return MapInstance->FUN_005865E0(crd);
}
