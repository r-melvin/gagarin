// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IUnknown AddRef/Release of objects that are not reference counted: each
// returns 1 and pops its `this` (`MOV EAX,1; RET 4`). The owning class of each
// body is the class whose vtable slot 1 (AddRef) or 2 (Release) holds it in
// the retail RTTI tables. They are written as free __stdcall
// functions taking `this`, as 0x410300 is in const_return_stub_methods.cpp,
// because none of these classes is declared with its COM bases yet.

#include <string.h>
#include "_layout/application_class.h"

// GLOBAL: GAMEMD 0x7E36C0 - the interface id the main object is asked for.
extern const GUID DAT_007E36C0;
// GLOBAL: GAMEMD 0x7F7C90 - IID_IUnknown.
extern const GUID DAT_007F7C90;
// GLOBAL: GAMEMD 0x7EA6E8 - the interface id GScreenClass answers to.
extern const GUID DAT_007EA6E8;
// GLOBAL: GAMEMD 0x87F7E8 - the map object, handed out without a reference.
class MapClass;
extern MapClass DAT_0087F7E8;

// FUNCTION: GAMEMD 0x429360 -- ApplicationClass::QueryInterface (vtable slot 0)
HRESULT __stdcall ApplicationClass::QueryInterface(REFIID riid, void** ppvObject)
{
    if (ppvObject == 0)
        return E_POINTER;
    if (memcmp(&riid, &DAT_007E36C0, sizeof(GUID)) == 0 || memcmp(&riid, &DAT_007F7C90, sizeof(GUID)) == 0) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    if (memcmp(&riid, &DAT_007EA6E8, sizeof(GUID)) == 0) {
        *ppvObject = &DAT_0087F7E8;
        return S_OK;
    }
    return E_NOINTERFACE;
}

// FUNCTION: GAMEMD 0x4293E0 -- ApplicationClass::AddRef (vtable slot 1)
int __stdcall FUN_004293E0(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x4293F0 -- ApplicationClass::Release (vtable slot 2)
int __stdcall FUN_004293F0(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x4E8240 -- TiberianSunClassFactory::AddRef (vtable slot 1)
int __stdcall FUN_004E8240(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x4E8250 -- TiberianSunClassFactory::Release (vtable slot 2)
int __stdcall FUN_004E8250(int)
{
    return 1;
}
