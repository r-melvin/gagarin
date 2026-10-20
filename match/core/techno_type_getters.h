// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access disassembly at 0x7177C0 / 0x7177E0 / 0x7178C0). Signatures
//   cross-checked against YRpp TechnoTypeClass.h (consult-only, no LICENSE;
//   every offset reconfirmed numerically from the disassembly below).
//
// TechnoTypeClass weapon/particle-offset getters. The full TechnoTypeClass
// layout lives in the committed P2 spine (../_layout/techno_type_class.h);
// these are three small __thiscall accessors layered on top of it. The methods
// are hosted on a no-data derived struct so the spine header stays untouched
// (the COM vptrs are modelled as plain data fields there, so deriving adds no
// vtable and keeps `this`/every offset identical).
#ifndef GG_MATCH_CORE_TECHNO_TYPE_GETTERS_H
#define GG_MATCH_CORE_TECHNO_TYPE_GETTERS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_type_class.h"  // TechnoTypeClass, WeaponStruct, CoordStruct

// All members touched here are already pinned in the spine; re-assert the few
// the getters reach so this TU self-guards to the 32-bit ABI.
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DamageSmokeOffset) == 0x7B0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DamSmkOffScrnRel)  == 0x7BC);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Weapon)            == 0x898);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, EliteWeapon)       == 0xA94);

struct TechnoTypeGetters : TechnoTypeClass
{
    // FUNCTION: GAMEMD 0x7177C0  TechnoTypeClass::GetWeapon            (__thiscall)
    WeaponStruct* GetWeapon(int index);
    // FUNCTION: GAMEMD 0x7177E0  TechnoTypeClass::GetEliteWeapon       (__thiscall)
    WeaponStruct* GetEliteWeapon(int index);
    // FUNCTION: GAMEMD 0x7178C0  TechnoTypeClass::GetParticleSysOffset (__thiscall)
    CoordStruct*  GetParticleSysOffset(CoordStruct* pBuffer) const;
};

#endif  // GG_MATCH_CORE_TECHNO_TYPE_GETTERS_H
