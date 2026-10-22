// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x5B2B90, 0x5B2BC0, 0x5B2BE0, 0x5B2C00, 0x5B2C20, 0x5B2C40,
//   0x5B2C60, 0x5B2CA0, 0x5B2CD0, 0x5B2D00, 0x5B2D30, 0x5B2D40, 0x5B2D60 and
//   0x5B2D80.
//
// Fourteen leaf setters that sit immediately above VelocityClass::SetPitch
// (0x5B2A30) in the same address run as the Dir16 primitives and the flight
// step at 0x5B20F0. None of them appears in the Ghidra function list -- the
// analysis stops at 0x5B2A30 and the next listed entry is 0x5B2DA0 -- so they
// were found by walking the gap; each has a clean entry at a 16-byte boundary
// and its own RET. (The Ghidra function list is not a complete
// worklist.)
//
// Every one of them writes a field of one contiguous block of file-scope
// statics based at 0x00ABEF10, which is also where the flight step reads its
// unset-coordinate sentinel (+0x00), its bridge rise (+0x34) and its level
// height (+0x40). Modelling the block as a struct is free at the byte level --
// a field reference emits the base relocation with the displacement inside the
// relocation slot -- and it is what lets this translation unit carry real
// offsetof asserts, which a file of loose externs could not.
#ifndef GG_MATCH_MOVEMENT_FLIGHT_TUNING_GLOBALS_H
#define GG_MATCH_MOVEMENT_FLIGHT_TUNING_GLOBALS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The CRT/engine math entry points these bodies call. Distinct names, the
// tree's convention for library thunks: the diff harness normalises the call
// relocation, so only the call shape matters.
extern "C" {
double __cdecl gamemd_sqrt(double);                 // LIBRARY: GAMEMD 0x004CAC40
double __cdecl gamemd_tabletrig(double);            // LIBRARY: GAMEMD 0x004CAD50
double __cdecl gamemd_tablescale(double);           // LIBRARY: GAMEMD 0x004CADE0
}

// The doubles these bodies reference are compiler literal-pool entries, not
// named globals: retail's pool holds 2.0, 256.0, 1.0, 45.0, 60.0, 90.0, 0.5
// and 0.00390625 consecutively at 0x007E1708..0x007E1740, with 60.0 and
// pi/180 again at 0x007EDC80/0x007EDC88. Writing them as literals is what
// lets cl fold `2.0 * x` into FADD ST,ST, which an extern const cannot.
//
// GLOBAL: GAMEMD 0x007E1708  2.0
// GLOBAL: GAMEMD 0x007E1710  256.0
// GLOBAL: GAMEMD 0x007E1718  1.0
// GLOBAL: GAMEMD 0x007E1720  45.0
// GLOBAL: GAMEMD 0x007E1728  60.0
// GLOBAL: GAMEMD 0x007E1730  90.0
// GLOBAL: GAMEMD 0x007E1738  0.5
// GLOBAL: GAMEMD 0x007E1740  0.00390625
//
// The two entries at 0x007EDC80 and 0x007EDC88 are not pool entries: they are
// named globals in their own right, and the tell is that cl folds a product of
// two literals. Written as literals the three degree-to-radian setters
// collapse to a single constant load and score zero; written against these
// externs they emit retail's FLD/FMUL pair. The binary agrees -- it holds 60.0
// twice, once here and once in the literal pool at 0x007E1728.
//
// GLOBAL: GAMEMD 0x007EDC80
extern const double GG_FRAMES_PER_SECOND;
// GLOBAL: GAMEMD 0x007EDC88
extern const double GG_DEGREES_TO_RADIANS;

