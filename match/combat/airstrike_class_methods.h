// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x41D830 (`MOV AL,[ECX+0x3C]`, `CMP EAX,[ECX+0x50]`). Method names
//   cross-checked against YRpp AirstrikeClass.h (consult-only, no LICENSE),
//   which binds StartMission @0x41D830 and ResetTarget @0x41DA20.
#ifndef GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H
#define GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ObjectClass;

struct AirstrikeClass
{
    char         _pad00[0x3C];          // +0x0000
    bool         unknown_3C;            // +0x003C  gates which path StartMission takes
    char         _pad3D[0x50 - 0x3D];   // +0x003D
    ObjectClass* Target;                // +0x0050

    // Declared ascending by retail address.
    void StartMission(ObjectClass* target);   // GAMEMD 0x41D830 (matched)

    // Retail callees we are NOT matching here — declared (no body) so cl emits
    // reloc-normalised direct __thiscall calls.
    void BeginMission(ObjectClass* target);   // GAMEMD 0x41D860 (placeholder name)
    void ResetTarget(ObjectClass* target);    // GAMEMD 0x41DA20
};

GG_STATIC_ASSERT(offsetof(AirstrikeClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(AirstrikeClass, Target)     == 0x50);

#endif  // GG_MATCH_COMBAT_AIRSTRIKE_CLASS_METHODS_H
