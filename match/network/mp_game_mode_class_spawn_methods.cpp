// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5D7030.

#include "mp_game_mode_class_spawn_methods.h"

// FUNCTION: GAMEMD 0x5D7030  MultiplayerGameMode::SpawnBaseUnits
//
// With bases switched off there is nothing to do. Otherwise pick the house's
// base unit type, build one, and try to place it at the house's base
// coordinate; failing that, scatter it near the base cell. A unit that could
// be placed neither way is deleted again.
bool MultiplayerGameMode_005D7030::SpawnBaseUnits(House_005D7030* house, unsigned long unused)
{
    if (DAT_00A8B258 == 0)
        return true;

    UnitType_005D7030* type = house->FUN_00505310(&DAT_008871E0->At_B20);
    if (type == 0)
        return false;

    Unit_005D7030* unit = (Unit_005D7030*)operator new(0x8E8);
    if (unit == 0)
        return false;
    unit = unit->Construct(type, house);
    if (unit == 0)
        return false;

    Coord_005D7030 coords;
    if ((unit->*unit->Vptr->At_D8)(house->FUN_0050DF30(&coords), 0))
        return true;

    Cell_005D7030 cell;
    if (FUN_00688ED0(unit, house->FUN_0050DEF0(&cell), 1))
        return true;

    (unit->*unit->Vptr->At_20)(1);
    return false;
}
