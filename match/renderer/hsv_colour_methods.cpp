// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Three unsigned bytes at +0x00/+0x01/+0x02, read and written byte-wise by
// 0x517360 and 0x5173F0. The class and component names are descriptive (the
// target list labels this area HSV); no size is asserted.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HSVColour
{
public:
    // FUNCTION: GAMEMD 0x517360
    void Adjust(unsigned char ratio, const HSVColour& other);
    // FUNCTION: GAMEMD 0x5173F0
    int Difference(const HSVColour& other) const;

    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02
};
GG_STATIC_ASSERT(offsetof(HSVColour, Hue)        == 0x00);
GG_STATIC_ASSERT(offsetof(HSVColour, Saturation) == 0x01);
GG_STATIC_ASSERT(offsetof(HSVColour, Value)      == 0x02);

// FUNCTION: GAMEMD 0x517360
void HSVColour::Adjust(unsigned char ratio, const HSVColour& other)
{
    Value = (unsigned char)(Value + ((other.Value - Value) * ratio) / 256);
    Saturation = (unsigned char)(Saturation + ((other.Saturation - Saturation) * ratio) / 256);
    Hue = (unsigned char)(Hue + ((other.Hue - Hue) * ratio) / 256);
}

// FUNCTION: GAMEMD 0x5173F0
int HSVColour::Difference(const HSVColour& other) const
{
    int hue = Hue - other.Hue;
    if (hue < 0) {
        hue = -hue;
    }
    int saturation = Saturation - other.Saturation;
    if (saturation < 0) {
        saturation = -saturation;
    }
    int value = Value - other.Value;
    if (value < 0) {
        value = -value;
    }
    return value * value + saturation * saturation + hue * hue;
}
