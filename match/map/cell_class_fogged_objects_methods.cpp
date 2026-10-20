// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x486C50.

#include "cell_class_fogged_objects_methods.h"

// The cell a coordinate falls in: the inlined signed divide by 256 of X and Y.
static inline Cell_00486C50 CoordToCell_00486C50(Coord_00486C50 coord)
{
    Cell_00486C50 cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// The cell `offset` steps away from `cell` (the occupy-list entry's delta).
static inline Cell_00486C50 OffsetCell_00486C50(Cell_00486C50 cell, const short* offset)
{
    Cell_00486C50 result;
    result.X = (short)(cell.X + offset[0]);
    result.Y = (short)(cell.Y + offset[1]);
    return result;
}

// FUNCTION: GAMEMD 0x486C50  CellClass::ClearFoggedObjects (__thiscall)
//
// Drop the cell's fog snapshot. Every fogged record is walked back to front;
// each one's occupy list is stepped until the 0x7FFF/0x7FFF sentinel, and the
// record is unregistered from every other cell it covered (the inlined
// DynamicVectorClass::RemoveItem slide-down) before the record itself is
// deleted. Finally the vector is cleared, deleted and the member zeroed.
void CellFog_00486C50::ClearFoggedObjects()
{
    if (FoggedObjects != 0)
    {
        for (int i = FoggedObjects->Count - 1; i >= 0; i--)
        {
            Obj_00486C50* object = FoggedObjects->Items[i];

            if (FUN_004D2790(object) != 0)
            {
                for (short* p = FUN_004D2790(object);
                     p[0] != 0x7FFF || p[1] != 0x7FFF;
                     p += 2)
                {
                    Cell_00486C50 cell = CoordToCell_00486C50(object->Location);
                    CellFog_00486C50* other =
                        DAT_0087F7E8.GetCellAt(OffsetCell_00486C50(cell, p));
                    if (other != this)
                    {
                        Vec_00486C50* v = other->FoggedObjects;
                        if (v != 0)
                        {
                            int index = (v->*v->Vptr->IndexOf)(object);
                            if (index != -1 && index < v->Count)
                            {
                                v->Count = v->Count - 1;
                                for (int j = index; j < v->Count; ++j)
                                    v->Items[j] = v->Items[j + 1];
                            }
                        }
                    }
                }
            }

            if (object != 0)
                (object->*object->Vptr->At_20)(1);
        }

        (FoggedObjects->*FoggedObjects->Vptr->Clear)();

        Vec_00486C50* v = FoggedObjects;
        if (v != 0)
            (v->*v->Vptr->At_00)(1);

        FoggedObjects = 0;
    }
}
