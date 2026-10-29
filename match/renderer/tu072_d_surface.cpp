// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU072 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4ba3b0-0x4c1b7f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail-compatible DSurface methods; no constructors or deleting wrapper.
//   Provenance note: frozen M2 entry-origin bodies, checked against retail.
//
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
//   Provenance note: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4)
// rectangle fill and Copy_From overrides that go through the DirectDraw Blt; spans are CFG-closed.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names.
//
// Small leaves (64 bytes or less) between 0x470000 and 0x500000 that other
// translation units already declared as callees but nothing defined.
//
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
//   Provenance note: own-binary-via-Ghidra. DSurface::CopyFrom (slot +0x0C, RTTI .?AVDSurface@@, vtable
// 0x7E85D4): the DirectDraw hardware blit with both clip rectangles. Retail inlines two copies of the
// rectangle intersection (the out-of-line body is 0x421B60) and one blit-rectangle clip call (0x7BBE20).
//
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
//   Provenance note: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4) slot +0x34 at 0x4BFD30:
// a Bresenham line on a 16-bit surface that is depth-tested against the Z buffer (global 0x887644) and
// tinted by the buffer at global 0x87E8A4; both observed buffers use circular wrapping. This is a readable
// partial candidate; the function's full control-flow extent is longer than the earlier saved span.
//
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
//   Provenance note: own-binary-via-Ghidra. DSurface::unknown_38 (slot +0x38, 0x4BBCA0): a clipped, Z-buffer tested
// line draw on 16-bit surfaces that brightens the destination pixels by `brightness`/256. Read from the retail
// entry disassembly at 0x4BBCA0; the earlier candidate span is shorter than the current CFG extent.
//
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
//   Provenance note: own-binary-via-Ghidra. DSurface slot +0x90 (0x4BF750, DSurface-only): a clipped line on a 16-bit
// surface whose colour is blended between two 3-byte colours; the blend factor ping-pongs in [0,1] by a step.
// Span CFG-closed from the entry disassembly.
//
// DSurface destructor body (non-deleting; four direct callers). Retail seats
// the DSurface table 0x7E85D4, detaches the shared primary clipper when this
// is the primary surface, frees the surface description, releases the
// DirectDraw surface, then seats the Surface table 0x7E2198 (the empty
// XSurface/Surface destructors inline away).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <string.h>
#include "dsurface_class.h"

#include "../core/global_getter_family_methods.h"

#include <string.h>
#include "dsurface_class.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" size_t __cdecl strlen(const char* s);
#pragma intrinsic(strlen)

// GLOBAL: GAMEMD 0x00A8ED84
extern "C" int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x00AA0738
extern "C" int DAT_00AA0738;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern "C" const char* const DAT_007E1B60[5];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern "C" const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x0081DA28 (twelve string pointers)
extern "C" const char* const DAT_0081DA28[12];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
// 0x5117D0: name -> index, -1 when absent (callee only).
int FUN_005117D0(const char* name);

// ---------------------------------------------------------------------------

#include "../_layout/obj_00483460.h"

#include "../_layout/obj_00485060.h"

#include "../_layout/obj_004870b0.h"

#include "../_layout/pair_00487f20.h"

#include "../_layout/obj_0048ba80.h"

#include "../_layout/obj_004a1d30.h"

#include "../_layout/obj_004a50f0.h"

#include "../_layout/pair_004c1b50.h"

#include "../_layout/obj_004c91c0.h"

#include "../_layout/obj_004ca160.h"

// GLOBAL: GAMEMD 0x0085D0A4 (4096-entry float table)
extern "C" const float DAT_0085D0A4[4096];

#include "../_layout/obj_004e1100.h"

struct Obj_004D2790;

struct Vtbl_004D2790;

#include "../_layout/obj_004d2790.h"


#include "../_layout/vtbl_004d2790.h"

#include "../_layout/record_004d2790.h"

// 0x7C5F3D and 0x7C5FFF: runtime-library helpers with no binary name; the
// first returns a byte (callees only).
extern "C" char __cdecl FUN_007C5F3D();
extern "C" void __cdecl FUN_007C5FFF();
extern "C" char* __cdecl strncpy(char* dst, const char* src, size_t count);

// GLOBAL: GAMEMD 0x0084E863
extern "C" signed char DAT_0084E863;
// GLOBAL: GAMEMD 0x0084E865
extern "C" const char DAT_0084E865[];


extern "C" char* __cdecl strcpy(char* dst, const char* src);
#pragma intrinsic(strcpy)
extern "C" char* __cdecl _strupr(char* text);

#include "../_layout/text_004f4cb0.h"

#include "../_layout/obj_004f4c20.h"

