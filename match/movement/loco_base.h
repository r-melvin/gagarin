// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: candidate native declaration, based on pinned retail layout/RTTI evidence. | YRpp-cross-check
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001:
//   RTTI.?AVLocomotionClass@@ (TD 0x820228, COL 0x8032E8 for the primary
//   table and the COL word before 0x7EADF4 for the ILocomotion table), the
//   primary vtable 0x7EAEC0 (10 slots), the ILocomotion vtable 0x7EADF4 (50
//   slots), the constructor 0x55A6C0 (vptr stores `[ECX]=0x7EAEC0`,
//   `[ECX+4]=0x7EADF4`) and the eleven leaf constructors, each of which calls
//   0x55A6C0 first and then stores its own vptrs and members (Mech/Fly store
//   their first member at +0x18, Drive/DropPod store the IPiggyback vptr at
//   +0x18 and their first member at +0x1C). Member names follow YRpp;
//   the two object pointers are indistinguishable in the
//   shared code (see Owner/LinkedTo below).
//
// LocomotionClass: candidate shared base supported by constructor/RTTI evidence.
//
//   RTTI chain  LocomotionClass -> IPersistStream -> IPersist -> IUnknown
//                               -> ILocomotion    -> IUnknown
//   +0x00  vptr  IPersistStream side, table 0x7EAEC0, 10 slots
//   +0x04  vptr  ILocomotion side,    table 0x7EADF4, 50 slots
//   +0x08  Owner
//   +0x0C  LinkedTo
//   +0x10  Powered (byte)
//   +0x11  Dirty   (byte)
//   +0x14  RefCount
//   (derived members start at +0x18; IPiggyback classes put its vptr there)
//
// COMPLETE-OBJECT offsets are used below. The ILocomotion-table bodies see
// `this` as complete+4 and the compiler adjusts the member offsets itself.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_BASE_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_BASE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"
#include "loco_vtable_layout.h"

// Retail address points observed: primary 0x7EAEC0, ILocomotion 0x7EADF4.
// This method-only candidate emits neither table; vtable ownership is deferred.
class LocomotionClass : public IPersistStream, public ILocomotion
{
public:
    // FUNCTION: GAMEMD 0x55A6C0 (decl only; out of this candidate scope).
    LocomotionClass();
    // No-init constructor: Load re-runs it through placement new to
    // restore the vptrs without touching members. Empty and inline; it is never emitted standalone.
    LocomotionClass(int) {}
    // Primary slot 8 (scalar deleting destructor 0x5172F0, synthetic). The
    // destructor body is 0x55A6F0 (EXPANSION CANDIDATE, unowned): it resets the
    // two vptrs to the base tables and clears LinkedTo.
    virtual ~LocomotionClass();

    // ---- IUnknown (one body serves both bases) -------------------------------
    // Primary slots 0-2 point at these bodies (this = complete object); the
    // ILocomotion table slots 0-2 are compiler adjustor thunks 0x4D0510 /
    // 0x4D0520 / 0x4D0530 (`SUB [ESP+4],4; JMP`).
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x55A9B0
    virtual ULONG   __stdcall AddRef();                                   // 0x55A950
    virtual ULONG   __stdcall Release();                                  // 0x55A970

