// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x551B90.

#include "layer_class_load_methods.h"

// FUNCTION: GAMEMD 0x551B90
//
// LayerClass::Load, the counterpart of LayerClass::Save (0x551B20); its callers
// DisplayClass::Load (0x4AE6F0) and 0x67E730 pass each layer in ECX. Load the
// layer's pointer vector from a stream: the element count, then each saved
// pointer appended through AddItem, then every element queued with the
// swizzle manager so the saved pointers are remapped to the reloaded
// objects. A null stream is E_POINTER; a failed read returns its HRESULT.
//
// The count lands in the dead `pStm` parameter slot (pStm lives in EDI after
// the null check) and each element in the one frame local; both reads are
// early returns on a negative HRESULT.
HRESULT LayerClass::Load(IStream_00551B90* pStm)
{
    if (pStm == 0) {
        return 0x80004003;
    }

    int count = 0;
    HRESULT hr = pStm->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }

    for (int i = 0; i < count; i++) {
        void* item;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0) {
            return hr;
        }
        this->AddItem(item);
    }

    for (int j = 0; j < count; j++) {
        DAT_00B0C110.FUN_006CF240(&this->Items[j]);
    }

    return 0;
}
