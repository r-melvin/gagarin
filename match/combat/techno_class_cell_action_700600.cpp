// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x700600 in retail gamemd.exe v1.001 (Techno.CPP range), vtable slot 28:
//   which cursor action this object offers over a map cell (attack, enter, harvest-style
//   action, move), from the modifier keys held, ownership, the weapon it would pick and the
//   cell's overlay, fogged objects and veinhole monster.
//
// Address index:
//   0x700600  TechnoClass::vf_28

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/foot_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/veinhole_monster_class.h"
#include "../_layout/warhead_type_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include "../platform/input_manager_class_methods.h"
#include "../core/scenario_class_methods.h"
#include "weapon_type_class.h"

// GLOBAL: GAMEMD 0xA8B230 -- the current scenario.
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0xA8EBF8 .. 0xA8EC0C -- the modifier key codes tested below.
extern int DAT_00A8EBF8;
extern int DAT_00A8EBFC;
extern int DAT_00A8EC00;
extern int DAT_00A8EC04;
extern int DAT_00A8EC08;
extern int DAT_00A8EC0C;

// The overlay type record, as far as this routine reads it.
struct OverlayView_00700600
{
    char unknown_000[0x9C];
    int  unknown_9C;            // +0x9C
    char unknown_A0[0x231 - 0xA0];
    bool unknown_231;           // +0x231
    char unknown_232[0x2A8 - 0x232];
    bool unknown_2A8;           // +0x2A8
};
GG_STATIC_ASSERT(offsetof(OverlayView_00700600, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(OverlayView_00700600, unknown_231) == 0x231);
GG_STATIC_ASSERT(offsetof(OverlayView_00700600, unknown_2A8) == 0x2A8);
// GLOBAL: GAMEMD 0xA83D84 -- overlay type records by index
extern OverlayView_00700600** DAT_00A83D84;
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items
extern HouseClass** DAT_00A8022C;

// A fogged object, as far as this routine reads it.
struct FogView_00700600
{
    char unknown_000[0x24];
    int  unknown_24;            // +0x24
    HouseClass* unknown_28;     // +0x28
    char unknown_2C[4];
    int  unknown_30;            // +0x30
    char unknown_34[0x74 - 0x34];
    bool unknown_74;            // +0x74
    // FUNCTION: GAMEMD 0x4D28C0 (decl; reloc)
    OverlayView_00700600* FUN_004D28C0();
};
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_74) == 0x74);

// The cell, as far as the cursor routine reads it beyond CellClass.
struct CellView_00700600
{
    // FUNCTION: GAMEMD 0x486900 (decl; reloc)
    bool FUN_00486900();
};

// The overlay type record at an index.
static inline OverlayView_00700600* OverlayAt(int index)
{
    return DAT_00A83D84[index];
}

// Whether an object is a building (null-safe).
static inline bool IsBuilding(AbstractClass* object)
{
    return object && object->vf_11() == 6;
}

// Whether a key is held, via the shared input manager.
static inline bool KeyDown(int key)
{
    return DAT_0087F770->IsKeyPressed(key);
}

// Whether the object can attack the centre of a cell with the given weapon.
static inline bool CanTargetCell(TechnoClass* object, CellStruct* cell, int weapon)
{
    CoordStruct coords;
    coords.Z = 0;
    coords.X = cell->X * 256 + 128;
    coords.Y = cell->Y * 256 + 128;
    return object->vf_89(coords, weapon);
}

