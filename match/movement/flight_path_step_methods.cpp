// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Op
//
// /Op (improve float consistency) is a claim about the retail build, so it has
// to justify itself. Without it cl keeps double-typed intermediates in the x87
// register stack; retail rounds each one through a memory temporary at every
// assignment boundary, which is exactly what /Op does and nothing else in the
// flag space reproduces. Measured on this body: under the locked set the two
// instruction streams differ by 54 retail-only MOVs (643 against 594
// instructions); with /Op added the difference falls to 11 and the counts to
// 643 against 644. That is the flag, not a phrasing.
#include "flight_path_step_methods.h"

// FUNCTION: GAMEMD 0x005B20F0
// One frame of guided flight. `coord` is advanced by `velocity`, and the
// velocity is re-aimed: with no target (the coordinate compares equal to the
// engine's unset-coordinate global) it simply eases its pitch toward the
// 0x2000 climb angle; with a target it turns toward the target's bearing and
// then chooses a pitch from the terrain height ahead of it. The return value
// is the distance still to travel.
//
// PARTIAL -- 9.2% on the offset-aligned oracle, 81.1% of retail's 640
// instructions in mnemonic sequence, 644 compiled instructions against 643.
// The model is right: the whole control-flow graph lines up block for block,
// both branches of the unset-coordinate test, all four inlined step-toward
// expansions, both out-of-line ones, the terrain probe, the three pitch arms
// and both epilogues. What is left is not a modelling error.
//
// The residual, exactly:
//
//   * Six int-to-double conversions of the form `FILD n; FMUL k` come out of
//     cl 12.00.8804 as `FILD n; FSTP tmp; FLD tmp; FMUL k` under /Op. Four of
//     the six have no counterpart in retail, which is 8 extra instructions.
//     /Op is required (see the flag note above) and rounds the conversion
//     through memory; retail's 12.00.8447 backend does not. The first of them
//     lands at compiled offset 0xF8, early enough that the offset-aligned
//     oracle scores everything after it as a miss -- which is why the
//     percentage reads far worse than the body is.
//   * Eleven retail-only MOVs and one retail-only FST, spread over the two
//     copy-and-convert blocks that turn the velocity into an integer offset
//     and the target delta into a VelocityClass. Retail keeps the third
//     component in ST(0) across the two __ftol calls (FST, not FSTP) where cl
//     rounds it through a stack temporary as well.
//   * `coord` and `velocity` are exchanged between EBX and ESI throughout,
//     and the frame is 0x8C in retail against 0x84 here -- one double slot,
//     the temporary the FILD round trip above needs.
//   * One retail JMP against an extra epilogue here: retail folds the
//     isMissile arm's return into the shared tail, cl emits its own.
//
// Spellings measured on the conversion block: the three components as int
// locals (26 retail-only MOVs), as three double locals then three int locals
// (11, the form kept), as two double locals with the third converted in place
// (17), as a whole VelocityClass copy (cl emits REP MOVSD where retail emits
// four MOVs, so the object is not being copied whole). Flag sweeps on top of
// /Op: /G3, /G4, /G5, /Ob2 identical; /G6 worse (20); /Os far worse; /Oi- no
// change; /Ox identical to /O2. Operand order reversed on the radian
// multiplies: no change.
//
// Next verification step: rebuild the same body under a 12.00.8447 cl (an
// outstanding toolchain follow-up), and re-measure. If the FILD round trip is the backend difference
// it looks like, that alone realigns the stream and the remaining work is the
// two copy blocks.
int __fastcall FlightPathStep(CoordStruct* coord, VelocityClass* velocity,
                              CoordStruct const* target, Dir16 const* turnRate,
                              char holdCourse, char isMissile, char isFast,
                              char freezePitch)
{
    if (target->X == GG_UnsetCoord.X && target->Y == GG_UnsetCoord.Y &&
        target->Z == GG_UnsetCoord.Z) {
        Dir16 pitch;
        Dir16 climb;
        double currentRadians;
        double speed;

        pitch = velocity->PitchFromComponents();
        climb.Raw = 0x2000;
        if (pitch.IsWithin(climb, *turnRate)) {
            pitch.Raw = climb.Raw;
        } else if (climb.Sub(pitch).Raw < 0) {
            pitch.Raw -= turnRate->Raw;
        } else {
            pitch.Raw += turnRate->Raw;
        }

        currentRadians = (velocity->GetPitch().Raw - 0x3FFF) * GG_DIR16_TO_RADIANS;
        speed = velocity->Length();
        if (currentRadians != GG_ZERO) {
            velocity->X /= gamemd_cos(currentRadians);
            velocity->Y /= gamemd_cos(currentRadians);
        }
        velocity->X *= gamemd_cos((pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS);
        velocity->Y *= gamemd_cos((pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS);
        velocity->Z = gamemd_sin((pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * speed;

        {
            double travelX = velocity->X;
            double travelY = velocity->Y;
            double travelZ = velocity->Z;
            int movedX = (int)travelX;
            int movedY = (int)travelY;
            int movedZ = (int)travelZ;

            *coord = CoordStruct(coord->X + movedX, coord->Y + movedY,
                                 coord->Z + movedZ);
        }
        return (int)gamemd_sqrt(velocity->Y * velocity->Y +
                                velocity->X * velocity->X +
                                velocity->Z * velocity->Z);
    }

    {
        Dir16 pitch;
        Dir16 heading;
        Dir16 bearing;
        int range;
        int flatRange;
        double flat;

        {
            double travelX = velocity->X;
            double travelY = velocity->Y;
            double travelZ = velocity->Z;
            int movedX = (int)travelX;
            int movedY = (int)travelY;
            int movedZ = (int)travelZ;

            *coord = CoordStruct(coord->X + movedX, coord->Y + movedY,
                                 coord->Z + movedZ);
        }

        range = (*coord - *target).Length();

        flatRange = (Point2D(coord->X, coord->Y) -
                     Point2D(target->X, target->Y)).Length();

        CoordStruct offset(target->X - coord->X,
                           target->Y - coord->Y,
                           target->Z - coord->Z);
        VelocityClass toTarget;
        VelocityClass aim;

        toTarget = VelocityClass((double)offset.X, (double)offset.Y, (double)offset.Z);
        aim = toTarget;

        heading.Raw = (short)(long)((gamemd_atan2(-velocity->Y, velocity->X) -
                                     GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
        bearing.Raw = (short)(long)((gamemd_atan2(-aim.Y, aim.X) -
                                     GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
        if (heading.IsWithin(bearing, *turnRate)) {
            heading.Raw = bearing.Raw;
        } else if (bearing.Sub(heading).Raw < 0) {
            heading.Raw -= turnRate->Raw;
        } else {
            heading.Raw += turnRate->Raw;
        }

        velocity->ClearDegenerate();
        flat = velocity->FlatSpeed();
        velocity->X = gamemd_cos((heading.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * flat;
        velocity->Y = -(gamemd_sin((heading.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * flat);

        pitch = velocity->PitchFromComponents();

        if (holdCourse == 0 &&
            (isMissile != 0 || flatRange > (((isFast != 0) ? 3 : 0) + 3) * 0x100) &&
            ((((unsigned short)turnRate->Raw >> 7) + 1 >> 1) & 0xFF) > 1) {
            CoordStruct lead((int)velocity->X * 6, (int)velocity->Y * 6,
                             (int)velocity->Z * 6);
            CoordStruct ahead(coord->X + lead.X, coord->Y + lead.Y, coord->Z + lead.Z);
            CoordStruct probe = ahead;
            int floorZ;
            CellClass* cell;
            int steps;
            int drop;
            int here;

            floorZ = MapClass_Instance.GetZPos(&probe);
            cell = MapClass_Instance.GetTargetCell(&probe);
            if ((cell->Flags & 0x100) != 0) {
                floorZ += GG_BridgeRise;
            }

            steps = range / 256;
            if (isMissile == 0 && isFast == 0) {
                if (steps >= 5) {
                    steps = 5;
                }
            } else {
                steps = 10;
            }

            if (freezePitch == 0) {
                here = coord->Z;
                drop = here - steps * GG_LevelHeight - floorZ;
                if (drop < -0x14) {
                    coord->Z = here + 0x12;
                } else if (drop > 0x14) {
                    coord->Z = here - 0x12;
                }

                if (drop < -(GG_LevelHeight / 2)) {
                    Dir16 up;
                    Dir16 half;

                    up.Raw = 0x2000;
                    half.Raw = (short)(turnRate->Raw / 2);
                    if (pitch.IsWithin(up, half)) {
                        pitch.Raw = up.Raw;
                    } else if (up.Sub(pitch).Raw < 0) {
                        pitch.Raw -= half.Raw;
                    } else {
                        pitch.Raw += half.Raw;
                    }
                } else if (drop > GG_LevelHeight / 2) {
                    Dir16 down;
                    Dir16 half;

                    down.Raw = 0x4800;
                    half.Raw = (short)(turnRate->Raw / 2);
                    if (pitch.IsWithin(down, half)) {
                        pitch.Raw = down.Raw;
                    } else if (down.Sub(pitch).Raw < 0) {
                        pitch.Raw -= half.Raw;
                    } else {
                        pitch.Raw += half.Raw;
                    }
                } else {
                    Dir16 level;
                    Dir16 half;

                    level.Raw = 0x4000;
                    half.Raw = (short)(turnRate->Raw / 2);
                    pitch.StepToward(level, half);
                }
            }
        } else if (freezePitch == 0) {
            pitch.StepToward(aim.GetPitch(), turnRate->Add(Dir16Raw(0x100)).Div(2));
        }

        velocity->SetPitch(pitch);

        if (isMissile != 0) {
            offset.Z = 0;
        } else {
            offset.Z = offset.Z / 4;
        }
        return offset.Length();
    }
}
