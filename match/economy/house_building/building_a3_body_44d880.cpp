// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 143 (+0x23C): the per-frame mission body of a building that lets its
//   passengers out (units leave through the cell facing the building, or one of its eight neighbours; a second
//   variant swaps the locomotor of the unloaded passenger and a third toggles a flag state), returning the delay
//   until its next call. Span 0x44D880..0x44E3A0 (0xB20 bytes: code to 0x44E389 and a 5-entry jump table). The method
//   names are slot labels / FUN_<addr>; no original name is confirmed.
// CAPPED (final) at 3.1% positional on the 0xB09-byte code span (26/849; the jump table is not scored), 52.2% by sequence alignment;
// all 94 calls are in retail order, including the whole inlined smart-pointer sequence. Delta: the zero constant lives in EDI in retail
// (`cmp esi,edi`) and is a TEST here; the frame is 0x4C against 0x40; the passenger scan keeps its locals in other slots; the
// direction index expansions differ in register use.
// Variants tried: the duration as a double (introduces an EBP frame and FPU traffic) against an 8-byte struct (matches the pushes),
// `if (passenger)` against early exit (retail places the null path last), the CLSID tests as `||` against nested ifs (retail order
// D, C, A/B), the release / assignment order of the smart pointers, the delay as one expression against two statements.

#include "building_a3_views.h"

// The delay returned by the passenger and state paths: the price-table delay scaled, plus a little random jitter.
#define BA3_RETURN_NEXT_DELAY()                                                           \
    {                                                                                      \
        int next = (int)(FUN_005B3A00()->unknown_10 * DAT_007E27F8);                        \
        return next + DAT_00A8B230->Counter.FUN_0065C7E0(0, 2);                             \
    }

