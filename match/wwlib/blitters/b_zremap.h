// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; method field accesses and allocation-size limits were confirmed in the frozen M2 binary evidence. | YRpp-cross-check
// This is a production method view. It does not claim alpha-pool ownership recovery.
// The two-argument constructors are the owner 0x48EBF0's inline construction: after
// `push 0xC; call 0x7C8E17` each site stores the pointer at +4, the second value at +8
// and the vptr, nothing else. blitter_ddtors_lucent_methods.cpp instantiates them to
// emit the vtables and scalar deleting destructors.
#ifndef GG_MATCH_RENDER_BLITTERS_B_ZREMAP_H
#define GG_MATCH_RENDER_BLITTERS_B_ZREMAP_H

#include <stddef.h>
#include "blitter.h"
#include "r_shared_zwrap.h"
#include "b_shared_alpha.h"

// Retail owner allocations: PUSH 0xC at 0x48EC45 (byte specialization) and
// 0x48F099 (word specialization), each followed by operator-new at +5.
template <class T> class BlitTransZRemapXlat : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    BlitTransZRemapXlat(const unsigned char* const* x, const T* r) : xlat(x), remap(r) {}
};
typedef BlitTransZRemapXlat<unsigned char> BlitTransZRemapXlatUC_;
typedef BlitTransZRemapXlat<unsigned short> BlitTransZRemapXlatUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatUC_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatUC_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatUC_, remap) == 0x08);
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatUS_, remap) == 0x08);

// Retail owner allocation: PUSH 0xC at 0x48F1C1, followed by operator-new
// at 0x48F1C6; the initialized object fields are at +4 and +8.
template <class T> class BlitTransZRemapXlatZRead : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    BlitTransZRemapXlatZRead(const unsigned char* const* x, const T* r) : xlat(x), remap(r) {}
};
typedef BlitTransZRemapXlatZRead<unsigned short> BlitTransZRemapXlatZReadUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatZReadUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatZReadUS_, remap) == 0x08);

// Retail owner allocation: PUSH 0xC at 0x48F376, followed by operator-new
// at 0x48F37B; this is the ZReadWrite object (not the separate +0x58 object).
template <class T> class BlitTransZRemapXlatZReadWrite : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    BlitTransZRemapXlatZReadWrite(const unsigned char* const* x, const T* r) : xlat(x), remap(r) {}
};
typedef BlitTransZRemapXlatZReadWrite<unsigned short> BlitTransZRemapXlatZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatZReadWriteUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatZReadWriteUS_, remap) == 0x08);

// Retail owner allocation: PUSH 0x10 at 0x48F4D1, followed by operator-new
// at 0x48F4D6; fields are initialized at +4, +8 and +0xC.
template <class T> class BlitTransZRemapXlatAlpha : public Blitter {
public:
    virtual ~BlitTransZRemapXlatAlpha();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    unsigned short* alpha;            // +0x0C
};
typedef BlitTransZRemapXlatAlpha<unsigned short> BlitTransZRemapXlatAlphaUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatAlphaUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaUS_, remap) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaUS_, alpha) == 0x0C);

// Retail owner allocation: PUSH 0x10 at 0x48F733, followed by operator-new
// at 0x48F73B; fields are initialized at +4, +8 and +0xC.
template <class T> class BlitTransZRemapXlatAlphaZRead : public Blitter {
public:
    virtual ~BlitTransZRemapXlatAlphaZRead();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    unsigned short* alpha;            // +0x0C
};
typedef BlitTransZRemapXlatAlphaZRead<unsigned short> BlitTransZRemapXlatAlphaZReadUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatAlphaZReadUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadUS_, remap) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadUS_, alpha) == 0x0C);

// Retail owner allocation: PUSH 0x10 at 0x48F9BE, followed by operator-new
// at 0x48F9C6; fields are initialized at +4, +8 and +0xC.
template <class T> class BlitTransZRemapXlatAlphaZReadWrite : public Blitter {
public:
    virtual ~BlitTransZRemapXlatAlphaZReadWrite();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const unsigned char* const* xlat; // +0x04
    const T* remap;                   // +0x08
    unsigned short* alpha;            // +0x0C
};
typedef BlitTransZRemapXlatAlphaZReadWrite<unsigned short> BlitTransZRemapXlatAlphaZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(BlitTransZRemapXlatAlphaZReadWriteUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadWriteUS_, remap) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransZRemapXlatAlphaZReadWriteUS_, alpha) == 0x0C);

#endif
