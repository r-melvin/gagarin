// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x71ABC0: the temporal's Target at +0x28, the two
//   dwords at +0x38/+0x3C cleared with it, the chain links PrevTemporal
//   +0x40 / NextTemporal +0x44 and the accumulator at +0x48 handed to the
//   next link; on the target TemporalTargetingMe at +0x278, the byte at
//   +0x270, Owner at +0x21C with the house bytes +0x5778 / +0x1FC, the
//   WhatAmI slot +0x2C (6 = building) and the Mark slot +0x124 (one int);
//   0x452210 is a __thiscall on the building. YRpp
//   names LetGo, Target, PrevTemporal, NextTemporal,
//   TemporalTargetingMe and BeingWarpedOut.
#ifndef GG_MATCH_COMBAT_TEMPORAL_CLASS_LET_GO_METHODS_H
#define GG_MATCH_COMBAT_TEMPORAL_CLASS_LET_GO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Temporal_0071ABC0;
struct VtblT_0071ABC0;

struct House_0071ABC0
{
    char _pad0000[0x1FC];              // +0x0000
    char RecheckTechTree;              // +0x01FC
    char _pad01FD[0x5778 - 0x1FD];     // +0x01FD
    char PowerBlackoutWasActivated;    // +0x5778
};
GG_STATIC_ASSERT(offsetof(House_0071ABC0, RecheckTechTree) == 0x1FC);
GG_STATIC_ASSERT(offsetof(House_0071ABC0, PowerBlackoutWasActivated) == 0x5778);

struct Techno_0071ABC0
{
    VtblT_0071ABC0* Vptr;                    // +0x0000
    char _pad0004[0x21C - 0x04];             // +0x0004
    House_0071ABC0* Owner;                   // +0x021C
    char _pad0220[0x270 - 0x220];            // +0x0220
    char BeingWarpedOut;                     // +0x0270
    char _pad0271[0x278 - 0x271];            // +0x0271
    Temporal_0071ABC0* TemporalTargetingMe;  // +0x0278

    // FUNCTION: GAMEMD 0x452210 (decl; reloc) — building power recount.
    void FUN_00452210();
};
GG_STATIC_ASSERT(offsetof(Techno_0071ABC0, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(Techno_0071ABC0, BeingWarpedOut) == 0x270);
GG_STATIC_ASSERT(offsetof(Techno_0071ABC0, TemporalTargetingMe) == 0x278);

typedef int  (Techno_0071ABC0::*Fn2C_0071ABC0)();
typedef void (Techno_0071ABC0::*Fn124_0071ABC0)(int mark);

struct VtblT_0071ABC0
{
    char _pad000[0x2C];            // +0x0000
    Fn2C_0071ABC0 WhatAmI;         // +0x002C
    char _pad030[0x124 - 0x30];    // +0x0030
    Fn124_0071ABC0 Mark;           // +0x0124
};
GG_STATIC_ASSERT(offsetof(VtblT_0071ABC0, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(VtblT_0071ABC0, Mark) == 0x124);

struct Temporal_0071ABC0
{
    char _pad0000[0x28];               // +0x0000
    Techno_0071ABC0* Target;           // +0x0028
    char _pad002C[0x38 - 0x2C];        // +0x002C
    int At_38;                         // +0x0038
    int At_3C;                         // +0x003C
    Temporal_0071ABC0* PrevTemporal;   // +0x0040
    Temporal_0071ABC0* NextTemporal;   // +0x0044
    int At_48;                         // +0x0048

    // FUNCTION: GAMEMD 0x71ABC0 — TemporalClass::LetGo.
    void LetGo();
};
GG_STATIC_ASSERT(offsetof(Temporal_0071ABC0, Target) == 0x28);
GG_STATIC_ASSERT(offsetof(Temporal_0071ABC0, At_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Temporal_0071ABC0, PrevTemporal) == 0x40);
GG_STATIC_ASSERT(offsetof(Temporal_0071ABC0, NextTemporal) == 0x44);
GG_STATIC_ASSERT(offsetof(Temporal_0071ABC0, At_48) == 0x48);

#endif  // GG_MATCH_COMBAT_TEMPORAL_CLASS_LET_GO_METHODS_H
