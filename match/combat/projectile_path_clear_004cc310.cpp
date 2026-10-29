// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x4CC310 in retail gamemd.exe v1.001: asks 0x4CC100 for the cell that blocks a
//   shot and tests it against the weapon's warhead.

#include "../_layout/cell_class.h"
#include "../_layout/warhead_type_class.h"
#include "weapon_type_class.h"
#include "bullet_type_class.h"

class HouseClass;
struct CoordStruct;

// Declaration: GAMEMD 0x4CC100 -- ECX from, EDX to, projectile and house on the stack, RET 8.
CellClass* __fastcall FUN_004CC100(const CoordStruct* from, const CoordStruct* to,
    BulletTypeClass* projectile, HouseClass* house);

// FUNCTION: GAMEMD 0x4CC310
// The cell blocking a shot of this weapon between two coordinates, or null when the blocker is
// a wall cell the weapon's warhead can destroy.
CellClass* __fastcall FUN_004CC310(const CoordStruct* from, const CoordStruct* to,
    WeaponTypeClass* weapon, HouseClass* house)
{
    BulletTypeClass* projectile = weapon->Projectile;
    CellClass* blocker = FUN_004CC100(from, to, projectile, house);
    if (blocker && blocker->ConnectsToOverlay(-1, -1) && weapon->Warhead->Wall) {
        return 0;
    }
    return blocker;
}
