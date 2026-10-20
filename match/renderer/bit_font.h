// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4346C0 / 0x434990),
//   cross-checked against YRpp BitFont.h / Surface.h (consult-only, no LICENSE;
//   every offset/slot reconfirmed from the disasm).
//
// BitFont — the engine's bitmap-font renderer. Only the two matched methods and
// the members/struct they touch are modelled (the full layout is P2).
#ifndef GG_MATCH_RENDERER_BIT_FONT_H
#define GG_MATCH_RENDERER_BIT_FONT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Surface — the polymorphic blit surface BitFont::UnLock releases. Modelled as
// a pure-virtual interface so cl emits the exact `MOV EAX,[ECX]; CALL [EAX+0x60]`
// indirect-virtual sequence. Only the invoked slot (24 == 0x60, Unlock) carries
// a real signature; the rest merely pin the slot offsets.
//   slot 24 (0x60): Unlock()   — UnLock  CALL [EAX+0x60]
// ---------------------------------------------------------------------------
class Surface
{
public:
    virtual void vf00() = 0;  // 0x00
    virtual void vf04() = 0;  // 0x04
    virtual void vf08() = 0;  // 0x08
    virtual void vf0C() = 0;  // 0x0C
    virtual void vf10() = 0;  // 0x10
    virtual void vf14() = 0;  // 0x14
    virtual void vf18() = 0;  // 0x18
    virtual void vf1C() = 0;  // 0x1C
    virtual void vf20() = 0;  // 0x20
    virtual void vf24() = 0;  // 0x24
    virtual void vf28() = 0;  // 0x28
    virtual void vf2C() = 0;  // 0x2C
    virtual void vf30() = 0;  // 0x30
    virtual void vf34() = 0;  // 0x34
    virtual void vf38() = 0;  // 0x38
    virtual void vf3C() = 0;  // 0x3C
    virtual void vf40() = 0;  // 0x40
    virtual void vf44() = 0;  // 0x44
    virtual void vf48() = 0;  // 0x48
    virtual void vf4C() = 0;  // 0x4C
    virtual void vf50() = 0;  // 0x50
    virtual void vf54() = 0;  // 0x54
    virtual void vf58() = 0;  // 0x58
    virtual void vf5C() = 0;  // 0x5C
    virtual bool Unlock() = 0; // 0x60
};

// ---------------------------------------------------------------------------
// BitFont::InternalData — the loaded font's glyph table. Offsets confirmed from
// GetCharacterBitmap's [ECX+0x14]/[ECX+0x18]/[ECX+0x1c] (where ECX == the
// InternalData* at BitFont+0x4). SymbolTable is loaded with a zero-extending
// 16-bit read (XOR/MOV DX), so it is typed unsigned short*.
// ---------------------------------------------------------------------------
struct BitFontInternalData
{
    char            pad_00[0x14];     // +0x00 (FontWidth..Count, unused here)
    int             SymbolDataSize;   // +0x14
    unsigned short* SymbolTable;      // +0x18
    char*           Bitmaps;          // +0x1C
};
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolDataSize) == 0x14);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolTable) == 0x18);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFontInternalData, Bitmaps)     == 0x1C);
#endif

// ---------------------------------------------------------------------------
// BitFont  (NOVTABLE — retail has its own vtable at +0x00; modelled here as an
// opaque pointer placeholder so the touched members land at their retail
// offsets). Members confirmed numerically:
//   +0x04 InternalPTR    (GetCharacterBitmap MOV ECX,[ECX+0x4])
//   +0x0C pGraphBuffer   (UnLock MOV [ESI+0xC], 0)
//   +0x10 PitchDiv2      (UnLock MOV [ESI+0x10], 0)
// ---------------------------------------------------------------------------
struct BitFont
{
    unsigned char* GetCharacterBitmap(wchar_t wch);  // GAMEMD 0x4346C0
    int            UnLock(Surface* pSurface);        // GAMEMD 0x434990

    void*                __vtable;     // +0x00 (retail vtable pointer)
    BitFontInternalData* InternalPTR;  // +0x04
    void*                Pointer_8;    // +0x08
    short*               pGraphBuffer; // +0x0C
    int                  PitchDiv2;    // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFont, InternalPTR)  == 0x04);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFont, pGraphBuffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFont, PitchDiv2)    == 0x10);
#endif

#endif  // GG_MATCH_RENDERER_BIT_FONT_H
