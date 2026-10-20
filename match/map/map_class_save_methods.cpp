// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x551B20.

#include "map_class_save_methods.h"

// FUNCTION: GAMEMD 0x551B20  MapClass::Save (__thiscall, ret 0x4)
// IPersistStream::Save over the object list: write the element count, then each
// element pointer, bailing on the first failing HRESULT. The count is taken
// into a local before the first write and the loop bound reads that local, not
// the member — the Write call could have changed the object underneath.
Gg_HRESULT MapClass::Save(Gg_IStream* pStm)
{
    if (pStm == 0)
        return GG_E_POINTER;

    int count = Count;

    Gg_HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; i++) {
        hr = pStm->Write(&((void**)Items)[i], 4, 0);
        if (hr < 0)
            return hr;
    }

    return GG_S_OK;
}
