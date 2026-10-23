// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, tables and member offsets read from the retail gamemd.exe v1.001:
//   RTTI .?AVDriveLocomotionClass@@ (TD 0x820248; COLs 0x7FFEB0 / 0x7FFDE8 /
//   0x7FFDD0 at base offsets 0 / 4 / 0x18), tables 0x7E7F7C (primary, 10
//   slots), 0x7E7EB0 (ILocomotion, 50) and 0x7E7E8C (IPiggyback, 8), the
//   constructor 0x4AF540 and its only allocation (`PUSH 0x70` at 0x6C403C).
//   Member names TrackNumber / TrackIndex / IsOnShortTrack / UnLocked /
//   SpeedAccum are kept because the bodies confirm the role: the slot 47-49
//   getters 0x4B4C00 / 0x4B4C10 / 0x4B4C20 return +0x58 / +0x5C / +0x4C,
//   WillJumpTracks 0x4B4B00 indexes the track table by +0x58 and picks the
//   short-track byte when +0x60 is set, and Lock / Unlock 0x4B4BE0 / 0x4B4BF0
//   clear / set +0x65 (constructor value 1).
//
// DriveLocomotionClass: the ground locomotor. It follows the turn/curve track
// tables and piggybacks another locomotor through IPiggyback.
//
//   +0x00  vptr  primary table 0x7E7F7C   (LocomotionClass / IPersistStream)
//   +0x04  vptr  ILocomotion   0x7E7EB0   (LocomotionClass)
//   +0x08..+0x17 LocomotionClass members (loco_base.h)
//   +0x18  vptr  IPiggyback    0x7E7E8C
//   +0x1C  unknown_1C   int       slope index; ForceNewSlope 0x4AFB40 writes it
//   +0x20  unknown_20   int       previous slope index; 0x4AFB00 copies 0x1C here
//   +0x24  SlopeTimer   RateTimer ctor RateTimer(0); 0x4AFB00 assigns RateTimer(3)
//   +0x34  DestCoord    LocoCoord MoveTo / Destination
//   +0x40  HeadTo       LocoCoord HeadToCoord / StopMoving
//   +0x4C  SpeedAccum   int       slot 49 getter
//   +0x50  unknown_50   double    StopMoving clamps it (`FLD QWORD [EDI+0x4C]`, if+0x4C),
//                                 ForceTrack stores 1.0 (`0x3FF00000` high dword)
//   +0x58  TrackNumber  int       ctor -1; ForceTrack writes it
//   +0x5C  TrackIndex   int       ctor -1; ForceTrack zeroes it
//   +0x60  IsOnShortTrack byte
//   +0x61..+0x64 unknown bytes (0x63: head-to valid flag, 0x4B0DA0)
//   +0x65  UnLocked     byte      ctor 1
//   +0x68  Piggybackee  ILocomotionPtr
//   +0x6C  unknown_6C   untouched tail
//   sizeof == 0x70
#ifndef GG_MATCH_MOVEMENT_DRIVE_LOCOMOTION_H
#define GG_MATCH_MOVEMENT_DRIVE_LOCOMOTION_H

#include "loco_base.h"
#include "loco_com.h"
#include "loco_foot.h"
#include "drive_support_views.h"
#include "../ui/transition_timer_methods.h"

// GLOBAL: GAMEMD 0x8A0790 - the empty coordinate this TU compares against
// (three dwords, read by the constructor at 0x4AF562..0x4AF573).
extern "C" LocoCoord DAT_008A0790;
// GLOBAL: GAMEMD 0x8A07C4 - height added on bridge cells by MoveTo 0x4AFD40.
extern "C" int DAT_008A07C4;
// GLOBAL: GAMEMD 0x8A07D0 - height tolerance read by IsMovingHere 0x4B4920.
extern "C" int DAT_008A07D0;

// FUNCTION: GAMEMD 0x755A40 (decl; reloc) - slope transition matrix: hidden
// result pointer in ECX, the previous slope in EDX, then the new slope and the
// blend fraction on the stack.
Matrix3D FUN_00755A40(int from, int to, double fraction);

