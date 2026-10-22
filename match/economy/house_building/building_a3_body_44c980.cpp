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

// A direction step as radians: the retail code subtracts the 0x3FFF quarter turn offset from the 16-bit direction.
inline double BA3DirToRadians(int dir)
{
    return (double)((short)dir - 0x3FFF) * DAT_007E2810;
}

// FUNCTION: GAMEMD 0x44C980
int BuildingA3View::vf_148()
{
    HBCoord zero;
    zero.X = 0;
    zero.Y = 0;
    zero.Z = 0;
    HBCoord at;

    if (Type->unknown_16BA) {
        switch (Status) {
        case 0: {
            unknown_6DD = 0;
            FUN_00447780(2);
            Status = 1;
            BA3ObjView* cell = DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5784);
            BA3HouseView* owner = Owner;
            const BA3AnimTypeView* warning = DAT_008B4154[FUN_00427CB0(s_PSIWARN_0081907C)];
            HBCoord where = cell->vf_18();
            BA3AnimMem* mem = new BA3AnimMem;
            BA3AnimView* anim;
            if (mem) {
                anim = mem->FUN_00421EA0(warning, &where, 0, 1, 0x600, 0, 0);
            } else {
                anim = 0;
            }
            anim->FUN_00424C90(0);
            anim->FUN_00424CA0(owner);
            anim->unknown_19D = 1;
            unknown_54C = anim;
        }
        case 1:
            if (unknown_6DD) {
                FUN_00447780(4);
                Status = 2;
            }
        case 2: {
            HBCoord tmp;
            vf_18();
            BA3ObjView* cell = DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5784);
            BA3LaunchInfoView* info = DAT_00A8E334[unknown_5F8]->unknown_9C;
            BA3MissileView* missile = FUN_0046B050(info->unknown_A0, cell, this, info->unknown_A4, info->unknown_AC, 0xFF, 1);
            if (missile) {
                missile->FUN_0046B260(info);
                if (unknown_54C) {
                    unknown_54C->FUN_00424C90(missile);
                    unknown_54C = 0;
                }
                missile->vf_53();
                // The velocity is a unit vector straight up (the retail code evaluates the trig functions of a
                // quarter turn instead of folding them).
                HBCoord pos = vf_44(0, zero);
                double quarter = 1.5707963267948966;
                double up = FUN_004CACB0(quarter);
                double velocity[3];
                velocity[0] = FUN_004CAD00(quarter) * up * DAT_007E44A8;
                velocity[1] = FUN_004CAD00(quarter) * FUN_004CAD00(quarter) * DAT_007E44A8;
                velocity[2] = FUN_004CACB0(quarter) * DAT_007E44A8;
                if (!missile->vf_124(&pos, velocity)) {
                    missile->vf_8(1);
                    Status = 3;
                    return 1;
                }
                BA3AnimMem* mem = new BA3AnimMem;
                BA3AnimView* anim;
                if (mem) {
                    HBCoord where = pos;
                    anim = mem->FUN_00421EA0(RulesInstance->unknown_98, &where, 0, 1, 0x600, 0, 0);
                } else {
                    anim = 0;
                }
                anim->unknown_100 = -100;
                Status = 3;
            }
            return 1;
        }
        case 3:
            FUN_00447780(5);
            Status = 4;
            return 6;
        case 4:
            goto finishStep;
        }
    }

    if (unknown_5F8 != -1) {
        vf_243(DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5784), 0);
        vf_122(5, 0);
    }

    if (Type->unknown_16C3) {
        switch (Status) {
        case 0: {
            HBDir dirA = vf_314(DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5780));
            HBDir dirB = vf_178(DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5780));
            if (abs(0) < abs((short)(Facing388.FUN_004C93D0().Raw - dirA.Raw))) {
                Facing388.FUN_004C9220(&dirA);
                return 1;
            }
            if (abs(0) < abs((short)(Facing370.FUN_004C93D0().Raw - dirB.Raw))) {
                Facing370.FUN_004C9220(&dirB);
                return 1;
            }
            Status = 1;
            return 1;
        }
        case 1: {
            BA3AnimMem* mem = new BA3AnimMem;
            if (mem) {
                const BA3AnimTypeView** entry = &DAT_008B4154[FUN_00422B20(s_PULSBALL_00819070)];
                mem->FUN_00421EA0(*entry, &vf_44(0, zero), 0, 1, 0x600, 0, 0);
            }
            Status = 2;
            return 0x20;
        }
        case 3: {
            HBDir up;
            up.Raw = 0x4000;
            Facing370.FUN_004C9220(&up);
            goto finishStep;
        }
        case 2: {
            BA3WeaponTypeView* weapon = vf_254(0)->First;
            BA3ObjView* cell = DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5780);
            BA3ObjView* targetCell = DAT_0087F7E8.FUN_005657A0(&Owner->unknown_5780);
            if (DAT_00A8ED6B || (Owner->unknown_5780.X == DAT_0089C818.X && Owner->unknown_5780.Y == DAT_0089C818.Y)) {
                FUN_00447780(1);
                vf_122(5, 0);
                return 0x3C;
            }
            Facing370.FUN_004C9220(&vf_178(cell));
            HBCoord muzzle = vf_44(0, zero);
            HBCoord aim;
            aim.X = Owner->unknown_5780.X * 256 + 0x80;
            aim.Y = Owner->unknown_5780.Y * 256 + 0x80;
            aim.Z = 0;
            DAT_0087F7E8.FUN_00578080(aim);
            int tx = Owner->unknown_5780.X * 256 + 0x80;
            int ty = Owner->unknown_5780.Y * 256 + 0x80;
            int yaw = (short)(int)((FUN_004CAE30((double)muzzle.Y - ty, (double)tx - muzzle.X) - DAT_007E2820) * DAT_007E2818);
            int speed = FUN_005F6360(cell)->FUN_0048AB90((double)RulesInstance->unknown_16B8);
            BA3MissileView* missile = FUN_0046B050(weapon->unknown_A0, cell, this, weapon->unknown_A4, weapon->unknown_AC,
                                                   speed * 3 / 4, weapon->unknown_12F);

            // The direction of the launch as a vector of the length of the speed, flattened to the horizontal plane.
            double velocity[3];
            velocity[0] = 100.0;
            velocity[1] = 0.0;
            velocity[2] = 0.0;
            double radius = FUN_004CAC40(10000.0);
            double radians = BA3DirToRadians(yaw);
            velocity[0] = FUN_004CAD00(radians) * radius;
            velocity[1] = -(FUN_004CACB0(radians) * radius);
            if (velocity[0] == 0.0 && velocity[1] == 0.0 && velocity[2] == 0.0) {
                velocity[0] = 100.0;
            }
            double scale = (double)speed / FUN_004CAC40(velocity[0] * velocity[0] + velocity[2] * velocity[2] + velocity[1] * velocity[1]);
            velocity[0] *= scale;
            velocity[1] *= scale;
            velocity[2] *= scale;

            // Ask for a firing solution against the target position, then tilt the velocity by the elevation.
            HBCoord from = vf_192(0);
            HBCoord to = targetCell->vf_18();
            HBCoord diff;
            diff.X = to.X - from.X;
            diff.Y = to.Y - from.Y;
            diff.Z = to.Z - from.Z;
            int flat2 = diff.Y * diff.Y + diff.X * diff.X;
            HBDir solution;
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
            double horizontal = FUN_004CAC40(velocity[1] * velocity[1] + velocity[0] * velocity[0]);
            double pitch = BA3DirToRadians((short)(int)((FUN_004CAE30(velocity[2], horizontal) - DAT_007E2820) * DAT_007E2818));
            double length = FUN_004CAC40(velocity[2] * velocity[2] + velocity[1] * velocity[1] + velocity[0] * velocity[0]);
            if (pitch != 0.0) {
                velocity[0] = velocity[0] / FUN_004CAD00(pitch);
                velocity[1] = velocity[1] / FUN_004CAD00(pitch);
            }
            double elevation = BA3DirToRadians(solution.Raw);
            velocity[0] = FUN_004CAD00(elevation) * velocity[0];
            velocity[1] = FUN_004CAD00(elevation) * velocity[1];
            velocity[2] = FUN_004CACB0(elevation) * length;

            if (found && missile->vf_124(&muzzle, velocity)) {
                if (vf_255() && vf_33()->unknown_CA2) {
                    unknown_3D8.FUN_0070ECE0();
                    unknown_3F8.FUN_0070ECE0();
                }
                if (!vf_33()->unknown_CD5) {
                    HBCounterView& rand = DAT_00886B88;
                    int sound = weapon->unknown_BC.Items[rand.FUN_0065C780() % weapon->unknown_BC.Count];
                    FUN_007509E0(sound, &vf_44(0, zero), 0);
                }
                Status = 3;
                return 1;
            }
            missile->vf_2();
            goto finishStep;
        }
        default:
            break;
        }
    }

    return (int)(FUN_005B3A00()->unknown_10 * DAT_007E27F8);

finishStep:
    FUN_00447780(1);
    vf_122(5, 0);
    return 0x3C;
}
