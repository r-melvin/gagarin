// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellClass accessors, ordered ascending by retail address.
#include "cell_class_methods.h"

// FUNCTION: GAMEMD 0x484FF0  CellClass::GetUIName (__thiscall)
// Same overlay->tiberium lookup as GetContainedTiberiumIndex below, then the
// tiberium type's UI name; a cell with no tiberium overlay yields a null name.
const wchar_t* CellClass::GetUIName() const
{
    int idxTiberium = OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
    if (idxTiberium != -1)
        return TiberiumArrayItems[idxTiberium]->UIName;

    return 0;
}

// FUNCTION: GAMEMD 0x485010  CellClass::GetContainedTiberiumIndex (__thiscall)
//   mov ecx,[ecx+0x44]; jmp 0x5fdd20  — forward OverlayTypeIndex to the lookup.
int CellClass::GetContainedTiberiumIndex() const
{
    return OverlayTypeIndexToTiberium(this->OverlayTypeIndex);
}

// FUNCTION: GAMEMD 0x485240  CellClass::SetMapCoords (__thiscall)
//   mov eax,[esp+4]; mov edx,[eax]; mov [ecx+0x24],edx; ret 4
void CellClass::SetMapCoords(CellStruct const* coords)
{
    this->MapCoords = *coords;
}

// FUNCTION: GAMEMD 0x487CB0  CellClass::GetRadLevel (__thiscall)
// The cell's radiation, clamped to the rules ceiling and truncated to an int.
// Retail tail-jumps into the CRT double-to-long helper at 0x7C5F00 rather than
// calling it, which is what a cast in return position produces.
//
// The compare is `FLD RadLevel; FCOMP` against the ceiling already on the
// stack, testing C0 alone (`TEST AH,1`). That shape comes from binding
// RadLevel to a double local that is used *only* in the comparison, with the
// ternary's result arm re-reading the member (retail's second `FLD [ECX+0xF0]`
// at 0x487CCC). Comparing the member directly folds it into `FCOM qword ptr
// [ECX+0xF0]` with `TEST AH,0x41` (20.0%); using the local in the result arm
// too spills it to a frame retail does not have (0.0%).
int CellClass::GetRadLevel()
{
    double ceiling = RulesGlobalPtr->RadLevelMax;
    double rad = RadLevel;

    return (int)(rad < ceiling ? RadLevel : ceiling);
}

// FUNCTION: GAMEMD 0x487CE0  CellClass::RadLevel_Increase (__thiscall)
//   fld [esp+4]; fadd [ecx+0xf0]; fstp [ecx+0xf0]; ret 8
void CellClass::RadLevel_Increase(double amount)
{
    this->RadLevel += amount;
}
