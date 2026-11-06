// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Exact existing Obj_005BCC40 extraction from trivial_tu139_b_methods.h.
// Additional declarations are proved by the primary logger entries cited below.
#ifndef GG_MATCH_LAYOUT_OBJ_005BCC40_H
#define GG_MATCH_LAYOUT_OBJ_005BCC40_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Obj_005BCC40
{
    char cells[80][25];     // +0x0000  character grid, first index is the column
    int attrs[80][25];      // +0x07D0  per-cell attribute, same indexing
    int unknown_2710;       // +0x2710  attribute written with each printed cell
    int unknown_2714;       // +0x2714  attribute last selected into the device context
    int unknown_2718;       // +0x2718
    int unknown_271C;   // +0x271C
    int unknown_2720;   // +0x2720
    int unknown_2724;       // +0x2724  window origin column
    int unknown_2728;       // +0x2728  window origin row
    int unknown_272C;       // +0x272C  window width
    int unknown_2730;       // +0x2730  window height
    unsigned char unknown_2734;  // +0x2734  grid changed
    // Declaration: GAMEMD 0x5BCC90 -- ECX receiver, no explicit arguments, RET.
    // ev_815b3e281a7c8c872877457e76f7e69e5b8ba7b2e43486ac16fe15ce1b436055.
    void FUN_005BCC90();
    // Declaration: GAMEMD 0x5BD1F0 -- receiver, format, varargs on stack, RET.
    // ev_0db0b30d05420a6fb6bc36f74a7f096998a2d7b284dbf4c2d2cd1d797fb85ad0.
    void __cdecl FUN_005BD1F0(const char* format, ...);
    // Declaration: GAMEMD 0x5BCC40
    void FUN_005BCC40(int a1, int a2);
    // Blanks the whole grid, marks it changed and redraws it (inlined in 0x5BC180).
    inline void Clear()
    {
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                cells[j][i] = ' ';
                attrs[j][i] = 0;
            }
        }
        unknown_2734 = 1;
        FUN_005BD490(0, 0, 80, 25);
    }
    // Constructor inlined in 0x5BC180: window covers the whole grid, grid blanked.
    inline Obj_005BCC40(int index)
    {
        unknown_271C = 0;
        unknown_2718 = index;
        unknown_2720 = 0;
        unknown_2724 = 0;
        unknown_2728 = 0;
        unknown_272C = 80;
        unknown_2730 = 25;
        Clear();
    }
    // Declaration: GAMEMD 0x5BCE10
    void FUN_005BCE10(int dir);
    // Declaration: GAMEMD 0x5BCF90
    void FUN_005BCF90(int dir);
    // Declaration: GAMEMD 0x5BD3D0
    void FUN_005BD3D0(int hdc, int x, int y);
    // Declaration: GAMEMD 0x5BD490
    void FUN_005BD490(int x, int y, int w, int h);
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, attrs) == 0x7D0);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2710) == 0x2710);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2714) == 0x2714);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2718) == 0x2718);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2724) == 0x2724);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2728) == 0x2728);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_272C) == 0x272C);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2730) == 0x2730);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2734) == 0x2734);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_271C) == 0x271C);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2720) == 0x2720);

#endif
