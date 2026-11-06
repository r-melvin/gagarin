// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI .?AVMapSelect@@ (type descriptor 0x82C0C8, locator 0x805C10): base chain MapSelect -> MSEngine, vtable
//   0x7EDB4C (slot 0 0x5AE5A0 deleting destructor, slot 1 0x5AE590 inherited OnRedraw, slot 2 0x5AE4C0).
//   Layout read from the inline construction in 0x5ADD10 / 0x5ADE20 (MSEngine constructor, MapStageList constructor
//   at +0x50, Wstring at +0xC8, wall-clock timer at +0xCC, vptr store last) and the member stores of 0x5AE220.
#ifndef GG_MATCH_LAYOUT_MAP_SELECT_H
#define GG_MATCH_LAYOUT_MAP_SELECT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ms_engine.h"
#include "map_stage_list.h"
#include "elapsed_timer.h"

class MSFont;
struct ScenarioClass;

// VTABLE: GAMEMD 0x7EDB4C
class MapSelect : public MSEngine
{
public:
    virtual void Process();                 // slot 2, 0x5AE4C0

    // FUNCTION: GAMEMD 0x5ADF20
    bool FUN_005ADF20(ScenarioClass* scenario, Wstring* name);
    // FUNCTION: GAMEMD 0x5AE100
    bool FUN_005AE100(ScenarioClass* scenario);
    // FUNCTION: GAMEMD 0x5AE220
    bool FUN_005AE220(ScenarioClass* scenario);
    // FUNCTION: GAMEMD 0x5AE460 (decl; reloc) -- delete the three owned members and reset the stage list.
    void FUN_005AE460();

    int unknown_48;                          // +0x48 screen x offset
    int unknown_4C;                          // +0x4C screen y offset
    MapStageList Stages;                     // +0x50
    int unknown_AC;                          // +0xAC
    int unknown_B0;                          // +0xB0
    MSFont* Font;                            // +0xB4
    RectangleStruct Bounds;                  // +0xB8
    Wstring Name;                            // +0xC8
    ScenarioElapsedTimer Timer;              // +0xCC
    int unknown_D8;                          // +0xD8
};
GG_STATIC_ASSERT(offsetof(MapSelect, unknown_48) == 0x48 && offsetof(MapSelect, Stages) == 0x50
              && offsetof(MapSelect, Font) == 0xB4 && offsetof(MapSelect, Bounds) == 0xB8
              && offsetof(MapSelect, Name) == 0xC8 && offsetof(MapSelect, Timer) == 0xCC
              && offsetof(MapSelect, unknown_D8) == 0xD8 && sizeof(MapSelect) == 0xDC);

#endif  // GG_MATCH_LAYOUT_MAP_SELECT_H
