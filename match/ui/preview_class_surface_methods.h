// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x6425F0:
//     PreviewClass::ImageSurface at [EBP+0] (MOV ECX,[EBP] / MOV [EBP],EAX).
//     The source blob in the argument: Width [EDI+0] (0x642603), Height
//     [EDI+4] (0x6425FD), palette entry count [EDI+8] read through ESI=EDI+8
//     (0x642610), palette words at [ESI+idx*2+4] = blob+0xC (0x642697), and
//     the 8-bit pixel run starting at blob + 0xC + count*2
//     (LEA ECX,[EDI+EAX*2+0xC] at 0x642664).
//     Surface vtable slots, all read off the retail indirect calls:
//       [EDX+0x00] scalar deleting destructor (PUSH 1)
//       [EDX+0x18] clear                      (PUSH 0)
//       [EBX+0x78] takes a 16-byte scratch buffer, returns a dword
//       [EBX+0x88] (point*, colour, dword)
//     The allocated surface is 0x24 bytes (PUSH 0x24 into 0x7C8E17) and its
//     constructor 0x4BA5A0 takes (width, height, 1, 0) — identical to the
//     already-matched 0x641DB0 in match/ui/preview_class_pcx_methods.{h,cpp}
//     (read, not edited; re-derived here so this TU stands alone).
//     The six pixel-format shift globals at 0x8A0DD0..0x8A0DE4 are read off
//     the shift instructions at 0x642691..0x6426E2; the two right-shift
//     counts are byte loads (MOV CL,byte ptr) and the four left/arithmetic
//     ones dword loads (MOV ECX,dword ptr).
//   Names (PreviewClass, CreatePreviewSurface) cross-checked against YRpp
//  ; every offset reconfirmed above.
#ifndef GG_MATCH_UI_PREVIEW_CLASS_SURFACE_METHODS_H
#define GG_MATCH_UI_PREVIEW_CLASS_SURFACE_METHODS_H

#include "../renderer/pixel_shift_view.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// LIBRARY: GAMEMD 0x7C8E17 (decl; reloc) — operator new, __cdecl.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

// ---------------------------------------------------------------------------
// The pixel-format shift table at 0x8A0DD0 (six consecutive dwords). The two
// right-shift counts are read as bytes by retail, the other four as dwords.
// ---------------------------------------------------------------------------

// The 2-int point handed to surface slot 0x88.
struct Point_006425F0
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(offsetof(Point_006425F0, Y) == 0x04);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_006425F0;

// The 0x24-byte drawing surface.
struct Surface_006425F0
{
    Vtbl_006425F0* Vtbl;           // +0x0000
    char _pad004[0x24 - 0x04];

    // FUNCTION: GAMEMD 0x4BA5A0 (decl; reloc) — the constructor, spelled as an
    // ordinary __thiscall member returning `this` so that the allocate / null
    // test / construct expansion can be written by hand (a `new T(...)`
    // expression with a declared constructor drags in a /GX exception frame
    // retail does not have).
    Surface_006425F0* FUN_004BA5A0(int width, int height, char a, char b);
};
GG_STATIC_ASSERT(sizeof(Surface_006425F0) == 0x24);

typedef void* (Surface_006425F0::*Fn000_006425F0)(char freeFlag);
typedef void  (Surface_006425F0::*Fn018_006425F0)(int colour);
typedef int   (Surface_006425F0::*Fn078_006425F0)(void* scratch);
typedef void  (Surface_006425F0::*Fn088_006425F0)(Point_006425F0* pt, int colour, int extra);

struct Vtbl_006425F0
{
    Fn000_006425F0 At_000;                  // +0x0000
    char _pad004[0x18 - 0x04];
    Fn018_006425F0 At_018;                  // +0x0018
    char _pad01C[0x78 - 0x1C];
    Fn078_006425F0 At_078;                  // +0x0078
    char _pad07C[0x88 - 0x7C];
    Fn088_006425F0 At_088;                  // +0x0088
};
GG_STATIC_ASSERT(offsetof(Vtbl_006425F0, At_018) == 0x18);
GG_STATIC_ASSERT(offsetof(Vtbl_006425F0, At_078) == 0x78);
GG_STATIC_ASSERT(offsetof(Vtbl_006425F0, At_088) == 0x88);

// The palette block of the source blob: an entry count followed by the 16-bit
// entries. Sits at blob+8, so the entries land at blob+0xC.
struct PaletteBlock_006425F0
{
    int            Count;        // +0x00
    unsigned short Entries[1];   // +0x04
};
GG_STATIC_ASSERT(offsetof(PaletteBlock_006425F0, Entries) == 0x04);

// The decoded preview blob handed to CreatePreviewSurface.
struct PreviewData_006425F0
{
    int                  Width;    // +0x00
    int                  Height;   // +0x04
    PaletteBlock_006425F0 Pal;     // +0x08 (entries at +0x0C)
};
GG_STATIC_ASSERT(offsetof(PreviewData_006425F0, Pal) == 0x08);

struct PreviewClass_006425F0
{
    Surface_006425F0* ImageSurface;   // +0x0000

    // FUNCTION: GAMEMD 0x6425F0
    void CreatePreviewSurface(PreviewData_006425F0* data);
};
GG_STATIC_ASSERT(offsetof(PreviewClass_006425F0, ImageSurface) == 0x0);

#endif  // GG_MATCH_UI_PREVIEW_CLASS_SURFACE_METHODS_H
