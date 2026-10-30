// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4346C0 / 0x434990),
//   cross-checked against YRpp (every offset/slot reconfirmed from the disasm).
//
// BitFont combines the constructor, destructor, lock and glyph-method views.
// Touched fields are pinned to the retail instructions cited below.
#ifndef GG_MATCH_RENDERER_BIT_FONT_H
#define GG_MATCH_RENDERER_BIT_FONT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "surface_class.h"

// ---------------------------------------------------------------------------
// BitFont::InternalData — the loaded font's glyph table. Offsets confirmed from
// GetCharacterBitmap's [ECX+0x14]/[ECX+0x18]/[ECX+0x1c] (where ECX == the
// InternalData* at BitFont+0x4). SymbolTable is loaded with a zero-extending
// 16-bit read (XOR/MOV DX), so it is typed unsigned short*.
// ---------------------------------------------------------------------------
struct BitFontInternalData
{
    int unknown_00;
    int Width;
    int unknown_08;
    int Height;
    int unknown_10;
    int             SymbolDataSize;   // +0x14
    unsigned short* SymbolTable;      // +0x18
    char*           Bitmaps;          // +0x1C
    int             GlyphCount;       // +0x20
};
// Constructor 0x433880 reads width +4 and height +0x0C from this record.
GG_STATIC_ASSERT(offsetof(BitFontInternalData, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, Width) == 4);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, Height) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolDataSize) == 0x14);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolTable) == 0x18);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFontInternalData, Bitmaps)     == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, GlyphCount) == 0x20);
GG_STATIC_ASSERT(sizeof(BitFontInternalData) == 0x24);
#endif

// ---------------------------------------------------------------------------
// BitFont has a virtual destructor at vtable slot zero.
// Members confirmed numerically:
//   +0x04 InternalPTR    (GetCharacterBitmap MOV ECX,[ECX+0x4])
//   +0x0C pGraphBuffer   (UnLock MOV [ESI+0xC], 0)
//   +0x10 PitchDiv2      (UnLock MOV [ESI+0x10], 0)
// ---------------------------------------------------------------------------
// The clip rectangle 0x433CA0 copies into +0x30..+0x3C: edges, not extents
// (0x621040 takes the width as right - left).
struct BitFontBounds
{
    int Left;     // +0x00
    int Top;      // +0x04
    int Right;    // +0x08
    int Bottom;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(BitFontBounds, Left) == 0);
GG_STATIC_ASSERT(offsetof(BitFontBounds, Top) == 4);
GG_STATIC_ASSERT(offsetof(BitFontBounds, Right) == 8);
GG_STATIC_ASSERT(offsetof(BitFontBounds, Bottom) == 12);
GG_STATIC_ASSERT(sizeof(BitFontBounds) == 0x10);

// VTABLE: GAMEMD 0x7E3A78
class BitFont
{
public:
    // FUNCTION: GAMEMD 0x433940
    virtual ~BitFont();
    // FUNCTION: GAMEMD 0x433880
    BitFont(const char* filename) throw();
    void Reset();
    void FUN_00434700(); // GAMEMD 0x434700
    bool Intersect(LTRBStruct* out, LTRBStruct* a, LTRBStruct* b); // GAMEMD 0x434840
    void FUN_004348F0(Surface*); // GAMEMD 0x4348F0, legacy spelling
    // FUNCTION: GAMEMD 0x433CE0 — ECX=this, one byte stack argument, RET 4.
    unsigned char SwapFlag(unsigned char value);
    // FUNCTION: GAMEMD 0x434100 — ECX=this, one dword stack argument, RET 4.
    int SwapTabWidth(int value);
    int FUN_00434500(const unsigned short*, int, int, int, int); // GAMEMD 0x434500
    void FUN_00434990(Surface*); // GAMEMD 0x434990, legacy spelling
    short         FUN_00433C70(short color);          // GAMEMD 0x433C70: swaps +0x24, returns the old
    unsigned char FUN_00433C90(unsigned char value);  // GAMEMD 0x433C90: swaps +0x41, returns the old
    void          FUN_00433CA0(const BitFontBounds* bounds);  // GAMEMD 0x433CA0: +0x30..+0x3C, 0 clears
    void          FUN_00433CF0(const unsigned short* text, int* width, int* height,
                               int wrapWidth);         // GAMEMD 0x433CF0: measure text
    unsigned char* GetCharacterBitmap(wchar_t wch);  // GAMEMD 0x4346C0
    int            UnLock(Surface* pSurface);        // GAMEMD 0x434990

    void Lock(Surface* pSurface);                    // GAMEMD 0x4348F0
    void FUN_00434110(int value);                    // GAMEMD 0x434110
    int  FUN_00434120(unsigned short glyph, int x, int y, int color);  // GAMEMD 0x434120

    BitFontInternalData* InternalPTR;  // +0x04
    void*                Pointer_8;    // +0x08
    short*               pGraphBuffer; // +0x0C
    int                  PitchDiv2;    // +0x10
    int                  unknown_14;
    int                  Width;
    int                  unknown_1C;   // +0x1C  line advance, added to the pen y per text line (0x434CD0)
    int                  unknown_20;   // +0x20  written by 0x434110
    unsigned short       unknown_24;   // +0x24  text colour, 0x434CD0 reads it as the draw colour
    short                unknown_26;   // +0x26
    int                  unknown_28;   // +0x28  tab width (0x434CD0 rounds the line width to it)
    int                  unknown_2C;   // +0x2C  glyph spacing added to every advance
    LTRBStruct           Bounds;
    unsigned char        unknown_40;   // +0x40  nonzero: 0x4353F0 draws twice for a doubled stroke
    char                 unknown_41;
    char                 unknown_42[2];
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFont, InternalPTR)  == 0x04);
GG_STATIC_ASSERT(offsetof(BitFont, Pointer_8) == 0x08);
GG_STATIC_ASSERT(offsetof(BitFont, Width) == 0x18);
GG_STATIC_ASSERT(offsetof(BitFont, Bounds) == 0x30);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_41) == 0x41);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFont, pGraphBuffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFont, PitchDiv2)    == 0x10);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_1C)   == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_20)   == 0x20);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_24)   == 0x24);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_26)   == 0x26);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_28)   == 0x28);
GG_STATIC_ASSERT(sizeof(((BitFont*)0)->unknown_28) == 4);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_2C)   == 0x2C);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_40)   == 0x40);
GG_STATIC_ASSERT(sizeof(((BitFont*)0)->unknown_40) == 1);
GG_STATIC_ASSERT(sizeof(BitFont)                 == 0x44);
#endif

#endif  // GG_MATCH_RENDERER_BIT_FONT_H
