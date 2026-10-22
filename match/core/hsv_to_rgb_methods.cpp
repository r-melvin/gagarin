// Provenance: own-binary-via-Ghidra
// SPDX-License-Identifier: GPL-3.0-or-later
// Three-byte hue/saturation/value colour converted to a three-byte RGB colour,
// a __thiscall member returning the triple through the hidden pointer
// (`RET 4`). Byte reads at [ECX+0..2] fix the field order. The six sector
// values sit in a local table and each output channel steps two entries
// further round it. 21 callers (scheme tint lookups among them).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RGBTripleValue
{
    unsigned char Red;    // +0x00
    unsigned char Green;  // +0x01
    unsigned char Blue;   // +0x02
};
GG_STATIC_ASSERT(offsetof(RGBTripleValue, Blue) == 2);

class HSVTriple
{
public:
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02

    RGBTripleValue FUN_00517440() const;
};
GG_STATIC_ASSERT(offsetof(HSVTriple, Hue) == 0);
GG_STATIC_ASSERT(offsetof(HSVTriple, Saturation) == 1);
GG_STATIC_ASSERT(offsetof(HSVTriple, Value) == 2);

// FUNCTION: GAMEMD 0x517440
RGBTripleValue HSVTriple::FUN_00517440() const
{
    int values[7];
    int hue = Hue;
    int sat = Saturation;
    int val = Value;

    int scaled = hue * 6;
    unsigned int frac = scaled % 255;

    values[2] = val;
    values[1] = val;
    values[3] = ((255 - (frac * sat) / 255) * val) / 255;
    values[5] = ((255 - sat) * val) / 255;
    values[4] = values[5];
    values[6] = ((255 - ((255 - frac) * sat) / 255) * val) / 255;

    RGBTripleValue rgb;
    unsigned int index = scaled / 255;
    index += (index > 4) ? -4 : 2;
    rgb.Red = (unsigned char)values[index];
    index += (index > 4) ? -4 : 2;
    rgb.Blue = (unsigned char)values[index];
    index += (index > 4) ? -4 : 2;
    rgb.Green = (unsigned char)values[index];
    return rgb;
}
