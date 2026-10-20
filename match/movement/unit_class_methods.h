// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp UnitClass.h (consult-only).
//
//   UnitClass : FootClass (FootClass sizeof = 0x6C0; spine in ../_layout).
//   The methods here touch:
//     - Deactivated @0x1C8  (TechnoClass base, already in the spine)
//     - FlagHouseIndex @0x6CC (UnitClass-specific; confirmed [ECX+0x6CC])
//   plus the ObjectClass virtual at primary-vtable slot +0x124 (Mark), invoked
//   through a fn-pointer cast (the spine models the vptrs as explicit fields, so
//   a real C++ virtual cannot be added without shifting the base layout).
#ifndef GG_MATCH_MOVEMENT_UNIT_CLASS_METHODS_H
#define GG_MATCH_MOVEMENT_UNIT_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"

// UnitClass — self-propelled ground vehicle. Derives FootClass at offset 0 and
// adds its own block from 0x6C0. Only the members the matched methods touch are
// modelled; the rest of the UnitClass span is P2.
struct UnitClass : FootClass
{
    int     CurrentFiringFrame;   // +0x6C0
    void*   Type;                 // +0x6C4  (UnitTypeClass*)
    void*   FollowerCar;          // +0x6C8  (UnitClass*)
    int     FlagHouseIndex;       // +0x6CC  (carries this house's flag; -1 = none)

    // FUNCTION: GAMEMD 0x70FBD0  UnitClass::IsDeactivated (__thiscall)
    bool IsDeactivated() const;
    // FUNCTION: GAMEMD 0x740DF0  UnitClass::FlagAttach    (__thiscall)
    bool FlagAttach(int houseIndex);
    // FUNCTION: GAMEMD 0x740E20  UnitClass::FlagRemove    (__thiscall)
    bool FlagRemove();
};

GG_STATIC_ASSERT(offsetof(UnitClass, CurrentFiringFrame) == 0x6C0);
GG_STATIC_ASSERT(offsetof(UnitClass, Type)               == 0x6C4);
GG_STATIC_ASSERT(offsetof(UnitClass, FollowerCar)        == 0x6C8);
GG_STATIC_ASSERT(offsetof(UnitClass, FlagHouseIndex)     == 0x6CC);

#endif  // GG_MATCH_MOVEMENT_UNIT_CLASS_METHODS_H
