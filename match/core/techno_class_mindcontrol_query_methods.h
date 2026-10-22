// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, vtable slots and offsets read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x53C450. Name cross-checked against
//   YRpp (`TechnoClass::CanBePermaMindControlled`).
#ifndef GG_MATCH_CORE_TECHNO_CLASS_MINDCONTROL_QUERY_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_MINDCONTROL_QUERY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// AbstractType discriminant returned by WhatAmI().
#define ABS_BUILDING 6

class TechnoClass;

// TechnoTypeClass — two flags are consulted, both keeping placeholder names:
// the bytes fix their offsets but not their meaning.
struct TechnoTypeClass
{
    char _pad000[0xD35];   // +0x0000
    bool unknown_D35;      // +0x0D35  (MOV CL,[EAX+0xD35])
    char _padD36[0xD6A - 0xD36];
    bool unknown_D6A;      // +0x0D6A  (MOV CL,[EAX+0xD6A])
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_D35) == 0xD35);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_D6A) == 0xD6A);

// Four primary-vtable virtuals, all dispatched through the tree's usual
// __fastcall-fn-pointer idiom so VC6 reproduces `MOV EAX,[ESI]; MOV ECX,ESI;
// CALL [EAX+slot]` exactly.
//   +0x2C   WhatAmI()      -> AbstractType
//   +0x54   (bool query, negated into the result)
//   +0x84   GetTechnoType() -> TechnoTypeClass*
//   +0x160  (bool query)
typedef int              (__fastcall* WhatAmIFunc)(TechnoClass*);
typedef bool             (__fastcall* BoolQueryFunc)(TechnoClass*);
// Slot +0x54 returns a bool like the others. The earlier note here had it as a
// byte on the theory that the narrow `TEST AL,AL; SETZ AL` implied a byte result;
// that was the wrong lever. The operand type makes no difference — bool, unsigned
// char and int all give the full-width `NEG/SBB/INC` for a negation. What decides
// it is whether the negation is written as an *expression* or as a *branch*: see
// the constructor of the return value in the .cpp.
typedef bool             (__fastcall* ByteQueryFunc)(TechnoClass*);
typedef TechnoTypeClass* (__fastcall* GetTypeFunc)(TechnoClass*);

#define TECHNO_WHAT_AM_I(o)   ((*(WhatAmIFunc*)(*(char**)(o) + 0x2c))(o))
#define TECHNO_SLOT_54(o)     ((*(ByteQueryFunc*)(*(char**)(o) + 0x54))(o))
#define TECHNO_GET_TYPE(o)    ((*(GetTypeFunc*)(*(char**)(o) + 0x84))(o))
#define TECHNO_SLOT_160(o)    ((*(BoolQueryFunc*)(*(char**)(o) + 0x160))(o))

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    bool CanBePermaMindControlled();   // GAMEMD 0x53C450
};

#endif  // GG_MATCH_CORE_TECHNO_CLASS_MINDCONTROL_QUERY_METHODS_H
