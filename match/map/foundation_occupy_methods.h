// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x456580: the cell list's count is `[EBX+0x10]` and its
//   items `[EBX+4]`, indexed with an 8-byte stride (`[ECX+EDI*8]` for the first
//   dword and `[ECX+EDI*8+4]` for the second), and the object's own pair sits at
//   +0x208/+0x20C.
#ifndef GG_MATCH_MAP_FOUNDATION_OCCUPY_METHODS_H
#define GG_MATCH_MAP_FOUNDATION_OCCUPY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x456580 -> BuildingClass slot 293 (byte-off 0x494).
// No other table in the image holds it, so the slot is declared on
// BuildingClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct BuildingClass_00456580;

// An 8-byte cell offset, applied to the object's own position.
struct Offset_00456580
{
    int X;      // +0x0000
    int Y;      // +0x0004
};
GG_STATIC_ASSERT(sizeof(Offset_00456580) == 8);

struct CellList_00456580
{
    char _pad000[0x4];          // +0x0000
    Offset_00456580* Items;     // +0x0004
    char _pad008[0x8];          // +0x0008
    int  Count;                 // +0x0010
};
GG_STATIC_ASSERT(offsetof(CellList_00456580, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(CellList_00456580, Count) == 0x10);

// The map registry the two calls go through, passed in ECX as an immediate
// address — a singleton object, not a pointer read from memory.
struct Registry_00456580
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x656580 — the cell list for a foundation id.
    CellList_00456580* FUN_00656580(int foundation);
    // FUNCTION: GAMEMD 0x655560 — mark one cell as occupied by the object.
    void FUN_00655560(BuildingClass_00456580* object, int x, int y);
};
// GLOBAL: GAMEMD 0x87F7E8
extern Registry_00456580 DAT_0087F7E8;

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x456580 -> BuildingClass slot 293 (byte-off 0x494).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00456580
{
    char _pad000[0x208];        // +0x0000
    int  X;                     // +0x0208
    int  Y;                     // +0x020C
    char _pad210[0x213];        // +0x0210
    char At_423;                // +0x0423
    char _pad424[0xFC];         // +0x0424
    int  Foundation;            // +0x0520

    // FUNCTION: GAMEMD 0x456580
    void FUN_00456580();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00456580, X) == 0x208);
GG_STATIC_ASSERT(offsetof(BuildingClass_00456580, At_423) == 0x423);
GG_STATIC_ASSERT(offsetof(BuildingClass_00456580, Foundation) == 0x520);

#endif  // GG_MATCH_MAP_FOUNDATION_OCCUPY_METHODS_H
