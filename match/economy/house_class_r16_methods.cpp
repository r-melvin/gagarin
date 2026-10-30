// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// HouseClass members, ordered ascending by retail address.
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/unit_type_class.h"

// FUNCTION: GAMEMD 0x5117D0 (decl; reloc) -- index of a house type by name.
int __fastcall FUN_005117D0(const char* name);


// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x4AE9B0
// Maps a planning-mode action id to the id used when the current player has a
// planning waypoint at `cell`: 1,2 -> 0x2D; 3,9,0xB -> 0x32; 5,6 -> 0x31;
// anything else (or no waypoint there) is returned unchanged.
int __stdcall FUN_004AE9B0(int action, const CellStruct* cell)
{
    if (CurrentPlayer->GetPlanningWaypointAt(cell) != 0) {
        switch (action) {
        case 1:
        case 2:
            return 0x2D;
        case 5:
        case 6:
            return 0x31;
        case 3:
        case 9:
        case 0xB:
            action = 0x32;
            break;
        }
    }
    return action;
}
