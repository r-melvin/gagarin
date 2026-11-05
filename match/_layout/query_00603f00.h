// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The record carried by control message 0x4E9, read off the senders 0x603F00, 0x603F60 and 0x603FC0 and the
//   handler 0x6AE3F0 in the user's retail gamemd.exe v1.001.
#ifndef GG_MATCH_LAYOUT_QUERY_00603F00_H
#define GG_MATCH_LAYOUT_QUERY_00603F00_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../wide_string_class.h"

// The three-word record the 0x4E9 control message fills in: two input words (the control and the item asked
// about), then the wide string it answers with.
struct Query_00603F00
{
    int           unknown_00;   // +0x00
    int           unknown_04;   // +0x04
    Obj_007B66D0  unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Query_00603F00, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(Query_00603F00) == 0x0C);

#endif
