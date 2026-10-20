// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI: vtable7E8118 has locator800010 at7E8114, naming
//   ToggleClass via type descriptor8202D8; complete-object offset0.
//   Layout, constructor call arguments, and vtable address were read from the
//   retail gamemd.exe v1.001 at 0x723E60 and its direct callee 0x48E520.
#ifndef GG_MATCH_UI_TOGGLE_CLASS_CTOR_00723E60_H
#define GG_MATCH_UI_TOGGLE_CLASS_CTOR_00723E60_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x007E8118
extern char VT_007E8118;

struct ObjectBase_00723E60
{
    void* Vptr;                 // +0x00
    char unknown_04[0x20];
    int BaseValue;              // +0x24
    int BaseUnknown_28;         // +0x28

    // FUNCTION: GAMEMD 0x48E520 (decl; reloc)
    ObjectBase_00723E60* Initialize(int a1, int a2, int a3, int a4,
                                    int a5, unsigned int a6, char a7);
};
GG_STATIC_ASSERT(offsetof(ObjectBase_00723E60, Vptr) == 0x00);
GG_STATIC_ASSERT(offsetof(ObjectBase_00723E60, BaseValue) == 0x24);
GG_STATIC_ASSERT(offsetof(ObjectBase_00723E60, BaseUnknown_28) == 0x28);
GG_STATIC_ASSERT(sizeof(ObjectBase_00723E60) == 0x2C);

struct ToggleClass_00723E60 : ObjectBase_00723E60
{
    unsigned char At_2C;        // +0x2C
    unsigned char At_2D;        // +0x2D
    unsigned char unknown_2E[2];
    int At_30;                  // +0x30

    // FUNCTION: GAMEMD 0x723E60
    ToggleClass_00723E60(int a1, int a2, int a3, int a4, int a5);
};
GG_STATIC_ASSERT(offsetof(ToggleClass_00723E60, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ToggleClass_00723E60, At_2D) == 0x2D);
GG_STATIC_ASSERT(offsetof(ToggleClass_00723E60, At_30) == 0x30);
GG_STATIC_ASSERT(sizeof(ToggleClass_00723E60) == 0x34);

#endif
