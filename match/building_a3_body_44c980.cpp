// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 148 (+0x250): the per-frame mission body of the missile launching super weapon
//   buildings (two variants selected by flags of the building type: a warning-animation launch and a pulse ball
//   launch that fires a missile object with a computed velocity), returning the delay until its next call.
//   Span 0x44C980..0x44D5C8 (0xC48 bytes: code to 0x44D5A1 and two jump tables, 5 and 4 entries). The method names
//   are slot labels / FUN_<addr>; no original name is confirmed.
// CAPPED (final) at 12.3% positional on the 0xC21-byte code span (110/895; the two jump tables are not scored), 50.7% by sequence
// alignment; all 93 calls are in retail order. Delta: the frame is 0xC0 against 0xD8 and the trigonometric block keeps the
// velocity doubles in other stack slots; zero-register / TEST differences as elsewhere. The launch velocity is computed from the
// instruction stream: spherical unit vector at a quarter turn (case 1), direction to the target flattened and scaled to the missile speed,
// ballistic elevation from FUN_0048A8D0 (twice, the second at speed*10/8, fallback 0xFA00).
// Variants tried: the quarter-turn constants folded against evaluated, velocity as three locals against an array, the elevation
// tilt written with the retail operand order.
// The coordinate argument passed to slot 44 is zeroed here; retail passes a stack value it never writes (indeterminate).

#include "building_a3_views.h"
#include "weapon_type_class.h"
#include "shared_constants_globals.h"

// A direction step as radians: the retail code subtracts the 0x3FFF quarter turn offset from the 16-bit direction.
inline double BA3DirToRadians(int dir)
{
    return (double)((short)dir - 0x3FFF) * DAT_007E2810;
}

