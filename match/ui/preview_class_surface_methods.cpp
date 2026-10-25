// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6425F0.

#include "preview_class_surface_methods.h"

// FUNCTION: GAMEMD 0x6425F0
//
// PARTIAL (97.3%, 107/110). The only residual delta is register naming for
// the palette index temporary: retail zero-extends the pixel byte into EDX
// (XOR EDX,EDX / MOV DL,[ECX] / MOV AX,word ptr [ESI+EDX*2+4]) while cl 8804
// picks EAX for the same temporary, so three instructions differ by register
// only — the instruction multiset is identical. Variants tried: the palette
// modelled as a struct member versus a walking char* over the blob; the pixel
// read fused into the palette subscript versus split into index/increment
// statements; the palette entry typed unsigned short, signed short with an
// explicit & 0xFFFF (what produces retail's MOV AX / AND EAX,0xffff), and via
// a named short temporary; the index typed unsigned int, int and unsigned char
// (the last costs two extra instructions, 40.2%); and pt.X assigned before
// versus after the pixel read (after is 94.5%).
//
// Re-measured this pass against the declaration-scope lever (sweep where each
// local is DECLARED before sweeping how the expression is written) and the
// re-derive-at-the-use-site lever. Neither reaches it. Declaration placement
// is inert: `index` hoisted above the row loop, `index` and `v` both hoisted,
// `v` alone hoisted, `index` typed `int` instead of `unsigned int`, and an
// explicit `(unsigned char)` narrowing on the load all score 97.3% unchanged.
// Re-deriving the index at its use site is actively worse: `pal[*cursor]` with
// the increment after it 94.5%, the increment first with `pal[cursor[-1]]`
// 90.9%, and the increment moved below the palette read 94.5%. The residual
// stays a scratch-register naming difference (EDX vs EAX) with an identical
// instruction multiset.
//
// PreviewClass::CreatePreviewSurface — turn a decoded preview blob into the
// class's image surface. Any previous surface is destroyed through its own
// deleting destructor, a fresh 0x24-byte surface of the blob's width and
// height is allocated and cleared, and then the blob's 8-bit pixel run is
// walked row by row: each byte indexes the blob's 16-bit palette, the entry is
// repacked into the display's pixel format through the six shift globals at
// 0x8A0DD0, and the result is handed to the surface's plotting slot together
// with the pixel's (x, y).
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. The exchanged
// registers here are EAX and EDX — caller-saved scratch, never pushed — and
// retail's four prologue pushes and two sunk pushes are reproduced exactly, so
// there is no merged return block and no hoisted prologue to undo. The lever
// only addresses callee-saved colouring.
void PreviewClass_006425F0::CreatePreviewSurface(PreviewData_006425F0* data)
{
    char* blob = (char*)data;
    int width = *(int*)blob;
    blob = blob + 4;
    int height = *(int*)blob;
    blob = blob + 4;
    int count = *(int*)blob;
    short* pal = (short*)(blob + 4);

    if (this->ImageSurface != 0) {
        (this->ImageSurface->*this->ImageSurface->Vtbl->At_000)(1);
    }

    Surface_006425F0* raw = (Surface_006425F0*)FUN_007C8E17(sizeof(Surface_006425F0));
    Surface_006425F0* made;
    if (raw != 0) {
        made = raw->FUN_004BA5A0(width, height, 1, 0);
    } else {
        made = 0;
    }
    this->ImageSurface = made;
    (made->*made->Vtbl->At_018)(0);

    const unsigned char* cursor = (const unsigned char*)&data->Pal.Entries[count];

    Point_006425F0 pt;
    char scratch[0x10];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pt.X = x;
            unsigned int index = *cursor;
            cursor = cursor + 1;
            unsigned int v = (unsigned int)pal[index] & 0xFFFF;
            int colour =
                (int)((((v >> 4) & 0xF0) >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0
                      | ((v & 0xF0) >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1
                      | (unsigned int)((int)((v & 0xF) << 4) >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
            pt.Y = y;
            (this->ImageSurface->*this->ImageSurface->Vtbl->At_088)(
                &pt, colour,
                (this->ImageSurface->*this->ImageSurface->Vtbl->At_078)(scratch));
        }
    }
}
