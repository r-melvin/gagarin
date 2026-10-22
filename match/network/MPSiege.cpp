// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPSiege.cpp. The name is the source-file string at 0x82ff2c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5ca726 inside this object's
//   code range (0x5ca420-0x5cac1f). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The MPSiege.cpp block of retail .text (0x5CA420..0x5CAC1F; the unit's own
// assert path at 0x82FF2C names it): three of the unit's run-time
// initialisers and the MultiplayerSiege constructor, destructor and slot
// overrides, in retail address order. MultiplayerSiege is declared in
// multiplayer_game_mode.h.
//
// STRING: GAMEMD 0x82FEE8 "MP:NoAttackers"
// STRING: GAMEMD 0x82FEF8 "MP:OnlyOneBeseiged"
// STRING: GAMEMD 0x82FF0C "MP:IllegalTeam"
// STRING: GAMEMD 0x82FF1C "MP:NoDefender"
// STRING: GAMEMD 0x82FF48 "Assigning Starting Points for Attacking house %d (%s)\n"
// STRING: GAMEMD 0x82FF80 "Assigning Starting Points for Defending house %d (%s)\n"

#include <string.h>
#include "multiplayer_game_mode.h"
#include "transport/conn_types.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/building_class.h"
#include "../core/header_tuning_globals.h"
#include "../core/vector_class_operations.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xABFA20
extern double DAT_00ABFA20;
// GLOBAL: GAMEMD 0x7EE6E8
const double DAT_007EE6E8 = 60.0;

// ---- MultiplayerSiege ----------------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x82FF2C -- this unit's build path, handed to the label lookup.
extern const char DAT_0082FF2C[];

// GLOBAL: GAMEMD 0xA80228 -- the house registry (Items +0x04 = 0xA8022C, Count +0x10 = 0xA80238).
extern DynamicVectorClass<HouseClass*> DAT_00A80228;

// FUNCTION: GAMEMD 0x688380 (decl; reloc) -- the scenario's start cells, built
// into the caller's vector (hidden pointer in ECX, the flag in DL).
DynamicVectorClass<Cell> __fastcall FUN_00688380(bool unknown);

// GLOBAL: GAMEMD 0x8871E0 -- the rules object; 0x5CAB33 passes the address of
// its +0x8AC member (a type list) to 0x5051E0.
struct Rules_008871E0
{
    char _pad000[0x8AC];      // +0x000
    char unknown_8AC[0x18];   // +0x8AC
};
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_8AC) == 0x8AC);
extern Rules_008871E0* DAT_008871E0;

// FUNCTION: GAMEMD 0x688ED0 (decl; reloc) -- __fastcall: the building in ECX,
// the cell's address in EDX, one stacked dword; nonzero on success.
int __fastcall FUN_00688ED0(BuildingClass* building, const Cell& cell, int unknown);

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised
// text; __fastcall with the file and line on the stack, RET 8.
const wchar_t* __fastcall FUN_00734E60(const char* label, int flags, const char* file, int line);

// SYNTHETIC: GAMEMD 0x5CA450
// GLOBAL: GAMEMD 0xABFA70
double DAT_00ABFA70 = DAT_00ABFA20 / DAT_007EE6E8;

// SYNTHETIC: GAMEMD 0x5CA470
// GLOBAL: GAMEMD 0xABFA58
double DAT_00ABFA58 = 1.0 / DAT_00ABFA70;

// SYNTHETIC: GAMEMD 0x5CA5F0
// GLOBAL: GAMEMD 0xABFA60
TuningCoordInit DAT_00ABFA60(128, 128, 0);

// FUNCTION: GAMEMD 0x5CA630
MultiplayerSiege::MultiplayerSiege(const Obj_007B66D0& name, const Obj_007B66D0& description,
                                   const Obj_007B4620& unknown_3, const Obj_007B4620& unknown_4,
                                   bool unknown_5, int unknown_6)
    : MultiplayerGameMode(name, description, unknown_3, unknown_4, unknown_5, unknown_6)
{
}

// FUNCTION: GAMEMD 0x5CA670
MultiplayerSiege::~MultiplayerSiege()
{
}

