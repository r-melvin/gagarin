// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Function Evidence:
// ev_330cf025e03b54b6fa8299b7f6c35d1e972a43f633bd33fc573655705ce6a4fa and
// ev_bfb450bcbcaaa457d07d4d24bcff0fb4268287b4723d36ed0e06e16e2079ac14.
// Callee ABI checks: ev_d986c04cb1bd463a2b063531d6a44e396177d3a148b9d20d513a11e872828910,
// ev_55999afd44dd9471401d3bd270ee742b75485429e7382fa6a318da35b9266320,
// ev_a56cad00b146b84958706bb8a89dcf54ae86ac8d0b6a50ab3f85419585eb6f78.
#ifndef GG_MAP_CELL_SWEEPS_005866C0_H
#define GG_MAP_CELL_SWEEPS_005866C0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellScan_005866C0 {
    char unknown_000[0x140];
    unsigned char flags; // +0x140
    // FUNCTION: GAMEMD 0x486A70 (decl; reloc)
    void FUN_00486A70();
    // FUNCTION: GAMEMD 0x486BF0 (decl; reloc)
    void FUN_00486BF0();
};
GG_STATIC_ASSERT(offsetof(CellScan_005866C0, flags) == 0x140);
GG_STATIC_ASSERT(sizeof(CellScan_005866C0) == 0x141);

struct MapScan_005866C0 {
    char unknown_000[0xF4];
    int cellCount; // +0xF4
    char unknown_0F8[0x10C - 0xF8];
    int iterState; // +0x10C
    int iterCount; // +0x110
    int iterLast; // +0x114
    int iterCursor; // +0x118
    char unknown_11C[0x13C - 0x11C];
    int cellBase; // +0x13C
    // FUNCTION: GAMEMD 0x578290 (decl; reloc)
    CellScan_005866C0* FUN_00578290();
    void FUN_005866C0();
    void FUN_00586720();
};
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, cellCount) == 0xF4);
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, iterState) == 0x10C);
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, iterCount) == 0x110);
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, iterLast) == 0x114);
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, iterCursor) == 0x118);
GG_STATIC_ASSERT(offsetof(MapScan_005866C0, cellBase) == 0x13C);
GG_STATIC_ASSERT(sizeof(MapScan_005866C0) == 0x140);
#endif
