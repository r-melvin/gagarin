// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   GeneralStructures.h `struct BasePlanningCellContainer` (consult-only; no
//   LICENSE; every offset reconfirmed numerically from the disasm below).
//
// BasePlanningCellContainer — a growable array of weighted base-planning cells
// used by the AI base layout routines. Element = BasePlanningCell (8 bytes:
// int Weight + Vector2D<short> Position).
#ifndef GG_MATCH_CORE_GENERAL_STRUCTURES_H
#define GG_MATCH_CORE_GENERAL_STRUCTURES_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Vector2D<short> — cell coordinate pair (used as BasePlanningCell::Position).
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02
};

// BasePlanningCell (sizeof = 0x08). In AddCapacity the copy loop moves each
// element as two dwords ([EDX] -> Weight, [EDX+4] -> Position), confirming the
// 8-byte element stride (LEA [EBX*8]).
struct BasePlanningCell
{
    int        Weight;    // +0x00
    CellStruct Position;  // +0x04
};

GG_STATIC_ASSERT(offsetof(BasePlanningCell, Weight) == 0x00);
GG_STATIC_ASSERT(offsetof(BasePlanningCell, Position) == 0x04);
GG_STATIC_ASSERT(sizeof(BasePlanningCell) == 0x08);

// ---------------------------------------------------------------------------
// BasePlanningCellContainer  (sizeof = 0x14)
//
// Confirmed from 0x510860 (AddCapacity):
//   [ESI]      Items     (BasePlanningCell*)  MOV EBX,[ESI]
//   [ESI+0x4]  Count     (int)                MOV EAX,[ESI+0x4]
//   [ESI+0x8]  Capacity  (int)                MOV EBX,[ESI+0x8]
//   [ESI+0x10] Unknown_10(DWORD)              MOV [ESI+0x10],0
// Sorted @+0xc is set by sibling ctors (MOV byte [ESI+0xc],1); not touched here.
// ---------------------------------------------------------------------------
struct BasePlanningCellContainer
{
    bool AddCapacity(int additionalCapacity);            // GAMEMD 0x510860 __thiscall
    static int __cdecl Comparator(const void* a, const void* b);  // GAMEMD 0x5108F0 __cdecl

    BasePlanningCell* Items;       // +0x00
    int               Count;       // +0x04
    int               Capacity;    // +0x08
    bool              Sorted;      // +0x0C
    unsigned long     Unknown_10;  // +0x10
};

GG_STATIC_ASSERT(offsetof(BasePlanningCellContainer, Items) == 0x00);
GG_STATIC_ASSERT(offsetof(BasePlanningCellContainer, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(BasePlanningCellContainer, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(BasePlanningCellContainer, Sorted) == 0x0C);
GG_STATIC_ASSERT(offsetof(BasePlanningCellContainer, Unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(BasePlanningCellContainer) == 0x14);

#endif  // GG_MATCH_CORE_GENERAL_STRUCTURES_H
