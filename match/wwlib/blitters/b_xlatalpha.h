// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M2 retail-binary method evidence. This is a touched-field | YRpp-cross-check
// and virtual-method view for unsigned-short TransXlat alpha leaves, not a
// recovered complete lifetime implementation.
#ifndef GG_MATCH_RENDER_BLITTERS_B_XLATALPHA_H
#define GG_MATCH_RENDER_BLITTERS_B_XLATALPHA_H

#include "blitter.h"
#include "b_shared_alpha.h"

// Alpha-row wrapping uses the observed fields of the global pointer at 0x87E8A4.
inline unsigned short* BlitAlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// The following classes declare the virtual slots implemented in this method
// subset. No VTABLE annotation or table-emission claim is made here.

template <class T>
class BlitTransXlatAlpha : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;               // touched at +0x04
    unsigned short* alpha;       // touched at +0x08
    BlitTransXlatAlpha(const T* table, void* handle); // declaration only
    ~BlitTransXlatAlpha();       // declaration only
};

template <class T>
class BlitTransXlatAlphaZRead : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;               // touched at +0x04
    unsigned short* alpha;       // touched at +0x08
    BlitTransXlatAlphaZRead(const T* table, void* handle); // declaration only
    ~BlitTransXlatAlphaZRead();  // declaration only
};

template <class T>
class BlitTransXlatAlphaZReadWrite : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;               // touched at +0x04
    unsigned short* alpha;       // touched at +0x08
    BlitTransXlatAlphaZReadWrite(const T* table, void* handle); // declaration only
    ~BlitTransXlatAlphaZReadWrite(); // declaration only
};

template <class T>
class BlitTransXlatWriteAlpha : public Blitter
{
public:
    BlitTransXlatWriteAlpha() {}
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
};

template <class T>
class BlitTransXlatMultWriteAlpha : public Blitter
{
public:
    BlitTransXlatMultWriteAlpha() {}
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
};

typedef BlitTransXlatAlpha<unsigned short> BlitTransXlatAlphaUS_;
typedef BlitTransXlatAlphaZRead<unsigned short> BlitTransXlatAlphaZReadUS_;
typedef BlitTransXlatAlphaZReadWrite<unsigned short> BlitTransXlatAlphaZReadWriteUS_;
typedef BlitTransXlatWriteAlpha<unsigned short> BlitTransXlatWriteAlphaUS_;
typedef BlitTransXlatMultWriteAlpha<unsigned short> BlitTransXlatMultWriteAlphaUS_;
GG_STATIC_ASSERT(sizeof(BlitTransXlatAlphaUS_) == 12);
GG_STATIC_ASSERT(sizeof(BlitTransXlatAlphaZReadUS_) == 12);
GG_STATIC_ASSERT(sizeof(BlitTransXlatAlphaZReadWriteUS_) == 12);
GG_STATIC_ASSERT(sizeof(BlitTransXlatWriteAlphaUS_) == 4);
GG_STATIC_ASSERT(sizeof(BlitTransXlatMultWriteAlphaUS_) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaZReadUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaZReadUS_, alpha) == 8);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaZReadWriteUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransXlatAlphaZReadWriteUS_, alpha) == 8);

#endif
