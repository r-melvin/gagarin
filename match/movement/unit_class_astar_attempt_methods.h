// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x746000: the height slot `[EAX+0x1C8]` on the unit
//   (int, negative rejects), the map object 0x87F7E8 with the six-argument
//   path pre-check 0x56D100, the CellStruct usable-area test 0x578460 and
//   GetCellAt 0x5657A0 (one argument, RET 4), the cell flag word
//   `[EAX+0x140]` bit 8 (the alternate/bridge level), and the AStarClass
//   instance 0x87E8B8 whose AttemptPath 0x42D170 takes six stack arguments.
//   Names cross-checked against YRpp UnitClass.h / AStarClass.h / MapClass.h
//   (consult-only; NO LICENSE).
#ifndef GG_MATCH_MOVEMENT_UNIT_CLASS_ASTAR_ATTEMPT_METHODS_H
#define GG_MATCH_MOVEMENT_UNIT_CLASS_ASTAR_ATTEMPT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_00746000
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_00746000) == 0x4);

// CellClass — only the flag word is read.
struct CellClass_00746000
{
    char _pad000[0x140];   // +0x0000
    unsigned int Flags;    // +0x0140  bit 8 = alternate (bridge) level
};
GG_STATIC_ASSERT(offsetof(CellClass_00746000, Flags) == 0x140);

struct Vtbl_00746000;

// UnitClass — only the vtable is touched.
struct Unit_00746000
{
    Vtbl_00746000* Vptr;   // +0x0000

    // FUNCTION: GAMEMD 0x746000 — UnitClass::AStarAttempt.
    bool AStarAttempt(const Cell_00746000* from, const Cell_00746000* to);
};

typedef int (Unit_00746000::*Fn1C8_00746000)();

struct Vtbl_00746000
{
    char            _pad000[0x1C8];   // +0x0000
    Fn1C8_00746000  GetHeight;        // +0x01C8
};
GG_STATIC_ASSERT(offsetof(Vtbl_00746000, GetHeight) == 0x1C8);

// MapClass — the three map queries the attempt goes through.
struct Map_00746000
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56D100 (decl; reloc) — path pre-check between two cells.
    bool FUN_0056D100(const Cell_00746000* from, const Cell_00746000* to,
                      int a, char b, char c, char d);
    // FUNCTION: GAMEMD 0x578460 (decl; reloc) — MapClass::IsWithinUsableArea(CellStruct const&, bool).
    bool IsWithinUsableArea(const Cell_00746000* cell, bool checkLevel);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_00746000* GetCellAt(const Cell_00746000* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_00746000 MapInstance_00746000;

// AStarClass — only AttemptPath on the global instance.
struct AStar_00746000
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x42D170 (decl; reloc) — AStarClass::AttemptPath.
    int AttemptPath(const Cell_00746000* from, const Cell_00746000* to,
                    Unit_00746000* foot, bool fromAlt, bool toAlt, int zone);
};
// GLOBAL: GAMEMD 0x87E8B8 — AStarClass::Instance.
extern AStar_00746000 DAT_0087E8B8;

#endif  // GG_MATCH_MOVEMENT_UNIT_CLASS_ASTAR_ATTEMPT_METHODS_H
