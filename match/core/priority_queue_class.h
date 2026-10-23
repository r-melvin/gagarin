// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + arithmetic derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x42B1C0 / 0x42B1F0),
//   cross-checked against YRpp (every offset reconfirmed against the user's binary below).
//
// PriorityQueueClassNode — the surface-data helper the A* surface heap hangs off.
// Only the two static index helpers are modelled in this TU; the templated
// PriorityQueueClass<T> heap body and the full node layout are later work.
#ifndef GG_MATCH_CORE_PRIORITY_QUEUE_CLASS_H
#define GG_MATCH_CORE_PRIORITY_QUEUE_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// CellStruct == Vector2D<short> (YRpp). The two map cell coordinates, each a
// 16-bit signed short. Confirmed from 0x42B1C0: MOVSX EDX,word[ECX+0x2] (Y) and
// MOVSX ECX,word[ECX] (X) read X@0 / Y@2 as sign-extended shorts.
// ---------------------------------------------------------------------------
#include "../_layout/cell.h"
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x04);

// ---------------------------------------------------------------------------
// PriorityQueueClassNode — surface-grid index helpers.
//
//   ToSurfaceIndex(cell):  maps a CellStruct (diamond/iso coords) to its linear
//                          index inside the per-surface data array.
//   SurfaceDataCount():    total element count of that surface data array.
//
// Both read two adjacent global map dimensions:
//   GLOBAL: GAMEMD 0x87F8DC  int  (surface "width" multiplier, g_dc)
//   GLOBAL: GAMEMD 0x87F8E0  int  (surface "height", g_e0)
// ---------------------------------------------------------------------------
struct PriorityQueueClassNode
{
    // Declared ascending by retail address (reccmp/isle TU discipline).
    static int ToSurfaceIndex(const CellStruct& mapCoord);  // GAMEMD 0x42B1C0
    static int __stdcall  SurfaceDataCount();                          // GAMEMD 0x42B1F0
};

#endif  // GG_MATCH_CORE_PRIORITY_QUEUE_CLASS_H
