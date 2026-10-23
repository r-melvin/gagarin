// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   No RTTI TypeDescriptor and no vtable: the ctor 0x665650 stores 5 into
//   [this+0] first. sizeof from FUN_0052BA60: PUSH 0x18C0; CALL operator new;
//   then the ctor; the result goes to the global at 0x8871E0.
//   C4Warhead: `MOV EAX,[0x8871E0]; MOV ECX,[EAX+0xFA8]` in HouseClass::DestroyAll.
//   No RTTI attests the class key, so the existing `struct` key is kept (no re-key).
#ifndef GG_MATCH_LAYOUT_RULES_CLASS_H
#define GG_MATCH_LAYOUT_RULES_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINIClass;
class WarheadTypeClass;

struct RulesClass
{
    // FUNCTION: GAMEMD 0x66D3A0
    bool Read_Colors(CCINIClass* pINI);

    char               _pad0000[0x1A0];             // +0x0000
    int                unknown_1A0;                 // +0x01A0 (voc index read by 0x608260)
    char               unknown_01A4[0x6AC - 0x1A4];
    int unknown_06AC; // native64A6F8
    char unknown_06B0[0x6C4 - 0x6B0];     // +0x01A4
    int                unknown_6C4;                 // +0x06C4 (read by 0x6023F0)
    char               _pad06C8[0xFA8 - 0x6C8];     // +0x06C8
    WarheadTypeClass*  C4Warhead;                   // +0x0FA8
    char               unknown_0FAC[0x1434 - 0xFAC];
    int                unknown_1434; // 0x64C998: source DWORD for House IQLevel2
    char               unknown_1438[0x14C0 - 0x1438];
    double             unknown_14C0; // 0x64A682/0x64A6BC: FLD qword
    char               unknown_14C8[0x18C0 - 0x14C8];
};
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1A0)  == 0x1A0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_6C4)  == 0x6C4);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0xFA8);
GG_STATIC_ASSERT(sizeof(RulesClass)              == 0x18C0);

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0

#endif  // GG_MATCH_LAYOUT_RULES_CLASS_H

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_06AC) == 0x6AC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14C0) == 0x14C0);
