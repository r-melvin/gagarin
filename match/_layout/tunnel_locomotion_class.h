// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TunnelLocomotionClass::TunnelLocomotionClass 0x00728A00, which chains
//   the LocomotionClass base constructor 0x0055A6C0 and writes every one of its
//   own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it. YRpp ships a
//   TunnelLocomotionClass header with no member list, so nothing here is a lift.
//
//   sizeof = 0x3C, proven twice and independently:
//     * the single allocation site - `PUSH 0x3C` @0x006C463C, `CALL operator new
//       (0x007C8E17)` @0x006C463E, `MOV ECX,EAX`, `CALL 0x00728A00` @0x006C464C;
//     * the class's own virtual size accessor, persist-vtable (0x007F5AF0) slot
//       +0x24 = 0x0072A200, whose entire body is `MOV EAX,0x3C / RET`.
//   The layout CLOSES: the last ctor write is the byte at 0x38 (@0x00728A39) and
//   0x38+1 = 0x39 <= 0x3C, with three untouched tail bytes.
//
//   RTTI: ".?AVTunnelLocomotionClass@@", type descriptor 0x00844AA0, has exactly
//   TWO complete object locators - 0x0080CB48 (base offset 0, vtable 0x007F5AF0,
//   IPersistStream) and 0x0080CAE8 (base offset 4, vtable 0x007F5A24,
//   ILocomotion). No IPiggyback. So this class has FlyLocomotionClass's base
//   shape: it derives LocomotionClass directly and its own data starts at 0x18,
//   with 0x18 a data member rather than a vptr.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct TunnelLocomotionClass : LocomotionLayoutView_0055A6C0
{
    int          unknown_18;      // +0x18 ctor `MOV [ESI+0x18],EAX` @0x00728A0D
                                  //       (=0). Read by ILocomotion::Is_Moving
                                  //       0x00728A50 - `MOV ECX,[EAX+0x14]`
                                  //       @0x00728A54 (if+0x14 = object 0x18),
                                  //       `TEST ECX,ECX` @0x00728A57 - so the
                                  //       class is "moving" exactly when this
                                  //       dword is non-zero. That makes it a
                                  //       state word, but nothing pins WHICH
                                  //       state, so it is not named.

    CoordStruct  Destination;     // +0x1C ctor `LEA ECX,[ESI+0x1c]` @0x00728A0A
                                  //       then X @0x00728A16, Y @0x00728A1E,
                                  //       Z @0x00728A27 from the file-scope
                                  //       globals 0x00B0F910 / 0x00B0F914 /
                                  //       0x00B0F918. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x00728A90
                                  //       copies 0x1C (if+0x18) @0x00728AA4,
                                  //       0x20 @0x00728AA7 and 0x24 @0x00728AAA
                                  //       out.

    CDTimerClass unknown_28;      // +0x28 (0xC) StartTime @0x00728A30 from the
                                  //       frame counter 0x00A8ED84; clock slot
                                  //       0x2C never written; TimeLeft 0x30
                                  //       @0x00728A33 (=0). The family's timer
                                  //       signature; what it times is not
                                  //       proven, so it is not named.

    int          unknown_34;      // +0x34 ctor @0x00728A36 (=0); no reader found
    char         unknown_38;      // +0x38 ctor `MOV [ESI+0x38],AL` @0x00728A39
                                  //       (=0); no reader found
    char         unknown_39[3];   // +0x39 untouched tail to sizeof 0x3C
};

GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_18)  == 0x18);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, Destination) == 0x1C);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_28)  == 0x28);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_34)  == 0x34);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionClass, unknown_38)  == 0x38);
GG_STATIC_ASSERT(sizeof(TunnelLocomotionClass)                == 0x3C);

#endif  // GG_MATCH_LAYOUT_TUNNEL_LOCOMOTION_CLASS_H
