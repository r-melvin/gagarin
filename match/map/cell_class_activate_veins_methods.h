// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x486920: the cell's OverlayTypeIndex `[EBX+0x44]`
//   (0x7E = veins), OverlayData `[EBX+0x11E]` (at least 0x30), SlopeIndex
//   `[EBX+0x11C]`, the flag word `[EBX+0x140]` bit 0x20000, MapCoords
//   `[EBX+0x24]` and the occupier list `[EBX+0xE4]` threaded through
//   `[ESI+0x30]`; on each occupier the height slot `[EAX+0x1C8]`, the
//   AbstractClass flag byte `[ESI+0x14]` bit 0, the type slot `[EDX+0x84]`
//   and the type's byte at `+0xC91`, plus the ability probe 0x70D0D0 with
//   8 pushed; the 0x1C8-byte animation from `operator new` 0x7C8E17 built
//   by 0x421EA0 with the rules animation at `[0x8871E0]+0xE8`; and the
//   cell's own height query 0x47B3A0 taking a sub-cell offset. Offsets
//   agree with match/map/cell_class_fog_methods.h (Flags 0x140) and
//   match/map/cell_class_wall_owner_methods.h (OverlayTypeIndex 0x44).
//   Names cross-checked against YRpp CellClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00486920
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_00486920) == 0xC);

// The sub-cell offset the height query is asked about.
struct Offset_00486920
{
    int X;   // +0x0000
    int Y;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Offset_00486920) == 8);

// The cell's map coordinate pair, copied whole into a local before use.
struct MapCoord_00486920
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(MapCoord_00486920) == 4);

struct TechnoType_00486920
{
    char _pad000[0xC91];   // +0x0000
    char At_C91;           // +0x0C91
};
GG_STATIC_ASSERT(offsetof(TechnoType_00486920, At_C91) == 0xC91);

struct ObjVtbl_00486920;

struct Obj_00486920
{
    ObjVtbl_00486920* Vptr;           // +0x0000
    char              _pad004[0x10];  // +0x0004
    unsigned char     AbstractFlags;  // +0x0014  bit 0 = TechnoClass
    char              _pad015[0x1B];  // +0x0015
    Obj_00486920*     NextObject;     // +0x0030

    // FUNCTION: GAMEMD 0x70D0D0 (decl; reloc) — does this object have the
    // given ability.
    bool FUN_0070D0D0(int ability);
};
GG_STATIC_ASSERT(offsetof(Obj_00486920, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00486920, NextObject)    == 0x30);

typedef TechnoType_00486920* (Obj_00486920::*Fn84_00486920)();
typedef int (Obj_00486920::*Fn1C8_00486920)();
struct ObjVtbl_00486920
{
    char            _pad000[0x84];          // +0x0000
    Fn84_00486920   GetTechnoType;          // +0x0084
    char            _pad088[0x1C8 - 0x88];  // +0x0088
    Fn1C8_00486920  GetHeight;              // +0x01C8
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486920, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486920, GetHeight)     == 0x1C8);

// The animation type the vein activation plays.
struct AnimType_00486920;
struct Rules_00486920
{
    char                _pad000[0xE8];   // +0x0000
    AnimType_00486920*  At_E8;           // +0x00E8
};
GG_STATIC_ASSERT(offsetof(Rules_00486920, At_E8) == 0xE8);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00486920* DAT_008871E0;

// The animation object: 0x1C8 bytes from operator new, then constructed.
struct Anim_00486920
{
    char opaque[0x1C8];

    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc) — AnimClass::AnimClass.
    void Construct(AnimType_00486920* type, Coord_00486920* coord, int a3,
                   int a4, int a5, int a6, char a7);
};
GG_STATIC_ASSERT(sizeof(Anim_00486920) == 0x1C8);

struct Cell_00486920
{
    char            _pad000[0x24];           // +0x0000
    MapCoord_00486920 MapCoords;             // +0x0024
    char            _pad028[0x44 - 0x28];    // +0x0028
    int             OverlayTypeIndex;        // +0x0044
    char            _pad048[0xE4 - 0x48];    // +0x0048
    Obj_00486920*   FirstObject;             // +0x00E4
    char            _pad0E8[0x11C - 0xE8];   // +0x00E8
    char            SlopeIndex;              // +0x011C
    char            _pad11D;                 // +0x011D
    unsigned char   OverlayData;             // +0x011E
    char            _pad11F[0x140 - 0x11F];  // +0x011F
    unsigned int    Flags;                   // +0x0140

    // FUNCTION: GAMEMD 0x47B3A0 (decl; reloc) — the floor height at a
    // sub-cell offset.
    int FUN_0047B3A0(Offset_00486920* offset);

    // The cell's own world coordinate: the centre of the cell, with the
    // floor height asked for at that same sub-cell offset. Expanded inline
    // at the one call site.
    Coord_00486920 GetCoords();
    Coord_00486920 GetCornerCoords();

    // FUNCTION: GAMEMD 0x486920 — CellClass::ActivateVeins.
    void ActivateVeins();
};
GG_STATIC_ASSERT(offsetof(Cell_00486920, MapCoords)        == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_00486920, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_00486920, FirstObject)      == 0xE4);
GG_STATIC_ASSERT(offsetof(Cell_00486920, SlopeIndex)       == 0x11C);
GG_STATIC_ASSERT(offsetof(Cell_00486920, OverlayData)      == 0x11E);
GG_STATIC_ASSERT(offsetof(Cell_00486920, Flags)            == 0x140);

// The cell's corner coordinate: the centre with the half-cell offset taken
// back off each axis, which is how retail spells it.
inline Coord_00486920 Cell_00486920::GetCornerCoords()
{
    Coord_00486920 centre = GetCoords();
    Coord_00486920 corner;
    corner.X = centre.X - 0x80;
    corner.Y = centre.Y - 0x80;
    corner.Z = centre.Z;
    return corner;
}

inline Coord_00486920 Cell_00486920::GetCoords()
{
    MapCoord_00486920 cell = MapCoords;

    Coord_00486920 coord;
    coord.X = cell.X * 256 + 0x80;
    coord.Y = cell.Y * 256 + 0x80;

    Offset_00486920 offset;
    offset.X = 0x80;
    offset.Y = 0x80;

    coord.Z = FUN_0047B3A0(&offset);
    return coord;
}

#endif  // GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H
