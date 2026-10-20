// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ShipLocomotionClass::ShipLocomotionClass 0x0069EC50, which chains
//   the LocomotionClass base constructor 0x0055A6C0 and then writes every one of
//   its own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 (sha256 1cdd1180...4298c) from the citing instruction
//   named beside it. Nothing here rests on scripts/data/*.json.
//
//   sizeof = 0x70, proven twice and independently:
//     * the single allocation site - `PUSH 0x70` @0x006C4F3C, `CALL operator new
//       (0x007C8E17)` @0x006C4F3E, `MOV ECX,EAX` @0x006C4F4A, `CALL 0x0069EC50`
//       @0x006C4F4C;
//     * the class's own virtual size accessor, persist-vtable (0x007F2E58) slot
//       +0x24 = 0x006A42A0, whose entire body is `MOV EAX,0x70 / RET`.
//   The layout CLOSES: last ctor write is the dword at 0x68 (@0x0069ECCF) and
//   0x68+4 = 0x6C <= 0x70, leaving one untouched dword.
//
//   RTTI: ".?AVShipLocomotionClass@@", type descriptor 0x0083F880, THREE
//   complete object locators - 0x00809408 (base offset 0, vtable 0x007F2E58,
//   IPersistStream), 0x008093A0 (base offset 4, vtable 0x007F2D8C, ILocomotion)
//   and 0x00809388 (base offset 0x18, vtable 0x007F2D68, IPiggyback). Base
//   chain ends ... ILocomotion / IUnknown / IPiggyback / IUnknown. So 0x18 is a
//   VPTR, this class cannot share FlyLocomotionClass's two-locator base, and its
//   own data starts at 0x1C.
//
//   ShipLocomotionClass and DriveLocomotionClass are the same layout, and their
//   constructors are instruction-for-instruction identical apart from the
//   file-scope globals and the three vtable immediates. Every member below is
//   nonetheless cited from SHIP's own instructions, and the four interface
//   accessors used as readers are Ship's own overrides, not Drive's.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct ShipLocomotionClass : LocomotionPiggybackBase
{
    int         unknown_1C;       // +0x1C ctor `MOV [ESI+0x1c],EAX` @0x0069EC5D
                                  //       (=0); the ramp/slope pair with 0x20 -
                                  //       not distinguished by any reader, so
                                  //       neither is named
    int         unknown_20;       // +0x20 ctor @0x0069EC60 (=0)

    RateTimer   SlopeTimer;       // +0x24 (0x10) StartTime @0x0069EC6C from the
                                  //       frame counter 0x00A8ED84; clock slot
                                  //       0x28 never written; TimeLeft 0x2C
                                  //       @0x0069EC69 (=0); Rate 0x30
                                  //       @0x0069EC6F (=0). The RateTimer shape
                                  //       at this offset is proven in the
                                  //       identical Drive body by Draw_Matrix
                                  //       0x004AFF60 (see
                                  //       drive_locomotion_class.h).

    CoordStruct Destination;      // +0x34 ctor `LEA EDX,[ESI+0x34]` @0x0069EC5A
                                  //       then X @0x0069EC78, Y @0x0069EC80,
                                  //       Z @0x0069EC89 from the file-scope
                                  //       globals 0x00B077F8 / 0x00B077FC /
                                  //       0x00B07800. CONFIRMED BY READER:
                                  //       Ship's ILocomotion::Destination
                                  //       0x0069F3A0 copies 0x34 (if+0x30)
                                  //       @0x0069F3AA, 0x38 @0x0069F3AD and
                                  //       0x3C @0x0069F3B0 out.

    CoordStruct HeadToCoord;      // +0x40 ctor `LEA EDX,[ESI+0x40]` @0x0069EC92
                                  //       then @0x0069EC95, @0x0069EC9E,
                                  //       @0x0069ECAD. CONFIRMED BY READER:
                                  //       Ship's Head_To_Coord 0x0069F3D0 reads
                                  //       0x40 (if+0x3c) @0x0069F3DC and 0x44
                                  //       @0x0069F3E3 against the same globals.

    int         SpeedAccum;       // +0x4C ctor @0x0069ECAA (=0). CONFIRMED BY
                                  //       READER: Ship's ILocomotion slot 49
                                  //       0x006A4250 is `MOV EAX,[EAX+0x48]`
                                  //       @0x006A4254.
    int         unknown_50;       // +0x50 ctor @0x0069ECA7 (=0)
    int         unknown_54;       // +0x54 ctor @0x0069ECB3 (=0). Two dwords the
                                  //       ctor zeroes; no reader at any width,
                                  //       so not the double YRpp guesses.

    int         TrackNumber;      // +0x58 ctor @0x0069ECB6 (= -1). CONFIRMED BY
                                  //       READER: Ship's ILocomotion slot 47
                                  //       0x006A4230 is `MOV EAX,[EAX+0x54]`
                                  //       @0x006A4234.
    int         TrackIndex;       // +0x5C ctor @0x0069ECB9 (= -1). CONFIRMED BY
                                  //       READER: Ship's slot 48 0x006A4240 is
                                  //       `MOV EAX,[EAX+0x58]` @0x006A4244.

    char        unknown_60;       // +0x60 ctor @0x0069ECBC (=0); the
                                  //       short-track flag in the identical
                                  //       Drive body, but Ship's own
                                  //       Will_Jump_Tracks was not read, so it
                                  //       is not named here
    char        unknown_61;       // +0x61 ctor @0x0069ECBF (=0)
    char        unknown_62;       // +0x62 ctor @0x0069ECC2 (=0)
    char        unknown_63;       // +0x63 ctor @0x0069ECC5 (=0)
    char        unknown_64;       // +0x64 ctor @0x0069ECC8 (=0)
    char        UnLocked;         // +0x65 ctor @0x0069ECCB (= 1). CONFIRMED BY
                                  //       READER: Ship's ILocomotion slot 45
                                  //       Lock 0x006A4210 writes
                                  //       `MOV BYTE PTR [EAX+0x61],0`
                                  //       @0x006A4214 and slot 46 Unlock
                                  //       0x006A4220 writes 1 @0x006A4224.
    char        unknown_66[2];    // +0x66 alignment; never written, never read

    void*       Piggybackee;      // +0x68 ILocomotion*; ctor @0x0069ECCF (=0).
                                  //       CONFIRMED BY READER: the destructor
                                  //       0x0069ECF0 loads it @0x0069ED07 and
                                  //       Releases it through its own vtable,
                                  //       exactly as Drive's does.
    int         unknown_6C;       // +0x6C untouched tail to sizeof
};

GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_1C)  == 0x1C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_20)  == 0x20);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, SlopeTimer)  == 0x24);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, Destination) == 0x34);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, HeadToCoord) == 0x40);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, SpeedAccum)  == 0x4C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_50)  == 0x50);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_54)  == 0x54);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, TrackNumber) == 0x58);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, TrackIndex)  == 0x5C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_60)  == 0x60);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_61)  == 0x61);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_62)  == 0x62);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_63)  == 0x63);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_64)  == 0x64);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, UnLocked)    == 0x65);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, Piggybackee) == 0x68);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_6C)  == 0x6C);
GG_STATIC_ASSERT(sizeof(ShipLocomotionClass)                == 0x70);

#endif  // GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H
