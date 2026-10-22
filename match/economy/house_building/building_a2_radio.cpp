// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot 101 of the building-a2 cluster: the radio message handler (BuildingClass::Receive_Message). Read from
//   the retail gamemd.exe v1.001 from its entry to its last RET with a LINEAR decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a2_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4). The message
//   numbers and the results (1 = accepted, 10 = refused) are kept numeric.

#include "building_a2_views.h"

// The length of the vector between two coordinates, as the original computed it inline (squared components
// summed in a double, square root, truncation).
static inline int BA2Distance(const HBCoord* a, const HBCoord* b)
{
    int dx = a->X - b->X;
    int dy = a->Y - b->Y;
    return (int)FUN_004CAC40((double)dy * (double)dy + (double)(a->Z - b->Z) * (double)(a->Z - b->Z) + (double)dx * (double)dx);
}

// CAPPED (partial, readable): 83.4% of the retail instructions align (91.3% with stack offsets ignored). Remaining
// delta: retail reaches two shared return blocks (`return 10` at 0x43CB68 from 13 jumps, `return 1` at 0x43CCF2 from 15
// jumps) where ours repeats the 7-instruction epilogue at each site, which also lets our compiler turn seven
// `if (x == 1) return 10; return 1;` pairs into neg/sbb arithmetic where retail keeps the branch; the cell of the
// transfer target is read through the returned pointer in retail (ours copies the dword). Compound `||` conditions
// reproduce the sharing only where the source really had one condition; the remaining sites are unexplained.
// FUNCTION: GAMEMD 0x43C2D0
int BA2Building::vf_101(BA2Other* from, int message, BA2Obj*& param)
{
    switch (message) {
    case 0xF:
        FUN_006F4AB0(from, message, param);
        if (!Owner->FUN_004F9A90(from)) {
            return 0;
        }
        if (vf_97() == 0x12 || vf_97() == 0x13 || BState == 0
            || (!DAT_00A8E7AC && !FUN_0065ADF0(from) && !Type->unknown_16AE && !Type->unknown_16AF)) {
            return 10;
        }
        if (from->vf_33()->unknown_5B4 != 5) {
            if ((vf_33()->unknown_CCE && !from->vf_33()->unknown_CCE)
                || (!vf_33()->unknown_CCE && from->vf_33()->unknown_CCE)) {
                return 10;
            }
        }
        if (from->vf_33()->unknown_D6A) {
            return 10;
        }
        if (!unknown_660) {
            return 10;
        }
        if (Type->unknown_16AE || Type->unknown_16AF) {
            if ((from->vf_11() == 1 && !Type->unknown_16AE) || (from->vf_11() == 0xF && !Type->unknown_16AF)) {
                return 10;
            }
            if (from->unknown_2BC && from->unknown_2BC->FUN_004722C0()) {
                return 10;
            }
            if (unknown_114.Count + 1 <= Type->unknown_5E0 && from->vf_33()->unknown_380 <= Type->unknown_388) {
                return 1;
            }
        }
        if (Type->unknown_16AD) {
            return 1;
        }
        if (Type->unknown_16AB) {
            if (!from->FUN_0070FB50() || vf_158(0x23, from) == 1) {
                return 10;
            }
            return 1;
        }
        if (Type->unknown_16A9) {
            if ((from->vf_11() != 1 && from->vf_11() != 2) || vf_158(0x23, from) == 1) {
                return 10;
            }
            return 1;
        }
        if ((Type->unknown_16C2 || Type->unknown_16C1) && from->vf_11() == 0xF) {
            BA2Other* other = !from ? 0 : (from->vf_11() == 0xF ? from : 0);
            if (other->unknown_2BC && other->unknown_2BC->FUN_004722C0()) {
                return 10;
            }
            if (other->FUN_007105E0()) {
                return 10;
            }
            return unknown_2FC ? 1 : 10;
        }
        if (Type->unknown_16CB) {
            return from->unknown_04.vf_3() == 2 ? 1 : 10;
        }
        if (Type->unknown_16B3 && from->vf_11() == 1 && from->unknown_6C4->unknown_E0E) {
            if (DAT_00A8E7AC || !unknown_118) {
                return 1;
            }
        }
        if (Type->unknown_16BC && from->vf_11() == 1 && from->unknown_6C4->unknown_E0F) {
            if (DAT_00A8E7AC || !unknown_118) {
                return 1;
            }
        }
        return 0;
    case 0x15:
        if (vf_97() == 0x13) {
            return 10;
        }
        if (Type->unknown_16AE || Type->unknown_16AF) {
            return 1;
        }
        if (Type->unknown_16A9 || Type->unknown_16AA || Type->unknown_16C1 || Type->unknown_16C2) {
            unknown_6DD = 1;
            vf_122(0x14, 0);
            from->vf_122(0, 0);
            return 1;
        }
        if (Type->unknown_16AB) {
            unknown_6DD = 1;
            vf_122(0x14, 0);
            return 1;
        }
        if (Type->unknown_16B3) {
            from->vf_122(0x10, 0);
            return 1;
        }
        break;
    case 0xE:
        FUN_006F4AB0(from, message, param);
        if (!unknown_660) {
            return 10;
        }
        if (Type->unknown_16A9 && FUN_0065AD50(from) && vf_158(0x22, from) == 10) {
            return 10;
        }
        if (Type->unknown_16AB && FUN_0065AD50(from) && !from->FUN_0070FB50()) {
            return 10;
        }
        if (!Type->unknown_16C1 && !Type->unknown_16C2) {
            if (!FUN_0065AD50(from) && FUN_0065ADF0(from)) {
                vf_158(2, from);
                FUN_0065AD50(from);
            }
            bool needsRetry = false;
            if (FUN_0065AD50(from) && (Type->unknown_16B3 || Type->unknown_16BC)) {
                BA2Other* other = !from ? 0 : (from->unknown_14 & 4 ? from : 0);
                HBCoord where;
                BA2CellObj* cell = DAT_0087F7E8.FUN_00565730(vf_42(&where, other));
                BA2Obj* expected = other->unknown_5A4;
                if (expected && cell != expected) {
                    needsRetry = true;
                }
            }
            if (FUN_0065AD30(0) && (Type->unknown_16A9 || Type->unknown_16AB)) {
                HBCoord a, b;
                HBCoord* there = FUN_0065AD30(0)->vf_18(&a);
                HBCoord* here = vf_18(&b);
                if (BA2Distance(here, there) > 0x80) {
                    needsRetry = true;
                }
            }
            if (vf_158(0x13, from) != 1 && !needsRetry) {
                return 1;
            }
            param = this;
            if (Type->unknown_16B3 || Type->unknown_16BC) {
                const HBCell& here = vf_110();
                HBCell target = HBCell(here.X + 3, here.Y + 1);
                param = DAT_0087F7E8.FUN_005657A0(&target);
                if (vf_159(0x12, param, from) != 0x14) {
                    return 1;
                }
                vf_158(0x18, from);
                if (vf_158(0x16, from) == 1) {
                    return 1;
                }
                from->vf_93(&DAT_0089C848, 1, 1);
                return 1;
            }
            if (!Type->unknown_16CB) {
                return 1;
            }
            param = this;
            if (vf_159(0x12, param, from) != 0x14) {
                return 1;
            }
            vf_157(0x18);
            return 1;
        }
        if (FUN_0065ADF0(from)) {
            HBCoord where = Location;
            param = DAT_0087F7E8.FUN_00565730(&where);
            vf_159(0x12, param, from);
            return 1;
        }
        {
            for (int i = 0; i < unknown_E8; i++) {
                BA2Obj* o = FUN_0065AD30(i);
                if (vf_158(0x22, o) == 10) {
                    vf_158(0x17, o);
                }
            }
        }
        if (FUN_0065ADF0(from)) {
            return 1;
        }
        return 10;
    case 0x10:
        if (unknown_118 != 0 || !FUN_0065ADF0(from) || unknown_81 || Owner != from->vf_15()) {
            return 10;
        }
        if (Type->unknown_16BB || Type->unknown_16A9 || Type->unknown_16BC) {
            return 1;
        }
        return 10;
    case 0xB:
        vf_122(0x14, 0);
        FUN_006F4AB0(from, message, param);
        return 1;
    case 0xC:
        if (vf_97() != 0x13) {
            vf_122(5, 0);
            if (Type->unknown_16B9) {
                FUN_00451E40(7);
                FUN_00451E40(0x12);
                double ratio = FUN_005F5C60();
                bool low = ratio <= RulesInstance_8871E0->unknown_1700;
                char* name = low ? Type->unknown_F4C[8].Low : Type->unknown_F4C[8].Normal;
                if (name && *name) {
                    FUN_00451890(name, 8, low, 0, 0);
                }
            }
        }
        FUN_006F4AB0(from, message, param);
        return 1;
    case 3:
        FUN_00447780(1);
        FUN_006F4AB0(from, message, param);
        return 1;
    case 8:
        if (Type->unknown_16A9 || Type->unknown_16AB) {
            HBCoord a, b;
            HBCoord* there = from->vf_18(&a);
            HBCoord* here = vf_18(&b);
            if (BA2Distance(here, there) < 0x180) {
                return 1;
            }
        }
        FUN_006F4AB0(from, message, param);
        if (!Type->unknown_16BD && !Type->unknown_16A9 && !Type->unknown_16AB) {
            return 1;
        }
        return 0x17;
    case 0xD:
        if (Type->unknown_16BD) {
            return 1;
        }
        break;
    }
    return FUN_006F4AB0(from, message, param);
}
