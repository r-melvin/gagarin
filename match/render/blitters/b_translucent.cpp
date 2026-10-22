// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
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
// PARTIAL 0x494690 BlitTranslucentWriteAlpha<us>::BlitCopy 88.0% (125/142 instruction
// positions; multiset identical, 427/501 raw bytes): dest and src are the running
// pointers themselves (parameters advanced in place, no d/s locals), while `abuf`
// and the count are copied to locals `ap` and `n` ahead of use, which is what makes
// retail's self-stores of the abuf and len slots appear. Residual: retail evaluates
// the channel-0 term first and keeps it in EDX with the cached pos0/loss0 registers
// (EBX/EBP) for the final OR, and loads dc[0] before sc[0] for the first multiply;
// ours shifts the third channel first through memory loads and swaps EAX/EDX in the
// first multiply. Measured with no effect: all 6 declaration orders of r/g/b, all 6
// clamp orders, g2 temp or in-place, all 8 per-channel sum operand orders, all 6 OR
// operand orders (plain and parenthesised), and building the pixel in a local.
#include "b_translucent.h"


// TEMPLATE: GAMEMD 0x494690
// BlitTranslucentWriteAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                int a = *ap;
                int ia = 255 - a;
                if (a == 255) a = 256;
                unsigned char sc[3];
                unsigned char dc[3];
                T sp = table[c];
                sc[0] = (sp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                sc[1] = (sp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                sc[2] = (sp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                T dp = *(T*)dest;
                dc[0] = (dp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                dc[1] = (dp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                dc[2] = (dp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                int r = (dc[0] * ia + sc[0] * a) >> 8;
                int g = (dc[1] * ia + sc[1] * a) >> 8;
                int b = (dc[2] * ia + sc[2] * a) >> 8;
                if (b > 255) b = 255;
                int g2 = g > 255 ? 255 : g;
                if (r > 255) r = 255;
                *(T*)dest = ((r >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0)
                   | ((g2 >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1)
                   | ((b >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
            }
            dest = (T*)dest + 1;
            ap = BTranslucentWrapRow(ap + 1);
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
// SYNTHETIC: GAMEMD 0x49A3C0
// BlitTranslucentWriteAlpha<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A3E0
// BlitTranslucent50NonzeroAlpha<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A400
// BlitTranslucent50ZeroAlpha<unsigned short> scalar deleting destructor
