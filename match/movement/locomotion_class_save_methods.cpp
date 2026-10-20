// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp LocomotionClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x55AA60  LocomotionClass::Save  (__stdcall)

#include "locomotion_class_save_methods.h"

// FUNCTION: GAMEMD 0x55AA60  (__stdcall)
//
// The shared `done:` epilogue is load-bearing: it forces cl to preserve the
// non-volatile EDI in the prologue (push EDI before the null-branch, pop EDI in
// the inline E_POINTER tail) exactly as retail does, instead of shrink-wrapping
// the save into the success path. With this shape the whole body is byte-exact.
//
// RESIDUAL (bool-delta, toolchain register-allocation): retail (cl build 8447)
// places pStm in ESI and `this` in EDI; our compiler swaps them
// (pStm->EDI, this->ESI). The three prologue setup instructions differ only by
// that ESI<->EDI choice; every other byte (control flow, the two IStream::Write
// thiscalls, Size(), the dirty-flag clear, the epilogue) is identical. 92.5%.
HRESULT __stdcall LocomotionClass::Save(Gg_IStream* pStm, LONG fClearDirty)
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
