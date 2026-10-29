// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x6E21E0, inside the TAction.cpp range.
//
//   Address index: 0x6E21E0

#include "taction_class_methods.h"
#include "../_layout/cell_class.h"
#include "../_layout/gbl_0087f7e8.h"
#include "../_layout/building_class.h"

// GLOBAL: GAMEMD 0xA8EB44 / 0xA8EB50 -- BuildingClass::Array items and count.
extern BuildingClass** DAT_00A8EB44;
extern int DAT_00A8EB50;

// GLOBAL: GAMEMD 0x87F8E4 -- the map rectangle.
extern Rect_4i DAT_0087F8E4;


// FUNCTION: GAMEMD 0x006E21E0
// Set the map rectangle from the action, then rebuild the map around it: refresh
// every cell, recalculate the zones and tell every building to re-read the map.
bool TActionClass::FUN_006E21E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_0087F8E4 = unknown_34;
    DAT_0087F7E8.FUN_00655990();
    DAT_0087F7E8.FUN_00578350();
    CellClass* c;
    while ((c = DAT_0087F7E8.FUN_00578290()) != 0)
        c->FUN_0047D2B0(-1);
    DAT_0087F7E8.FUN_0056C510();
    DAT_0087F7E8.FUN_00581F50();
    DAT_0087F7E8.FUN_00657CE0();
    for (int i = DAT_00A8EB50 - 1; i >= 0; i--)
        DAT_00A8EB44[i]->vf_296(1);
    return true;
}
