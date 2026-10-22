// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
// CAPPED (final) at 11.5% positional (39/339), 56.3% by sequence alignment; all 30 calls are in retail order and the frame (0x44)
// matches. Delta: retail keeps the 12-byte result of FUN_0070BCB0 and the copy `c` in one stack slot (c.X/c.Y in EDI/EBX, only c.Z
// written back at +0x4C) while the compiled code gives the temporary (+0x38) and `c` their own slots; the muzzle copy, the squared
// difference struct and the pair temporaries then sit at other offsets, the final direction copy goes through a temporary where
// retail stores the 0x4000 word straight into the hidden result, and the register assignment of the scalar copies differs.
// Variants tried (three materially different families, ~12 forms): copy through a pointer into named locals, the by-value return of the
// temporaries, const-reference binding of the temporary, struct copies against scalar locals, the muzzle Z written before the call
// result (matches retail's single slot for fz and m.Z), a nested pair argument (gets the retail frame), all 24 declaration orders
// of the four locals (identical code), copy-constructor / constructor forms of the 4-byte direction return.

#include "building_a3_views.h"

// FUNCTION: GAMEMD 0x43E940
HBDir BuildingA3View::vf_178(BA3ObjView* target)
{
    if (vf_254(0)->First->unknown_149) {
        vf_33();
        if (target) {
            HBCoord c = FUN_0070BCB0();
            HBCoord m;
            m.Z = vf_254(0)->unknown_0C;
            HBCoord tmp;
            HBCoord* pm = vf_43(&tmp);
            m.X = pm->X;
            m.Y = pm->Y;
            m.Z += pm->Z;
            HBPoint2D out2;
            HBPoint2D* r = DAT_00887324->FUN_006D2070(&out2, &Type->unknown_11E0);
            HBCoord diff;
            diff.X = c.X - (m.X + r->X);
            diff.Y = c.Y - (m.Y + r->Y);
            diff.Z = c.Z - m.Z;
            if (diff.Z == 0) {
                return HBDir((short)0x4000);
            }
            double h = (double)(diff.Y * diff.Y + diff.X * diff.X);
            double flat = FUN_004CAC40(h);
            int len = (int)FUN_004CAC40((double)diff.X * diff.X + (double)diff.Z * diff.Z + (double)diff.Y * diff.Y);
            double ratio = flat / len;
            if (ratio > DAT_007E1718) {
                ratio = 1.0;
            }
            HBDir d;
            d.Raw = (short)(int)(FUN_004CAD80(ratio) * DAT_007E4418 * DAT_007E4410);
            if (diff.Z < 0) {
                d.Raw = (short)(-0x8000 - d.Whole);
            }
            return d;
        }
        return Facing370.FUN_004C93D0();
    }
    if (Type->unknown_16C3) {
        DAT_0087F7E8.FUN_00578080(target->vf_18());
        HBCoord t = target->vf_18();
        HBCoord zero;
        zero.X = 0;
        zero.Y = 0;
        zero.Z = 0;
        HBCoord rc = vf_44(0, zero);
        FUN_004CAE30((double)rc.Y - t.Y, (double)t.X - rc.X);
        int a = FUN_005F6360(target)->FUN_0048AB90((double)RulesInstance->unknown_16B8);
        HBCoord g = vf_192(0);
        HBCoord pe = target->vf_18();
        HBCoord e;
        e.X = pe.X - g.X;
        e.Y = pe.Y - g.Y;
        e.Z = pe.Z - g.Z;
        double sq = (double)(e.Y * e.Y + e.X * e.X);
        HBDir d;
        if (!FUN_0048A8D0(FUN_0070D590(0), a, (int)FUN_004CAC40(sq), e.Z, (double)RulesInstance->unknown_16B8, &d)) {
            FUN_0048A8D0(FUN_0070D590(0), a * 10 / 8, (int)FUN_004CAC40(sq), e.Z, (double)RulesInstance->unknown_16B8, &d);
        }
        return d;
    }
    return FUN_006FDA00(target);
}
