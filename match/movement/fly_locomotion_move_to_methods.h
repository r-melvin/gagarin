// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Ninth translation unit of the FlyLocomotionClass cluster: the ILocomotion
//   slot at +0x44 of the locomotor vtable 0x7E89F4, which hands the flyer a
//   new destination. Membership is settled by the vtable read, not by
//   proximity: `ghidra memory read 0x7E89F4 200` puts 0x4CCC80 in slot +0x44,
//   between the flyer's own per-frame step at +0x40 (0x4CCB40) and its stop
//   at +0x48 (0x4CCFD0).
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo      `MOV ECX,[EBX+0x8]` / `LEA EDI,[EBX+0x8]` at 0x4CCCE6
//   +0x18/+0x1C/+0x20 Destination, three dword stores at 0x4CCDC9..0x4CCDD8
//   +0x30 HasMoveOrder   `MOV BYTE PTR [EBX+0x30],0x1`   at 0x4CCEAA
//   +0x4C IsTakingOff   `MOV AL,[EBX+0x4C]`             at 0x4CCDB2
//   +0x4D IsLanding     `MOV AL,[EBX+0x4D]`             at 0x4CCCDB
//   +0x58 unknown_58    `MOV [EBX+0x58],AL`             at 0x4CCF86
// `LEA ECX,[EBX-0x4]` at 0x4CCDCC and 0x4CCED1 is the object's own `this`,
// four below the interface pointer, and both __thiscall members it reaches
// (0x4CFA70, 0x4CF950) are already matched elsewhere in this cluster.
//
// The frame is `SUB ESP,0xC` with four callee-saved pushes and `RET 0x10`:
// the receiver plus a twelve-byte coordinate passed by value, which is
// ILocomotion::Move_To(CoordStruct).
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MOVE_TO_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MOVE_TO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A world coordinate: three ints.
struct Coord_004CCC80
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    Coord_004CCC80() {}
    // The three-integer form is what builds retail's twelve-byte frame
    // temporary: the copy the map lookup takes the address of is a
    // constructed temporary, not a named copy of the by-value parameter,
    // which cl proves redundant and elides.
    Coord_004CCC80(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(Coord_004CCC80) == 0xC);

// A cell address: two shorts. The conversion is the signed divide-by-256
// idiom cl emits as `CDQ; AND EDX,0xFF; ADD EAX,EDX; SAR EAX,8`, and the two
// components are compared sixteen bits at a time (`CMP SI,CX`), which is what
// pins them as shorts rather than ints.
struct Cell_004CCC80
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Cell_004CCC80) == 4);

// Taken as two ints rather than as a coordinate: retail reads the two
// components straight off their member displacements (`[EBX+0x18]`,
// `[EBX+0x1C]`) and never materialises the coordinate's address, which a
// reference parameter forces and a by-value parameter turns into a third
// load of the unused Z.
inline Cell_004CCC80 CellOf_004CCC80(int x, int y)
{
    Cell_004CCC80 r;
    r.X = (short)(x / 256);
    r.Y = (short)(y / 256);
    return r;
}

// Written with the arguments by value so cl's right-to-left evaluation runs
// the destination's conversion first, which is retail's order.
inline int operator==(Cell_004CCC80 a, Cell_004CCC80 b)
{
    return a.X == b.X && a.Y == b.Y;
}

// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
extern const Coord_004CCC80 UnsetCoord_008B3C78;

// The client's type object; only the gate byte at +0xE0A is read.
struct FootTypeVtbl_004CCC80;

struct FootType_004CCC80
{
    FootTypeVtbl_004CCC80* Vtbl;          // +0x0000
    char _pad004[0xE0A - 0x4];            // +0x0004
    char At_E0A;                          // +0x0E0A
};
GG_STATIC_ASSERT(offsetof(FootType_004CCC80, At_E0A) == 0xE0A);

typedef int (FootType_004CCC80::*FnTypeInt_004CCC80)();

struct FootTypeVtbl_004CCC80
{
    char               _pad000[0xBC];     // +0x0000
    FnTypeInt_004CCC80 At_BC;             // +0x00BC
};
GG_STATIC_ASSERT(offsetof(FootTypeVtbl_004CCC80, At_BC) == 0xBC);

