// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x7438F0.

#include "unit_class_should_crash_methods.h"

// FUNCTION: GAMEMD 0x7438F0
//
// MATCHED (100.0%, 108/108). Retail's per-operand store/FILD interleave
// (store Y, compute Z, FILD Y, store Z, FILD Z) comes from binding each
// component of the CoordStruct difference to its own `double` local
// immediately after that component's store, and then writing the sum over the
// doubles; writing the casts inside the sum expression lets cl 12.00.8804
// batch both int stores and then both FILDs. Variants tried: the difference as
// three separate ints (84.3%), as a `volatile` CoordStruct (28.7% — volatile
// also breaks the FMUL/FLD duplication), and the casts inline (95.4%). The
// final compare needed the slot-0xC8 result bound to a `char` local and then to
// a named bool: spelled inline as `call(...) == 0` cl emits NEG/SBB/INC instead
// of retail's TEST AL,AL / SETZ AL (84.4%).
//
// UnitClass::ShouldCrashIt — decide whether this unit may run the candidate
// over. The unit's house type must allow crushing outright or the unit must
// answer capability 0x11; the candidate must exist and accept the unit; the
// straight-line distance between the two coordinate triples (taken through the
// by-value coordinate slot 0x48 of each) must be inside the rules limit; and
// the owning house must pass three further checks — a human/AI split crossed
// with the rules flag and the house type's second byte, a house state that is
// not 2, and a minimum count for AI houses. Only then is the candidate's own
// veto slot 0xC8 asked, and its answer is inverted into the result.
bool Obj_007438F0::ShouldCrashIt(Obj_007438F0* victim)
{
    if (this->At_6C4->At_D28 == 0 && !this->FUN_0070D0D0(0x11)) {
        return false;
    }

    if (victim != 0 && victim->FUN_005F6CD0(this)) {
        Coord_007438F0 there;
        Coord_007438F0 here;
        Coord_007438F0* a = (victim->*victim->Vtbl->At_048)(&there);
        Coord_007438F0* b = (this->*this->Vtbl->At_048)(&here);

        Coord_007438F0 d;
        d.X = b->X - a->X;
        d.Y = b->Y - a->Y;
        double dy = (double)d.Y;
        d.Z = b->Z - a->Z;
        double dz = (double)d.Z;
        double dx = (double)d.X;

        double dist = Sqrt_004CAC40(dx * dx + dz * dz + dy * dy);

        if ((int)dist <= RulesInstance_007438F0->At_1728) {
            if (this->At_21C->FUN_0050B730()
                && RulesInstance_007438F0->At_17EB == 0
                && this->At_6C4->At_D2D == 0) {
                return false;
            }
            if (this->At_21C->At_184 == 2) {
                return false;
            }
            if (!this->At_21C->FUN_0050B730()
                && this->At_21C->At_24C < RulesInstance_007438F0->At_1448) {
                return false;
            }
            char veto = (victim->*victim->Vtbl->At_0C8)(this->At_21C);
            bool ok = (veto == 0);
            return ok;
        }
    }

    return false;
}
