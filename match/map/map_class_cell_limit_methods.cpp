// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x588960 and 0x588990. MapClass keeps a
//   capped count at +0x148 that is clamped against a value and against zero.
//
// Address index: 0x588960 0x588990

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Minimal cell view: only the signed byte +0x11B is read.
#include "../_layout/cell_class.h"
GG_STATIC_ASSERT(offsetof(CellClass, Level) == 0x11B);

#include "../ui/input_controls/ui_display_chain.h"

// In-place clamps; the retail code stores through the member between them.
inline void ClampMax(int& x, int limit) { x = x < limit ? x : limit; }
inline void ClampMinZero(int& x) { x = x > 0 ? x : 0; }

// FUNCTION: GAMEMD 0x588960
// Lowers the capped count to the limit, then keeps it from going below zero.
void MapClass::FUN_00588960(int limit)
{
    ClampMax(unknown_148, limit);
    ClampMinZero(unknown_148);
}

// FUNCTION: GAMEMD 0x588990
// When the count is at least 13, lowers it to the smallest per-cell value, floored at zero.
int MapClass::FUN_00588990()
{
    if (unknown_148 >= 13) {
        int n = Owned.Capacity;
        for (int i = 0; i < n; ++i) {
            CellClass* cell = Owned.Items[i];
            if (cell) {
                ClampMax(unknown_148, cell->Level);
                ClampMinZero(unknown_148);
            }
        }
    }
    return unknown_148;
}
