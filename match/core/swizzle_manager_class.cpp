// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native constructor 0x6CF180 and destruction 0x6CF1D0 establish two owning
// dynamic vectors. CRT slot 0x814E10 selects initializer 0x6CF070; cleanup
// 0x6CF0F0 resolves pending entries and destroys the second vector first.
// Constructor/global migration is held; this TU supplies the recovered methods.
#include "../_layout/swizzle_manager_class.h"
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x6CF1D0
SwizzleManagerClass::~SwizzleManagerClass()
{
    FUN_006CF350();
}

// FUNCTION: GAMEMD 0x6CF230
HRESULT __stdcall SwizzleManagerClass::vf_3()
{
    FUN_006CF350();
    return S_OK;
}

// FUNCTION: GAMEMD 0x6CF240
HRESULT __stdcall SwizzleManagerClass::vf_4(void* pointerFieldAddress)
{
    if (pointerFieldAddress == 0)
        return E_POINTER;
    // Native 0x6CF254 loads a DWORD through this address; 0x6CF2A8
    // zeroes that same four-byte slot after queuing its old value/address.
    if (*(int*)pointerFieldAddress == 0)
        return S_OK;
    unknown_04.AddItem(SwizzlePointerClass(*(int*)pointerFieldAddress,
                                          pointerFieldAddress));
    *(int*)pointerFieldAddress = 0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6CF2C0
HRESULT __stdcall SwizzleManagerClass::vf_6(int identity, void* subject)
{
    SwizzlePointerClass item;
    item.B = subject;
    item.A = identity;
    unknown_1C.AddItem(item);
    return S_OK;
}

// FUNCTION: GAMEMD 0x6CF410
HRESULT __stdcall SwizzleManagerClass::vf_9(unsigned int* outputValue)
{
    if (outputValue == 0)
        return E_POINTER;
    *outputValue = 4;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6CF490
HRESULT __stdcall SwizzleManagerClass::vf_5(void* subject, void** outputValue)
{
    if (subject == 0 || outputValue == 0)
        return E_POINTER;
    *outputValue = subject;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6CF4B0
ULONG __stdcall SwizzleManagerClass::AddRef()
{
    return 1;
}

// FUNCTION: GAMEMD 0x6CF4C0
ULONG __stdcall SwizzleManagerClass::Release()
{
    return 1;
}

// FUNCTION: GAMEMD 0x6CF4D0
HRESULT __stdcall SwizzleManagerClass::vf_7(int a1, int a2)
{
    return E_NOTIMPL;
}

// FUNCTION: GAMEMD 0x6CF4E0
HRESULT __stdcall SwizzleManagerClass::vf_8(int a1, int a2, int a3)
{
    return E_NOTIMPL;
}
