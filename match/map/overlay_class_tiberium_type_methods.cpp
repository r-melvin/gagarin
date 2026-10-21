// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5FDD20.

#include "overlay_class_tiberium_type_methods.h"

// FUNCTION: GAMEMD 0x5FDD20
//
// Map an overlay type index to the tiberium it belongs to. No overlay, or one
// that is not flagged as tiberium, gives -1. Otherwise each tiberium claims two
// consecutive index ranges starting at its image's own index — the flat frames
// and then the slope frames — and the first tiberium whose ranges contain the
// index wins. A flagged overlay that no tiberium claims is logged (the name
// travels by value) and reported as tiberium 0.
int __fastcall OverlayClass::GetTiberiumType(int idxOverlay)
{
    OverlayType_005FDD20* type;
    if (idxOverlay == -1 || (type = (OverlayType_005FDD20*)DAT_00A83D84[idxOverlay])->Tiberium == 0) {
        return -1;
    }

    for (int i = 0; i < DAT_00B0F4F8; ++i) {
        Tiberium_005FDD20* tiberium = DAT_00B0F4EC[i];
        int first = tiberium->Image->ArrayIndex;
        if (idxOverlay >= first && idxOverlay < first + tiberium->NumImages) {
            return tiberium->ArrayIndex;
        }
        if (idxOverlay >= first + tiberium->NumImages
            && idxOverlay < first + tiberium->NumImages + tiberium->NumSlopes) {
            return tiberium->ArrayIndex;
        }
    }

    FUN_004068E0(STR_00833490, type->Name);
    return 0;
}
