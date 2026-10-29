// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x410E50 / 0x4112D0 /
//   0x411310 / 0x4114B0 / 0x4355D0), cross-checked against YRpp
//   (every offset/slot reconfirmed from the disasm).
//
// Renderer drawing helpers:
//   - ABuffer   : the alpha-buffer (NOVTABLE) wrapping a BSurface. Only the
//                 four matched methods + the members they touch are modelled.
//   - BSurface  : opaque virtual surface; only the vtable slots the matched
//                 ABuffer methods call (0x00, 0x14, 0x5C, 0x60) are typed.
//   - Drawing   : the static colour helper holding RGB_To_Int.
#ifndef GG_MATCH_RENDERER_DRAWING_H
#define GG_MATCH_RENDERER_DRAWING_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RectangleStruct — {X, Y, Width, Height}, 16 bytes. ABuffer::Bounds is one of
// these at +0x00; Fill/FillRect build/pass one by value (RET 0x14 == 4+16).
#include "../_layout/geometry2d.h"
GG_STATIC_ASSERT(sizeof(RectangleStruct) == 0x10);

// ---------------------------------------------------------------------------
// BSurface — the polymorphic blit surface ABuffer draws into. Modelled as a
// pure-virtual interface so cl emits the exact `MOV EAX,[ECX]; CALL [EAX+off]`
// indirect-virtual sequences. Only the slots the matched methods invoke carry
// real signatures; the rest are placeholders that merely pin the slot offsets.
//   slot  0 (0x00): Destroy(int)            — ReleaseSurface  CALL [EAX]
//   slot  5 (0x14): FillRect(Rect*, int)    — Fill / FillRect CALL [EAX+0x14]
//   slot 23 (0x5C): vf_23(int, int)     — GetBuffer       CALL [EAX+0x5C]
//   slot 24 (0x60): Lock()                  — GetBuffer       CALL [EAX+0x60]
// ---------------------------------------------------------------------------
// This address-scoped call interface remains separate from native BSurface.
class BSurfaceLayout
{
public:
    virtual void Destroy(int freeMem) = 0;                       // 0x00
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
    virtual void vf64() = 0;                                     // 0x64
    virtual void vf68() = 0;                                     // 0x68
    virtual void vf6C() = 0;                                     // 0x6C
    virtual void vf70() = 0;                                     // 0x70
    virtual int  vf74() = 0;                                     // 0x74  row pitch in bytes
};

// ---------------------------------------------------------------------------
// ABuffer  (NOVTABLE — no own vtable; Bounds sits at +0x00).
// Members below confirmed numerically from the matched methods:
//   +0x10 BufferPosition  (GetBuffer MOV EAX,[ESI+0x10])
//   +0x14 Surface         (ReleaseSurface/Fill/FillRect/GetBuffer [ECX/ESI+0x14])
//   +0x1C BufferTail      (GetBuffer MOV ECX,[ESI+0x1C])
//   +0x20 BufferSize      (GetBuffer SUB EAX,[ESI+0x20])
//   +0x28 Width           (Fill MOV EAX,[ECX+0x28])
//   +0x2C Height          (Fill MOV EDX,[ECX+0x2C])
// ---------------------------------------------------------------------------
struct ABuffer
{
    // Declaration: GAMEMD 0x411330 -- rectangle16 bytes by value, RET16.
    void FUN_00411330(RectangleStruct rectangle);
    void FUN_00410ED0(int dx, int dy, unsigned short color); // RET12
    // FUNCTION: GAMEMD 0x410DC0 -- copy a width x height block of 16-bit pixels from the ring buffer to a surface, RET 0x14.
    void FUN_00410DC0(BSurfaceLayout* dest, int x, int y, int width, int height);
    void  ReleaseSurface();                                  // GAMEMD 0x410E50
    bool  Fill(unsigned short Color);                        // GAMEMD 0x4112D0
    bool  FillRect(unsigned short Color, RectangleStruct Rect); // GAMEMD 0x411310
    void* GetBuffer(int X, int Y);                           // GAMEMD 0x4114B0

    RectangleStruct Bounds;          // +0x00
    int             BufferPosition;  // +0x10
    BSurfaceLayout* Surface;         // +0x14
    void*           BufferHead;      // +0x18
    void*           BufferTail;      // +0x1C
    int             BufferSize;      // +0x20
    int             MaxValue;        // +0x24
    int             Width;           // +0x28
    int             Height;          // +0x2C
};

GG_STATIC_ASSERT(offsetof(ABuffer, BufferPosition) == 0x10);
GG_STATIC_ASSERT(offsetof(ABuffer, BufferSize)     == 0x20);
GG_STATIC_ASSERT(offsetof(ABuffer, Width)          == 0x28);
GG_STATIC_ASSERT(offsetof(ABuffer, Height)         == 0x2C);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ABuffer, Surface)    == 0x14);  // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(ABuffer, BufferTail) == 0x1C);
#endif

// GLOBAL: GAMEMD 0x87E8A4 (declaration; existing storage)
// Display4A8AD7 constructs with410CE0, then stores the result at4A8ADC.
extern ABuffer* ABuffer_0087E8A4;
GG_STATIC_ASSERT(sizeof(ABuffer) == 0x30);

// ---------------------------------------------------------------------------
// Drawing — static colour helper. RGB_To_Int packs (r,g,b) into the surface's
// current 16-bit colour format using the global per-channel shift amounts.
// ---------------------------------------------------------------------------
class Drawing
{
public:
    static int RGB_To_Int(int red, int green, int blue);  // GAMEMD 0x4355D0
};

#endif  // GG_MATCH_RENDERER_DRAWING_H
