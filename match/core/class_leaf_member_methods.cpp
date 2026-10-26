// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// One-instruction leaf members that repeat at several addresses (constant
// returns, field reads and writes, return -1), found in the engine's class
// vtables. Their owning classes are not modelled here, so each address is a
// member of a placeholder owner `Obj_<ADDR>` that declares only the field it
// touches (earlier bytes are `unknown_XX`), with an offset assert. The
// vtable owner and slot read from retail are noted per function. Each address
// was verified separately.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// vtable owner / slot: -
struct Obj_00681060 {
    unsigned char unknown_00[0x4];
    int unknown_04;
    void FUN_00681060(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00681060, unknown_04) == 0x4);
// FUNCTION: GAMEMD 0x00681060
void Obj_00681060::FUN_00681060(int value)
{
    unknown_04 = value;
}

// vtable owner / slot: ShipLocomotionClass+4/s29
struct Obj_006A3E50 {
    int FUN_006A3E50(void*);
};
// FUNCTION: GAMEMD 0x006A3E50
int Obj_006A3E50::FUN_006A3E50(void*)
{
    return 2;
}

// vtable owner / slot: TeleportLocomotionClass+4/s29
struct Obj_00719E20 {
    int FUN_00719E20(void*);
};
// FUNCTION: GAMEMD 0x00719E20
int Obj_00719E20::FUN_00719E20(void*)
{
    return 2;
}

// vtable owner / slot: WalkLocomotionClass+4/s29
struct Obj_0075C7E0 {
    int FUN_0075C7E0(void*);
};
