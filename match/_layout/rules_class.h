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

    char               _pad0000[0xFA8];             // +0x0000
    WarheadTypeClass*  C4Warhead;                   // +0x0FA8
    char               _pad0FAC[0x18C0 - 0xFAC];    // +0x0FAC
};
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0xFA8);
GG_STATIC_ASSERT(sizeof(RulesClass)              == 0x18C0);

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0

#endif  // GG_MATCH_LAYOUT_RULES_CLASS_H
