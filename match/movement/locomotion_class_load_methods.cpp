// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55AAC0.

#include "locomotion_class_load_methods.h"

// FUNCTION: GAMEMD 0x55AAC0
//
// IPersistStream::Load for a locomotor. Read the saved object id, register
// this object as its replacement, then overwrite the object wholesale with the
// saved image (its own Size() bytes) while keeping the +0x14 member, and queue
// the two pointer members for swizzling.
//
// The id lands in the dead `pStm` parameter slot: `pStm` lives in EDI after
// the null check, so retail reads the four bytes into [ESP+0xC] and reloads
// them from there.
//
// The first HRESULT is tested in EAX and returned as-is on failure, so it is
// an early return; folding the body into `if (hr >= 0)` makes VC6 park hr in
// EBX and push the callee-saves before the first Read (15.4%).
HRESULT __stdcall FUN_0055AAC0(Loco_0055AAC0* self, IStream_0055AAC0* pStm)
{
    if (pStm == 0) {
        return 0x80004003;
    }

    int id;
    HRESULT hr = pStm->Read(&id, 4, 0);

    if (hr < 0) {
        return hr;
    }

    DAT_00B0C110.FUN_006CF2C0(id, self);

    void* keep = self->At_14;
    hr = pStm->Read(self, (self->*self->Vtbl->At_24)(), 0);
    self->At_14 = keep;

    DAT_00B0C110.FUN_006CF240(&self->At_C);
    DAT_00B0C110.FUN_006CF240(&self->At_8);

    return hr;
}
