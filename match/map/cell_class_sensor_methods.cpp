// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against the user's retail gamemd.exe v1.001; bodies ascending
//   by retail address.
#include "cell_class_sensor_methods.h"

// FUNCTION: GAMEMD 0x487150
// Register one more sensor (a unit able to detect cloaked objects) belonging to
// house `idxHouse` over this cell.
void CellClass::IncreaseSensorsOfHouse(int idxHouse)
{
    ++this->SensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487160
// Drop one sensor belonging to house `idxHouse` from this cell.
void CellClass::DecreaseSensorsOfHouse(int idxHouse)
{
    --this->SensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487170
// Register one more disguise-piercing sensor for house `idxHouse` over this
// cell. Same counter shape as above against the second array.
void CellClass::IncreaseDisguiseSensorsOfHouse(int idxHouse)
{
    ++this->DisguiseSensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487180
// Drop one disguise-piercing sensor for house `idxHouse` from this cell.
void CellClass::DecreaseDisguiseSensorsOfHouse(int idxHouse)
{
    --this->DisguiseSensorsOfHouses[idxHouse];
}

// FUNCTION: GAMEMD 0x487DF0
// One-line land-type predicate: true when the cell's LandType is 5.
bool CellClass::IsLandType5() const
{
    if (this->LandType == 5) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x487E00
// Report whether the cell counts as covered for occupation-height purposes.
// While the occupier list is valid the cell is walked for an occupier whose
// WhatAmI() is 6; finding one with a covering height of exactly 1 clears the
// answer. Otherwise the answer is simply "the covering height is non-zero".
//
// The redundant null test retail performs on the occupier it has just
// dereferenced is reproduced verbatim -- it is the source's own belt-and-braces
// guard and dropping it loses the branch.
bool CellClass::FUN_00487E00() const
{
    if (CellOccupiersValid) {
        for (ObjectClass* obj = this->FirstObject; obj != 0;
             obj = (ObjectClass*)obj->NextObject) {
            if (((WhatAmIFunc)((void**)*(void**)obj)[11])(obj) == 6) {
                if (obj != 0 && this->OccupyHeightsCoveringMe == 1) {
                    return false;
                }
                break;
            }
        }
    }
    return this->OccupyHeightsCoveringMe != 0;
}

// FUNCTION: GAMEMD 0x487EA0
// Step `src` one square in direction `dir`, wrapping the direction into the
// eight-entry step table. The pair is built in a temporary and copied out as a
// single dword, which is the shape retail emits.
CellStruct* FUN_00487EA0(CellStruct* dest, CellStruct const* src,
                         int dir)
{
    CellStruct const* step = &AdjacentCellTable[dir & 7];
    CellStruct out;

    out.X = (short)(step->X + src->X);
    out.Y = (short)(step->Y + src->Y);
    *dest = out;
    return dest;
}
