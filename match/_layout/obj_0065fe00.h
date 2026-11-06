// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
// The radar event record (the element type of the registry at 0xB04DA8, RTTI
// DynamicVectorClass<RadarEventClass*>). Layout read off its constructor at
// 0x65FB80 and the per-frame update at 0x65FE00.
#ifndef GG_MATCH__LAYOUT_OBJ_0065FE00_H_H
#define GG_MATCH__LAYOUT_OBJ_0065FE00_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "cell.h"
#include "frame_timer.h"
#include "rgb_class.h"

struct Obj_0065FE00 {
    int Type;               // +0x00 index into the 0x7F0998 type table
    int ScreenX;            // +0x04 radar position of the cell
    int ScreenY;            // +0x08
    float Radius;           // +0x0C
    float Angle;            // +0x10
    float AngleStep;        // +0x14
    float Fade;             // +0x18
    float FadeStep;         // +0x1C
    CellStruct Cell;        // +0x20
    CDTimerClass Pulse;     // +0x24
    CDTimerClass Life;      // +0x30
    bool Running;           // +0x3C
    bool Active;            // +0x3D
    char pad_3E[2];

    // FUNCTION: GAMEMD 0x65FE00 (decl; reloc)
    void FUN_0065FE00();
    // FUNCTION: GAMEMD 0x660540 (decl; reloc)
    void FUN_00660540();
    // FUNCTION: GAMEMD 0x660950
    RGBClass FUN_00660950();
    // FUNCTION: GAMEMD 0x660A10
    RGBClass FUN_00660A10();
};
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, ScreenX) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Radius) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Angle) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, AngleStep) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Fade) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, FadeStep) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Cell) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Pulse) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Life) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Running) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_0065FE00, Active) == 0x3D);
GG_STATIC_ASSERT(sizeof(Obj_0065FE00) == 0x40);
#endif
