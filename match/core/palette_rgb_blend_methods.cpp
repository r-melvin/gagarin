// Provenance: own-binary-via-Ghidra
// 256-entry three-byte color table and its color element. Layout read off the
// bodies at 0x626070 (0x100 three-byte zeroing loop, then a 0xC0-dword copy)
// and 0x661350 (byte reads at +0/+1/+2). Names are descriptive placeholders.
#include "../_rt/gg_static_assert.h"
#include <stddef.h>

struct ColorRGB_00661350
{
    unsigned char unknown_00;   // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char unknown_02;   // +0x02

    ColorRGB_00661350() : unknown_00(0), unknown_01(0), unknown_02(0) {}

    // retail thiscall helper, matched elsewhere in main as a separate view.
    void Blend(int ratio, const ColorRGB_00661350& target);
    int Difference(const ColorRGB_00661350& other) const;
};

GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_01) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_02) == 0x02);
// 0x626070 steps the element loop by 3.
GG_STATIC_ASSERT(sizeof(ColorRGB_00661350) == 0x03);

// GLOBAL: GAMEMD 0x00A83CD9 -- fixed target color pushed by 0x626170.
extern ColorRGB_00661350 DAT_00A83CD9;

struct ColorTable_00626070
{
    ColorRGB_00661350 Colors[256];   // +0x000

    ColorTable_00626070(const ColorTable_00626070& other);

    const ColorRGB_00661350& operator[](int index) const { return Colors[index % 256]; }

    void FUN_00626120(int ratio, const ColorTable_00626070& target);
    void FUN_00626170(int ratio, const char* marks);
    void FUN_006261B0(int ratio, const ColorTable_00626070& target, const char* marks);
    int Nearest(const ColorRGB_00661350& color) const;
};

GG_STATIC_ASSERT(offsetof(ColorTable_00626070, Colors) == 0x000);


// FUNCTION: GAMEMD 0x661350
int ColorRGB_00661350::Difference(const ColorRGB_00661350& other) const
{
    int r = unknown_00 - other.unknown_00;
    if (r < 0) r = -r;
    int g = unknown_01 - other.unknown_01;
    if (g < 0) g = -g;
    int b = unknown_02 - other.unknown_02;
    if (b < 0) b = -b;
    return r * 2 + g * 4 + b * 3;
}