// FUNCTION: GAMEMD 0x44D880
int BuildingA3View::vf_143()
{
    if (vf_258() > 0) {
        FUN_00457DE0(0, 0);
    }

    if ((Type->unknown_16AE || Type->unknown_16AF) && unknown_114.Count > 0) {
        BA3TechnoView* passenger = unknown_114.FUN_00473430();
        if (passenger) {
            HBDir start;
            start.Raw = Facing388.FUN_004C93D0().Raw + 0x7FFF;
            bool first = true;
            int index = 0;
            unsigned int base = ((start.Whole >> 12) + 1) >> 1;
            do {
                int dir = (base + index) & 7;
                HBCell scratch;
        HBCell origin = *vf_110(&scratch);
                HBCell cellA;
                cellA.X = origin.X + DAT_0089F688[dir].X;
                cellA.Y = origin.Y + DAT_0089F688[dir].Y;
                HBCell cellB;
                cellB.X = cellA.X + DAT_0089F688[dir].X;
                cellB.Y = cellA.Y + DAT_0089F688[dir].Y;
                HBCell copyA = cellA;
                HBCell copyB = cellB;

                bool farFree = passenger->vf_107(DAT_0087F7E8.FUN_005657A0(&copyB), dir, FUN_005F5F00(), 0, 1) == 0;
                int nearBlocked = passenger->vf_107(DAT_0087F7E8.FUN_005657A0(&copyA), dir, FUN_005F5F00(), 0, 1);
                if (!nearBlocked) {
                    if (!farFree && first) {
                        goto restart;
                    }
                    if (!(DAT_0087F7E8.FUN_005657A0(&copyA)->unknown_140 & 0x100)) {
                        // The near cell is free: put the passenger there.
                        ++DAT_00A8E7AC;
                        HBCoord where;
                        where.X = copyA.X * 256 + 0x80;
                        where.Y = copyA.Y * 256 + 0x80;
                        where.Z = 0;
                        if (passenger->vf_11() == 0xF) {
                            HBCoord tmp;
                            where = *DAT_0087F7E8.FUN_004ACA10(&tmp, &where, 0);
                        } else {
                            HBCell zero;
                            zero.X = 0;
                            zero.Y = 0;
                            HBCell found = *DAT_0087F7E8.FUN_0056DC20(
                                &where, &copyA, passenger->vf_33()->unknown_67C, -1, 0, 0, 1, 1, 0, 0, 0, 1, &zero, 0, 0);
                            copyA = found;
                            HBCoord centre = DAT_0087F7E8.FUN_005657A0(&copyA)->vf_18();
                            HBCell back;
                            HBCell snapped = *back.FUN_0042D470((short)(centre.X / 256), (short)(centre.Y / 256));
                            where.X = snapped.X * 256 + 0x80;
                            where.Y = snapped.Y * 256 + 0x80;
                            where.Z = 0;
                        }
                        HBDir facing;
                        facing.Raw = (short)(dir << 13);
                        bool placed = passenger->vf_54(where, ((facing.Whole >> 7) + 1 >> 1) & 0xFF);
                        --DAT_00A8E7AC;
                        if (!placed) {
                            goto failed;
                        }
                        if (Type->unknown_16AF) {
                            FUN_007509E0(RulesInstance->unknown_274, &vf_18(), 0);
                            if (passenger->unknown_21C->IsHumanPlayer) {
                                passenger->unknown_68F = 0;
                            }
                            if (!passenger->unknown_438) {
                                passenger->unknown_21C->OwnedInfantry++;
                                passenger->unknown_438 = 1;
                            }
                            passenger->unknown_439 = 0;
                        }
                        passenger->vf_122(2, 0);
                        passenger->vf_288(DAT_0087F7E8.FUN_005657A0(first ? &copyB : &copyA), 1);
                        if (Type->unknown_EE8 > 0) {
                            Owner->RecheckPower = 1;
                        }
                        goto done;
                    }
                } else if (first) {
                restart:
                    if (index == 7) {
                        index = 0;
                        first = false;
                    }
                }
                index++;
            } while (index < 8);
        failed:
            unknown_114.FUN_004733A0(passenger);
            passenger->vf_71();
        }
    done:
        BA3_RETURN_NEXT_DELAY()
    }

    if (Type->unknown_16BD) {
    HBCoord exit;
    exit.X = 0;
    exit.Y = 0;
    exit.Z = 0;
    if (!Type->unknown_CCE) {
        HBCell offset = Type->unknown_ED4->unknown_28;
        HBCell scratch;
        HBCell origin = *vf_110(&scratch);
        HBCell cell;
        cell.X = offset.X + origin.X;
        cell.Y = origin.Y + offset.Y;
        exit.X = (short)(cell.X - 1) * 256 + 0x80;
        exit.Y = cell.Y * 256 + 0x80;
        exit.Z = 0;
    }

    switch (Status) {
    case 0: {
        BA3TechnoView* passenger = FUN_0065AD30(0);
        if (passenger) {
            passenger->vf_122(5, 0);
            passenger->vf_123();
        }
        unknown_350.FUN_004A51F0(Type->unknown_3C8);
        unknown_80 = 1;
        Status = (Type->unknown_CCE != 0 ? 3 : 0) + 1;
        FUN_00451E40(0x12);
        BA3_PLAY_NAME(this, unknown_116C, unknown_117C, 8)
        break;
    }
    case 1:
        if (!FUN_00449540()) {
            FUN_004068E0(DAT_00819098);
            Status = 2;
        }
        break;
    case 2: {
        if (!unknown_350.FUN_004A51B0()) {
            break;
        }
        BA3TechnoView* passenger = FUN_0065AD30(0);
        if (passenger) {
            passenger->vf_122(2, 0);
            // The locomotor of the passenger decides how it is put on the ground.
            BA3ComPtr* locomotor = &passenger->unknown_674;
            BA3ComPtr persist;
            persist.p = 0;
            if (locomotor->p) {
                long hr = persist.FUN_0045AEA0(locomotor);
                if (hr < 0 && hr != (long)0x80004002) {
                    FUN_007DC720(hr);
                }
            }
            unsigned char clsid[16];
            persist->vf_3(clsid);
            if (memcmp(clsid, DAT_007E9A50, 16) != 0 && memcmp(clsid, DAT_007E9A90, 16) != 0) {
                if (memcmp(clsid, DAT_007E9A30, 16) != 0) {
                    HBCell scratch;
                    HBCell here = *passenger->vf_110(&scratch);
                    HBCell beside;
                    beside.X = here.X + 4;
                    beside.Y = here.Y + 1;
                    passenger->vf_288(DAT_0087F7E8.FUN_005657A0(&beside), 1);
                } else {
                    (*locomotor)->vf_28(0x42, exit);
                }
            } else {
                // A piggy-backing locomotor: end the piggy-back and give the passenger a fresh Drive locomotor.
                BA3ComPtr drive;
                drive.p = 0;
                if (locomotor->p) {
                    long hr = drive.FUN_0045AF20(locomotor);
                    if (hr < 0 && hr != (long)0x80004002) {
                        FUN_007DC720(hr);
                    }
                }
                if (drive.p && ((BA3PiggyIface*)drive.p)->vf_7()) {
                    if (locomotor->p) {
                        locomotor->p->Release();
                    }
                    locomotor->p = 0;
                    if (!drive.p) {
                        FUN_007DC720(0x80004003);
                    }
                    ((BA3PiggyIface*)drive.p)->vf_4(locomotor);
                }
                BA3ComPtr fresh;
                fresh.p = 0;
                long hr = fresh.FUN_0041C250(DAT_007E9A30, 0, 7);
                if (hr < 0 && hr != (long)0x80004002) {
                    FUN_007DC720(hr);
                }
                fresh->vf_3(passenger);
                BA3ComPtr typed;
                typed.p = 0;
                if (fresh.p) {
                    void* out;
                    long qi = fresh.FUN_0045A050()->QueryInterface(DAT_00819088, &out);
                    if (qi < 0) {
                        typed.FUN_0045A160();
                        typed.p = 0;
                    } else {
                        BA3ComUnk* acquired = (BA3ComUnk*)out;
                        typed.FUN_0045A160();
                        typed.p = acquired;
                    }
                    if (qi < 0 && qi != (long)0x80004002) {
                        FUN_007DC720(qi);
                    }
                }
                if (drive.p != typed.p) {
                    BA3ComUnk* old = drive.p;
                    drive.p = typed.p;
                    drive.FUN_0045A170();
                    if (old) {
                        old->Release();
                    }
                }
                if (typed.p) {
                    typed.p->Release();
                }
                if (drive.p) {
                    drive.p->vf_3(locomotor->p);
                    BA3ComUnk* old = locomotor->p;
                    if (old != drive.p) {
                        locomotor->p = drive.p;
                        if (drive.p) {
                            drive.p->AddRef();
                        }
                        if (old) {
                            old->Release();
                        }
                    }
                    (*locomotor)->vf_28(0x42, exit);
                } else {
                    int target = passenger->unknown_6C;
                    passenger->vf_91(&target, 0, RulesInstance->unknown_FA8, 0, 1, 0, 0);
                }
                if (fresh.p) {
                    fresh.p->Release();
                }
                if (drive.p) {
                    drive.p->Release();
                }
            }
            passenger->vf_337(0.5);
            Status = 3;
            if (persist.p) {
                persist.p->Release();
            }
        } else {
            unknown_350.FUN_004A5240(Type->unknown_3C8);
            Status = 4;
        }
        break;
    }
    case 3:
        if (!unknown_418) {
            unknown_350.FUN_004A5240(Type->unknown_3C8);
            Status = 4;
        }
        break;
    case 4:
        if (unknown_350.FUN_004A51D0() || Type->unknown_CCE) {
            vf_289(false, 1);
            unknown_80 = 1;
        }
        break;
    }
    BA3_RETURN_NEXT_DELAY()
    }

    // The type without the second exit: toggle the flag state of the building.
    if (Type->unknown_CD1 && Type->unknown_CD3) {
            if (!unknown_268) {
                vf_262();
                unknown_26C = Type->unknown_CD3;
                if (vf_212()) {
                    vf_261();
                    unknown_268 = 1;
                    unknown_669 = 1;
                    Owner->RecheckPower = 1;
                } else {
                    unknown_26C = Type->unknown_CD2;
                    vf_261();
                }
            } else {
                vf_262();
                unknown_268 = 0;
                unknown_669 = 0;
                unknown_26C = Type->unknown_CD2;
                vf_261();
                Owner->RecheckPower = 1;
            }
        }
        vf_122(5, 0);
    return 1;
}
