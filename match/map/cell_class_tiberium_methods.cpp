// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellClass tiberium / shroud accessors, ordered ascending by retail address.
#include "cell_class_tiberium_methods.h"

// FUNCTION: GAMEMD 0x485020  CellClass::GetContainedTiberiumValue (__thiscall)
//   ecx=[esi+0x44]; call 0x5fdd20; if eax==-1 return 0;
//   edx=TiberiumArrayItems[eax]; return [edx+0xb8] * ([esi+0x11e] + 1).
int CellClass::GetContainedTiberiumValue() const
{
    int idx = OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
    if (idx == -1)
        return 0;
    return TiberiumArrayItems[idx]->Value * (this->OverlayData + 1);
}

// FUNCTION: GAMEMD 0x487690  CellClass::IncreaseShroudCounter (__thiscall)
//   normalise a -1 counter to 0, ++ it, clamp to GapsCoveringThisCell, and if it
//   crossed up through zero set Flags |= 0x20.
void CellClass::IncreaseShroudCounter()
{
    int old = this->ShroudCounter;
    if (old == -1)
        this->ShroudCounter = 0;
    this->ShroudCounter = this->ShroudCounter + 1;
    if (this->ShroudCounter > (int)this->GapsCoveringThisCell)
        this->ShroudCounter = this->GapsCoveringThisCell;
    if (old <= 0 && this->ShroudCounter > 0)
        this->Flags = (CellFlags)(this->Flags | 0x20);
}
