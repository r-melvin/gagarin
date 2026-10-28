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
//   The class is declared with its real bases (LocomotionClass, IPiggyback) so
//   that VC6 lays out the three tables and generates the ILocomotion (+4) and
//   IPiggyback (+0x18) adjustor thunks itself. The overridden slots, read from
//   the three tables against LocomotionClass's 0x7EAEC0 / 0x7EADF4, are the
//   same slot set DriveLocomotionClass overrides (movement/drive_locomotion.h).
//   +0x50 is a double: StopMoving 0x69F510 reads and writes it with
//   `FLD/FSTP double ptr [EDI+0x4c]` (if+0x4C).
#ifndef GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/loco_base.h"
#include "../movement/loco_com.h"
#include "../ui/transition_timer_methods.h"

// Tables 0x7F2E58 (primary), 0x7F2D8C (ILocomotion), 0x7F2D68 (IPiggyback);
// not claimed while slot bodies such as IsMoving 0x69F290 are unmatched.
class ShipLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    // FUNCTION: GAMEMD 0x69EC50 (declaration)
    ShipLocomotionClass();
    // No-init constructor (Load re-runs it through placement new).
    ShipLocomotionClass(int) : LocomotionClass(0), SlopeTimer() {}
    // Primary slot 8 holds the scalar deleting destructor 0x6A42B0; the
    // destructor body is 0x69ECF0.
    virtual ~ShipLocomotionClass();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x69EE30
    virtual ULONG   __stdcall AddRef();                                   // 0x6A4260
    virtual ULONG   __stdcall Release();                                  // 0x6A4270

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 0x6A3E60
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 0x69EE90
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x69EF10
    virtual int Size();                                                   // 0x6A42A0

    virtual bool __stdcall IsMoving();                                    // 4  0x69F290
    virtual LocoCoord __stdcall Destination();                            // 5  0x69F3A0
    virtual LocoCoord __stdcall HeadToCoord();                            // 6  0x69F3D0
    virtual Matrix3D __stdcall DrawMatrix(unsigned int* key);         // 9  0x69F670
    virtual Matrix3D __stdcall ShadowMatrix(unsigned int* key);       // 10 0x69FB20
    virtual int __stdcall ZAdjust();                                      // 14 0x6A3EA0
    virtual int __stdcall ZGradient();                                    // 15 0x6A3EB0
    virtual bool __stdcall Process();                                     // 16 0x69FC10
    virtual void __stdcall MoveTo(LocoCoord to);                          // 17 0x69F450
    virtual void __stdcall StopMoving();                                  // 18 0x69F510
    virtual void __stdcall DoTurn(unsigned long dir);                     // 19 0x6A05C0
    virtual void __stdcall Unlimbo();                                     // 20 0x69FBE0
    virtual void __stdcall ForceTrack(int track, LocoCoord coord);        // 28 0x6A0310
    virtual int __stdcall InWhichLayer();                                 // 29 0x6A3E50
    virtual void __stdcall ForceNewSlope(int ramp);                       // 31 0x69F250
    virtual bool __stdcall IsMovingNow();                                 // 32 0x69F330
    virtual void __stdcall MarkAllOccupationBits(int mark);               // 39 0x6A3F00
    virtual bool __stdcall IsMovingHere(LocoCoord to);                    // 40 0x6A3F50
    virtual bool __stdcall WillJumpTracks();                              // 41 0x6A4130
    virtual void __stdcall Lock();                                        // 45 0x6A4210
    virtual void __stdcall Unlock();                                      // 46 0x6A4220
    virtual int __stdcall GetTrackNumber();                               // 47 0x6A4230
    virtual int __stdcall GetTrackIndex();                                // 48 0x6A4240
    virtual int __stdcall GetSpeedAccum();                                // 49 0x6A4250

    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* loco);          // 3  0x69EFF0
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** out);            // 4  0x69F040
    virtual bool __stdcall IsOkToEnd();                                   // 5  0x69F080
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* out);                 // 6  0x69ED20
    virtual bool __stdcall IsPiggybacking();                              // 7  0x6A4280

    // MarkAllOccupationBits 0x6A3F00 calls this with (&HeadTo, mark).
    void FUN_006A01A0(const LocoCoord* coord, int mark);                  // 0x6A01A0
    LocoPoint2D FUN_006A3DB0(const LocoPoint2D* point, int* facing);      // 0x6A3DB0
    bool FUN_006A0470();                                                  // 0x6A0470
    bool FUN_006A04C0(const LocoCoord* coord);                            // 0x6A04C0
    bool FUN_006A3EC0();                                                  // 0x6A3EC0
    double FUN_0069F1B0();                                                // 0x69F1B0
    void FUN_0069F210(int ramp);                                          // 0x69F210

    // +0x18 is the IPiggyback vptr.
    int            unknown_1C;    // +0x1C ctor `MOV [ESI+0x1c],EAX` @0x0069EC5D
    int            unknown_20;    // +0x20 ctor @0x0069EC60 (=0)
    RateTimer      SlopeTimer;    // +0x24 StartTime @0x0069EC6C from the frame counter
    LocoCoord      DestCoord;     // +0x34 ctor `LEA EDX,[ESI+0x34]` @0x0069EC5A
    LocoCoord      HeadTo;        // +0x40 ctor `LEA EDX,[ESI+0x40]` @0x0069EC92
    int            SpeedAccum;    // +0x4C ctor @0x0069ECAA (=0); slot 49 getter
    double         unknown_50;    // +0x50 ctor @0x0069ECA7 / @0x0069ECB3 (=0)
    int            TrackNumber;   // +0x58 ctor @0x0069ECB6 (= -1)
    int            TrackIndex;    // +0x5C ctor @0x0069ECB9 (= -1)
    bool           unknown_60;    // +0x60 ctor @0x0069ECBC (=0)
    bool           unknown_61;    // +0x61 ctor @0x0069ECBF (=0)
    bool           unknown_62;    // +0x62 ctor @0x0069ECC2 (=0)
    bool           unknown_63;    // +0x63 ctor @0x0069ECC5 (=0)
    bool           unknown_64;    // +0x64 ctor @0x0069ECC8 (=0)
    bool           UnLocked;      // +0x65 ctor @0x0069ECCB (= 1)
    ILocomotionPtr Piggybackee;   // +0x68 ctor @0x0069ECCF (=0)
    int            unknown_6C;    // +0x6C untouched tail to sizeof
};

GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_1C)    == 0x1C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_20)    == 0x20);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, SlopeTimer)    == 0x24);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, DestCoord)     == 0x34);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, HeadTo)        == 0x40);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, SpeedAccum)    == 0x4C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_50)    == 0x50);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, TrackNumber)   == 0x58);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, TrackIndex)    == 0x5C);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_60)    == 0x60);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, UnLocked)      == 0x65);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((ShipLocomotionClass*)0)->Piggybackee) == 0x68);
GG_STATIC_ASSERT(offsetof(ShipLocomotionClass, unknown_6C)    == 0x6C);
GG_STATIC_ASSERT(sizeof(ShipLocomotionClass)                  == 0x70);

#endif  // GG_MATCH_LAYOUT_SHIP_LOCOMOTION_CLASS_H
