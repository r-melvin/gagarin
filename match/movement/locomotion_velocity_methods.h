// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70F670 and 0x70F6A0. The pair apply and undo one
//   object's contribution to a mover's accumulated velocity: the apply reads
//   the current contribution through vtable slot +0x2C0, remembers it at
//   +0x508, converts it through slot +0x38 and hands it to the mover; the
//   undo negates the remembered value, converts it the same way, hands it
//   over and forgets it. Every offset and
//   convention is derived here.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_VELOCITY_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_VELOCITY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The mover that accumulates the contributions.
struct Mover_0070F670
{
    // FUNCTION: GAMEMD 0x481870 (decl; reloc) — accumulate one contribution.
    void Accumulate(int amount);
};

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_0070F670;

struct VelocitySource_0070F670
{
    Vtbl_0070F670* Vtbl;                  // +0x0000
    char           _pad004[0x508 - 0x04];
    int            Contribution;          // +0x0508

    // FUNCTION: GAMEMD 0x70F670
    void ApplyVelocity(Mover_0070F670* mover);
    // FUNCTION: GAMEMD 0x70F6A0
    void RemoveVelocity(Mover_0070F670* mover);
};
GG_STATIC_ASSERT(offsetof(VelocitySource_0070F670, Contribution) == 0x508);

typedef int (VelocitySource_0070F670::*Fn2C0_0070F670)();
typedef int (VelocitySource_0070F670::*Fn38_0070F670)(int amount);

struct Vtbl_0070F670
{
    char           _pad000[0x38];          // +0x0000
    Fn38_0070F670  Convert;                // +0x0038
    char           _pad03C[0x2C0 - 0x3C];  // +0x003C
    Fn2C0_0070F670 CurrentContribution;    // +0x02C0
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070F670, Convert)             == 0x38);
GG_STATIC_ASSERT(offsetof(Vtbl_0070F670, CurrentContribution) == 0x2C0);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_VELOCITY_METHODS_H