// FUNCTION: GAMEMD 0x44C980
int BuildingClass::vf_148()
{
    CoordStruct zero;
    zero.X = 0;
    zero.Y = 0;
    zero.Z = 0;
    CoordStruct at;

    if (Type->NukeSilo) {
        switch (MissionStatus) {
        case 0: {
            IsReadyToCommence = 0;
            FUN_00447780(2);
            MissionStatus = 1;
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&Owner->NukeTarget);
            HouseClass* owner = Owner;
            const AnimTypeClass* warning = DAT_008B4154[FUN_00427CB0(s_PSIWARN_0081907C)];
            CoordStruct where = cell->vf_18();
            BA3AnimMem* mem = new BA3AnimMem;
            AnimClass* anim;
            if (mem) {
                anim = mem->FUN_00421EA0(warning, &where, 0, 1, 0x600, 0, 0);
            } else {
                anim = 0;
            }
            anim->FUN_00424C90(0);
            anim->FUN_00424CA0(owner);
            anim->Invisible = 1;
            PsiWarnAnim = anim;
        }
        case 1:
            if (IsReadyToCommence) {
                FUN_00447780(4);
                MissionStatus = 2;
            }
        case 2: {
            CoordStruct tmp;
            vf_18();
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&Owner->NukeTarget);
            WeaponTypeClass* info = DAT_00A8E334[FiringSWType]->unknown_9C;
            BulletClass* missile = FUN_0046B050(info->Projectile, cell, this, info->Damage, info->Warhead, 0xFF, 1);
            if (missile) {
                missile->FUN_0046B260(info);
                if (PsiWarnAnim) {
                    PsiWarnAnim->FUN_00424C90(missile);
                    PsiWarnAnim = 0;
                    missile->vf_53();
                } else {
                    missile->vf_53();
                }
                // The velocity is a unit vector straight up (the retail code evaluates the trig functions of a
                // quarter turn instead of folding them).
                CoordStruct pos = vf_44(0, zero);
                double quarter = 1.5707483884323126;
                double up = FUN_004CACB0(quarter);
                BulletVelocity velocity;
                velocity.X = FUN_004CAD00(quarter) * up * DAT_007E44A8;
                velocity.Y = FUN_004CAD00(quarter) * FUN_004CAD00(quarter) * DAT_007E44A8;
                velocity.Z = FUN_004CACB0(quarter) * DAT_007E44A8;
                if (!missile->vf_124(pos, velocity)) {
                    delete missile;
                    MissionStatus = 3;
                    return 1;
                }
                BA3AnimMem* mem = new BA3AnimMem;
                AnimClass* anim;
                if (mem) {
                    CoordStruct where = pos;
                    anim = mem->FUN_00421EA0(RulesInstance->unknown_98, &where, 0, 1, 0x600, 0, 0);
                } else {
                    anim = 0;
                }
                anim->ZAdjust = -100;
                MissionStatus = 3;
            }
            return 1;
        }
        case 3:
            FUN_00447780(5);
            MissionStatus = 4;
            return 6;
        case 4:
            goto finishStep;
        }
    }

    if (FiringSWType != -1) {
        vf_243(DAT_0087F7E8.FUN_005657A0(&Owner->NukeTarget), 0);
        vf_122(5, 0);
    }

    if (Type->EMPulseCannon) {
        switch (MissionStatus) {
        case 0: {
            DirStruct dirA = vf_314(DAT_0087F7E8.FUN_005657A0(&Owner->EMPTarget));
            DirStruct dirB = vf_178(DAT_0087F7E8.FUN_005657A0(&Owner->EMPTarget));
            if (abs(0) < abs((short)(PrimaryFacing.FUN_004C93D0().Raw - dirA.Raw))) {
                PrimaryFacing.FUN_004C9220(dirA);
                return 1;
            }
            if (abs(0) < abs((short)(BarrelFacing.FUN_004C93D0().Raw - dirB.Raw))) {
                BarrelFacing.FUN_004C9220(dirB);
                return 1;
            }
            MissionStatus = 1;
            return 1;
        }
        case 1: {
            BA3AnimMem* mem = new BA3AnimMem;
            if (mem) {
                const AnimTypeClass** entry = &DAT_008B4154[FUN_00422B20(s_PULSBALL_00819070)];
                mem->FUN_00421EA0(*entry, vf_44(0, zero), 0, 1, 0x600, 0, 0);
            }
            MissionStatus = 2;
            return 0x20;
        }
        case 3: {
            DirStruct up;
            up.Raw = 0x4000;
            BarrelFacing.FUN_004C9220(up);
            goto finishStep;
        }
        case 2: {
            WeaponTypeClass* weapon = vf_254(0)->WeaponType;
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&Owner->EMPTarget);
            CellClass* targetCell = DAT_0087F7E8.FUN_005657A0(&Owner->EMPTarget);
            if (DAT_00A8ED6B || (Owner->EMPTarget.X == DAT_0089C818.X && Owner->EMPTarget.Y == DAT_0089C818.Y)) {
                FUN_00447780(1);
                vf_122(5, 0);
                return 0x3C;
            }
            BarrelFacing.FUN_004C9220(vf_178(cell));
            CoordStruct muzzle = vf_44(0, zero);
            CoordStruct aim;
            aim.X = Owner->EMPTarget.X * 256 + 0x80;
            aim.Y = Owner->EMPTarget.Y * 256 + 0x80;
            aim.Z = 0;
            DAT_0087F7E8.FUN_00578080(aim);
            int tx = Owner->EMPTarget.X * 256 + 0x80;
            int ty = Owner->EMPTarget.Y * 256 + 0x80;
            int yaw = (short)(int)((FUN_004CAE30((double)muzzle.Y - ty, (double)tx - muzzle.X) - GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
            int speed = BA3ProbeOf(FUN_005F6360(cell))->FUN_0048AB90((double)RulesInstance->unknown_16B8);
            BulletClass* missile = FUN_0046B050(weapon->Projectile, cell, this, weapon->Damage, weapon->Warhead,
                                                   speed * 3 / 4, weapon->Bright);

            // The direction of the launch as a vector of the length of the speed, flattened to the horizontal plane.
            BulletVelocity velocity;
            velocity.X = 100.0;
            velocity.Y = 0.0;
            velocity.Z = 0.0;
            double radius = FUN_004CAC40(10000.0);
            double radians = BA3DirToRadians(yaw);
            velocity.X = FUN_004CAD00(radians) * radius;
            velocity.Y = -(FUN_004CACB0(radians) * radius);
            if (velocity.X == 0.0 && velocity.Y == 0.0 && velocity.Z == 0.0) {
                velocity.X = 100.0;
            }
            double scale = (double)speed / FUN_004CAC40(velocity.X * velocity.X + velocity.Z * velocity.Z + velocity.Y * velocity.Y);
            velocity.X *= scale;
            velocity.Y *= scale;
            velocity.Z *= scale;

            // Ask for a firing solution against the target position, then tilt the velocity by the elevation.
            CoordStruct from = vf_192(0);
            CoordStruct to = targetCell->vf_18();
            CoordStruct diff;
            diff.X = to.X - from.X;
            diff.Y = to.Y - from.Y;
            diff.Z = to.Z - from.Z;
            int flat2 = diff.Y * diff.Y + diff.X * diff.X;
            DirStruct solution;
            bool found = FUN_0048A8D0(FUN_0070D590(0), speed, (int)FUN_004CAC40((double)flat2), diff.Z,
                                      (double)RulesInstance->unknown_16B8, &solution);
            if (!found) {
                found = FUN_0048A8D0(FUN_0070D590(0), speed * 10 / 8, (int)FUN_004CAC40((double)flat2), diff.Z,
                                     (double)RulesInstance->unknown_16B8, &solution);
                if (!found) {
                    solution.Raw = (short)0xFA00;
                    found = true;
                }
            }
            double horizontal = FUN_004CAC40(velocity.Y * velocity.Y + velocity.X * velocity.X);
            double pitch = BA3DirToRadians((short)(int)((FUN_004CAE30(velocity.Z, horizontal) - GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16));
            double length = FUN_004CAC40(velocity.Z * velocity.Z + velocity.Y * velocity.Y + velocity.X * velocity.X);
            if (pitch != 0.0) {
                velocity.X = velocity.X / FUN_004CAD00(pitch);
                velocity.Y = velocity.Y / FUN_004CAD00(pitch);
            }
            double elevation = BA3DirToRadians(solution.Raw);
            velocity.X = FUN_004CAD00(elevation) * velocity.X;
            velocity.Y = FUN_004CAD00(elevation) * velocity.Y;
            velocity.Z = FUN_004CACB0(elevation) * length;

            if (found && missile->vf_124(muzzle, velocity)) {
                if (vf_255() && vf_33()->TurretRecoil) {
                    TurretRecoil.Fire();
                    BarrelRecoil.Fire();
                }
                if (!vf_33()->IsGattling) {
                    HBCounterView& rand = DAT_00886B88;
                    int sound = weapon->Reports.Items[rand.FUN_0065C780() % weapon->Reports.GetCount()];
                    FUN_007509E0(sound, vf_44(0, zero), 0);
                }
                MissionStatus = 3;
                return 1;
            }
            missile->Release();
            goto finishStep;
        }
        default:
            break;
        }
    }

    return (int)(FUN_005B3A00()->Rate * DAT_007E27F8);

finishStep:
    FUN_00447780(1);
    vf_122(5, 0);
    return 0x3C;
}
