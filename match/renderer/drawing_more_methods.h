// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Legacy GetBuffer ABI retained at7BD130. Caller ownership is ZBuffer887644;
// migration to canonical Surface::Lock(Point2D)/Unlock is held at65.2%.
// Fill7BCF50 now belongs to zbuffer_class_methods.cpp after exact proof.
#ifndef GG_MATCH_RENDERER_DRAWING_MORE_METHODS_H
#define GG_MATCH_RENDERER_DRAWING_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RectangleStruct — {X, Y, Width, Height}, 16 bytes. Fill builds one full-extent
// rect by value and forwards it to the surface's FillRect virtual.
#include "../_layout/geometry2d.h"
GG_STATIC_ASSERT(sizeof(RectangleStruct) == 0x10);

// ---------------------------------------------------------------------------
// AlphaSurface — the polymorphic blit surface the buffer draws into. Modelled
// as a pure-virtual interface so cl emits the exact indirect-virtual sequences
// `MOV EAX,[ECX]; CALL [EAX+off]`. Only the slots the two matched methods invoke
// carry real signatures; the rest merely pin the slot offsets.
//   slot  5 (0x14): FillRect(Rect*, int)   — Fill      CALL [EAX+0x14]
//   slot 23 (0x5C): vf_23(int, int)    — GetBuffer CALL [EAX+0x5C]
//   slot 24 (0x60): Lock()                 — GetBuffer CALL [EAX+0x60]
// ---------------------------------------------------------------------------
class AlphaSurface
{
public:
    virtual void vf00() = 0;                                     // 0x00
    virtual void vf04() = 0;                                     // 0x04
    virtual void vf08() = 0;                                     // 0x08
    virtual void vf0C() = 0;                                     // 0x0C
    virtual void vf10() = 0;                                     // 0x10
    virtual bool FillRect(RectangleStruct* rect, int color) = 0; // 0x14
    virtual void vf18() = 0;                                     // 0x18
    virtual void vf1C() = 0;                                     // 0x1C
    virtual void vf20() = 0;                                     // 0x20
    virtual void vf24() = 0;                                     // 0x24
    virtual void vf28() = 0;                                     // 0x28
    virtual void vf2C() = 0;                                     // 0x2C
    virtual void vf30() = 0;                                     // 0x30
    virtual void vf34() = 0;                                     // 0x34
    virtual void vf38() = 0;                                     // 0x38
    virtual void vf3C() = 0;                                     // 0x3C
    virtual void vf40() = 0;                                     // 0x40
    virtual void vf44() = 0;                                     // 0x44
    virtual void vf48() = 0;                                     // 0x48
    virtual void vf4C() = 0;                                     // 0x4C
    virtual void vf50() = 0;                                     // 0x50
    virtual void vf54() = 0;                                     // 0x54
    virtual void vf58() = 0;                                     // 0x58
    virtual int  vf_23(int x, int y) = 0;                    // 0x5C
    virtual int  Lock() = 0;                                     // 0x60
};

// ---------------------------------------------------------------------------
// Legacy buffer view retained for the existing exact GetBuffer method:
//   +0x10 BufferPosition  (GetBuffer MOV EAX,[ESI+0x10])
//   +0x14 Surface         (Fill [ECX+0x14] / GetBuffer [ESI+0x14])
//   +0x1C BufferTail      (GetBuffer MOV ECX,[ESI+0x1C])
//   +0x20 BufferSize      (GetBuffer SUB EAX,[ESI+0x20])
//   +0x28 Width           (Fill MOV EAX,[ECX+0x28])
//   +0x2C Height          (Fill MOV EDX,[ECX+0x2C])
// ---------------------------------------------------------------------------
struct AlphaBuffer
{
    void* GetBuffer(int X, int Y);          // GAMEMD 0x7BD130

    RectangleStruct Bounds;          // +0x00
    int             BufferPosition;  // +0x10
    AlphaSurface*   Surface;         // +0x14
    void*           BufferHead;      // +0x18
    void*           BufferTail;      // +0x1C
    int             BufferSize;      // +0x20
    int             MaxValue;        // +0x24
    int             Width;           // +0x28
    int             Height;          // +0x2C
};

GG_STATIC_ASSERT(offsetof(AlphaBuffer, BufferPosition) == 0x10);
GG_STATIC_ASSERT(offsetof(AlphaBuffer, BufferSize)     == 0x20);
GG_STATIC_ASSERT(offsetof(AlphaBuffer, Width)          == 0x28);
GG_STATIC_ASSERT(offsetof(AlphaBuffer, Height)         == 0x2C);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AlphaBuffer, Surface)    == 0x14);  // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(AlphaBuffer, BufferTail) == 0x1C);
#endif

#endif  // GG_MATCH_RENDERER_DRAWING_MORE_METHODS_H
