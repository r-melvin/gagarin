// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI TypeDescriptor 0x817AD8 `.?AVFlasherClass@@` (class key V).
//   TechnoClass's class hierarchy descriptor lists it as a base at mdisp 0xF0.
//   No vtable: FlasherClass::Update (0x4CC770) reads `[ECX]` as the countdown
//   and writes the visible flag with `MOV byte [ECX+4],imm8`.
#ifndef GG_MATCH_LAYOUT_FLASHER_CLASS_H
#define GG_MATCH_LAYOUT_FLASHER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class FlasherClass
{
public:
    int  DurationRemaining;   // +0x00
    bool FlashingNow;         // +0x04

    bool Update();            // GAMEMD 0x4CC770
};

GG_STATIC_ASSERT(offsetof(FlasherClass, DurationRemaining) == 0x00);
GG_STATIC_ASSERT(offsetof(FlasherClass, FlashingNow)       == 0x04);
GG_STATIC_ASSERT(sizeof(FlasherClass)                      == 0x08);

#endif  // GG_MATCH_LAYOUT_FLASHER_CLASS_H
