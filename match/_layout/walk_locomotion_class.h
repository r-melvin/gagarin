// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: WalkLocomotionClass::WalkLocomotionClass 0x0075AA90, which chains the
//   LocomotionClass base constructor 0x0055A6C0 and writes every one of its own
//   fields. Every offset below was read back out of the user's retail gamemd.exe
//   v1.001 from the citing instruction beside it.
//
//   sizeof = 0x3C, proven twice and independently:
//     * the single allocation site - `PUSH 0x3C` @0x006C47BC, `CALL operator new
//       (0x007C8E17)` @0x006C47BE, `MOV ECX,EAX`, `CALL 0x0075AA90` @0x006C47CC;
//     * the class's own virtual size accessor, persist-vtable (0x007F6AC4) slot
//       +0x24 = 0x0075CBD0, whose entire body is `MOV EAX,0x3C / RET`.
//   The layout CLOSES EXACTLY: the last member is the dword at 0x38
//   (@0x0075AADC) and 0x38+4 = 0x3C = sizeof, with no tail.
//
//   RTTI: ".?AVWalkLocomotionClass@@", type descriptor 0x00847BF0, THREE
//   complete object locators - 0x0080D2A8 (base offset 0, vtable 0x007F6AC4,
//   IPersistStream), 0x0080D240 (base offset 4, vtable 0x007F69F8, ILocomotion)
//   and 0x0080D228 (base offset 0x18, vtable 0x007F69D4, IPiggyback). So 0x18 is
//   a VPTR and this class cannot share FlyLocomotionClass's two-locator base;
//   its own data starts at 0x1C.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_WALK_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_WALK_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct WalkLocomotionClass : LocomotionPiggybackBase
{
    CoordStruct Destination;      // +0x1C ctor `LEA EAX,[ESI+0x1c]` @0x0075AA9E
                                  //       then X @0x0075AAA1, Y @0x0075AAAA,
                                  //       Z @0x0075AAB6 from the file-scope
                                  //       globals 0x00B45BE8 / 0x00B45BEC /
                                  //       0x00B45BF0. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x0075ABA0
                                  //       copies 0x1C (if+0x18) @0x0075ABB4,
                                  //       0x20 @0x0075ABB7 and 0x24 @0x0075ABBA
                                  //       out.

    CoordStruct HeadToCoord;      // +0x28 ctor `LEA EDX,[ESI+0x28]` @0x0075AAB3
                                  //       then @0x0075AABE, @0x0075AAC6,
                                  //       @0x0075AACE from the same globals.
                                  //       CONFIRMED BY READER:
                                  //       ILocomotion::Head_To_Coord 0x0075AC00
                                  //       reads 0x28 (if+0x24) @0x0075AC0C,
                                  //       0x2C @0x0075AC13 and 0x30 @0x0075AC20
                                  //       and compares them against the same
                                  //       three globals - which is what
                                  //       separates this coordinate from
                                  //       Destination.

    char        unknown_34;       // +0x34 ctor `MOV [ESI+0x34],AL` @0x0075AAD3
                                  //       (=0); no reader found
    char        unknown_35;       // +0x35 ctor @0x0075AAD6 (=0); no reader found
    char        unknown_36;       // +0x36 ctor @0x0075AAD9 (=0); no reader found
    char        unknown_37;       // +0x37 alignment; no access at any width

    void*       Piggybackee;      // +0x38 ILocomotion*; ctor @0x0075AADC (=0).
                                  //       Last member; 0x38+4 = sizeof.
};

GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, Destination) == 0x1C);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, HeadToCoord) == 0x28);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_34)  == 0x34);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_35)  == 0x35);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_36)  == 0x36);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, Piggybackee) == 0x38);
GG_STATIC_ASSERT(sizeof(WalkLocomotionClass)                == 0x3C);

#endif  // GG_MATCH_LAYOUT_WALK_LOCOMOTION_CLASS_H
