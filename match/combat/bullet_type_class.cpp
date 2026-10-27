// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x46C790  BulletTypeClass::FindOrAllocate      (__fastcall)
//   FUNCTION: GAMEMD 0x46C840  BulletTypeClass::SetScaledSpawnDelay (__thiscall)
//   FUNCTION: GAMEMD 0x46BBC0  BulletTypeClass::Construct (ctor; referenced, matched elsewhere)
//   GLOBAL:   GAMEMD 0xA83C80  BulletTypeClass::Array
//   STRING:   GAMEMD 0x817474  "<none>"
//   STRING:   GAMEMD 0x817694  "none"

#include "bullet_type_class.h"

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
