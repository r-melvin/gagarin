// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 53 at 0x445880 (0x5C6 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode). Slot 53 is where ObjectClass keeps its "take off the
//   map" virtual; the original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x445880
bool BA4Building::vf_53()
{
    int i;
    bool result;
    bool anyUpgradeFlag = false;
    HBCoordPod coord = Location;
    HBCell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);

    if (!unknown_81 && Type != 0) {
        for (i = 0; i < 8; i++) {
            if (DamageFireAnims[i]) {
                DamageFireAnims[i]->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        if (Type->unknown_16CC && unknown_6E4) {
            Owner->unknown_538C--;
            if (Owner->unknown_538C < 0) {
                Owner->unknown_538C = 0;
            }
        }
        if (Type->unknown_16CB && unknown_6E4) {
            Owner->unknown_2D4 -= Type->unknown_1780;
            if (Owner->unknown_2D4 < 0) {
                Owner->unknown_2D4 = 0;
            }
        }
        if (Type->unknown_1564 && unknown_6E4) {
            Owner->unknown_164 -= Type->unknown_1564;
            if (Owner->unknown_164 < 0) {
                Owner->unknown_164 = 0;
            }
        }
        if (Type->unknown_1568 && unknown_6E4) {
            Owner->unknown_168 -= Type->unknown_1568;
            if (Owner->unknown_168 < 0) {
                Owner->unknown_168 = 0;
            }
        }
        if (Type->unknown_16BE) {
            FUN_00452A40(0);
        }
        if (!DAT_00A8E7AC) {
            if (Type->unknown_16C8) {
                vf_318(DAT_0089C818);
            }
            if (Type->unknown_D31) {
                vf_320(DAT_0089C818);
            }
            if ((!Type->unknown_408 || !Type->unknown_5EC) && !vf_32()) {
                FUN_004561F0();
            }
        }
        for (i = 0; i < 3; i++) {
            if (Upgrades[i + 1] && Upgrades[i + 1]->unknown_1763) {
                anyUpgradeFlag = true;
                break;
            }
        }
        if (!DAT_00A8E9A0) {
            if (Type->unknown_16BE && !DAT_00A8E7AC) {
                unknown_618 = 0;
            }
            return true;
        }
        if (Type == DAT_008871E0->unknown_87C) {
            for (i = 0; i < 8; i += 2) {
                BA4MapCell* mc = DAT_0087F7E8.FUN_005657A0(cell + DAT_0089F688[i & 7]);
                mc->FUN_00480630(0);
                if (mc->unknown_44 != -1 && DAT_00A83D84[mc->unknown_44]->unknown_2A8 && mc->unknown_11E < 0x10) {
                    mc->FUN_00480CB0(200);
                }
            }
        }
        if (Type == DAT_008871E0->unknown_86C || Type == DAT_008871E0->unknown_874) {
            DAT_0087F7E8.FUN_005657A0(cell + HBCell(-1, 0))->FUN_00480630(0);
            DAT_0087F7E8.FUN_005657A0(cell + HBCell(3, 0))->FUN_00480630(0);
        }
        if (Type == DAT_008871E0->unknown_870 || Type == DAT_008871E0->unknown_878) {
            DAT_0087F7E8.FUN_005657A0(cell + HBCell(0, -1))->FUN_00480630(0);
            DAT_0087F7E8.FUN_005657A0(cell + HBCell(0, 3))->FUN_00480630(0);
        }
        if (!Type->unknown_E58) {
            int width = Type->FUN_0045EC90();
            int height = Type->FUN_0045ECA0(false);
            HBCell scratch;
            HBCell origin = *vf_110(&scratch);
            for (int y = 0; y < height + 2; y++) {
                HBCell corner = origin + HBCell(-1, -1);
                for (i = 0; i < width + 2; i++) {
                    DAT_0087F7E8.FUN_005657A0(corner + HBCell(i, y))->unknown_122--;
                }
            }
        }
        if (DAT_00887324) {
            HBRect buf;
            DAT_00887324->FUN_006D2790(*vf_75(&buf), 0);
        }
        if (Spotlight) {
            Spotlight->vf_62();
        }
        Owner->FUN_004FF980(this);
        Owner->unknown_1FC = 1;
        Owner->FUN_004FD150();
        if (Owner == DAT_00A83D4C) {
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        Owner->FUN_0050A490(this);
    }
    result = FUN_006F6AC0();
    if (anyUpgradeFlag) {
        Owner->FUN_00509130();
    }
    if (Type->unknown_EB8) {
        Owner->FUN_00509140(Type->unknown_EB8, Type->unknown_CCE, 0);
    }
    if (Type->unknown_16BE && !DAT_00A8E7AC) {
        unknown_618 = 0;
    }
    return result;
}
