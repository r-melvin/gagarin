// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Imported sound API records, as populated in 40A090 and 40A340.
#ifndef GG_MODULE_TU002_SOUND_H
#define GG_MODULE_TU002_SOUND_H
#include "../_rt/gg_static_assert.h"
#pragma pack(push, 1)
struct Wave_0040A340
{
    unsigned short format, channels;
    unsigned rate, average;
    unsigned short alignment, bits, extra;
};
#pragma pack(pop)
GG_STATIC_ASSERT(sizeof(Wave_0040A340) == 18);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, format) == 0);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, channels) == 2);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, rate) == 4);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, average) == 8);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, alignment) == 12);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, bits) == 14);
GG_STATIC_ASSERT(offsetof(Wave_0040A340, extra) == 16);
struct Descriptor_0040A340
{
    unsigned size, flags, bytes, reserved;
    Wave_0040A340* format;
};
GG_STATIC_ASSERT(sizeof(Descriptor_0040A340) == 20);
GG_STATIC_ASSERT(offsetof(Descriptor_0040A340, size) == 0);
GG_STATIC_ASSERT(offsetof(Descriptor_0040A340, flags) == 4);
GG_STATIC_ASSERT(offsetof(Descriptor_0040A340, bytes) == 8);
GG_STATIC_ASSERT(offsetof(Descriptor_0040A340, reserved) == 12);
GG_STATIC_ASSERT(offsetof(Descriptor_0040A340, format) == 16);
struct Caps_0040A090 { unsigned size; char unknown_04[92]; };
GG_STATIC_ASSERT(sizeof(Caps_0040A090) == 96);
#endif
