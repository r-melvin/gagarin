// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A04B0, 0x4A05D0 and 0x4A0610.
//
// ConnectionPointClass IConnectionPoint bodies that only read fields.
// Address index: 0x4A04B0 QueryInterface, 0x4A05D0 GetConnectionInterface, 0x4A0610 GetConnectionPointContainer.

#include <string.h>
#include "../_layout/connection_point_class.h"

#pragma intrinsic(memcmp)

// GLOBAL: GAMEMD 0x7F7CD0 - IID_IConnectionPointContainer (SDK import library).
extern "C" const IID IID_IConnectionPointContainer;
// GLOBAL: GAMEMD 0x7F7C90 - IID_IUnknown
extern const GUID DAT_007F7C90;
// GLOBAL: GAMEMD 0x7F7CC0 - IID_IConnectionPoint
extern const GUID DAT_007F7CC0;

// FUNCTION: GAMEMD 0x4A04B0
HRESULT __stdcall ConnectionPointClass::QueryInterface(REFIID riid, void** ppvObject)
{
    if (ppvObject == 0)
        return E_POINTER;
    IUnknown* result = 0;
    if (memcmp(&riid, &DAT_007F7CC0, sizeof(GUID)) == 0 || memcmp(&riid, &DAT_007F7C90, sizeof(GUID)) == 0)
        result = this;
    *ppvObject = result;
    if (result) {
        result->AddRef();
        return 0;
    }
    return E_NOINTERFACE;
}

// FUNCTION: GAMEMD 0x4A05D0
HRESULT __stdcall ConnectionPointClass::GetConnectionInterface(IID* pIID)
{
    if (pIID == 0)
        return E_POINTER;
    *pIID = unknown_04;
    return 0;
}

// FUNCTION: GAMEMD 0x4A0610
HRESULT __stdcall ConnectionPointClass::GetConnectionPointContainer(IConnectionPointContainer** ppCPC)
{
    return unknown_18->QueryInterface(IID_IConnectionPointContainer, (void**)ppCPC);
}
