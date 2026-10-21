// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Translucent family leaves of Blitter for 16-bit surfaces:
// BlitTranslucent50NonzeroAlpha<us>, BlitTranslucent50ZeroAlpha<us>,
// BlitTranslucentWriteAlpha<us>. Source byte 0 is transparent in all three.
// Cluster b-translucent.
#ifndef GG_MATCH_RENDER_BLITTERS_B_TRANSLUCENT_H
#define GG_MATCH_RENDER_BLITTERS_B_TRANSLUCENT_H

#include "blitter.h"

#include "b_shared_alpha.h"   // BlitAlphaWrapBlock / gg_blit_alpha_wrap_global (0x87E8A4)

// Wrap an alpha-row pointer the way the retail leaves do (re-reads the global).
inline unsigned short* BTranslucentWrapRow(unsigned short* row)
{
    if ((unsigned char*)row >= (unsigned char*)gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// Address view beginning at 0x8A0DD0 over the six DWORD shift operands used by
// WriteAlpha. These bytes share storage with the six scalar shift globals used
// elsewhere; this declaration does not claim separate storage or a full owner.
// The access order follows the instructions in this method; no channel identity
// or enclosing-object extent is asserted here.
struct BTranslucentPixelFormat
{
    int pos0;   // +0x00  0x8A0DD0
    int loss0;  // +0x04  0x8A0DD4
    int pos2;   // +0x08  0x8A0DD8
    int loss2;  // +0x0C  0x8A0DDC
    int pos1;   // +0x10  0x8A0DE0
    int loss1;  // +0x14  0x8A0DE4
};

GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos0) == 0);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss0) == 4);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos2) == 8);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss2) == 0xC);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos1) == 0x10);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss1) == 0x14);
GG_STATIC_ASSERT(sizeof(BTranslucentPixelFormat) == 0x18);

// GLOBAL: GAMEMD 0x8A0DD0
extern "C" BTranslucentPixelFormat gg_b_translucent_pixel_format;

// BlitTranslucent50NonzeroAlpha<unsigned short>  RTTI .?AV?$BlitTranslucent50NonzeroAlpha@G@@
// Draws a pixel only where the source byte is nonzero AND the alpha-row word
// is nonzero: dest = ((table[src] >> 1) & mask) + ((dest >> 1) & mask).
// Allocation: PUSH 0xC before operator new 0x7C8E17 (0x48F64F, in 0x48EBF0);
// inline ctor at 0x48F663..0x48F677 stores table ([owner+0x174]) at +4, the
// 16-bit mask ([owner+0x180]) at +8, then the vptr.
template <class T>
class BlitTranslucent50NonzeroAlpha : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* table;      // +0x04
    unsigned short mask; // +0x08  (+0x0A padding)

    BlitTranslucent50NonzeroAlpha(const T* tbl, unsigned short m) : table(tbl), mask(m) {}
};

// BlitTranslucent50ZeroAlpha<unsigned short>: as above but draws only where the
// alpha-row word is zero. Allocation PUSH 0xC (0x48F681), ctor at 0x48F695..0x48F6A9.
template <class T>
class BlitTranslucent50ZeroAlpha : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* table;      // +0x04
    unsigned short mask; // +0x08  (+0x0A padding)

    BlitTranslucent50ZeroAlpha(const T* tbl, unsigned short m) : table(tbl), mask(m) {}
};

// BlitTranslucentWriteAlpha<unsigned short>: dest = blend(table[src], dest) with
// per-channel weights from the alpha-row word (see source). Allocation: PUSH 8
// (0x48F628), inline ctor stores the vptr and the table ([owner+0x170]) at +4.
template <class T>
class BlitTranslucentWriteAlpha : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* table; // +0x04

    BlitTranslucentWriteAlpha(const T* tbl) : table(tbl) {}
};

// Prefix sizes proven by allocation (PUSH N; CALL 0x7C8E17 in 0x48EBF0): 0xC, 0xC, 8. This does not claim a complete owner layout.
// (sizeof asserts must precede the offsetof ones: VC6 instantiation order quirk.)
typedef BlitTranslucent50NonzeroAlpha<unsigned short> BlitTranslucent50NonzeroAlphaUS_;
typedef BlitTranslucent50ZeroAlpha<unsigned short> BlitTranslucent50ZeroAlphaUS_;
typedef BlitTranslucentWriteAlpha<unsigned short> BlitTranslucentWriteAlphaUS_;
GG_STATIC_ASSERT(sizeof(BlitTranslucent50NonzeroAlphaUS_) == 0xC);
GG_STATIC_ASSERT(sizeof(BlitTranslucent50ZeroAlphaUS_) == 0xC);
GG_STATIC_ASSERT(sizeof(BlitTranslucentWriteAlphaUS_) == 8);

// Member offsets.
GG_STATIC_ASSERT(offsetof(BlitTranslucent50NonzeroAlphaUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(BlitTranslucent50NonzeroAlphaUS_, mask) == 8);
GG_STATIC_ASSERT(offsetof(BlitTranslucent50ZeroAlphaUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(BlitTranslucent50ZeroAlphaUS_, mask) == 8);
GG_STATIC_ASSERT(offsetof(BlitTranslucentWriteAlphaUS_, table) == 4);

#endif // GG_MATCH_RENDER_BLITTERS_B_TRANSLUCENT_H