    // ---- IPersist / IPersistStream (primary table slots 3-7) ----------------
    // Slot 3 GetClassID is pure (inherited, __purecall).
    // Slot 4. S_OK/S_FALSE convention: returns 1 (S_FALSE) while Dirty == 0.
// Inline default implementation observed at the 0x4B4C30 call site; this is not a separate standalone match row. The existing 0x4B4C30 free-function binding remains owned by its COLUMNZERO row until that migration is handled.
    virtual HRESULT __stdcall IsDirty() { return !Dirty; }                // 0x4B4C30 (inline in retail)
    // Slot 5 Load remains pure in this base table. Its out-of-line body in
    // loco_base.cpp is used by derived loaders through a qualified call.
    virtual HRESULT __stdcall Load(IStream* pStm) = 0;
    // Slot 6. READ-ONLY binding (0x55AA60 is owned elsewhere).
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x55AA60
    // Slot 7. pcbSize = Size() + 4 (low dword), high dword 0; E_POINTER on null.
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);        // 0x55AB40
    // Primary slot 9 (new virtual, __thiscall, pure). Each leaf returns its sizeof.
    virtual int Size() = 0;

    // ---- ILocomotion (table 0x7EADF4, slots 3-49) ---------------------------
    virtual HRESULT __stdcall LinkToObject(FootClass* object);            // 3   0x55A710
    virtual bool __stdcall IsMoving();                                    // 4   0x55ACD0
    virtual LocoCoord __stdcall Destination();                            // 5   0x55AC70
    virtual LocoCoord __stdcall HeadToCoord();                           // 6   0x55ACA0
    virtual int __stdcall CanEnterCell(int cell);                         // 7   0x55ABF0
    virtual bool __stdcall IsToHaveShadow();                              // 8   0x55ABE0
    virtual LocoMatrix3D __stdcall DrawMatrix(unsigned int* key);         // 9   0x55A730
    virtual LocoMatrix3D __stdcall ShadowMatrix(unsigned int* key);       // 10  0x55A7D0
    virtual LocoPoint2D __stdcall DrawPoint();                           // 11  0x55ABD0
    virtual LocoPoint2D __stdcall ShadowPoint();                         // 12  0x55A8C0
    virtual int __stdcall VisualCharacter(int unused);                    // 13  0x55ABC0
    virtual int __stdcall ZAdjust();                                      // 14  0x55ABA0
    virtual int __stdcall ZGradient();                                    // 15  0x55ABB0
    virtual bool __stdcall Process();                                     // 16  0x55AC60
    virtual void __stdcall MoveTo(LocoCoord to);                          // 17  0x55AC50
    virtual void __stdcall StopMoving();                                  // 18  0x55AC40
    virtual void __stdcall DoTurn(unsigned long dir);                     // 19  0x55AC30
    virtual void __stdcall Unlimbo();                                     // 20  0x55AC20
    virtual void __stdcall TiltPitchAI();                                 // 21  0x55AB90
    virtual bool __stdcall PowerOn();                                     // 22  0x55A8F0
    virtual bool __stdcall PowerOff();                                    // 23  0x55A910
    virtual bool __stdcall IsPowered();                                   // 24  0x55A930
    virtual bool __stdcall IsIonSensitive();                              // 25  0x55A940
    virtual bool __stdcall Push(unsigned long dir);                       // 26  0x55AB70
    virtual bool __stdcall Shove(unsigned long dir);                      // 27  0x55AB80
    virtual void __stdcall ForceTrack(int track, LocoCoord coord);        // 28  0x55AC10
    virtual int __stdcall InWhichLayer() = 0;                             // 29  __purecall 0x4C9150
    virtual void __stdcall ForceImmediateDestination(LocoCoord coord);    // 30  0x55AC00
    virtual void __stdcall ForceNewSlope(int ramp);                       // 31  0x55ACE0
// FUNCTION: GAMEMD 0x4B6610 (inline default definition; no standalone match row claimed here)
    virtual bool __stdcall IsMovingNow() { return IsMoving(); }           // 32  0x4B6610 (inline in retail)
    virtual int __stdcall ApparentSpeed();                                // 33  0x55AD10
    virtual int __stdcall DrawingCode();                                  // 34  0x55ACF0
    virtual int __stdcall CanFire();                                      // 35  0x55AD00

    // Slots 36-49 are all inline in retail: their bodies sit between the Drive
    // and DropPod functions (0x4B4C50-0x4B4CA0, 0x4B6610-0x4B6690), i.e. each address has an inline/default implementation; this candidate does
    // not claim a standalone match row or emitted vtable for those targets.
// FUNCTION: GAMEMD 0x4B4C60 (inline default definition; no standalone match row claimed here)
    virtual int __stdcall GetStatus() { return 0; }                       // 36  0x4B4C60
// FUNCTION: GAMEMD 0x4B4C70 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall AcquireHunterSeekerTarget() {}                 // 37  0x4B4C70
// FUNCTION: GAMEMD 0x4B4C80 (inline default definition; no standalone match row claimed here)
    virtual bool __stdcall IsSurfacing() { return false; }                // 38  0x4B4C80
