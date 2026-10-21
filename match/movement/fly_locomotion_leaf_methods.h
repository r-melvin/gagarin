// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Second translation unit of the FlyLocomotionClass cluster. The class was
//   identified from its own runtime type information - see
//   fly_locomotion_com_methods.h for that derivation; this header only adds
//   the members and slots the leaf bodies in
//   fly_locomotion_leaf_methods.cpp touch.
//
//   The locomotor interface vtable at 0x7E89F4 was read out whole
//   (`ghidra memory read 0x7E89F4 200`). Slots used here, by byte offset into
//   that table: +0x0C = 0x4CCA20, +0x10 = 0x4CCA90, +0x14 = 0x4CCAE0,
//   +0x30 = 0x4CF940, +0x4C = 0x4CFC10, +0x80 = 0x4CCAC0, +0x84 = 0x4CFE20,
//   +0x90 = 0x4CFE50. The persist vtable at 0x7E8AC0 and the locomotor vtable
//   at 0x7E89F4 are the two constants the destructor at 0x4CCA70 re-seats,
//   which is what pins the persist vptr to object +0x00 and the locomotor
//   vptr to object +0x04.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// Every displacement below is interface-relative (four lower than the
// object's), because the COM methods receive the locomotor interface pointer:
//   +0x08 LinkedTo          `MOV ECX,[ESI+0x8]`      in 0x4CFE20, 0x4CFC10
//   +0x14 IsOnBridge        `MOV BYTE PTR [EBX+0x14]` in 0x4CCA20
//   +0x18/+0x1C/+0x20 the destination coordinate, three dword moves in
//                           0x4CCAE0
//   +0x30 HasMoveOrder       `MOV CL,[EAX+0x30]`       in 0x4CCA90
//   +0x44 Height            `FLD QWORD PTR [EAX+0x44]` in 0x4CCAC0, 0x4CFE20
//   +0x4C IsTakingOff       `MOV CL,[EAX+0x4C]`       in 0x4CFE50
//   +0x4D IsLanding         `MOV CL,[EAX+0x4D]`       in 0x4CFE50
//   +0x4F IsSpinning, +0x50 SpinRate, +0x54 SpinCount - object +0x53/+0x54/
//                           +0x58, written by 0x4CFDD0 off ECX.
// LinkedTo's own slots: +0x2C returns the type discriminant 0x4CCA20 compares
// against two, +0x84 returns the owner object, +0x1C8 the remaining travel.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_LEAF_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_LEAF_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

typedef long GgHRESULT;

// A map coordinate: three dwords, copied whole by the slot at +0x14.
struct Coord_004CCAE0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_004CCAE0) == 12);

// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
extern const Coord_004CCAE0 UnsetCoord_008B3C78;

// The object the slot at +0x84 of LinkedTo's vtable hands back. Only the two
// fields the leaves read are modelled.
struct Owner_004CFE20
{
    char _pad000[0x678];   // +0x0000
    int  At_678;           // +0x0678
    char _pad67C[0xC95 - 0x67C];
    char At_C95;           // +0x0C95
};
GG_STATIC_ASSERT(offsetof(Owner_004CFE20, At_678) == 0x678 &&
                 offsetof(Owner_004CFE20, At_C95) == 0xC95);

// LinkedTo's type object; only the gate byte at +0xE0D is read.
struct FootType_004CCA20
{
    char _pad000[0xE0D];   // +0x0000
    char At_E0D;           // +0x0E0D
};
GG_STATIC_ASSERT(offsetof(FootType_004CCA20, At_E0D) == 0xE0D);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CCA20;

// The object reached through LinkedTo +0x3A0 by the slot at +0x4C. Its one
// used method takes the address of a four-byte handle.
struct Target_004CFC10
{
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc)
    void Assign(void** handle);
};

struct Foot_004CCA20
{
    FootVtbl_004CCA20* Vtbl;             // +0x0000
    char _pad004[0x2E8 - 0x4];           // +0x0004
    float Altitude;                      // +0x02E8
    char _pad2EC[0x3A0 - 0x2EC];         // +0x02EC
    Target_004CFC10 TargetSlot;          // +0x03A0
    char _pad3A1[0x6C4 - 0x3A1];         // +0x03A1
    FootType_004CCA20* Type;             // +0x06C4
};
GG_STATIC_ASSERT(offsetof(Foot_004CCA20, Altitude) == 0x2E8 &&
                 offsetof(Foot_004CCA20, TargetSlot) == 0x3A0 &&
                 offsetof(Foot_004CCA20, Type) == 0x6C4);

typedef int (Foot_004CCA20::*FnWhatAmI_004CCA20)();
typedef Owner_004CFE20* (Foot_004CCA20::*FnOwner_004CFE20)();

