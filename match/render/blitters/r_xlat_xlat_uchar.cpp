// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
#include "r_xlat.h"

// TEMPLATE: GAMEMD 0x491820
// Span: 0x7e bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlat<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransXlat<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int, unsigned short*, unsigned short*, int, int,
                                  const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);

    // Left clip: a nonzero byte uses one skip, a zero byte is followed by a
    // transparent run. An overshoot past zero is transparent output.
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d++ = table[c];
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x4918a0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlat<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransXlat<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

template class RLEBlitTransXlat<unsigned char>;
