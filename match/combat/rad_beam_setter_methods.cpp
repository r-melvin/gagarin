// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x659470, 0x6594A0, 0x6594C0, 0x659580 and
//   0x65A1B0. Small RadBeam setters and an integer-vector divide that sits in the same unit; the
//   receivers are placeholder views of just the members touched.
//
// Address index: 0x659470 0x6594A0 0x6594C0 0x659580 0x65A1B0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rgb3_00659470
{
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
};

struct Int3_006594A0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
};

// RadBeam members: colour at +0x20, two coordinates at +0x24 and +0x30, a double at +0x18.
struct RadBeamView_00659470
{
    char          unknown_00[0x18];
    double        unknown_18;       // +0x18
    Rgb3_00659470 unknown_20;       // +0x20
    char          unknown_23;       // +0x23
    Int3_006594A0 unknown_24;       // +0x24
    Int3_006594A0 unknown_30;       // +0x30

    void FUN_00659470(const Rgb3_00659470& color);
    void FUN_006594A0(const Int3_006594A0& value);
    void FUN_006594C0(const Int3_006594A0& value);
    void FUN_00659580(int value);
};
GG_STATIC_ASSERT(offsetof(RadBeamView_00659470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(RadBeamView_00659470, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(RadBeamView_00659470, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(RadBeamView_00659470, unknown_30) == 0x30);

// FUNCTION: GAMEMD 0x659470
// Set the beam colour.
void RadBeamView_00659470::FUN_00659470(const Rgb3_00659470& color)
{
    unknown_20 = color;
}

// FUNCTION: GAMEMD 0x6594A0
// Set the first coordinate triple.
void RadBeamView_00659470::FUN_006594A0(const Int3_006594A0& value)
{
    unknown_24 = value;
}

// FUNCTION: GAMEMD 0x6594C0
// Set the second coordinate triple.
void RadBeamView_00659470::FUN_006594C0(const Int3_006594A0& value)
{
    unknown_30 = value;
}

// FUNCTION: GAMEMD 0x659580
// Set the double at +0x18 from an integer.
void RadBeamView_00659470::FUN_00659580(int value)
{
    unknown_18 = value;
}

// Integer triple that divides itself by a scalar.
struct IntVec3_0065A1B0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;

    IntVec3_0065A1B0& FUN_0065A1B0(int divisor);
};

// FUNCTION: GAMEMD 0x65A1B0
// Divide every component by the divisor; a zero divisor leaves it unchanged.
IntVec3_0065A1B0& IntVec3_0065A1B0::FUN_0065A1B0(int divisor)
{
    if (divisor != 0) {
        unknown_0 /= divisor;
        unknown_4 /= divisor;
        unknown_8 /= divisor;
    }
    return *this;
}
