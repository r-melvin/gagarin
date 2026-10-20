// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Tenth translation unit of the FlyLocomotionClass cluster: the ILocomotion
//   slot at +0x48 of the locomotor vtable 0x7E89F4, which stops the flyer.
//   Membership is settled by the vtable read
//   (`ghidra memory read 0x7E89F4 200`, decimal count): +0x44 = 0x4CCC80,
//   +0x48 = 0x4CCFD0, +0x4C = 0x4CFC10.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo      `MOV ECX,[ESI+0x8]`, eleven times
//   +0x18 Destination   `ADD ESI,0x18` then three stores at 0x4CD27B..0x4CD28C
//   +0x4D IsLanding     `MOV AL,[ESI+0x4D]`            at 0x4CD217
// The frame is `SUB ESP,0x18` with two callee-saved pushes and `RET 0x4`: the
// receiver only, which is ILocomotion::Stop_Moving().
//
// The client's members: +0x6C the travel counter (its ADDRESS is handed to
// the slot at +0x16C, so the field is the head of a sub-object), +0x9C its
// location, +0x3D4 a gate byte. Its vtable slots: +0x2C the type
// discriminant, +0x16C a seven-argument order, +0x184 a three-way state,
// +0x480 a one-argument cell assignment, +0x4DC a gate.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_STOP_MOVING_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_STOP_MOVING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A world coordinate: three ints.
struct Coord_004CCFD0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_004CCFD0) == 0xC);

// A cell address: two shorts. User-declared default constructor, so the type
// is non-POD and a by-value result is built in a temporary and copied - which
// is retail's `MOV EAX,[ESP+0x24]; MOV [ESP+0x24],EAX` self-copy at 0x4CD024,
// the temporary and the named cell having been given the same slot.
struct Cell_004CCFD0
{
    short X;   // +0x00
    short Y;   // +0x02
    Cell_004CCFD0() {}
};
GG_STATIC_ASSERT(sizeof(Cell_004CCFD0) == 4);

// The signed divide-by-256 idiom, taken as two ints: retail reads the two
// components straight off the client's location and never materialises its
// address a second time.
inline Cell_004CCFD0 CellOf_004CCFD0(int x, int y)
{
    Cell_004CCFD0 r;
    r.X = (short)(x / 256);
    r.Y = (short)(y / 256);
    return r;
}

// GLOBAL: GAMEMD 0x8B3C58 — the engine's unset cell.
extern const Cell_004CCFD0 UnsetCell_008B3C58;
// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
extern const Coord_004CCFD0 UnsetCoord_008B3C78;
// GLOBAL: GAMEMD 0x8B3CAC — the bridge height a deck adds.
extern int BridgeHeight_008B3CAC;

// CellClass — only the flag dword @0x140 is touched, as `TEST CH,0x1`.
struct CellClass_004CCFD0
{
    char _pad000[0x140];   // +0x0000
    int  Flags;            // +0x0140
};
GG_STATIC_ASSERT(offsetof(CellClass_004CCFD0, Flags) == 0x140);

// The object the global at 0x8871E0 points at; only +0xFA8 is read.
struct Rules_008871E0
{
    char  _pad000[0xFA8];   // +0x0000
    void* At_FA8;           // +0x0FA8
};
GG_STATIC_ASSERT(offsetof(Rules_008871E0, At_FA8) == 0xFA8);
// GLOBAL: GAMEMD 0x8871E0 — that object.
extern Rules_008871E0* Rules_008871E0_Instance;

// MapClass singleton — the object itself lives at 0x87F7E8 (`MOV ECX,imm32`).
struct Map_004CCFD0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x578460 (decl; reloc) — is the cell usable?
    char At_578460(Cell_004CCFD0* cell, int flag);
    // FUNCTION: GAMEMD 0x586AC0 (decl; reloc) — nudge to a usable cell; the
    // result comes back through the buffer whose address is handed in and is
    // read straight off the returned register.
    Cell_004CCFD0* At_586AC0(Cell_004CCFD0* out, Cell_004CCFD0* cell,
                             int flag);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCell(cell).
    CellClass_004CCFD0* GetCell(Cell_004CCFD0* cell);
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — MapClass::GetCellAt(coord).
    CellClass_004CCFD0* GetCellAt(Coord_004CCFD0* coord, int flag);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) — the ground height at a coord.
    int GetZHeightAt(const Coord_004CCFD0& coord);
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — find a free cell near one.
    // Fifteen stacked arguments plus the receiver; the first is the buffer
    // the cell comes back in, and retail reads the cell off the returned
    // register, so it is an explicit out-parameter and not a hidden return.
    Cell_004CCFD0* NearByLocation(Cell_004CCFD0* out, Cell_004CCFD0* cell,
                                  int a3, int a4, int a5, int a6, int a7,
                                  int a8, int a9, int a10, int a11, int a12,
                                  Cell_004CCFD0* a13, int a14, int a15);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_004CCFD0 MapInstance_004CCFD0;

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CCFD0;

