// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below; REA ev_cd24287207db30224cd75bcda1775e47aedcb3e41b00c6e3b676e4539cf64578.
//
// The map's cell pack readers. Each reads (cell coordinate, tile index, height, level) records from a straw
// until the coordinate equals the "no cell" marker; a record for a missing cell (or the invalid cell) is
// skipped by reading and discarding its payload. The invalid cell is rebuilt at the end.
//
// Address index: 0x56B5A0 0x56B780 0x56B8A0 0x56B9A0 0x56BAC0

#include <new.h>
#include "_layout/cell_class.h"
#include "_layout/straw.h"
#include "compression_straws.h"
#include "ui_display_chain.h"

// GLOBAL: GAMEMD 0xABDC50 -- the cell returned for an out-of-range lookup.
extern CellClass DAT_00ABDC50;
// GLOBAL: GAMEMD 0xABDC74 -- the coordinate that failed the last lookup.
extern CellStruct DAT_00ABDC74;
// GLOBAL: GAMEMD 0xABD480 -- the "no cell" coordinate.
extern CellStruct DAT_00ABD480;

// FUNCTION: GAMEMD 0x544E30 (decl; reloc) -- maps a stored tile index to the loaded tile set's index.
extern int __fastcall FUN_00544E30(int index);

// FUNCTION: GAMEMD 0x56B5A0
bool MapClass::FUN_0056B5A0(Straw* straw)
{
    int i;
    LCWStraw reader(LCWStraw::DECOMPRESS, 0x2000);
    reader.SetChainTo(straw);
    for (i = 0; i < 0x4000; ++i) {
        CellStruct coord;
        coord.X = i % 128;
        coord.Y = i / 128;
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell) {
            cell->IsoTileTypeIndex = 0xFFFF;
            reader.FUN_006C98E0(&cell->IsoTileTypeIndex, 2);
            cell->IsoTileTypeIndex = FUN_00544E30(cell->IsoTileTypeIndex);
        } else {
            reader.FUN_006C98E0(&DAT_00ABDC50.IsoTileTypeIndex, 2);
        }
    }
    for (i = 0; i < 0x4000; ++i) {
        CellStruct coord;
        coord.X = i % 128;
        coord.Y = i / 128;
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell)
            reader.FUN_006C98E0(&cell->Height, 1);
        else
            reader.FUN_006C98E0(&DAT_00ABDC50.Height, 1);
    }
    for (i = 0; i < 0x4000; ++i) {
        CellStruct coord;
        coord.X = i % 128;
        coord.Y = i / 128;
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell)
            reader.FUN_006C98E0(&cell->Level, 1);
        else
            reader.FUN_006C98E0(&DAT_00ABDC50.Level, 1);
    }
    new (&DAT_00ABDC50) CellClass;
    return true;
}

// FUNCTION: GAMEMD 0x56B780
bool MapClass::FUN_0056B780(Straw* straw)
{
    LCWStraw reader(LCWStraw::DECOMPRESS, 0x2000);
    reader.SetChainTo(straw);
    CellStruct coord;
    char skipped[8];
    reader.FUN_006C98E0(&coord, 4);
    while (coord.X != DAT_00ABD480.X || coord.Y != DAT_00ABD480.Y) {
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell == 0 || cell == &DAT_00ABDC50) {
            reader.FUN_006C98E0(skipped, 6);
        } else {
            cell->IsoTileTypeIndex = 0xFFFF;
            reader.FUN_006C98E0(&cell->IsoTileTypeIndex, 4);
            cell->IsoTileTypeIndex = FUN_00544E30(cell->IsoTileTypeIndex);
            reader.FUN_006C98E0(&cell->Height, 1);
            reader.FUN_006C98E0(&cell->Level, 1);
        }
        coord = DAT_00ABD480;
        reader.FUN_006C98E0(&coord, 4);
    }
    new (&DAT_00ABDC50) CellClass;
    return true;
}

// FUNCTION: GAMEMD 0x56B8A0
bool MapClass::FUN_0056B8A0(Straw* straw)
{
    CellStruct coord;
    char skipped[6];
    straw->FUN_006C98E0(&coord, 4);
    while (coord.X != DAT_00ABD480.X || coord.Y != DAT_00ABD480.Y) {
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell == 0 || cell == &DAT_00ABDC50) {
            straw->FUN_006C98E0(skipped, 6);
        } else {
            cell->IsoTileTypeIndex = 0xFFFF;
            straw->FUN_006C98E0(&cell->IsoTileTypeIndex, 4);
            cell->IsoTileTypeIndex = FUN_00544E30(cell->IsoTileTypeIndex);
            straw->FUN_006C98E0(&cell->Height, 1);
            straw->FUN_006C98E0(&cell->Level, 1);
        }
        coord = DAT_00ABD480;
        straw->FUN_006C98E0(&coord, 4);
    }
    new (&DAT_00ABDC50) CellClass;
    return true;
}

// FUNCTION: GAMEMD 0x56B9A0
bool MapClass::FUN_0056B9A0(Straw* straw)
{
    LZOStraw reader(LZOStraw::DECOMPRESS, 0x2000);
    reader.SetChainTo(straw);
    CellStruct coord;
    char skipped[8];
    reader.FUN_006C98E0(&coord, 4);
    while (coord.X != DAT_00ABD480.X || coord.Y != DAT_00ABD480.Y) {
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell == 0 || cell == &DAT_00ABDC50) {
            reader.FUN_006C98E0(skipped, 6);
        } else {
            cell->IsoTileTypeIndex = 0xFFFF;
            reader.FUN_006C98E0(&cell->IsoTileTypeIndex, 4);
            cell->IsoTileTypeIndex = FUN_00544E30(cell->IsoTileTypeIndex);
            reader.FUN_006C98E0(&cell->Height, 1);
            reader.FUN_006C98E0(&cell->Level, 1);
        }
        coord = DAT_00ABD480;
        reader.FUN_006C98E0(&coord, 4);
    }
    new (&DAT_00ABDC50) CellClass;
    return true;
}

// FUNCTION: GAMEMD 0x56BAC0
bool MapClass::FUN_0056BAC0(Straw* straw)
{
    LZOStraw reader(LZOStraw::DECOMPRESS, 0x2000);
    reader.SetChainTo(straw);
    CellStruct coord;
    char skipped[8];
    reader.FUN_006C98E0(&coord, 4);
    while (coord.X != DAT_00ABD480.X || coord.Y != DAT_00ABD480.Y) {
        CellClass* cell;
        int idx = (coord.Y << 9) + coord.X;
        if (idx >= 0 && idx < 0x40000 && Owned.Items[idx] != 0) {
            cell = Owned.Items[idx];
        } else {
            DAT_00ABDC74 = coord;
            cell = &DAT_00ABDC50;
        }
        if (cell == 0 || cell == &DAT_00ABDC50) {
            reader.FUN_006C98E0(skipped, 7);
        } else {
            cell->IsoTileTypeIndex = 0xFFFF;
            reader.FUN_006C98E0(&cell->IsoTileTypeIndex, 4);
            cell->IsoTileTypeIndex = FUN_00544E30(cell->IsoTileTypeIndex);
            reader.FUN_006C98E0(&cell->Height, 1);
            reader.FUN_006C98E0(&cell->Level, 1);
            reader.FUN_006C98E0(&cell->IsIceGrowthAllowed, 1);
        }
        coord = DAT_00ABD480;
        reader.FUN_006C98E0(&coord, 4);
    }
    new (&DAT_00ABDC50) CellClass;
    return true;
}
