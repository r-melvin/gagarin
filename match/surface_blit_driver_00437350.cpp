// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at 0x437350 (offsets read numerically). It fetches the
//   bounds rectangles of both surfaces through slot 30 (GetRect, hidden result) and hands everything to
//   the scanline blit routine 0x4373B0.

#include "wwlib/surface/surface_class.h"

// FUNCTION: GAMEMD 0x4373B0 (decl; reloc) -- ECX = destination surface, EDX = its bounds,
// ten stack arguments, RET 0x28.
bool __fastcall FUN_004373B0(Surface* dest, const RectangleStruct& destBounds,
                             const RectangleStruct* destRect, Surface* src,
                             const RectangleStruct& srcBounds, const RectangleStruct* srcRect,
                             Blitter* blitter, int a, int b, int c, int d, int e);

// FUNCTION: GAMEMD 0x437350
bool BlitDriver(Surface* dest, const RectangleStruct* destRect, Surface* src,
                const RectangleStruct* srcRect, Blitter* blitter, int a, int b, int c, int d)
{
    return FUN_004373B0(dest, dest->GetRect(), destRect, src, src->GetRect(), srcRect, blitter, a, b, c, d, 0);
}
