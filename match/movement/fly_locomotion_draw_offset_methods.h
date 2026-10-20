// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Fifth translation unit of the FlyLocomotionClass cluster: the ILocomotion
//   slot at +0x2C of the locomotor vtable 0x7E89F4, which is the flyer's
//   per-frame draw offset. The sibling slot at +0x30 (0x4CF940) hands back a
//   zeroed pair and is already matched in fly_locomotion_leaf_methods.cpp;
//   this one keeps the X component zero and bobs the Y component.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo      `MOV EAX,[EDI+0x8]` at 0x4CF83C
//   +0x4C IsTakingOff   `MOV AL,[EDI+0x4C]` at 0x4CF8C2
//   +0x4D IsLanding     `MOV AL,[EDI+0x4D]` at 0x4CF8BB
// `RET 0x8` with the receiver at the first stack slot and the hidden eight-byte
// return buffer at the second is the __stdcall MEMBER layout; a free __stdcall
// function with an explicit self parameter puts the buffer first and returns
// an eight-byte value in the register pair instead.
//
// The client's slot 0 is IUnknown::QueryInterface (`MOV ECX,[EAX]; PUSH &out;
// PUSH 0x822410; PUSH EAX; CALL [ECX]`), so the client is COM-aggregated; the
// interface it hands back is used through its own slot +0x0C. 0x4D0430 is the
// already-matched member-release helper (see
// match/core/com_member_release_family_methods.h), which is what makes the
// held pointer a smart pointer rather than a raw one.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_DRAW_OFFSET_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_DRAW_OFFSET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The interface the client aggregates. Only IUnknown's three slots and the
// reader at +0x0C are reached.
struct IFace_004CF830;

struct IFaceVtbl_004CF830
{
    long (__stdcall* QueryInterface)(IFace_004CF830*, const void* riid,
                                     void** ppv);                    // +0x00
    unsigned long (__stdcall* AddRef)(IFace_004CF830*);              // +0x04
    unsigned long (__stdcall* Release)(IFace_004CF830*);             // +0x08
    int (__stdcall* GetGroundClearance)(IFace_004CF830*);            // +0x0C
};
GG_STATIC_ASSERT(offsetof(IFaceVtbl_004CF830, Release) == 0x8 &&
                 offsetof(IFaceVtbl_004CF830, GetGroundClearance) == 0xC);

struct IFace_004CF830 { IFaceVtbl_004CF830* Vtbl; };

// GLOBAL: GAMEMD 0x822410 — the interface id the client is queried for.
extern const char riid_00822410[16];
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// FUNCTION: GAMEMD 0x7DC720 (decl; reloc) — report a failed HRESULT.
void __stdcall FUN_007DC720(long hr);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) — table sine of a double.
extern "C" float __cdecl FUN_004CACB0(double angle);

// The one-pointer smart holder the release helper operates on.
struct Holder_004CF830
{
    IFace_004CF830* Held;   // +0x00

    // The release is a real destructor: retail writes both components of the
    // return value into the hidden buffer and only then releases, which is
    // scope-exit order, not a statement the body could have written. The
    // no-throw specification keeps the locked `/GX` from wrapping the scope
    // in an unwind frame retail's bare prologue rules out.
    // Defined in-class so cl expands it at the scope exit; an out-of-line
    // definition is emitted as a call retail does not have.
    ~Holder_004CF830() throw()
    {
        if (Held != 0) {
            Held->Vtbl->Release(Held);
        }
    }
};
GG_STATIC_ASSERT(sizeof(Holder_004CF830) == 4);

// FUNCTION: GAMEMD 0x4D0430 (decl; reloc) — release whatever the holder holds.
void __fastcall FUN_004D0430(Holder_004CF830* self);

// The client's type object; only the ground-hugging gate byte is read.
struct FootType_004CF830
{
    char _pad000[0xC95];   // +0x0000
    char IsFlatOnGround;   // +0x0C95
};
GG_STATIC_ASSERT(offsetof(FootType_004CF830, IsFlatOnGround) == 0xC95);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CF830;

struct Foot_004CF830
{
    FootVtbl_004CF830* Vtbl;   // +0x0000
};

typedef FootType_004CF830* (Foot_004CF830::*FnType_004CF830)();
typedef int (Foot_004CF830::*FnInt_004CF830)();

struct FootVtbl_004CF830
{
    long (__stdcall* QueryInterface)(Foot_004CF830*, const void* riid,
                                     void** ppv);                   // +0x00
    char              _pad004[0x84 - 0x4];                          // +0x0004
    FnType_004CF830   At_84;                                        // +0x0084
    char              _pad088[0x1C8 - 0x88];                        // +0x0088
    FnInt_004CF830    At_1C8;                                       // +0x01C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CF830, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CF830, At_1C8) == 0x1C8);

// The eight-byte pair the slot hands back. The user-declared constructor is
// what keeps it in memory behind a hidden pointer, which is how retail writes
// it (`MOV ESI,[ESP+0x18]; MOV [ESI],EAX; MOV [ESI+4],EBP; MOV EAX,ESI`).
struct Pair_004CF830
{
    int A;   // +0x00
    int B;   // +0x04
    Pair_004CF830() {}
};
GG_STATIC_ASSERT(sizeof(Pair_004CF830) == 8);

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
struct FlyLocoOffset
{
    void*            _vtable_locomotor;      // +0x0000  (object +0x04)
    void*            _vtable_persist;        // +0x0004  (object +0x08)
    Foot_004CF830*   LinkedTo;               // +0x0008  (object +0x0C)
    char             _pad00C[0x4C - 0xC];    // +0x000C
    char             IsTakingOff;            // +0x004C  (object +0x50)
    char             IsLanding;              // +0x004D  (object +0x51)

    // FUNCTION: GAMEMD 0x4CF830
    Pair_004CF830 __stdcall GetDrawOffset();
};
GG_STATIC_ASSERT(offsetof(FlyLocoOffset, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoOffset, IsTakingOff) == 0x4C &&
                 offsetof(FlyLocoOffset, IsLanding) == 0x4D);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_DRAW_OFFSET_METHODS_H
