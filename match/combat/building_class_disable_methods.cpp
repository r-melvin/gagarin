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
void BuildingClass::DisableStuff()
{
    StuffEnabled = 0;
    if (LightSource != 0)
        LightSource->FUN_00554A80(0);
    BuildingTypeClass* type = Type;
    if (type->bools_16A4[0x16C7 - 0x16A4]) {
        HasCloakingData = -1;
        if (CloakRadius == 0)
            CloakRadius = type->CloakRadiusInCells;
        NeedsRedraw = 1;
    }
    if (type->GapGenerator && GeneratingGap)
        vf_262();
    if (Type->bools_16A4[0x16BE - 0x16A4])
        CreateEndPost(0);
    for (int i = 0; i < 0x15; ++i) {
        if (Type->BuildingAnim[i].Powered && Anims[i])
            Anims[i]->FUN_00425260();
    }
}
