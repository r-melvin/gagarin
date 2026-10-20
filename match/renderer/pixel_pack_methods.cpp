// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x63DAD0.

#include "pixel_pack_methods.h"

// FUNCTION: GAMEMD 0x63DAD0
//
// MATCHED (100.0%, 26/26). The final combination is `(blue | green) | red`,
// but retail's LOAD/SHIFT instruction sequences run green first, then blue,
// then red -- the source order `blue; green; red;` (matching the textual
// left-to-right of the OR chain) has cl 8804 schedule the green and blue
// instruction groups swapped (confirmed via the object's relocation table,
// not the operand text: the first `mov cl,[global]` after the swap resolves
// to DAT_008A0DE4, green's, even though blue's OR still combines correctly).
// Declaring green before blue -- with the final `blue | green | red`
// expression left unchanged -- reproduces retail's instruction order exactly.
unsigned int __fastcall PackPixel_0063DAD0(const unsigned char* rgb)
{
    unsigned int green = (rgb[1] >> DAT_008A0DE4) << DAT_008A0DE0;
    unsigned int blue  = (rgb[2] >> DAT_008A0DDC) << DAT_008A0DD8;
    unsigned int red   = (rgb[0] >> DAT_008A0DD4) << DAT_008A0DD0;
    return blue | green | red;
}
