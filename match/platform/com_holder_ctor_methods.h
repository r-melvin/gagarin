// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x437F50. Imports from the IAT thunks at 0x7E15FC
//   (CoCreateInstance) and 0x7E1600 (OleRun). 0x817BC0 is IID_IUnknown — the same
//   GUID 0x41C250 uses — and 0x80004002 is E_NOINTERFACE, which is why that one
//   failure is not reported.
#ifndef GG_MATCH_PLATFORM_COM_HOLDER_CTOR_METHODS_H
#define GG_MATCH_PLATFORM_COM_HOLDER_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct IUnk_00437F50;

struct IUnkVtbl_00437F50
{
    long (__stdcall* QueryInterface)(IUnk_00437F50*, const void* riid, void** ppv);
    long (__stdcall* AddRef)(IUnk_00437F50*);
    long (__stdcall* Release)(IUnk_00437F50*);
};
GG_STATIC_ASSERT(offsetof(IUnkVtbl_00437F50, Release) == 0x8);

struct IUnk_00437F50 { IUnkVtbl_00437F50* Vtbl; };

extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
    const void* rclsid, void* outer, unsigned long context,
    const void* riid, void** ppv);
extern "C" __declspec(dllimport) long __stdcall OleRun(IUnk_00437F50* object);

// GLOBAL: GAMEMD 0x7E9500 — the class id created here.
extern const char rclsid_007E9500[16];
// GLOBAL: GAMEMD 0x817BC0 — IID_IUnknown.
extern const char riid_00817BC0[16];
// GLOBAL: GAMEMD 0x818C08 — the interface the holder wants.
extern const char riid_00818C08[16];

// FUNCTION: GAMEMD 0x7DC720 — report a failed HRESULT. __stdcall: retail pushes
// the value and there is no stack cleanup after the call, so the callee pops it.
void __stdcall FUN_007DC720(long hr);

struct Holder_00437F50
{
    IUnk_00437F50* Interface;   // +0x0000

    // FUNCTION: GAMEMD 0x437F50
    Holder_00437F50* Ctor();
};
GG_STATIC_ASSERT(offsetof(Holder_00437F50, Interface) == 0);

#endif  // GG_MATCH_PLATFORM_COM_HOLDER_CTOR_METHODS_H
