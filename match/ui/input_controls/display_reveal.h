// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and conventions read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI from the entry disassembly of 0x4A9890, 0x4A9CA0, 0x4A9DD0 and 0x4AA050, and from the RTTI
//   vtable .?AVDisplayClass@@ at 0x7E6114 (50 slots; slots 36..39 are these four entries).
//
// The "reveal" family of DisplayClass (ui_display_chain.h). The four entries take (cell*, house*[, bool]) with
// ECX = this (the pointer is passed untouched to MapClass::GetCellAt, 0x5657A0) and return a bool in AL; they are
// __thiscall, not the census __stdcall lead.
//
// CellClass fields touched (all offsets from instructions in the entries):
//   +0x120 signed byte  visibility value of layer 0 (compared with the projector result, `MOVSX ECX,[ESI+0x120]`)
//   +0x121 signed byte  visibility value of layer 1
//   +0x12C dword flags  bit 3 (0x08), bit 4 (0x10)
//   +0x140 dword flags  bit 0 (0x01), bit 1 (0x02), bit 6 (0x40)
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_REVEAL_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_REVEAL_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_display_chain.h"
#include "../../core/cell_step_tables.h"

// Component-wise 16-bit sums use CellStruct::operator+ (_layout/cell.h).


class DisplayHouse;

class DisplayCell
{
public:
    char          unknown_000[0x120];   // +0x000
    signed char   Layer0Value;          // +0x120
    signed char   Layer1Value;          // +0x121
    char          unknown_122[0x12C - 0x122];   // +0x122
    unsigned long Flags12C;             // +0x12C
    char          unknown_130[0x140 - 0x130];   // +0x130
    unsigned long Flags140;             // +0x140

    // FUNCTION: GAMEMD 0x486BF0 (decl; reloc)
    void CleanFog_00486BF0();
    // FUNCTION: GAMEMD 0x487630 (decl; reloc)
    void ReduceShroudCounter_00487630();
    // FUNCTION: GAMEMD 0x487690 (decl; reloc)
    void IncreaseShroudCounter_00487690();
};
GG_STATIC_ASSERT(offsetof(DisplayCell, Layer0Value) == 0x120);
GG_STATIC_ASSERT(offsetof(DisplayCell, Layer1Value) == 0x121);
GG_STATIC_ASSERT(offsetof(DisplayCell, Flags12C) == 0x12C);
GG_STATIC_ASSERT(offsetof(DisplayCell, Flags140) == 0x140);

// The projector (Tactical) instance at 0x887324.
class DisplayProjector
{
public:
    char opaque[4];
    // FUNCTION: GAMEMD 0x6D8700 (decl; reloc) -- per-layer value of a cell; -1 / -2 are the special results.
    int FUN_006D8700(CellStruct const* cell, int layer);
    // FUNCTION: GAMEMD 0x6DA7D0 (decl; reloc) -- redraw / refresh the cell.
    void FUN_006DA7D0(DisplayCell* cell);
};
// GLOBAL: GAMEMD 0x887324 -- the projector instance pointer.
extern DisplayProjector* DisplayProjector_00887324;

// The MapClass instance at 0x87F7E8 (an immediate in the entries).
class DisplayMapInstance
{
public:
    char opaque[4];
    // FUNCTION: GAMEMD 0x5865F0 (decl; reloc)
    void RevealCheck_005865F0(DisplayCell* cell, DisplayHouse* house, bool arg);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the MapClass instance itself.
extern DisplayMapInstance DisplayMap_0087F7E8;

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
#include "../../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// DisplayClass (slots 36..39) and MapClass::GetCellAt_005657A0 are declared in ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_REVEAL_H
