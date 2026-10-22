// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4B4D50 and its ten duplicates. The whole function is
//   thirteen bytes and names exactly one member: the interface pointer at
//   offset 0 (`MOV EAX,[ECX]`). The call shape fixes the convention — the
//   receiver is PUSHed rather than left in ECX (`MOV ECX,[EAX]; PUSH EAX;
//   CALL dword ptr [ECX+8]`), i.e. a __stdcall COM virtual, and +8 is
//   IUnknown slot 2, Release. These entry points carry no name in the binary
//   or in the YRpp map and keep their placeholder names.
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `ComOwner_004B4D50` is not one recovered class: it is eleven separate retail addresses spread from 0x4B4D50 to 0x7AC680, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_COM_MEMBER_RELEASE_FAMILY_METHODS_H
#define GG_MATCH_CORE_COM_MEMBER_RELEASE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct IUnk;

typedef unsigned long (__stdcall* ReleaseSlot)(IUnk*);

#define GG_COM_RELEASE(p) \
    ((*(ReleaseSlot*)(*(char**)(p) + 0x08))(p))

struct ComOwner_004B4D50
{
    IUnk* Held;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(ComOwner_004B4D50, Held) == 0);
GG_STATIC_ASSERT(sizeof(ComOwner_004B4D50) == 4);

#define GG_COM_MEMBER_RELEASE_BODY(ADDR)                                  \
void __fastcall FUN_##ADDR(ComOwner_004B4D50* self)                       \
{                                                                         \
    IUnk* held = self->Held;                                              \
    if (held != 0) {                                                      \
        GG_COM_RELEASE(held);                                             \
    }                                                                     \
}

// FUNCTION: GAMEMD 0x004B4D50
void FUN_004B4D50(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x004B4D60
void FUN_004B4D60(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x004D0430
void FUN_004D0430(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x004E02C0
void FUN_004E02C0(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x0067FDD0
void FUN_0067FDD0(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x0067FDE0
void FUN_0067FDE0(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x00683050
void FUN_00683050(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x00683060
void FUN_00683060(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x006C61C0
void FUN_006C61C0(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x007AC670
void FUN_007AC670(ComOwner_004B4D50* self);
// FUNCTION: GAMEMD 0x007AC680
void FUN_007AC680(ComOwner_004B4D50* self);

#endif  // GG_MATCH_CORE_COM_MEMBER_RELEASE_FAMILY_METHODS_H