// FUNCTION: GAMEMD 0x4B6620 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall MarkAllOccupationBits(int) {}                  // 39  0x4B6620
// FUNCTION: GAMEMD 0x4B6630 (inline default definition; no standalone match row claimed here)
    virtual bool __stdcall IsMovingHere(LocoCoord) { return false; }      // 40  0x4B6630
// FUNCTION: GAMEMD 0x4B6640 (inline default definition; no standalone match row claimed here)
    virtual bool __stdcall WillJumpTracks() { return false; }             // 41  0x4B6640
// FUNCTION: GAMEMD 0x4B4C50 (inline default definition; no standalone match row claimed here)
    virtual bool __stdcall IsReallyMovingNow() { return IsMovingNow(); }  // 42  0x4B4C50
// FUNCTION: GAMEMD 0x4B4C90 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall StopMovementAnimation() {}                     // 43  0x4B4C90
// FUNCTION: GAMEMD 0x4B4CA0 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall ClearCoords() {}                               // 44  0x4B4CA0
// FUNCTION: GAMEMD 0x4B6650 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall Lock() {}                                      // 45  0x4B6650
// FUNCTION: GAMEMD 0x4B6660 (inline default definition; no standalone match row claimed here)
    virtual void __stdcall Unlock() {}                                    // 46  0x4B6660
// FUNCTION: GAMEMD 0x4B6670 (inline default definition; no standalone match row claimed here)
    virtual int __stdcall GetTrackNumber() { return -1; }                 // 47  0x4B6670
// FUNCTION: GAMEMD 0x4B6680 (inline default definition; no standalone match row claimed here)
    virtual int __stdcall GetTrackIndex() { return -1; }                  // 48  0x4B6680
// FUNCTION: GAMEMD 0x4B6690 (inline default definition; no standalone match row claimed here)
    virtual int __stdcall GetSpeedAccum() { return -1; }                  // 49  0x4B6690

    // ---- members (complete-object offsets) ----------------------------------
    // Owner and LinkedTo are written together by LinkToObject and zeroed by the
    // constructor; only LinkedTo is read (DrawMatrix, ShadowMatrix,
    // HeadToCoord, ShadowPoint, ApparentSpeed) and cleared by the destructor.
    // YRpp assigns the names in this order; the binary cannot tell them apart.
    FootClass* Owner;       // +0x08
    FootClass* LinkedTo;    // +0x0C
    bool       Powered;     // +0x10  ctor 1; PowerOn sets, PowerOff clears
    bool       Dirty;       // +0x11  ctor 1; IsDirty reads, Save clears
    LONG       RefCount;    // +0x14  ctor 0; Interlocked* by AddRef/Release
};

GG_STATIC_ASSERT(offsetof(LocomotionClass, Owner)    == 0x08);
GG_STATIC_ASSERT(offsetof(LocomotionClass, LinkedTo) == 0x0C);
GG_STATIC_ASSERT(offsetof(LocomotionClass, Powered)  == 0x10);
GG_STATIC_ASSERT(offsetof(LocomotionClass, Dirty)    == 0x11);
GG_STATIC_ASSERT(offsetof(LocomotionClass, RefCount) == 0x14);
// Size is MODELED, not allocated (the class is abstract). It is the derived
// layout that proves it: leaf members start at +0x18 (Mech 0x5AFEF0, Fly
// 0x4CC9A0) and the IPiggyback vptr sits at +0x18 (Drive 0x4AF540).
GG_STATIC_ASSERT(sizeof(LocomotionClass) == 0x18);

// vptr offsets: both interface bases are vptr-only (4 bytes each) and are laid
// out in declaration order, so the IPersistStream subobject is the primary base
// at +0, the ILocomotion subobject sits at +4 (RTTI base_offset 4, ctor store
// `[ECX+4]=0x7EADF4`) and the first member follows at +8. VC6 cannot evaluate a
// base-pointer conversion as a constant, so the offsets are pinned through the
// sizes; the constructor bytes (0x55A6C0) pin the stores themselves.
GG_STATIC_ASSERT(sizeof(IPersistStream) == 4);
GG_STATIC_ASSERT(sizeof(ILocomotion) == 4);
GG_STATIC_ASSERT(offsetof(LocomotionClass, Owner) == sizeof(IPersistStream) + sizeof(ILocomotion));

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_BASE_H
