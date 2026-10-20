// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x554AA0-0x554AE5), cross-checked
//   against YRpp LightSourceClass.h / BasicStructures.h (consult-only;
//   reconfirmed numerically from the disasm).
//
// LightSourceClass — extra (ChangeLevels) binding. Models only the members the
// ChangeLevels method touches: LightIntensity@0x24, the TintStruct LightTint
// (Red@0x28, Green@0x2c, Blue@0x30) and the Activated flag@0x48.
#ifndef GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H
#define GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TintStruct
{
    int Red, Green, Blue;
};

struct LightSourceClass
{
    void ChangeLevels(int nIntensity, TintStruct Tint, unsigned long mode);

    // Internal recompute helper @0x554AF0, shared with Activate/Deactivate.
    // Declared (no body) so cl emits a reloc-normalised __thiscall call.
    void Calculate(unsigned long mode);

    char       _base[0x24];   // +0x00  AbstractClass base + leading props
    int        LightIntensity; // +0x24
    TintStruct LightTint;      // +0x28  (Red +0x28, Green +0x2c, Blue +0x30)
    int        DetailLevel;    // +0x34
    int        LocationX;      // +0x38  CoordStruct Location
    int        LocationY;      // +0x3c
    int        LocationZ;      // +0x40
    int        LightVisibility; // +0x44
    unsigned char Activated;   // +0x48
};

GG_STATIC_ASSERT(offsetof(LightSourceClass, LightIntensity) == 0x24);
GG_STATIC_ASSERT(offsetof(LightSourceClass, LightTint)      == 0x28);
GG_STATIC_ASSERT(offsetof(LightSourceClass, DetailLevel)    == 0x34);
GG_STATIC_ASSERT(offsetof(LightSourceClass, Activated)      == 0x48);

#endif  // GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H
