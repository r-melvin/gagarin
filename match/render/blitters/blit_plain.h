// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// RTTI TypeDescriptors 0x84E718 (unsigned char) and 0x84E6F8 (unsigned short),
// with COLs 0x80EDE8 and 0x80ED98, identify direct Blitter subclasses at
// offset zero. The table markers below record retail identity/address only;
// this method-only TU emits neither these tables nor deleting destructors.
#ifndef GG_MATCH_RENDER_BLITTERS_BLIT_PLAIN_H
#define GG_MATCH_RENDER_BLITTERS_BLIT_PLAIN_H

#include "blitter.h"

// VTABLE: GAMEMD 0x7F7BDC -- BlitPlain<unsigned char>, five slots; table
// comparison used recorded weak defaults and is conditional, not link proof.
// VTABLE: GAMEMD 0x7F7BC4 -- BlitPlain<unsigned short>, five slots; same scope.

// RTTI identifies BlitPlain<unsigned char> and BlitPlain<unsigned short> as
// direct Blitter subclasses with a zero-offset base. No data members are
// modeled here. The eight reviewed method bodies do not touch object fields;
// the complete object extent is not inferred or asserted by this header.
template <class T>
class BlitPlain : public Blitter
{
public:
    BlitPlain() {}
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
};

#endif // GG_MATCH_RENDER_BLITTERS_BLIT_PLAIN_H
