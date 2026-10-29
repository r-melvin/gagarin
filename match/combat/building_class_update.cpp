// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Complete 0x43FB20..0x44057B body (0xA5B bytes, two RETs plus the shared
//   exit) read from the entry-bounded retail function. RTTI COL 0x7FC360 names
//   BuildingClass; its primary table 0x7E3EBC holds this function at slot 23.
//   Virtual calls are slot offsets divided by four: 0x350 = 212, 0x184 = 97,
//   0x1D4 = 117, 0x1D8 = 118, 0x200 = 128, 0x1EC = 123, 0x124 = 73,
//   0x3C8 = 242, 0x3AC = 235, 0x16C = 91, 0x1B8 = 110, 0xAC = 43, 0xD4 = 53.
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"
#include "../combat/airstrike_class_methods.h"
#include "../core/rules_class.h"
#include "../core/frame_counter.h"
#include "../map/map_class_methods.h"
#include "../ui/tactical_class_coords_to_client_methods.h"
#include "../_layout/map_0087f7e8.h"

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- ECX = sound, EDX = coordinate,
// one stack argument (the sound's audio controller).
void FUN_007509E0(int sound, const CoordStruct* coordinate, AudioController* controller);
// FUNCTION: GAMEMD 0x750D40 (decl; reloc) -- ECX = coordinate, EDX = audio controller.
void FUN_00750D40(const CoordStruct* coordinate, AudioController* controller);

// The global object whose method 0x5FB2E0 converts a rate.
struct Global_00A8EB60
{
    // FUNCTION: GAMEMD 0x5FB2E0 (decl; reloc) -- one stack argument.
    int FUN_005FB2E0(int rate);
};

// GLOBAL: GAMEMD 0xA8EB60
extern Global_00A8EB60 DAT_00A8EB60;
// GLOBAL: GAMEMD 0x887324 -- the tactical object.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0xABAD1C
extern int DAT_00ABAD1C;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// The frame timer's remaining time, expanded inline at each use: the whole
// duration while unstarted, 0 once it has run out, otherwise what is left.
static int TimeLeft(const CDTimerClass& timer)
{
    int left = timer.TimeLeft;
    if (timer.StartTime != -1) {
        int passed = CurrentFrame - timer.StartTime;
        if (passed >= left)
            return 0;
        left -= passed;
    }
    return left;
}

