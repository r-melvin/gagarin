// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: RocketLocomotionClass::RocketLocomotionClass 0x00661EC0, which chains
//   the LocomotionClass base constructor 0x0055A6C0 and writes every one of its
//   own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it. The file-scope
//   configuration block this constructor reads is already documented in
//   match/movement/rocket_locomotion_globals.h.
//
//   sizeof = 0x60, proven twice and independently:
//     * the single allocation site - `PUSH 0x60` @0x006C44BC, `CALL operator new
//       (0x007C8E17)` @0x006C44BE, `MOV ECX,EAX`, `CALL 0x00661EC0` @0x006C44CC;
//     * the class's own virtual size accessor, persist-vtable (0x007F0BE8) slot
//       +0x24 = 0x006635B0, whose entire body is `MOV EAX,0x60 / RET`.
//   The layout CLOSES: the last ctor write is the dword at 0x58 (@0x00661F12)
//   and 0x58+4 = 0x5C <= 0x60, leaving one untouched dword.
//
//   RTTI: ".?AVRocketLocomotionClass@@", type descriptor 0x008399C8, has exactly
//   TWO complete object locators - 0x00808968 (base offset 0, vtable 0x007F0BE8,
//   IPersistStream) and 0x00808908 (base offset 4, vtable 0x007F0B1C,
//   ILocomotion). No IPiggyback. So this class has FlyLocomotionClass's base
//   shape - it derives LocomotionClass directly and its own data starts at 0x18,
//   with 0x18 a data member rather than a vptr. (The batch brief listed only
//   Hover/Mech/Tunnel as two-locator; Rocket is a fourth, confirmed here.)
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_ROCKET_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_ROCKET_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct RocketLocomotionClass : LocomotionClass
{
    CoordStruct  Destination;     // +0x18 ctor `LEA EAX,[ESI+0x18]` @0x00661ECE
                                  //       then X @0x00661ED1, Y @0x00661EDA,
                                  //       Z @0x00661EE3 from the rocket TU's own
                                  //       configuration block 0x00B04E38 /
                                  //       0x00B04E3C / 0x00B04E40. CONFIRMED BY
                                  //       READER: ILocomotion::Destination
                                  //       0x00661FB0 copies 0x18 (if+0x14)
                                  //       @0x00661FBA, 0x1C @0x00661FBD and
                                  //       0x20 @0x00661FC0 out.

    CDTimerClass unknown_24;      // +0x24 (0xC) StartTime @0x00661EEE from the
                                  //       frame counter 0x00A8ED84; clock slot
                                  //       0x28 never written; TimeLeft 0x2C
                                  //       @0x00661EF1 (=0). The shape is the
                                  //       family's unmistakable timer signature;
                                  //       what it times is not proven, so it is
                                  //       not named.
    int          unknown_30;      // +0x30 ctor @0x00661EF4 (=0). YRpp folds this
                                  //       into the preceding timer as a
                                  //       RateTimer's Rate, which would be
                                  //       consistent, but unlike Drive there is
                                  //       no FIDIV-by-Rate reader here to prove
                                  //       it, so it stays a separate int.

    CDTimerClass unknown_34;      // +0x34 (0xC) StartTime @0x00661F00 from
                                  //       0x00A8ED84; clock slot 0x38 never
                                  //       written; TimeLeft 0x3C @0x00661EFD
                                  //       (=0). Second timer, same signature.

    int          unknown_40;      // +0x40 ctor @0x00661F06 (=0)
    int          unknown_44;      // +0x44 never written by the ctor, no read
                                  //       found - the gap before the
                                  //       8-byte-aligned pair at 0x48
    int          unknown_48;      // +0x48 ctor @0x00661F03 (=0)
    int          unknown_4C;      // +0x4C ctor @0x00661F09 (=0). 0x48/0x4C is an
                                  //       8-byte-aligned pair zeroed as two
                                  //       dwords; no non-zero high word and no
                                  //       float read, so two ints rather than
                                  //       the double YRpp guesses.
    char         unknown_50;      // +0x50 ctor `MOV BYTE PTR [ESI+0x50],1`
                                  //       @0x00661F15 - the only member of this
                                  //       class the constructor does not zero
    char         unknown_51;      // +0x51 ctor @0x00661F0C (=0)
    char         unknown_52[2];   // +0x52 alignment; no access at any width
    int          unknown_54;      // +0x54 ctor @0x00661F0F (=0)
    int          unknown_58;      // +0x58 ctor @0x00661F12 (=0)
    int          unknown_5C;      // +0x5C untouched tail to sizeof
};

GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, Destination) == 0x18);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_24)  == 0x24);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_30)  == 0x30);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_34)  == 0x34);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_40)  == 0x40);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_44)  == 0x44);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_48)  == 0x48);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_4C)  == 0x4C);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_50)  == 0x50);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_51)  == 0x51);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_54)  == 0x54);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_58)  == 0x58);
GG_STATIC_ASSERT(offsetof(RocketLocomotionClass, unknown_5C)  == 0x5C);
GG_STATIC_ASSERT(sizeof(RocketLocomotionClass)                == 0x60);

#endif  // GG_MATCH_LAYOUT_ROCKET_LOCOMOTION_CLASS_H
