// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Second batch of the building-a cluster: BuildingClass virtual methods of medium size. Every body was
//   read from the retail gamemd.exe v1.001 from its entry to its last RET; offsets are pinned in
//   building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).

#include "building_a_views.h"
#include "../../_layout/building_class.h"
#include "../../_layout/house_class.h"

// FUNCTION: GAMEMD 0x43ED40
//
// CAPPED at 10.1% (first transcription plus two reshapes). The facing from this building (plus the per-type
// firing offset, a zero coordinate by default) to a target. Delta: retail keeps the offset in ESI/EDI with
// the Z in a stack slot and reaches one shared transform call from both branches with different buffers;
// the sequential, shared-pointer and branch-swapped forms differ in prologue, frame (0x18 vs 0x2c) and call order.
HBDir BuildingAView::vf_314(BAObjView* target)
{
    HBCoord off = DAT_0089C848;
    BATypeView* type = Type;
    HBPoint2D p;
    HBPoint2D buf;
    if (type->unknown_E44.X == 0xFFFF && type->unknown_E44.Y == 0xFFFF) {
        p = type->unknown_11E0;
        if (p.X != 0 || p.Y != 0) {
            HBPoint2D* r = DAT_00887324->FUN_006D2070(&buf, &p);
            off.X = r->X;
            off.Y = r->Y;
            off.Z = 0;
        }
    } else {
        HBPoint2D* r = DAT_00887324->FUN_006D2070(&p, &type->unknown_E44);
        off.X = r->X;
        off.Y = r->Y;
        off.Z = 0;
    }
    HBCoord c;
    HBCoord* pc = vf_18(&c);
    int px = pc->X + off.X;
    int py = pc->Y + off.Y;
    HBCoord t;
    HBCoord* pt = target->vf_18(&t);
    int tx = pt->X;
    HBDir d;
    d.Raw = (short)((FUN_004CAE30((double)py - pt->Y, (double)tx - px) - DAT_007E2820) * DAT_007E2818);
    return d;
}

// FUNCTION: GAMEMD 0x442C40
// CAPPED at 86.5% (multiset identical). Delta: retail loads the AddItem vptr before the capacity sum and uses EDX
// for the type value; AddItem written as cap-local, member-reload and nested forms (86.5/84.3/77.5%).
void BuildingAView::vf_9()
{
    FUN_006F3F40();
    if (Owner) {
        unknown_53C = Owner->unknown_34->unknown_B8;
        Owner->FUN_004FF700(this);
    }
    if (Type) {
        unknown_70 = unknown_6C = Type->unknown_A0;
        int v = Type->unknown_680;
        if (v == -1) {
            v = Type->unknown_684;
        }
        unknown_2FC = v;
        Facing.FUN_004C9680(Type->unknown_71C);
        if (!Type->vf_48()) {
            unknown_6DC = 0;
        } else {
            Type->FUN_00465AF0();
            unknown_6E9 = 1;
        }
        if (Owner && Owner->unknown_2C0 && !Type->unknown_CCE && Type->unknown_C8E && Type->unknown_408) {
            unknown_150.FUN_00750090(1);
        }
    }
    if (Type && Type->unknown_16B0) {
        DAT_008B41E0.AddItem(this);
    }
}

// FUNCTION: GAMEMD 0x4436F0
bool BuildingAView::vf_80(int mode, HBCell* cell, int a3, int a4)
{
    if (mode == 5) {
        vf_222(1, DAT_0087F7E8.FUN_005657A0(cell), 0, 0);
    } else if (mode == 6 || mode == 1) {
        bool blocked = false;
        if (!Type->unknown_16B9
            || (Owner->FUN_0050B730() && DAT_00A8B238 && DAT_00A8B320 && unknown_2C0 == 0)) {
            if (Type->unknown_408 != 0 || vf_161()) {
                FUN_00443860(cell, 1);
            }
        } else {
            blocked = true;
        }
        if (Type->unknown_408 != 0 && !blocked) {
            BATargetRef targetBuf;
            BAEvent ev;
            BAEvent* queued = ev.FUN_004C65E0(vf_14(), 0x16, *targetBuf.FUN_006E6AB0(this));
            if (DAT_00A802C8.Count < 128) {
                DAT_00A802C8.List[DAT_00A802C8.Head] = *queued;
                DAT_00A802C8.unknown_378C[DAT_00A802C8.Head] = timeGetTime();
                DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 0x7F;
                DAT_00A802C8.Count++;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x4456D0
void BuildingAView::vf_312()
{
    int i;
    if (Owner == DAT_00A83D4C && !unknown_81 && unknown_41B && unknown_660) {
        switch (Type->unknown_EB8) {
        case 7:
            for (i = 0; i < DAT_00A83C68.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A83C68.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(7, i);
                }
            }
            break;
        case 0x28:
            for (i = 0; i < DAT_00A83CE0.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A83CE0.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(0x28, i);
                }
            }
            break;
        case 0x10:
            for (i = 0; i < DAT_00A8E348.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A8E348.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(0x10, i);
                }
            }
            break;
        case 3:
            for (i = 0; i < DAT_00A8B218.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A8B218.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(3, i);
                }
            }
            break;
        }
    }
}

