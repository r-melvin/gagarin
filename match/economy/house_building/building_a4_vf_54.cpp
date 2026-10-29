// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 54 at 0x440580 (0x1069 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode). It takes a world coordinate and a facing and puts the
//   building on the map; slot 54 follows the take-off-the-map virtual at slot 53 (0x445880), and the
//   original name is not confirmed here.

#include "building_a4_views.h"
#include "../../_layout/session_class.h"

// FUNCTION: GAMEMD 0x440580
bool BuildingClass::vf_54(const CoordStruct& where, int dir)
{
    int i;
    int x;
    int y;
    bool ok = vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0;

    if (ok) {
        if (Type == RulesInstance->WallTower) {
            CellClass* mc = DAT_0087F7E8.FUN_00565730(where);
            HouseClass* cellOwner = 0;
            if (mc->WallOwnerIndex >= 0) {
                cellOwner = DAT_00A8022C[mc->WallOwnerIndex];
            }
            if (cellOwner == Owner && (mc->OverlayTypeIndex == 2 || mc->OverlayTypeIndex == 0)) {
                Owner->FUN_004FCE80(&mc->MapCoords, 1);
            }
        } else if (Type->ToOverlay) {
            CellClass* mc = DAT_0087F7E8.FUN_00565730(where);
            HouseClass* cellOwner = 0;
            if (mc->WallOwnerIndex >= 0) {
                cellOwner = DAT_00A8022C[mc->WallOwnerIndex];
            }
            if (cellOwner == Owner && mc->OverlayTypeIndex == Type->ToOverlay->ArrayIndex) {
                Owner->FUN_004FCE80(&mc->MapCoords, 1);
            }
        } else if (Type->bools_16A4[19]) {
            CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
            for (CellStruct* p = static_cast<CellStruct*>(Type->vf_36(1)); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
                CellClass* mc = BA4At(*p + cell);
                HouseClass* cellOwner = 0;
                if (mc->WallOwnerIndex >= 0) {
                    cellOwner = DAT_00A8022C[mc->WallOwnerIndex];
                }
                if (cellOwner == Owner && (mc->OverlayTypeIndex == 2 || mc->OverlayTypeIndex == 0 || mc->OverlayTypeIndex == 0x1A)) {
                    Owner->FUN_004FCE80(&mc->MapCoords, 1);
                }
                BuildingClass* neighbour = mc->FUN_0047C520();
                if (neighbour && neighbour->Type->bools_16A4[27]) {
                    if (neighbour->vf_14() == vf_14()) {
                        CellStruct copy = mc->MapCoords;
                        copy.FUN_00453240();
                    }
                }
            }
        }
    }

    if (Type->bools_1570[1]) {
        if (vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0) {
            ObjectClass* created = Type->ToOverlay->vf_35(Owner);
            if (created && created->vf_54(where, 0)) {
                DAT_0087F7E8.FUN_00565730(where)->WallOwnerIndex = Owner->ArrayIndex;
                vf_157(3);
                DAT_0087F7E8.FUN_005678E0(&where, Type->Sight, Owner, 0, 0, 0, 1, 0);
                DAT_0087F7E8.FUN_005678E0(&where, Type->Sight, Owner, 0, 0, 0, 1, 1);
                vf_62();
                return true;
            }
        }
        goto refuse;
    }

    if (Type->PowersUpBuilding) {
        Point2D unused;
        unused.X = 0;
        unused.Y = 0;
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        BuildingClass* other = DAT_0087F7E8.FUN_004AA290(&cell, &unused);
        if (!other || other->vf_11() != 6) {
            goto refuse;
        }
        BuildingTypeClass* thisType = Type;
        if (Owner != other->Owner) {
            goto refuse;
        }
        if (_stricmp(thisType->PowersUpBuilding, other->Type->ID) != 0) {
            goto refuse;
        }
        int levels = thisType->PowersUpToLevel;
        if (levels == -1) {
            if (!(other->UpgradeLevel < other->Type->Upgrades)) {
                if (other->UpgradeLevel != 0) {
                    goto refuse;
                }
            }
        } else {
            if (levels <= 0 || levels > 3) {
                goto refuse;
            }
            if (other->UpgradeLevel != 0) {
                goto refuse;
            }
        }
        Owner->RecheckRadar = 1;
        Owner->RecheckPower = 1;
        int count = Type->PowersUpToLevel;
        if (count == -1) {
            count = 1;
        }
        char* name = &other->Type->BuildingAnim[other->UpgradeLevel].Anim[0];
        if (_stricmp(name, Type->ImageFile) != 0) {
            strncpy(name, Type->ImageFile, 16);
        }
        for (; count != 0; count--) {
            other->FUN_00451400();
        }
        other->Upgrades[other->UpgradeLevel] = Type;
        Owner->FUN_0050B1D0();
        Owner->RecheckTechTree = 1;
        if (Type->bools_1760[3]) {
            Owner->AcquiredThreatNode();
        }
        vf_62();
        return true;
    }

    if (Type->bools_16A4[27]) {
        DirStruct facing;
        facing.Whole = dir;
        if ((((facing.Whole >> 12) + 1) & 6) == 4) {
            LaserFenceFrame = 8;
        } else {
            LaserFenceFrame = 12;
        }
    }
    if (ok && Type->bools_16A4[26]) {
        LaserFenceFrame = 0;
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        BuildingClass* other = BA4At(cell)->FUN_0047C520();
        if (other && other->Type->bools_16A4[27]) {
            if (other->vf_14() == vf_14()) {
                other->vf_62();
            }
        }
    }
    if (!TechnoClass::vf_54(where, dir)) {
        goto refuse;
    }
    if (Type->bools_16A4[35]) {
        Owner->HasCloakingRanges = 1;
    }
    if (!IsAlive) {
        return true;
    }
    if (Session_00A8B238.GameMode && !Owner->IsControlledByHuman() && !Owner->Type->MultiplayPassive) {
        ShouldRebuild = 1;
    }
    if (DAT_00A8B230->unknown_0000 & 0x1000) {
        CellStruct here = vf_110();
        CellStruct* p;
        for (p = static_cast<CellStruct*>(Type->vf_36(0)); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
            if (BA4At(p->FUN_0042D510(here))->Flags & 0x400000) {
                goto skip;
            }
        }
        FUN_00457AA0(0, 0, 0);
    }
skip:
    if ((!Type->UndeploysInto || !Type->ResourceGatherer) && !vf_32()) {
        FUN_00455F10(0);
    }
    {
        int width = Type->GetFoundationWidth();
        int height = Type->GetFoundationHeight(false);
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        for (y = 0; y < height + 2; y++) {
            for (x = 0; x < width + 2; x++) {
                BA4At(cell + BA4Off(x - 1, y - 1))->BlockedNeighbours++;
            }
        }
    }
    Owner->FUN_004FD150();
    Owner->FUN_004FFA50(this);
    Owner->RecheckTechTree = 1;
    unknown_544 = 0;
    if ((!DiscoveredByCurrentPlayer && (DAT_0087F7E8.FUN_00565730(where)->AltFlags & 0x10)) || Session_00A8B238.GameMode) {
        vf_102(DAT_00A83D4C);
    } else if (Type->LightIntensity) {
        if (!LightSource) {
            LightSourceClass* light = new LightSourceClass(vf_18(), Type->LightVisibility, Type->LightIntensity, Type->LightRedTint, Type->LightGreenTint, Type->LightBlueTint);
            LightSource = light;
        }
        LightSource->Activate(0);
    }
    if (Type->bools_16A4[26] && !DAT_00A8E7AC && IsAlive && !InLimbo) {
        FUN_00452DC0(0);
        FUN_00452DC0(2);
        FUN_00452DC0(4);
        FUN_00452DC0(6);
        CreateEndPost(true);
    }
    if (!Owner->IsControlledByHuman()) {
        vf_102(Owner);
    }
    if (IsOwnedByCurrentPlayer) {
        DAT_00880CF4 = 1;
        DAT_0087F7E8.FUN_004F42F0(0);
    }
    if (Type->NaturalParticleSystem && !NaturalParticleSystem) {
        CoordStruct offset = Type->NaturalParticleSystemLocation;
        CoordStruct loc = Location;
        CoordStruct target;
        target.X = Location.X + offset.X;
        target.Y = Location.Y + offset.Y;
        target.Z = Location.Z + offset.Z;
        NaturalParticleSystem = new BA4Tracker(Type->NaturalParticleSystem, &target, DAT_0087F7E8.FUN_00565730(&loc), 0, &DAT_0089C848, 0);
    }
    if (Type == RulesInstance->WallTower) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(-1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(0, 1))->FUN_00480630(0);
        BA4At(base + BA4Off(0, -1))->FUN_00480630(0);
    }
    if (Type == RulesInstance->GDIGateOne || Type == RulesInstance->NodGateOne) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(-1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(3, 0))->FUN_00480630(0);
    }
    if (Type == RulesInstance->GDIGateTwo || Type == RulesInstance->NodGateTwo) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(0, -1))->FUN_00480630(0);
        BA4At(base + BA4Off(0, 3))->FUN_00480630(0);
    }
    if (Type->bools_154B[0]) {
        Spotlight = new BuildingLightClass(this);
    }
    IsPrimaryFactory = 0;
    if (Type->Factory) {
        FUN_00448070(0);
    }
    for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
        if (RulesInstance->list_08AC.Items[i] == Type) {
            Owner->ConYards.AddItem(this);
            break;
        }
    }
    if (Type->bools_16A4[5]) {
        Owner->UnitRepairStations.AddItem(this);
    }
    if (Type->bools_16A4[9]) {
        Owner->Grinders.AddItem(this);
    }
    if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
        Owner->Absorbers.AddItem(this);
    }
    if (Type->bools_16A4[7]) {
        Owner->Bunkers.AddItem(this);
    }
    if (Type->bools_1570[11] && Type->TechLevel > -1) {
        Owner->Occupiables.AddItem(this);
    }
    if (Type->bools_16A4[8]) {
        Owner->CloningVats.AddItem(this);
    }
    if (Type->bools_16A4[12]) {
        Owner->SecretLabs.AddItem(this);
    }
    if (Type->PsychicDetectionRadius > 0) {
        Owner->PsychicDetectionBuildings.AddItem(this);
    }
    if (Type->bools_16A4[41]) {
        Owner->FactoryPlants.AddItem(this);
        Owner->CalculateCostMultipliers();
    }
    Owner->Buildings.AddItem(this);
    if (!Owner->IsControlledByHuman()) {
        Owner->Base.FUN_0042F260(this);
    }
    if (Type->Factory) {
        Owner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
    }
    return true;
refuse:
    return false;
}
