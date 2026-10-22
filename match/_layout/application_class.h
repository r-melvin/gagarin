// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x008186C8 `.?AVApplicationClass@@`; class hierarchy descriptor 0x007FBC08.
//   Bases in RTTI (declaration) order: IApplication +0x0.
// VTABLE: GAMEMD 0x7E36D4 (11 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Slots past IUnknown are __stdcall (each body reads `this` from the stack); argument counts come from RET n less `this`;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_APPLICATION_CLASS_H
#define GG_MATCH_LAYOUT_APPLICATION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "i_application.h"

class ApplicationClass : public IApplication
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void * *ppvObject);// 0  0x429360: override (SDK declaration)
    virtual ULONG __stdcall AddRef(void);                       // 1  0x4293E0: override (SDK declaration)
    virtual ULONG __stdcall Release(void);                      // 2  0x4293F0: override (SDK declaration)
    virtual void __stdcall vf_3(int a1);                        // 3  0x429420: RET 0x8, this on the stack
    virtual void __stdcall vf_4(int a1);                        // 4  0x429450: RET 0x8, this on the stack
    virtual void __stdcall vf_5();                              // 5  0x4294A0: RET 0x4, this on the stack
    virtual void __stdcall vf_6(int a1);                        // 6  0x4294B0: RET 0x8, this on the stack
    virtual void __stdcall vf_7(int a1);                        // 7  0x429500: RET 0x8, this on the stack
    virtual void __stdcall vf_8(int a1);                        // 8  0x429550: RET 0x8, this on the stack
    virtual void __stdcall vf_9(int a1);                        // 9  0x429400: RET 0x8, this on the stack
    virtual void __stdcall vf_10(int a1);                       // 10  0x429480: RET 0x8, this on the stack
};

#endif  // GG_MATCH_LAYOUT_APPLICATION_CLASS_H
