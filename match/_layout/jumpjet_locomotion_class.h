// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracles: JumpjetLocomotionClass::JumpjetLocomotionClass 0x0054AC40 for
//   0x40..0x97, and the class's own ILocomotion::Link_To_Object override
//   0x0054AD30 for 0x1C..0x3F, which the constructor never touches. Every offset
//   below was read back out of the user's retail gamemd.exe v1.001 from the
//   citing instruction beside it.
//
//   sizeof = 0x98, proven twice and independently:
//     * the single allocation site - `PUSH 0x98` @0x006C41BC, `CALL operator new
//       (0x007C8E17)` @0x006C41C1, `MOV ECX,EAX` @0x006C41CD, `CALL 0x0054AC40`
//       @0x006C41CF;
//     * the class's own virtual size accessor, persist-vtable (0x007ECE34) slot
//       +0x24 = 0x0054DF90, whose entire body is `MOV EAX,0x98 / RET`.
//   The layout CLOSES EXACTLY: the last member is the dword at 0x94
//   (@0x0054ACB5) and 0x94+4 = 0x98 = sizeof, with no tail at all.
//
//   RTTI: ".?AVJumpjetLocomotionClass@@", type descriptor 0x00829648, THREE
//   complete object locators - 0x00804CF0 (base offset 0, vtable 0x007ECE34,
//   IPersistStream), 0x00804C88 (base offset 4, vtable 0x007ECD68, ILocomotion)
//   and 0x00804C70 (base offset 0x18, vtable 0x007ECD44, IPiggyback). So 0x18 is
//   a VPTR, this class cannot share FlyLocomotionClass's two-locator base, and
//   its own data starts at 0x1C.
//
//   THE 0x1C..0x3F BLOCK. The constructor writes nothing between the piggyback
//   vptr and 0x40 - a 0x24-byte hole. It is filled by Link_To_Object 0x0054AD30,
//   which calls the owner's Get_Techno_Type (`CALL [EAX+0x84]`) once per field
//   and copies one TechnoTypeClass member into each slot. In that body EBX is
//   the FootClass argument and EBP is the ILocomotion interface pointer
//   (object+4), so each `MOV [EBP+N]` is object offset N+4. The source offsets
//   are the Jumpjet* block already proven in match/_layout/techno_type_class.h,
//   which is what lets these nine be NAMED rather than left unknown.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_JUMPJET_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_JUMPJET_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

class JumpjetLocomotionClass : public LocomotionPiggybackBase
{
public:
    int         TurnRate;         // +0x1C <- TechnoTypeClass::JumpjetTurnRate
                                  //       (type+0xD70, read @0x0054AD49, stored
                                  //       `MOV [EBP+0x18],ECX` @0x0054AD4F).
                                  //       Re-read @0x0054ADF8 and passed as the
                                  //       rate-of-turn to the FacingClass
                                  //       constructor 0x004C91E0 @0x0054AE00.
    int         Speed;            // +0x20 <- JumpjetSpeed (type+0xD74,
                                  //       @0x0054AD5C, stored @0x0054AD64)
    float       Climb;            // +0x24 <- JumpjetClimb (type+0xD78,
                                  //       @0x0054AD6F, stored @0x0054AD77);
                                  //       float because the source member is
                                  //       float in techno_type_class.h and the
                                  //       copy is a plain dword move
    float       Crash;            // +0x28 <- JumpjetCrash (type+0xD7C,
                                  //       @0x0054AD82, stored @0x0054AD8A)
    int         Height;           // +0x2C <- JumpjetHeight (type+0xD80,
                                  //       @0x0054AD9B), clamped up to twice the
                                  //       file-scope global 0x00ABC5E8
                                  //       (`ADD ECX,ECX` @0x0054ADA1,
                                  //       `CMP EAX,ECX` @0x0054ADA3) before the
                                  //       store @0x0054ADA9
    float       Accel;            // +0x30 <- JumpjetAccel (type+0xD84,
                                  //       @0x0054ADB6, stored @0x0054ADBE)
    float       Wobbles;          // +0x34 <- JumpjetWobbles (type+0xD88,
                                  //       @0x0054ADC9, stored @0x0054ADD1)
    int         unknown_38;       // +0x38 <- type+0xD90 (@0x0054ADDC, stored
                                  //       @0x0054ADE4). techno_type_class.h does
                                  //       not yet name type+0xD90, so this slot
                                  //       is proven but unnamed (YRpp guesses
                                  //       "Deviation").
    char        NoWobbles;        // +0x3C <- TechnoTypeClass::JumpjetNoWobbles
                                  //       (type+0xD8C), copied as a BYTE:
                                  //       `MOV AL,[EAX+0xd8c]` @0x0054ADEF,
                                  //       `MOV [EBP+0x38],AL` @0x0054ADF5
    char        unknown_3D[3];    // +0x3D alignment behind the bool at 0x3C; no
                                  //       access at any width

