// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Lucent50 (50% translucent) method subset of Blitter, <unsigned short> only.
// The source byte is looked up in a 16-bit table (+4) and averaged with the
// destination pixel: ((a >> 1) & mask) + ((b >> 1) & mask). Alpha methods use
// 256-word rows at +8. Constructor/destructor bodies are outside this subset.
#ifndef GG_MATCH_RENDER_BLITTERS_B_LUCENT50_H
#define GG_MATCH_RENDER_BLITTERS_B_LUCENT50_H

#include "blitter.h"
#include "b_shared_alpha.h"

// One 256-word alpha row (index = source byte, row = alpha level).
struct BlitAlphaRow256
{
    unsigned short v[256];
};
GG_STATIC_ASSERT(sizeof(BlitAlphaRow256) == 0x200);
GG_STATIC_ASSERT(offsetof(BlitAlphaRow256, v) == 0);

// BlitTransLucent50<unsigned short>  RTTI .?AV?$BlitTransLucent50@G@@
// Retail construction passes 0xC bytes to operator new. The methods read the
// table at +4 and the 16-bit mask at +8. Constructor implementation is outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E59C0 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50 : public Blitter
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

    const T* xlat;                    // +0x04
    unsigned short mask;              // +0x08

    BlitTransLucent50(const T* table, unsigned short m) : xlat(table), mask(m) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50<unsigned short>) == 0xC);

// BlitTransLucent50ZRead<unsigned short>  RTTI .?AV?$BlitTransLucent50ZRead@G@@
// Retail construction passes 0xC bytes to operator new. The methods read the
// table at +4 and the 16-bit mask at +8. Constructor implementation is outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E5918 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50ZRead : public Blitter
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

    const T* xlat;                    // +0x04
    unsigned short mask;              // +0x08

    BlitTransLucent50ZRead(const T* table, unsigned short m) : xlat(table), mask(m) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50ZRead<unsigned short>) == 0xC);

// BlitTransLucent50ZReadWarp<unsigned short>  RTTI .?AV?$BlitTransLucent50ZReadWarp@G@@
// Retail construction passes 0xC bytes to operator new. The methods read the
// table at +4 and the 16-bit mask at +8. Constructor implementation is outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E58D0 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50ZReadWarp : public Blitter
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

    const T* xlat;                    // +0x04
    unsigned short mask;              // +0x08

    BlitTransLucent50ZReadWarp(const T* table, unsigned short m) : xlat(table), mask(m) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50ZReadWarp<unsigned short>) == 0xC);

// BlitTransLucent50ZReadWrite<unsigned short>  RTTI .?AV?$BlitTransLucent50ZReadWrite@G@@
// Retail construction passes 0xC bytes to operator new. The methods read the
// table at +4 and the 16-bit mask at +8. Constructor implementation is outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E5828 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50ZReadWrite : public Blitter
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

    const T* xlat;                    // +0x04
    unsigned short mask;              // +0x08

    BlitTransLucent50ZReadWrite(const T* table, unsigned short m) : xlat(table), mask(m) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50ZReadWrite<unsigned short>) == 0xC);

// BlitTransLucent50Alpha<unsigned short>  RTTI .?AV?$BlitTransLucent50Alpha@G@@
// Retail construction passes 0x10 bytes to operator new. The methods read the
// table at +4, alpha rows at +8 and 16-bit mask at +0xC. Constructor/destructor
// implementation and pool ownership are outside this method-only candidate.
// VTABLE: GAMEMD 0x7E5798 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50Alpha : public Blitter
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

    const T* xlat;                    // +0x04
    const BlitAlphaRow256* alpha;     // +0x08, methods read 256-word rows
    unsigned short mask;              // +0x0C

    BlitTransLucent50Alpha(const T* table, const BlitAlphaRow256* rows, unsigned short m);
    ~BlitTransLucent50Alpha();
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50Alpha<unsigned short>) == 0x10);

