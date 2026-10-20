// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4348F0: `[ESI+0xC]` (the locked
//   buffer), `[ESI+0x10]` (pitch halved with SHR), `[ESI+0x30..0x3C]` (the
//   clip rectangle, OR-tested for all-zero); surface slots `CALL [EDX+0x5C]`
//   (Lock, two zeroed dwords pushed from two separately materialised
//   registers), `[EAX+0x74]` (pitch), `[EDX+0x7C]` (width), `[EAX+0x80]`
//   (height). Names cross-checked against YRpp BitFont.h / Surface.h
//   (consult-only, no LICENSE); YRpp types the Lock slot as (int, int), but
//   only a by-value two-int struct reproduces the two XORs, so it is modelled
//   that way here.
#ifndef GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H
#define GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The point passed by value to Surface::Lock. Two ints, 8 bytes on the stack.
struct Point2D
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(Point2D) == 0x8);

// Surface — pure-virtual interface so cl emits `MOV EDX,[EDI]; CALL [EDX+n]`.
// Only the four invoked slots carry real signatures; the rest pin the offsets.
// Lock takes its origin by value: retail materialises the two zero members in
// two registers (`XOR ECX,ECX; XOR EAX,EAX; PUSH ECX; PUSH EAX`), which two
// int arguments never do (they fold to `PUSH 0; PUSH 0`).
struct Surface
{
    virtual void vf00() = 0;  // 0x00
    virtual void vf04() = 0;  // 0x04
    virtual void vf08() = 0;  // 0x08
    virtual void vf0C() = 0;  // 0x0C
    virtual void vf10() = 0;  // 0x10
    virtual void vf14() = 0;  // 0x14
    virtual void vf18() = 0;  // 0x18
    virtual void vf1C() = 0;  // 0x1C
    virtual void vf20() = 0;  // 0x20
    virtual void vf24() = 0;  // 0x24
    virtual void vf28() = 0;  // 0x28
    virtual void vf2C() = 0;  // 0x2C
    virtual void vf30() = 0;  // 0x30
    virtual void vf34() = 0;  // 0x34
    virtual void vf38() = 0;  // 0x38
    virtual void vf3C() = 0;  // 0x3C
    virtual void vf40() = 0;  // 0x40
    virtual void vf44() = 0;  // 0x44
    virtual void vf48() = 0;  // 0x48
    virtual void vf4C() = 0;  // 0x4C
    virtual void vf50() = 0;  // 0x50
    virtual void vf54() = 0;  // 0x54
    virtual void vf58() = 0;  // 0x58
    virtual void* Lock(Point2D origin) = 0;   // 0x5C
    virtual void vf60() = 0;  // 0x60
    virtual void vf64() = 0;  // 0x64
    virtual void vf68() = 0;  // 0x68
    virtual void vf6C() = 0;  // 0x6C
    virtual void vf70() = 0;  // 0x70
    virtual unsigned int GetPitch() = 0;    // 0x74  bytes per scanline
    virtual void vf78() = 0;  // 0x78
    virtual int GetWidth() = 0;             // 0x7C
    virtual int GetHeight() = 0;            // 0x80
};

struct LTRBStruct
{
    int Left;     // +0x00
    int Top;      // +0x04
    int Right;    // +0x08
    int Bottom;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(LTRBStruct) == 0x10);

// BitFont (partial) — only the members Lock touches.
struct BitFont
{
    char        _pad000[0xC];    // +0x0000
    void*       pGraphBuffer;    // +0x000C  locked surface base
    int         PitchDiv2;       // +0x0010  surface stride in 16-bit words
    char        _pad014[0x1C];   // +0x0014
    LTRBStruct  Bounds;          // +0x0030  clip rectangle; all-zero = unset

    // FUNCTION: GAMEMD 0x434840 (decl; reloc) — clip `a` against `b` into
    // `out`; three stack arguments (`RET 0xC`), `this` unused.
    bool Intersect(LTRBStruct* out, LTRBStruct* a, LTRBStruct* b);

    // FUNCTION: GAMEMD 0x4348F0
    void Lock(Surface* surface);
};
GG_STATIC_ASSERT(offsetof(BitFont, pGraphBuffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFont, PitchDiv2)    == 0x10);
GG_STATIC_ASSERT(offsetof(BitFont, Bounds)       == 0x30);

#endif  // GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H
