// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include <math.h>
#include "flight_tuning_globals.h"

// FUNCTION: GAMEMD 0x005B2B90
// The cell diagonal: the hypotenuse of a 256-unit square. Retail wrote the
// square as a pow() call rather than a multiplication -- the x87 `FLD 256.0 /
// FLD 2.0 / CALL _CIpow` sequence is the intrinsic two-argument form -- and
// the doubling comes out as FADD ST,ST.
void __cdecl SetCellDiagonal()
{
    Tuning.CellDiagonal = gamemd_sqrt(2.0 * pow(256.0, 2.0));
}

// FUNCTION: GAMEMD 0x005B2BC0
// How far one cell diagonal is per game frame.
void __cdecl SetStepPerFrame()
{
    Tuning.StepPerFrame = Tuning.CellDiagonal / GG_FRAMES_PER_SECOND;
}

// FUNCTION: GAMEMD 0x005B2BE0
// Its reciprocal.
void __cdecl SetInverseStep()
{
    Tuning.InverseStep = 1.0 / Tuning.StepPerFrame;
}

// FUNCTION: GAMEMD 0x005B2C00
void __cdecl SetRadians45()
{
    Tuning.Radians45 = GG_DEGREES_TO_RADIANS * 45.0;
}

// FUNCTION: GAMEMD 0x005B2C20
void __cdecl SetRadians60()
{
    Tuning.Radians60 = GG_DEGREES_TO_RADIANS * 60.0;
}

// FUNCTION: GAMEMD 0x005B2C40
void __cdecl SetRadians90()
{
    Tuning.Radians90 = GG_DEGREES_TO_RADIANS * 90.0;
}

// FUNCTION: GAMEMD 0x005B2C60
// Half the span covered over the 30-degree wedge between the two stored
// angles, in world units, truncated to an integer.
void __cdecl SetHalfSpan()
{
    Tuning.HalfSpan = (int)(gamemd_tabletrig(Tuning.Radians90 - Tuning.Radians60) *
                            Tuning.CellDiagonal * 0.5);
}

// FUNCTION: GAMEMD 0x005B2CA0
void __cdecl SetStepScale()
{
    Tuning.StepScale = gamemd_tablescale(Tuning.HalfSpan * 0.00390625);
}

// FUNCTION: GAMEMD 0x005B2CD0
// The doubled span reaches the scale helper as a whole number of units, which
// is why retail materialises `HalfSpan * 2` into its own stack slot and FILDs
// it rather than doubling in the x87 stack.
void __cdecl SetSpanScale()
{
    Tuning.SpanScale = gamemd_tablescale((Tuning.HalfSpan * 2) / Tuning.CellDiagonal);
}

// FUNCTION: GAMEMD 0x005B2D00
void __cdecl SetSpanCells()
{
    Tuning.SpanCells = (int)(Tuning.HalfSpan * 4 + 0.5);
}

// FUNCTION: GAMEMD 0x005B2D30
void __cdecl ResetPair70()
{
    Tuning.Reset70 = 0;
    Tuning.Reset72 = 0;
}

// FUNCTION: GAMEMD 0x005B2D40
void __cdecl ResetTriple90()
{
    Tuning.Reset90 = 0;
    Tuning.Reset94 = 0;
    Tuning.Reset98 = 0;
}

// FUNCTION: GAMEMD 0x005B2D60
void __cdecl ResetLimits()
{
    Tuning.ResetC0 = 0;
    Tuning.Limit1B8 = 0x80;
    Tuning.Limit1BC = 0x80;
}

// FUNCTION: GAMEMD 0x005B2D80
void __cdecl ResetQuad60()
{
    Tuning.Reset60 = 0;
    Tuning.Reset64 = 0;
    Tuning.Reset68 = 0;
    Tuning.Reset6C = 0;
}
