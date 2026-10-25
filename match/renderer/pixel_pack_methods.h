// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x63DAD0.
//
//   The six pixel-format shift globals at 0x8A0DD0..0x8A0DE4 are ints. Each
//   channel is shifted right into a byte, then the byte is shifted left into
//   place: 0x63DAD0 reads the right-shift counts with byte loads (only CL is
//   needed), and 0x63D0F0, which expands the same packing twice, keeps them in
//   registers as `MOV reg,dword / AND reg,0xFF` and the channel bytes as bytes.
#ifndef GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H
#define GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H


// FUNCTION: GAMEMD 0x63DAD0
//
// Pack a raw 8-bit-per-channel {R,G,B} triple into the display's native pixel
// format using the six shift globals, __fastcall with the triple pointer in
// ECX.
unsigned int PackPixel_0063DAD0(const unsigned char* rgb);

#include "pixel_shift_view.h"
#include "../_layout/components.h"

// The same packing for a ColorStruct, expanded in place where retail expands it
// (0x63D0F0).
inline unsigned int PackPixel(const ColorStruct& color)
{
    unsigned char red = color.R >> gg_b_translucent_pixel_format.loss0;
    unsigned char green = color.G >> gg_b_translucent_pixel_format.loss1;
    unsigned char blue = color.B >> gg_b_translucent_pixel_format.loss2;
    return (red << gg_b_translucent_pixel_format.pos0) | (green << gg_b_translucent_pixel_format.pos1) | (blue << gg_b_translucent_pixel_format.pos2);
}

#endif  // GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H
