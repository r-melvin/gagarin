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
#include "../core/vector_class.h"

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
    // FUNCTION: GAMEMD 0x4A0C20 (copy constructor used by Clone)
    // FUNCTION: GAMEMD 0x4A0DB0 (destructor: releases every held point; Release deletes the object)
    ~EnumConnectionPointsClass();

    int Index;               // +0x04  next point to hand out (Next, Skip, Reset)
    LONG RefCount;           // +0x08  InterlockedIncrement / Decrement target (0x4A0990, 0x4A09B0)
    DynamicVectorClass<IConnectionPoint*> Points;   // +0x0C  the enumerated points (vtable 0x7E5D08, capacity increment 10)
};
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Index) == 0x4);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, RefCount) == 0x8);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points) == 0xC);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Items) == 0x10);
GG_STATIC_ASSERT(offsetof(EnumConnectionPointsClass, Points.Count) == 0x1C);
GG_STATIC_ASSERT(sizeof(EnumConnectionPointsClass) == 0x24);

#endif  // GG_MATCH_LAYOUT_ENUM_CONNECTION_POINTS_CLASS_H