// FUNCTION: GAMEMD 0x5CA680
//
// After the base check, the first player defends (team 1) and the second
// attacks (team 2). The loop runs once per further player, but retail stores
// through Items[1] every time (`MOV ESI,[ESI+0x4]` at 0x5CA6BD, a constant
// displacement), so the other players' fields are left as they were.
bool MultiplayerSiege::vf_4()
{
    if (!MultiplayerGameMode::vf_4()) {
        return false;
    }
    if (PlayerCount_00A8DA84 > 0) {
        Players_00A8DA78[0]->unknown_6B = 1;
        for (int i = 1; i < PlayerCount_00A8DA84; i++) {
            Players_00A8DA78[1]->unknown_6B = 2;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5CA6D0
//
// Validate the team assignment: exactly one defender, at least one attacker
// and no other team; the first failure's label text goes to `message`.
bool MultiplayerSiege::vf_5(Obj_007B66D0& message)
{
    if (!MultiplayerGameMode::vf_5(message)) {
        return false;
    }

    bool defender = false;
    int attackers = 0;
    for (int i = 0; i < PlayerCount_00A8DA84; i++) {
        switch (Players_00A8DA78[i]->unknown_6B) {
        case 0:
            break;
        case 1:
            if (defender) {
                message = FUN_00734E60("MP:OnlyOneBeseiged", 0, DAT_0082FF2C, 0x33);
                return false;
            }
            defender = true;
            break;
        case 2:
            attackers++;
            break;
        default:
            message = FUN_00734E60("MP:IllegalTeam", 0, DAT_0082FF2C, 0x3C);
            return false;
        }
    }

    if (!defender) {
        message = FUN_00734E60("MP:NoDefender", 0, DAT_0082FF2C, 0x41);
        return false;
    }
    if (attackers < 1) {
        message = FUN_00734E60("MP:NoAttackers", 0, DAT_0082FF2C, 0x46);
        return false;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA7D0
bool MultiplayerSiege::vf_6()
{
    return MultiplayerGameMode::vf_6();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA7E0
bool MultiplayerSiege::vf_15()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA7F0
bool MultiplayerSiege::vf_31()
{
    return MultiplayerGameMode::vf_31();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA800
//
// Hand out the start cells: the first team-1 player's house takes cell 0,
// then every other house that is not multiplay-passive takes the cell slot 49
// picks for it. Fails when there is no defender, its house index is out of
// range, or its house is passive.
//
// PARTIAL (9.4% positional, 91.4% aligned). The search for the team-1 player:
// retail loads both the player count and the item pointer before testing the
// count, and re-tests `i < count` after the loop instead of jumping straight
// to the failure path; VC6 here loads the items only inside the loop and
// threads the jump, which shifts everything after it. The rest lines up.
// Tried: a for/break loop (7.2%), a while loop (9.4%), a file-local inline
// search helper (9.4%). Caching count and items in locals reaches 17.3% /
// 97.1% aligned, but those are redundant aliases and are not kept.
bool MultiplayerSiege::vf_33(bool unknown)
{
    DynamicVectorClass<Cell> starts = FUN_00688380(unknown);
    bool taken[16];
    memset(taken, 0, sizeof(taken));

    int i = 0;
    while (i < PlayerCount_00A8DA84 && Players_00A8DA78[i]->unknown_6B != 1) {
        i++;
    }
    if (i >= PlayerCount_00A8DA84) {
        return false;
    }

    int index = Players_00A8DA78[i]->Id;
    if (index < 0 || index >= DAT_00A80228.Count) {
        return false;
    }
    HouseClass* defender = DAT_00A80228.Items[index];
    HouseTypeClass* type = (HouseTypeClass*)defender->Type;
    if (type->MultiplayPassive) {
        return false;
    }
    FUN_004068E0("Assigning Starting Points for Defending house %d (%s)\n", index, type->ID);
    taken[0] = true;
    defender->FUN_0050E000(starts.Items[0]);

    for (int h = 0; h < DAT_00A80228.Count; h++) {
        HouseClass* house = DAT_00A80228.Items[h];
        HouseTypeClass* houseType = (HouseTypeClass*)house->Type;
        if (!houseType->MultiplayPassive && house != defender) {
            FUN_004068E0("Assigning Starting Points for Attacking house %d (%s)\n", h, houseType->ID);
            house->FUN_0050E000(vf_49(h, starts, taken));
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA9B0
//
// The siege's three teams, in order: observers, defenders, attackers.
void MultiplayerSiege::CreateMPTeams(DynamicVectorClass<MultiplayerTeam*>& teams)
{
    teams.AddItem(new MultiplayerObserverTeam);
    teams.AddItem(new MultiplayerSiegeDefenderTeam);
    teams.AddItem(new MultiplayerSiegeAttackerTeam);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CAAC0
//
// A defending player's house gets one building of the first buildable type
// from the rules list at +0x8AC, placed at the house's own coordinate or, if
// that fails, at the cell 0x688ED0 finds near its base cell; a building that
// cannot be placed is deleted. Houses with no player, and attackers, take the
// base-class path (the former reporting failure regardless).
//
// PARTIAL (6.5% positional, 65.0% aligned). The same player search as 0x5CA800
// (retail hoists the item pointer and keeps `this` in a stack slot it reloads
// before the post-loop test), and retail sends the three failure exits after
// the search (no type, allocation failed, null building) to one shared
// epilogue where VC6 here gives each its own. Tried: for/break (6.5%), a while
// search (5.6%), the placement written as nested ifs with one final
// `return false` (8.6% positional but 58.6% aligned).
bool MultiplayerSiege::SpawnBaseUnits(HouseClass* house, int unknown)
{
    int i;
    for (i = 0; i < PlayerCount_00A8DA84; i++) {
        if (Players_00A8DA78[i]->Id == house->ArrayIndex) {
            break;
        }
    }
    if (i >= PlayerCount_00A8DA84) {
        MultiplayerGameMode::SpawnBaseUnits(house, unknown);
        return false;
    }
    if (Players_00A8DA78[i]->unknown_6B != 1) {
        return MultiplayerGameMode::SpawnBaseUnits(house, unknown);
    }

    BuildingTypeClass* type = house->FUN_005051E0(DAT_008871E0->unknown_8AC);
    if (type == 0) {
        return false;
    }
    BuildingClass* building = new BuildingClass(type, house);
    if (building == 0) {
        return false;
    }
    if (!building->vf_54(house->FUN_0050DF30(), 0)) {
        if (FUN_00688ED0(building, house->FUN_0050DEF0(), 1) == 0) {
            delete building;
            return false;
        }
    }
    return true;
}
