// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x50D440: the house's starting-unit vector
//   through `[EBX+0x17C]` (count) and `[EBX+0x170]` (items) — a
//   DynamicVectorClass at +0x16C; each entry's type at `[EBP]` and its cell
//   at `EBP+4` (pushed to CALL 0x5657A0 with `MOV ECX,0x87F7E8`, the map
//   singleton); the type's slots `[EDX+0x2C]` (WhatAmI, no args) and
//   `[EDX+0x8C]` (CreateObject, the house pushed); the created object's flag
//   byte `[EAX+0x14]` masked with 1; the cell's slot `[EDX+0x48]` (GetCoords,
//   out-buffer pushed, pointer returned); the techno's slots `[EAX+0x490]`
//   (coords pointer and 0 pushed, AL returned) and `[EDX+0xF8]` (no args).
//   The jump table at 0x50D524 and its index bytes at 0x50D530 dispatch
//   WhatAmI values 3, 7 and 0x28 to one body and 0x10 to another. Names are
//   YRpp's; every offset reconfirmed here. The
//   map singleton, GetCellAt and the GetCoords slot agree with
//   match/combat/bullet_class_lose_target_methods.h.
#ifndef GG_MATCH_AI_HOUSE_CLASS_RESPAWN_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_RESPAWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CoordStruct — the user-declared constructor makes VC6 return it through a
// hidden pointer, which is the temporary retail builds at [ESP+0x20] before
// copying it into the named local.
struct Coord_0050D440
{
    int X;   // +0x0
    int Y;   // +0x4
    int Z;   // +0x8

    Coord_0050D440() { }
};
GG_STATIC_ASSERT(sizeof(Coord_0050D440) == 0xC);

struct CellStruct_0050D440
{
    short X;   // +0x0
    short Y;   // +0x2
};
GG_STATIC_ASSERT(sizeof(CellStruct_0050D440) == 0x4);

struct House_0050D440;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct AbsVtbl_0050D440;

// Any AbstractClass: the flag byte and the slots reached here. Slot +0x2C is
// WhatAmI; +0x48 GetCoords (on a cell); +0x8C CreateObject (on a type);
// +0x490 and +0xF8 are the techno's Unlimbo and the no-argument follow-up.
struct Abs_0050D440
{
    AbsVtbl_0050D440* Vtbl;   // +0x0000
    char _pad004[0x10];       // +0x0004
    char Flags;               // +0x0014  bit 0 => the object is a techno
};
GG_STATIC_ASSERT(offsetof(Abs_0050D440, Flags) == 0x14);

typedef int            (Abs_0050D440::*Fn2C_0050D440)();
typedef Coord_0050D440 (Abs_0050D440::*Fn48_0050D440)();
typedef Abs_0050D440*  (Abs_0050D440::*Fn8C_0050D440)(House_0050D440* owner);
typedef void           (Abs_0050D440::*FnF8_0050D440)();
typedef bool           (Abs_0050D440::*Fn490_0050D440)(Coord_0050D440* coord, int dir);

struct AbsVtbl_0050D440
{
    char _pad000[0x2C];              // +0x0000
    Fn2C_0050D440 WhatAmI;           // +0x002C
    char _pad030[0x48 - 0x30];       // +0x0030
    Fn48_0050D440 GetCoords;         // +0x0048
    char _pad04C[0x8C - 0x4C];       // +0x004C
    Fn8C_0050D440 CreateObject;      // +0x008C
    char _pad090[0xF8 - 0x90];       // +0x0090
    FnF8_0050D440 At_F8;             // +0x00F8
    char _pad0FC[0x490 - 0xFC];      // +0x00FC
    Fn490_0050D440 At_490;           // +0x0490
};
GG_STATIC_ASSERT(offsetof(AbsVtbl_0050D440, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(AbsVtbl_0050D440, GetCoords) == 0x48);
GG_STATIC_ASSERT(offsetof(AbsVtbl_0050D440, CreateObject) == 0x8C);
GG_STATIC_ASSERT(offsetof(AbsVtbl_0050D440, At_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(AbsVtbl_0050D440, At_490) == 0x490);

// The map singleton is a static object at 0x87F7E8 (`MOV ECX,0x87F7E8`).
struct Map_0050D440
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    Abs_0050D440* GetCellAt(const CellStruct_0050D440& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_0050D440 MapInstance;

// One starting-force record: the type and the cell it is placed on.
struct StartingTechno_0050D440
{
    Abs_0050D440*        Type;   // +0x0000
    CellStruct_0050D440  Cell;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(StartingTechno_0050D440, Cell) == 0x4);

// DynamicVectorClass<StartingTechnoStruct*> — only Items and Count are read.
struct StartingVector_0050D440
{
    void*                      Vtable;       // +0x0000
    StartingTechno_0050D440**  Items;        // +0x0004
    char                       _pad008[0x8]; // +0x0008
    int                        Count;        // +0x0010
};
GG_STATIC_ASSERT(offsetof(StartingVector_0050D440, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(StartingVector_0050D440, Count) == 0x10);

// HouseClass (partial).
struct House_0050D440
{
    char _pad000[0x16C];                    // +0x0000
    StartingVector_0050D440 StartingUnits;  // +0x016C  (Items +0x170, Count +0x17C)

    // FUNCTION: GAMEMD 0x50D440 — HouseClass::RespawnStartingForces.
    void RespawnStartingForces();
};
GG_STATIC_ASSERT(offsetof(House_0050D440, StartingUnits) == 0x16C);
GG_STATIC_ASSERT(offsetof(House_0050D440, StartingUnits.Items) == 0x170);
GG_STATIC_ASSERT(offsetof(House_0050D440, StartingUnits.Count) == 0x17C);

#endif  // GG_MATCH_AI_HOUSE_CLASS_RESPAWN_METHODS_H
