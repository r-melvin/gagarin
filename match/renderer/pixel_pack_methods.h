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

// GLOBAL: GAMEMD 0x8A0DD0 -- red left-shift.
extern int DAT_008A0DD0;
// GLOBAL: GAMEMD 0x8A0DD4 -- red right-shift.
extern int DAT_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8 -- blue left-shift.
extern int DAT_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DDC -- blue right-shift.
extern int DAT_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0 -- green left-shift.
extern int DAT_008A0DE0;
// GLOBAL: GAMEMD 0x8A0DE4 -- green right-shift.
extern int DAT_008A0DE4;

// FUNCTION: GAMEMD 0x63DAD0
//
// Pack a raw 8-bit-per-channel {R,G,B} triple into the display's native pixel
// format using the six shift globals, __fastcall with the triple pointer in
// ECX.
unsigned int PackPixel_0063DAD0(const unsigned char* rgb);

#include "../_layout/components.h"

// The same packing for a ColorStruct, expanded in place where retail expands it
// (0x63D0F0).
inline unsigned int PackPixel(const ColorStruct& color)
{
    unsigned char red = color.R >> DAT_008A0DD4;
    unsigned char green = color.G >> DAT_008A0DE4;
    unsigned char blue = color.B >> DAT_008A0DDC;
    return (red << DAT_008A0DD0) | (green << DAT_008A0DE0) | (blue << DAT_008A0DD8);
}

#endif  // GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H
