// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x6FB740 in retail gamemd.exe v1.001 (Techno.CPP range): the per-frame cloak state
//   machine. It steps the cloak stage timer and moves the object between uncloaked, cloaking, cloaked
//   and uncloaking according to its state, rank, health and surroundings.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/unit_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/scenario_ptr_00a8b230.h"
#include "../core/scenario_class_methods.h"
#include "../core/vector_class_operations.h"
#include "../core/vector_class_mutation.h"
#include "../core/mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0xA8EC78 -- TechnoClass::Array.
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
// GLOBAL: GAMEMD 0xB0EA90
extern MathTblZero3 DAT_00B0EA90;

// Rank-granted cloak: a veteran whose type grants the cloak ability at the veteran tier, or an elite
// granted it at either tier.
static inline bool CloaksByRank(TechnoClass* self)
{
    VeterancyStruct* vet = &self->Veterancy;
    TechnoTypeClass* type;
    return (vet->FUN_0074FF90() || vet->FUN_00750010())
        && (type = self->vf_33(),
            (vet->FUN_0074FF90() && type->VeteranAbilities._raw[6])
            || (vet->FUN_00750010() && (type->VeteranAbilities._raw[6] || type->EliteAbilities._raw[6])));
}

// The stage advance shared by both paths: when the timer has run out and a rate is set, step the value and
// restart the timer; the changed flag reports whether it advanced.
static inline void AdvanceStage(StageClass& stage)
{
    if (!stage.Timer.FUN_00426630() && stage.Rate != 0) {
        stage.HasChanged = true;
        stage.Value += stage.Step;
        stage.Timer = CDTimerClass(stage.Rate);
    } else {
        stage.HasChanged = false;
    }
}

// FUNCTION: GAMEMD 0x6FB740
// Per-frame cloak update.
void TechnoClass::vf_260(int)
{
    if (CloakState == 0) {
        if (!IsCloakable() || IsUnderEMP() || vf_224() || vf_117() || vf_118()) {
            if (!CloaksByRank(this)) {
                return;
            }
        }
        TechnoClass* link = FUN_0065AD30(0);
        if (link && link->vf_11() == 6 && ((BuildingClass*)link)->Type->bools_16A4[25]) {
            return;
        }
        AdvanceStage(CloakProgress);
        if (vf_168()) {
            if (FUN_005F5C60() > Rules->ConditionRed) {
                vf_280(false);
                return;
            }
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 4) {
                vf_280(false);
            }
        }
        return;
    }
    AdvanceStage(CloakProgress);
    if (CloakProgress.Value < 0) {
        CloakProgress.Value = 0;
    }
    switch (CloakState) {
    case 3:
        vf_73(2);
        switch (vf_26(1, 0)) {
        case 0: {
            CloakProgress.SetRate(0);
            CloakProgress.Value = 0;
            CloakState = 0;
            CDTimerClass delay;
            delay.StartTime = delay.CurrentTime;
            delay.TimeLeft = (int)(Rules->CloakDelay * 900.0);
            CloakDelayTimer = delay;
            vf_73(2);
            return;
        }
        case 1:
            if (vf_168()) {
                vf_280(true);
            }
            break;
        }
        break;
    case 2:
        if (vf_169()) {
            vf_279(false);
        }
        break;
    case 1:
        vf_73(2);
        if (CloakProgress.Rate == 0) {
            CloakProgress.SetRate(1);
        }
        switch (vf_26(1, 0)) {
        case 2:
            if (FUN_005F5C60() > Rules->ConditionRed) {
                return;
            }
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 10) {
                vf_279(true);
            }
            break;
        case 3:
        case 5:
            CloakState = 2;
            CloakProgress.SetRate(0);
            CloakProgress.Value = 0;
            vf_73(2);
            if (vf_11() == 1 && ((UnitClass*)this)->FlagHouseIndex != -1) {
                vf_63();
            } else {
                DynamicVectorClass<TechnoClass*> watchers;
                for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
                    TechnoClass* other = DAT_00A8EC78.Items[i];
                    if (other->Target == this) {
                        if (DAT_0087F7E8.FUN_00565730(vf_18())->FUN_004870D0(other->Owner->ArrayIndex)
                            || other->Owner == Owner) {
                            watchers.AddItem(other);
                        }
                    }
                }
                vf_55(false);
                for (int j = watchers.Count - 1; j >= 0; j--) {
                    watchers.Items[j]->vf_242(this);
                }
            }
            if (vf_11() == 1 && !Owner->FUN_0050B730()) {
                vf_93(DAT_00B0EA90, true, false);
            }
            break;
        }
        break;
    }
}
