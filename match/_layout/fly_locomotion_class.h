// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: FlyLocomotionClass::FlyLocomotionClass 0x004CC9A0, which chains the
//   LocomotionClass base constructor 0x0055A6C0 at offset 0 and then stores
//   every one of its own fields. Each member below carries the address of the
//   instruction that proves it; all of them were read back out of the user's
//   retail gamemd.exe v1.001 (sha256 1cdd1180...4298c) before being written
//   here. Nothing in this file rests on scripts/data/*.json, which are leads.
//
//   sizeof = 0x60, proven twice and independently:
//     * the single allocation site, `PUSH 0x60` @0x006C4ABC immediately before
//       `CALL operator new` @0x006C4ABE and `MOV ECX,EAX; CALL 0x004CC9A0`
//       @0x006C4ACA..0x006C4ACC;
//     * the class's own virtual size accessor, persist-vtable slot +0x24 =
//       0x004D0390, whose entire body is `MOV EAX,0x60 / RET`.
//   The layout closes: the last member the constructor writes is the byte at
//   0x5C (@0x004CCA09) and 0x5C+1 <= 0x60, with three trailing bytes no code
//   in the cluster touches.
//
//   RTTI, read out of the binary (this is the check that caught the
//   AircraftClass/HouseClass defects): ".?AVFlyLocomotionClass@@", type
//   descriptor 0x008223E8, has exactly TWO complete object locators -
//   0x008006B8 (base offset 0, vtable 0x007E8AC0, IPersistStream) and
//   0x00800658 (base offset 4, vtable 0x007E89F4, ILocomotion). Its base chain
//   is FlyLocomotionClass / LocomotionClass / IPersistStream / IPersist /
//   IUnknown / ILocomotion / IUnknown - seven entries, no IPiggyback.
//   This MATTERS and is the reason this header cannot be shared with its
//   siblings: DriveLocomotionClass, ShipLocomotionClass, WalkLocomotionClass,
//   TeleportLocomotionClass, JumpjetLocomotionClass and DropPodLocomotionClass
//   each carry a THIRD locator at base offset 24 (0x18) for IPiggyback, so in
//   those classes 0x18 is a vptr. In FlyLocomotionClass 0x18 is a plain byte -
//   `MOV BYTE PTR [ESI+0x18],AL` @0x004CC9AD - and the class's own derived data
//   therefore starts at 0x18, not 0x1C. Hover/Mech/Tunnel share Fly's
//   two-locator shape.
//
//   Both vptrs are written by the constructor's last two stores:
//     `MOV DWORD PTR [ESI],0x7E8AC0`     @0x004CCA0C   (base offset 0)
//     `MOV DWORD PTR [ESI+0x4],0x7E89F4` @0x004CCA12   (base offset 4)
//   The ILocomotion vtable 0x007E89F4 runs slots +0x00..+0xC4 - 50 slots.
//
//   AGREEMENT WITH THE MINE: all 24 constructor-mined offsets
//   (0x00 0x04 0x18 0x1C 0x20 0x24 0x28 0x2C 0x30 0x34 0x38 0x40 0x44 0x48
//   0x4C 0x50 0x51 0x52 0x53 0x54 0x58 0x5C, plus the two vptrs counted at
//   0x00/0x04) were re-read from their own citing instructions and every one
//   was confirmed exactly. Zero disagreements on offset, width or kind.
//
//   NAMING DISAGREEMENTS worth recording (offsets agree in every case; only
//   the labels differ):
//     * 0x38. match/movement/fly_locomotion_approach_methods.h calls it
//       "MoveDistance". The binary says otherwise: Process 0x004CCB40 fills it
//       from the client's owner (`CALL [EAX+0x84]` then `CALL [EDX+0xBC]`,
//       stored @0x004CCB81), and 0x004CFC40 tests the remaining travel against
//       `that value / 2` (@0x004CFC5E..0x004CFC68). That is a cruise altitude,
//       not a distance; YRpp's "FlightLevel" is the better name and is used
//       here. The Approach TU's own offset is right either way.
//     * 0x34. match/movement/fly_locomotion_leaf_methods.h calls it
//       "IsElevating". It is the flag Is_Moving 0x004CCA90 returns
//       (`MOV CL,[EAX+0x30]` interface-relative = object +0x34) and the one
//       Move_To sets (`MOV BYTE PTR [EBX+0x30],1` @0x004CCEAA). HasMoveOrder.
//       The name "IsElevating" belongs to 0x5C, which is the byte the approach
//       driver 0x004CD2A0 sets (`MOV BYTE PTR [ESI+0x5C],1` @0x004CD2CD) and
//       0x004CD674/0x004CD67B reads and clears.
//     * 0x53/0x54/0x58. match/movement/fly_locomotion_com_methods.h names these
//       IsSpinning / unknown_54 / SpinCount from the touchdown spin path
//       (0x004CFD20, 0x004CFDD0) and that reading is kept here; YRpp leaves all
//       three unnamed.
//
//   OFFSETS THAT GO IN AS unknown_XX, and why:
//     * 0x12..0x13 - never written by either constructor and never read
//       anywhere in the 0x4CC9A0..0x4D0600 cluster. Alignment only.
//     * 0x19..0x1B, 0x35..0x37 - alignment behind the bools at 0x18 and 0x34;
//       no access at any width.
//     * 0x28 (twelve bytes). Proven to exist and proven to be a coordinate
//       sub-object: `LEA ECX,[ESI+0x28]` @0x004CC9D0 takes its address, and the
//       constructor fills 0x28/0x2C/0x30 from the same three globals
//       (0x008B3C78/0x008B3C7C/0x008B3C80) it fills Destination from
//       (@0x004CC9D3, @0x004CC9DC, @0x004CCA1B). What it MEANS is not proven:
//       no reader of 0x28 exists anywhere in the cluster, so it goes in as a
//       named-shape/unnamed-meaning member rather than on YRpp's "XYZ2".
//     * 0x3C - dead. Not written by the constructor and not read at any width
//       anywhere in the cluster; it is the alignment pad in front of the
//       eight-byte-aligned double at 0x40.
//     * 0x5D..0x5F - untouched tail to sizeof. YRpp guesses three bools; the
//       binary offers nothing, so they stay padding.
//
// FlyLocomotionClass - a COM locomotor. Derives LocomotionClass at offset 0.
#ifndef GG_MATCH_LAYOUT_FLY_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_FLY_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CoordStruct - lepton 3-space coordinate (sizeof = 0xC). Self-guarded so this
// header composes with techno_type_class.h / bounce_class.h.
#include "coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

