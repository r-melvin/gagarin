// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6BA580: a `__stdcall` taking the destination rectangle,
//   the destination surface, the source surface and the transparent colour
//   (`RET 0x10`, the colour read as a word from `[ESP+0x34]`); the surface
//   slots `[EDX+0x5C]` (lock, two pushed zeroes, returning the bits),
//   `[EDX+0x60]` (unlock), `[EDX+0x74]` (pitch in bytes, halved for the
//   16-bit stride), `[EDX+0x7C]` (width) and `[EAX+0x80]` (height); and the
//   rectangle's four ints at `[ECX]` .. `[ECX+0xC]`.
#ifndef GG_MATCH_RENDERER_PCX_BLIT_SURFACE_METHODS_H
#define GG_MATCH_RENDERER_PCX_BLIT_SURFACE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Rect_006BA580
{
    int X;       // +0x0000
    int Y;       // +0x0004
    int Width;   // +0x0008
    int Height;  // +0x000C
};
GG_STATIC_ASSERT(sizeof(Rect_006BA580) == 0x10);

struct SurfaceVtbl_006BA580;

struct Surface_006BA580
{
    SurfaceVtbl_006BA580* Vptr;   // +0x0000
};
typedef void* (Surface_006BA580::*Fn5C_006BA580)(int a, int b);
typedef int   (Surface_006BA580::*Fn60_006BA580)();
typedef int   (Surface_006BA580::*Fn74_006BA580)();
typedef int   (Surface_006BA580::*Fn7C_006BA580)();
typedef int   (Surface_006BA580::*Fn80_006BA580)();

struct SurfaceVtbl_006BA580
{
    char           _pad000[0x5C];          // +0x0000
    Fn5C_006BA580  Lock;                   // +0x005C
    Fn60_006BA580  Unlock;                 // +0x0060
    char           _pad064[0x74 - 0x64];   // +0x0064
    Fn74_006BA580  GetPitch;               // +0x0074
    char           _pad078[4];             // +0x0078
    Fn7C_006BA580  GetWidth;               // +0x007C
    Fn80_006BA580  GetHeight;              // +0x0080
};
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006BA580, Lock)      == 0x5C);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006BA580, Unlock)    == 0x60);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006BA580, GetPitch)  == 0x74);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006BA580, GetWidth)  == 0x7C);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006BA580, GetHeight) == 0x80);

// FUNCTION: GAMEMD 0x6BA580 — blit a locked surface with one colour keyed out.
bool __stdcall PCX_BlitToSurface(const Rect_006BA580* area, Surface_006BA580* dst,
                                 Surface_006BA580* src, unsigned short transparent);

#endif  // GG_MATCH_RENDERER_PCX_BLIT_SURFACE_METHODS_H
