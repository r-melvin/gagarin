// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53D850. Method name
//   from YRpp (name only).

#include "ion_blast_draw_methods.h"

// FUNCTION: GAMEMD 0x53D850
//
// Draws every live ion blast. First the shared offset table is (re)built if
// the temp surface's pitch changed since last time: entry i is the pixel
// offset X + Y * pitch of the i-th square-spiral point, entry 0 the origin.
// Then the array is swept from the back, each blast drawing itself.
void IonBlastClass::DrawAll()
{
    if ((DSurface_Temp->*DSurface_Temp->Vtbl->GetPitch)() != IonBlastOffsetsPitch) {
        int pitch = (DSurface_Temp->*DSurface_Temp->Vtbl->GetPitch)();
        IonBlastOffsets[0] = 0;
        IonBlastOffsetsPitch = pitch;
        for (int i = 1; i < ION_BLAST_OFFSET_COUNT; i++) {
            Point2D pt = FUN_0053D8E0(i);
            IonBlastOffsets[i] = pt.X + pt.Y * pitch;
        }
    }

    for (int j = IonBlastArray.Count - 1; j >= 0; j--) {
        ((IonBlastClass**)IonBlastArray.Items)[j]->Draw();
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887314
Surface* DSurface_Temp;
// GLOBAL: GAMEMD 0xA9FAE8
int IonBlastOffsets[ION_BLAST_OFFSET_COUNT];
// GLOBAL: GAMEMD 0xAA0118
DynamicVectorClassLayout IonBlastArray;
// GLOBAL: GAMEMD 0xAA0150
int IonBlastOffsetsPitch;
// END defined globals
