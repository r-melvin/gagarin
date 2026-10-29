// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_NETWORK_OBJ_00A8B230_H_H
#define GG_MATCH_NETWORK_OBJ_00A8B230_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00A8B230
{
    char unknown_00[0x1254];  // +0x0000
    int unknown_1254;         // +0x1254
    char _pad1258[0x35A2 - 0x1258];
    bool unknown_35A2;        // +0x35A2
};
GG_STATIC_ASSERT(offsetof(Obj_00A8B230, unknown_1254) == 0x1254);
GG_STATIC_ASSERT(offsetof(Obj_00A8B230, unknown_35A2) == 0x35A2);

#endif
