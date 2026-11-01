// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared alpha-buffer declarations for every Blitter/RLEBlitter Alpha leaf family.
// Single owner: the blitter module orchestrator (split out of b_plainxlat.h, where the
// b-plainxlat worker first recovered them). Other clusters #include this; never redeclare.
#ifndef GG_MATCH_RENDER_BLITTERS_B_SHARED_ALPHA_H
#define GG_MATCH_RENDER_BLITTERS_B_SHARED_ALPHA_H

#include <stddef.h>
#include "blitter.h"

// Alpha-buffer row wrap block (global pointer at 0x87E8A4). Only +0x1C and
// +0x20 are read by the leaves, same shape as the Z block; size is not asserted.
struct BlitAlphaWrapBlock
{
    unsigned char unknown_00[0x1C];
    unsigned short* wrap_end;   // +0x1C
    unsigned int wrap_step;     // +0x20, bytes subtracted on wrap
};

GG_STATIC_ASSERT(offsetof(BlitAlphaWrapBlock, wrap_end) == 0x1C);
GG_STATIC_ASSERT(offsetof(BlitAlphaWrapBlock, wrap_step) == 0x20);

// GLOBAL: GAMEMD 0x87E8A4
extern "C" BlitAlphaWrapBlock* gg_blit_alpha_wrap_global;

#endif // GG_MATCH_RENDER_BLITTERS_B_SHARED_ALPHA_H
