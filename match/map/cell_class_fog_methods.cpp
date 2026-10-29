// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellClass fog helper, ordered ascending by retail address.
#include "cell_class_fog_methods.h"

// The retail MapClass singleton lives at this fixed address; calling through it
// makes cl emit `mov ecx,0x87F7E8` exactly as retail does.
#define MapInstance (reinterpret_cast<MapView_5657A0_2*>(0x87F7E8))

// FUNCTION: GAMEMD 0x486BF0  CellClass::CleanFog (__thiscall)
//   Walks a small diagonal stripe of cells starting at this cell's MapCoords:
//   i runs 1,3,5,...,13; each step the running coord steps (+1,+1). For every
//   cell whose Level falls within [i-2, i] the fog bit (0x400000) is cleared
//   from Flags and its fogged objects are dropped.
void CellClass::CleanFog()
{
    CellStruct coords = this->MapCoords;
    int i = 1;
    do
    {
        CellClass* cell = MapInstance->GetCellAt(coords);
        int level = cell->Level;
        if (level >= i - 2 && level <= i)
        {
            cell->Flags &= 0xFFBFFFFF;
            cell->ClearFoggedObjects();
        }
        ++coords.X;
        ++coords.Y;
        i += 2;
    } while (i < 15);
}