#include "../movement/loco_base.h"

// ---------------------------------------------------------------------------
// FlyLocomotionClass (sizeof = 0x60).
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E8AC0 -- primary IPersistStream, 10 slots.
// VTABLE: GAMEMD 0x7E89F4 -- secondary ILocomotion at +4, 50 slots.
class FlyLocomotionClass : public LocomotionClass
{
public:
    // Declaration: GAMEMD 0x4CC9A0 -- external default constructor.
    FlyLocomotionClass();
    // Inline no-init reconstruction observed in Load at 0x4CFCD8.
    FlyLocomotionClass(int) : LocomotionClass(0) {}
    // Scalar deleting provider 0x4D03A0 is annotated in the owning TU.
    virtual ~FlyLocomotionClass() {}
    virtual HRESULT __stdcall GetClassID(CLSID* classID); // primary 3, 4CFC80
    virtual HRESULT __stdcall Load(IStream* stream);      // primary 5, 4CFCC0
    virtual int Size();                                // primary 9, 4D0390
    // Secondary ILocomotion overrides. Native stack-self is complete+4.
    virtual HRESULT __stdcall LinkToObject(FootClass* object); // 3, 4CCA20
    virtual bool __stdcall IsMoving();                         // 4, 4CCA90
    virtual LocoCoord __stdcall Destination();                 // 5, 4CCAE0
    virtual Matrix3D __stdcall DrawMatrix(unsigned int* key);  // 9, 4CF610
    virtual Matrix3D __stdcall ShadowMatrix(unsigned int* key);// 10,4CFB00
    virtual LocoPoint2D __stdcall DrawPoint();                 // 11,4CF830
    virtual LocoPoint2D __stdcall ShadowPoint();               // 12,4CF940
    virtual bool __stdcall Process();                         // 16,4CCB40
    virtual void __stdcall MoveTo(LocoCoord to);               // 17,4CCC80
    virtual void __stdcall StopMoving();                      // 18,4CCFD0
    virtual void __stdcall DoTurn(unsigned long dir);          // 19,4CFC10
    virtual bool __stdcall PowerOff();                        // 23,4CFD20
    virtual bool __stdcall IsPowered();                       // 24,4CFD90
    virtual bool __stdcall IsIonSensitive();                  // 25,4CFDA0
    virtual int __stdcall InWhichLayer();                     // 29,4CFCF0
    virtual bool __stdcall IsMovingNow();                     // 32,4CCAC0
    virtual int __stdcall ApparentSpeed();                    // 33,4CFE20
    virtual int __stdcall GetStatus();                        // 36,4CFE50
    virtual void __stdcall AcquireHunterSeekerTarget();       // 37,4CFE80
    // Declaration: GAMEMD 0x4CFC40 -- complete-object __thiscall helper.
    char FUN_004CFC40() const;

