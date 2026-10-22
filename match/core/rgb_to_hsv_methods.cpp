// Provenance: own-binary-via-Ghidra
// RGB -> HSV conversion, a __thiscall member on a 3-byte colour triple
// returning a 3-byte triple through the hidden return pointer (`ret 4`).
// Byte reads at [ECX+0..2] fix the field order; the result stores
// [ret+0..1] as a word (H, S) and [ret+2] as the maximum channel (V).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HSVClass
{
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02
};
GG_STATIC_ASSERT(offsetof(HSVClass, Hue) == 0);
GG_STATIC_ASSERT(offsetof(HSVClass, Saturation) == 1);
GG_STATIC_ASSERT(offsetof(HSVClass, Value) == 2);

class RGBClass
{
public:
    unsigned char Red;          // +0x00
    unsigned char Green;        // +0x01
    unsigned char Blue;         // +0x02

    HSVClass FUN_006613A0() const;
};
GG_STATIC_ASSERT(offsetof(RGBClass, Red) == 0);
GG_STATIC_ASSERT(offsetof(RGBClass, Green) == 1);
GG_STATIC_ASSERT(offsetof(RGBClass, Blue) == 2);

// FUNCTION: GAMEMD 0x6613A0
// PARTIAL (97.5%). Saturation is cleared after the channel minimum is found,
// not at its declaration; that order gives retail's register assignment. The
// remaining delta is the stack slot of the result temporary (retail [ESP+0x1C],
// ours [ESP+0x10]).
HSVClass RGBClass::FUN_006613A0() const
{
    HSVClass hsv;
    int red = Red;
    int green = Green;
    int blue = Blue;
    unsigned int hue = 0;
    int saturation;
    unsigned int rc, gc, bc;

    int value = (red > green) ? red : green;
    if (blue > value) value = blue;
    int low = (red < green) ? red : green;
    if (blue < low) low = blue;

    saturation = 0;

    if (value != 0) {
        saturation = ((value - low) * 255) / value;
        if (saturation != 0) {
            unsigned int delta = value - low;
            rc = (unsigned int)(value * 255 - red * 255) / delta;
            gc = (unsigned int)(value * 255 - green * 255) / delta;
            bc = (unsigned int)(value * 255 - blue * 255) / delta;
            if (value == red) {
                hue = (low == green) ? 0x500 + bc : 0x100 - gc;
            } else if (value == green) {
                hue = (low == blue) ? 0x100 + rc : 0x300 - bc;
            } else {
                hue = (low == red) ? 0x300 + gc : 0x500 - rc;
            }
            hue /= 6;
        }
    }

    hsv.Hue = (unsigned char)hue;
    hsv.Saturation = (unsigned char)saturation;
    hsv.Value = (unsigned char)value;
    return hsv;
}
