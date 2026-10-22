// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x008186C8 `.?AVApplicationClass@@`; class hierarchy descriptor 0x007FBC08.
//   Bases in RTTI (declaration) order: IApplication +0x0.
// VTABLE: GAMEMD 0x7E36D4 (11 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
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
    virtual void vf_3(int a1, int a2);                          // 3  0x429420: RET 0x8
    virtual void vf_4(int a1, int a2);                          // 4  0x429450: RET 0x8
    virtual void vf_5(int a1);                                  // 5  0x4294A0: RET 0x4
    virtual void vf_6(int a1, int a2);                          // 6  0x4294B0: RET 0x8
    virtual void vf_7(int a1, int a2);                          // 7  0x429500: RET 0x8
    virtual void vf_8(int a1, int a2);                          // 8  0x429550: RET 0x8
    virtual void vf_9(int a1, int a2);                          // 9  0x429400: RET 0x8
    virtual void vf_10(int a1, int a2);                         // 10  0x429480: RET 0x8
};

#endif  // GG_MATCH_LAYOUT_APPLICATION_CLASS_H
