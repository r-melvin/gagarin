// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: MechLocomotionClass::MechLocomotionClass 0x005AFEF0, which chains the
//   LocomotionClass base constructor 0x0055A6C0 and writes every one of its own
//   fields. Every offset below was read back out of the user's retail gamemd.exe
//   v1.001 from the citing instruction beside it. YRpp ships a
//   MechLocomotionClass header with no member list at all, so nothing here is a
//   lift: the names below come from this class's own readers.
//
//   sizeof = 0x34, proven twice and independently:
//     * the single allocation site - `PUSH 0x34` @0x006C4DBC, `CALL operator new
//       (0x007C8E17)` @0x006C4DBE, `MOV ECX,EAX`, `CALL 0x005AFEF0` @0x006C4DCC;
//     * the class's own virtual size accessor, persist-vtable (0x007EDC38) slot
//       +0x24 = 0x005B1B40, whose entire body is `MOV EAX,0x34 / RET`.
//   The layout CLOSES: the last ctor write is the byte at 0x30 (@0x005AFF2E) and
//   0x30+1 = 0x31 <= 0x34, with three untouched tail bytes.
//
//   RTTI: ".?AVMechLocomotionClass@@", type descriptor 0x0082C228, has exactly
//   TWO complete object locators - 0x00805C88 (base offset 0, vtable 0x007EDC38,
//   IPersistStream) and 0x00805C28 (base offset 4, vtable 0x007EDB6C,
//   ILocomotion). No IPiggyback. So this class has FlyLocomotionClass's base
//   shape: it derives LocomotionClass directly and its own data starts at 0x18,
//   with 0x18 a data member rather than a vptr.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_MECH_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_MECH_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct MechLocomotionClass : LocomotionLayoutView_0055A6C0
{
    CoordStruct Destination;      // +0x18 ctor `LEA EAX,[ESI+0x18]` @0x005AFEFE
                                  //       then X @0x005AFF01, Y @0x005AFF0A,
                                  //       Z @0x005AFF16 from the file-scope
                                  //       globals 0x00ABEE10 / 0x00ABEE14 /
                                  //       0x00ABEE18. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x005AFF80
                                  //       copies 0x18 (if+0x14) @0x005AFF94,
                                  //       0x1C @0x005AFF97 and 0x20 @0x005AFF9A
                                  //       out.

    CoordStruct HeadToCoord;      // +0x24 ctor `LEA EDX,[ESI+0x24]` @0x005AFF13
                                  //       then @0x005AFF1E, @0x005AFF26,
                                  //       @0x005AFF38 from the same globals.
                                  //       CONFIRMED BY READER:
                                  //       ILocomotion::Head_To_Coord 0x005AFFE0
                                  //       reads 0x24 (if+0x20) @0x005AFFEC,
                                  //       0x28 @0x005AFFF3 and 0x2C @0x005B0000
                                  //       and compares them against the same
                                  //       three globals - which is what
                                  //       separates this coordinate from
                                  //       Destination.

    char        unknown_30;       // +0x30 ctor `MOV BYTE PTR [ESI+0x30],0x0`
                                  //       @0x005AFF2E; no reader found
    char        unknown_31[3];    // +0x31 untouched tail to sizeof 0x34
};

GG_STATIC_ASSERT(offsetof(MechLocomotionClass, Destination) == 0x18);
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, HeadToCoord) == 0x24);
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, unknown_30)  == 0x30);
GG_STATIC_ASSERT(sizeof(MechLocomotionClass)                == 0x34);

#endif  // GG_MATCH_LAYOUT_MECH_LOCOMOTION_CLASS_H
