// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x6A4710 and 0x6A48A0.
//
// SideClass bodies that serialise the +0x9C list (count at +0xA8).
// Address index: 0x6A4710 vf_13, 0x6A48A0 Save.

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x6A4710
void SideClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_A8);
}

// FUNCTION: GAMEMD 0x6A48A0
HRESULT __stdcall SideClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = unknown_A8;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++)
            pStm->Write(&unknown_9C[i], 4, 0);
        hr = 0;
    }
    return hr;
}
