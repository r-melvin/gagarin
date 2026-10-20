// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: DriveLocomotionClass::DriveLocomotionClass 0x004AF540, which chains
//   the LocomotionClass base constructor 0x0055A6C0 at offset 0 and then writes
//   every one of its own fields. Every offset below was read back out of the
//   user's retail gamemd.exe v1.001 (sha256 1cdd1180...4298c) from the citing
//   instruction named beside it. Nothing here rests on scripts/data/*.json.
//
//   sizeof = 0x70, proven twice and independently:
//     * the single allocation site - `PUSH 0x70` @0x006C403C, `CALL operator new
//       (0x007C8E17)` @0x006C403E, `MOV ECX,EAX` @0x006C404A, `CALL 0x004AF540`
//       @0x006C404C;
//     * the class's own virtual size accessor, persist-vtable (0x007E7F7C) slot
//       +0x24 = 0x004B4CF0, whose entire body is `MOV EAX,0x70 / RET`.
//   The layout CLOSES: the last member the constructor writes is the dword at
//   0x68 (@0x004AF5BF) and 0x68+4 = 0x6C <= 0x70, leaving one untouched dword.
//
//   RTTI, read out of the binary: ".?AVDriveLocomotionClass@@", type descriptor
//   0x00820248, has THREE complete object locators - 0x007FFEB0 (base offset 0,
//   vtable 0x007E7F7C, IPersistStream), 0x007FFDE8 (base offset 4, vtable
//   0x007E7EB0, ILocomotion) and 0x007FFDD0 (base offset 0x18, vtable
//   0x007E7E8C, IPiggyback). Base chain: DriveLocomotionClass / LocomotionClass
//   / IPersistStream / IPersist / IUnknown / ILocomotion / IUnknown /
//   IPiggyback / IUnknown. So 0x18 is a VPTR here, this class CANNOT share
//   FlyLocomotionClass's two-locator base, and its own data starts at 0x1C.
//
//   ShipLocomotionClass has an instruction-for-instruction identical
//   constructor and the identical layout; the two are kept in separate headers
//   with separate citations rather than aliased.
//
//   INTERFACE-RELATIVE READS: the ILocomotion methods are __stdcall on the
//   interface at base offset 4, so a `[reg+N]` in one of them is object offset
//   N+4. Such citations are marked "(if+N)".
#ifndef GG_MATCH_LAYOUT_DRIVE_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_DRIVE_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "locomotion_class.h"

struct DriveLocomotionClass : LocomotionPiggybackBase
{
    int         unknown_1C;       // +0x1C ctor `MOV [ESI+0x1c],EAX` @0x004AF54D
                                  //       (=0). Force_New_Slope(int) 0x004AFB40
                                  //       writes the SAME argument here
                                  //       (if+0x18) @0x004AFB50 and to 0x20
                                  //       (if+0x1c) @0x004AFB4D, so the pair is
                                  //       the ramp/slope state; nothing in the
                                  //       cluster distinguishes which is the
                                  //       current and which the previous ramp,
                                  //       so neither is named (YRpp guesses
                                  //       CurrentRamp / PreviousRamp).
    int         unknown_20;       // +0x20 ctor @0x004AF550 (=0); see 0x1C

    RateTimer   SlopeTimer;       // +0x24 (0x10) StartTime @0x004AF55C from the
                                  //       frame counter 0x00A8ED84; the clock
                                  //       slot 0x28 is never written; TimeLeft
                                  //       0x2C @0x004AF559 (=0); Rate 0x30
                                  //       @0x004AF55F (=0). Proven a RateTimer
                                  //       and not a bare CDTimerClass by
                                  //       Draw_Matrix 0x004AFF60: StartTime
                                  //       (if+0x20) @0x004AFF85, TimeLeft
                                  //       (if+0x28) @0x004AFF88, then
                                  //       `FIDIV dword ptr [ESP+0x18]`
                                  //       @0x004AFFAC where that slot holds
                                  //       Rate (if+0x2c) loaded @0x004AFF72.

    CoordStruct Destination;      // +0x34 ctor `LEA EDX,[ESI+0x34]` @0x004AF54A
                                  //       then X @0x004AF568, Y @0x004AF570,
                                  //       Z @0x004AF579 from the file-scope
                                  //       globals 0x008A0790 / 0x008A0794 /
                                  //       0x008A0798. CONFIRMED BY READER:
                                  //       ILocomotion::Destination 0x004AFC90
                                  //       copies 0x34 (if+0x30) @0x004AFC9A,
                                  //       0x38 @0x004AFC9D and 0x3C @0x004AFCA0
                                  //       into the out-parameter; Is_Moving
                                  //       0x004AFB80 compares 0x34 @0x004AFB87
                                  //       and 0x38 @0x004AFB9C against the same
                                  //       three globals.

    CoordStruct HeadToCoord;      // +0x40 ctor `LEA EDX,[ESI+0x40]` @0x004AF582
                                  //       then @0x004AF585, @0x004AF58E,
                                  //       @0x004AF59D from the same globals.
                                  //       CONFIRMED BY READER:
                                  //       ILocomotion::Head_To_Coord 0x004AFCC0
                                  //       reads 0x40 (if+0x3c) @0x004AFCCC and
                                  //       0x44 @0x004AFCD3; Stop_Moving
                                  //       0x004AFE00 reads 0x40 @0x004AFE0C,
                                  //       0x44 @0x004AFE13, 0x48 @0x004AFE1F.

