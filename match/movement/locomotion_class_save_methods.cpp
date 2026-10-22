// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp LocomotionClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x55AA60  SaveView_0055AA60::Save  (__stdcall)

#include "locomotion_class_save_methods.h"

// FUNCTION: GAMEMD 0x55AA60  (__stdcall)
//
// PARTIAL (67.5%): the instruction multiset agrees, but register assignment
// and scheduling differ. Retail holds pStm in ESI and this in EDI; this build
// swaps those registers. The shared done epilogue keeps the early null exit
// and common cleanup shape. Earlier byte-exact/92.5% comments were not
// reproduced by the second-look verification and have been removed.
HRESULT __stdcall SaveView_0055AA60::Save(Gg_IStream* pStm, LONG fClearDirty)
{
    HRESULT hr;
    void* self;
    if (pStm == 0)
    {
        hr = (HRESULT)0x80004003;          // E_POINTER
        goto done;
    }

    // Serialise the raw `this` pointer (4 bytes) as the load swizzle key.
    self = this;
    hr = pStm->Write(&self, 4, 0);
    if (hr >= 0)
    {
        // Serialise the object body: Size() bytes starting at `this`.
        hr = pStm->Write(this, this->Size(), 0);
        if (hr >= 0 && fClearDirty)
            *((char*)this + 0x11) = 0;     // clear dirty flag
    }
done:
    return hr;
}
