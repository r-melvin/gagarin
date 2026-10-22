// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI. 0x70FEB0 reads `[ECX+0x1CC]` and is the exact twin of
//   the already-matched 0x70FEC0 in match/economy/building_class_drain.cpp,
//   which reads `[ECX+0x1D0]`; the two pointers sit side by side and are the
//   two ends of the same drain link. 0x710460 tail-jumps to 0x472140 with
//   `[ECX+0x2BC]` already in ECX. 0x710600 and 0x710630 both dispatch through
//   vtable slot +0x2C (the type discriminator) and slot +0x84 (the type
//   object), then read the byte at +0xD97 of the type. Every offset and
//   every convention is derived here from the disassembly.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LINK_QUERY_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LINK_QUERY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x472140 (decl; reloc) — release the waypoint buffer.
void FUN_00472140(void* buffer);

// The type object: only the byte at +0xD97 is read here.
struct LocoType_00710600
{
    char _pad000[0xD97];   // +0x0000
    char Flag_D97;         // +0x0D97
};
GG_STATIC_ASSERT(offsetof(LocoType_00710600, Flag_D97) == 0xD97);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00710600;

struct LocoObject_0070FEB0
{
    Vtbl_00710600* Vtbl;                 // +0x0000
    char           _pad004[0x1CC - 0x04];
    void*          DrainingWhom;         // +0x01CC
    void*          DrainingMe;           // +0x01D0
    char           _pad1D4[0x2BC - 0x1D4];
    void*          WaypointBuffer;       // +0x02BC

    // FUNCTION: GAMEMD 0x70FEB0
    bool IsDraining() const;
    // FUNCTION: GAMEMD 0x710460
    void FreeWaypointBuffer();
    // FUNCTION: GAMEMD 0x710600
    int CanFireFromGround();
    // FUNCTION: GAMEMD 0x710630
    int CanFireAny();
};
GG_STATIC_ASSERT(offsetof(LocoObject_0070FEB0, DrainingWhom)   == 0x1CC);
GG_STATIC_ASSERT(offsetof(LocoObject_0070FEB0, DrainingMe)     == 0x1D0);
GG_STATIC_ASSERT(offsetof(LocoObject_0070FEB0, WaypointBuffer) == 0x2BC);

typedef int                  (LocoObject_0070FEB0::*Fn2C_00710600)();
typedef LocoType_00710600*   (LocoObject_0070FEB0::*Fn84_00710600)();

struct Vtbl_00710600
{
    char          _pad000[0x2C];         // +0x0000
    Fn2C_00710600 WhatAmI;               // +0x002C
    char          _pad030[0x84 - 0x30];  // +0x0030
    Fn84_00710600 GetType;               // +0x0084
};
GG_STATIC_ASSERT(offsetof(Vtbl_00710600, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_00710600, GetType) == 0x84);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_LINK_QUERY_METHODS_H
