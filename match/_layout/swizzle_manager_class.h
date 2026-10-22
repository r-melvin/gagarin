// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00842730 `.?AVSwizzleManagerClass@@`; class hierarchy descriptor 0x0080B720.
//   Bases in RTTI (declaration) order: ISwizzle +0x0.
// VTABLE: GAMEMD 0x7F4108 (10 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "i_swizzle.h"

class SwizzleManagerClass : public ISwizzle
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x6CF430: override (SDK declaration)
    virtual ULONG __stdcall AddRef(void);                       // 1  0x6CF4B0: override (SDK declaration)
    virtual ULONG __stdcall Release(void);                      // 2  0x6CF4C0: override (SDK declaration)
    virtual void vf_3(int a1);                                  // 3  0x6CF230: RET 0x4
    virtual void vf_4(int a1, int a2);                          // 4  0x6CF240: RET 0x8
    virtual void vf_5(int a1, int a2, int a3);                  // 5  0x6CF490: RET 0xC
    virtual void vf_6(int a1, int a2, int a3);                  // 6  0x6CF2C0: RET 0xC
    virtual void vf_7(int a1, int a2, int a3);                  // 7  0x6CF4D0: RET 0xC
    virtual void vf_8(int a1, int a2, int a3, int a4);          // 8  0x6CF4E0: RET 0x10
    virtual void vf_9(int a1, int a2);                          // 9  0x6CF410: RET 0x8
    int unknown_04;  // +0x4 vptr store at 0x6CF196
    int unknown_08;  // +0x8 store at 0x6CF189
    int unknown_0C;  // +0xC store at 0x6CF18C
    unsigned char unknown_10;  // +0x10 store at 0x6CF18F
    unsigned char unknown_11;  // +0x11 store at 0x6CF193
    unsigned char unknown_12[2];  // +0x12
    int unknown_14;  // +0x14 store at 0x6CF1A0
    int unknown_18;  // +0x18 store at 0x6CF19D
    int unknown_1C;  // +0x1C vptr store at 0x6CF1B3
    int unknown_20;  // +0x20 store at 0x6CF1A3
    int unknown_24;  // +0x24 store at 0x6CF1A6
    unsigned char unknown_28;  // +0x28 store at 0x6CF1AF
    unsigned char unknown_29;  // +0x29 store at 0x6CF1A9
    unsigned char unknown_2A[2];  // +0x2A
    int unknown_2C;  // +0x2C store at 0x6CF1AC
    int unknown_30;  // +0x30 store at 0x6CF1BA
};
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_11) == 0x11);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_29) == 0x29);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_30) == 0x30);

#endif  // GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H
