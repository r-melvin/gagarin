// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x473AB0 loads the dword at 0x81C1D0 before its CD callback.
// The existing project name is retained; original ownership/type are unknown.
#ifndef GG_LAYOUT_GLOBAL_0081C1D0_H
#define GG_LAYOUT_GLOBAL_0081C1D0_H
#include "../_rt/gg_static_assert.h"
// GLOBAL: GAMEMD 0x0081C1D0
extern int g_FileSearchMode;
GG_STATIC_ASSERT(sizeof(g_FileSearchMode) == 4);
#endif
