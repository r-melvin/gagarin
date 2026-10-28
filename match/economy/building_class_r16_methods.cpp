// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// BuildingClass members, ordered ascending by retail address.
// Address index: 0x44F7A0, 0x455B90, 0x4529E0.

#include "../_layout/building_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int ScenarioInit_00A8E7AC;

// The map object (MapClass::Instance at 0x87F7E8), as far as the call below.
struct MapObj_0044F7A0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc)
    void FUN_004F42F0(int a);
};
// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance (an object).
extern MapObj_0044F7A0 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x44F7A0
// Recompute the owner's radar-visibility mask as the OR of the display masks of
// its live buildings whose type has the radar flag, then tell the map.
void BuildingClass::FUN_0044F7A0()
{
    Owner->RadarVisibleTo = 0;
    int count = Owner->Buildings.Count;
    for (int i = 0; i < count; i++) {
        BuildingClass* building = Owner->Buildings.Items[i];
        if (building != 0 && !building->InLimbo && building->Type->bools_16A4[0]) {
            Owner->RadarVisibleTo |= building->DisplayProductionTo;
        }
    }
    DAT_0087F7E8.FUN_004F42F0(2);
}

// The map object as the 0x455B90 body uses it.
struct MapObj_00455B90
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* FUN_00565730(CoordStruct* coord);
};
extern MapObj_00455B90 Map_00455B90;

// FUNCTION: GAMEMD 0x455B90
// One bit per edge neighbour (directions 0, 2, 4, 6 -> bits 0..3) that holds a
// live, in-play building whose type has the flag at +0x16C0.
unsigned int BuildingClass::FUN_00455B90()
{
    CoordStruct here = Location;
    unsigned int mask = 0;
    CellClass* cell = Map_00455B90.FUN_00565730(&here);
    for (int dir = 0; dir < 8; dir += 2) {
        BuildingClass* neighbour = cell->FUN_00481810(dir)->GetBuilding();
        if (neighbour != 0 && neighbour->Type->bools_16A4[0x1C] && !neighbour->InLimbo && neighbour->IsAlive) {
            mask |= 1 << (dir >> 1);
        }
    }
    return mask;
}

// FUNCTION: GAMEMD 0x4529E0
// Once the scenario is running, for a live, owned building whose type has the
// flag at +0x16BE set, refresh sides 0, 2, 4 and 6 and then the end post.
void BuildingClass::FUN_004529E0()
{
    if (ScenarioInit_00A8E7AC == 0 && Type->bools_16A4[0x1A] && IsAlive && !InLimbo) {
        FUN_00452DC0(0);
        FUN_00452DC0(2);
        FUN_00452DC0(4);
        FUN_00452DC0(6);
        CreateEndPost(true);
    }
}
