// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x45E8F0. Both dimensions are sign-extended 16-bit reads
//   (`MOVSX` from +0x2 and +0x4), and the per-pixel bias is 0x41.
#ifndef GG_MATCH_RENDERER_FONT_BIAS_METHODS_H
#define GG_MATCH_RENDERER_FONT_BIAS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Image_0045E8F0
{
    char _pad000[0x2];      // +0x0000
    short Width;            // +0x0002
    short Height;           // +0x0004

    // FUNCTION: GAMEMD 0x69E7E0
    void FUN_0069E7E0(void* scratch, int flags);
    // FUNCTION: GAMEMD 0x69E740 — the pixel buffer.
    char* FUN_0069E740(int index);
};
GG_STATIC_ASSERT(offsetof(Image_0045E8F0, Height) == 0x4);

struct Source_0045E8F0 { char opaque[4]; };
// GLOBAL: GAMEMD 0x8193F4
extern Source_0045E8F0 DAT_008193F4;
// GLOBAL: GAMEMD 0x89DDBC — loaded once and kept.
extern Image_0045E8F0* DAT_0089DDBC;

// FUNCTION: GAMEMD 0x5B40B0
Image_0045E8F0* __fastcall FUN_005B40B0(Source_0045E8F0* source, char flag);

// FUNCTION: GAMEMD 0x45E8F0
void FUN_0045E8F0();

#endif  // GG_MATCH_RENDERER_FONT_BIAS_METHODS_H
