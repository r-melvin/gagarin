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
#include "../core/vector_class.h"

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
    // FUNCTION: GAMEMD 0x4A0450 (destructor: releases every held sink; Release deletes the object)
    ~EnumConnectionsClass();

    DynamicVectorClass<tagCONNECTDATA> Connections;   // +0x04  the enumerated sinks (vtable 0x7E5CC4 chain, increment 10)
    int Index;               // +0x1C  next connection to hand out (Next, Skip, Reset)
    LONG RefCount;           // +0x20  InterlockedIncrement target (0x49FFF0)
};
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections) == 0x4);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.Items) == 0x8);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Connections.Count) == 0x14);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, Index) == 0x1C);
GG_STATIC_ASSERT(offsetof(EnumConnectionsClass, RefCount) == 0x20);
GG_STATIC_ASSERT(sizeof(EnumConnectionsClass) == 0x24);

#endif  // GG_MATCH_LAYOUT_ENUM_CONNECTIONS_CLASS_H
