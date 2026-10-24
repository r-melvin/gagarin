// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Existing ZBuffer owner extended from constructor7BC970 and rectangle-clear
// consumer7BCFB0. Display4A8960 allocates0x30, calls7BC970 and stores887644.
// This does not merge the separate alpha-buffer receiver at87E8A4.
#ifndef GG_MATCH_RENDERER_ZBUFFER_CLASS_METHODS_H
#define GG_MATCH_RENDERER_ZBUFFER_CLASS_METHODS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "surface_class.h"
struct ZBuffer
{
    RectangleStruct unknown_00;
    int unknown_10;
    Surface* Buffer;
    unsigned short* unknown_18;
    unsigned short* unknown_1C;
    int unknown_20;
    int unknown_24;
    int unknown_28;
    int unknown_2C;
    bool Fill(unsigned short color); // GAMEMD 0x7BCF50
    void ReleaseSurface(); // GAMEMD 0x7BCAE0
    // Declaration: GAMEMD 0x7BCFB0 -- four stacked DWORDs, RET0x10.
    void FUN_007BCFB0(RectangleStruct rectangle);
};
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ZBuffer, Buffer) == 0x14);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(ZBuffer, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(sizeof(ZBuffer) == 0x30);
// GLOBAL: GAMEMD 0x887644 (declaration; existing storage)
extern ZBuffer* ZBuffer_00887644;
#endif
