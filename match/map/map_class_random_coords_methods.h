// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x49F420: a __fastcall static with the hidden result
//   pointer in ECX (saved to the frame, written through at the end) and the
//   source coordinate in EDX, then distance and the centre flag on the
//   stack (RET 8); the scenario randomizer at 0xA8B230 + 0x218 (0x65C780,
//   one byte of the draw placed in the high byte of a zeroed 16-bit
//   direction), the binary-angle scale at 0x7E2810 (-2*pi/65536), the
//   table sin 0x4CACB0 and cos 0x4CAD00 each taking the angle as a pushed
//   double, __ftol 0x7C5F00, and the three-int coordinate constructor
//   0x41C230 building the result in the frame. Names cross-checked against
//   YRpp.
#ifndef GG_MATCH_MAP_MAP_CLASS_RANDOM_COORDS_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_RANDOM_COORDS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) — table sin(double).
extern "C" double __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) — table cos(double).
extern "C" double __cdecl FUN_004CAD00(double angle);

// GLOBAL: GAMEMD 0x7E2810 — radians per binary-angle unit, negated.
extern const double DAT_007E2810;

// The scenario randomizer; only the raw draw is called.
struct Random_0049F420
{
    // FUNCTION: GAMEMD 0x65C780 (decl; reloc) — Randomizer::Random.
    int Random();
};

// ScenarioClass — only Random @0x218 is touched.
struct Scenario_0049F420
{
    char             _pad000[0x218];   // +0x0000
    Random_0049F420  Random;           // +0x0218
};
GG_STATIC_ASSERT(offsetof(Scenario_0049F420, Random) == 0x218);
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_0049F420* DAT_00A8B230;

// A binary angle: the facing byte sits in the high half of the 16-bit value.
// The bit-fields use an int container and the value is built through the
// constructor and a setter: retail zeroes it with a word store before the
// random draw (the object is address-taken through `this`), reads the
// container back as a dword, masks the high byte with `AND DH,0` and ORs
// the draw in — the int-container bit-field store.
struct Dir_0049F420
{
    union
    {
        unsigned short Raw;
        short          Signed;
        struct
        {
            unsigned int Low  : 8;
            unsigned int High : 8;
        } Bits;
    };

    Dir_0049F420() { Raw = 0; }
    void SetHigh(int value) { Bits.High = value; }
};
GG_STATIC_ASSERT(sizeof(Dir_0049F420) == 4);


// CoordStruct. The user-declared constructor is what selects the
// hidden-pointer return convention (see the banked "Struct returns" rule).
struct Coord_0049F420
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008

    Coord_0049F420() {}
    // FUNCTION: GAMEMD 0x41C230 (decl; reloc) — the three-int constructor.
    Coord_0049F420(int x, int y, int z);
};
GG_STATIC_ASSERT(sizeof(Coord_0049F420) == 0xC);

// FUNCTION: GAMEMD 0x49F420 — MapClass::GetRandomCoordsNear (static).
Coord_0049F420 __fastcall MapClass_GetRandomCoordsNear(const Coord_0049F420& coords,
                                                       int distance, bool center);

#endif  // GG_MATCH_MAP_MAP_CLASS_RANDOM_COORDS_METHODS_H
