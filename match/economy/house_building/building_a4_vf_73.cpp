// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 73 at 0x43F180 (0x99C bytes with its 4-entry jump table at 0x43FB0C),
//   read from the retail gamemd.exe v1.001 from its entry to its last RET (linear decode; Ghidra's flow
//   listing drops instructions after some calls). The one argument selects a mode 0..3 through the jump
//   table; modes 1 and 3 share a body. The original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x43F180
bool BA4Building::vf_73(int mark)
{
    HBCell scratch;
    HBCell cell;
    int zero = 0;
    int x;
    int y;

    if (!FUN_006F4A70(mark)) {
        goto refuse;
    }

    cell = *vf_110(&scratch);

    switch (mark) {
    case 0:
        DAT_0087F7E8.FUN_005687F0(&cell, this);
        return true;

    case 1:
    case 3:
        if (Type->unknown_E58) {
            if (vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, 1) == 0) {
                int width = Type->FUN_0045EC90();
                int height = Type->FUN_0045ECA0(false);
                bool placed = zero;

                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        HBCell c = cell + HBCell(x, y);
                        if (DAT_0087F7E8.FUN_005657A0(c)->FUN_0047C620(Type->unknown_67C, Type, Owner)
                            && DAT_0087F7E8.FUN_005657A0(c)->unknown_38 != Type->unknown_E58->unknown_294
                            && DAT_0087F7E8.FUN_005657A0(c)->unknown_EC != 1) {
                            BA4MapCell* mc = DAT_0087F7E8.FUN_005657A0(c);
                            if (mc->unknown_48 != -1) {
                                BA4Placed* placedType = DAT_00A8EC1C[mc->unknown_48];
                                HBCell base = mc->unknown_24;
                                int index = mc->unknown_11F;
                                base.X -= (short)(index % placedType->unknown_298);
                                base.Y -= (short)(index / placedType->unknown_298);
                                for (int j = 0; j < placedType->unknown_29C; j++) {
                                    for (int i = 0; i < placedType->unknown_298; i++) {
                                        DAT_0087F7E8.FUN_005657A0(base + HBCell(i, j))->unknown_48 = -1;
                                        DAT_0087F7E8.FUN_005657A0(base + HBCell(i, j))->FUN_004852D0();
                                    }
                                }
                            }
                            BA4Object* created = Type->unknown_E58->vf_35(Owner);
                            HBCoordPod where;
                            where.X = c.X * 256 + 128;
                            where.Y = c.Y * 256 + 128;
                            where.Z = zero;
                            created->vf_54(&where, 0);
                            if (Owner == DAT_00A83D4C) {
                                HBCoordPod reveal;
                                reveal.X = c.X * 256 + 128;
                                reveal.Y = c.Y * 256 + 128;
                                reveal.Z = zero;
                                DAT_0087F7E8.FUN_005678E0(&reveal, 1, DAT_00A83D4C, zero, zero, zero, 1, zero);
                                HBCoordPod reveal2;
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
                        DAT_0087F7E8.FUN_005657A0(cell + HBCell(x - 1, y - 1))->FUN_00486E70();
                    }
                }
                if (placed) {
                    vf_160(3);
                    vf_62();
                    return true;
                }
            }
            FUN_006F4A70(0);
            goto refuse;
        }
        if (Type->unknown_1571) {
            BA4Spawned* spawned = new BA4Spawned(Type->unknown_E54, &cell, Owner->unknown_34->unknown_B8);
            vf_160(3);
            vf_62();
            return true;
        }
        if (mark != 3) {
            if (vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, 1) != 0) {
                goto refuse;
            }
        }
        DAT_0087F7E8.FUN_005683C0(&cell, this);
        {
            HBCoordPod where;
            where.X = cell.X * 256 + 128;
            where.Y = cell.Y * 256 + 128;
            where.Z = zero;
            HBCoordPod scratchCoord;
            vf_109(Type->vf_27(&scratchCoord, &where));
        }
        {
            HBCoordPod scratchCoord;
            HBCoordPod center = *vf_43(&scratchCoord);
            for (int k = 0; k < 21; k++) {
                if (Anims[k]) {
                    HBCoordPod scratchOffset;
                    HBCoordPod* offset = DAT_00887324->FUN_006D2360(&scratchOffset, &Type->unknown_F4C[k].unknown_30);
                    HBCoordPod sumScratch;
                    HBCoordPod sum = *sumScratch.FUN_0041C230(center.X + offset->X, offset->Y + center.Y, offset->Z + center.Z);
                    Anims[k]->vf_109(&sum);
                }
            }
        }
        {
            int width = Type->FUN_0045EC90();
            int height = Type->FUN_0045ECA0(false);
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    BA4MapCell* mc = DAT_0087F7E8.FUN_005657A0(cell + HBCell(x, y));
                    if (mc->unknown_48 != -1) {
                        BA4Placed* placedType = DAT_00A8EC1C[mc->unknown_48];
                        HBCell base = mc->unknown_24;
                        int index = mc->unknown_11F;
                        base.X -= (short)(index % placedType->unknown_298);
                        base.Y -= (short)(index / placedType->unknown_298);
                        for (int j = 0; j < placedType->unknown_29C; j++) {
                            for (int i = 0; i < placedType->unknown_298; i++) {
                                DAT_0087F7E8.FUN_005657A0(base + HBCell(i, j))->unknown_48 = -1;
                                DAT_0087F7E8.FUN_005657A0(base + HBCell(i, j))->FUN_004852D0();
                            }
                        }
                    }
                }
            }
            for (y = 0; y < height + 2; y++) {
                for (x = 0; x < width + 2; x++) {
                    DAT_0087F7E8.FUN_005657A0(cell + HBCell(x - 1, y - 1))->FUN_00486E70();
                }
            }
        }
        return true;

    case 2:
        {
            int value = vf_121();
            int angle = vf_281(vf_111()->unknown_10A);
            BA4Building* techno = BA4As(this, 6);
            if (vf_88() || (unknown_294 && unknown_294->unknown_50 == (unsigned int)techno)) {
                angle = FUN_0070E360(angle);
            }
            unknown_700 = (short)angle;
            for (int k = 0; k < 21; k++) {
                BA4Object* anim = Anims[k];
                if (anim) {
                    if (anim->unknown_C8 && anim->unknown_C8->unknown_35C) {
                        anim->unknown_D4 = value;
                        anim->unknown_FC = angle & 0xFFFF;
                    }
                    char facing = unknown_6ED;
                    if (facing == 0xF && vf_26(0, 0) == 5) {
                        facing = 0x10;
                    }
                    for (int m = 0; m < 21; m++) {
                        if (Anims[m]) {
                            Anims[m]->unknown_178 = facing;
                        }
                    }
                }
            }
            char facing = unknown_6ED;
            if (facing == 0xF && vf_26(0, 0) == 5) {
                facing = 0x10;
            }
            for (int m = 0; m < 21; m++) {
                if (Anims[m]) {
                    Anims[m]->unknown_178 = facing;
                }
            }
        }
        break;
    }
    return true;
refuse:
    return false;
}
