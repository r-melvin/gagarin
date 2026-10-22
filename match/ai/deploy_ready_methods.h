// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and the vtable slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x41B890: `[ESI+0x2B4]`,
//   `[ESI+0xAC]`, `[ESI+0x3D4]`, `[ESI+0x3D5]`, `[ESI+0x5D4]`, and the
//   zero-argument slot `[EAX+0x184]` called twice.
#ifndef GG_MATCH_AI_DEPLOY_READY_METHODS_H
#define GG_MATCH_AI_DEPLOY_READY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x6EC300 — ask the linked type whether it is enabled.
char __fastcall FUN_006EC300(int linked);

struct Vtbl_0041B890;

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41B890 -> AircraftClass slot 311 (byte-off 0x4DC).
// That table is the only table in the image that holds it, so the slot is
// declared on AircraftClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AircraftClass_0041B890
{
    Vtbl_0041B890* Vtbl;     // +0x0000
    char _pad004[0xA8];      // +0x0004
    int  At_AC;              // +0x00AC
    char _pad0B0[0x204];     // +0x00B0
    void* At_2B4;            // +0x02B4
    char _pad2B8[0x11C];     // +0x02B8
    char At_3D4;             // +0x03D4
    char At_3D5;             // +0x03D5
    char _pad3D6[0x1FE];     // +0x03D6
    int  At_5D4;             // +0x05D4

    // FUNCTION: GAMEMD 0x41B890
    bool FUN_0041B890();
};
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B890, At_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B890, At_2B4) == 0x2B4);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B890, At_3D4) == 0x3D4);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B890, At_3D5) == 0x3D5);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B890, At_5D4) == 0x5D4);

typedef int (AircraftClass_0041B890::*Fn184_0041B890)();

struct Vtbl_0041B890
{
    char _pad000[0x184];         // +0x0000
    Fn184_0041B890 At_184;       // +0x0184
};
GG_STATIC_ASSERT(offsetof(Vtbl_0041B890, At_184) == 0x184);

#endif  // GG_MATCH_AI_DEPLOY_READY_METHODS_H
