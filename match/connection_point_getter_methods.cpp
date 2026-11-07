// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A04B0, 0x4A05D0 and 0x4A0610.
//
// ConnectionPointClass IConnectionPoint bodies that only read fields.
// Address index: 0x4A04B0 QueryInterface, 0x4A05D0 GetConnectionInterface, 0x4A0610 GetConnectionPointContainer.

#include <string.h>
#include "_layout/connection_point_class.h"
#include "vector_class_operations.h"
#include "_layout/scenario_ptr_00a8b230.h"

// GLOBAL: GAMEMD 0xA8B230 -- the current scenario; 0x68BCB0 hands out the next advise cookie (its +0x214 counter).
int FUN_0068BCB0(ScenarioClass* self);   // GAMEMD 0x68BCB0 (decl; reloc)


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
    *pIID = Iid;
    return 0;
}

// FUNCTION: GAMEMD 0x4A0610
HRESULT __stdcall ConnectionPointClass::GetConnectionPointContainer(IConnectionPointContainer** ppCPC)
{
    return Container->QueryInterface(IID_IConnectionPointContainer, (void**)ppCPC);
}

// FUNCTION: GAMEMD 0x4A0630
HRESULT __stdcall ConnectionPointClass::Advise(IUnknown* pUnkSink, DWORD* pdwCookie)
{
    if (pUnkSink == 0 || pdwCookie == 0)
        return E_POINTER;
    tagCONNECTDATA data;
    data.dwCookie = FUN_0068BCB0(DAT_00A8B230);
    if (pUnkSink->QueryInterface(Iid, (void**)&data.pUnk) < 0)
        return (HRESULT)0x80040202L; // CONNECT_E_CANNOTCONNECT
    if (!Connections.AddItem(data))
        return (HRESULT)0x80040201L; // CONNECT_E_ADVISELIMIT
    *pdwCookie = data.dwCookie;
    return S_OK;
}

// FUNCTION: GAMEMD 0x4A0700
HRESULT __stdcall ConnectionPointClass::Unadvise(DWORD dwCookie)
{
    int count = Connections.Count;
    for (int index = 0; index < count; ++index) {
        if (Connections.Items[index].dwCookie == dwCookie) {
            Connections.Delete(index);
            return S_OK;
        }
    }
    return (HRESULT)0x80040200L; // CONNECT_E_NOCONNECTION
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F7CC0
extern const GUID DAT_007F7CC0 = {0xB196B286, 0xBAB4, 0x101A, {0xB6, 0x9C, 0x00, 0xAA, 0x00, 0x34, 0x1D, 0x07}};
// END defined globals
