// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x43E7B0.

#include "building_class_info_tip_methods.h"

// FUNCTION: GAMEMD 0x43E7B0
//
// Draw the hover information over a discovered building: the selection box
// for an ally or for a house that has spied this one, and, for a spied
// building that is producing something, the name of what it is building.
//
// PARTIAL (29.5%, 105 versus 100 instructions, five of a kind apart). The
// out-parameter call, the ally-or-spy test, the tip position built by a
// two-argument constructor into the slot the out buffer just vacated, the
// factory selection and the fourteen-argument text draw all match. The
// residual is retail materialising the repeated zero argument into EBX
// (with its own deferred push and pop inside the final block) and a second
// zero into ESI, where cl 8804 pushes the immediates directly; that also
// frees EBX for the flags parameter, which retail keeps in EBP. The same
// materialised-push-constant difference is recorded for the NearByLocation
// call sites. Tried: the out buffer scoped to its own block (kept; it is
// what makes the tip reuse the slot and the frame eight bytes), both
// operand orders for the spied-by bit test, and the flags parameter read
// once versus at each use.
// Lift pass 2 (2026-09-18): classified, not re-chased. The residual is entirely
// the banked 8447-vs-8804 "repeated push constants materialised into
// registers" class (shared with 0x74D490, 0x4FBF60, 0x703590, 0x41A2C0); a
// flag bisection over /O1, /O2 /Os, /Ox and /O2 /Gs on the sibling 0x74D490
// showed no flag set makes cl 8804 materialise those constants, so it is the
// compiler build, not the switches. Best form kept at 29.5%.
void Building_0043E7B0::DrawInfoTipAndSpiedSelection(Point_0043E7B0* pos,
                                                     unsigned int flags)
{
    {
        Point_0043E7B0 unused;
        (this->*Vptr->At_1B8)(&unused);
    }

    if (IsDiscovered) {
        if (Owner->IsAlliedWith(DAT_00A83D4C)
            || ((1 << DAT_00A83D4C->Type->ArrayIndex) & SpiedBy)) {
            (this->*Vptr->At_458)(Point_0043E7B0(pos->X - 10, pos->Y + 10),
                                  pos, flags);
        }
    }

    if (((1 << DAT_00A83D4C->Type->ArrayIndex) & SpiedBy) && IsDiscovered) {
        Object_0043E7B0* factory;
        if (Owner->FUN_0050B730()) {
            factory = Owner->FUN_00500510(Type->At_EB8, Type->Naval, 0);
        } else {
            factory = Factory;
        }
        if (factory != 0) {
            Object_0043E7B0* object = FUN_004CA160(factory);
            if (object != 0) {
                Type_0043E7B0* type = (object->*object->Vptr->GetTechnoType)();
                FUN_004AED70(DAT_00887314, DAT_0087F6C4,
                             (type->*type->Vptr->GetUIName)(), 0, pos, flags,
                             0xE00, 0, 0, 0, 1000, 0, 0, 0, 0, 0);
            }
        }
    }
}
