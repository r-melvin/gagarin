// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 315 (+0x4EC): the destruction effects of a building. Span 0x4415F0..0x441F57
//   (0x967 bytes, one RET epilogue, no tables). The method names are slot labels / FUN_<addr>; no original name is
//   confirmed.
// CAPPED (final) at 4.3% positional (29/679), 39.8% by sequence alignment; all 64 calls are in retail order and the frame (0x54) matches.
// Delta: the constant 0 sits in EBP in the compiled code and in EBX in retail (and the 8-count anim loop counter in EBX against
// EBP), so every `cmp r,0` / `push 0` differs; the cell-centre coordinate argument is built before the stack arguments are pushed in the
// compiled code and after them in retail (a constructor-style temporary evaluated inside the call); the vector tail AddItem /
// destructor expansion and the stack offsets follow. Retail also stores a stack word that is not always written (the middle word
// of the last scatter result) into the middle word of the 528/100 timers; that read is indeterminate, so the source leaves the middle
// word unchanged instead.
// Variants tried: counted do/while against an index loop, pointer loop, inline cell-centre helper by value / by reference / field-by-field
// with the copy of Location first, the vector item added by value / by reference, signed and unsigned moduli.

#include "building_a3_views.h"

// One cell of the 256-lepton grid as its centre lepton: the retail code divides by 256 (rounding towards zero),
// narrows to 16 bits, and scales back.
inline int BA3CellCentre(int lepton)
{
    return (short)(lepton / 256) * 256 + 0x80;
}

// The element type is complete in the original; here only the one field read is viewed.
inline const BA3ParticleTypeView* BA3ParticleType(const ParticleSystemTypeClass* type)
{
    return reinterpret_cast<const BA3ParticleTypeView*>(type);
}