    char        AirportBound;     // +0x18 ctor `MOV BYTE [ESI+0x18],AL` @0x004CC9AD (=0);
                                  //       read as a byte @0x004CD9F5, @0x004CE99A, @0x004CE9B5
    char        unknown_19[3];    // +0x19 alignment; no access at any width

    CoordStruct Destination_;      // +0x1C ctor `LEA ECX,[ESI+0x1C]` @0x004CC9AA then
                                  //       X @0x004CC9B6, Y @0x004CC9BE, Z @0x004CC9C7,
                                  //       all three from the globals 0x008B3C78 /
                                  //       0x008B3C7C / 0x008B3C80. Confirmed as one
                                  //       coordinate by 0x004D02B0, which passes
                                  //       `LEA EAX,[ESI+0x1C]` @0x004D02BB to the map
                                  //       lookup 0x00578080 and then reads the Z
                                  //       component `MOV ECX,[ESI+0x24]` @0x004D02C4.
                                  //       Written whole by Move_To @0x004CCDC9..

    CoordStruct unknown_28;       // +0x28 a second coordinate: `LEA ECX,[ESI+0x28]`
                                  //       @0x004CC9D0 takes its address and the same
                                  //       three globals are stored to 0x28 @0x004CC9D3,
                                  //       0x2C @0x004CC9DC and 0x30 @0x004CCA1B.
                                  //       Shape proven, meaning NOT proven - no reader
                                  //       of 0x28 exists in the cluster, so it is not
                                  //       given a name.

    char        HasMoveOrder;     // +0x34 ctor `MOV BYTE [ESI+0x34],AL` @0x004CC9EB (=0);
                                  //       set `MOV BYTE [EBX+0x30],1` @0x004CCEAA
                                  //       (interface-relative, = object +0x34) by
                                  //       Move_To; cleared `MOV BYTE [ESI+0x34],0`
                                  //       @0x004CEF55; returned by Is_Moving 0x004CCA90
                                  //       (`MOV CL,[EAX+0x30]` @0x004CCA94)
    char        unknown_35[3];    // +0x35 alignment; no access at any width

