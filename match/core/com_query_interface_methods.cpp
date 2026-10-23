// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IUnknown::QueryInterface body of a single-interface COM object. Each
// rejects a null out pointer, accepts the object's own interface id or the
// base IUnknown id (compared as sixteen raw bytes), hands out the object
// itself and takes a reference through its own AddRef slot.

#include <string.h>
#include <objbase.h>
#include "../_layout/swizzle_manager_class.h"

#pragma intrinsic(memcmp)

// GLOBAL: GAMEMD 0x7F7C90
extern const GUID DAT_007F7C90;
// GLOBAL: GAMEMD 0x7E9B20
extern const GUID DAT_007E9B20;

// FUNCTION: GAMEMD 0x6CF430
HRESULT __stdcall SwizzleManagerClass::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return 0x80004003;
    if (memcmp(&riid, &DAT_007E9B20, sizeof(GUID)) != 0
        && memcmp(&riid, &DAT_007F7C90, sizeof(GUID)) != 0)
        return 0x80004002;
    *ppv = this;
    AddRef();
    return 0;
}
