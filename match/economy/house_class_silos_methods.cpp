// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F9970.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) casts; reloc)

#include "house_class_silos_methods.h"

// FUNCTION: GAMEMD 0x4F9970
//
// Redraw every silo when the house's fill level changes. Both the previous
// and the current storage are reduced to a quarter-step (0..4, rounded) and
// nothing happens unless the step moved; then every live, on-map building of a
// silo-capable type is re-marked so its fill art updates.
void House_004F9970::UpdateAllSilos(int prevStorage, int prevTotalStorage)
{
    int before = 0;
    if (prevTotalStorage != 0) {
        before = (int)((double)prevStorage / prevTotalStorage * 4.0 + 0.5);
    }

    int after = 0;
    if (this->TotalStorage != 0) {
        after = (int)(this->OwnedTiberium.GetTotalAmount() / this->TotalStorage * 4.0 + 0.5);
    }

    if (before != after) {
        int count = this->BuildingCount;
        for (int i = 0; i < count; i++) {
            Building_004F9970* b = this->BuildingItems[i];
            if (b != 0 && !b->InLimbo && b->Type->At_16A8) {
                (b->*(*(BuildingVtbl_004F9970**)b)->Mark)(2);
            }
        }
    }
}