// FUNCTION: GAMEMD 0x700600
// The cursor action over a map cell.
int TechnoClass::vf_28(CellStruct* cell, char a2, char a3)
{
    if (Berzerk) {
        return 0;
    }
    if (DirectRockerLinkedUnit && !vf_33()->Pushy) {
        return 0;
    }
    CellClass* mapCell = DAT_0087F7E8.FUN_005657A0(cell);
    OverlayView_00700600* overlay = 0;
    bool x = !a3 && (KeyDown(DAT_00A8EC00) || KeyDown(DAT_00A8EC04));
    bool y = !a3 && (KeyDown(DAT_00A8EC08) || KeyDown(DAT_00A8EC0C));
    bool z = !a3 && (KeyDown(DAT_00A8EBF8) || KeyDown(DAT_00A8EBFC));
    if (y && x) {
        y = false;
        x = false;
    }
    int overlayIndex = -1;
    bool flag = false;
    if (vf_117() || vf_118()) {
        return 0;
    }
    if ((DAT_00A8B230->unknown_0000 & 0x1000) && a2 && mapCell->FoggedObjects) {
        for (int i = 0; i < mapCell->FoggedObjects->Count; i++) {
            FogView_00700600* fog = (FogView_00700600*)mapCell->FoggedObjects->Items[i];
            if (fog->unknown_74) {
                if (fog->unknown_30 == 0x14) {
                    overlayIndex = fog->unknown_24;
                } else if (fog->unknown_30 == 6) {
                    if (!fog->unknown_28 || !DAT_00A83D4C->IsAlliedWith(fog->unknown_28)) {
                        if (!fog->FUN_004D28C0() || fog->FUN_004D28C0()->unknown_231) {
                            flag = true;
                        }
                    }
                }
            }
        }
    }
    if (overlayIndex != -1) {
        overlay = DAT_00A83D84[overlayIndex];
    } else if (mapCell->OverlayTypeIndex != -1) {
        overlay = DAT_00A83D84[mapCell->OverlayTypeIndex];
    }
    bool canAttack = vf_204();
    if (Owner->IsControlledByCurrentPlayer() && ((x && z) || unknown_bool_43A) && vf_40()
        && (vf_39() || canAttack)) {
        if (!DAT_00A83D4C->GetPlanningWaypointAt(cell) && !unknown_bool_43A) {
            return 0x1a;
        }
        return 0x33;
    }
    WeaponStruct* primary;
    if (Owner->IsControlledByCurrentPlayer() && (primary = GetPrimaryWeapon()) != 0 && primary->WeaponType) {
        int weapon = vf_185(DAT_0087F7E8.FUN_005657A0(cell));
        bool unfriendly = ((CellView_00700600*)DAT_0087F7E8.FUN_005657A0(cell))->FUN_00486900();
        if (unfriendly) {
            WeaponTypeClass* fireWeapon = GetPrimaryWeapon()->WeaponType;
            if (fireWeapon->Warhead->Fire) {
                unfriendly = false;
            }
        }
        if (x || (overlay && overlay->unknown_231) || unfriendly || flag) {
            WarheadTypeClass* warhead = GetPrimaryWeapon()->WeaponType->Warhead;
            bool notAllied;
            if (mapCell->WallOwnerIndex != -1) {
                notAllied = !DAT_00A8022C[mapCell->WallOwnerIndex]->IsAlliedWith(Owner);
            } else {
                notAllied = false;
            }
            VeinholeMonsterClass* monster = VeinholeMonsterClass::GetVeinholeMonsterFrom(cell);
            bool alive = monster && !monster->IsDead && monster->Health > 0;
            if (x || !overlay || alive
                || (notAllied && overlay->unknown_2A8
                    && (warhead->Wall || (warhead->Wood && overlay->unknown_9C == 6)))) {
                if (vf_40() || CanTargetCell(this, cell, weapon)) {
                    return 5;
                }
            }
        }
        if (vf_230(mapCell)) {
            if (vf_40() || CanTargetCell(this, cell, weapon)) {
                return 5;
            }
        }
    }
    if (Owner->IsControlledByCurrentPlayer() && (vf_40() || vf_161())) {
        if (DAT_0087F7E8.FUN_00578460(cell, 1)) {
            if (y) {
                return 1;
            }
            if (vf_161() && z) {
                return 1;
            }
            if (vf_40()) {
                if (!a2) {
                    if (vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, true) > 1) {
                        if (IsBuilding(this) && vf_33()->UndeploysInto
                            && vf_33()->UndeploysInto->ResourceGatherer) {
                            return 1;
                        }
                        if (vf_33()->bools_D20[12]
                            && vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, false) <= 1) {
                            return 1;
                        }
                        return 2;
                    }
                }
                return 1;
            }
        }
        return 2;
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EBF8
int DAT_00A8EBF8;
// GLOBAL: GAMEMD 0xA8EBFC
int DAT_00A8EBFC;
// GLOBAL: GAMEMD 0xA8EC00
int DAT_00A8EC00;
// GLOBAL: GAMEMD 0xA8EC04
int DAT_00A8EC04;
// GLOBAL: GAMEMD 0xA8EC08
int DAT_00A8EC08;
// GLOBAL: GAMEMD 0xA8EC0C
int DAT_00A8EC0C;
// END defined globals
