// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 53 at 0x445880 (0x5C6 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode). Slot 53 is where ObjectClass keeps its "take off the
//   map" virtual; the original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x445880
bool BuildingClass::vf_53()
{
    int i;
    bool result;
    bool anyUpgradeFlag = false;
    CoordStruct coord = Location;
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);

    if (!InLimbo && Type != 0) {
        for (i = 0; i < 8; i++) {
            if (DamageFireAnims[i]) {
                DamageFireAnims[i]->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        if (Type->bools_16A4[40] && ActuallyPlacedOnMap) {
            Owner->NumOrePurifiers--;
            if (Owner->NumOrePurifiers < 0) {
                Owner->NumOrePurifiers = 0;
            }
        }
        if (Type->bools_16A4[39] && ActuallyPlacedOnMap) {
            Owner->AirportDocks -= Type->NumberOfDocks;
            if (Owner->AirportDocks < 0) {
                Owner->AirportDocks = 0;
            }
        }
        if (Type->InfantryGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->InfantrySelfHeal -= Type->InfantryGainSelfHeal;
            if (Owner->InfantrySelfHeal < 0) {
                Owner->InfantrySelfHeal = 0;
            }
        }
        if (Type->UnitsGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->UnitsSelfHeal -= Type->UnitsGainSelfHeal;
            if (Owner->UnitsSelfHeal < 0) {
                Owner->UnitsSelfHeal = 0;
            }
        }
        if (Type->bools_16A4[26]) {
            FUN_00452A40(0);
        }
        if (!DAT_00A8E7AC) {
            if (Type->bools_16A4[36]) {
                vf_318(DAT_0089C818.raw_dword);
            }
            if (Type->bools_D20[17]) {
                vf_320(DAT_0089C818.raw_dword);
            }
            if ((!Type->UndeploysInto || !Type->ResourceGatherer) && !vf_32()) {
                FUN_004561F0();
            }
        }
        for (i = 0; i < 3; i++) {
            if (Upgrades[i] && Upgrades[i]->bools_1760[3]) {
                anyUpgradeFlag = true;
                break;
            }
        }
        if (!DAT_00A8E9A0) {
            if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
                LaserFenceFrame = 0;
            }
            return true;
        }
        if (Type == RulesInstance->WallTower) {
            for (i = 0; i < 8; i += 2) {
                CellClass* mc = BA4At(cell + DAT_0089F688[i & 7]);
                mc->FUN_00480630(0);
                if (mc->OverlayTypeIndex != -1 && DAT_00A83D84[mc->OverlayTypeIndex]->Wall && mc->OverlayData < 0x10) {
                    mc->FUN_00480CB0(200);
                }
            }
        }
        if (Type == RulesInstance->GDIGateOne || Type == RulesInstance->NodGateOne) {
            BA4At(cell + BA4Off(-1, 0))->FUN_00480630(0);
            BA4At(cell + BA4Off(3, 0))->FUN_00480630(0);
        }
        if (Type == RulesInstance->GDIGateTwo || Type == RulesInstance->NodGateTwo) {
            BA4At(cell + BA4Off(0, -1))->FUN_00480630(0);
            BA4At(cell + BA4Off(0, 3))->FUN_00480630(0);
        }
        if (!Type->ToTile) {
            int width = Type->GetFoundationWidth();
            int height = Type->GetFoundationHeight(false);
            CellStruct scratch = vf_110();
            CellStruct origin = scratch;
            for (int y = 0; y < height + 2; y++) {
                CellStruct corner = origin + BA4Off(-1, -1);
                for (i = 0; i < width + 2; i++) {
                    BA4At(corner + BA4Off(i, y))->BlockedNeighbours--;
                }
            }
        }
        if (DAT_00887324) {
            RectangleStruct buf = vf_75();
            DAT_00887324->FUN_006D2790(buf, false);
        }
        if (Spotlight) {
            Spotlight->vf_62();
        }
        Owner->FUN_004FF980(this);
        Owner->RecheckTechTree = 1;
        Owner->FUN_004FD150();
        if (Owner == DAT_00A83D4C) {
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        Owner->FUN_0050A490(this);
    }
    result = TechnoClass::vf_53();
    if (anyUpgradeFlag) {
        Owner->AcquiredThreatNode();
    }
    if (Type->Factory) {
        Owner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
    }
    if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
        LaserFenceFrame = 0;
    }
    return result;
}
