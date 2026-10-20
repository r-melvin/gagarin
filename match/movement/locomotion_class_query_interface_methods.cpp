// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55A9B0.

#include <string.h>
#include "locomotion_class_query_interface_methods.h"

#pragma intrinsic(memcmp)

// FUNCTION: GAMEMD 0x55A9B0
//
// IUnknown::QueryInterface for a locomotor. The four interface ids are tested
// one after another (no early exit between them - each compare is a separate
// `REPE CMPSD` block and a later match overwrites an earlier one), then the
// result is checked once and AddRef'd through the primary vptr.
//
// The casts to the +4 base carry VC6's null-safe adjustment, which is the
// `TEST EDX,EDX / LEA ECX,[EDX+4] / XOR ECX,ECX` retail has on those two arms.
HRESULT __stdcall FUN_0055A9B0(Loco_0055A9B0* self, const Guid_0055A9B0* riid,
                               void** ppv)
{
    if (ppv == 0) {
        return 0x80004003;
    }

    *ppv = 0;

    if (memcmp(riid, &IID_IUnknown_007F7C90, sizeof(Guid_0055A9B0)) == 0) {
        *ppv = static_cast<ILocomotion_0055A9B0*>(self);
    }
    if (memcmp(riid, &IID_IPersistStream_007F7C80, sizeof(Guid_0055A9B0)) == 0) {
        *ppv = static_cast<IPersistStream_0055A9B0*>(self);
    }
    if (memcmp(riid, &IID_ILocomotion_007ED358, sizeof(Guid_0055A9B0)) == 0) {
        *ppv = static_cast<ILocomotion_0055A9B0*>(self);
    }
    if (memcmp(riid, &IID_IPersist_007F7C70, sizeof(Guid_0055A9B0)) == 0) {
        *ppv = static_cast<IPersistStream_0055A9B0*>(self);
    }

    if (*ppv == 0) {
        return 0x80004002;
    }

    static_cast<IPersistStream_0055A9B0*>(self)->AddRef();
    return 0;
}
