// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x59D480. The constants
//   are the float literals 0.5, 10.0 and 0.02 read at 0x7ED764/0x7ED768/0x7ED76C
//   and the 2^-32 double at 0x7ED898 (the same scale 0x598000 uses).

#include "../_layout/cell.h"
#include "trivial_tu130_methods.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- table square root.
float __cdecl FUN_004CAC40(double value);

// The uniform [0, 1) draw that retail expands in place here (its out-of-line
// copy is 0x598000): the raw 32-bit draw scaled by 2^-32.
static inline double UniformDraw()
{
    unsigned int draw = DAT_00ABE890.FUN_0065C780();
    return (double)draw * 2.3283064370807974e-10;
}

// FUNCTION: GAMEMD 0x59D480
// PARTIAL: 92.1% -- same instruction multiset as retail; cl emits the 10.0 factor as a
// double constant (FMUL qword) where retail multiplies by the float constant, and loads the
// distance before the 0.5 factor where retail loads 0.5 first.
// Score a candidate cell against another: half the straight-line distance
// plus a random jitter of up to ten, less a small penalty per `penalty` point.
float __stdcall FUN_0059D480(const CellStruct* from, const CellStruct* to, int penalty)
{
    int dx = from->X - to->X;
    int dy = from->Y - to->Y;
    float distance = FUN_004CAC40((double)(dy * dy + dx * dx));
    double u = UniformDraw();
    return u * 10.0f + 0.5f * distance - penalty * 0.02f;
}
