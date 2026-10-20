// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: HoverLocomotionClass::HoverLocomotionClass 0x00513C20, which chains
//   the LocomotionClass base constructor 0x0055A6C0 and writes every one of its
//   own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it.
//
//   sizeof = 0x78, proven twice and independently:
//     * the single allocation site - `PUSH 0x78` @0x006C433C, `CALL operator new
//       (0x007C8E17)` @0x006C433E, `MOV ECX,EAX` @0x006C434A, `CALL 0x00513C20`;
//     * the class's own virtual size accessor, persist-vtable (0x007EADC8) slot
//       +0x24 = 0x005172B0, whose entire body is `MOV EAX,0x78 / RET`.
//   The layout CLOSES: the last ctor write is the byte at 0x70 (@0x00513C8E) and
//   0x70+1 = 0x71 <= 0x78; the seven-byte tail is untouched (see unknown_71).
//
//   RTTI: ".?AVHoverLocomotionClass@@", type descriptor 0x008254B8, has exactly
//   TWO complete object locators - 0x00803288 (base offset 0, vtable 0x007EADC8,
//   IPersistStream) and 0x00803228 (base offset 4, vtable 0x007EACFC,
//   ILocomotion). Base chain: HoverLocomotionClass / LocomotionClass /
//   IPersistStream / IPersist / IUnknown / ILocomotion / IUnknown - no
//   IPiggyback. So this class has FlyLocomotionClass's base shape: it derives
//   LocomotionClass directly and its own data starts at 0x18, with 0x18 a data
//   member rather than a vptr.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_HOVER_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_HOVER_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct HoverLocomotionClass : LocomotionClass
{
    CoordStruct Destination;      // +0x18 ctor `LEA EAX,[ESI+0x18]` @0x00513C2F
                                  //       then X @0x00513C34, Y @0x00513C3D,
                                  //       Z @0x00513C49 from the file-scope
                                  //       globals 0x00A8F180 / 0x00A8F184 /
                                  //       0x00A8F188. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x00514CB0
                                  //       reads 0x18 (if+0x14) @0x00514CBC,
                                  //       0x1C @0x00514CC7 and 0x20 @0x00514CD4
                                  //       and compares them against the same
                                  //       three globals.

    CoordStruct HeadToCoord;      // +0x24 ctor `LEA EDX,[ESI+0x24]` @0x00513C46
                                  //       then @0x00513C51, @0x00513C59,
                                  //       @0x00513C64 from the same globals.
                                  //       CONFIRMED BY READER: Head_To_Coord
                                  //       0x00514D10 reads 0x24 (if+0x20)
                                  //       @0x00514D1C, 0x28 @0x00514D23 and
                                  //       0x2C @0x00514D30.

    FacingClass LocomotionFacing; // +0x30 (0x18) ctor takes its address
                                  //       `LEA ECX,[ESI+0x30]` @0x00513C61,
                                  //       pushes a zero rate-of-turn
                                  //       @0x00513C3C and calls the FacingClass
                                  //       constructor 0x004C91E0 @0x00513C67.
                                  //       Sizeof 0x18 is what puts the next
                                  //       ctor-written member at 0x48.

    double      unknown_48;       // +0x48 ctor zeroes both halves - low
                                  //       @0x00513C6C, high @0x00513C78
    double      unknown_50;       // +0x50 ctor low @0x00513C6F, high @0x00513C7B
    double      unknown_58;       // +0x58 ctor low @0x00513C72 (=0), high
                                  //       @0x00513C7E = 0x3FF00000. That high
                                  //       word with a zero low word is exactly
                                  //       the IEEE-754 double 1.0, which is what
                                  //       proves all four of these are doubles
                                  //       and not int pairs: the ctor writes the
                                  //       four low halves first (0x48, 0x50,
                                  //       0x58, 0x60) and then the four high
                                  //       halves. No reader of any of them was
                                  //       found, so none is named (YRpp guesses
                                  //       MaxSpeed / CurrentSpeed / BoostSpeed /
                                  //       CurrentWobbles).
    double      unknown_60;       // +0x60 ctor low @0x00513C75, high @0x00513C85

    char        unknown_68;       // +0x68 ctor `MOV [ESI+0x68],BL` @0x00513C88
                                  //       (=0)
    char        unknown_69[3];    // +0x69 alignment; never written, never read
    int         unknown_6C;       // +0x6C ctor @0x00513C8B (=0)
    char        unknown_70;       // +0x70 ctor `MOV [ESI+0x70],BL` @0x00513C8E
                                  //       (=0)
    char        unknown_71[7];    // +0x71 untouched tail to sizeof 0x78. Seven
                                  //       bytes is a wide tail; the ctor writes
                                  //       nothing here and no read at any width
                                  //       was found, so it stays padding rather
                                  //       than an invented member.
};

GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Destination)      == 0x18);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, HeadToCoord)      == 0x24);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, LocomotionFacing) == 0x30);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_48)       == 0x48);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_50)       == 0x50);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_58)       == 0x58);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_60)       == 0x60);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_68)       == 0x68);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_6C)       == 0x6C);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, unknown_70)       == 0x70);
GG_STATIC_ASSERT(sizeof(HoverLocomotionClass)                     == 0x78);

#endif  // GG_MATCH_LAYOUT_HOVER_LOCOMOTION_CLASS_H
