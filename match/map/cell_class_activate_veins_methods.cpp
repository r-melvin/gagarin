// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x486920.

#include <new.h>
#include "cell_class_activate_veins_methods.h"

// FUNCTION: GAMEMD 0x486920
//
// Wake the veins in a grown, flat vein cell the first time something
// vulnerable stands in it: a low-flying techno without vein immunity and
// without the ability that protects it gets the attack animation played at
// the cell centre, and the cell is flagged so it only happens once.
//
// Load-bearing: the map coordinate pair is copied whole into a local before
// its halves are used (retail spills the dword and reads Y back out of the
// spill), the coordinate arithmetic is written before the sub-cell offset
// so the shared half-cell constant is materialised after the shifts, the
// corner is a separate inline helper returning by value so the offsets come
// out as LEAs rather than in-place subtractions, and the techno flag is
// assigned inside the guard chain so it is stored to the frame while its
// own AND sets the flags.
void Cell_00486920::ActivateVeins()
{
    if (OverlayTypeIndex == 0x7E && OverlayData >= 0x30 && SlopeIndex == 0
        && !(Flags & 0x20000)) {
        bool techno;
        for (Obj_00486920* obj = FirstObject; obj != 0; obj = obj->NextObject) {
            if ((obj->*obj->Vptr->GetHeight)() <= 5 && obj != 0
                && (techno = (obj->AbstractFlags & 1) != 0) != false) {
                if (techno
                    && !(obj->*obj->Vptr->GetTechnoType)()->At_C91
                    && !obj->FUN_0070D0D0(8)) {
                    Anim_00486920* anim =
                        (Anim_00486920*)operator new(sizeof(Anim_00486920));
                    if (anim != 0) {
                        Coord_00486920 at = GetCornerCoords();
                        anim->Construct(DAT_008871E0->At_E8, &at, 0, 1, 0x600, 0, 0);
                    }
                    Flags |= 0x20000;
                }
            }
        }
    }
}