// VTABLE: GAMEMD 0x7E7F7C (primary), 0x7E7EB0 (ILocomotion), 0x7E7E8C (IPiggyback)
class DriveLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    // FUNCTION: GAMEMD 0x4AF540
    DriveLocomotionClass();
    // No-init constructor (Load re-runs it through placement new): retail
    // 0x4AF79C stores only the piggyback pointer and the three vptrs.
    DriveLocomotionClass(int) : LocomotionClass(0), SlopeTimer() {}
    // Primary slot 8: inline, so the deleting wrapper 0x4B4D00 carries the body.
    virtual ~DriveLocomotionClass() {}

    // ---- IUnknown -----------------------------------------------------------
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x4AF720
    virtual ULONG   __stdcall AddRef();                                   // 0x4B4CB0
    virtual ULONG   __stdcall Release();                                  // 0x4B4CC0

    // ---- primary table ------------------------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 0x4B4830
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 0x4AF780
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x4AF800
    virtual int Size();                                                   // 0x4B4CF0

    // ---- ILocomotion overrides ---------------------------------------------
    virtual bool __stdcall IsMoving();                                    // 4  0x4AFB80
    virtual LocoCoord __stdcall Destination();                            // 5  0x4AFC90
    virtual LocoCoord __stdcall HeadToCoord();                            // 6  0x4AFCC0
    virtual Matrix3D __stdcall DrawMatrix(unsigned int* key);         // 9  0x4AFF60
    virtual Matrix3D __stdcall ShadowMatrix(unsigned int* key);       // 10 0x4B0410
    virtual int __stdcall ZAdjust();                                      // 14 0x4B4870
    virtual int __stdcall ZGradient();                                    // 15 0x4B4880
    virtual bool __stdcall Process();                                     // 16 0x4B0500
    virtual void __stdcall MoveTo(LocoCoord to);                          // 17 0x4AFD40
    virtual void __stdcall StopMoving();                                  // 18 0x4AFE00
    virtual void __stdcall DoTurn(unsigned long dir);                     // 19 0x4B0EF0
    virtual void __stdcall Unlimbo();                                     // 20 0x4B04D0
    virtual void __stdcall ForceTrack(int track, LocoCoord coord);        // 28 0x4B0C40
    virtual int __stdcall InWhichLayer();                                 // 29 0x4B4820
    virtual void __stdcall ForceNewSlope(int ramp);                       // 31 0x4AFB40
    virtual bool __stdcall IsMovingNow();                                 // 32 0x4AFC20
    virtual void __stdcall MarkAllOccupationBits(int mark);               // 39 0x4B48D0
    virtual bool __stdcall IsMovingHere(LocoCoord to);                    // 40 0x4B4920
    virtual bool __stdcall WillJumpTracks();                              // 41 0x4B4B00
    virtual void __stdcall Lock();                                        // 45 0x4B4BE0
    virtual void __stdcall Unlock();                                      // 46 0x4B4BF0
    virtual int __stdcall GetTrackNumber();                               // 47 0x4B4C00
    virtual int __stdcall GetTrackIndex();                                // 48 0x4B4C10
    virtual int __stdcall GetSpeedAccum();                                // 49 0x4B4C20

    // ---- IPiggyback ---------------------------------------------------------
    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* loco);          // 3  0x4AF8E0
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** out);            // 4  0x4AF930
    virtual bool __stdcall IsOkToEnd();                                   // 5  0x4AF970
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* out);                 // 6  0x4AF610
    virtual bool __stdcall IsPiggybacking();                              // 7  0x4B4CD0

    // ---- non-virtual helpers (__thiscall, complete-object this) -------------
    Matrix3D FUN_004AF9B0();                                          // 0x4AF9B0
    double FUN_004AFAA0();                                                // 0x4AFAA0
    void FUN_004AFB00(int ramp);                                          // 0x4AFB00
    int FUN_004AFED0();                                                  // 0x4AFED0
    void FUN_004B0AD0(const LocoCoord* coord, int mode);                  // 0x4B0AD0
    bool FUN_004B0DA0();                                                  // 0x4B0DA0
    bool FUN_004B0DF0(const LocoCoord* coord);                            // 0x4B0DF0
    LocoPoint2D FUN_004B4780(const LocoPoint2D* point, int* facing);     // 0x4B4780
    void FUN_004B4800(int arg);                                           // 0x4B4800
    bool FUN_004B4890();                                                  // 0x4B4890

    DriveFootView* Foot() const { return (DriveFootView*)LinkedTo; }

    // ---- members (complete-object offsets) ----------------------------------
    // +0x18 is the IPiggyback vptr.
    int             unknown_1C;
    int             unknown_20;
    RateTimer       SlopeTimer;
    LocoCoord       DestCoord;
    LocoCoord       HeadTo;
    int             SpeedAccum;
    double          unknown_50;
    int             TrackNumber;
    int             TrackIndex;
    bool            IsOnShortTrack;
    bool            unknown_61;
    bool            unknown_62;
    bool            unknown_63;
    bool            unknown_64;
    bool            UnLocked;
    ILocomotionPtr  Piggybackee;
    int             unknown_6C;
};

GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_1C)     == 0x1C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_20)     == 0x20);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, SlopeTimer)     == 0x24);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, DestCoord)      == 0x34);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, HeadTo)         == 0x40);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, SpeedAccum)     == 0x4C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_50)     == 0x50);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, TrackNumber)    == 0x58);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, TrackIndex)     == 0x5C);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, IsOnShortTrack) == 0x60);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_63)     == 0x63);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, UnLocked)       == 0x65);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((DriveLocomotionClass*)0)->Piggybackee) == 0x68);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, unknown_6C)     == 0x6C);
GG_STATIC_ASSERT(sizeof(DriveLocomotionClass) == 0x70);   // allocation 0x6C403C

// FUNCTION: GAMEMD 0x4B4770 - an empty `RET` with no callers or table entry.
void __cdecl FUN_004B4770();

#endif  // GG_MATCH_MOVEMENT_DRIVE_LOCOMOTION_H