    int         FlightLevel;      // +0x38 ctor @0x004CC9EE (=0); filled from the
                                  //       client's owner in Process
                                  //       (`MOV [ESI+0x34],EAX` @0x004CCB81,
                                  //       interface-relative); halved and compared
                                  //       against the remaining travel
                                  //       `MOV EAX,[ESI+0x38]; CDQ; SUB EAX,EDX;
                                  //        SAR EAX,1` @0x004CFC5E..0x004CFC64
    int         unknown_3C;       // +0x3C dead: never written by the ctor, never read
                                  //       at any width in the cluster. Alignment pad
                                  //       in front of the double at 0x40.

    double      TargetSpeed;      // +0x40 ctor zeroes both halves, @0x004CC9E5 (0x40)
                                  //       and @0x004CC9F1 (0x44). Eight-byte wide in
                                  //       use: `FLD QWORD PTR [ESI+0x3C]` @0x004CCB55
                                  //       (interface-relative), `FST QWORD PTR
                                  //       [ESI+0x40]` @0x004CE260, `FLD QWORD PTR
                                  //       [ESI+0x40]` @0x004CE2AB / @0x004CE417
    double      CurrentSpeed;     // +0x48 ctor zeroes both halves, @0x004CC9E8 (0x48)
                                  //       and @0x004CC9F4 (0x4C). `FLD QWORD PTR
                                  //       [ESI+0x48]` @0x004CE288, `FSTP QWORD PTR
                                  //       [ESI+0x48]` @0x004CE297; ramped towards
                                  //       TargetSpeed - `FLD [ESI+0x48]; FCOMP
                                  //       [ESI+0x40]` @0x004CE449..0x004CE44C

    char        IsTakingOff;      // +0x50 ctor @0x004CC9F7 (=0); `MOV AL,[ESI+0x50]`
                                  //       @0x004CFC4A
    char        IsLanding;        // +0x51 ctor @0x004CC9FA (=0); `MOV AL,[ESI+0x51]`
                                  //       @0x004CFC43, @0x004D01B6
    char        WasLanding;       // +0x52 ctor @0x004CC9FD (=0); `MOV AL,[ESI+0x52]`
                                  //       @0x004CEB02, set `MOV BYTE [ESI+0x52],1`
                                  //       @0x004CEB4D
    char        IsSpinning;       // +0x53 ctor @0x004CCA00 (=0); `MOV AL,[ESI+0x53]`
                                  //       @0x004CE5A6, cleared @0x004CE639; the
                                  //       touchdown spin gate (see
                                  //       fly_locomotion_com_methods.h)
    int         unknown_54;         // +0x54 ctor @0x004CCA03 (=0); read/modified/written
                                  //       @0x004CE5E0, @0x004CE60A, @0x004CE624,
                                  //       @0x004CE62E
    int         SpinCount;        // +0x58 ctor @0x004CCA06 (=0); read/modified/written
                                  //       @0x004CD6B6, @0x004CD6C6, @0x004CD6DD

    char        IsElevating;      // +0x5C ctor `MOV BYTE [ESI+0x5C],AL` @0x004CCA09
                                  //       (=0); set `MOV BYTE [ESI+0x5C],1`
                                  //       @0x004CD2CD, read @0x004CD674 / @0x004CE3C0,
                                  //       cleared @0x004CD67B
    char        unknown_5D[3];    // +0x5D untouched tail to sizeof
};

GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, AirportBound) == 0x18);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, Destination_)  == 0x1C);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, unknown_28)   == 0x28);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, HasMoveOrder) == 0x34);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, FlightLevel)  == 0x38);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, unknown_3C)   == 0x3C);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, TargetSpeed)  == 0x40);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, CurrentSpeed) == 0x48);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, IsTakingOff)  == 0x50);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, IsLanding)    == 0x51);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, WasLanding)   == 0x52);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, IsSpinning)   == 0x53);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, unknown_54)     == 0x54);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, SpinCount)    == 0x58);
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, IsElevating)  == 0x5C);
GG_STATIC_ASSERT(sizeof(FlyLocomotionClass)                 == 0x60);

#endif  // GG_MATCH_LAYOUT_FLY_LOCOMOTION_CLASS_H
