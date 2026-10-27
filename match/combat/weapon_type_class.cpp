// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7729F0  WeaponTypeClass::CalculateSpeed  (__thiscall)
//   FUNCTION: GAMEMD 0x772A90  WeaponTypeClass::AllowedThreats  (__thiscall)
//   FUNCTION: GAMEMD 0x772FA0  WeaponTypeClass::FindOrAllocate  (__fastcall)
//   FUNCTION: GAMEMD 0x771C70  WeaponTypeClass::Construct (ctor; referenced, matched elsewhere)
//   GLOBAL:   GAMEMD 0x887568  WeaponTypeClass::Array
//   GLOBAL:   GAMEMD 0x8871E0  GameRulesPtr
//   STRING:   GAMEMD 0x817474  "<none>"
//   STRING:   GAMEMD 0x817694  "none"

#include "weapon_type_class.h"

// CRT case-insensitive compare (_strcmpi @ GAMEMD 0x7C8D20). Declared (no body)
// so the call is a reloc; excluded from the match target.
int __cdecl gg_strcmpi(const char* a, const char* b);

// FUNCTION: GAMEMD 0x7729F0  (__thiscall)
// Recompute the launch Speed of this weapon: if the projectile exists and its
// gating field @0x2DC is clear, take the gravity baseline (Rules int @0x16B8)
// — or the Func_0048ACF0 value when the projectile byte at +0x295 is set — and feed
// it with the weapon Range to Func_0048AB90, storing the result in Speed.
void WeaponTypeClass::CalculateSpeed()
{
    BulletTypeClass* proj = this->Projectile;
    if (proj != 0 && proj->unknown_2DC == 0)
    {
        double v = (double)GameRulesPtr->Field16B8;
        if (proj->unknown_295 != 0)
            v = Func_0048ACF0();
        this->Speed = (int)Func_0048AB90(this->Range, v);
    }
}

// FUNCTION: GAMEMD 0x772A90  (__thiscall)
// Build the projectile threat mask from native byte fields +0x2A4 and +0x2A5;
// the second condition corresponds to the retail `or al,0xB8` operation.
int WeaponTypeClass::AllowedThreats()
{
    BulletTypeClass* proj = this->Projectile;
    int threats = 0;
    if (proj->unknown_2A4[0])
        threats = 4;
    if (proj->unknown_2A4[1])
        threats |= 0xB8;
    return threats;
}

// FUNCTION: GAMEMD 0x772FA0  (__fastcall)
// Find the weapon type named `id` in the global Array (case-insensitive); if it
// is not present, allocate and construct a fresh one. The reserved names
// "<none>" and "none" are rejected (return null).
WeaponTypeClass* WeaponTypeClass::FindOrAllocate(const char* id)
{
    if (gg_strcmpi("<none>", id) != 0 && gg_strcmpi("none", id) != 0)
    {
        for (int i = 0; i < WeaponTypeClass_Array.Count; ++i)
        {
            if (gg_strcmpi(WeaponTypeClass_Array.Items[i]->ID, id) == 0)
                return WeaponTypeClass_Array.Items[i];
        }

        // Hand-rolled `new WeaponTypeClass(id)`: raw operator new + null guard +
        // construct (no /GX exception-cleanup frame around construction).
        WeaponTypeClass* p = (WeaponTypeClass*)::operator new(sizeof(WeaponTypeClass));
        if (p)
            return p->Construct(id);
    }
    return 0;
}