    int         SpeedAccum;       // +0x4C ctor @0x004AF59A (=0). CONFIRMED BY
                                  //       READER: ILocomotion slot 49
                                  //       Get_Speed_Accum 0x004B4C20 is
                                  //       `MOV EAX,[EAX+0x48]; RET 0x4`
                                  //       @0x004B4C24 - if+0x48 = object 0x4C.
    int         unknown_50;       // +0x50 ctor @0x004AF597 (=0)
    int         unknown_54;       // +0x54 ctor @0x004AF5A3 (=0). 0x50/0x54 are
                                  //       an 8-byte-aligned pair the ctor zeroes
                                  //       as two dwords; no instruction in the
                                  //       cluster was found reading either at
                                  //       any width, so they go in as two ints
                                  //       rather than the double YRpp guesses.

    int         TrackNumber;      // +0x58 ctor @0x004AF5A6 (= -1). CONFIRMED BY
                                  //       READER: ILocomotion slot 47
                                  //       0x004B4C00 is `MOV EAX,[EAX+0x54]`
                                  //       @0x004B4C04 (if+0x54 = object 0x58);
                                  //       Will_Jump_Tracks 0x004B4B00 loads it
                                  //       @0x004B4B21 and uses it as the index
                                  //       into the TurnTrack table at 0x007E7B28
                                  //       (`LEA ECX,[ECX+ECX*2]` @0x004B4B29,
                                  //       `LEA ECX,[ECX*4+0x7E7B28]`
                                  //       @0x004B4B2C).
    int         TrackIndex;       // +0x5C ctor @0x004AF5A9 (= -1). CONFIRMED BY
                                  //       READER: ILocomotion slot 48
                                  //       0x004B4C10 is `MOV EAX,[EAX+0x58]`
                                  //       @0x004B4C14.

    char        IsOnShortTrack;   // +0x60 ctor @0x004AF5AC (=0). CONFIRMED BY
                                  //       READER: Will_Jump_Tracks reads it
                                  //       `MOV DL,[EDI+0x5c]` @0x004B4B24 and
                                  //       uses it to pick byte +1 @0x004B4B35
                                  //       instead of byte +0 @0x004B4B3B of the
                                  //       TurnTrack entry - the short-track
                                  //       variant of the same track.
    char        unknown_61;       // +0x61 ctor @0x004AF5AF (=0); no reader found
    char        unknown_62;       // +0x62 ctor @0x004AF5B2 (=0); read as a byte
                                  //       by the drive Process body 0x004B0F20
                                  //       (`MOV AL,[EBP+0x62]` @0x004B0F49,
                                  //       object-relative), but the branch does
                                  //       not name it
    char        unknown_63;       // +0x63 ctor @0x004AF5B5 (=0); read
                                  //       `MOV AL,[EBP+0x63]` @0x004B0F2C,
                                  //       gating on TrackNumber != -1
    char        unknown_64;       // +0x64 ctor @0x004AF5B8 (=0); no reader found
    char        UnLocked;         // +0x65 ctor @0x004AF5BB (= 1). CONFIRMED BY
                                  //       READER: ILocomotion slot 45 Lock
                                  //       0x004B4BE0 writes
                                  //       `MOV BYTE PTR [EAX+0x61],0`
                                  //       @0x004B4BE4 and slot 46 Unlock
                                  //       0x004B4BF0 writes 1 @0x004B4BF4 -
                                  //       if+0x61 = object 0x65, and the ctor's
                                  //       initial value is the unlocked one.
    char        unknown_66[2];    // +0x66 alignment; never written, never read

    void*       Piggybackee;      // +0x68 ILocomotion*; ctor @0x004AF5BF (=0).
                                  //       CONFIRMED BY READER: the destructor
                                  //       0x004AF5E0 loads it @0x004AF5F7 and,
                                  //       if non-null, calls slot +8 of its own
                                  //       vtable (`MOV ECX,[EAX]` @0x004AF5FE,
                                  //       `CALL [ECX+0x8]` @0x004AF601) - an
                                  //       IUnknown::Release, which is what
                                  //       proves it is an interface pointer.
    int         unknown_6C;       // +0x6C untouched tail to sizeof: never
                                  //       written by the ctor and no read at any
                                  //       width was found in the cluster.
};

GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_1C)     == 0x1C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_20)     == 0x20);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, SlopeTimer)     == 0x24);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, Destination)    == 0x34);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, HeadToCoord)    == 0x40);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, SpeedAccum)     == 0x4C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_50)     == 0x50);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_54)     == 0x54);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, TrackNumber)    == 0x58);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, TrackIndex)     == 0x5C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, IsOnShortTrack) == 0x60);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_61)     == 0x61);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_62)     == 0x62);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_63)     == 0x63);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_64)     == 0x64);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, UnLocked)       == 0x65);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, Piggybackee)    == 0x68);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_6C)     == 0x6C);
GG_STATIC_ASSERT(sizeof(DriveLocomotionClass)                   == 0x70);

#endif  // GG_MATCH_LAYOUT_DRIVE_LOCOMOTION_CLASS_H
