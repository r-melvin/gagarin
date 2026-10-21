// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x47AD50 allocates eight bytes, stores Next at +0 and Path at +4;
// 0x47AAC0 frees the same fields. 0x47AE10 traverses Next and reads Path.
// Shared address-scoped view; original type/member names and ownership are unknown.
#ifndef GG_MATCH_LAYOUT_CD_SEARCH_PATH_H
#define GG_MATCH_LAYOUT_CD_SEARCH_PATH_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One entry of the CD search-path list: the next node, then the directory
// prefix that is prepended to a bare file name.
struct SearchPath_0047AE10
{
    SearchPath_0047AE10* Next;   // +0x00
    const char*          Path;   // +0x04
};
GG_STATIC_ASSERT(offsetof(SearchPath_0047AE10, Next) == 0x0);
GG_STATIC_ASSERT(offsetof(SearchPath_0047AE10, Path) == 0x4);
GG_STATIC_ASSERT(sizeof(SearchPath_0047AE10) == 8);

// GLOBAL: GAMEMD 0x89E410 — head of the CD search-path list.
extern SearchPath_0047AE10* DAT_0089E410;

#endif
