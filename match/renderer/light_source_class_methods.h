// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x554A60-0x554A95), cross-checked
//   against YRpp (consult-only; reconfirmed numerically).
//
// LightSourceClass — a light post / radiation source. Activate/Deactivate flip
// the Activated flag @0x48 and (de)register the light by recomputing the light
// converts via the internal helper @0x554AF0.
#ifndef GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_H
#define GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct LightSourceClass
{
    void Activate(unsigned long dwZero);    // GAMEMD 0x554A60 __thiscall
    void Deactivate(unsigned long dwZero);  // GAMEMD 0x554A80 __thiscall

    // Internal recompute helper, shared by Activate/Deactivate/ChangeLevels.
    // Declared (no body) so cl emits a reloc-normalised __thiscall call.
    void Calculate(unsigned long dwZero);   // GAMEMD 0x554AF0 __thiscall

    // AbstractClass base + LightSourceClass properties occupy [0x00..0x47];
    // only the Activated flag @0x48 is touched by these two methods (P2 layout).
    char          _base[0x48];   // +0x00
    unsigned char Activated;     // +0x48
};

GG_STATIC_ASSERT(offsetof(LightSourceClass, Activated) == 0x48);

#endif  // GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_H
