// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x486C50: `[EBX+0x28]` (the cell's fogged-object
//   vector, re-read every iteration and finally zeroed), the vector's
//   `[EAX+0x4]` Items / `[EAX+0x10]` Count and its slots `[EDX+0x0]`
//   (scalar-deleting destructor, PUSH 1), `[EDX+0xC]` (Clear, no args) and
//   `[EDX+0x10]` (index-of, address of the element pushed), the fogged
//   object's `ADD EDX,0x34` coordinate triple and its `[EAX+0x20]` scalar
//   deleting destructor, and the 0x7FFF/0x7FFF sentinel pair walked two
//   shorts at a time out of 0x4D2790. The cell coordinate is the inlined
//   signed divide by 256 (`CDQ; AND EDX,0xFF; ADD; SAR 8`) and the
//   MapClass::GetCellAt receiver is the fixed instance `MOV ECX,0x87F7E8`.
//   CellClass::ClearFoggedObjects and MapClass::GetCellAt are YRpp names;
//   every offset is reconfirmed here.
#ifndef GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_00486C50  { short X; short Y; };
struct Coord_00486C50 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Cell_00486C50)  == 4);
GG_STATIC_ASSERT(sizeof(Coord_00486C50) == 0xC);

struct ObjVtbl_00486C50;

// One fogged-object record held by a cell.
struct Obj_00486C50
{
    ObjVtbl_00486C50* Vptr;                  // +0x0000
    char              _pad0004[0x34 - 4];    // +0x0004
    Coord_00486C50    Location;              // +0x0034
};
GG_STATIC_ASSERT(offsetof(Obj_00486C50, Location) == 0x34);

typedef void (Obj_00486C50::*Fn20_00486C50)(int freeFlag);

struct ObjVtbl_00486C50
{
    char _pad000[0x20];          // +0x0000
    Fn20_00486C50 At_20;         // +0x0020  scalar deleting destructor
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486C50, At_20) == 0x20);

// FUNCTION: GAMEMD 0x4D2790 (decl; reloc) -- the record's occupy list, or 0.
short* FUN_004D2790(Obj_00486C50* object);

struct VecVtbl_00486C50;

// The per-cell DynamicVectorClass of fogged objects.
struct Vec_00486C50
{
    VecVtbl_00486C50* Vptr;                   // +0x0000
    Obj_00486C50**    Items;                  // +0x0004
    char              _pad0008[0x10 - 8];     // +0x0008
    int               Count;                  // +0x0010
};
GG_STATIC_ASSERT(offsetof(Vec_00486C50, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(Vec_00486C50, Count) == 0x10);

typedef void (Vec_00486C50::*Fn00V_00486C50)(int freeFlag);
typedef void (Vec_00486C50::*Fn0CV_00486C50)();
typedef int  (Vec_00486C50::*Fn10V_00486C50)(Obj_00486C50* const& item);

struct VecVtbl_00486C50
{
    Fn00V_00486C50 At_00;        // +0x0000  scalar deleting destructor
    char _pad004[0xC - 4];       // +0x0004
    Fn0CV_00486C50 Clear;        // +0x000C
    Fn10V_00486C50 IndexOf;      // +0x0010
};
GG_STATIC_ASSERT(offsetof(VecVtbl_00486C50, Clear)   == 0xC);
GG_STATIC_ASSERT(offsetof(VecVtbl_00486C50, IndexOf) == 0x10);

struct CellFog_00486C50
{
    char          _pad0000[0x28];    // +0x0000
    Vec_00486C50* FoggedObjects;     // +0x0028

    // FUNCTION: GAMEMD 0x486C50 -- CellClass::ClearFoggedObjects.
    void ClearFoggedObjects();
};
GG_STATIC_ASSERT(offsetof(CellFog_00486C50, FoggedObjects) == 0x28);

struct Map_00486C50
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    CellFog_00486C50* GetCellAt(const Cell_00486C50& cell);
};

// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance (used by address, ECX).
extern Map_00486C50 DAT_0087F7E8;

#endif  // GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H
