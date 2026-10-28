// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Function entries and member offsets are confirmed in retail gamemd.exe
//   v1.001. RTTI: the locator at 0x7FB4C0 points to type descriptor
//   0x817B90, whose name is ".?AVAircraftClass@@"; the locator slot at
//   0x7E22A0 points to that locator, and the primary table starts at 0x7E22A4.
//   Its entries at 0x7E2498 and 0x7E27CC contain 0x41BB30 and 0x41BBD0,
//   respectively (byte offsets +0x1F4 / +0x528, slots 125 / 330).
#ifndef GG_MATCH_AI_AIRCRAFT_HELPERS_0041BB30_H
#define GG_MATCH_AI_AIRCRAFT_HELPERS_0041BB30_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Vtbl_0041BB30;
struct Object_0041BB30
{
    char unknown_000[0xE0D];
    unsigned char At_E0D;
};
GG_STATIC_ASSERT(offsetof(Object_0041BB30, At_E0D) == 0xE0D);
GG_STATIC_ASSERT(sizeof(Object_0041BB30) == 0xE0E);

struct AircraftClass_0041BB30
{
    Vtbl_0041BB30* Vtbl;                 // +0x000
    char unknown_004[0xA8];              // +0x004
    int At_AC;                             // +0x0AC
    char unknown_0B0[0x1E4];             // +0x0B0
    int At_294;                           // +0x294
    char unknown_298[0x42C];             // +0x298
    Object_0041BB30* At_6C4;              // +0x6C4
    char unknown_6C8[4];                 // +0x6C8
    void* At_6CC;                         // +0x6CC

    // FUNCTION: GAMEMD 0x41BB30
    void FUN_0041BB30(int first, int second, int third);

    // The direct callee is a thiscall method; the original binary calls it
    // with this in ECX and three stack arguments.
    // FUNCTION: GAMEMD 0x4D8F40 — direct thiscall target of 0x41BB30.
    void FUN_004D8F40(int first, int second, int third);
};

GG_STATIC_ASSERT(offsetof(AircraftClass_0041BB30, Vtbl) == 0x000);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041BB30, At_AC) == 0x0AC);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041BB30, At_294) == 0x294);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041BB30, At_6C4) == 0x6C4);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041BB30, At_6CC) == 0x6CC);
GG_STATIC_ASSERT(sizeof(AircraftClass_0041BB30) == 0x6D0);

typedef int (AircraftClass_0041BB30::*Fn278_0041BB30)(int mission, void* target);
struct Vtbl_0041BB30
{
    char unknown_000[0x278];
    // FUNCTION: GAMEMD 0x65A970 — target read from primary vtable +0x278.
    Fn278_0041BB30 At_278;
};
GG_STATIC_ASSERT(offsetof(Vtbl_0041BB30, At_278) == 0x278);
GG_STATIC_ASSERT(sizeof(Fn278_0041BB30) == 4);
GG_STATIC_ASSERT(sizeof(Vtbl_0041BB30) == 0x27C);

#endif  // GG_MATCH_AI_AIRCRAFT_HELPERS_0041BB30_H
