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
void BuildingClass::vf_313(Point2D* pos, RectangleStruct* clip)
{
    CellStruct here = vf_110();
    int i;

    if (vf_97() == 0x10) {
        if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A51B0() || UnloadTimer.FUN_004A51D0() || UnloadTimer.FUN_004A5130()) {
            if (IsTether) {
                for (i = 0; i < RadioLinks.Capacity; i++) {
                    ObjectClass* object = FUN_0065AD40(i);
                    if (object && !object->InLimbo && object->vf_11() != 6) {
                        CoordStruct a = object->vf_19(0);
                        a.Z = object->Location.Z;
                        if (DAT_00B73550 && !DAT_00A8ED6B && (DAT_00A8B230->unknown_0000 & 0x1000)) {
                            CoordStruct q = object->Location;
                            if (DAT_0087F7E8.IsLocationFogged(&q)) {
                                continue;
                            }
                            if (DAT_0087F7E8.IsLocationFogged(&a)) {
                                continue;
                            }
                        }
                        Point2D screen = DAT_00887324->FUN_006D2140(object->vf_43());
                        object->vf_69(&screen, clip);
                    }
                }
            }
        }
    }

    unsigned color = 0;
    if (Airstrike) {
        RulesColor_004B9BD0* c = &RulesInstance->ColorAdd[RulesInstance->LaserTargetColor];
        color |= BA4PackColor(c->R, c->G, c->B);
    }
    if (vf_88() && ForceShielded == 1) {
        RulesColor_004B9BD0* c = &RulesInstance->ColorAdd[RulesInstance->ForceShieldColor];
        color |= BA4PackColor(c->R, c->G, c->B);
    }

    CoordStruct loc = vf_18();
    CellStruct cell = BA4Off(loc.X / 256, loc.Y / 256);
    if (BA4At(cell)->FUN_00487950()) {
        color = 0;
    }

    if (vf_97() == 0x10 && Type->DoorAnim) {
        if (UnloadTimer.FUN_004A51D0() || UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
            int frame = (int)(UnloadTimer.FUN_004A52F0() * Type->DoorStages);
            if (UnloadTimer.FUN_004A5130()) {
                frame = Type->DoorStages - frame;
            }
            if (UnloadTimer.FUN_004A51D0()) {
                frame = 0;
            }
            if (frame >= Type->DoorStages) {
                frame = Type->DoorStages - 1;
            }
            if (frame < 0) {
                frame = 0;
            }
            if (FUN_005F5C60() <= RulesInstance->ConditionYellow && Type->bools_1700[0]) {
                frame += Type->DoorStages;
            }
            int sortKey = -5 - FUN_006D20E0(FUN_005F5F30());
            FUN_00705E00(Type->DoorAnim, frame, pos, clip, 0, 0x100, sortKey, 0, 0,
                         BA4At(cell)->Intensity_Normal, 0, 0, 0, 0, 0, 0);
            if (UnloadTimer.FUN_004A5130() && frame == 0) {
                NeedsRedraw = 1;
            }
        }
    }

    if (Type->bools_16A4[33]) {
        bool inSale = false;
        if (CurrentMission == 0x12 || QueuedMission == 0x12) {
            if (StageClass::Value < Type->BuildingAnimFrame[0].Count + Type->BuildingAnimFrame[0].Frame - 1) {
                inSale = true;
            }
        }
        if (((CurrentMission != 0x13 || StageClass::Value < 1) && !inSale) || Type->bools_16A4[38]) {
            int tint;
            int shadowTint;
            if (DAT_00887418) {
                tint = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                shadowTint = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
            } else {
                tint = -1;
                shadowTint = -1;
            }
            int phaseA = 0;
            int phaseB = 0;
            if (Type->TurretVoxel.HVAData) {
                phaseA = TurretAnimFrame % Type->TurretVoxel.HVAData->unknown_08;
            }
            if (Type->BarrelVoxel.HVAData) {
                phaseB = TurretAnimFrame % Type->BarrelVoxel.HVAData->unknown_08;
            }
            tint |= (phaseA & 0xFF) << 16;
            shadowTint |= (phaseB & 0xFF) << 16;

            BA4Matrix matrix;
            if (Type->TurretVoxel.unknown_00) {
                int dirA = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateZ((float)(dirA - 8) * (-0.19634954084936207));
                matrix.TranslateX((float)(Type->TurretOffset / 8));
                float vx = matrix.Row[0][3];
                float vy = matrix.Row[1][3];
                float vz = matrix.Row[2][3];
                Vector3D negative(-vx, -vy, -vz);
                Vector3D positive(vx, vy, vz);
                BA4Matrix second = matrix;
                second.Translate(negative);
                if (TurretRecoil.State) {
                    matrix.TranslateX(-TurretRecoil.TravelSoFar);
                    tint = -1;
                }
                if (BarrelRecoil.State) {
                    second.TranslateX(-BarrelRecoil.TravelSoFar);
                    tint = -1;
                }
                int dirB = ((BarrelFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                second.RotateY(-((float)(dirB - 8) * (-0.19634954084936207)));
                second.Translate(positive);
                Point2D at;
                at.X = pos->X + Type->BuildingAnim[9].X;
                at.Y = pos->Y + Type->BuildingAnim[9].Y;
                bool tail = false;
                if (((PrimaryFacing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) > 0
                    && ((PrimaryFacing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) < 3) {
                    tail = true;
                } else if (Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->BarrelVoxel, 0, tint, &Type->VoxelTurretBarrelCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
                {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->TurretVoxel, 0, tint, &Type->VoxelShadowCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
                if (tail && Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->BarrelVoxel, 0, tint, &Type->VoxelTurretBarrelCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
            } else if (Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                float vx = matrix.Row[0][3];
                float vy = matrix.Row[1][3];
                float vz = matrix.Row[2][3];
                Vector3D negative(-vx, -vy, -vz);
                Vector3D positive(vx, vy, vz);
                matrix.Translate(negative);
                int dirA = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateZ((float)(dirA - 8) * (-0.19634954084936207));
                int dirB = ((BarrelFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateY(-((float)(dirB - 8) * (-0.19634954084936207)));
                matrix.Translate(positive);
                Point2D at;
                at.X = pos->X + Type->BuildingAnim[9].X;
                at.Y = pos->Y + Type->BuildingAnim[9].Y;
                BA4MatrixTemp product;
                BA4MatrixTemp defaults;
                vf_273(&Type->BarrelVoxel, 0, shadowTint, &Type->VoxelTurretBarrelCache, clip, &at,
                       FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                       BA4At(cell)->Intensity_Normal, color, 0);
            }
        }
    } else if (Type->bools_16A4[34]) {
        bool inSale = false;
        if (CurrentMission == 0x12 || QueuedMission == 0x12) {
            if (StageClass::Value < Type->BuildingAnimFrame[0].Count + Type->BuildingAnimFrame[0].Frame - 1) {
                inSale = true;
            }
        }
        if (!(CurrentMission == 0x13 && StageClass::Value > 0) && !inSale) {
            BA4MatrixTemp scratchMatrix;
            BA4MatrixTemp matrix = *FUN_00458810(&scratchMatrix);
            int angle = ((((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F) + DAT_00818CB0) % 32;
            bool visible = angle <= 0x10;
            AnimClass* child = Anims[9];
            if (visible && child) {
                if (DAT_00818CB4) {
                    child->Invisible = 0;
                }
                child->vf_65(&DAT_00886FA0, 1, 0);
                child->Invisible = 1;
            }
            Point2D at;
            at.X = pos->X + Type->BuildingAnim[9].X;
            at.Y = pos->Y + Type->BuildingAnim[9].Y;
            BA4MatrixTemp product;
            BA4MatrixTemp defaults;
            vf_273(&Type->BarrelVoxel, 0, -1, &Type->VoxelMainCache, clip, &at,
                   FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                   BA4At(cell)->Intensity_Normal, color, 0);
            if (!visible && child) {
                if (DAT_00818CB4) {
                    child->Invisible = 0;
                }
                child->vf_65(&DAT_00886FA0, 1, 0);
                child->Invisible = 1;
            }
        }
    }
}
