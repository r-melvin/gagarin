// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00842730 `.?AVSwizzleManagerClass@@`; class hierarchy descriptor 0x0080B720.
//   Bases in RTTI (declaration) order: ISwizzle +0x0.
// VTABLE: GAMEMD 0x7F4108 (10 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Slots past IUnknown are __stdcall (each body reads `this` from the stack); argument counts come from RET n less `this`;
//   All slots return HRESULT or ULONG as read from the native return paths.
//   Member offsets come from constructor stores and queue operations.
#ifndef GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "i_swizzle.h"
#include "swizzle_pointer_class.h"
#include "../core/vector_class.h"

class SwizzleManagerClass : public ISwizzle
{
public:
    // Declaration: GAMEMD 0x6CF180 -- constructor.
    SwizzleManagerClass();
    // Declaration: GAMEMD 0x6CF1D0 -- nonvirtual destruction.
    ~SwizzleManagerClass();
    // Declaration: GAMEMD 0x6CF350 -- resolve and clear entries.
    void FUN_006CF350();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x6CF430: override (SDK declaration)
    virtual ULONG __stdcall AddRef(void);                       // 1  0x6CF4B0: override (SDK declaration)
    virtual ULONG __stdcall Release(void);                      // 2  0x6CF4C0: override (SDK declaration)
    virtual HRESULT __stdcall vf_3();                              // 3  0x6CF230: RET 0x4, this on the stack
    // Declaration: GAMEMD 0x6CF240 -- stack this and writable DWORD-slot address; RET 8.
    // Null address returns E_POINTER; a zero DWORD returns S_OK immediately.
    // A nonzero DWORD is queued with its address, then zeroed; failed queue
    // growth also zeroes that DWORD and returns S_OK (0x6CF2A8..0x6CF2B5).
    virtual HRESULT __stdcall vf_4(void* pointerFieldAddress);   // 4
    virtual HRESULT __stdcall vf_5(void* subject, void** outputValue);                // 5  0x6CF490: RET 0xC, this on the stack
    virtual HRESULT __stdcall vf_6(int identity, void* subject);                // 6  0x6CF2C0: RET 0xC, this on the stack
    virtual HRESULT __stdcall vf_7(int a1, int a2);                // 7  0x6CF4D0: RET 0xC, this on the stack
    virtual HRESULT __stdcall vf_8(int a1, int a2, int a3);        // 8  0x6CF4E0: RET 0x10, this on the stack
    virtual HRESULT __stdcall vf_9(unsigned int* outputValue);                        // 9  0x6CF410: RET 0x8, this on the stack
    // Native constructor 0x6CF180: dynamic-vector vptrs at +4/+1C,
    // items at +8/+20, counts at +14/+2C and growth at +18/+30.
    DynamicVectorClass<SwizzlePointerClass> unknown_04;
    DynamicVectorClass<SwizzlePointerClass> unknown_1C;
};
GG_STATIC_ASSERT(sizeof(SwizzleManagerClass) == 0x34);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(SwizzleManagerClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SwizzlePointerClass>) == 0x18);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, IsInitialized) == 0xC);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SwizzlePointerClass>, CapacityIncrement) == 0x14);

// GLOBAL: GAMEMD 0xB0C110
// Native CRT6CF070 installs7F4108 and registers external teardown6CF0F0.
// Storage and compiler-generated initialization remain external while the
// constructor/global migration is held.
extern SwizzleManagerClass DAT_00B0C110;

#endif  // GG_MATCH_LAYOUT_SWIZZLE_MANAGER_CLASS_H
