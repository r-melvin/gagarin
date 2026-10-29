// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Small value types shared by every cluster of the house/building module (BuildingClass, HouseClass,
//   HouseTypeClass, BuildingTypeClass). Each is declared once, here, with the union of the members,
//   constructors and read-only helpers the module's bodies use. Layouts were read from the retail
//   gamemd.exe v1.001.
//
// Naming: the clusters were first recovered independently under BA* / BA2* / BA3* / BA4* / BuildingB* /
// House* / Types* prefixes. Everything they share lives under the HB* prefix. Types that are NOT merged
// (because merging them changes the generated code) stay in the cluster headers with a comment saying why.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_COMMON_TYPES_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_COMMON_TYPES_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../../_layout/cell.h"

// No-init constructor tag: Load re-runs the constructor through placement new to restore the vptrs
// without touching any other member.
struct HBNoInit {};

// A world coordinate (three leptons). The empty constructor matters: it makes a by-value return go
// through the caller's buffer exactly as retail's does.
struct HBCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    HBCoord() {}
    HBCoord(int x, int y, int z) : X(x), Y(y), Z(z) {}

    // FUNCTION: GAMEMD 0x41C230 (read-only here) - builds the coordinate in place, returns it.
    HBCoord* FUN_0041C230(int x, int y, int z);
    // FUNCTION: GAMEMD 0x41C380 (read-only here) - the length of the vector.
    int FUN_0041C380();
    // FUNCTION: GAMEMD 0x459F60 (read-only here; the body is the next function after building-b's range)
    bool Func_459F60(const HBCoord* other);
};
GG_STATIC_ASSERT(sizeof(HBCoord) == 0xC);

// The same coordinate WITHOUT constructors (a POD). Kept separate on purpose: building-a4's bodies were
// recovered against a constructor-less coordinate, and giving them HBCoord's empty constructor changes
// their code (measured: 0x43F180 drops from 10.3% to 8.8%).
struct HBCoordPod
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    // FUNCTION: GAMEMD 0x41C230 (read-only here) - builds the coordinate in place, returns it.
    HBCoordPod* FUN_0041C230(int x, int y, int z);
    // FUNCTION: GAMEMD 0x41C380 (read-only here) - the length of the vector.
    int FUN_0041C380();
};
GG_STATIC_ASSERT(sizeof(HBCoordPod) == 0xC);

// A map cell coordinate (two 16-bit halves). The user constructors make it a non-POD, so a by-value
// return goes through a hidden pointer as retail's does.
struct HBCell
{
    short X;   // +0x00
    short Y;   // +0x02

    HBCell() {}
    HBCell(short x, short y) : X(x), Y(y) {}

    HBCell operator+(const HBCell& o) const
    {
        HBCell r;
        r.X = (short)(X + o.X);
        r.Y = (short)(Y + o.Y);
        return r;
    }
    // The same sum with a plain cell (the facing step table at 0x89F688).
    HBCell operator+(const CellStruct& o) const
    {
        HBCell r;
        r.X = (short)(X + o.X);
        r.Y = (short)(Y + o.Y);
        return r;
    }
    HBCell operator-() const
    {
        HBCell r;
        r.X = -X;
        r.Y = -Y;
        return r;
    }

    // FUNCTION: GAMEMD 0x42D470 (read-only here) - builds a cell from two shorts, returns it.
    HBCell* FUN_0042D470(short x, short y);
    // FUNCTION: GAMEMD 0x42D510 (read-only here) - the sum of this offset and a cell, returned by value.
    HBCell FUN_0042D510(const HBCell& base) const;
    // FUNCTION: GAMEMD 0x453240 (read-only here)
    void FUN_00453240();
    // FUNCTION: GAMEMD 0x660B80 (read-only here)
    void FUN_00660B80();
};
GG_STATIC_ASSERT(sizeof(HBCell) == 4);

// A pair of ints: an x/y offset, a map-coordinate pair or a screen point. POD (no constructors).
struct HBPoint2D
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(HBPoint2D) == 8);

// A rectangle (x, y, width, height).
struct HBRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(HBRect) == 0x10);

// A facing value: a signed 16-bit direction in the low half of a dword (the whole dword is copied).
// building-a2's facing (BA2Dir) reads the half as UNSIGNED and stays separate: the signedness picks
// MOVZX against MOVSX in the generated code.
struct HBDir
{
    union {
        unsigned int Whole;   // +0x00
        short Raw;            // +0x00
    };
    HBDir() {}
    // Constructed from the raw 16-bit value ...
    HBDir(short raw) { Raw = raw; }
    // ... from an 8-bit direction (the high byte of the 16-bit value) ...
    HBDir(unsigned char dir8) { Raw = (short)(dir8 << 8); }
    // ... or from a 5-bit direction (the top five bits).
    HBDir(unsigned short dir5) { Raw = (short)((dir5 & 0x1F) << 11); }
};
GG_STATIC_ASSERT(sizeof(HBDir) == 4);

#endif
