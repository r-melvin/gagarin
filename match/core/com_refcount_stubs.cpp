// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IUnknown AddRef/Release of objects that are not reference counted: each
// returns 1 and pops its `this` (`MOV EAX,1; RET 4`). The owning class of each
// body is the class whose vtable slot 1 (AddRef) or 2 (Release) holds it in
// the retail RTTI tables. They are written as free __stdcall
// functions taking `this`, as 0x410300 is in const_return_stub_methods.cpp,
// because none of these classes is declared with its COM bases yet.

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

// FUNCTION: GAMEMD 0x6CF4B0 -- SwizzleManagerClass::AddRef (vtable slot 1)
int __stdcall FUN_006CF4B0(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x6CF4C0 -- SwizzleManagerClass::Release (vtable slot 2)
int __stdcall FUN_006CF4C0(int)
{
    return 1;
}