// MapClass singleton — the object itself lives at 0x87F7E8 (`MOV ECX,imm32`).
struct Map_004CCC80
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x578080 (decl; reloc) — the ground height at a coord.
    int GetZHeightAt(const Coord_004CCC80& coord);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_004CCC80 MapInstance_004CCC80;

// The interface the client aggregates. Only IUnknown's Release and the
// clearance reader at +0x0C and the gate at +0x20 are reached.
struct IFace_004CCC80;

struct IFaceVtbl_004CCC80
{
    long (__stdcall* QueryInterface)(IFace_004CCC80*, const void* riid,
                                     void** ppv);                    // +0x00
    unsigned long (__stdcall* AddRef)(IFace_004CCC80*);              // +0x04
    unsigned long (__stdcall* Release)(IFace_004CCC80*);             // +0x08
    int (__stdcall* GetGroundClearance)(IFace_004CCC80*);            // +0x0C
    char _pad010[0x20 - 0x10];                                       // +0x10
    int (__stdcall* At_20)(IFace_004CCC80*);                         // +0x20
};
GG_STATIC_ASSERT(offsetof(IFaceVtbl_004CCC80, GetGroundClearance) == 0xC &&
                 offsetof(IFaceVtbl_004CCC80, At_20) == 0x20);

struct IFace_004CCC80 { IFaceVtbl_004CCC80* Vtbl; };

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CCC80;

struct Foot_004CCC80
{
    FootVtbl_004CCC80* Vtbl;                  // +0x0000
    char           _pad004[0x6C - 0x4];       // +0x0004
    int            Remaining;                 // +0x006C
    char           _pad070[0x9C - 0x70];      // +0x0070
    Coord_004CCC80 Location;                  // +0x009C
    char           _pad0A8[0x2B4 - 0xA8];     // +0x00A8
    int            At_2B4;                    // +0x02B4
    char           _pad2B8[0x2FC - 0x2B8];    // +0x02B8
    int            At_2FC;                    // +0x02FC
    char           _pad300[0x6C4 - 0x300];    // +0x0300
    FootType_004CCC80* Type;                  // +0x06C4
};
GG_STATIC_ASSERT(offsetof(Foot_004CCC80, Remaining) == 0x6C &&
                 offsetof(Foot_004CCC80, Location) == 0x9C &&
                 offsetof(Foot_004CCC80, At_2B4) == 0x2B4 &&
                 offsetof(Foot_004CCC80, At_2FC) == 0x2FC &&
                 offsetof(Foot_004CCC80, Type) == 0x6C4);

typedef char (Foot_004CCC80::*FnChar_004CCC80)();
typedef int (Foot_004CCC80::*FnInt_004CCC80)();
typedef FootType_004CCC80* (Foot_004CCC80::*FnType_004CCC80)();

struct FootVtbl_004CCC80
{
    char            _pad000[0x2C];            // +0x0000
    FnInt_004CCC80  At_2C;                    // +0x002C
    char            _pad030[0x84 - 0x30];     // +0x0030
    FnType_004CCC80 At_84;                    // +0x0084
    char            _pad088[0x1C8 - 0x88];    // +0x0088
    FnInt_004CCC80  At_1C8;                   // +0x01C8
    char            _pad1CC[0x1D4 - 0x1CC];   // +0x01CC
    FnChar_004CCC80 At_1D4;                   // +0x01D4
    FnChar_004CCC80 At_1D8;                   // +0x01D8
    char            _pad1DC[0x37C - 0x1DC];   // +0x01DC
    FnChar_004CCC80 At_37C;                   // +0x037C
    FnChar_004CCC80 At_380;                   // +0x0380
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CCC80, At_2C) == 0x2C &&
                 offsetof(FootVtbl_004CCC80, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CCC80, At_1C8) == 0x1C8 &&
                 offsetof(FootVtbl_004CCC80, At_1D4) == 0x1D4 &&
                 offsetof(FootVtbl_004CCC80, At_1D8) == 0x1D8 &&
                 offsetof(FootVtbl_004CCC80, At_37C) == 0x37C &&
                 offsetof(FootVtbl_004CCC80, At_380) == 0x380);

