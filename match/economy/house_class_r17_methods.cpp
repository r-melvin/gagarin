// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and callees read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at
//   the address in each annotation.
//
// Round 17 HouseClass bodies, ascending by retail address. They are declared on a view
// derived from HouseClass so the shared header stays untouched.
// Address index: 0x4FC980 0x4FF980 0x4FFA50.
#include "../_layout/house_class.h"
#include "../_layout/techno_type_class.h"

struct HouseView_004FC980 : HouseClass
{
    char FUN_004FC980();
};

// FUNCTION: GAMEMD 0x4FC980
// Ends the game for this house once, unless it has already won or lost, and starts the
// borrowed-time countdown from now. Answers the game-over flag.
char HouseView_004FC980::FUN_004FC980()
{
    if (IsWinner == 0) {
        if (IsGameOver == 0 && IsLoser == 0) {
            IsGameOver = 1;
            CDTimerClass tmp(0);
            BorrowedTime = tmp;
        }
    }
    return IsGameOver;
}

// A building type and the building that points at it, only as far as the counters need.
struct BuildingTypeView_r17
{
    char _pad_000[0xEB8];
    int Category;            // +0xEB8
};
GG_STATIC_ASSERT(offsetof(BuildingTypeView_r17, Category) == 0xEB8);

struct BuildingView_r17
{
    char _pad_000[0x520];
    BuildingTypeView_r17* Type;   // +0x520
};
GG_STATIC_ASSERT(offsetof(BuildingView_r17, Type) == 0x520);

struct HouseView_004FF980 : HouseClass
{
    void FUN_004FF980(TechnoClass* building);
    void FUN_004FFA50(TechnoClass* building);
};

// FUNCTION: GAMEMD 0x4FF980
// PARTIAL: 88.9%. Retail tests the naval flag as a byte (test cl,cl); a plain bool test differs.
// Takes one off the matching factory counter (airpad, barracks, war factory, construction
// yard or shipyard) when a building of that category is removed from this house.
void HouseView_004FF980::FUN_004FF980(TechnoClass* building)
{
    if (building->vf_11() == 6) {
        TechnoTypeClass* type = building->vf_33();
        bool naval;
        if (type == 0 || !type->Naval)
            naval = false;
        else
            naval = true;
        int* counter;
        switch (((BuildingView_r17*)building)->Type->Category) {
        case 1:
        case 0x28:
            if (naval)
                counter = &NumShipyards;
            else
                counter = &NumWarFactories;
            break;
        case 2:
        case 3:
            counter = &NumAirpads;
            break;
        default:
            return;
        case 0xF:
        case 0x10:
            counter = &NumBarracks;
            break;
        case 6:
        case 7:
            counter = &NumConYards;
        }
        if (counter != 0)
            *counter -= 1;
    }
}

// FUNCTION: GAMEMD 0x4FFA50
// PARTIAL: 88.9%. Retail tests the naval flag as a byte (test cl,cl); a plain bool test differs.
// As 0x4FF980, adding one when a building of the category is added.
void HouseView_004FF980::FUN_004FFA50(TechnoClass* building)
{
    if (building->vf_11() == 6) {
        TechnoTypeClass* type = building->vf_33();
        bool naval;
        if (type == 0 || !type->Naval)
            naval = false;
        else
            naval = true;
        int* counter;
        switch (((BuildingView_r17*)building)->Type->Category) {
        case 1:
        case 0x28:
            if (naval)
                counter = &NumShipyards;
            else
                counter = &NumWarFactories;
            break;
        case 2:
        case 3:
            counter = &NumAirpads;
            break;
        default:
            return;
        case 0xF:
        case 0x10:
            counter = &NumBarracks;
            break;
        case 6:
        case 7:
            counter = &NumConYards;
        }
        if (counter != 0)
            *counter += 1;
    }
}
