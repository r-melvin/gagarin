// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// /GX is off for this TU: /O2 /DNDEBUG /Gy /GX emits non-retail bodies. Cluster b-translucent:
// BlitTranslucent50NonzeroAlpha<us>, BlitTranslucent50ZeroAlpha<us>,
// BlitTranslucentWriteAlpha<us>. Slots 2-4 are forwarding shims (slot 1, warp = 0).
// Entry-origin CFG-closed spans (entry, length):
//   50NonzeroAlpha<us> BlitCopy 0x494920 (0x83)
//   50ZeroAlpha<us>    BlitCopy 0x494A40 (0x83)
//   WriteAlpha<us>     BlitCopy 0x494690 (0x1F5; frozen partial)
//
// Candidate rows cover the twelve native method bodies in this source only.
// Compiler-emitted constructor/destructor and vtable COMDATs are not claimed by
// the function rows; harness-only deleting-wrapper evidence is excluded.
// Levers that matched the 50% pair: copy abuf into a local (`ap`) BEFORE the
// `if (len > 0)`; wrap the alpha row through the inline BTranslucentWrapRow(ap + 1)
// after ++d (retail adds to abuf second); table/mask read inside the loop.
// CAP 0x494690 BlitTranslucentWriteAlpha<us>::BlitCopy 60.8%: 142 retail vs 143
// compiled instructions; multiset delta retail-only {lea 1}, compiled-only
// {mov 1, add 1} (retail forms abuf+2 with LEA into a fresh register). Frame size
// (0x18), the unsigned char[3] src/dest channel arrays, clamp order (b,g,r with a
// ternary for g) and every IMUL/SAR/OR all match. Remaining gap: retail keeps dest,
// src and the counter in their own argument slots, spills `this` and stores abuf
// back to its own slot at entry; we spill c into the src slot and keep s separate.
// Tried: all s/d/n declaration orders, abuf direct vs `ap` copy at top / in the if
// (copy gives 5%, +3 MOV), explicit wrap-global local vs direct, len as counter,
// c/sc/dc declared at function scope in all orders, 6 clamp orders, wrap written
// as helper / inline / temp pointer (compiler normalises all to the same bytes).
#include "b_translucent.h"


// TEMPLATE: GAMEMD 0x494690
// BlitTranslucentWriteAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    if (len > 0) {
        int n = len;
        T* d = (T*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            unsigned char c = *s++;
            if (c) {
                int a = *abuf;
                int ia = 255 - a;
                if (a == 255) a = 256;
                unsigned char sc[3];
                unsigned char dc[3];
                T sp = table[c];
                sc[0] = (sp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                sc[1] = (sp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                sc[2] = (sp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                T dp = *d;
                dc[0] = (dp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                dc[1] = (dp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                dc[2] = (dp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                int r = (dc[0] * ia + sc[0] * a) >> 8;
                int g = (dc[1] * ia + sc[1] * a) >> 8;
                int b = (dc[2] * ia + sc[2] * a) >> 8;
                if (b > 255) b = 255;
                int g2 = g > 255 ? 255 : g;
                if (r > 255) r = 255;
                *d = ((r >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0)
                   | ((g2 >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1)
                   | ((b >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
            }
            ++d;
            abuf = BTranslucentWrapRow(abuf + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x494890
// BlitTranslucentWriteAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4948C0
// BlitTranslucentWriteAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4948F0
// BlitTranslucentWriteAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494920
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        T* d = (T*)dest;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c && *ap) {
                T m = mask;
                *d = ((table[c] >> 1) & m) + ((*d >> 1) & m);
            }
            ++d;
            ap = BTranslucentWrapRow(ap + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x4949B0
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4949E0
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494A10
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494A40
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        T* d = (T*)dest;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c && !*ap) {
                T m = mask;
                *d = ((table[c] >> 1) & m) + ((*d >> 1) & m);
            }
            ++d;
            ap = BTranslucentWrapRow(ap + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x494AD0
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494B00
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494B30
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// VC6 requires class instantiation to emit these member bodies. The object also
// contains compiler-generated support COMDATs; they are not reviewed candidate
// rows and no deleting-wrapper/vtable ownership is claimed here.
template class BlitTranslucent50NonzeroAlpha<unsigned short>;
template class BlitTranslucent50ZeroAlpha<unsigned short>;
template class BlitTranslucentWriteAlpha<unsigned short>;