// FUNCTION: GAMEMD 0x7DC720 (decl; reloc) — report a failed HRESULT.
void __stdcall FUN_007DC720(long hr);

// The one-pointer smart holder. Unlike the copies in
// fly_locomotion_approach_methods.cpp and
// fly_locomotion_draw_offset_methods.cpp, every one of its operations is
// called OUT OF LINE here, so each is a declared-not-defined member: cl
// refuses the receiver-register convention on a free function, so the
// receiver has to arrive as a member's implicit `this`.
struct Holder_004CCC80
{
    IFace_004CCC80* Held;   // +0x00

    // FUNCTION: GAMEMD 0x4D0490 (decl; reloc) — query the client and adopt.
    long QueryFrom(Foot_004CCC80** source);
    // FUNCTION: GAMEMD 0x4D0430 (decl; reloc) — release whatever is held.
    void Release();
    // FUNCTION: GAMEMD 0x4D0400 (decl; reloc) — compare against a pointer,
    // asserting that pointer is null. Retail passes a literal zero.
    char operator==(IFace_004CCC80* other) const;

    // Expanded in place: the null check at 0x4CCF52 and the E_POINTER report
    // at 0x4CCF56 are inline, unlike the three members above.
    IFace_004CCC80* operator->() const
    {
        if (Held == 0) {
            FUN_007DC720((long)0x80004003);
        }
        return Held;
    }
};
GG_STATIC_ASSERT(sizeof(Holder_004CCC80) == 4);

// A COM slot of the locomotor interface itself, dispatched on `this`:
// `MOV EAX,[EBX]; PUSH EBX; CALL [EAX+0x60]` — the receiver goes on the stack
// rather than into ECX, which is the __stdcall COM convention RA2 uses.
struct FlyLocoMoveTo;
typedef char (__stdcall* SelfSlotB_004CCC80)(FlyLocoMoveTo*);
#define GG_FLY_SELF_B(p, slot) \
    ((*(SelfSlotB_004CCC80*)(*(char**)(p) + (slot)))(p))

// The object's own `this`, four below the interface pointer. Both members are
// already matched: 0x4CFA70 in fly_locomotion_spin_methods.cpp and 0x4CF950
// in fly_locomotion_takeoff_methods.cpp.
struct FlyLocoObj_004CCC80
{
    // FUNCTION: GAMEMD 0x4CFA70 (decl; reloc) — the landing switch.
    void BeginLanding();
    // FUNCTION: GAMEMD 0x4CF950 (decl; reloc) — the take-off switch.
    void BeginTakeOff();
};

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
#pragma pack(push, 4)
struct FlyLocoMoveTo
{
    void*              _vtable_locomotor;      // +0x0000  (object +0x04)
    void*              _vtable_persist;        // +0x0004  (object +0x08)
    Foot_004CCC80*     LinkedTo;               // +0x0008  (object +0x0C)
    char               _pad00C[0x18 - 0xC];    // +0x000C
    Coord_004CCC80     Destination;            // +0x0018  (object +0x1C)
    char               _pad024[0x30 - 0x24];   // +0x0024
    char               HasMoveOrder;            // +0x0030  (object +0x34)
    char               _pad031[0x4C - 0x31];   // +0x0031
    char               IsTakingOff;            // +0x004C  (object +0x50)
    char               IsLanding;              // +0x004D  (object +0x51)
    char               _pad04E[0x58 - 0x4E];   // +0x004E
    char               unknown_58;             // +0x0058  (object +0x5C)

    // FUNCTION: GAMEMD 0x4CCC80
    void __stdcall MoveTo(Coord_004CCC80 to);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoMoveTo, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoMoveTo, Destination) == 0x18 &&
                 offsetof(FlyLocoMoveTo, HasMoveOrder) == 0x30 &&
                 offsetof(FlyLocoMoveTo, IsTakingOff) == 0x4C &&
                 offsetof(FlyLocoMoveTo, IsLanding) == 0x4D &&
                 offsetof(FlyLocoMoveTo, unknown_58) == 0x58);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MOVE_TO_METHODS_H