#include "dsurface_class.h"

// The inline form of 0x421B60: `b` clipped to `a`, an all-zero rectangle when nothing is left. The adjustment
// pointers of the out-of-line form are null at the two inlined uses and left out.
static inline RectangleStruct Intersect(const RectangleStruct* a, const RectangleStruct* b)
{
    RectangleStruct r = {0, 0, 0, 0};
    if (a->Width <= 0 || a->Height <= 0 || b->Width <= 0 || b->Height <= 0)
        return r;
    RectangleStruct t = *b;
    if (t.X < a->X) {
        t.Width += t.X - a->X;
        t.X = a->X;
    }
    if (t.Width < 1)
        return r;
    if (t.Y < a->Y) {
        t.Height += t.Y - a->Y;
        t.Y = a->Y;
    }
    if (t.Height < 1)
        return r;
    if (t.X + t.Width > a->X + a->Width)
        t.Width = a->X - t.X + a->Width;
    if (t.Width < 1)
        return r;
    if (t.Y + t.Height > a->Y + a->Height)
        t.Height = a->Y + a->Height - t.Y;
    if (t.Height < 1)
        return r;
    r = t;
    return r;
}

#include <math.h>
#include "dsurface_class.h"
#include "drawing.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

#pragma function(sqrt)

// Circular row buffer object behind the Z buffer (0x887644) and the alpha buffer (0x87E8A4). Only the fields
// the line reads are modelled: +0x04 / +0x24 / +0x28 locate the pixel origin, +0x18 / +0x1C bound the
// buffer, +0x20 is the wrap distance in bytes (evidence: 0x4C02A1, 0x4C02A6..0x4C02B0, 0x4C0065).
struct WrapBuffer_004BFD30
{
    unsigned char unknown_00[4];
    int Top;                      // +0x04
    unsigned char unknown_08[0x10];
    unsigned short* WrapBegin;    // +0x18
    unsigned short* WrapEnd;      // +0x1C
    unsigned int WrapStep;        // +0x20
    unsigned short Origin;        // +0x24
    unsigned char unknown_26[2];
    int RowStride;                // +0x28 (in 16-bit units)
};
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((WrapBuffer_004BFD30*)0)->unknown_08) == 0x10);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapBegin) == 0x18);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapEnd) == 0x1C);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapStep) == 0x20);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, Origin) == 0x24);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, RowStride) == 0x28);
GG_STATIC_ASSERT(sizeof(WrapBuffer_004BFD30) == 0x2C);

// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- see dsurface.h (pair 0 = byte 0, pair 2 = byte 1, pair 1 = byte 2).
// Declaration: GAMEMD 0x4CAC40 (decl; reloc) -- unresolved engine table helper.
// LIBRARY: _ftol (0x7C5F00).

static inline unsigned short* WrapRow(WrapBuffer_004BFD30* buf, unsigned short* p, int step)
{
    if (step > 0) {
        if (p >= buf->WrapEnd)
            p = (unsigned short*)((char*)p - buf->WrapStep);
    } else if (p < buf->WrapBegin) {
        p = (unsigned short*)((char*)p + buf->WrapStep);
    }
    return p;
}

static inline int Distance(int dx, int dy)
{
    return (int)sqrt((double)dx * (double)dx + (double)dy * (double)dy);
}

static inline unsigned short Shade(unsigned int alpha, unsigned int ch0, unsigned int ch1, unsigned int ch2)
{
    return (unsigned short)((((int)(alpha * ch0) >> 7) >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
           (unsigned short)((((int)(alpha * ch2) >> 7) >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1) |
           (unsigned short)((((int)(alpha * ch1) >> 7) >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
}

#include <stdlib.h>
#include "dsurface_class.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"

// Address-scoped prefix view for data read through 0x887644. Only method-accessed fields are represented; offsets are read from
// the instructions at 0x4BBF2D..0x4BC2B0.
struct ZBufferLike_004BBCA0
{
    int unknown_00;                // +0x00
    int Top;                       // +0x04
    int unknown_08[3];             // +0x08
    int unknown_14;                // +0x14
    unsigned short* Low;           // +0x18 wrap lower bound
    unsigned short* High;          // +0x1C wrap upper bound
    int Size;                      // +0x20 wrap size in bytes
    short Extent;                  // +0x24
    short unknown_26;              // +0x26
    int Stride;                    // +0x28 row stride in depth words
};
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((ZBufferLike_004BBCA0*)0)->unknown_08) == 0x0C);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Low) == 0x18);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, High) == 0x1C);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Size) == 0x20);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Extent) == 0x24);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Stride) == 0x28);
GG_STATIC_ASSERT(sizeof(ZBufferLike_004BBCA0) == 0x2C);

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E85A8
extern const double DAT_007E85A8;
// GLOBAL: GAMEMD 0x8A0968
extern double DAT_008A0968;

