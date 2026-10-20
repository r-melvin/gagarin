// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D9EF0: `[ECX+0xDB0]` (the selectable count, compared
//   against 500 and incremented), `[ECX+0xB0]` / `[ECX+0xB4]` (the tactical
//   view origin added to the client point), the 12-byte-stride global array
//   `[EAX*4+0xB0CEC8]` / `+0xB0CECC` / `+0xB0CED0` (EAX = count*3), and the
//   view-bound globals at 0x886FA8 / 0x886FAC. Method/member names from the
//   YRpp method map (consult-only; names only, no text copied).
#ifndef GG_MATCH_RENDERER_TACTICAL_CLASS_SELECTABLE_METHODS_H
#define GG_MATCH_RENDERER_TACTICAL_CLASS_SELECTABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D) == 0x8);

// One queued selectable: the object and its screen-space point.
struct TacticalSelectableStruct
{
    void*   Techno;           // +0x0000
    Point2D Point;            // +0x0004
};
GG_STATIC_ASSERT(sizeof(TacticalSelectableStruct) == 0xC);
GG_STATIC_ASSERT(offsetof(TacticalSelectableStruct, Point) == 0x4);

// GLOBAL: GAMEMD 0xB0CEC8 — the selectable queue (500 entries).
extern TacticalSelectableStruct TacticalSelectables[500];

// GLOBAL: GAMEMD 0x886FA8 — view bound width.
extern int DAT_00886FA8;
// GLOBAL: GAMEMD 0x886FAC — view bound height.
extern int DAT_00886FAC;

struct TacticalClass
{
    char    _pad000[0xB0];    // +0x0000
    Point2D TacticalPos;      // +0x00B0
    char    _pad0B8[0xDB0 - 0xB8];  // +0x00B8
    int     SelectableCount;  // +0x0DB0

    // FUNCTION: GAMEMD 0x6D9EF0
    bool AddSelectable(void* pTechno, int x, int y);
};
GG_STATIC_ASSERT(offsetof(TacticalClass, TacticalPos) == 0xB0);
GG_STATIC_ASSERT(offsetof(TacticalClass, SelectableCount) == 0xDB0);

#endif  // GG_MATCH_RENDERER_TACTICAL_CLASS_SELECTABLE_METHODS_H
