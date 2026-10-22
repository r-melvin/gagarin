// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081F6C8 `.?AVConnectionPointClass@@`; class hierarchy descriptor 0x007FF7E8.
//   Bases in RTTI (declaration) order: IConnectionPoint +0x0.
// VTABLE: GAMEMD 0x7E5CE4 (8 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H
#define GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <ocidl.h>

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
    int unknown_04;  // +0x4 store at 0x4A0877
    int unknown_08;  // +0x8 store at 0x4A0881
    int unknown_0C;  // +0xC store at 0x4A0887
    int unknown_10;  // +0x10 store at 0x4A088D
    int unknown_14;  // +0x14 store at 0x4A0899
    int unknown_18;  // +0x18 store at 0x4A0896
    int unknown_1C;  // +0x1C vptr store at 0x4A08A9
    int unknown_20;  // +0x20 store at 0x4A089C
    int unknown_24;  // +0x24 store at 0x4A089F
    unsigned char unknown_28;  // +0x28 store at 0x4A08A2
    unsigned char unknown_29;  // +0x29 store at 0x4A08A6
    unsigned char unknown_2A[2];  // +0x2A
    int unknown_2C;  // +0x2C store at 0x4A08B7
    int unknown_30;  // +0x30 store at 0x4A08B0
};
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_29) == 0x29);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ConnectionPointClass, unknown_30) == 0x30);

#endif  // GG_MATCH_LAYOUT_CONNECTION_POINT_CLASS_H
