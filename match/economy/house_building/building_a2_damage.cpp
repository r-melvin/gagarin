// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot 91 of the building-a2 cluster: BuildingClass::ReceiveDamage. Read from the retail gamemd.exe
//   v1.001 from its entry to its last RET with a LINEAR decode of the retail bytes (Ghidra's function-flow
//   listing drops instructions after some calls); offsets are pinned in building_a2_views.h. Method names are
//   slot labels (vf_N = primary-table byte offset / 4).

#include "building_a2_views.h"

// The animation-name refresh the original expanded twice: the health ratio against the rules threshold
// decides which of the two names of every damage-state animation slot is shown.
inline void BA2Building::RefreshAnimStates()
{
    double ratio = FUN_005F5C60();
    bool low = ratio <= RulesInstance_8871E0->unknown_1700;
    if (unknown_6E6 != low) {
        unknown_6E6 = low;
        for (int i = 0; i < 0x15; i++) {
            if (Anims[i]) {
                char* name = low ? Type->unknown_F4C[i].Low : Type->unknown_F4C[i].Normal;
                if (name && *name) {
                    FUN_00451890(name, i, low, 0, 0);
                }
            }
        }
    }
}

// CAPPED (partial, readable): 60.8% of the retail instructions align (69.1% with stack offsets ignored; 77.0% with
// registers also ignored).
// Remaining delta: retail keeps the zero constant in EBX (the first loop counter) and the attacker in EBP, ours puts
// zero in EBP and the attacker in EDI, so every null test is `cmp r,ebp` instead of `test r,r` and every push of
// zero differs; the two expansions of the health-ratio refresh are cross-jumped in ours but duplicated in retail;
// the animation constructor arguments are scheduled differently (counter call before the zero pushes).
// Variants tried: declaration points of the loop counter, the case order (retail order 5, 4, 2/3 matched), compound
// early returns, vector shapes (inline destructor, vtable stores matched), inline helper vs duplicated source.
// FUNCTION: GAMEMD 0x442230
// Slot 91, ReceiveDamage: the base-class damage run decides the resulting damage state; this override adds
// the occupant bookkeeping and the destruction / state-change reactions on top.
int BA2Building::vf_91(int* damage, int distance, BA2Warhead* warhead, BA2Obj* attacker, bool ignoreDefenses,
                       bool preventsPassengerEscape, BA2House* sourceHouse)
{
    int result = 0;

    if (this == attacker && !attacker->vf_33()->unknown_CA0) {
        return result;
    }
    FUN_005F5C60();
    int stateBefore = FUN_0043EF90();
    int i = 0;

    if (attacker && !vf_32()) {
        Owner->unknown_54D8 = Frame_A8ED84;
        Owner->unknown_54DC = attacker->vf_15()->unknown_30;
        FUN_00708080(attacker);
    }

    HBCell* cells = vf_66(0);
    BA2DynVector<BA2Occupant*> occupants;
    for (; i < unknown_E8; i++) {
        BA2Occupant* occupant = FUN_0065AD30(i);
        if (occupant) {
            occupants.AddItem(occupant);
        }
    }

    if (Type->unknown_16BF && !ignoreDefenses) {
        return 0;
    }
    if (Type->unknown_16B6 && Type->unknown_233) {
        return 0;
    }

    if (unknown_6C) {
        result = FUN_00701900(damage, distance, warhead, attacker, ignoreDefenses, preventsPassengerEscape, sourceHouse);
        if (!unknown_90) {
            return result;
        }
        switch (result) {
        case 5:
            return result;
        case 4:
            if (unknown_2E4) {
                occupants.RemoveItem(unknown_2E4);
                FUN_004593A0();
            }
            if (unknown_2BC) {
                unknown_2BC->FUN_00472140();
            }
            if (unknown_2AC) {
                FUN_0070FEE0(1);
            }
            for (i = 0; i < occupants.Count; i++) {
                BA2Occupant* occupant = occupants.Items[i];
                HBCoord a, b, c;
                HBCoord* from = occupant->vf_18(&a);
                HBCoord* to = vf_18(&b);
                HBCoord delta = *c.FUN_0041C230(to->X - from->X, to->Y - from->Y, to->Z - from->Z);
                if (delta.FUN_0041C380() >= 256 && !Type->unknown_16CB) {
                    vf_158(0x17, occupant);
                    occupant->unknown_500 = 0;
                } else {
                    int hurt = occupant->vf_33()->unknown_A0 * 10;
                    occupant->vf_91(&hurt, 0, RulesInstance_8871E0->unknown_FA8, 0, true, true, 0);
                }
            }
            {
                int capacity = occupants.Capacity;
                occupants.Clear();
                occupants.SetCapacity(capacity, 0);
            }
            if (Type->unknown_157B) {
                FUN_00457DE0(0, 0);
            }
            if (LightSource) {
                LightSource->FUN_00554A80(0);
            }
            vf_315(0, attacker, ignoreDefenses, cells);
            {
                int left = unknown_530;
                if (unknown_528 != -1) {
                    int elapsed = Frame_A8ED84 - unknown_528;
                    if (elapsed >= left) {
                        break;
                    }
                    left -= elapsed;
                }
                if (left > 0) {
                    vf_62();
                    FUN_00441F60();
                }
            }
            break;
        case 2:
            if (unknown_30C) {
                unknown_30C->unknown_E8 = unknown_30C->unknown_E8 * 1.5f;
            }
            // fall through
        case 3:
            if (vf_33()->unknown_538 == -1) {
                HBCoord where = Location;
                FUN_00750E20(RulesInstance_8871E0->unknown_714, &where, 0);
            }
            while (!(cells->X == 0x7FFF && cells->Y == 0x7FFF)) {
                HBCell offset = *cells++;
                HBCell here = vf_110();
                HBCoord pos;
                pos.X = (short)(offset.X + here.X) * 256 + 128;
                pos.Y = (short)(offset.Y + here.Y) * 256 + 128;
                pos.Z = 0;
                pos.Z = DAT_0087F7E8.FUN_00578080(&pos);
                if (!warhead->unknown_14A) {
                    continue;
                }
                int rows = Type->FUN_0045ECA0(0);
                switch (DAT_00A8B230->Counter.FUN_0065C7E0(0, rows + Type->FUN_0045EC90() + 5)) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    {
                        HBCoord scatter;
                        BA2Anim* anim = new BA2Anim(RulesInstance_8871E0->unknown_B78[0],
                                                    FUN_0049F420(&scatter, &pos, 0x60, 0), 0,
                                                    DAT_00A8B230->Counter.FUN_0065C7E0(1, 3), 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                case 6:
                case 7:
                case 8:
                    {
                        HBCoord scatter;
                        BA2Anim* anim = new BA2Anim(RulesInstance_8871E0->unknown_B78[1],
                                                    FUN_0049F420(&scatter, &pos, 0x60, 0),  0,
                                                    DAT_00A8B230->Counter.FUN_0065C7E0(1, 3), 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                case 9:
                    {
                        HBCoord scatter;
                        BA2Anim* anim = new BA2Anim(RulesInstance_8871E0->unknown_B78[2],
                                                    FUN_0049F420(&scatter, &pos, 0x60, 0), 0, 1, 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    if (!unknown_90) {
        return 4;
    }
    if (attacker) {
        if (result) {
            if (!Type->unknown_232 && !vf_32()) {
                Owner->FUN_004F93E0(this);
            }
            unknown_53C = attacker->vf_15()->unknown_30;
            if (unknown_AC != 0x13 && !Owner->FUN_004F9A90(attacker) && vf_254(0)->First
                && !vf_254(0)->First->ObjType->unknown_2A4 && (!unknown_2B4 || !vf_235(unknown_2B4))) {
                if (attacker->vf_11() == 2 || (Owner->FUN_0050B730() && !RulesInstance_8871E0->unknown_17EC)) {
                    if (!Facing.FUN_004C9480() && vf_212()) {
                        BA2Dir dir;
                        dir.Raw = 0;
                        dir.Bytes.Hi = DAT_00A8B230->Counter.FUN_0065C780();
                        Facing.FUN_004C9220(&dir);
                    }
                } else {
                    vf_242(attacker);
                }
            }
        }
    }
    if (result) {
        RefreshAnimStates();
    }
    if (stateBefore != FUN_0043EF90()) {
        unknown_80 = 1;
        RefreshAnimStates();
    }
    return result;
}
