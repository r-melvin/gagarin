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
    char unknown_00[0x271C];
    int unknown_271C;   // +0x271C
    int unknown_2720;   // +0x2720
    // Declaration: GAMEMD 0x5BCC90 -- ECX receiver, no explicit arguments, RET.
    // ev_815b3e281a7c8c872877457e76f7e69e5b8ba7b2e43486ac16fe15ce1b436055.
    void FUN_005BCC90();
    // Declaration: GAMEMD 0x5BD1F0 -- receiver, format, varargs on stack, RET.
    // ev_0db0b30d05420a6fb6bc36f74a7f096998a2d7b284dbf4c2d2cd1d797fb85ad0.
    void __cdecl FUN_005BD1F0(const char* format, ...);
    // Declaration: GAMEMD 0x5BCC40
    void FUN_005BCC40(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_271C) == 0x271C);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2720) == 0x2720);

#endif
