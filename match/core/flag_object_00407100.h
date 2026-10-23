// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Shared observed prefix: 0x407150 sets bit0 at +0 and writes value<<16
// at +8. Receiver passed through global0x87E758 by 0x69BAB0/0x69BB40.
#ifndef GG_MATCH_CORE_FLAG_OBJECT_00407100_H
#define GG_MATCH_CORE_FLAG_OBJECT_00407100_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Obj_00407100
{
    int  Flags;        // +0x0000
    char _pad04[0x4];
    int  unknown_08;   // +0x0008

    // Declaration: GAMEMD 0x407150
    void __fastcall FUN_00407150(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00407100, unknown_08) == 0x8);

GG_STATIC_ASSERT(offsetof(Obj_00407100, Flags) == 0);
GG_STATIC_ASSERT(sizeof(((Obj_00407100*)0)->Flags) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_00407100*)0)->unknown_08) == 4);
#endif