// FUNCTION: GAMEMD 0x43FB20
void BuildingClass::vf_23()
{
    unsigned char working;
    if (vf_212() && vf_97() != 0x12 && vf_97() != 0x13)
        working = 1;
    else
        working = 0;

    if (working != WasOnline) {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            Audio8.FUN_00405FD0();
            CoordStruct location = Location;
            if (working)
                FUN_007509E0(Type->WorkingSound, &location, &Audio8);
            else
                FUN_007509E0(Type->NotWorkingSound, &location, &Audio8);
        }
        FUN_004549B0();
        WasOnline = working;
    } else {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            CoordStruct location = Location;
            FUN_00750D40(&location, &Audio8);
        }
    }

    unsigned char damaged;
    if (Type->bools_1570[0xB])
        damaged = GetHealthPercentage() <= RulesInstance->ConditionRed;
    else
        damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    if (damaged != RequiresDamageFires) {
        if (damaged) {
            FUN_0043C0D0();
        } else {
            for (int i = 0; i < 8; i++) {
                if (DamageFireAnims[i] != 0) {
                    ((ObjectClass*)DamageFireAnims[i])->vf_62();
                    DamageFireAnims[i] = 0;
                }
            }
        }
        RequiresDamageFires = damaged;
    }

    if (Type->bools_C8C[0x15])
        TurretIsRotating = PrimaryFacing.FUN_004C9480();
    else
        TurretIsRotating = 0;

    if (TemporalTargetingMe != 0)
        ((AbstractClass*)TemporalTargetingMe)->vf_23();

    if (vf_117() || vf_118()) {
        // Active or occupied: spawn the type's anim at its muzzle points or, when
        // there are none, at the building's own location.
        if (Type->MaxNumberOccupants == 0 || RulesInstance->unknown_344 == 0) {
            if (CurrentFrame % 0x18 == 0 && RulesInstance->unknown_344 != 0)
                new AnimClass(RulesInstance->unknown_344, Location, 0, 1, 0x600, 0, false);
        } else {
            for (int index = 0; index < Type->MaxNumberOccupants; index++) {
                if ((CurrentFrame + index) % 0x18 == 0 && RulesInstance->unknown_344 != 0) {
                    Point2D projected;
                    Point2D* point = DAT_00887324->FUN_006D2070(&projected, &Type->MuzzleFlash[index]);
                    CoordStruct coordinate;
                    coordinate.X = point->X;
                    coordinate.Y = point->Y;
                    coordinate.Z = 0;
                    CoordStruct origin = vf_43();
                    coordinate.X += origin.X;
                    coordinate.Y += origin.Y;
                    coordinate.Z += origin.Z;
                    AnimClass* anim = new AnimClass(RulesInstance->unknown_344, coordinate, 0, 1, 0x600, 0, false);
                    anim->ZAdjust = -200;
                }
            }
        }
        if (Target != 0)
            vf_242(0);
        return;
    }

    if (TimeLeft(CashProductionTimer) == 1) {
        CashProductionTimer.StartTime = CurrentFrame;
        CashProductionTimer.TimeLeft = Type->ProduceCashDelay;
        if (!((HouseTypeClass*)Owner->Type)->MultiplayPassive && vf_212()) {
            if (Type->ProduceCashAmount > 0)
                Owner->FUN_004F9950(Type->ProduceCashAmount);
            else
                Owner->FUN_004F9790(-Type->ProduceCashAmount);
        }
    }

    if (Airstrike != 0 && ((AirstrikeClass*)Airstrike)->Target == this)
        vf_73(2);

    if (Type->bools_16A4[0x14] && Target != 0 && !((AbstractClass*)Target)->IsInAir())
        vf_242(0);

    FUN_004509D0();
    if (vf_128() && BState != 0 && vf_123())
        IsReadyToCommence = false;
    FUN_006F9E50();
    if (!IsAlive)
        return;

    if (vf_33()->IsGattling && FUN_0070DDF0() > 0)
        TurretAnimFrame++;

    if (Ammo == 0 && !Type->bools_16A4[0x1D] && !Type->bools_16A4[0x1E])
        Ammo = Type->Ammo;

    if (vf_97() != 1) {
        if (vf_33()->IsGattling && CurrentFrame - LastFireBulletFrame > RulesInstance->unknown_E04 + 5) {
            FUN_0070DE40(Type->RateDown);
            int current = FUN_0070DDF0();
            int stage = FUN_0070DDC0();
            if (stage > 0) {
                int limit;
                if (Veterancy.FUN_00750010())
                    limit = Type->EliteStage[stage - 1];
                else
                    limit = Type->WeaponStage[stage - 1];
                if (current < limit)
                    FUN_0070DDD0(stage - 1);
            }
        }
        if (vf_33()->IsGattling && FUN_0070DDF0() > 0)
            TurretAnimFrame++;
    }

    if (vf_128() && vf_123())
        IsReadyToCommence = false;

    if (QueueBState != -1) {
        if (BState != QueueBState) {
            BuildingAnimFrameStruct* row = &Type->BuildingAnimFrame[QueueBState];
            BState = QueueBState;
            int duration = row->Rate;
            if (BState == 0 || BState == 1)
                duration = DAT_00A8EB60.FUN_005FB2E0(row->Rate);
            StageClass::Timer.StartTime = CurrentFrame;
            StageClass::Timer.TimeLeft = duration;
            StageClass::Rate = duration;
            StageClass::Value = row->Frame;
        }
        QueueBState = -1;
    }

    if (Health != unknown_544) {
        Owner->RecheckPower = 1;
        Owner->RecheckRadar = 1;
        unknown_544 = Health;
    }

    if (Health == 0) {
        for (int i = 0; i < 8; i++) {
            if (DamageFireAnims[i] != 0) {
                ((ObjectClass*)DamageFireAnims[i])->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        if (TimeLeft(C4Timer) != 0)
            return;
        vf_53();
        FUN_00442D90((int)C4AppliedBy);
        vf_62();
        FUN_00441F60();
        return;
    }

    FUN_004503F0();
    if (Type->bools_1570[5]) {
        TechnoClass** list = (TechnoClass**)Overpowerers.Items;
        for (int i = Overpowerers.Count - 1; i >= 0; i--) {
            if (list[i]->Target != this && i < Overpowerers.Count) {
                Overpowerers.Count--;
                for (int j = i; j < Overpowerers.Count; j++)
                    list[j] = list[j + 1];
            }
        }
        int count = Overpowerers.Count;
        if (count >= 3 || (Owner->FUN_004FCE30() == DAT_007E1718 && HasPower && count >= 1))
            IsOverpowered = true;
        else
            IsOverpowered = false;
    }
    if (Type->bools_1570[0xB])
        FUN_00458200();
    FUN_00450630();
    if (Type->Factory != 0)
        FUN_004500F0();

    if (C4Applied) {
        if (TimeLeft(C4Timer) == 0) {
            if (Type->bools_16A4[0x12]) {
                bool special = false;
                for (int y = -2; y < 3; y++) {
                    for (int x = -2; x < 3; x++) {
                        CellStruct origin = vf_110();
                        CellStruct first;
                        first.X = origin.X + x;
                        first.Y = origin.Y + y;
                        int tile = DAT_0087F7E8.FUN_005657A0(&first)->IsoTileTypeIndex;
                        origin = vf_110();
                        CellStruct second;
                        second.X = origin.X + x;
                        second.Y = origin.Y + y;
                        int overlay = DAT_0087F7E8.FUN_005657A0(&second)->OverlayTypeIndex;
                        if ((tile >= DAT_00ABAD1C && tile < DAT_00ABAD1C + 0x10)
                            || (overlay >= 0x4A && overlay <= 0x65))
                            special = true;
                    }
                }
                CellStruct cell = vf_110();
                if (special)
                    DAT_0087F7E8.FUN_00574C20(&cell);
                else
                    DAT_0087F7E8.FUN_00574000(&cell);
                C4Applied = false;
                C4AppliedBy = 0;
            } else {
                int damage = Health;
                vf_91(&damage, 0, RulesInstance->C4Warhead, C4AppliedBy, true, false, 0);
            }
            if (!IsAlive)
                return;
            vf_73(2);
        }
    }

    if (Target == 0)
        return;
    if (IsCloseEnoughToAttack((AbstractClass*)Target))
        return;
    if (((AbstractClass*)Target)->vf_11() == 2 && !((AbstractClass*)Target)->IsOnFloor())
        return;
    vf_242(0);
}
