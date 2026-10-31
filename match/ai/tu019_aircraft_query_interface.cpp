// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x414290.
//
// AircraftClass::QueryInterface: the AbstractClass answer first; when it refuses and the id is the one at
// 0x7E9B40 (IFlyControl, the second base at +0x6C0), hand out that subobject. The reference is taken through
// the primary AddRef slot and the call reports success.
//
// Address index: 0x414290

#include <string.h>
#include "../_layout/aircraft_class.h"

// GLOBAL: GAMEMD 0x7E9B40 -- the IID compared by AircraftClass::QueryInterface.
extern const GUID DAT_007E9B40;

// FUNCTION: GAMEMD 0x414290
HRESULT __stdcall AircraftClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = AbstractClass::QueryInterface(riid, ppv);
    if (hr < 0) {
        if (memcmp(&riid, &DAT_007E9B40, sizeof(GUID)) == 0)
            *ppv = static_cast<IFlyControl*>(this);
        hr = S_OK;
        AddRef();
    }
    return hr;
}
