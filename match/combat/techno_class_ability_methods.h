// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and the vtable slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x70D0D0:
//   `LEA EDI,[ESI+0x150]` (TechnoClass::Veterancy), `CALL [EAX+0x84]`
//   (GetTechnoType slot), `[ESI+EBX+0x29C]` (TechnoTypeClass::VeteranAbilities)
//   and `[ESI+EBX+0x2AE]` (TechnoTypeClass::EliteAbilities), with the two
//   helpers at 0x74FF90 / 0x750010 taking the VeterancyStruct in ECX.
//   Every offset agrees with the committed spines match/_layout/techno_class.h
//   and match/_layout/techno_type_class.h (the latter cannot be included next
//   to the former — both define TurretControl — so the two ability tables are
//   modelled by a local placeholder here). Method name from YRpp TechnoClass.h
//   (HasAbility @0x70D0D0, consult-only).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_ABILITY_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_ABILITY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/techno_class.h"   // TechnoClass (Veterancy @0x150), VeterancyStruct

// The two veterancy gauge tests, reached by a direct CALL with the
// VeterancyStruct in ECX. Declared-only so cl emits a reloc-normalised CALL;
// a single-pointer __fastcall has the same call shape as a 0-arg __thiscall.
// FUNCTION: GAMEMD 0x74FF90 (decl; reloc) — gauge is in the veteran band.
bool __fastcall FUN_0074FF90(VeterancyStruct* vet);
// FUNCTION: GAMEMD 0x750010 (decl; reloc) — gauge is in the elite band.
bool __fastcall FUN_00750010(VeterancyStruct* vet);

// TechnoTypeClass view: only the two per-ability bool tables touched here.
struct TechnoType_0070D0D0
{
    char          _pad000[0x29C];        // +0x0000
    unsigned char VeteranAbilities[0x12]; // +0x029C (bool[18])
    unsigned char EliteAbilities[0x12];   // +0x02AE (bool[18])
};
GG_STATIC_ASSERT(offsetof(TechnoType_0070D0D0, VeteranAbilities) == 0x29C);
GG_STATIC_ASSERT(offsetof(TechnoType_0070D0D0, EliteAbilities)   == 0x2AE);

// Declaration order matters — see match/_rt/gg_vslot.h. The class must be
// complete before the member-function-pointer type, or VC6 uses the 8-byte
// multiple-inheritance representation and emits a `this` adjustment.
struct Vtbl_0070D0D0;

// This address-scoped derived view adds a matched method at offset zero,
// without adjusting this. Its raw vptr access predates the class-key fix;
// the former access issue is resolved in the shared spine. This view does not
// establish the complete TechnoClass hierarchy.
struct Techno_0070D0D0 : TechnoClass
{
    // FUNCTION: GAMEMD 0x70D0D0 — TechnoClass::HasAbility
    bool HasAbility(int ability);
};
GG_STATIC_ASSERT(offsetof(Techno_0070D0D0, Veterancy) == 0x150);
GG_STATIC_ASSERT(sizeof(Techno_0070D0D0)              == 0x520);

typedef TechnoType_0070D0D0* (IPersistStream::*Fn084_0070D0D0)();

struct Vtbl_0070D0D0
{
    char           _pad000[0x84];   // +0x0000
    Fn084_0070D0D0 At_084;          // +0x0084  GetTechnoType()
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070D0D0, At_084) == 0x84);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_ABILITY_METHODS_H