// SYNTHETIC: GAMEMD 0x4BA3E0
// GLOBAL: GAMEMD 0x8A0DC0
double DAT_008A0DC0 = DAT_008A0968 / DAT_007E85A8;

// SYNTHETIC: GAMEMD 0x4BA400
// GLOBAL: GAMEMD 0x8A0DA8
double DAT_008A0DA8 = DAT_007E1718 / DAT_008A0DC0;

// FUNCTION: GAMEMD 0x4C1B50 (decl; reloc). fastcall: ECX = vector, returns (int)FUN_004CAC40(x*x + y*y).
struct LengthVector : public Point2D
{
    int Length() const;
};

// Declaration: GAMEMD 0x4CAC40 (decl; reloc). Engine table helper; stacked argument, ST0 result.
// Zero takes the equality path; negative input follows sign adjustment and table lookup.
double __cdecl FUN_004CAC40(double value);

static inline void StepRowUp(unsigned short*& zp, int step, ZBufferLike_004BBCA0* zb)
{
    zp += step;
    if (step <= 0) {
        if (zp < zb->Low)
            zp = (unsigned short*)((char*)zp + zb->Size);
    } else if (zp >= zb->High)
        zp = (unsigned short*)((char*)zp - zb->Size);
}

static inline void StepColumn(unsigned short*& zp, ZBufferLike_004BBCA0* zb)
{
    zp += 1;
    if (zp >= zb->High)
        zp = (unsigned short*)((char*)zp - zb->Size);
}

