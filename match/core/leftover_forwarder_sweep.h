// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every member displacement, vtable slot index and relayed address below read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI at the address in each annotation. None of these classes is bound by
//   YRpp, so all keep Ghidra placeholder names.
//
// One forwarding shape:
//
//   SUBCALL `MOV EAX,[ESI+0x50]; LEA ECX,[ESI+0x50]; PUSH arg;
//            CALL [EAX+slot]; PUSH arg; MOV ECX,ESI; CALL helper` — a member
//          that calls one virtual on the polymorphic subobject embedded at
//          +0x50 and then a non-virtual helper on itself, passing the same
//          argument to both. `LEA ECX,[ESI+0x50]` with the vptr loaded from the
//          same address is an embedded subobject, not a pointer member.
//
// Phrasing note: the shape loads its argument from `[ESP+4]`, so it is a
// __thiscall member and must be written as a real member function; the free
// `__fastcall` spelling passes the argument in EDX and does not match.
#ifndef GG_MATCH_CORE_LEFTOVER_FORWARDER_SWEEP_H
#define GG_MATCH_CORE_LEFTOVER_FORWARDER_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// SUBCALL. The embedded subobject's vtable is only used through the one slot
// each instantiation calls, so the slots are placeholders; slot 3 is +0x0C,
// slot 4 is +0x10 and slot 5 is +0x14.
struct SubCallPart
{
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3(void* a);
    virtual void Slot4(void* a);
    virtual void Slot5(void* a);
};

#define GG_SUBCALL_DECL(TAG)                                              \
struct SubCall_##TAG                                                      \
{                                                                         \
    char _pad00[0x50];                                                    \
    SubCallPart Part;              /* +0x50 */                            \
    void Helper(void* a);                                                 \
    void Run(void* a);                                                    \
}

#define GG_SUBCALL_BODY(TAG, SLOT)                                        \
void SubCall_##TAG::Run(void* a)                                          \
{                                                                         \
    this->Part.SLOT(a);                                                   \
    this->Helper(a);                                                      \
}

// SUBCALL instantiations, with the retail address each helper lands on.
GG_SUBCALL_DECL(004B4F20); // SubCall_004B4F20::Helper is GAMEMD 0x5566A0
GG_SUBCALL_DECL(004B4F40); // SubCall_004B4F40::Helper is GAMEMD 0x556700
GG_SUBCALL_DECL(004B4F60); // SubCall_004B4F60::Helper is GAMEMD 0x5566D0

GG_STATIC_ASSERT(offsetof(SubCall_004B4F20, Part) == 0x50 &&
                 sizeof(SubCallPart) == 0x4 &&
                 sizeof(SubCall_004B4F20) == 0x54);

#endif  // GG_MATCH_CORE_LEFTOVER_FORWARDER_SWEEP_H
