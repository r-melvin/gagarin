// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FBE40.

#include "house_class_flag_coords_methods.h"

// FUNCTION: GAMEMD 0x4FBE40  HouseClass::UpdateFlagCoords (__thiscall, ret 8)
//
// Takes this house's flag away from wherever `obj` says it is. A unit gives
// the flag up itself; anything else names a cell (its coordinates divided
// down, refused when off-map) whose flag is removed. Either way, if the
// flag came off and the object was our recorded carrier, the carrier is
// forgotten. With `clearCell` set the recorded flag cell is also released
// (its owner index reset) and set to the "no cell" sentinel unless it
// already is. Reports whether a flag actually came off.
//
// Phrasing that matters: the carrier test sits inside each branch (retail
// tests BL and the carrier per arm and cross-jumps only the store; a shared
// test after the if/else gives a JMP into it, 9.1%); the null object falls
// through to a trailing `return false` so its epilogue lands after the main
// one; and the flag cell goes through a pointer local so Y is read as
// `[ESI+2]` off the LEA (95.5% with member access).
bool House_004FBE40::UpdateFlagCoords(Obj_004FBE40* obj, bool clearCell)
{
    bool removed = false;
    if (obj != 0) {
        if ((obj->*obj->Vtbl->WhatAmI)() == 1) {
            removed = obj->FlagRemove();
            if (removed && this->OurFlagCarrier == obj) {
                this->OurFlagCarrier = 0;
            }
        } else {
            Coord_004FBE40 buf;
            Cell_004FBE40 cell = CoordToCell_004FBE40((obj->*obj->Vtbl->GetCoords)(&buf));
            if (DAT_0087F7E8.CoordinatesLegal(cell)) {
                removed = DAT_0087F7E8.GetCellAt(cell)->FUN_00483460();
                if (removed && this->OurFlagCarrier == obj) {
                    this->OurFlagCarrier = 0;
                }
            }
        }

        if (clearCell) {
            Cell_004FBE40* flagCell = &this->OurFlagCoords;
            if (flagCell->X != DAT_00A8EF98.X || flagCell->Y != DAT_00A8EF98.Y) {
                DAT_0087F7E8.GetCellAt(*flagCell)->At_44 = -1;
                *flagCell = DAT_00A8EF98;
            }
        }
        return removed;
    }
    return false;
}