struct Foot_004CCFD0
{
    FootVtbl_004CCFD0* Vtbl;                 // +0x0000
    char           _pad004[0x6C - 0x4];      // +0x0004
    int            At_6C;                    // +0x006C
    char           _pad070[0x9C - 0x70];     // +0x0070
    Coord_004CCFD0 Location;                 // +0x009C
    char           _pad0A8[0x3D4 - 0xA8];    // +0x00A8
    char           At_3D4;                   // +0x03D4

    // FUNCTION: GAMEMD 0x41A160 (decl; reloc) — the flyer's own parking cell.
    CellClass_004CCFD0* FUN_0041A160();
    // FUNCTION: GAMEMD 0x418E20 (decl; reloc) — pick a cell to settle on.
    CellClass_004CCFD0* FUN_00418E20(CellClass_004CCFD0* cell);
};
GG_STATIC_ASSERT(offsetof(Foot_004CCFD0, At_6C) == 0x6C &&
                 offsetof(Foot_004CCFD0, Location) == 0x9C &&
                 offsetof(Foot_004CCFD0, At_3D4) == 0x3D4);

typedef int (Foot_004CCFD0::*FnInt_004CCFD0)();
typedef char (Foot_004CCFD0::*FnChar_004CCFD0)();
typedef void (Foot_004CCFD0::*FnOrder_004CCFD0)(int*, int, void*, int, int,
                                                int, int);
typedef void (Foot_004CCFD0::*FnSettle_004CCFD0)(CellClass_004CCFD0*);

struct FootVtbl_004CCFD0
{
    char              _pad000[0x2C];           // +0x0000
    FnInt_004CCFD0    At_2C;                   // +0x002C
    char              _pad030[0x16C - 0x30];   // +0x0030
    FnOrder_004CCFD0  At_16C;                  // +0x016C
    char              _pad170[0x184 - 0x170];  // +0x0170
    FnInt_004CCFD0    At_184;                  // +0x0184
    char              _pad188[0x480 - 0x188];  // +0x0188
    FnSettle_004CCFD0 At_480;                  // +0x0480
    char              _pad484[0x4DC - 0x484];  // +0x0484
    FnChar_004CCFD0   At_4DC;                  // +0x04DC
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CCFD0, At_2C) == 0x2C &&
                 offsetof(FootVtbl_004CCFD0, At_16C) == 0x16C &&
                 offsetof(FootVtbl_004CCFD0, At_184) == 0x184 &&
                 offsetof(FootVtbl_004CCFD0, At_480) == 0x480 &&
                 offsetof(FootVtbl_004CCFD0, At_4DC) == 0x4DC);

// A COM slot of the locomotor interface itself, dispatched on `this`:
// `MOV EAX,[ESI]; PUSH ESI; CALL [EAX+0x10]`.
struct FlyLocoStop;
typedef char (__stdcall* SelfSlotB_004CCFD0)(FlyLocoStop*);
#define GG_FLY_SELF_B(p, slot) \
    ((*(SelfSlotB_004CCFD0*)(*(char**)(p) + (slot)))(p))

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
#pragma pack(push, 4)
struct FlyLocoStop
{
    void*           _vtable_locomotor;      // +0x0000  (object +0x04)
    void*           _vtable_persist;        // +0x0004  (object +0x08)
    Foot_004CCFD0*  LinkedTo;               // +0x0008  (object +0x0C)
    char            _pad00C[0x18 - 0xC];    // +0x000C
    Coord_004CCFD0  Destination;            // +0x0018  (object +0x1C)
    char            _pad024[0x4D - 0x24];   // +0x0024
    char            IsLanding;              // +0x004D  (object +0x51)

    // FUNCTION: GAMEMD 0x4CCFD0
    void __stdcall StopMoving();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoStop, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoStop, Destination) == 0x18 &&
                 offsetof(FlyLocoStop, IsLanding) == 0x4D);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_STOP_MOVING_METHODS_H
