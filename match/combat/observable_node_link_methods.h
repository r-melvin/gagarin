// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Every offset and virtual slot below is read numerically off the user's
//   retail gamemd.exe v1.001 with the local Ghidra CLI at 0x632D10 and
//   0x6330C0.
//
// Two instances of the same "point this slot at that node" operation. Both
// take the new node in the single stack argument, return nothing (`RET 0x4`
// with nothing set in EAX) and do nothing at all when the slot already points
// there -- the whole body sits under `CMP [this+0x18],<arg>; JZ`.
//
// Slot layout, confirmed instruction by instruction:
//   +0x04  BackRef   `MOV [this+4],<this+0x14>`
//   +0x14  Embedded  the address `LEA reg,[this+0x14]` forms; never read here
//   +0x18  Target    `CMP [this+0x18],<arg>`, reloaded and then overwritten
//   +0x1C  Owner     `MOV [this+0x1C],this`
//
// Node layout:
//   +0x08  Back      `MOV ECX,[node+8]`, cleared on both the old and the new
//                    node and finally re-pointed at the slot
//
// The detach is a virtual call on the node's back-pointer with one pushed
// argument and the receiver already in ECX, so `__thiscall`. The two instances
// differ in exactly two places, and both differences are visible in the bytes:
// the slot index (`CALL [EAX+0xC]` at 0x632D10 against `CALL [EAX+0x4]` at
// 0x6330C0) and what is written back into the node (the embedded subobject's
// address at 0x632D10, the slot itself at 0x6330C0).
#ifndef GG_MATCH_COMBAT_OBSERVABLE_NODE_LINK_METHODS_H
#define GG_MATCH_COMBAT_OBSERVABLE_NODE_LINK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The back-pointer target: only its vtable is reached, at slot 3 from 0x632D10
// and at slot 1 from 0x6330C0. Declared, never defined.
struct LinkBackA
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void Detach(int reason);   // [vtbl+0x0C]
};
struct LinkBackB
{
    virtual void vt_000();
    virtual void Detach(int reason);   // [vtbl+0x04]
};

struct LinkNodeA
{
    int        unknown_00;
    int        unknown_04;
    LinkBackA* Back;   // +0x08
};
GG_STATIC_ASSERT(offsetof(LinkNodeA, Back) == 0x08);

struct LinkNodeB
{
    int        unknown_00;
    int        unknown_04;
    LinkBackB* Back;   // +0x08
};
GG_STATIC_ASSERT(offsetof(LinkNodeB, Back) == 0x08);

struct LinkSlotA
{
    char*      Vptr;             // +0x00 (not reached by this function)
    void*      BackRef;          // +0x04
    int        unknown_08;       // +0x08
    int        unknown_0C;       // +0x0C
    int        unknown_10;       // +0x10
    char       Embedded[0x04];   // +0x14
    LinkNodeA* Target;           // +0x18
    void*      Owner;            // +0x1C

    // FUNCTION: GAMEMD 0x632D10
    void SetTarget(LinkNodeA* newTarget);
};
GG_STATIC_ASSERT(offsetof(LinkSlotA, BackRef)  == 0x04);
GG_STATIC_ASSERT(offsetof(LinkSlotA, Embedded) == 0x14);
GG_STATIC_ASSERT(offsetof(LinkSlotA, Target)   == 0x18);
GG_STATIC_ASSERT(offsetof(LinkSlotA, Owner)    == 0x1C);

struct LinkSlotB
{
    char*      Vptr;             // +0x00
    void*      BackRef;          // +0x04
    int        unknown_08;       // +0x08
    int        unknown_0C;       // +0x0C
    int        unknown_10;       // +0x10
    char       Embedded[0x04];   // +0x14
    LinkNodeB* Target;           // +0x18
    void*      Owner;            // +0x1C

    // FUNCTION: GAMEMD 0x6330C0
    void SetTarget(LinkNodeB* newTarget);
};
GG_STATIC_ASSERT(offsetof(LinkSlotB, BackRef)  == 0x04);
GG_STATIC_ASSERT(offsetof(LinkSlotB, Embedded) == 0x14);
GG_STATIC_ASSERT(offsetof(LinkSlotB, Target)   == 0x18);
GG_STATIC_ASSERT(offsetof(LinkSlotB, Owner)    == 0x1C);

#endif  // GG_MATCH_COMBAT_OBSERVABLE_NODE_LINK_METHODS_H
