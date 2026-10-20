// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Sixth translation unit of the FlyLocomotionClass cluster: the ILocomotion
//   slot at +0x40 of the locomotor vtable 0x7E89F4, the flyer's per-frame
//   step. It is the hub of the cluster - it is the only caller of the two
//   __thiscall members at 0x4CD2A0 and 0x4CEFB0, which is what establishes
//   those two as members of this class rather than free helpers.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo      `MOV ECX,[ESI+0x8]`            at 0x4CCB6C
//   +0x18 Destination   three dwords `[ESI+0x18/0x1C/0x20]` at 0x4CCBF0
//   +0x34 Speed         `MOV EAX,[ESI+0x34]` / `MOV [ESI+0x34],EAX`
//   +0x3C Ramp          `FLD QWORD PTR [ESI+0x3C]`     at 0x4CCB55
//   +0x4C IsTakingOff   `MOV AL,[ESI+0x4C]`            at 0x4CCB4E
//   +0x4D IsLanding     `MOV AL,[ESI+0x4D]`            at 0x4CCB47
// `LEA EDI,[ESI-0x4]` at 0x4CCBB3 is the object's own `this`, four below the
// interface pointer, and every __thiscall call in the tail goes through it.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PROCESS_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PROCESS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A map coordinate: three dwords, passed whole into 0x4CEFB0.
struct Coord_004CCB40
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    Coord_004CCB40() {}
    Coord_004CCB40(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(Coord_004CCB40) == 12);

// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
extern const Coord_004CCB40 UnsetCoord_008B3C78;

// The client's type object. Declaration order matters - see gg_vslot.h.
struct FootTypeVtbl_004CCB40;

struct FootType_004CCB40
{
    FootTypeVtbl_004CCB40* Vtbl;   // +0x0000
};

typedef int (FootType_004CCB40::*FnInt_004CCB40)();

struct FootTypeVtbl_004CCB40
{
    char           _pad000[0xBC];   // +0x0000
    FnInt_004CCB40 At_BC;           // +0x00BC
};
GG_STATIC_ASSERT(offsetof(FootTypeVtbl_004CCB40, At_BC) == 0xBC);

// The locomotor's client object.
struct FootVtbl_004CCB40;

struct Foot_004CCB40
{
    FootVtbl_004CCB40* Vtbl;              // +0x0000
    char _pad004[0x6C - 0x4];             // +0x0004
    int  Remaining;                       // +0x006C
    char _pad070[0x90 - 0x70];            // +0x0070
    char IsAlive;                         // +0x0090
};
GG_STATIC_ASSERT(offsetof(Foot_004CCB40, Remaining) == 0x6C &&
                 offsetof(Foot_004CCB40, IsAlive) == 0x90);

typedef FootType_004CCB40* (Foot_004CCB40::*FnType_004CCB40)();
typedef int (Foot_004CCB40::*FnIntF_004CCB40)();
typedef char (Foot_004CCB40::*FnChar_004CCB40)();
typedef void (Foot_004CCB40::*FnVoid_004CCB40)();

struct FootVtbl_004CCB40
{
    char            _pad000[0x84];            // +0x0000
    FnType_004CCB40 At_84;                    // +0x0084
    char            _pad088[0x1C8 - 0x88];    // +0x0088
    FnIntF_004CCB40 At_1C8;                   // +0x01C8
    char            _pad1CC[0x1EC - 0x1CC];   // +0x01CC
    FnVoid_004CCB40 At_1EC;                   // +0x01EC
    char            _pad1F0[0x200 - 0x1F0];   // +0x01F0
    FnChar_004CCB40 At_200;                   // +0x0200
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CCB40, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CCB40, At_1C8) == 0x1C8 &&
                 offsetof(FootVtbl_004CCB40, At_1EC) == 0x1EC &&
                 offsetof(FootVtbl_004CCB40, At_200) == 0x200);

// FlyLocomotionClass through its own `this`: only the four __thiscall members
// this body calls are named. 0x4CE5A0 and 0x4CFA70 are already matched in
// fly_locomotion_spin_methods.cpp.
struct FlyLocoObj_004CCB40
{
    // FUNCTION: GAMEMD 0x4CE5A0 (decl; reloc) — one frame of the touchdown spin.
    void ProcessSpin();
    // FUNCTION: GAMEMD 0x4CD510 (decl; reloc)
    void FUN_004CD510();
    // FUNCTION: GAMEMD 0x4CD600 (decl; reloc)
    void FUN_004CD600();
    // FUNCTION: GAMEMD 0x4CD2A0 (decl; reloc)
    void FUN_004CD2A0();
    // FUNCTION: GAMEMD 0x4CEFB0 (decl; reloc)
    void FUN_004CEFB0(int flag, Coord_004CCB40 where);
};

// A COM slot of the locomotor interface itself, dispatched on `this`:
// `MOV EAX,[ESI]; PUSH ESI; CALL [EAX+slot]` — the receiver goes on the stack
// rather than into ECX, which is the __stdcall COM convention RA2 uses.
struct FlyLocoProcess;
typedef char (__stdcall* SelfSlotB_004CCB40)(FlyLocoProcess*);
#define GG_FLY_SELF_B(p, slot) \
    ((*(SelfSlotB_004CCB40*)(*(char**)(p) + (slot)))(p))

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
// Packed to four, because the interface pointer sits four into the object, so
// the double at object +0x40 lands on an odd four-byte boundary here.
#pragma pack(push, 4)
struct FlyLocoProcess
{
    void*             _vtable_locomotor;      // +0x0000  (object +0x04)
    void*             _vtable_persist;        // +0x0004  (object +0x08)
    Foot_004CCB40*    LinkedTo;               // +0x0008  (object +0x0C)
    char              _pad00C[0x18 - 0xC];    // +0x000C
    Coord_004CCB40    Destination;            // +0x0018  (object +0x1C)
    char              _pad024[0x34 - 0x24];   // +0x0024
    int               Speed;                  // +0x0034  (object +0x38)
    char              _pad038[0x3C - 0x38];   // +0x0038
    double            Ramp;                   // +0x003C  (object +0x40)
    char              _pad044[0x4C - 0x44];   // +0x0044
    char              IsTakingOff;            // +0x004C  (object +0x50)
    char              IsLanding;              // +0x004D  (object +0x51)

    // FUNCTION: GAMEMD 0x4CCB40
    char __stdcall Process();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoProcess, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoProcess, Destination) == 0x18 &&
                 offsetof(FlyLocoProcess, Speed) == 0x34 &&
                 offsetof(FlyLocoProcess, Ramp) == 0x3C &&
                 offsetof(FlyLocoProcess, IsTakingOff) == 0x4C &&
                 offsetof(FlyLocoProcess, IsLanding) == 0x4D);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PROCESS_METHODS_H
