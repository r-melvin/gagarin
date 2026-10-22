// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081F648 `.?AVEnumConnectionsClass@@`; class hierarchy descriptor 0x007FF730.
//   Bases in RTTI (declaration) order: IEnumConnections +0x0.
// VTABLE: GAMEMD 0x7E5CA4 (7 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_ENUM_CONNECTIONS_CLASS_H
#define GG_MATCH_LAYOUT_ENUM_CONNECTIONS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <ocidl.h>

class EnumConnectionsClass : public IEnumConnections
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x49FF80: implements IEnumConnections
    virtual ULONG __stdcall AddRef(void);                       // 1  0x49FFF0: implements IEnumConnections
    virtual ULONG __stdcall Release(void);                      // 2  0x4A0010: implements IEnumConnections
    virtual HRESULT __stdcall Next(ULONG cConnections, LPCONNECTDATA rgcd, ULONG *pcFetched);// 3  0x4A00B0: implements IEnumConnections
    virtual HRESULT __stdcall Skip(ULONG cConnections);         // 4  0x4A0160: implements IEnumConnections
    virtual HRESULT __stdcall Reset(void);                      // 5  0x4A0180: implements IEnumConnections
    virtual HRESULT __stdcall Clone(IEnumConnections * *ppEnum);// 6  0x4A0190: implements IEnumConnections
    int unknown_04;  // +0x4 vptr store at 0x4A02CE
    int unknown_08;  // +0x8 store at 0x4A02C1
    int unknown_0C;  // +0xC store at 0x4A02C4
    unsigned char unknown_10;  // +0x10 store at 0x4A02C7
    unsigned char unknown_11;  // +0x11 store at 0x4A02CB
    unsigned char unknown_12[2];  // +0x12
    int unknown_14;  // +0x14 store at 0x4A0331
    int unknown_18;  // +0x18 store at 0x4A0337
    int unknown_1C;  // +0x1C store at 0x4A0340
    int unknown_20;  // +0x20 store at 0x4A0343
};
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_11) == 0x11);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, unknown_20) == 0x20);

#endif  // GG_MATCH_LAYOUT_ENUM_CONNECTIONS_CLASS_H
