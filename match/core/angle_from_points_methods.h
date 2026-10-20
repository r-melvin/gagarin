// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, argument slots and both constants read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4265B0. The two
//   doubles are `ghidra memory read`: 0x7E2820 is 1.5707963267948966 (pi/2)
//   and 0x7E2818 is -10430.060040584269.
//
// The direction from one point to another, as a binary angle.
//
// The scaling constant is not 65536/(2*pi) = 10430.378, so this is not a plain
// turn-to-16-bit conversion; the value is recorded as read rather than
// rewritten as an expression.
//
// Argument order into 0x4CAE30 comes off the stack, not the FPU sequence:
// `b->X - a->X` is stored at [ESP+8] and `a->Y - b->Y` at [ESP], so the first
// parameter is the Y difference. Note the Y difference runs a-to-b while the X
// difference runs b-to-a.
//
// Equal points zero the field first and then fall through into the same
// arithmetic - retail does not skip it.
#ifndef GG_MATCH_CORE_ANGLE_FROM_POINTS_METHODS_H
#define GG_MATCH_CORE_ANGLE_FROM_POINTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4CAE30 — two-argument arctangent, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);

struct Point_004265B0
{
    int X;   // +0x0000
    int Y;   // +0x0004
};

// The result is four bytes even though only the low word is computed: retail
// writes `MOV word ptr [ESP+0xC],AX` into a scratch slot and then copies the
// whole dword out with `MOV EAX,[ESP+0xC]; MOV [ESI],EAX`, so the upper half
// carries whatever the slot held. Modelled as a two-field struct assigned
// through a temporary rather than a bare `short` store.
struct Angle_004265B0
{
    short Value;      // +0x0000
    short Unwritten;  // +0x0002

    // FUNCTION: GAMEMD 0x4265B0
    Angle_004265B0* FUN_004265B0(Point_004265B0* from, Point_004265B0* to);
};
GG_STATIC_ASSERT(sizeof(Angle_004265B0) == 4);

// ---------------------------------------------------------------------------
// 0x41C2E0 — the same binary angle, taken from a stored vector instead.
//
// The horizontal distance is `sqrt(x*x + z*z)` over the doubles at +0x00 and
// +0x08, and that plus the double at +0x10 goes into the same arctangent, the
// same pi/2 subtraction and the same scaling.
//
// The return is a *two*-byte struct this time (`MOV word ptr [ECX],AX`, not the
// dword copy 0x4265B0 does), handed back through a hidden buffer that arrives
// as the first stack argument with `this` still in ECX - `RET 4` covers the
// buffer alone.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4CAC40 — square root, __cdecl.
double __cdecl FUN_004CAC40(double value);

struct Angle16_0041C2E0
{
    short Value;   // +0x0000

    // Declared, never defined: a user-declared copy assignment makes the type
    // non-POD, which is what puts a two-byte return in a caller-supplied buffer
    // instead of AX.
    Angle16_0041C2E0& operator=(const Angle16_0041C2E0& other);
};

struct Vector_0041C2E0
{
    double X;        // +0x0000
    double Z;        // +0x0008
    double Height;   // +0x0010

    // FUNCTION: GAMEMD 0x41C2E0
    Angle16_0041C2E0 FUN_0041C2E0();
};
GG_STATIC_ASSERT(offsetof(Vector_0041C2E0, Height) == 0x10);

#endif  // GG_MATCH_CORE_ANGLE_FROM_POINTS_METHODS_H
