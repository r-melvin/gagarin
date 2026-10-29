// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 245 at 0x448260 (0x11A6 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode; Ghidra's flow listing mixes up the old and the new owner
//   in the second half). It moves the building to another house: the old house's lists drop it, the base
//   class changes the owner, the new house's lists take it. The original name is not confirmed here.

#include "building_a4_views.h"
#include "../../_layout/bomb_class.h"
#include "../../_layout/session_class.h"

// FUNCTION: GAMEMD 0x448260
bool BuildingClass::vf_245(HouseClass* newOwner, bool announce)
{
    int i;

    if (newOwner != Owner) {        if (AttachedBomb && !Type->bools_1570[11]) {
            AttachedBomb->Disarm();
        }
        if (Type->bools_16A4[35]) {
            newOwner->HasCloakingRanges = 1;
        }
        if (Owner->Type->MultiplayPassive && Type->ProduceCashStartup) {
            newOwner->GiveMoney(Type->ProduceCashStartup);
            CashProductionTimer = CDTimerClass(Type->ProduceCashDelay);
        }
        unsigned int bit = 1 << (newOwner->Type->ArrayIndex2);
        if ((bit & DisplayProductionTo) != 0) {
            DisplayProductionTo = DisplayProductionTo - bit;
            if (Type->bools_16A4) {
                Owner->RadarVisibleTo = 0;
                int count = Owner->Buildings.Count;
            for (i = 0; i < count; i++) {
                    BuildingClass* b = Owner->Buildings.Items[i];
                    if (b && !b->InLimbo && b->Type->bools_16A4) {
                        Owner->RadarVisibleTo |= b->DisplayProductionTo;
                    }
                }
                DAT_0087F7E8.FUN_004F42F0(2);
            }
        }
        IsPrimaryFactory = 0;
        if (Type->bools_16A4[26]) {
            FUN_00452A40(0);
        }
        if (Owner->IsControlledByCurrentPlayer() || newOwner->IsControlledByCurrentPlayer()) {
            if (!newOwner->Type->MultiplayPassive && announce) {
                if (Type->bools_154B[7]) {
                    if (Owner != newOwner) {
                        if (Owner->IsControlledByCurrentPlayer()) {
                            FUN_00752700(s_EVA_TechBuildingLost_00818FC4, -1, -1);
                        }
                        if (newOwner->IsControlledByCurrentPlayer() && newOwner->IsControlledByCurrentPlayer() && Type->CaptureEvaEvent != -1) {
                            FUN_00752480(Type->CaptureEvaEvent, -1, -1);
                        }
                    }
                } else {
                    if (FUN_0065FA70(10, vf_110())) {
                        FUN_00752700(s_EVA_BuildingCaptured_00818FAC, -1, -1);
                    }
                }
            }
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        NeedsRedraw = 1;
        HasEngineer = 1;
        if (Type->bools_154B[7]) {
            StuffEnabled = 1;
            if (LightSource) {
                LightSource->Activate(0);
            }
            if (Type->bools_16A4[26]) {
                CreateEndPost(false);
            }
            for (int k = 0; k < 21; k++) {
                if (Type->BuildingAnim[k].Powered && Anims[k]) {
                    Anims[k]->FUN_00425270();
                }
            }
        }
        if (Session_00A8B238.GameMode == 4 && !vf_33()->bools_C8C[19]) {
            newOwner->CapturedBuildings.IncrementUnitTotal(Type->ArrayIndex);
        }

        BA4HeldList held;
        for (i = 0; i < RadioLinks.Capacity; i++) {
            TechnoClass* object = FUN_0065AD30(i);
            if (object) {
                if (!object->Flags.IsFoot) {
                    object = 0;
                } else if (vf_158(0x13, object) == 1) {
                    bool inRange = false;
                    if (!Type->bools_16A4[25]) {
                        CoordStruct a = vf_42(object);
                        CoordStruct b = object->vf_18();
                        CoordStruct scratchC;
                        CoordStruct diff = *scratchC.FUN_0041C230(b.X - a.X, b.Y - a.Y, b.Z - a.Z);
                        inRange = diff.FUN_0041C380() < 0x40;
                    } else {
                        inRange = true;
                    }
                    if (inRange) {
                        unsigned char flag = object->IsTether;
                        object->vf_245(newOwner, 1);
                        BA4Held* entry = new BA4Held(object, flag);
                        held.AddItem(entry);
                        continue;
                    }
                    vf_158(0x17, object);
                    vf_158(3, object);
                    continue;
                }
                vf_158(0x17, object);
                vf_158(3, object);
            }
        }
        if (Factory) {
            Factory->AbandonProduction();
            if (Factory) {
                delete Factory;
            }
            Factory = 0;
        }
        Owner->FUN_004FF980(this);
        HouseClass* oldOwner = Owner;
        BA4TargetRef target;
        target.FUN_006E6AB0(this);
        HasBeenCaptured = 1;

        for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
            if (RulesInstance->list_08AC.Items[i] == Type) {
                oldOwner->ConYards.RemoveItem(this);
                break;
            }
        }
        if (Type->bools_16A4[5]) {
            oldOwner->UnitRepairStations.RemoveItem(this);
        }
        if (Type->bools_16A4[9]) {
            oldOwner->Grinders.RemoveItem(this);
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            oldOwner->Absorbers.RemoveItem(this);
        }
        if (Type->bools_16A4[7]) {
            oldOwner->Bunkers.RemoveItem(this);
        }
        if (Type->bools_1570[11] && Type->TechLevel > -1) {
            oldOwner->Occupiables.RemoveItem(this);
        }
        if (Type->bools_16A4[8]) {
            oldOwner->CloningVats.RemoveItem(this);
        }
        if (Type->bools_16A4[12]) {
            oldOwner->SecretLabs.RemoveItem(this);
        }
        if (Type->PsychicDetectionRadius > 0) {
            oldOwner->PsychicDetectionBuildings.RemoveItem(this);
        }
        if (Type->bools_16A4[41]) {
            oldOwner->FactoryPlants.RemoveItem(this);
            oldOwner->FUN_0050BF60();
        }
        oldOwner->Buildings.RemoveItem(this);
        if (Type->bools_16A4[40]) {
            oldOwner->NumOrePurifiers--;
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
        if (Type->bools_16A4[39]) {
            oldOwner->AirportDocks -= Type->NumberOfDocks;
        }
        if (Type->bools_16A4[35]) {
            HasCloakingData = 0xFF;
            if (!CloakRadius) {
                CloakRadius = Type->CloakRadiusInCells;
            }
            NeedsRedraw = 1;
            CloakRadius = 1;
            vf_260(1);
        }
        if (Type->GapGenerator) {
            vf_262();
        }
        vf_291(0, 0, 0, 0);
        TechnoClass::vf_245(newOwner, true);
        if (Type->bools_16A4[35] && vf_212() && Type->bools_16A4[35]) {
            HasCloakingData = 1;
            if (CloakRadius == Type->CloakRadiusInCells) {
                CloakRadius = 0;
            }
            NeedsRedraw = 1;
        }
        if (Type->GapGenerator && vf_212()) {
            vf_261();
        }
        FUN_00448070(0);
        oldOwner->ToCapture = this;
        oldOwner->FUN_004FD150();
        Owner->FUN_004FD150();
        if (Owner->ToCapture == this) {
            Owner->ToCapture = 0;
        }
        if (oldOwner->FUN_0050B6F0() && Type->bools_16A4[21]) {
            DAT_0088098C = 0;
            DAT_00880990 = 0;
            DAT_00880994 = -1;
            DAT_0087F7E8.FUN_004A8BF0(0);
        }
        Owner->FUN_004FFA50(this);
        IsBeingRepaired = 0;
        vf_311(1);
        if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
            if (IsAlive && !InLimbo) {
                FUN_00452DC0(0);
                FUN_00452DC0(2);
                FUN_00452DC0(4);
                FUN_00452DC0(6);
                CreateEndPost(true);
                if (DAT_00A8E7AC) {
                    goto afterFacing;
                }
            }
            if (Type->bools_16A4[26]) {
                LaserFenceFrame = 0;
            }
        }
    afterFacing:
        if (Owner->IsControlledByCurrentPlayer()) {
            vf_290(0, 0, 0, 0, 0);
            DAT_0087F7E8.FUN_004F42F0(1);
        }
        bit = 1 << (newOwner->Type->ArrayIndex2);
        if ((bit & DisplayProductionTo) != 0) {
            DisplayProductionTo = ~bit & DisplayProductionTo;
        }
        void* value = vf_121();
        int angle = vf_281(vf_111()->Intensity_Normal);
        if (vf_88() || (Airstrike && Airstrike->Target == FUN_00459F40())) {
            angle = FUN_0070E360(angle);
        }
        LightTint = (short)angle;
        FUN_00451F60(value, angle & 0xFFFF);
        FUN_00452170(Translucency);

        for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
            if (RulesInstance->list_08AC.Items[i] == Type) {
                newOwner->ConYards.AddItem(this);
                break;
            }
        }
        if (Type->bools_16A4[5]) {
            newOwner->UnitRepairStations.AddItem(this);
        }
        if (Type->bools_16A4[9]) {
            newOwner->Grinders.AddItem(this);
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            newOwner->Absorbers.AddItem(this);
        }
        if (Type->bools_16A4[7]) {
            newOwner->Bunkers.AddItem(this);
        }
        if (Type->bools_1570[11] && Type->TechLevel > -1) {
            newOwner->Occupiables.AddItem(this);
        }
        if (Type->bools_16A4[8]) {
            newOwner->CloningVats.AddItem(this);
        }
        if (Type->bools_16A4[12]) {
            newOwner->SecretLabs.AddItem(this);
        }
        if (Type->PsychicDetectionRadius > 0) {
            newOwner->PsychicDetectionBuildings.AddItem(this);
        }
        if (Type->bools_16A4[41]) {
            newOwner->FactoryPlants.AddItem(this);
            newOwner->CalculateCostMultipliers();
        }
        newOwner->Buildings.AddItem(this);
        if (Type->bools_16A4[40]) {
            Owner->NumOrePurifiers++;
        }
        if (Type->InfantryGainSelfHeal) {
            Owner->InfantrySelfHeal += Type->InfantryGainSelfHeal;
        }
        if (Type->UnitsGainSelfHeal) {
            Owner->UnitsSelfHeal += Type->UnitsGainSelfHeal;
        }
        if (Type->bools_16A4[39]) {
            Owner->AirportDocks += Type->NumberOfDocks;
        }
        if (Type->Factory) {
            oldOwner->FUN_00509140(Type->Factory, Type->Naval, 0);
            newOwner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
        }
        for (i = 0; i < held.Count; i++) {
            vf_158(2, held.Items[i]->Object);
            if (held.Items[i]->Flag) {
                IsTether = 1;
                held.Items[i]->Object->IsTether = 1;
            }
        }
        if (Session_00A8B238.GameMode && !newOwner->IsControlledByHuman() && InitialOwner != newOwner && !InitialOwner->Type->MultiplayPassive) {
            while (UpgradeLevel > 0) {
                int r = Upgrades[UpgradeLevel]->vf_46(Owner, 1);
                Owner->GiveMoney(r);
                FUN_00451690();
                Owner->RecheckPower = 1;
                Owner->RecheckRadar = 1;
            }
            vf_104(1);
        }
        oldOwner->RecheckTechTree = 1;
        newOwner->RecheckTechTree = 1;
        return true;
    }
    return false;
}
