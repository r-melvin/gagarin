// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: InfantryClass ctor FUN_0x00517A50 (chains FootClass ctor
//   FUN_0x004D31E0 at offset 0, CALL @0x00517A5B). Every member below is read
//   from a field-init store in that ctor. Argument identification: after the
//   four register pushes and the __thiscall FootClass call (which pops its own
//   stack argument), [ESP+0x14] is arg1 = pType, so the store
//   `MOV [ESI+0x6C0],ECX` @0x00517A6E installs Type at 0x6C0 — not 0x6C4.
//   sizeof is read from the allocation sites: `PUSH 0x6F0` before the ctor call
//   at 8 of the 8 call sites found by `ghidra x-ref to 0x517A50`.
//
//   RTTI (read from the binary): all four vptr targets resolve to
//   ".?AVInfantryClass@@" with COL base-offset 0 / 4 / 8 / 12.
//
//   Cross-read against YRpp InfantryClass.h: 11 named members claimed, 11
//   confirmed. No disagreement found.
//
// InfantryClass — a foot soldier. Derives FootClass at offset 0
// (sizeof(FootClass) == 0x6C0) and adds its own block from 0x6C0.
#ifndef GG_MATCH_LAYOUT_INFANTRY_CLASS_H
#define GG_MATCH_LAYOUT_INFANTRY_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "foot_class.h"

struct InfantryClass : FootClass
{
    void*         Type;                 // +0x6C0  InfantryTypeClass*; ctor: MOV [ESI+0x6C0],ECX(=pType) @0x00517A6E
    int           SequenceAnim;         // +0x6C4  Sequence enum; ctor: MOV [ESI+0x6C4],0xFFFFFFFF @0x00517A64
    CDTimerClass  unknown_Timer_6C8;    // +0x6C8  (0xC) ctor: StartTime MOV [ESI+0x6C8],EDX(=[0x00A8ED84], the
                                        //         frame clock) @0x00517A7F; TimeLeft MOV [ESI+0x6D0],EBX(0)
                                        //         @0x00517A85. 0x6CC is the CDTimerClass clock slot the ctor
                                        //         does not store, exactly as in every other CDTimerClass here.
    unsigned int  PanicDurationLeft;    // +0x6D4  ctor: MOV [ESI+0x6D4],EBX(0) @0x00517A8C
    unsigned char PermanentBerzerk;     // +0x6D8  ctor: MOV byte [ESI+0x6D8],BL @0x00517A92
    unsigned char Technician;           // +0x6D9  ctor: MOV byte [ESI+0x6D9],BL @0x00517A98
    unsigned char unknown_bool_6DA;     // +0x6DA  ctor: MOV byte [ESI+0x6DA],BL @0x00517A9E
    unsigned char Crawling;             // +0x6DB  ctor: MOV byte [ESI+0x6DB],BL @0x00517AA4
    unsigned char unknown_bool_6DC;     // +0x6DC  ctor: MOV byte [ESI+0x6DC],BL @0x00517AAA
    unsigned char unknown_bool_6DD;     // +0x6DD  ctor: MOV byte [ESI+0x6DD],BL @0x00517AB0
    unsigned char align_6DE[2];         // +0x6DE
    unsigned int  unknown_6E0;          // +0x6E0  ctor: MOV [ESI+0x6E0],EBX(0) @0x00517AB6
    unsigned char ShouldDeploy;         // +0x6E4  ctor: MOV byte [ESI+0x6E4],BL @0x00517ABC
    unsigned char align_6E5[3];         // +0x6E5
    int           unknown_int_6E8;      // +0x6E8  ctor: MOV [ESI+0x6E8],2 @0x00517AC2
    unsigned int  unused_6EC;           // +0x6EC  (PROTECTED_PROPERTY; closes the object at 0x6F0)
};

GG_STATIC_ASSERT(offsetof(InfantryClass, Type)              == 0x6C0);
GG_STATIC_ASSERT(offsetof(InfantryClass, SequenceAnim)      == 0x6C4);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_Timer_6C8) == 0x6C8);
GG_STATIC_ASSERT(offsetof(InfantryClass, PanicDurationLeft) == 0x6D4);
GG_STATIC_ASSERT(offsetof(InfantryClass, PermanentBerzerk)  == 0x6D8);
GG_STATIC_ASSERT(offsetof(InfantryClass, Technician)        == 0x6D9);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DA)  == 0x6DA);
GG_STATIC_ASSERT(offsetof(InfantryClass, Crawling)          == 0x6DB);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DC)  == 0x6DC);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_bool_6DD)  == 0x6DD);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_6E0)       == 0x6E0);
GG_STATIC_ASSERT(offsetof(InfantryClass, ShouldDeploy)      == 0x6E4);
GG_STATIC_ASSERT(offsetof(InfantryClass, unknown_int_6E8)   == 0x6E8);
GG_STATIC_ASSERT(offsetof(InfantryClass, unused_6EC)        == 0x6EC);
GG_STATIC_ASSERT(sizeof(InfantryClass)                      == 0x6F0);

// VTABLE: GAMEMD 0x007EB058  InfantryClass          (COL @0x007EB054, base 0)
// VTABLE: GAMEMD 0x007EB03C  InfantryClass::(+0x04) (base 4)
// VTABLE: GAMEMD 0x007EB034  InfantryClass::(+0x08) (base 8)
// VTABLE: GAMEMD 0x007EB02C  InfantryClass::(+0x0C) (base 12)

#endif  // GG_MATCH_LAYOUT_INFANTRY_CLASS_H
