// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4158E0: `[ESI+0x2B4]`,
//   `[ESI+0x5A4]`, `[ESI+0x6D3]`, and the two slots `[EAX+0x480]` and
//   `[EDX+0x1E8]`.
#ifndef GG_MATCH_AI_MISSION_STOP_METHODS_H
#define GG_MATCH_AI_MISSION_STOP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Rules_004158E0
{
    char _pad000[0x54C];      // +0x0000
    int  At_54C;              // +0x054C
};
GG_STATIC_ASSERT(offsetof(Rules_004158E0, At_54C) == 0x54C);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_004158E0* RulesInstance;

// Declaration order matters — see match/_rt/gg_vslot.h. The class must be
// complete before the member-function-pointer types, or VC6 uses the 8-byte
// multiple-inheritance representation and emits a `this` adjustment.
struct Vtbl_004158E0;

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x4158E0 -> AircraftClass slot 152 (byte-off 0x260).
// That table is the only table in the image that holds it, so the slot is
// declared on AircraftClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AircraftClass_004158E0
{
    Vtbl_004158E0* Vtbl;      // +0x0000
    char _pad004[0x2B0];      // +0x0004
    AircraftClass_004158E0* Target;     // +0x02B4
    char _pad2B8[0x2EC];      // +0x02B8
    int  At_5A4;              // +0x05A4
    char _pad5A8[0x12B];      // +0x05A8
    char At_6D3;              // +0x06D3

    // FUNCTION: GAMEMD 0x5F6440 — distance to the target.
    int FUN_005F6440(AircraftClass_004158E0* target);

    // FUNCTION: GAMEMD 0x4158E0
    int FUN_004158E0();
};
GG_STATIC_ASSERT(offsetof(AircraftClass_004158E0, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(AircraftClass_004158E0, At_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(AircraftClass_004158E0, At_6D3) == 0x6D3);

typedef int (AircraftClass_004158E0::*Fn1E8_004158E0)(int mission, int immediate);
typedef int (AircraftClass_004158E0::*Fn480_004158E0)(AircraftClass_004158E0* target, int flag);

struct Vtbl_004158E0
{
    char _pad000[0x1E8];              // +0x0000
    Fn1E8_004158E0 At_1E8;            // +0x01E8
    char _pad1EC[0x480 - 0x1EC];      // +0x01EC
    Fn480_004158E0 At_480;            // +0x0480
};
GG_STATIC_ASSERT(offsetof(Vtbl_004158E0, At_1E8) == 0x1E8);
GG_STATIC_ASSERT(offsetof(Vtbl_004158E0, At_480) == 0x480);

#endif  // GG_MATCH_AI_MISSION_STOP_METHODS_H