    CoordStruct Destination;      // +0x40 ctor `LEA EAX,[ESI+0x40]` @0x0054AC51
                                  //       then X @0x0054AC59, Y @0x0054AC61,
                                  //       Z @0x0054AC70 from the file-scope
                                  //       globals 0x00ABC5A8 / 0x00ABC5AC /
                                  //       0x00ABC5B0. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x0054AE60
                                  //       copies 0x40 (if+0x3c) @0x0054AE74,
                                  //       0x44 @0x0054AE77 and 0x48 @0x0054AE7A
                                  //       out.

    char        unknown_4C;       // +0x4C ctor `MOV [ESI+0x4c],BL` @0x0054AC6A
                                  //       (=0); no reader found
    char        unknown_4D[3];    // +0x4D alignment; no access at any width
    int         unknown_50;       // +0x50 ctor @0x0054AC6D (=0). Read by
                                  //       Head_To_Coord 0x0054D9B0
                                  //       (`MOV ECX,[EAX+0x4c]` @0x0054D9B6,
                                  //       if+0x4c = object 0x50) and branched on
                                  //       non-zero, so it is a state/flag word;
                                  //       nothing pins which state, so it is not
                                  //       named (YRpp guesses "State").

    FacingClass LocomotionFacing; // +0x54 (0x18). ctor takes its address
                                  //       `LEA EDI,[ESI+0x54]` @0x0054AC56 and
                                  //       constructs it @0x0054AC82 with the
                                  //       rate-of-turn [[0x008871E0]+0x40C],
                                  //       then drives it @0x0054ACDC
                                  //       (0x004C9220) and @0x0054ACED
                                  //       (0x004C9300) with 0x4000. Its 0x18
                                  //       width is proven independently by
                                  //       Link_To_Object, which builds one on
                                  //       the stack and copies it in with
                                  //       `LEA EAX,[EBP+0x50]` @0x0054AE05
                                  //       (object 0x54), `MOV ECX,0x6`
                                  //       @0x0054AE08 and `REP MOVSD`
                                  //       @0x0054AE13 - six dwords.
    int         unknown_6C;       // +0x6C never written by either body and no
                                  //       read at any width; the gap between the
                                  //       FacingClass and the 8-byte-aligned
                                  //       pair at 0x70

    int         unknown_70;       // +0x70 ctor @0x0054AC87 (=0)
    int         unknown_74;       // +0x74 ctor @0x0054AC93 (=0)
    int         unknown_78;       // +0x78 ctor @0x0054AC8A (=0)
    int         unknown_7C;       // +0x7C ctor @0x0054AC96 (=0). 0x70/0x74 and
                                  //       0x78/0x7C are 8-byte-aligned pairs the
                                  //       ctor zeroes low-halves-first exactly
                                  //       as HoverLocomotionClass zeroes its
                                  //       doubles, but here no store carries a
                                  //       non-zero high word and no float read
                                  //       was found, so they go in as four ints
                                  //       rather than the two doubles YRpp
                                  //       guesses.
    int         unknown_80;       // +0x80 ctor @0x0054AC99 (=0)
    int         unknown_84;       // +0x84 never written, never read - the gap
                                  //       before the 8-byte-aligned pair at 0x88
    int         unknown_88;       // +0x88 ctor @0x0054AC8D (=0)
    int         unknown_8C;       // +0x8C ctor @0x0054AC9F (=0)
    char        unknown_90;       // +0x90 ctor `MOV [ESI+0x90],BL` @0x0054ACA5
    char        unknown_91;       // +0x91 ctor @0x0054ACAB (=0)
    char        unknown_92[2];    // +0x92 alignment; no access at any width

    void*       Piggybackee;      // +0x94 ILocomotion*; ctor @0x0054ACB5 (=0).
                                  //       Last member; 0x94+4 = sizeof.
};

GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, TurnRate)         == 0x1C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Speed)            == 0x20);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Climb)            == 0x24);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Crash)            == 0x28);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Height)           == 0x2C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Accel)            == 0x30);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Wobbles)          == 0x34);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_38)       == 0x38);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, NoWobbles)        == 0x3C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Destination)      == 0x40);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_4C)       == 0x4C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_50)       == 0x50);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, LocomotionFacing) == 0x54);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_6C)       == 0x6C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_70)       == 0x70);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_78)       == 0x78);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_80)       == 0x80);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_84)       == 0x84);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_88)       == 0x88);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_8C)       == 0x8C);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_90)       == 0x90);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, unknown_91)       == 0x91);
GG_STATIC_ASSERT(offsetof(JumpjetLocomotionClass, Piggybackee)      == 0x94);
GG_STATIC_ASSERT(sizeof(JumpjetLocomotionClass)                     == 0x98);

#endif  // GG_MATCH_LAYOUT_JUMPJET_LOCOMOTION_CLASS_H
