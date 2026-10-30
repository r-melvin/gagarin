// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081F6C8 `.?AVConnectionPointClass@@`; class hierarchy descriptor 0x007FF7E8.
//   Bases in RTTI (declaration) order: IConnectionPoint +0x0.
// VTABLE: GAMEMD 0x7E5CE4 (8 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
//   Size 0x34: the vector at +0x1C (0x18 bytes) ends the object.
#ifndef GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H
#define GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <ocidl.h>
#include "../core/vector_class.h"

// Element comparison for the vector template's out-of-line members (never called by the matched code).
inline bool operator==(const tagCONNECTDATA& a, const tagCONNECTDATA& b) { return a.pUnk == b.pUnk && a.dwCookie == b.dwCookie; }
inline bool operator!=(const tagCONNECTDATA& a, const tagCONNECTDATA& b) { return !(a == b); }

class ConnectionPointClass : public IConnectionPoint
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x4A04B0: implements IConnectionPoint
    virtual ULONG __stdcall AddRef(void);                       // 1  0x4A0520: implements IConnectionPoint
    virtual ULONG __stdcall Release(void);                      // 2  0x4A0540: implements IConnectionPoint
    virtual HRESULT __stdcall GetConnectionInterface(IID *pIID);// 3  0x4A05D0: implements IConnectionPoint
    virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer * *ppCPC);// 4  0x4A0610: implements IConnectionPoint
    virtual HRESULT __stdcall Advise(IUnknown *pUnkSink, DWORD *pdwCookie);// 5  0x4A0630: implements IConnectionPoint
    virtual HRESULT __stdcall Unadvise(DWORD dwCookie);         // 6  0x4A0700: implements IConnectionPoint
    virtual HRESULT __stdcall EnumConnections(IEnumConnections * *ppEnum);// 7  0x4A0760: implements IConnectionPoint
    // FUNCTION: GAMEMD 0x4A0870 (constructor: copies the interface id and holds the container)
    ConnectionPointClass(const IID* iid, IUnknown* container);
    // FUNCTION: GAMEMD 0x4A08D0 (destructor: releases the container; Release deletes the object)
    ~ConnectionPointClass();

    IID Iid;                 // +0x04  copied from the first constructor argument; GetConnectionInterface copies it out
    LONG RefCount;           // +0x14  InterlockedIncrement / Decrement target (0x4A0520, 0x4A0540)
    IUnknown* Container;     // +0x18  the owning container; held with AddRef, queried by 0x4A0610
    DynamicVectorClass<tagCONNECTDATA> Connections;   // +0x1C  the advised sinks (vtable 0x7E5CC4, capacity increment 10)
};
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Iid) == 0x4);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, RefCount) == 0x14);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Container) == 0x18);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, Connections) == 0x1C);
GG_STATIC_ASSERT(sizeof(ConnectionPointClass) == 0x34);

#endif  // GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H