// BlitTransLucent50AlphaZRead<unsigned short>  RTTI .?AV?$BlitTransLucent50AlphaZRead@G@@
// Retail construction passes 0x10 bytes to operator new. The methods read the
// table at +4, alpha rows at +8 and 16-bit mask at +0xC. Constructor/destructor
// implementation and pool ownership are outside this method-only candidate.
// VTABLE: GAMEMD 0x7E56A8 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50AlphaZRead : public Blitter
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

    const T* xlat;                    // +0x04
    const BlitAlphaRow256* alpha;     // +0x08, methods read 256-word rows
    unsigned short mask;              // +0x0C

    BlitTransLucent50AlphaZRead(const T* table, const BlitAlphaRow256* rows, unsigned short m);
    ~BlitTransLucent50AlphaZRead();
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50AlphaZRead<unsigned short>) == 0x10);

// BlitTransLucent50AlphaZReadWarp<unsigned short>  RTTI .?AV?$BlitTransLucent50AlphaZReadWarp@G@@
// Retail construction passes 0x10 bytes to operator new. The methods read the
// table at +4, alpha rows at +8 and 16-bit mask at +0xC. Constructor/destructor
// implementation and pool ownership are outside this method-only candidate.
// VTABLE: GAMEMD 0x7E5660 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50AlphaZReadWarp : public Blitter
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

    const T* xlat;                    // +0x04
    const BlitAlphaRow256* alpha;     // +0x08, methods read 256-word rows
    unsigned short mask;              // +0x0C

    BlitTransLucent50AlphaZReadWarp(const T* table, const BlitAlphaRow256* rows, unsigned short m);
    ~BlitTransLucent50AlphaZReadWarp();
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50AlphaZReadWarp<unsigned short>) == 0x10);

// BlitTransLucent50AlphaZReadWrite<unsigned short>  RTTI .?AV?$BlitTransLucent50AlphaZReadWrite@G@@
// Retail construction passes 0x10 bytes to operator new. The methods read the
// table at +4, alpha rows at +8 and 16-bit mask at +0xC. Constructor/destructor
// implementation and pool ownership are outside this method-only candidate.
// VTABLE: GAMEMD 0x7E55E8 (identity only; probe-only, no production emission claim)
template <class T>
class BlitTransLucent50AlphaZReadWrite : public Blitter
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

    const T* xlat;                    // +0x04
    const BlitAlphaRow256* alpha;     // +0x08, methods read 256-word rows
    unsigned short mask;              // +0x0C

    BlitTransLucent50AlphaZReadWrite(const T* table, const BlitAlphaRow256* rows, unsigned short m);
    ~BlitTransLucent50AlphaZReadWrite();
};

GG_STATIC_ASSERT(sizeof(BlitTransLucent50AlphaZReadWrite<unsigned short>) == 0x10);

// Member offsets (typedefs: VC6 rejects offsetof on a template-id inside the macro).
typedef BlitTransLucent50<unsigned short> BlitTransLucent50US_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50US_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50US_, mask) == 8);
typedef BlitTransLucent50ZRead<unsigned short> BlitTransLucent50ZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadUS_, mask) == 8);
typedef BlitTransLucent50ZReadWarp<unsigned short> BlitTransLucent50ZReadWarpUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadWarpUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadWarpUS_, mask) == 8);
typedef BlitTransLucent50ZReadWrite<unsigned short> BlitTransLucent50ZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadWriteUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50ZReadWriteUS_, mask) == 8);
typedef BlitTransLucent50Alpha<unsigned short> BlitTransLucent50AlphaUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaUS_, mask) == 0xC);
typedef BlitTransLucent50AlphaZRead<unsigned short> BlitTransLucent50AlphaZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadUS_, mask) == 0xC);
typedef BlitTransLucent50AlphaZReadWarp<unsigned short> BlitTransLucent50AlphaZReadWarpUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWarpUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWarpUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWarpUS_, mask) == 0xC);
typedef BlitTransLucent50AlphaZReadWrite<unsigned short> BlitTransLucent50AlphaZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWriteUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWriteUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransLucent50AlphaZReadWriteUS_, mask) == 0xC);

#endif // GG_MATCH_RENDER_BLITTERS_B_LUCENT50_H
