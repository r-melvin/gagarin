// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slot numbers read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x40A7C0. The three calls go
//   through `[ECX+0x48]`, `[EDX+0x38]` and `[EDX+0x30]` with the receiver
//   pushed, so the interface uses __stdcall virtuals.
#ifndef GG_MATCH_RENDERER_PRESENT_FRAME_METHODS_H
#define GG_MATCH_RENDERER_PRESENT_FRAME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Surface_0040A7C0;

// The rectangle-ish descriptor built on the stack and handed to slot +0x38.
// Everything but the two ints is 16-bit, which is what forces the word stores
// and the zero-extending read-back of Span at 0x40A7F9.
struct Region_0040A7C0
{
    unsigned short Kind;    // +0x0000  always 1 here
    unsigned short Step;    // +0x0002
    int  Rows;              // +0x0004
    int  Total;             // +0x0008
    unsigned short Span;    // +0x000C
    unsigned short Width;   // +0x000E
    unsigned short Tail;    // +0x0010
};
GG_STATIC_ASSERT(offsetof(Region_0040A7C0, Rows) == 0x4);
GG_STATIC_ASSERT(offsetof(Region_0040A7C0, Span) == 0xC);
GG_STATIC_ASSERT(offsetof(Region_0040A7C0, Tail) == 0x10);

typedef int (__stdcall* Fn30_0040A7C0)(Surface_0040A7C0*, int, int, int);
typedef int (__stdcall* Fn38_0040A7C0)(Surface_0040A7C0*, Region_0040A7C0*);
typedef int (__stdcall* Fn48_0040A7C0)(Surface_0040A7C0*);

struct Vtbl_0040A7C0
{
    char _pad000[0x30];       // +0x0000
    Fn30_0040A7C0 At_30;      // +0x0030
    char _pad034[0x4];        // +0x0034
    Fn38_0040A7C0 At_38;      // +0x0038
    char _pad03C[0xC];        // +0x003C
    Fn48_0040A7C0 At_48;      // +0x0048
};
GG_STATIC_ASSERT(offsetof(Vtbl_0040A7C0, At_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Vtbl_0040A7C0, At_48) == 0x48);

struct Surface_0040A7C0 { Vtbl_0040A7C0* Vtbl; };

// GLOBAL: GAMEMD 0x87E8A0 — the active surface, null before it is created.
extern Surface_0040A7C0* DAT_0087E8A0;

// What 0x407010 hands back: the three dimensions the region is built from. The
// two 16-bit ones are loaded with 16-bit moves into AX and SI, so the arithmetic
// on them runs with whatever is left in the upper halves — harmless because only
// the low words are ever stored.
struct Mode_0040A850
{
    char _pad000[0x4C];       // +0x0000
    int  Rows;                // +0x004C
    unsigned short Step;      // +0x0050
    char _pad052[0x2];        // +0x0052
    unsigned short Bands;     // +0x0054
};
GG_STATIC_ASSERT(offsetof(Mode_0040A850, Rows) == 0x4C);
GG_STATIC_ASSERT(offsetof(Mode_0040A850, Bands) == 0x54);

// FUNCTION: GAMEMD 0x407010 — the current mode, or null.
Mode_0040A850* __fastcall FUN_00407010();

// FUNCTION: GAMEMD 0x40A7C0
void __fastcall FUN_0040A7C0(int rows, int height, int step);
// FUNCTION: GAMEMD 0x40A850
void FUN_0040A850();

#endif  // GG_MATCH_RENDERER_PRESENT_FRAME_METHODS_H
