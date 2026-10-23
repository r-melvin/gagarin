// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Exact declaration extraction from unit_class_astar_attempt_methods.h.
// Retail 0x746000 and Queue caller0x64D64B use six stacked arguments.
#ifndef GG_MATCH_LAYOUT_ASTAR_00746000_H
#define GG_MATCH_LAYOUT_ASTAR_00746000_H
#include "cell.h"
class FootClass;
// AStarClass — only AttemptPath on the global instance.
struct AStar_00746000
{
    char opaque[4];
    // Declaration: GAMEMD 0x42D170 (decl; reloc) — AStarClass::AttemptPath.
    int AttemptPath(const CellStruct* from, const CellStruct* to,
                    FootClass* foot, bool fromAlt, bool toAlt, int zone);
};
// GLOBAL: GAMEMD 0x87E8B8 — AStarClass::Instance.
extern AStar_00746000 DAT_0087E8B8;

#endif
