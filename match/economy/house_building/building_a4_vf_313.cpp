// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 313 at 0x43DA80 (0xD22 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode; Ghidra's decompile of this body is unusable because it
//   loses the outgoing stack arguments). It draws the building: it first lets the objects tracked by the
//   building draw themselves, packs the two house colours for the display's pixel format, picks the frame of
//   the construction/sell animation, then draws the body voxel (and a turret voxel) through slot 273 with a
//   rotation matrix built from the two facings. The original name is not confirmed here.

#include "building_a4_views.h"

// The colour of one house-colour table entry in the display's pixel format: the format code selects which of
// three packings are added (the format 2 packing is added on top of the format 1 one, which sits on top of
// the base one).
inline unsigned BA4PackColor(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned value = 0;
    switch (FUN_004BBC90()) {
    case 2:
        value |= (((((unsigned short)r) << 6) | (unsigned short)g) << 5) | (unsigned short)b;
    case 1:
        value |= (((((unsigned short)(g >> 1)) | (((unsigned short)r) << 5)) << 6) | (unsigned short)b);
    }
    value |= (((((unsigned short)(g >> 1)) | (((unsigned short)r) << 5)) << 5) | (unsigned short)b);
    return value;
}

// FUNCTION: GAMEMD 0x43DA80
void BA4Building::vf_313(HBPoint2D* pos, int clip)
{
    HBCell scratch;
    HBCell here = *vf_110(&scratch);
    int i;

    if (vf_97() == 0x10) {
        if (unknown_350.FUN_004A5110() || unknown_350.FUN_004A51B0() || unknown_350.FUN_004A51D0() || unknown_350.FUN_004A5130()) {
            if (unknown_418) {
                for (i = 0; i < unknown_E8; i++) {
                    BA4Object* object = FUN_0065AD40(i);
                    if (object && !object->unknown_81 && object->vf_11() != 6) {
                        HBCoordPod scratchA;
                        HBCoordPod a = *object->vf_19(&scratchA, 0);
                        a.Z = object->Location.Z;
                        if (DAT_00B73550 && !DAT_00A8ED6B && (DAT_00A8B230->unknown_00 & 0x1000)) {
                            HBCoordPod q = object->Location;
                            if (DAT_0087F7E8.FUN_005865E0(&q)) {
                                continue;
                            }
                            if (DAT_0087F7E8.FUN_005865E0(&a)) {
                                continue;
                            }
                        }
                        HBCoordPod scratchB;
                        HBCoordPod screen = DAT_00887324->FUN_006D2140(*object->vf_43(&scratchB));
                        object->vf_69(&screen, clip);
                    }
                }
            }
        }
    }

    unsigned color = 0;
    if (unknown_294) {
        BA4Rgb* c = &DAT_008871E0->unknown_1874[DAT_008871E0->unknown_18A4];
        color |= BA4PackColor(c->R, c->G, c->B);
    }
    if (vf_88() && unknown_1C4 == 1) {
        BA4Rgb* c = &DAT_008871E0->unknown_1874[DAT_008871E0->unknown_18B0];
        color |= BA4PackColor(c->R, c->G, c->B);
    }

    HBCoordPod scratchLoc;
    HBCoordPod* loc = vf_18(&scratchLoc);
    HBCell cell(loc->X / 256, loc->Y / 256);
    if (DAT_0087F7E8.FUN_005657A0(cell)->FUN_00487950()) {
        color = 0;
    }

    if (vf_97() == 0x10 && Type->unknown_150C) {
        if (unknown_350.FUN_004A51D0() || unknown_350.FUN_004A5110() || unknown_350.FUN_004A5130() || unknown_350.FUN_004A51B0()) {
            int frame = (int)(unknown_350.FUN_004A52F0() * Type->unknown_F00);
            if (unknown_350.FUN_004A5130()) {
                frame = Type->unknown_F00 - frame;
            }
            if (unknown_350.FUN_004A51D0()) {
                frame = 0;
            }
            if (frame >= Type->unknown_F00) {
                frame = Type->unknown_F00 - 1;
            }
            if (frame < 0) {
                frame = 0;
            }
            if (FUN_005F5C60() <= DAT_008871E0->unknown_1700 && Type->unknown_1700) {
                frame += Type->unknown_F00;
            }
            int sortKey = -5 - FUN_006D20E0(vf_116());
            FUN_00705E00(Type->unknown_150C, frame, pos, clip, 0, 0x100, sortKey, 0, 0,
                         DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, 0, 0, 0, 0, 0, 0);
            if (unknown_350.FUN_004A5130() && frame == 0) {
                unknown_80 = 1;
            }
        }
    }

    if (Type->unknown_16C5) {
        bool inSale = false;
        if (unknown_AC == 0x12 || unknown_B4 == 0x12) {
            if (unknown_F8 < Type->unknown_F08 + Type->unknown_F04 - 1) {
                inSale = true;
            }
        }
        if (((unknown_AC != 0x13 || unknown_F8 < 1) && !inSale) || Type->unknown_16CA) {
            int tint;
            int shadowTint;
            if (DAT_00887418) {
                tint = ((Facing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                shadowTint = ((Facing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
            } else {
                tint = -1;
                shadowTint = -1;
            }
            int phaseA = 0;
            int phaseB = 0;
            if (Type->unknown_B8v.unknown_04) {
                phaseA = unknown_148 % Type->unknown_B8v.unknown_04->unknown_08;
            }
            if (Type->unknown_C0.unknown_04) {
                phaseB = unknown_148 % Type->unknown_C0.unknown_04->unknown_08;
            }
            tint |= (phaseA & 0xFF) << 16;
            shadowTint |= (phaseB & 0xFF) << 16;

            BA4Matrix matrix;
            if (Type->unknown_B8v.unknown_00) {
                int dirA = ((Facing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.FUN_005AF1A0((float)(dirA - 8) * (-0.19634954084936207));
                matrix.FUN_005AE980((float)(Type->unknown_720 / 8));
                float vx = matrix.M[3];
                float vy = matrix.M[7];
                float vz = matrix.M[11];
                float negative[3];
                negative[0] = -vx;
                negative[1] = -vy;
                negative[2] = -vz;
                float positive[3];
                positive[0] = vx;
                positive[1] = vy;
                positive[2] = vz;
                BA4Matrix second = matrix;
                second.FUN_005AE8F0(negative);
                if (unknown_3F0) {
                    matrix.FUN_005AE980(-unknown_3EC);
                    tint = -1;
                }
                if (unknown_410) {
                    second.FUN_005AE980(-unknown_40C);
                    tint = -1;
                }
                int dirB = ((unknown_370.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                second.FUN_005AF080(-((float)(dirB - 8) * (-0.19634954084936207)));
                second.FUN_005AE8F0(positive);
                HBPoint2D at;
                at.X = pos->X + Type->unknown_F4C[9].unknown_30.X;
                at.Y = pos->Y + Type->unknown_F4C[9].unknown_30.Y;
                bool tail = false;
                if (((Facing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) > 0
                    && ((Facing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) < 3) {
                    tail = true;
                } else if (Type->unknown_C0.unknown_00 && Type->unknown_C0.unknown_04) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->unknown_C0, 0, tint, &Type->unknown_244[3], clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, color, 0);
                }
                {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->unknown_B8v, 0, tint, &Type->unknown_244[2], clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                           DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, color, 0);
                }
                if (tail && Type->unknown_C0.unknown_00 && Type->unknown_C0.unknown_04) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->unknown_C0, 0, tint, &Type->unknown_244[3], clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, color, 0);
                }
            } else if (Type->unknown_C0.unknown_00 && Type->unknown_C0.unknown_04) {
                float vx = matrix.M[3];
                float vy = matrix.M[7];
                float vz = matrix.M[11];
                float negative[3];
                negative[0] = -vx;
                negative[1] = -vy;
                negative[2] = -vz;
                float positive[3];
                positive[0] = vx;
                positive[1] = vy;
                positive[2] = vz;
                matrix.FUN_005AE8F0(negative);
                int dirA = ((Facing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.FUN_005AF1A0((float)(dirA - 8) * (-0.19634954084936207));
                int dirB = ((unknown_370.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.FUN_005AF080(-((float)(dirB - 8) * (-0.19634954084936207)));
                matrix.FUN_005AE8F0(positive);
                HBPoint2D at;
                at.X = pos->X + Type->unknown_F4C[9].unknown_30.X;
                at.Y = pos->Y + Type->unknown_F4C[9].unknown_30.Y;
                BA4MatrixTemp product;
                BA4MatrixTemp defaults;
                vf_273(&Type->unknown_C0, 0, shadowTint, &Type->unknown_244[3], clip, &at,
                       FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                       DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, color, 0);
            }
        }
    } else if (Type->unknown_16C6) {
        bool inSale = false;
        if (unknown_AC == 0x12 || unknown_B4 == 0x12) {
            if (unknown_F8 < Type->unknown_F08 + Type->unknown_F04 - 1) {
                inSale = true;
            }
        }
        if (!(unknown_AC == 0x13 && unknown_F8 > 0) && !inSale) {
            BA4MatrixTemp scratchMatrix;
            BA4MatrixTemp matrix = *FUN_00458810(&scratchMatrix);
            int angle = ((((Facing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F) + DAT_00818CB0) % 32;
            bool visible = angle <= 0x10;
            BA4Object* child = Anims[9];
            if (visible && child) {
                if (DAT_00818CB4) {
                    child->unknown_19D = 0;
                }
                child->vf_65(DAT_00886FA0, 1, 0);
                child->unknown_19D = 1;
            }
            HBPoint2D at;
            at.X = pos->X + Type->unknown_F4C[9].unknown_30.X;
            at.Y = pos->Y + Type->unknown_F4C[9].unknown_30.Y;
            BA4MatrixTemp product;
            BA4MatrixTemp defaults;
            vf_273(&Type->unknown_244[1], 0, -1, &Type->unknown_244[0], clip, &at,
                   FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                   DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, color, 0);
            if (!visible && child) {
                if (DAT_00818CB4) {
                    child->unknown_19D = 0;
                }
                child->vf_65(DAT_00886FA0, 1, 0);
                child->unknown_19D = 1;
            }
        }
    }
}
