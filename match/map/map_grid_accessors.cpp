// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 with the local Ghidra CLI at each address.
//   Per-cell accessors of the 0x50-byte record grid at 0xABED10 that the MapGen.cpp
//   unit (0x58B530-0x5ADB1F) keeps: the record for a cell is
//   DAT_00ABED10[cell.Y * DAT_0089C2DC + cell.X], and the cell is passed as a pointer
//   to its two 16-bit coordinates (this pointer or first argument). Names are
//   address placeholders.
#include "MapGen.h"

// A cell coordinate pair viewed as the receiver of the grid accessors.
struct GridCell
{
    short X;
    short Y;

    // FUNCTION: GAMEMD 0x58C1C0
    int FUN_0058C1C0() const;
    // FUNCTION: GAMEMD 0x58C1F0
    unsigned char FUN_0058C1F0() const;
    // FUNCTION: GAMEMD 0x58C240
    void FUN_0058C240() const;
    // FUNCTION: GAMEMD 0x58C2A0
    Rec_50* FUN_0058C2A0() const;
    // FUNCTION: GAMEMD 0x58D0A0
    int FUN_0058D0A0() const;
};
GG_STATIC_ASSERT(sizeof(GridCell) == 4);

#define GRID_REC(cell) (DAT_00ABED10[(cell).Y * DAT_0089C2DC + (cell).X])

// FUNCTION: GAMEMD 0x58C1C0
// True when the cell's flag byte at +0x45 is clear.
int GridCell::FUN_0058C1C0() const
{
    return GRID_REC(*this).unknown_45 == 0;
}

// FUNCTION: GAMEMD 0x58C1F0
// The cell record's byte at +0x44.
unsigned char GridCell::FUN_0058C1F0() const
{
    return GRID_REC(*this).unknown_44;
}

// FUNCTION: GAMEMD 0x58C240
// Clear the cell record's flag byte at +0x45.
void GridCell::FUN_0058C240() const
{
    GRID_REC(*this).unknown_45 = 0;
}

// FUNCTION: GAMEMD 0x58C2A0
// The record of this cell.
Rec_50* GridCell::FUN_0058C2A0() const
{
    return &GRID_REC(*this);
}

// FUNCTION: GAMEMD 0x58C2C0
// The record at a linear index.
Rec_50* __fastcall FUN_0058C2C0(int index)
{
    return &DAT_00ABED10[index];
}

// FUNCTION: GAMEMD 0x58D0A0
// The record's +0x38 field, or -1 before the grid exists.
int GridCell::FUN_0058D0A0() const
{
    if (DAT_00ABED10 == 0) {
        return -1;
    }
    return GRID_REC(*this).unknown_38;
}

// FUNCTION: GAMEMD 0x58C270
// Clear the flag byte at +0x45 of every record. Retail indexes the one-past-the-end
// record on every pass (the loop variable is not used in the subscript).
void FUN_0058C270()
{
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        DAT_00ABED10[n].unknown_45 = 0;
    }
}

// FUNCTION: GAMEMD 0x58C6C0
// Reset the +0x3C field of every record to -1.
void FUN_0058C6C0()
{
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        DAT_00ABED10[i].unknown_3C = -1;
    }
}

// FUNCTION: GAMEMD 0x58D070
// Store the +0x38 field of the cell's record, once the grid exists.
void FUN_0058D070(const GridCell* cell, int value)
{
    if (DAT_00ABED10 != 0) {
        GRID_REC(*cell).unknown_38 = value;
    }
}

// FUNCTION: GAMEMD 0x58D0D0
// Store the +0x3C field of the cell's record.
void FUN_0058D0D0(const GridCell* cell, int value)
{
    GRID_REC(*cell).unknown_3C = value;
}

// FUNCTION: GAMEMD 0x58D100
// The +0x3C field of the cell's record.
int FUN_0058D100(const GridCell* cell)
{
    return GRID_REC(*cell).unknown_3C;
}

// FUNCTION: GAMEMD 0x5A0090
// Store the +0x38 field of the cell's record, once the grid exists.
void __stdcall FUN_005A0090(const GridCell* cell, int value)
{
    if (DAT_00ABED10 != 0) {
        GRID_REC(*cell).unknown_38 = value;
    }
}

// FUNCTION: GAMEMD 0x5A00C0
// The +0x38 field of the cell's record, or -1 before the grid exists.
int __stdcall FUN_005A00C0(const GridCell* cell)
{
    if (DAT_00ABED10 == 0) {
        return -1;
    }
    return GRID_REC(*cell).unknown_38;
}

// FUNCTION: GAMEMD 0x5A0100
// Store the +0x3C field of the cell's record.
void __stdcall FUN_005A0100(const GridCell* cell, int value)
{
    GRID_REC(*cell).unknown_3C = value;
}

// FUNCTION: GAMEMD 0x5A0130
// The +0x3C field of the cell's record.
int __stdcall FUN_005A0130(const GridCell* cell)
{
    return GRID_REC(*cell).unknown_3C;
}
