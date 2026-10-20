// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals and offsets read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x53D850: the surface pointer
//   `[0x887314]` with the zero-arg slot `[EAX+0x74]`, the cached pitch
//   `[0xAA0150]`, the offset table starting at 0xA9FAE8 (`[0xA9FAE8]` cleared,
//   ESI walks 0xA9FAEC..0xA9FF6C, i.e. 289 ints), the vector Items `[0xAA011C]`
//   / Count `[0xAA0128]` (IonBlastClass::Array @0xAA0118), the __fastcall
//   Point2D-returning helper at 0x53D8E0 (ECX = hidden result, EDX = index,
//   `[EAX]`/`[EAX+4]` read back) and the per-element `CALL 0x53D580`.
//   Names cross-checked against the consult-only YRpp IonBlastClass.h /
//   Surface.h (names only; slot 0x74 is GetPitch in YRpp's Surface order).
#ifndef GG_MATCH_COMBAT_ION_BLAST_DRAW_METHODS_H
#define GG_MATCH_COMBAT_ION_BLAST_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/vector_class.h"

// Point2D carries a (trivial) user constructor so VC6 returns it through a
// hidden result pointer rather than in EDX:EAX, which is the retail convention
// for the 0x53D8E0 helper (`LEA ECX,[ESP+0xC]` before the call, `[EAX]` after).
struct Point2D
{
    int X;                    // +0x0000
    int Y;                    // +0x0004

    Point2D() {}
};
GG_STATIC_ASSERT(sizeof(Point2D) == 0x8);

// Surface — only the zero-argument slot at +0x74 is reached (GetPitch).
struct Vtbl_Surface;

struct Surface
{
    Vtbl_Surface* Vtbl;       // +0x0000
};

typedef int (Surface::*Fn74_Surface)();

struct Vtbl_Surface
{
    char         _pad000[0x74];   // +0x0000
    Fn74_Surface GetPitch;        // +0x0074
};
GG_STATIC_ASSERT(offsetof(Vtbl_Surface, GetPitch) == 0x74);

// GLOBAL: GAMEMD 0x887314 — DSurface::Temp.
extern Surface* DSurface_Temp;

// FUNCTION: GAMEMD 0x53D8E0 (decl; reloc) — the n-th point of a square spiral
// walked outward from the origin, returned by value (hidden pointer in ECX).
Point2D __fastcall FUN_0053D8E0(int index);

// Number of spiral points held by the offset table: 289 = 17 x 17.
#define ION_BLAST_OFFSET_COUNT 289

// GLOBAL: GAMEMD 0xA9FAE8 — per-pitch pixel offset table for the blast
// pattern, rebuilt whenever the surface pitch changes.
extern int IonBlastOffsets[ION_BLAST_OFFSET_COUNT];

// GLOBAL: GAMEMD 0xAA0150 — the pitch the table was last built for.
extern int IonBlastOffsetsPitch;

struct IonBlastClass
{
    // FUNCTION: GAMEMD 0x53D580 (decl; reloc)
    void Draw();

    // FUNCTION: GAMEMD 0x53D850
    static void __fastcall DrawAll();
};

// GLOBAL: GAMEMD 0xAA0118 — IonBlastClass::Array (Items 0xAA011C, Count 0xAA0128).
extern DynamicVectorClassLayout IonBlastArray;

#endif  // GG_MATCH_COMBAT_ION_BLAST_DRAW_METHODS_H
