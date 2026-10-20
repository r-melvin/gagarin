// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x41C250. Imports resolved from the IAT thunks at 0x7E15FC
//   (CoCreateInstance) and 0x7E1600 (OleRun). The two GUIDs are read from
//   .rdata: 0x817BC0 is {00000000-0000-0000-C000-000000000046}, IID_IUnknown,
//   and 0x817BB0 is {070F3290-9841-11D1-B709-00A024DDAFD1}, the interface the
//   holder actually wants.
#ifndef GG_MATCH_PLATFORM_COM_CREATE_HOLDER_METHODS_H
#define GG_MATCH_PLATFORM_COM_CREATE_HOLDER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct IUnknown_0041C250;

// Minimal IUnknown: __stdcall virtuals with the receiver pushed, slots
// QueryInterface / AddRef / Release at +0x00 / +0x04 / +0x08.
struct IUnknownVtbl_0041C250
{
    long (__stdcall* QueryInterface)(IUnknown_0041C250*, const void* riid, void** ppv);
    long (__stdcall* AddRef)(IUnknown_0041C250*);
    long (__stdcall* Release)(IUnknown_0041C250*);
};
GG_STATIC_ASSERT(offsetof(IUnknownVtbl_0041C250, Release) == 0x8);

struct IUnknown_0041C250 { IUnknownVtbl_0041C250* Vtbl; };

// OLE32, dllimport so the calls go indirect through the IAT.
extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
    const void* rclsid, IUnknown_0041C250* outer, unsigned long context,
    const void* riid, void** ppv);
extern "C" __declspec(dllimport) long __stdcall OleRun(IUnknown_0041C250* object);

// GLOBAL: GAMEMD 0x817BB0 — the wanted interface's IID.
extern const char riid_00817BB0[16];
// GLOBAL: GAMEMD 0x817BC0 — IID_IUnknown.
extern const char riid_00817BC0[16];

// A one-pointer holder. Its single member is the interface it owns, which is
// also what makes `this` usable directly as the `ppv` out-parameter.
struct Holder_0041C250
{
    IUnknown_0041C250* Interface;   // +0x0000

    // FUNCTION: GAMEMD 0x41C250
    long Create(const void* rclsid, IUnknown_0041C250* outer,
                unsigned int context);
};
GG_STATIC_ASSERT(offsetof(Holder_0041C250, Interface) == 0);

#endif  // GG_MATCH_PLATFORM_COM_CREATE_HOLDER_METHODS_H
