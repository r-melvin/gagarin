// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at each
//   address below). Slot numbering is the in-tree authoritative ILocomotion
//   vtable slots read from the pinned retail image at the concrete tables.
//   Member names cross-checked against YRpp
//   LocomotionClass.h (consult-only, no LICENSE; offsets reconfirmed below).
//
// This header models the address-local PowerOffView_0055A910 through its
// **ILocomotion** interface, which is the *second* base (`class LocomotionClass : public IPersistStream,
// public ILocomotion`). The `this` an ILocomotion method receives is therefore
// the ILocomotion subobject — the complete object address **plus 4** — so every
// offset here is 4 lower than the corresponding YRpp member offset:
//
//   this-relative   complete-object   member
//   +0x00           +0x04             ILocomotion vptr
//   +0x04           +0x08             Owner
//   +0x08           +0x0C             LinkedTo
//   +0x0C           +0x10             Powered
//   +0x0D           +0x11             Dirty
//
// Confirmed numerically: LinkToObject @0x55A710 stores the object into
// [ECX+0x8] then [ECX+0x4]; PowerOff @0x55A910 clears [EAX+0xC]; IsPowered
// @0x55A930 returns byte [EAX+0xC]. The IPersistStream view of the same object
// (RefCount at complete-object +0x14) lives in locomotion_class_methods.h.
//
// All ILocomotion methods are `__stdcall`, so `this` arrives as the first
// *stack* argument, not in ECX — retail opens each one with
// `MOV EAX/ECX,[ESP+4]` and returns with `RET 4` (or `RET 8` with one argument).
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_ILOCO_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_ILOCO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct FootClass;

struct PowerOffView_0055A910
{
    // --- ILocomotion vtable, slots 0..35 in binary order ---
    // Only the seven implemented below are given real signatures; the rest are
    // opaque pure virtuals whose sole job is to hold their slot, so that
    // PowerOff's `CALL [ECX+0x60]` lands on IsPowered (slot 24) exactly.
    virtual long __stdcall QueryInterface(void* iid, void** ppv) = 0;   //  0  0x00
    virtual unsigned long __stdcall AddRef() = 0;                       //  1  0x04
    virtual unsigned long __stdcall Release() = 0;                      //  2  0x08
    virtual long __stdcall LinkToObject(FootClass* object);             //  3  0x0C  *match*
    virtual void __stdcall v10() = 0;                                   //  4  0x10  IsMoving
    virtual void __stdcall v14() = 0;                                   //  5  0x14  Destination
    virtual void __stdcall v18() = 0;                                   //  6  0x18  HeadToCoord
    virtual void __stdcall v1C() = 0;                                   //  7  0x1C  CanEnterCell
    virtual void __stdcall v20() = 0;                                   //  8  0x20  IsToHaveShadow
    virtual void __stdcall v24() = 0;                                   //  9  0x24  DrawMatrix
    virtual void __stdcall v28() = 0;                                   // 10  0x28  ShadowMatrix
    virtual void __stdcall v2C() = 0;                                   // 11  0x2C  DrawPoint
    virtual void __stdcall v30() = 0;                                   // 12  0x30  ShadowPoint
    virtual void __stdcall v34() = 0;                                   // 13  0x34  VisualCharacter
    virtual int  __stdcall ZAdjust();                                   // 14  0x38  *match*
    virtual int  __stdcall ZGradient();                                 // 15  0x3C  *match*
    virtual void __stdcall v40() = 0;                                   // 16  0x40  Process
    virtual void __stdcall v44() = 0;                                   // 17  0x44  MoveTo
    virtual void __stdcall v48() = 0;                                   // 18  0x48  StopMoving
    virtual void __stdcall v4C() = 0;                                   // 19  0x4C  DoTurn
    virtual void __stdcall v50() = 0;                                   // 20  0x50  Unlimbo
    virtual void __stdcall v54() = 0;                                   // 21  0x54  TiltPitchAI
    virtual void __stdcall v58() = 0;                                   // 22  0x58  PowerOn
    virtual bool __stdcall PowerOff();                                  // 23  0x5C  *match*
    virtual bool __stdcall IsPowered();                                 // 24  0x60  *match*
    virtual bool __stdcall IsIonSensitive();                            // 25  0x64  *match*
    virtual void __stdcall v68() = 0;                                   // 26  0x68  Push
    virtual void __stdcall v6C() = 0;                                   // 27  0x6C  Shove
    virtual void __stdcall v70() = 0;                                   // 28  0x70  ForceTrack
    virtual void __stdcall v74() = 0;                                   // 29  0x74  InWhichLayer
    virtual void __stdcall v78() = 0;                                   // 30  0x78  ForceImmediateDestination
    virtual void __stdcall v7C() = 0;                                   // 31  0x7C  ForceNewSlope
    virtual void __stdcall v80() = 0;                                   // 32  0x80  IsMovingNow
    virtual void __stdcall v84() = 0;                                   // 33  0x84  ApparentSpeed
    virtual void __stdcall v88() = 0;                                   // 34  0x88  DrawingCode
    virtual int  __stdcall CanFire();                                   // 35  0x8C  *match*

    FootClass* Owner;        // +0x04  (complete object +0x08)
    FootClass* LinkedTo;     // +0x08  (complete object +0x0C)
    bool       Powered;      // +0x0C  (complete object +0x10)
    bool       Dirty;        // +0x0D  (complete object +0x11)
};

GG_STATIC_ASSERT(offsetof(PowerOffView_0055A910, Owner)    == 0x04);
GG_STATIC_ASSERT(offsetof(PowerOffView_0055A910, LinkedTo) == 0x08);
GG_STATIC_ASSERT(offsetof(PowerOffView_0055A910, Powered)  == 0x0C);
GG_STATIC_ASSERT(offsetof(PowerOffView_0055A910, Dirty)    == 0x0D);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_ILOCO_METHODS_H
