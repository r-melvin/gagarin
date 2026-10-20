// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x452480.

#include "building_class_disable_methods.h"

// FUNCTION: GAMEMD 0x452480  BuildingClass::DisableStuff
//
// Everything a powered-down building stops doing: the light goes off, a cloak
// generator drops its field (remembering the radius if it had none yet), a
// charged gap generator is collapsed through the virtual, the sensor-style
// flag on the type gets its off call, and every enabled per-slot animation is
// halted.
void Building_00452480::DisableStuff()
{
    At_6EA = 0;
    if (LightSource != 0)
        LightSource->FUN_00554A80(0);

    BuildingType_00452480* type = Type;
    if (type->CloakGenerator) {
        At_6EB = -1;
        if (CloakRadius == 0)
            CloakRadius = type->CloakRadiusInCells;
        NeedsRedraw = 1;
    }

    if (type->GapGenerator && At_269)
        (this->*this->Vptr->At_418)();

    if (Type->At_16BE)
        FUN_004533A0(0);

    for (int i = 0; i < 21; ++i) {
        if (Type->Anims[i].Enabled && Anims[i])
            Anims[i]->FUN_00425260();
    }
}
