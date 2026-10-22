// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary (candidate declaration; see scope below).
// The pinned retail PE directly proves 50 ILocomotion slots for the concrete
// Fly table at 0x7E89F4 and DropPod table at 0x7E8278; see
// /tmp/gagarin-locomotion-foundation-review/concrete-interface-audit.md.
// It does not, by itself, validate every signature/name here or generalize all
// locomotion table extents. Those declarations remain hypotheses until each
// use is confirmed against retail instructions.
//
//
// Interface declarations for the locomotion module (candidate only). Existing
// address-local interface views under match/ remain until their callers are
// migrated and checked.
//
// Calling convention: declarations model COM methods as __stdcall, with `this`
// as the first stack argument. Direct slot/callee evidence is recorded per
// reviewed table; this candidate does not claim every interface slot is audited.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_INTERFACES_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_INTERFACES_H

#include <stddef.h>
#include <objidl.h>        // IUnknown, IPersist, IPersistStream, IStream (VC98 SDK, LIBRARY)
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Value types that appear in interface signatures.
// ---------------------------------------------------------------------------

// Three-dword world coordinate (YRpp CoordStruct). Passed by value as 12 stack
// bytes (MoveTo RET 0x10, ForceImmediateDestination RET 0x10, ForceTrack RET
// 0x14, IsMovingHere RET 0x10) and returned through an out pointer.
struct LocoCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(offsetof(LocoCoord, X) == 0x00);
GG_STATIC_ASSERT(offsetof(LocoCoord, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(LocoCoord, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(LocoCoord) == 0xC);

// Two-dword screen offset (YRpp Point2D); returned by value from DrawPoint and
// ShadowPoint. Retail returns it through a hidden pointer (EAX = that pointer),
// which VC6 only does for a non-POD of this size (a POD would come back in
// EAX:EDX), hence the user-declared constructors.
struct LocoPoint2D
{
    int X;   // +0x00
    int Y;   // +0x04

    LocoPoint2D() {}
    LocoPoint2D(int x, int y) : X(x), Y(y) {}
};
GG_STATIC_ASSERT(offsetof(LocoPoint2D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(LocoPoint2D, Y) == 0x04);
GG_STATIC_ASSERT(sizeof(LocoPoint2D) == 0x8);

// 3 rows x 4 floats (sizeof 0x30, proven by the 12-dword `REP MOVSD` copies in
// 0x55A730 / 0x55A7D0). The user-declared constructor makes the type non-POD,
// which is what makes VC6 hand the return slot over as a hidden pointer the
// way retail does (also needed for the __fastcall slope lookup 0x7559B0).
struct LocoMatrix3D
{
    float Row[3][4];   // +0x00

    LocoMatrix3D() {}

    // FUNCTION: GAMEMD 0x5AE860 (decl; reloc) - identity (__thiscall).
    void MakeIdentity();
    // FUNCTION: GAMEMD 0x5AF1A0 (decl; reloc) - rotate about Z (__thiscall).
    void RotateZ(float angle);
};
GG_STATIC_ASSERT(offsetof(LocoMatrix3D, Row) == 0x00);
GG_STATIC_ASSERT(sizeof(LocoMatrix3D) == 0x30);

struct FootClass;   // linked object; any layout view is scoped by its owning TU

// ---------------------------------------------------------------------------
// GUIDs. Each value below was read from the retail image; the pairing with the
// interface is proven by the QueryInterface bodies (0x55A9B0 for ILocomotion,
// 0x4AF720 and the five other piggyback-class QIs for IPiggyback).
//
//   IID_ILocomotion  {070F3290-9841-11D1-B709-00A024DDAFD1}  GAMEMD 0x7ED358
//     0x55A9B0 returns (this + 4) for it. Also read (x-ref, DATA/READ) by
//     0x4DB3C0, 0x54B750, 0x719CA0, 0x4AF780, 0x69EE90, 0x4B6240 and 0x75C680.
//   IID_IPiggyback   {92FEA800-A184-11D1-B70A-00A024DDAFD1}  GAMEMD 0x7E9B10
//     the QIs of Drive 0x4AF720, DropPod 0x4B6470, Jumpjet 0x54DC60, Ship
//     0x69EE30, Teleport 0x719E30 and Walk 0x75C7F0 return (this + 0x18) for it.
//
// IID_IUnknown (0x7F7C90), IID_IPersistStream (0x7F7C80) and IID_IPersist
// (0x7F7C70) are the SDK's uuid.lib constants (LIBRARY): they are declared by
// <objidl.h>, never defined here.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0x7ED358
extern "C" const IID IID_ILocomotion;
// GLOBAL: GAMEMD 0x7E9B10 — IPiggyback interface identifier.
extern "C" const IID IID_IPiggyback;

// ---------------------------------------------------------------------------
// ILocomotion: RTTI base at +4 of every locomotor, vtable of 50 slots
// (0..49). Slots 0-2 are IUnknown. In LocomotionClass 0x7EADF4 slots 0-2 are
// compiler adjustor thunks (`SUB [ESP+4],4; JMP primary`) and slot 29 is
// __purecall; every other slot points at a real default body.
//
// `this` of slots 3..49 is the ILocomotion SUBOBJECT (complete object + 4):
// retail bodies read the members at [this+4]/[this+8]/[this+0xC]/[this+0xD]
// for Owner/LinkedTo/Powered/Dirty (complete +8/+0xC/+0x10/+0x11). VC6 emits
// exactly this when a class overrides a virtual that is declared only in its
// non-primary base (no thunk is generated; only functions that also occupy the
// primary table, i.e. QI/AddRef/Release, get an adjustor). So a plain C++
// override reproduces retail; never hand-model the `this` shift.
// ---------------------------------------------------------------------------
class __declspec(novtable) ILocomotion : public IUnknown
{
public:
    // Slot 3 +0x0C. Stores the object into LinkedTo then Owner; returns S_OK.
    virtual HRESULT __stdcall LinkToObject(FootClass* object) = 0;
    // Slot 4 +0x10. Base: false.
    virtual bool __stdcall IsMoving() = 0;
    // Slot 5 +0x14. Returns a coordinate by value (hidden pointer, RET 8).
    virtual LocoCoord __stdcall Destination() = 0;
    // Slot 6 +0x18. Base: the linked object's Location (hidden pointer, RET 8).
    virtual LocoCoord __stdcall HeadToCoord() = 0;
    // Slot 7 +0x1C. One stack dword (a cell coordinate); returns a Move code (base 0).
    virtual int __stdcall CanEnterCell(int cell) = 0;
    // Slot 8 +0x20. Base: true.
    virtual bool __stdcall IsToHaveShadow() = 0;
    // Slot 9 +0x24. Hidden return pointer, then the voxel index key pointer.
    virtual LocoMatrix3D __stdcall DrawMatrix(unsigned int* key) = 0;
    // Slot 10 +0x28. Same shape as DrawMatrix.
    virtual LocoMatrix3D __stdcall ShadowMatrix(unsigned int* key) = 0;
    // Slot 11 +0x2C. Returns a 2D point by value (hidden pointer, RET 8).
    virtual LocoPoint2D __stdcall DrawPoint() = 0;
    // Slot 12 +0x30. Returns a 2D point by value (hidden pointer, RET 8).
    virtual LocoPoint2D __stdcall ShadowPoint() = 0;
    // Slot 13 +0x34. One stack dword (an unused flag in the base).
    virtual int __stdcall VisualCharacter(int unused) = 0;
    // Slot 14 +0x38. Base 0.
    virtual int __stdcall ZAdjust() = 0;
    // Slot 15 +0x3C. Base 2.
    virtual int __stdcall ZGradient() = 0;
    // Slot 16 +0x40. Per-frame update; base true.
    virtual bool __stdcall Process() = 0;
    // Slot 17 +0x44. Coordinate by value (12 stack bytes).
    virtual void __stdcall MoveTo(LocoCoord to) = 0;
    // Slot 18 +0x48.
    virtual void __stdcall StopMoving() = 0;
    // Slot 19 +0x4C. One stack dword (a binary-angle direction).
    virtual void __stdcall DoTurn(unsigned long dir) = 0;
    // Slot 20 +0x50.
    virtual void __stdcall Unlimbo() = 0;
    // Slot 21 +0x54.
    virtual void __stdcall TiltPitchAI() = 0;
    // Slot 22 +0x58. Sets Powered, then returns IsPowered() (slot 24).
    virtual bool __stdcall PowerOn() = 0;
    // Slot 23 +0x5C. Clears Powered, then returns IsPowered(). READ-ONLY here
    // (0x55A910 is owned elsewhere); declared so the slot holds its place.
    virtual bool __stdcall PowerOff() = 0;
    // Slot 24 +0x60.
    virtual bool __stdcall IsPowered() = 0;
    // Slot 25 +0x64. Base false.
    virtual bool __stdcall IsIonSensitive() = 0;
    // Slot 26 +0x68. One stack dword (direction); base false.
    virtual bool __stdcall Push(unsigned long dir) = 0;
    // Slot 27 +0x6C. One stack dword (direction); base false.
    virtual bool __stdcall Shove(unsigned long dir) = 0;
    // Slot 28 +0x70. Track number then a coordinate by value (0x14 total).
    virtual void __stdcall ForceTrack(int track, LocoCoord coord) = 0;
    // Slot 29 +0x74. PURE in LocomotionClass (__purecall 0x4C9150, RET 4).
    virtual int __stdcall InWhichLayer() = 0;
    // Slot 30 +0x78. Coordinate by value (RET 0x10).
    virtual void __stdcall ForceImmediateDestination(LocoCoord coord) = 0;
    // Slot 31 +0x7C. One stack dword (a ramp/slope index).
    virtual void __stdcall ForceNewSlope(int ramp) = 0;
    // Slot 32 +0x80. Base: IsMoving() (slot 4).
    virtual bool __stdcall IsMovingNow() = 0;
    // Slot 33 +0x84. Base: owner virtual +0x538.
    virtual int __stdcall ApparentSpeed() = 0;
    // Slot 34 +0x88. Base 0.
    virtual int __stdcall DrawingCode() = 0;
    // Slot 35 +0x8C. Base 0 (no firing restriction).
    virtual int __stdcall CanFire() = 0;
    // Slot 36 +0x90. Behavioural name; base 0 (int).
    virtual int __stdcall GetStatus() = 0;
    // Slot 37 +0x94. Behavioural name; base no-op.
    virtual void __stdcall AcquireHunterSeekerTarget() = 0;
    // Slot 38 +0x98. Tunnel returns (state == 5 || state == 6); base false.
    virtual bool __stdcall IsSurfacing() = 0;
    // Slot 39 +0x9C. One stack dword (mark/unmark flag); base no-op.
    virtual void __stdcall MarkAllOccupationBits(int mark) = 0;
    // Slot 40 +0xA0. Coordinate by value (RET 0x10); base false.
    virtual bool __stdcall IsMovingHere(LocoCoord to) = 0;
    // Slot 41 +0xA4. Base false.
    virtual bool __stdcall WillJumpTracks() = 0;
    // Slot 42 +0xA8. Base: IsMovingNow() (slot 32).
    virtual bool __stdcall IsReallyMovingNow() = 0;
    // Slot 43 +0xAC. Walk clears its moving byte here; base no-op.
    virtual void __stdcall StopMovementAnimation() = 0;
    // Slot 44 +0xB0. Walk resets two coordinates to the global empty; base no-op.
    virtual void __stdcall ClearCoords() = 0;
    // Slot 45 +0xB4. Ship stores 0 into a byte member; base no-op.
    virtual void __stdcall Lock() = 0;
    // Slot 46 +0xB8. Ship stores 1 into the same byte; base no-op.
    virtual void __stdcall Unlock() = 0;
    // Slot 47 +0xBC. Behavioural name; leaf getters return a member; base -1.
    virtual int __stdcall GetTrackNumber() = 0;
    // Slot 48 +0xC0. Behavioural name; base -1.
    virtual int __stdcall GetTrackIndex() = 0;
    // Slot 49 +0xC4. Behavioural name; base -1.
    virtual int __stdcall GetSpeedAccum() = 0;
};


// VTABLE: GAMEMD 0x7E8254 — IPiggyback interface prefix (8 entries). The
// DropPod table and the five other piggyback tables expose the same five
// methods after IUnknown's three slots.
class __declspec(novtable) IPiggyback : public IUnknown
{
public:
    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* locomotion) = 0;
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** locomotion) = 0;
    virtual bool __stdcall IsOkToEnd() = 0;
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* clsid) = 0;
    virtual bool __stdcall IsPiggybacking() = 0;
};

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_INTERFACES_H