// FUNCTION: GAMEMD 0x446FF0
void BuildingClass::vf_103(int mode)
{
    switch (mode) {
    case -1:
        IsBeingRepaired = IsBeingRepaired == 0;
        break;
    case 0:
        if (!IsBeingRepaired) {
            return;
        }
        IsBeingRepaired = 0;
        break;
    case 1:
        if (IsBeingRepaired) {
            return;
        }
        IsBeingRepaired = 1;
        break;
    }
    int sound;
    if (IsBeingRepaired) {
        if (Health == Type->Strength) {
            sound = RulesInstance->unknown_700;
        } else {
            sound = RulesInstance->unknown_70C;
            if (Owner->IsControlledByCurrentPlayer()) {
                vf_82(7);
            }
            NeedsRepairs = 1;
            if (Owner->IsControlledByCurrentPlayer()) {
                FUN_00752700(s_EVA_Repairing_00818F18, -1, -1);
            }
        }
    } else {
        sound = RulesInstance->unknown_70C;
    }
    if (Owner->IsControlledByCurrentPlayer()) {
        CoordStruct where = Location;
        FUN_007509E0(sound, &where, 0);
    }
}

// FUNCTION: GAMEMD 0x447110
//
// CAPPED (see the report): retail is a three-case switch on the mode whose "nothing to do" exits jump to the
// shared epilogue, which no switch/return/flag formulation tried here reproduces; the first-written
// if-chain form below scores best.
void BuildingAView::vf_104(int mode)
{
    if (!unknown_6E9) {
        if (Type->unknown_16C0) {
            Type->vf_33(Owner);
            Owner->FUN_0050B730();
            vf_53();
            vf_62();
        }
        return;
    }
    bool act;
    if (mode == -1) {
        act = vf_97() != 0x13;
    } else if (mode == 0) {
        if (vf_97() != 0x13) {
            return;
        }
        act = false;
    } else if (mode == 1) {
        if (vf_97() == 0x13 || unknown_6DF) {
            return;
        }
        act = true;
    } else {
        act = false;
    }
    if (act) {
        vf_122(0x13, 0);
        vf_123();
    }
    if (Owner->FUN_0050B6F0()) {
        VocClass::PlayGlobal(RulesInstance->unknown_70C, 1.0f, 0x2000, 0);
    }
}

// FUNCTION: GAMEMD 0x448160
// CAPPED at 81.7% (multiset identical). Delta: retail keeps the type pointer in EAX and the kind in ECX; the
// kind-first and result-first orders both allocate the other way.
char BuildingAView::vf_316()
{
    int kind = Type->unknown_EB8;
    char r = unknown_3D3;
    if (kind != 0) {
        if (r) {
            unknown_3D3 = 0;
        } else {
            int i = 0;
            int count = Owner->unknown_78;
            if (count > 0) {
                do {
                    BuildingAView* other = Owner->unknown_6C[i];
                    if (!other->unknown_81) {
                        BATypeView* ot = other->Type;
                        if (ot->unknown_EB8 == Type->unknown_EB8) {
                            if ((Type->unknown_CCE && ot->unknown_CCE) || (!Type->unknown_CCE && !ot->unknown_CCE)) {
                                other->unknown_3D3 = 0;
                            }
                        }
                    }
                    i++;
                } while (i < count);
            }
            unknown_3D3 = 1;
            if (Owner->FUN_0050B6F0()) {
                FUN_00752700(s_EVA_PrimaryBuildingSelected_00818F28, -1, -1);
            }
            if (Type->unknown_EB8 == 7) {
                Owner->FUN_0050DB00(this);
            }
        }
        vf_73(2);
        r = unknown_3D3;
    }
    return r;
}

// FUNCTION: GAMEMD 0x449A50
int BuildingAView::vf_145()
{
    HBCoord soundPos;
    HBCoord pos;
    switch (unknown_BC) {
    case 0: {
        FUN_00447780(0);
        vf_157(0xB);
        int sound = Type->unknown_E6C;
        if (sound != -1 || (sound = RulesInstance->unknown_6C8) != -1) {
            soundPos = Location;
            FUN_007509E0(sound, &soundPos, &unknown_6A0);
        }
        unknown_80 = 1;
        unknown_BC = 1;
        break;
    }
    case 1:
        unknown_80 = 1;
        pos = Location;
        FUN_00750D40(&pos, &unknown_6A0);
        if (unknown_6DD) {
            vf_157(0xC);
            vf_157(3);
            FUN_00447780(1);
            vf_311(0);
            vf_122(5, 0);
            if (!Type->unknown_16BF) {
                HBDir dir((unsigned char)Type->unknown_ED8);
                Facing.FUN_004C9300(&dir);
            }
            Type->FUN_00465AF0();
            unknown_6A0.FUN_00406060();
            return 1;
        }
        break;
    }
    return 1;
}
