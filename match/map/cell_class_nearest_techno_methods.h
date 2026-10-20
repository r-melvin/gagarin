// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x47C3D0: the two occupier list heads `[ECX+0xE4]` /
//   `[ECX+0xE8]` (FirstObject / AltObject), the list link `[ESI+0x30]`
//   (ObjectClass::NextObject), the AbstractClass flag byte `[ESI+0x14]` bit 0
//   (techno), the hidden-pointer GetCoords slot `[EDX+0x48]`, sqrt via
//   0x4CAC40 and __ftol 0x7C5F00. The method name is YRpp's
//   CellClass::FindTechnoNearestTo (name only; every offset re-derived here).
#ifndef GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — square root, __cdecl.
double __cdecl FUN_004CAC40(double value);

// Pixel offset within the cell (two ints).
struct Point_0047C3D0
{
    int X;   // +0x0000
    int Y;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point_0047C3D0) == 0x8);

// CoordStruct returned by value through the hidden-pointer convention: the
// user-declared constructor is what selects that convention (see the banked
// "Struct returns" rule).
struct Coord_0047C3D0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
    Coord_0047C3D0() {}
};
GG_STATIC_ASSERT(sizeof(Coord_0047C3D0) == 0xC);

struct Vtbl_0047C3D0;

// ObjectClass as seen from this method: the flag byte at +0x14 and the
// occupier-list link at +0x30.
struct Obj_0047C3D0
{
    Vtbl_0047C3D0* Vptr;             // +0x0000
    char           _pad004[0x10];    // +0x0004
    char           AbstractFlags;    // +0x0014  bit 0 = TechnoClass
    char           _pad015[0x1B];    // +0x0015
    Obj_0047C3D0*  NextObject;       // +0x0030
};
GG_STATIC_ASSERT(offsetof(Obj_0047C3D0, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0047C3D0, NextObject)    == 0x30);

typedef Coord_0047C3D0 (Obj_0047C3D0::*Fn48_0047C3D0)();

struct Vtbl_0047C3D0
{
    char           _pad000[0x48];   // +0x0000
    Fn48_0047C3D0  GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(Vtbl_0047C3D0, GetCoords) == 0x48);

// CellClass — only the two occupier list heads are read.
struct Cell_0047C3D0
{
    char           _pad000[0xE4];   // +0x0000
    Obj_0047C3D0*  FirstObject;     // +0x00E4
    Obj_0047C3D0*  AltObject;       // +0x00E8

    // FUNCTION: GAMEMD 0x47C3D0 — CellClass::FindTechnoNearestTo.
    Obj_0047C3D0* FindTechnoNearestTo(Point_0047C3D0* offset, bool alt,
                                      Obj_0047C3D0* exclude);
};
GG_STATIC_ASSERT(offsetof(Cell_0047C3D0, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(Cell_0047C3D0, AltObject)   == 0xE8);

#endif  // GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H
