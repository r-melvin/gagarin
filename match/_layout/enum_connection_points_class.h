// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081F750 `.?AVEnumConnectionPointsClass@@`; class hierarchy descriptor 0x007FF898.
//   Bases in RTTI (declaration) order: IEnumConnectionPoints +0x0.
// VTABLE: GAMEMD 0x7E5D28 (7 slots)
//   Allocation: operator new (0x7C8E17) of 0x24 bytes at 0x4A0B36, 0x502504.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_ENUM_CONNECTION_POINTS_CLASS_H
#define GG_MATCH_LAYOUT_ENUM_CONNECTION_POINTS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <ocidl.h>

class EnumConnectionPointsClass : public IEnumConnectionPoints
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x4A0920: implements IEnumConnectionPoints
    virtual ULONG __stdcall AddRef(void);                       // 1  0x4A0990: implements IEnumConnectionPoints
    virtual ULONG __stdcall Release(void);                      // 2  0x4A09B0: implements IEnumConnectionPoints
    virtual HRESULT __stdcall Next(ULONG cConnections, LPCONNECTIONPOINT *ppCP, ULONG *pcFetched);// 3  0x4A0A50: implements IEnumConnectionPoints
    virtual HRESULT __stdcall Skip(ULONG cConnections);         // 4  0x4A0AF0: implements IEnumConnectionPoints
    virtual HRESULT __stdcall Reset(void);                      // 5  0x4A0B10: implements IEnumConnectionPoints
    virtual HRESULT __stdcall Clone(IEnumConnectionPoints * *ppEnum);// 6  0x4A0B20: implements IEnumConnectionPoints
    int unknown_04;  // +0x4 store at 0x4A0C2F
    int unknown_08;  // +0x8 store at 0x4A0C32
    int unknown_0C;  // +0xC vptr store at 0x4A0C44
    IConnectionPoint** unknown_10;  // +0x10 store at 0x4A0C37; the array Next hands out from (0x4A0A50)
    int unknown_14;  // +0x14 store at 0x4A0C3A
    unsigned char unknown_18;  // +0x18 store at 0x4A0C3D
    unsigned char unknown_19;  // +0x19 store at 0x4A0C41
    unsigned char unknown_1A[2];  // +0x1A
    int unknown_1C;  // +0x1C store at 0x4A0C9D
    int unknown_20;  // +0x20 store at 0x4A0CA3
};
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_19) == 0x19);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(EnumConnectionPointsClass) == 0x24);

#endif  // GG_MATCH_LAYOUT_ENUM_CONNECTION_POINTS_CLASS_H
