// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TeleportLocomotionClass::TeleportLocomotionClass 0x00718000, which
//   chains the LocomotionClass base constructor 0x0055A6C0 and writes every one
//   of its own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it.
//
//   sizeof = 0x4C, proven twice and independently:
//     * the single allocation site - `PUSH 0x4C` @0x006C4C3C, `CALL operator new
//       (0x007C8E17)` @0x006C4C3E, `MOV ECX,EAX`, `CALL 0x00718000` @0x006C4C4C;
//     * the class's own virtual size accessor, persist-vtable (0x007F50CC) slot
//       +0x24 = 0x0071A120, whose entire body is `MOV EAX,0x4C / RET`.
//   The layout CLOSES EXACTLY: the last member is the dword at 0x48
//   (@0x0071805B) and 0x48+4 = 0x4C = sizeof, with no tail.
//
//   RTTI: ".?AVTeleportLocomotionClass@@", type descriptor 0x00844538, THREE
//   complete object locators - 0x0080C1E0 (base offset 0, vtable 0x007F50CC,
//   IPersistStream), 0x0080C178 (base offset 4, vtable 0x007F5000, ILocomotion)
//   and 0x0080C160 (base offset 0x18, vtable 0x007F4FDC, IPiggyback). So 0x18 is
//   a VPTR and this class cannot share FlyLocomotionClass's two-locator base;
//   its own data starts at 0x1C.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct TeleportLocomotionClass : LocomotionPiggybackBase
{
    CoordStruct  Destination;     // +0x1C ctor `LEA EAX,[ESI+0x1c]` @0x0071800E
                                  //       then X @0x00718011, Y @0x0071801A,
                                  //       Z @0x00718026 from the file-scope
                                  //       globals 0x00B0EBF8 / 0x00B0EBFC /
                                  //       0x00B0EC00. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x007180A0
                                  //       copies 0x1C (if+0x18) @0x007180B4,
                                  //       0x20 @0x007180B7 and 0x24 @0x007180BA
                                  //       out.

    CoordStruct  unknown_28;      // +0x28 a second coordinate, shape proven:
                                  //       `LEA EDX,[ESI+0x28]` @0x00718023 takes
                                  //       its address and the SAME three globals
                                  //       are stored to 0x28 @0x0071802E, 0x2C
                                  //       @0x00718036 and 0x30 @0x0071803E. What
                                  //       it MEANS is not proven - no reader of
                                  //       0x28 was found - so it is not named
                                  //       (YRpp guesses "LastCoords").

    char         IsMoving;        // +0x34 ctor `MOV [ESI+0x34],AL` @0x00718043
                                  //       (=0). CONFIRMED BY READER:
                                  //       ILocomotion::Is_Moving 0x00718080 is
                                  //       `CMP BYTE PTR [EAX+0x30],0x1`
                                  //       @0x00718084 / `SETZ AL` @0x00718088 -
                                  //       if+0x30 = object 0x34, and that
                                  //       predicate IS the member's meaning.
    char         unknown_35;      // +0x35 ctor @0x00718046 (=0); no reader found
    char         unknown_36;      // +0x36 ctor @0x00718049 (=0); no reader found
    char         unknown_37;      // +0x37 alignment; no access at any width
    int          unknown_38;      // +0x38 ctor @0x0071804C (=0)

    CDTimerClass unknown_3C;      // +0x3C (0xC) StartTime @0x00718058 from the
                                  //       frame counter 0x00A8ED84; clock slot
                                  //       0x40 never written; TimeLeft 0x44
                                  //       @0x00718055 (=0). The family's timer
                                  //       signature; what it times is not
                                  //       proven, so it is not named.

    void*        Piggybackee;     // +0x48 ILocomotion*; ctor @0x0071805B (=0).
                                  //       Last member; 0x48+4 = sizeof.
};

GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, Destination) == 0x1C);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_28)  == 0x28);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, IsMoving)    == 0x34);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_35)  == 0x35);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_36)  == 0x36);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_38)  == 0x38);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_3C)  == 0x3C);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, Piggybackee) == 0x48);
GG_STATIC_ASSERT(sizeof(TeleportLocomotionClass)                == 0x4C);

#endif  // GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H
