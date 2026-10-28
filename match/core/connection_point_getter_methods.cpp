// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A05D0 and 0x4A0610.
//
// ConnectionPointClass IConnectionPoint bodies that only read fields.
// Address index: 0x4A05D0 GetConnectionInterface, 0x4A0610 GetConnectionPointContainer.

#include "../_layout/connection_point_class.h"

// GLOBAL: GAMEMD 0x7F7CD0 - IID_IConnectionPointContainer (SDK import library).
extern "C" const IID IID_IConnectionPointContainer;

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
