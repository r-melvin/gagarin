// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 73 at 0x43F180 (0x99C bytes with its 4-entry jump table at 0x43FB0C),
//   read from the retail gamemd.exe v1.001 from its entry to its last RET (linear decode; Ghidra's flow
//   listing drops instructions after some calls). The one argument selects a mode 0..3 through the jump
//   table; modes 1 and 3 share a body. The original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x43F180
bool BuildingClass::vf_73(int mark)
{
    CellStruct cell;
    int zero = 0;
    int x;
    int y;

    if (!TechnoClass::vf_73(mark)) {
        goto refuse;
    }

    cell = vf_110();

    switch (mark) {
    case 0:
        DAT_0087F7E8.FUN_005687F0(&cell, this);
        return true;

    case 1:
    case 3:
        if (Type->ToTile) {
            if (vf_107(BA4At(cell), -1, -1, 0, 1) == 0) {
                int width = Type->GetFoundationWidth();
                int height = Type->GetFoundationHeight(false);
                bool placed = zero;

                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        CellStruct c = cell + BA4Off(x, y);
                        if (BA4At(c)->FUN_0047C620(Type->SpeedType, Type, Owner)
                            && BA4At(c)->IsoTileTypeIndex != Type->ToTile->unknown_294
                            && BA4At(c)->LandType != 1) {
                            CellClass* mc = BA4At(c);
                            if (mc->SmudgeTypeIndex != -1) {
                                BA4Placed* placedType = DAT_00A8EC1C[mc->SmudgeTypeIndex];
                                CellStruct base = mc->MapCoords;
                                int index = mc->SmudgeData;
                                base.X -= (short)(index % placedType->unknown_298);
                                base.Y -= (short)(index / placedType->unknown_298);
                                for (int j = 0; j < placedType->unknown_29C; j++) {
                                    for (int i = 0; i < placedType->unknown_298; i++) {
                                        BA4At(base + BA4Off(i, j))->SmudgeTypeIndex = -1;
                                        BA4At(base + BA4Off(i, j))->FUN_004852D0();
                                    }
                                }
                            }
                            ObjectClass* created = (Type->ToTile->*(Type->ToTile->Vfptr->At_8C))(Owner);
                            CoordStruct where;
                            where.X = c.X * 256 + 128;
                            where.Y = c.Y * 256 + 128;
                            where.Z = zero;
                            created->vf_54(where, 0);
                            if (Owner == DAT_00A83D4C) {
                                CoordStruct reveal;
                                reveal.X = c.X * 256 + 128;
                                reveal.Y = c.Y * 256 + 128;
                                reveal.Z = zero;
                                DAT_0087F7E8.FUN_005678E0(&reveal, 1, DAT_00A83D4C, zero, zero, zero, 1, zero);
                                CoordStruct reveal2;
                                reveal2.X = c.X * 256 + 128;
                                reveal2.Y = c.Y * 256 + 128;
                                reveal2.Z = zero;
                                DAT_0087F7E8.FUN_005678E0(&reveal2, 1, DAT_00A83D4C, zero, zero, zero, 1, 1);
                            }
                            placed = true;
                        }
                    }
                }
                for (y = 0; y < height + 2; y++) {
                    for (x = 0; x < width + 2; x++) {
                        BA4At(cell + BA4Off(x - 1, y - 1))->FUN_00486E70();
                    }
                }
                if (placed) {
                    vf_160(3);
                    vf_62();
                    return true;
                }
            }
            TechnoClass::vf_73(0);
            goto refuse;
        }
        if (Type->bools_1570[1]) {
            BA4Spawned* spawned = new BA4Spawned(Type->ToOverlay, &cell, Owner->Type->ArrayIndex2);
            vf_160(3);
            vf_62();
            return true;
        }
        if (mark != 3) {
            if (vf_107(BA4At(cell), -1, -1, 0, 1) != 0) {
                goto refuse;
            }
        }
        DAT_0087F7E8.FUN_005683C0(&cell, this);
        {
            CoordStruct where;
            where.X = cell.X * 256 + 128;
            where.Y = cell.Y * 256 + 128;
            where.Z = zero;
            vf_109(Type->vf_27(where));
        }
        {
            CoordStruct center = vf_43();
            for (int k = 0; k < 21; k++) {
                if (Anims[k]) {
                    CoordStruct scratchOffset;
                    CoordStruct* offset = DAT_00887324->FUN_006D2360(&scratchOffset, &Type->BuildingAnim[k].X);
                    CoordStruct sumScratch;
                    CoordStruct sum = *sumScratch.FUN_0041C230(center.X + offset->X, offset->Y + center.Y, offset->Z + center.Z);
                    Anims[k]->vf_109(sum);
                }
            }
        }
        {
            int width = Type->GetFoundationWidth();
            int height = Type->GetFoundationHeight(false);
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    CellClass* mc = BA4At(cell + BA4Off(x, y));
                    if (mc->SmudgeTypeIndex != -1) {
                        BA4Placed* placedType = DAT_00A8EC1C[mc->SmudgeTypeIndex];
                        CellStruct base = mc->MapCoords;
                        int index = mc->SmudgeData;
                        base.X -= (short)(index % placedType->unknown_298);
                        base.Y -= (short)(index / placedType->unknown_298);
                        for (int j = 0; j < placedType->unknown_29C; j++) {
                            for (int i = 0; i < placedType->unknown_298; i++) {
                                BA4At(base + BA4Off(i, j))->SmudgeTypeIndex = -1;
                                BA4At(base + BA4Off(i, j))->FUN_004852D0();
                            }
                        }
                    }
                }
            }
            for (y = 0; y < height + 2; y++) {
                for (x = 0; x < width + 2; x++) {
                    BA4At(cell + BA4Off(x - 1, y - 1))->FUN_00486E70();
                }
            }
        }
        return true;

    case 2:
        {
            void* value = vf_121();
            int angle = vf_281(vf_111()->Intensity_Normal);
            BuildingClass* techno = BA4As<BuildingClass>(this, 6);
            if (vf_88() || (Airstrike && Airstrike->Target == techno)) {
                angle = FUN_0070E360(angle);
            }
            LightTint = (short)angle;
            for (int k = 0; k < 21; k++) {
                AnimClass* anim = Anims[k];
                if (anim) {
                    if (anim->Type && anim->Type->ShouldUseCellDrawer) {
                        anim->LightConvert = value;
                        anim->TintColor = angle & 0xFFFF;
                    }
                    char facing = Translucency;
                    if (facing == 0xF && vf_26(0, 0) == 5) {
                        facing = 0x10;
                    }
                    for (int m = 0; m < 21; m++) {
                        if (Anims[m]) {
                            Anims[m]->TranslucencyLevel = facing;
                        }
                    }
                }
            }
            char facing = Translucency;
            if (facing == 0xF && vf_26(0, 0) == 5) {
                facing = 0x10;
            }
            for (int m = 0; m < 21; m++) {
                if (Anims[m]) {
                    Anims[m]->TranslucencyLevel = facing;
                }
            }
        }
        break;
    }
    return true;
refuse:
    return false;
}
