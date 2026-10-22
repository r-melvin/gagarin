// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4A8BF0: the cursor cell pair at `[EBX+0x1174]` /
//   `[EBX+0x1176]`, the placement offset pair at `[EBX+0x1178]` /
//   `[EBX+0x117A]`, the active foundation pointer at `[EBX+0x117C]`, the
//   global cell pair at 0x8A03F8, the function-local static foundation
//   buffer at 0x8A041C (0x78 dwords copied by `REP MOVSD`) with its guard
//   byte 0x8A0618, `atexit` 0x7C978A and destructor thunk 0x4A8D40, the
//   size query 0x4A94F0 (out pointer and foundation pushed) and the
//   redraw 0x4A95A0 (cell reference and flag pushed). Names cross-checked
//   against YRpp.
#ifndef GG_MATCH_UI_DISPLAY_CLASS_ACTIVE_FOUNDATION_METHODS_H
#define GG_MATCH_UI_DISPLAY_CLASS_ACTIVE_FOUNDATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct — passed by const reference, which is why retail stores the two
// words and then copies the pair as one dword into the argument slot.
struct Cell_004A8BF0
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_004A8BF0) == 4);

// A cell built in place and handed straight to a const-reference parameter.
inline Cell_004A8BF0 MakeCell_004A8BF0(int x, int y)
{
    Cell_004A8BF0 cell;
    cell.X = (short)x;
    cell.Y = (short)y;
    return cell;
}

// GLOBAL: GAMEMD 0x8A03F8 — the cell pair the offset is reset to.
extern Cell_004A8BF0 DAT_008A03F8;

// The foundation the display is currently showing: 0x78 dwords, held in a
// function-local static whose destructor is registered with atexit.
struct Foundation_004A8BF0
{
    int Data[0x78];

    // FUNCTION: GAMEMD 0x4A8D40 (decl; reloc) — the destructor registered
    // with atexit for the static copy.
    ~Foundation_004A8BF0();
};
GG_STATIC_ASSERT(sizeof(Foundation_004A8BF0) == 0x1E0);

struct Display_004A8BF0
{
    char                 _pad0000[0x1174];   // +0x0000
    Cell_004A8BF0        unknown_1174;         // +0x1174
    Cell_004A8BF0        Offset;             // +0x1178
    Foundation_004A8BF0* Active;             // +0x117C

    // FUNCTION: GAMEMD 0x4A94F0 (decl; reloc) — the foundation's size in
    // cells, written through the out pointer and returned.
    Cell_004A8BF0* GetFoundationSize(Cell_004A8BF0* out, Foundation_004A8BF0* foundation);
    // FUNCTION: GAMEMD 0x4A95A0 (decl; reloc) — redraw the footprint at a
    // cell; the flag selects drawing it or erasing it.
    void RedrawFoundation(const Cell_004A8BF0& cell, int draw);

    // FUNCTION: GAMEMD 0x4A8BF0 — DisplayClass::SetActiveFoundation.
    void SetActiveFoundation(Foundation_004A8BF0* foundation);
};
GG_STATIC_ASSERT(offsetof(Display_004A8BF0, unknown_1174) == 0x1174);
GG_STATIC_ASSERT(offsetof(Display_004A8BF0, Offset)     == 0x1178);
GG_STATIC_ASSERT(offsetof(Display_004A8BF0, Active)     == 0x117C);

#endif  // GG_MATCH_UI_DISPLAY_CLASS_ACTIVE_FOUNDATION_METHODS_H
