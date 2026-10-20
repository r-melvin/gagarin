// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: DropPodLocomotionClass::DropPodLocomotionClass 0x004B5AB0, which
//   chains the LocomotionClass base constructor 0x0055A6C0 and writes every one
//   of its own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it.
//
//   sizeof = 0x30, proven twice and independently:
//     * the single allocation site - `PUSH 0x30` @0x006C493C, `CALL operator new
//       (0x007C8E17)` @0x006C493E, `MOV ECX,EAX`, `CALL 0x004B5AB0` @0x006C494C;
//     * the class's own virtual size accessor, persist-vtable (0x007E8344) slot
//       +0x24 = 0x004B66E0, whose entire body is `MOV EAX,0x30 / RET`.
//   The layout CLOSES EXACTLY: the last member is the dword at 0x2C
//   (@0x004B5ADA) and 0x2C+4 = 0x30 = sizeof, with no tail.
//
//   RTTI: ".?AVDropPodLocomotionClass@@", type descriptor 0x008202F8, THREE
//   complete object locators - 0x008000A8 (base offset 0, vtable 0x007E8344,
//   IPersistStream), 0x00800040 (base offset 4, vtable 0x007E8278, ILocomotion)
//   and 0x00800028 (base offset 0x18, vtable 0x007E8254, IPiggyback). So 0x18 is
//   a VPTR and this class cannot share FlyLocomotionClass's two-locator base;
//   its own data starts at 0x1C.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_DROPPOD_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_DROPPOD_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct DropPodLocomotionClass : LocomotionPiggybackBase
{
    char        unknown_1C;       // +0x1C ctor `MOV BYTE PTR [ESI+0x1c],AL`
                                  //       @0x004B5ABD (=0); no reader found
                                  //       (YRpp guesses "OutOfMap")
    char        unknown_1D[3];    // +0x1D alignment behind the byte at 0x1C; no
                                  //       access at any width

    CoordStruct Destination;      // +0x20 ctor `LEA ECX,[ESI+0x20]` @0x004B5ABA
                                  //       then X @0x004B5AC6, Y @0x004B5ACE,
                                  //       Z @0x004B5AD7 from the file-scope
                                  //       globals 0x008A0820 / 0x008A0824 /
                                  //       0x008A0828. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x004B5B40
                                  //       copies 0x20 (if+0x1c) @0x004B5B4A,
                                  //       0x24 @0x004B5B4D and 0x28 @0x004B5B50
                                  //       out.

    void*       Piggybackee;      // +0x2C ILocomotion*; ctor @0x004B5ADA (=0).
                                  //       CONFIRMED BY READER: the destructor
                                  //       0x004B5B00 loads it @0x004B5B17 to
                                  //       Release it. Last member;
                                  //       0x2C+4 = sizeof.
};

GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, unknown_1C)  == 0x1C);
GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, Destination) == 0x20);
GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, Piggybackee) == 0x2C);
GG_STATIC_ASSERT(sizeof(DropPodLocomotionClass)                == 0x30);

#endif  // GG_MATCH_LAYOUT_DROPPOD_LOCOMOTION_CLASS_H
