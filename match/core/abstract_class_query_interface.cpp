// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x410260 compares four 16-byte IIDs independently, returns the
// +4 IRTTITypeInfo base for the last IID, and dispatches primary AddRef.
#include "../_layout/abstract_class.h"

// GLOBAL: GAMEMD 0x7E9AE0
// The native comparison at 0x4102C7 selects AbstractClass's +4 interface.
extern "C" const IID IID_IRTTITypeInfo = {
    0x170DAC82, 0x12E4, 0x11D2, {0x81, 0x75, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}
};
GG_STATIC_ASSERT(sizeof(IID) == 16);
GG_STATIC_ASSERT(offsetof(IID, Data1) == 0);
GG_STATIC_ASSERT(offsetof(IID, Data2) == 4);
GG_STATIC_ASSERT(offsetof(IID, Data3) == 6);
GG_STATIC_ASSERT(offsetof(IID, Data4) == 8);

// FUNCTION: GAMEMD 0x410260
HRESULT __stdcall AbstractClass::QueryInterface(REFIID riid, void** output)
{
    if (output == 0)
        return E_POINTER;
    *output = 0;
    if (riid == IID_IUnknown)
        *output = static_cast<IPersistStream*>(this);
    if (riid == IID_IPersistStream)
        *output = static_cast<IPersistStream*>(this);
    if (riid == IID_IPersist)
        *output = static_cast<IPersistStream*>(this);
    if (riid == IID_IRTTITypeInfo)
        *output = static_cast<IRTTITypeInfo*>(this);
    if (*output == 0)
        return E_NOINTERFACE;
    AddRef();
    return S_OK;
}