struct FlightTuning
{
    int    UnsetX;              // +0x00  0x00ABEF10
    int    UnsetY;              // +0x04  0x00ABEF14
    int    UnsetZ;              // +0x08  0x00ABEF18
    char   unknown_0C[0x28];    // +0x0C
    int    BridgeRise;          // +0x34  0x00ABEF44
    char   unknown_38[0x08];    // +0x38
    int    LevelHeight;         // +0x40  0x00ABEF50
    char   unknown_44[0x04];    // +0x44
    double Radians90;           // +0x48  0x00ABEF58
    int    Reset60;             // +0x50  0x00ABEF60
    int    Reset64;             // +0x54  0x00ABEF64
    int    Reset68;             // +0x58  0x00ABEF68
    int    Reset6C;             // +0x5C  0x00ABEF6C
    short  Reset70;             // +0x60  0x00ABEF70
    short  Reset72;             // +0x62  0x00ABEF72
    char   unknown_64[0x04];    // +0x64
    double CellDiagonal;        // +0x68  0x00ABEF78
    double Radians60;           // +0x70  0x00ABEF80
    double StepScale;           // +0x78  0x00ABEF88
    int    Reset90;             // +0x80  0x00ABEF90
    int    Reset94;             // +0x84  0x00ABEF94
    int    Reset98;             // +0x88  0x00ABEF98
    char   unknown_8C[0x04];    // +0x8C
    double SpanScale;           // +0x90  0x00ABEFA0
    double Radians45;           // +0x98  0x00ABEFA8
    double InverseStep;         // +0xA0  0x00ABEFB0
    int    Limit1B8;            // +0xA8  0x00ABEFB8
    int    Limit1BC;            // +0xAC  0x00ABEFBC
    int    ResetC0;             // +0xB0  0x00ABEFC0
    int    SpanCells;           // +0xB4  0x00ABEFC4
    double StepPerFrame;        // +0xB8  0x00ABEFC8
    int    HalfSpan;            // +0xC0  0x00ABEFD0
};

GG_STATIC_ASSERT(offsetof(FlightTuning, UnsetX)       == 0x00 &&
                 offsetof(FlightTuning, UnsetY)       == 0x04 &&
                 offsetof(FlightTuning, UnsetZ)       == 0x08 &&
                 offsetof(FlightTuning, BridgeRise)   == 0x34 &&
                 offsetof(FlightTuning, LevelHeight)  == 0x40 &&
                 offsetof(FlightTuning, Radians90)    == 0x48 &&
                 offsetof(FlightTuning, Reset60)      == 0x50 &&
                 offsetof(FlightTuning, Reset70)      == 0x60 &&
                 offsetof(FlightTuning, CellDiagonal) == 0x68);
GG_STATIC_ASSERT(offsetof(FlightTuning, Radians60)    == 0x70 &&
                 offsetof(FlightTuning, StepScale)    == 0x78 &&
                 offsetof(FlightTuning, Reset90)      == 0x80 &&
                 offsetof(FlightTuning, SpanScale)    == 0x90 &&
                 offsetof(FlightTuning, Radians45)    == 0x98 &&
                 offsetof(FlightTuning, InverseStep)  == 0xA0 &&
                 offsetof(FlightTuning, Limit1B8)     == 0xA8 &&
                 offsetof(FlightTuning, SpanCells)    == 0xB4 &&
                 offsetof(FlightTuning, StepPerFrame) == 0xB8 &&
                 offsetof(FlightTuning, HalfSpan)     == 0xC0 &&
                 sizeof(FlightTuning)                 == 0xC8);

// GLOBAL: GAMEMD 0x00ABEF10
extern FlightTuning Tuning;

// FUNCTION: GAMEMD 0x005B2B90
void __cdecl SetCellDiagonal();
// FUNCTION: GAMEMD 0x005B2BC0
void __cdecl SetStepPerFrame();
// FUNCTION: GAMEMD 0x005B2BE0
void __cdecl SetInverseStep();
// FUNCTION: GAMEMD 0x005B2C00
void __cdecl SetRadians45();
// FUNCTION: GAMEMD 0x005B2C20
void __cdecl SetRadians60();
// FUNCTION: GAMEMD 0x005B2C40
void __cdecl SetRadians90();
// FUNCTION: GAMEMD 0x005B2C60
void __cdecl SetHalfSpan();
// FUNCTION: GAMEMD 0x005B2CA0
void __cdecl SetStepScale();
// FUNCTION: GAMEMD 0x005B2CD0
void __cdecl SetSpanScale();
// FUNCTION: GAMEMD 0x005B2D00
void __cdecl SetSpanCells();
// FUNCTION: GAMEMD 0x005B2D30
void __cdecl ResetPair70();
// FUNCTION: GAMEMD 0x005B2D40
void __cdecl ResetTriple90();
// FUNCTION: GAMEMD 0x005B2D60
void __cdecl ResetLimits();
// FUNCTION: GAMEMD 0x005B2D80
void __cdecl ResetQuad60();

#endif  // GG_MATCH_MOVEMENT_FLIGHT_TUNING_GLOBALS_H
