// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
//
// Shared Z-row wrap view used by the Blitter and RLE leaf families. Names
// describe the observed accesses; the original owner type is not established.
//
// Evidence (disassembly of RLEBlitTransXlatZRead / ZReadWrite, 0x491B40,
// 0x491FD0 and the <unsigned short> twins): the Z row is addressed through a pointer to
// 16-bit Z entries. After the left-clip overshoot and after every iteration of the draw
// loop the code does
//     MOV  reg, [0x887644]       ; global pointer, reloaded each time
//     CMP  zrow, [reg + 0x1C]    ; unsigned (JC), byte-address compare
//     JC   skip
//     SUB  zrow, [reg + 0x20]    ; step back by that many BYTES
// i.e. the Z row is a circular buffer. Only offsets +0x1C and +0x20 are read
// by these leaves; every other field of the block is unrecovered, so it is
// modeled as an opaque gap and the total size is NOT asserted.
#ifndef GG_MATCH_RENDER_BLITTERS_R_SHARED_ZWRAP_H
#define GG_MATCH_RENDER_BLITTERS_R_SHARED_ZWRAP_H

#include <stddef.h>
#include "blitter.h"

struct RLEZWrapBlock
{
    unsigned char unknown_00[0x1C];
    unsigned short* wrap_end;   // +0x1C, end of the Z row buffer
    unsigned int wrap_step;     // +0x20, bytes subtracted on wrap
};

GG_STATIC_ASSERT(offsetof(RLEZWrapBlock, wrap_end) == 0x1C);
GG_STATIC_ASSERT(offsetof(RLEZWrapBlock, wrap_step) == 0x20);

// GLOBAL: GAMEMD 0x887644
extern "C" RLEZWrapBlock* gg_rle_zwrap_global;

// Wrap a Z row pointer the way the retail leaves do (re-reads the global).
inline unsigned short* RLEZWrapRow(unsigned short* row)
{
    if (row >= gg_rle_zwrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_rle_zwrap_global->wrap_step);
    return row;
}

#endif // GG_MATCH_RENDER_BLITTERS_R_SHARED_ZWRAP_H
