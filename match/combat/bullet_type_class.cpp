// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Function claims in this TU are ordered by their retail entry addresses.

#include "bullet_type_class.h"
#include "../core/abstract_registry.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x46BBC0
BulletTypeClass::BulletTypeClass(const char* id)
    : ObjectTypeClass(id)
{
    unknown_294 = 0;
    unknown_295 = 0;
    unknown_296 = 0;
    unknown_297 = 0;
    unknown_298 = 0;
    unknown_299 = 0;
    unknown_29A = 1;
    unknown_29B = 0;
    unknown_29C = 0;
    unknown_29D = 0;
    unknown_29E = 0;
    unknown_29F = 0;
    unknown_2A0 = 0;
    unknown_2A1 = 1;
    unknown_2A2 = 0;
    unknown_2A3 = 0;
    unknown_2A4[0] = 0;
    unknown_2A4[1] = 1;

    unknown_2D0 = 3;
    unknown_2E4 = 3;

    unknown_2A6 = 0;
    unknown_2A7 = 0;
    unknown_2A8 = 0;
    unknown_2A9 = 0;
    unknown_2AC = 1;
    AirburstWeapon = 0;
    ShrapnelWeapon = 0;
    ShrapnelCount = 0;
    unknown_2BC = 0;
    unknown_2C0 = 0;
    unknown_2C1[0] = 0;
    unknown_2C1[1] = 0;
    unknown_2C1[2] = 0;
    unknown_2C8 = 0.75;
    unknown_2D4[0] = 0;
    unknown_2D4[1] = 0;
    unknown_2D4[2] = 0;
    unknown_2D4[3] = 0;
    unknown_2D8 = 0;
    unknown_2DC = 0;
    unknown_2E0 = 0;
    ScaledSpawnDelay = 0;
    unknown_2EC = 0;
    unknown_2F0 = 0;
    unknown_2F4 = 0;
    unknown_2F5 = 0;
    unknown_2F6 = 0;
    unknown_2F7 = 0;

    // The native call targets AbstractClass's RTTI-interface slot 5.
    AbstractClass::vf_rtti_5();

    IsLogic = true;
    RadarInvisible = true;
    Selectable = false;
    LegalTarget = false;
    Insignificant = true;
    Immune = true;
    AllowCellContent = false;

    BulletTypeClass_Array.AddItem(this);
    // Native instructions at 0x46BD84..0x46BDD4 treat 0xB0F670 as a
    // pointer-valued DynamicVectorClass and append this through slot +8.
    reinterpret_cast<DynamicVectorClass<void*>*>(&DAT_00B0F670)->AddItem((void*)this);
}

// FUNCTION: GAMEMD 0x46BDE0
BulletTypeClass::BulletTypeClass(const AbstractNoInit& noInit)
    : ObjectTypeClass(noInit)
{
}

// CRT case-insensitive compare (_strcmpi @ GAMEMD 0x7C8D20). Declared (no body)
// so the call is a reloc; excluded from the match target.
int __cdecl gg_strcmpi(const char* a, const char* b);

// FUNCTION: GAMEMD 0x46C790  (__fastcall)
// Find the bullet type named `id` in the global Array (case-insensitive); if it
// is not present, allocate and construct a fresh one. The reserved names
// "<none>" and "none" are rejected (return null).
BulletTypeClass* BulletTypeClass::FindOrAllocate(const char* id)
{
    // Single shared `return 0` tail (one `xor eax,eax` epilogue, reached by JZ
    // from both reserved-name rejects and the alloc-failure path) — the retail
    // shape. The two rejects are folded into one short-circuit `&&` so the
    // compiler merges the null exits instead of emitting a local zero-return at
    // each site.
    if (gg_strcmpi("<none>", id) != 0 && gg_strcmpi("none", id) != 0)
    {
        for (int i = 0; i < BulletTypeClass_Array.Count; ++i)
        {
            if (gg_strcmpi(BulletTypeClass_Array.Items[i]->ID, id) == 0)
                return BulletTypeClass_Array.Items[i];
        }

        // Hand-rolled `new BulletTypeClass(id)`: raw operator new + null guard +
        // construct. Spelled out (rather than a new-expression) because the
        // retail site has no /GX exception-cleanup frame around construction.
        BulletTypeClass* p = (BulletTypeClass*)::operator new(sizeof(BulletTypeClass));
        if (p)
            return p->Construct(id);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x46C840  (__thiscall)
void BulletTypeClass::SetScaledSpawnDelay(int delay)
{
    ScaledSpawnDelay = delay;
}
