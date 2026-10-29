// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00696F10_H_H
#define GG_MATCH__LAYOUT_OBJ_00696F10_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F30() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_53) == 0x53);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_57) == 0x57);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);
#endif
