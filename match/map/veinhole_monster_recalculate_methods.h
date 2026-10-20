// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x74E930: `LEA
//   EBP,[ECX+0xF8]` (the monster's cell coordinate, pushed by address into
//   `MOV ECX,0x87F7E8; CALL 0x5657A0`, MapClass::GetCellAt), the cell's
//   `[ESI+0x44] = 0x7E` / `-1` (overlay type index) and byte `[ESI+0x11E] =
//   0` (overlay data), `PUSH -1; CALL 0x47D2B0` (RecalcAttributes), `PUSH i;
//   CALL 0x481810` (GetNeighbourCell) over eight facings with the signed
//   `i % 2` test, the 5x5 walk building `{X+dx, Y+dy}` as two words at
//   `[ESP+0x10]`, copying the dword to `[ESP+0x14]` and pushing that address
//   (the inlined by-value helper plus the const-ref temporary, the same shape
//   as the matched 0x481810), CALL 0x485AF0 on each cell, `CALL 0x74E6B0` on
//   `this`, `PUSH EBP; MOV ECX,0x87F7E8; CALL 0x56D460` and `CALL 0x584550`,
//   and the byte `[ESI+0x100] = 1`. YRpp names only (consult-only, no
//   LICENSE): VeinholeMonsterClass::Recalculate, RecalculateSpread
//   @0x74E6B0, CellClass::RecalcAttributes @0x47D2B0, GetNeighbourCell
//   @0x481810, MapClass::GetCellAt @0x5657A0, ResetZones @0x56D460,
//   RecalculateSubZones @0x584550.
#ifndef GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4).
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Displace a cell coordinate; returned by value so the caller binds a
// const-ref temporary to the copy, exactly as retail's frame shows.
static inline CellStruct CellOffset(CellStruct const& c, int dx, int dy)
{
    CellStruct ret;
    ret.X = c.X + dx;
    ret.Y = c.Y + dy;
    return ret;
}

// CellClass view: the overlay type index and overlay data byte.
struct Cell_0074E930
{
    char _pad000[0x44];            // +0x0000
    int  OverlayTypeIndex;         // +0x0044
    char _pad048[0x11E - 0x48];    // +0x0048
    char OverlayData;              // +0x011E

    // FUNCTION: GAMEMD 0x47D2B0 (decl; reloc) — CellClass::RecalcAttributes.
    void RecalcAttributes(int level);
    // FUNCTION: GAMEMD 0x481810 (decl; reloc) — CellClass::GetNeighbourCell.
    Cell_0074E930* GetNeighbourCell(int facing);
    // FUNCTION: GAMEMD 0x485AF0 (decl; reloc)
    void FUN_00485AF0();
};
GG_STATIC_ASSERT(offsetof(Cell_0074E930, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_0074E930, OverlayData)      == 0x11E);

// The static map object at 0x87F7E8.
struct Map_0074E930
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    Cell_0074E930* GetCellAt(CellStruct const& cell);
    // FUNCTION: GAMEMD 0x56D460 (decl; reloc) — MapClass::ResetZones.
    void ResetZones(CellStruct const& cell);
    // FUNCTION: GAMEMD 0x584550 (decl; reloc) — MapClass::RecalculateSubZones.
    void RecalculateSubZones(CellStruct const& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_0074E930 MapInstance;

struct VeinholeMonsterClass
{
    char       _pad000[0xF8];      // +0x0000
    CellStruct Cell;               // +0x00F8
    char       _padFC[4];          // +0x00FC
    char       At_100;             // +0x0100

    // FUNCTION: GAMEMD 0x74E6B0 (decl; reloc) — RecalculateSpread.
    void RecalculateSpread();

    // FUNCTION: GAMEMD 0x74E930
    void Recalculate();
};
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, Cell)   == 0xF8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, At_100) == 0x100);

#endif  // GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H