struct FootVtbl_004CCA20
{
    char _pad000[0x2C];                  // +0x0000
    FnWhatAmI_004CCA20 At_2C;            // +0x002C
    char _pad030[0x84 - 0x30];           // +0x0030
    FnOwner_004CFE20 At_84;              // +0x0084
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CCA20, At_2C) == 0x2C &&
                 offsetof(FootVtbl_004CCA20, At_84) == 0x84);

// The eight-byte pair the slot at +0x30 hands back, always zeroed.
struct Pair_004CF940
{
    int A;   // +0x00
    int B;   // +0x04
};
GG_STATIC_ASSERT(sizeof(Pair_004CF940) == 8);

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
// Packed to four, because the interface pointer sits four into the object, so
// the double at object +0x48 lands on an odd four-byte boundary here.
#pragma pack(push, 4)

// The COM slots are __stdcall, so the interface pointer arrives as the first
// stacked argument. Only the slots these bodies dispatch through carry names.
struct FlyLocoIface
{
    virtual GgHRESULT __stdcall QueryInterface(const void* riid,
                                               void** ppv) = 0;      // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                    // +0x04
    virtual unsigned long __stdcall Release() = 0;                   // +0x08
    virtual GgHRESULT __stdcall LinkTo(Foot_004CCA20* obj) = 0;      // +0x0C
    // +0x10 — true while the flyer is still above the ground.
    virtual int __stdcall IsToHaveShadow() = 0;                      // +0x10

    char  _pad004[0x4];              // +0x0004  (object +0x08)
    Foot_004CCA20* LinkedTo;         // +0x0008  (object +0x0C)
    char  _pad00C[0x8];              // +0x000C
    char  IsOnBridge;                // +0x0014  (object +0x18)
    char  _pad015[0x3];              // +0x0015
    Coord_004CCAE0 Destination;      // +0x0018  (object +0x1C)
    char  _pad024[0xC];              // +0x0024
    char  HasMoveOrder;               // +0x0030  (object +0x34)
    char  _pad031[0x13];             // +0x0031
    double Height;                   // +0x0044  (object +0x48)
    char  IsTakingOff;               // +0x004C  (object +0x50)
    char  IsLanding;                 // +0x004D  (object +0x51)

    // The two slots that hand back an aggregate. A __stdcall MEMBER puts the
    // hidden return buffer *after* the receiver, which is retail's stack
    // layout here (`this` at +4, the buffer at +8); the same bodies written
    // as free functions with an explicit self parameter put the buffer first
    // and every frame displacement moves.
    // FUNCTION: GAMEMD 0x4CCAE0
    Coord_004CCAE0 __stdcall GetDestination();
    // FUNCTION: GAMEMD 0x4CF940
    Pair_004CF940 __stdcall GetShadowOffset();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoIface, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoIface, IsOnBridge) == 0x14 &&
                 offsetof(FlyLocoIface, Destination) == 0x18 &&
                 offsetof(FlyLocoIface, HasMoveOrder) == 0x30 &&
                 offsetof(FlyLocoIface, Height) == 0x44 &&
                 offsetof(FlyLocoIface, IsTakingOff) == 0x4C &&
                 offsetof(FlyLocoIface, IsLanding) == 0x4D);

// The same class through its own `this` - the __thiscall members and the
// destructor, whose displacements are the object's own.
struct FlyLocoObject
{
    void* PersistVptr;      // +0x0000
    void* LocomotorVptr;    // +0x0004
    char  _pad008[0x4B];    // +0x0008
    char  IsSpinning;       // +0x0053
    int   SpinRate;         // +0x0054
    int   SpinCount;        // +0x0058

    // FUNCTION: GAMEMD 0x4CCA70
    void Destroy();
    // FUNCTION: GAMEMD 0x4CFDD0
    void StartSpin();
};
GG_STATIC_ASSERT(offsetof(FlyLocoObject, LocomotorVptr) == 0x04 &&
                 offsetof(FlyLocoObject, IsSpinning) == 0x53 &&
                 offsetof(FlyLocoObject, SpinRate) == 0x54 &&
                 offsetof(FlyLocoObject, SpinCount) == 0x58);

// The scenario's random generator; the touchdown spin is drawn from it.
struct RandomClass_004CFDD0
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — RandomClass::RandomRanged.
    int RandomRanged(int minval, int maxval);
};

struct ScenarioClass_004CFDD0
{
    char _pad000[0x218];                  // +0x0000
    RandomClass_004CFDD0 RandomNumber;    // +0x0218
};
GG_STATIC_ASSERT(offsetof(ScenarioClass_004CFDD0, RandomNumber) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — the scenario object.
extern ScenarioClass_004CFDD0* Scenario_00A8B230;

// The base whose destructor the derived one tail-jumps to. A layout-
// compatible stand-in, cast onto `this`, is what emits the bare jump.
struct LocoBase_0055A6F0
{
    // FUNCTION: GAMEMD 0x55A6F0 (decl; reloc) — LocomotionClass::~LocomotionClass.
    void Destroy();
};

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_LEAF_METHODS_H