static inline void Brighten(unsigned short* pixel, int brightness)
{
    unsigned short old = *pixel;
    unsigned char c0 = (old >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
    unsigned char c2 = (old >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
    unsigned char c1 = (old >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
    int r = c0 + ((c0 * brightness) >> 8);
    int g = c2 + ((c2 * brightness) >> 8);
    int b = c1 + ((c1 * brightness) >> 8);
    if (b > 255)
        b = 255;
    if (g > 255)
        g = 255;
    if (r > 255)
        r = 255;
    *pixel = ((r >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
             ((g >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2) |
             ((b >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1);
}

#include <stdlib.h>
#include "dsurface_class.h"

// FUNCTION: GAMEMD 0x661020 (decl; reloc). thiscall colour blend: ECX = 3-byte result, stack = (colour a, colour b,
// float t by value), RET 0xC, returns the result pointer. Not in the surface cluster's reserved list.
struct BlendedColor
{
    unsigned char Channel[3];
    BlendedColor* Blend(const unsigned char* a, const unsigned char* b, float t);
};

static inline unsigned short PackPixel(const BlendedColor& c)
{
    return (c.Channel[0] >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0 |
           (c.Channel[1] >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1 |
           (c.Channel[2] >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2;
}

// Pixel for the current blend factor.
static inline unsigned short PixelAt(const unsigned char* a, const unsigned char* b, float* blend)
{
    BlendedColor mixer;
    BlendedColor c = *mixer.Blend(a, b, *blend);
    return PackPixel(c);
}

// Advance the blend factor; the step reverses direction at 0 and 1.
static inline void Advance(float* step, float* blend)
{
    float next = *step + *blend;
    *blend = next;
    if (next >= 0.0f || *step >= 0.0f) {
        if (next > 1.0f && *step > 0.0f) {
            *blend = 1.0f;
            *step = -*step;
        }
    } else {
        *blend = 0.0f;
        *step = -*step;
    }
}

#include "dsurface_class.h"

// GLOBAL: GAMEMD 0x8A0DCC -- the clipper attached to the primary surface.
extern "C" DDClipper* DAT_008A0DCC;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BA6B0
DSurface::~DSurface()
{
    if (IsPrimary && DDSurf != 0 && DAT_008A0DCC != 0) {
        DDSurf->lpVtbl->SetClipper(DDSurf, 0);
        DAT_008A0DCC->lpVtbl->Release(DAT_008A0DCC);
        DAT_008A0DCC = 0;
    }

    operator delete(Desc);
    Desc = 0;

    if (DDSurf != 0) {
        DDSurf->lpVtbl->Release(DDSurf);
    }
    DDSurf = 0;
}

// FUNCTION: GAMEMD 0x4BACF0
// Takes a device context from the DirectDraw surface when it is not locked; returns it, or 0.
void* DSurface::FUN_004BACF0()
{
    void* dc = 0;
    if (!IsLocked()) {
        if (!DDSurf->lpVtbl->GetDC(DDSurf, &dc))
            ++LockLevel;
        else
            return 0;
    }
    return dc;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAD60
int DSurface::GetBytesPerPixel()
{
    return BytesPerPixel;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAD70
unsigned int DSurface::GetPitch()
{
    return Desc->lPitch;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAD80
void* DSurface::Lock(Point2D origin)
{
    if (!DAT_0089F978 && !DAT_00A8ED80)
        return 0;
    if (!Recover())
        return 0;
    if (origin.X < 0 || origin.Y < 0)
        return 0;
    if (LockLevel == 0) {
        DDSurfaceDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (DDSurf->lpVtbl->Lock(DDSurf, 0, &desc, 1, 0))
            return 0;
        *Desc = desc;
        BytesPerPixel = (Desc->dwRGBBitCount + 7) >> 3;
        InVideoMemory = (Desc->dwCaps >> 14) & 1;
        Buffer = Desc->lpSurface;
    }
    ++LockLevel;
    return (char*)Buffer + (GetPitch() * origin.Y + GetBytesPerPixel() * origin.X);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAEC0
bool DSurface::unknown_64(unsigned int, unsigned int)
{
    if (LockLevel == 0) {
        DDSurfaceDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (DDSurf->lpVtbl->Lock(DDSurf, 0, &desc, 0, 0))
            return false;
        DDSurf->lpVtbl->Unlock(DDSurf, desc.lpSurface);
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAF20
bool DSurface::unknown_94()
{
    return DDSurf->lpVtbl->GetBltStatus(DDSurf, 1) == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BAF40
bool DSurface::Unlock()
{
    if (DAT_0089F978 || DAT_00A8ED80)
        Recover();
    if (LockLevel > 0) {
        if (--LockLevel == 0) {
            DDSurf->lpVtbl->Unlock(DDSurf, Buffer);
            Buffer = 0;
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4BB000
// Reports whether the surface is usable: restores a lost DirectDraw surface and, if it was locked, re-takes the lock.
bool DSurface::FUN_004BB000()
{
    if (!DAT_0089F978 && !DAT_00A8ED80)
        return false;
    if (DDSurf && DDSurf->lpVtbl->IsLost(DDSurf) == (long)DDERR_SURFACELOST_VALUE) {
        if (DDSurf->lpVtbl->Restore(DDSurf) || DDSurf->lpVtbl->IsLost(DDSurf))
            return false;
        int saved = LockLevel;
        if (saved > 0) {
            Point2D zero;
            LockLevel = 0;
            zero.X = 0;
            zero.Y = 0;
            Lock(zero);
            ++LockLevel;
            Unlock();
            LockLevel = saved;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BB080
bool DSurface::CopyFromPart(RectangleStruct* dest, Surface* src, RectangleStruct* srcRect, bool a, bool b)
{
    return CopyFrom(&GetRect(), dest, src, &src->GetRect(), srcRect, a, b);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BB0D0
bool DSurface::CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect, Surface* src,
                        RectangleStruct* srcClip, RectangleStruct* srcRect, bool a, bool b)
{
    if (destClip->Width <= 0 || destClip->Height <= 0)
        return false;
    if (srcClip->Width <= 0 || srcClip->Height <= 0)
        return false;
    if (destRect->Width <= 0 || destRect->Height <= 0)
        return false;
    if (srcRect->Width <= 0 || srcRect->Height <= 0)
        return false;

    DSurface* source = (DSurface*)src;
    bool useSoftware = false;
    if (!source->unknown_84() || source->IsLocked() == true || a == true || GetBytesPerPixel() != source->GetBytesPerPixel())
        useSoftware = true;

    bool direct = (IsPrimary == true && DAT_0089F978 == true) ? false : b;
    if (!useSoftware && direct == true) {
        if (!InVideoMemory || (source->unknown_84() == true && !source->InVideoMemory)) {
            if (srcRect->Width == destRect->Width && srcRect->Height == destRect->Height)
                useSoftware = true;
        }
    }

    if (!DAT_0089F978 && !DAT_00A8ED80)
        return false;
    if (!Recover())
        return false;
    if (useSoftware)
        return XSurface::CopyFromPart(destRect, src, srcRect, a, true);

    RectangleStruct dest = *destRect;
    RectangleStruct from = *srcRect;
    RectangleStruct srcVisible = Intersect(srcClip, &src->GetRect());
    RectangleStruct destVisible = Intersect(destClip, &GetRect());
    if (!ClipBlitRects(&dest, &destVisible, &from, &srcVisible))
        return false;

    DDRect destBounds;
    destBounds.left = destVisible.X + dest.X;
    destBounds.top = destVisible.Y + dest.Y;
    destBounds.right = destVisible.X + dest.X + dest.Width;
    destBounds.bottom = destVisible.Y + dest.Y + dest.Height;
    DDRect srcBounds;
    srcBounds.left = srcVisible.X + from.X;
    srcBounds.top = srcVisible.Y + from.Y;
    srcBounds.right = srcVisible.X + from.X + from.Width;
    srcBounds.bottom = srcVisible.Y + from.Y + from.Height;
    return DDSurf->lpVtbl->Blt(DDSurf, &destBounds, source->DDSurf, &srcBounds, 0x1000000, 0) == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BB5F0
bool DSurface::FillRect(RectangleStruct* rect, unsigned int color)
{
    return DSurface::FillRectEx(&GetRect(), rect, color);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BB620
bool DSurface::FillRectEx(RectangleStruct* clip, RectangleStruct* rect, unsigned int color)
{
    if (!DDSurf)
        return false;
    if (rect->Width <= 0 || rect->Height <= 0)
        return false;
    if (DAT_008205D4 && !IsLocked() && DDSurf->lpVtbl->GetBltStatus(DDSurf, 1) == 0) {
        if (!DAT_0089F978 && !DAT_00A8ED80)
            return false;
        if (!Recover())
            return false;
        RectangleStruct scratch;
        RectangleStruct* surfaceRect = &GetRect();
        RectangleStruct visible = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
        RectangleStruct target = *rect;
        target.X += clip->X;
        target.Y += clip->Y;
        target = *RectIntersect(&scratch, &target, &visible, 0, 0);
        if (target.Width <= 0 || target.Height <= 0)
            return false;
        DDRect bounds;
        bounds.left = target.X;
        bounds.top = target.Y;
        bounds.right = target.X + target.Width;
        bounds.bottom = target.Y + target.Height;
        DDBltFx fx;
        memset(&fx, 0, sizeof(fx));
        fx.dwSize = sizeof(fx);
        fx.dwFillColor = color;
        return DDSurf->lpVtbl->Blt(DDSurf, &bounds, 0, 0, 0x1000400, &fx) == 0;
    }
    return XSurface::FillRectEx(clip, rect, color);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BB830
// Alpha-blended rectangle fill on 16-bit surfaces. The base declaration's argument types are placeholders: the
// second argument points at a 3-byte colour and the third is an opacity percentage (clamped to 100).
bool DSurface::unknown_1C(RectangleStruct* rect, RectangleStruct* colorBytes, int percent)
{
    if (GetBytesPerPixel() < 2)
        return false;
    if (rect->Width <= 0 || rect->Height <= 0)
        return false;

    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, surfaceRect, rect, 0, 0);
    if (area.Width <= 0 || area.Height <= 0)
        return false;

    unsigned short maskA = 0xFF;
    maskA >>= gg_b_translucent_pixel_format.loss0;
    maskA <<= gg_b_translucent_pixel_format.pos0;
    unsigned short maskC = 0xFF;
    maskC >>= gg_b_translucent_pixel_format.loss2;
    maskC <<= gg_b_translucent_pixel_format.pos2;
    unsigned short maskB = 0xFF;
    maskB >>= gg_b_translucent_pixel_format.loss1;
    maskB <<= gg_b_translucent_pixel_format.pos1;

    Point2D origin;
    unsigned char* buffer = (unsigned char*)Lock(*((PointCopier*)&area)->CopyTo(&origin));
    if (!buffer)
        return false;

    unsigned int opacity = percent;
    if (opacity > 100)
        opacity = 100;
    unsigned int weight = opacity * 255 / 100;
    unsigned short inverse = 255 - weight;

    const unsigned char* rgb = (const unsigned char*)colorBytes;
    unsigned char byte2 = rgb[2];
    byte2 >>= gg_b_translucent_pixel_format.loss1;
    unsigned short part2 = byte2;
    unsigned char byte1 = rgb[1];
    byte1 >>= gg_b_translucent_pixel_format.loss2;
    unsigned short part1 = byte1;
    unsigned char byte0 = rgb[0];
    byte0 >>= gg_b_translucent_pixel_format.loss0;
    unsigned short part0 = byte0;
    unsigned short color = (part2 << gg_b_translucent_pixel_format.pos1) | (part1 << gg_b_translucent_pixel_format.pos2) |
                           (part0 << gg_b_translucent_pixel_format.pos0);

    for (int y = 0; y < area.Height; y++) {
        unsigned short* pixel = (unsigned short*)buffer + ((int)GetPitch() / 2) * y;
        for (int x = 0; x < area.Width; x++) {
            unsigned short old = *pixel;
            *pixel++ = ((((maskA & old) * inverse + (maskA & color) * weight) >> 8) & maskA) |
                       ((((maskC & old) * inverse + (maskC & color) * weight) >> 8) & maskC) |
                       ((((maskB & old) * inverse + (maskB & color) * weight) >> 8) & maskB);
        }
    }
    Unlock();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC30
int FUN_004BBC30()
{
    return gg_b_translucent_pixel_format.pos0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC40
int FUN_004BBC40()
{
    return gg_b_translucent_pixel_format.loss0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC50
int FUN_004BBC50()
{
    return gg_b_translucent_pixel_format.pos1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC60
int FUN_004BBC60()
{
    return gg_b_translucent_pixel_format.loss1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC70
int FUN_004BBC70()
{
    return gg_b_translucent_pixel_format.pos2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC80
int FUN_004BBC80()
{
    return gg_b_translucent_pixel_format.loss2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004BBC90
int FUN_004BBC90()
{
    return DAT_008205D0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BBCA0
// The base declaration keeps seven ints (retail RET 0x1c), so the typed values are recovered by casts:
// (RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ).
bool DSurface::unknown_38(RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct bounds = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
    if (bounds.Width == 0 && bounds.Height == 0)
        return false;

    Point2D p0;
    Point2D p1;
    p0.X = from->X + bounds.X;
    p0.Y = from->Y + bounds.Y;
    p1.X = to->X + bounds.X;
    p1.Y = to->Y + bounds.Y;
    if (p0.X > p1.X) {
        Point2D t = p0;
        p0 = p1;
        p1 = t;
        int swapZ = zFrom;
        zFrom = zTo;
        zTo = swapZ;
    }

    int ox = p0.X;
    int oy = p0.Y;
    int ex = p1.X;
    int ey = p1.Y;
    if (!ClipLine(&p0, &p1, &bounds))
        return false;

    if (p1.X != ex || p1.Y != ey) {
        LengthVector whole;
        whole.X = ox - ex;
        whole.Y = oy - ey;
        LengthVector part;
        part.X = ox - p1.X;
        part.Y = oy - p1.Y;
        int wholeLength = whole.Length();
        int partLength = part.Length();
        int dz = abs((int)((double)partLength / wholeLength * (zFrom - zTo)));
        if (zFrom < zTo)
            zTo = dz + zFrom;
        else
            zTo = zFrom - dz;
    }
    if (p0.X != ox || p0.Y != oy) {
        double partLength = FUN_004CAC40((double)(p0.X - ex) * (p0.X - ex) + (double)(p0.Y - ey) * (p0.Y - ey));
        int partLen = (int)partLength;
        int wholeLen = (int)FUN_004CAC40((double)(ox - ex) * (ox - ex) +
                                 (double)(oy - ey) * (oy - ey));
        int dz = abs((int)(partLen / (double)wholeLen * (zFrom - zTo)));
        if (zTo > zFrom)
            zFrom = zTo - dz;
        else
            zFrom = dz + zTo;
    }

    int bytesPerPixel = GetBytesPerPixel();
    unsigned char* row = (unsigned char*)Lock(p0);
    ZBufferLike_004BBCA0* zb = ((ZBufferLike_004BBCA0*)gg_rle_zwrap_global);
    if (!zb || !row)
        return false;

    // The entry loads ECX from 0x887644 and directly calls 0x7BD130.
    unsigned short* zp = (unsigned short*)((AlphaBuffer*)gg_rle_zwrap_global)->GetBuffer(p0.X, p0.Y - zb->Top);
    int zRowStep = zb->Stride;
    int zCur = (unsigned short)(zb->Extent + zb->Top) - p0.Y - bounds.Y + zFrom;
    int zRowDir = -1;

    int dx = p1.X - p0.X;
    int dy = p1.Y - p0.Y;
    int dz = zTo - zFrom;
    int pitch = GetPitch();
    if (dy < 0) {
        pitch = -pitch;
        zRowStep = -zRowStep;
        zRowDir = 1;
    }
    int absDy = abs(dy);
    int zSign = 1;
    if (dz < 0)
        zSign = -1;
    int absDz = abs(dz);
    int xOffset = 0;

    if (dx < absDz && absDy < absDz) {
        int errY = -absDz;
        int errX = -absDz;
        for (int n = absDz; n > 0; n--) {
            errY += absDy * 2;
            errX += dx * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + xOffset), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errY > 0) {
                row += pitch;
                errY -= absDz * 2;
                StepRowUp(zp, zRowStep, zb);
                zCur += zRowDir;
            }
            if (errX > 0) {
                StepColumn(zp, zb);
                xOffset += 2;
                errX -= absDz * 2;
            }
            zCur += zSign;
        }
    } else if (absDy < dx) {
        int errZ = -dx;
        int errY = absDy * 2 - dx;
        for (int x = 0; x < dx; x++) {
            errZ += absDz * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + x * 2), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errY > 0) {
                row += pitch;
                errY -= dx * 2;
                StepRowUp(zp, zRowStep, zb);
                zCur += zRowDir;
            }
            if (errZ > 0) {
                zCur += zSign;
                errZ -= dx * 2;
            }
            StepColumn(zp, zb);
            errY += absDy * 2;
        }
    } else {
        int errX = dx * 2 - absDy;
        int errZ = -absDy;
        for (int n = absDy; n > 0; n--) {
            errZ += absDz * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + xOffset), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errX > 0) {
                StepColumn(zp, zb);
                xOffset += 2;
                errX -= absDy * 2;
            }
            if (errZ > 0) {
                zCur += zSign;
                errZ -= absDy * 2;
            }
            errX += dx * 2;
            row += pitch;
            StepRowUp(zp, zRowStep, zb);
            zCur += zRowDir;
        }
    }
    Unlock();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BF750
// PARTIAL (second look, 21.3% positional; instruction multiset gap 8 of 483). Channel terms are packed in
// channel 0, 1, 2 order and the horizontal store precedes the pointer increment. Remaining delta: retail
// keeps `this` in EBP (ours EBX), zeroes the first channel with `XOR DX,DX; MOV DL,AL`, and loads the
// 0x661020 arguments in a different order.
bool DSurface::DrawLineGradient(RectangleStruct* clip, Point2D* from, Point2D* to, const unsigned char* colorA,
                                const unsigned char* colorB, float* step, float* blend)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);

    Point2D p1;
    Point2D p2;
    p1.X = from->X + area.X;
    p1.Y = from->Y + area.Y;
    p2.X = to->X + area.X;
    p2.Y = to->Y + area.Y;
    if (ClipLine(&p1, &p2, &area)) {
        if (p1.X > p2.X) {
            Point2D swap = p1;
            p1 = p2;
            p2 = swap;
        }
        if (GetBytesPerPixel() == 2) {
            unsigned short* pixel = (unsigned short*)Lock(p1);
            if (pixel) {
            if (p1.Y == p2.Y) {
                for (int i = 0; i <= p2.X - p1.X; i++) {
                    *pixel = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                    pixel++;
                }
                Unlock();
                return true;
            }
            if (p1.X == p2.X) {
                int pitch = p1.Y > p2.Y ? -(int)GetPitch() : (int)GetPitch();
                int dy = abs(p2.Y - p1.Y);
                for (int i = 0; i <= dy; i++) {
                    *pixel = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                    pixel = (unsigned short*)((char*)pixel + pitch);
                }
                Unlock();
                return true;
            }
            int dy = p2.Y - p1.Y;
            int dx = p2.X - p1.X;
            int pitch = GetPitch();
            if (dy < 0)
                pitch = -pitch;
            int ady = abs(dy);
            if (dx > ady) {
                int err = ady * 2 - dx;
                for (int i = 0; i <= dx; i++) {
                    pixel[i] = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                    if (err > 0) {
                        pixel = (unsigned short*)((char*)pixel + pitch);
                        err -= dx * 2;
                    }
                    err += ady * 2;
                }
                Unlock();
                return true;
            }
            int err = dx * 2 - ady;
            int xoff = 0;
            for (int i = 0; i <= ady; i++) {
                *(unsigned short*)((char*)pixel + xoff) = PixelAt(colorA, colorB, blend);
                Advance(step, blend);
                if (err > 0) {
                    xoff += 2;
                    err -= ady * 2;
                }
                err += dx * 2;
                pixel = (unsigned short*)((char*)pixel + pitch);
            }
            Unlock();
            return true;
            }
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4BFD30
// The base declaration keeps seven ints (retail RET 0x1c), so the typed values are recovered by casts:
// (RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ).
bool DSurface::unknown_34(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
    if (area.Width == 0 && area.Height == 0)
        return false;

    Point2D pt[2];
    pt[0].X = from->X + area.X;
    pt[0].Y = from->Y + area.Y;
    pt[1].X = to->X + area.X;
    pt[1].Y = to->Y + area.Y;
    if (pt[1].X < pt[0].X) {
        Point2D t = pt[0];
        pt[0] = pt[1];
        pt[1] = t;
        int zt = zEnd;
        zEnd = zStart;
        zStart = zt;
    }
    Point2D& a = pt[0];
    Point2D& b = pt[1];
    int& zA = zStart;
    int& zB = zEnd;

    Point2D origA = a;
    Point2D origB = b;
    if (!ClipLine(&a, &b, &area))
        return false;

    if (b.X != origB.X || b.Y != origB.Y) {
        int cut = Distance(origA.X - b.X, origA.Y - b.Y);
        int total = Distance(origA.X - origB.X, origA.Y - origB.Y);
        int delta = abs((int)(((double)cut / (double)total) * (double)(zB - zA)));
        zB = zB < zA ? zA - delta : zA + delta;
    }
    if (a.X != origA.X || a.Y != origA.Y) {
        int cut = Distance(a.X - origA.X, a.Y - origA.Y);
        int total = Distance(origB.X - origA.X, origB.Y - origA.Y);
        int delta = abs((int)(((double)cut / (double)total) * (double)(zB - zA)));
        zA = zA < zB ? zA + delta : zA - delta;
    }

    GetBytesPerPixel();
    unsigned short* dest = (unsigned short*)Lock(a);
    if (!((WrapBuffer_004BFD30*)gg_rle_zwrap_global))
        return false;
    // Entry callsites load ECX from 0x887644 before CALL 0x7BD130, then from
    // 0x87E8A4 before CALL 0x4114B0. These are address-checked receiver views.
    unsigned short* zrow = (unsigned short*)((AlphaBuffer*)gg_rle_zwrap_global)->GetBuffer(a.X, a.Y - ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Top);
    unsigned short* arow = (unsigned short*)((ABuffer*)gg_blit_alpha_wrap_global)->GetBuffer(a.X, a.Y - ((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global)->Top);
    int zStep = -1;
    int zCur = (unsigned short)(((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Origin + ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Top) - a.Y - area.Y + zA;
    int rowStride = ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->RowStride;
    if (!dest)
        return false;

    unsigned char ch0 = color >> gg_b_translucent_pixel_format.pos0;
    ch0 <<= gg_b_translucent_pixel_format.loss0;
    unsigned char ch1 = color >> gg_b_translucent_pixel_format.pos2;
    ch1 <<= gg_b_translucent_pixel_format.loss2;
    unsigned char ch2 = color >> gg_b_translucent_pixel_format.pos1;
    ch2 <<= gg_b_translucent_pixel_format.loss1;

    int dx = b.X - a.X;
    int dy = b.Y - a.Y;
    int pitch = GetPitch();
    int rowDelta = pitch;
    if (dy < 0) {
        rowDelta = -pitch;
        rowStride = -rowStride;
        zStep = 1;
    }
    int ystep = 1;
    if ((zB - zA) < 0)
        ystep = -1;
    int adx = abs(dx);
    int ady = abs(dy);
    int adx2 = adx * 2;
    int ady2 = ady * 2;

    if (dx < ady && adx < ady) {
        // steep line: one row per step
        int err = -ady;
        int errX = -ady;
        for (int i = 0; i < ady; i++) {
            errX += dx * 2;
            err += adx2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (err > 0) {
                dest = (unsigned short*)((char*)dest + rowDelta);
                err -= ady2;
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
                zCur += zStep;
            }
            if (errX > 0) {
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
                errX -= ady2;
            }
            zCur += ystep;
        }
    } else if (adx < dx) {
        int err = -dx;
        int errY = -dx;
        for (int i = 0; i < dx; i++) {
            err += ady2;
            errY += adx2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (errY > 0) {
                dest = (unsigned short*)((char*)dest + rowDelta);
                errY -= dx * 2;
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
                zCur += zStep;
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
            }
            if (err > 0) {
                zCur += ystep;
                err -= dx * 2;
            }
            zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
            arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
        }
    } else {
        int err = -adx;
        int errMinor = ady2 - adx;
        for (int i = 0; i < adx; i++) {
            err += ady2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (err > 0) {
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
                err -= adx2;
            }
            if (errMinor > 0) {
                zCur += ystep;
                errMinor -= adx2;
            }
            errMinor += ady2;
            dest = (unsigned short*)((char*)dest + rowDelta);
            zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
            zCur += zStep;
            arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
        }
    }
    Unlock();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C1A90
bool DSurface::CopyFromWhole(Surface* src, bool a, bool b)
{
    return XSurface::CopyFromWhole(src, a, b);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C1AB0
bool DSurface::unknown_84()
{
    return true;
}

// SYNTHETIC: GAMEMD 0x4C1AC0
// DSurface scalar deleting destructor (compiler-generated from the virtual destructor).

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004C1B50
// Euclidean length of the pair through 0x4CAC40, truncated.
int FUN_004C1B50(const Pair_004C1B50* self)
{
    double y = self->unknown_4;
    double x = self->unknown_0;
    return (int)FUN_004CAC40(x * x + y * y);
}