// FUNCTION: GAMEMD 0x4415F0
void BuildingA3View::vf_315(int unused, int a, char flag, short* list)
{
    for (int i = 0; i < 8; ++i) {
        if (DamageFireAnims[i]) {
            DamageFireAnims[i]->vf_62();
            DamageFireAnims[i] = 0;
        }
    }

    if (unknown_210) {
        unknown_210 = 0;
        if (Type->unknown_16A4) {
            Owner->unknown_54E4 = 0;
            for (int i = 0; i < Owner->unknown_78; ++i) {
                BuildingA3View* other = Owner->unknown_6C[i];
                if (other && !other->unknown_81 && other->Type->unknown_16A4) {
                    Owner->unknown_54E4 |= other->unknown_210;
                }
            }
            DAT_0087F7E8.FUN_004F42F0(2);
        }
    }

    if (Type->unknown_16C7) {
        unknown_6EB = 0xFF;
        if (!unknown_6EC) {
            unknown_6EC = Type->unknown_1707;
        }
        unknown_80 = 1;
        unknown_6EC = 1;
        vf_260(1);
    }

    if (Type->unknown_16BE) {
        FUN_00452A40(1);
    }

    if (Type->unknown_5EE && !Owner->FUN_0050B6F0()) {
        vf_291(0, 0, 1, DAT_00A83D4C);
    }

    if (vf_33()->unknown_510.unknown_10 == 0) {
        HBCoord where = Location;
        FUN_00750E20(RulesInstance->unknown_6E8, &where, 0);
    }

    if (Type->FUN_0045EC90() >= 2 && Type->FUN_0045ECA0(0) >= 2) {
        if (Type->FUN_0045EC90() > 2) {
            DAT_00A8B230->Counter.FUN_0065C7E0(0, Type->FUN_0045EC90() - 2);
        }
        if (Type->FUN_0045ECA0(0) > 2) {
            DAT_00A8B230->Counter.FUN_0065C7E0(0, Type->FUN_0045ECA0(0) - 2);
        }
        if (DAT_00A8B230->Counter.FUN_0065C7E0(0, 99) < 50) {
            HBCoord at;
            at.Z = 0;
            HBCoord loc = Location;
            at.X = BA3CellCentre(loc.X);
            at.Y = BA3CellCentre(loc.Y);
            FUN_006B59A0(at, 100, 100, 1);
        } else {
            HBCoord at;
            at.Z = 0;
            HBCoord loc = Location;
            at.X = BA3CellCentre(loc.X);
            at.Y = BA3CellCentre(loc.Y);
            FUN_006B5C90(at, 100, 100, 1);
        }
    }

    HBCoord scatter;
    while (list[0] != 0x7FFF || list[1] != 0x7FFF) {
        short* entry = list;
        list += 2;
        HBCoord tmp;
        HBCoord* centre = vf_43(&tmp);
        short x = (short)(centre->X / 256) + entry[0];
        short y = entry[1] + (short)(centre->Y / 256);
        if (Type->unknown_72C.Count > 0) {
            HBCoord at;
            at.X = (short)x * 256 + 0x80;
            at.Y = (short)y * 256 + 0x80;
            HBCoord loc = Location;
            at.Z = 0;
            HBCoord* p = FUN_0049F420(&scatter, &at, 0x40, 0);
            HBCoord spawn;
            spawn.X = p->X;
            spawn.Y = p->Y;
            spawn.Z = p->Z + loc.Z;
            BA3AnimMem* mem = new BA3AnimMem;
            if (mem) {
                int delay = DAT_00A8B230->Counter.FUN_0065C7E0(0, 3);
                BA3TypeView* type = Type;
                mem->FUN_00421EA0(type->unknown_72C.Items[DAT_00A8B230->Counter.FUN_0065C780() % type->unknown_72C.Count],
                                  &spawn, delay, 1, 0x600, 0, 0);
            }
        }
    }

    if (Type->unknown_D15) {
        for (int* offset = DAT_00818CB8; offset < DAT_00818CB8 + 4; ++offset) {
            HBCoord loc = Location;
            HBCoord cellAt = *FUN_0049F550(&scatter, &loc, *offset);
            if (DAT_0087F7E8.FUN_00565730(&cellAt)->unknown_44 != -1
                && DAT_00A83D84[DAT_0087F7E8.FUN_00565730(&cellAt)->unknown_44]->unknown_2B0) {
                BA3AnimMem* mem = new BA3AnimMem;
                if (mem) {
                    int delay = DAT_00A8B230->Counter.FUN_0065C7E0(1, 3);
                    mem->FUN_00421EA0(DAT_008B4154[FUN_00427CB0(s_FIRE3_00818E00)], &cellAt, delay + 3, 1, 0x600, 0, 0);
                }
            }
        }
    }

    while (unknown_33C.FUN_006C9650() >= DAT_007E2AC8) {
        int index = unknown_33C.FUN_006C9820();
        unknown_33C.FUN_006C96B0(1.0f, index);
        Owner->unknown_2FC.FUN_006C96B0(1.0f, index);
        int distance = DAT_00A8B230->Counter.FUN_0065C7E0(0x100, 0x300);
        HBCoord loc = Location;
        HBCoord shot = *FUN_0049F420(&scatter, &loc, distance, 1);
        DAT_0087F7E8.FUN_00565730(&shot)->FUN_00487190(index, 1);
    }

    int amount = Type->vf_33(Owner) / RulesInstance->unknown_5C8;
    if (amount > 0) {
        FUN_0048DED0(amount);
    }

    if (vf_97() == 0x13 || Type->unknown_D15) {
        unknown_528.X = DAT_00A8ED84;
        unknown_528.Z = 0;
        unknown_100.X = DAT_00A8ED84;
        unknown_100.Z = 0;
        unknown_10C = 0;
    } else {
        unknown_528.X = DAT_00A8ED84;
        unknown_528.Z = 8;
    }

    if (Type->unknown_748.Count > 0) {
        const BA3AnimTypeView* animType =
            Type->unknown_748.Items[DAT_00A8B230->Counter.FUN_0065C780() % Type->unknown_748.Count];
        if (animType) {
            BA3AnimMem* mem = new BA3AnimMem;
            BA3AnimView* anim;
            if (mem) {
                HBCoord tmp;
                anim = mem->FUN_00421EA0(animType, vf_43(&tmp), 0, 1, 0x600, 0, 0);
            } else {
                anim = 0;
            }
            if (vf_33()->unknown_DF0) {
                anim->unknown_D4 = vf_121();
                if (Type->unknown_DD0) {
                    strncpy(anim->unknown_DC, &Type->unknown_DD0, 0x20);
                }
            }
        }
    }

    DynamicVectorClass<const ParticleSystemTypeClass*> systems(0, 0);
    for (int k = vf_33()->unknown_794.Count - 1; k >= 0; --k) {
        if (BA3ParticleType(vf_33()->unknown_794.Items[k])->unknown_2B4 == 0) {
            BA3AddItem(systems, vf_33()->unknown_794.Items[k]);
        }
    }

    if (unknown_320 == 0 && systems.Count > 0 && vf_114() > -10) {
        HBCoord offset = vf_33()->unknown_7C0;
        BA3ParticleMem* mem = new BA3ParticleMem;
        BA3ParticleView* made;
        if (mem) {
            HBCoord at;
            at.X = Location.X + offset.X;
            at.Y = Location.Y + offset.Y;
            at.Z = Location.Z + offset.Z;
            made = mem->FUN_0062DC50(systems.Items[DAT_00A8B230->Counter.FUN_0065C7E0(0, systems.Count - 1)], &at, 0, this,
                                      &DAT_0089C848, 0);
        } else {
            made = 0;
        }
        unknown_320 = made;
    }

    unknown_6C = 0;
    if (flag) {
        unknown_6E0 = 1;
    }
    FUN_00442D90(C4AppliedBy);
    FUN_00707CB0(a);
}
