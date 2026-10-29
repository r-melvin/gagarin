// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x668FB0.

#include "rules_class_ini_support.h"

// FUNCTION: GAMEMD 0x668FB0
//
// Read the [SpecialWeapons] section into the rules object. Reports whether the section exists.
bool RulesClass::Read_SpecialWeapons(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(SpecialWeaponsSection) != 0;
    } else {
        ok = pINI->GetEntry(SpecialWeaponsSection, key) != 0;
    }
    if (ok) {
        char buffer[0x80];

        { WarheadTypeClass* t0 = NukeWarhead; NukeWarhead = pINI->ReadString(SpecialWeaponsSection, "NukeWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t0; }
        { BulletTypeClass* t1 = NukeProjectile; NukeProjectile = pINI->ReadString(SpecialWeaponsSection, "NukeProjectile", STR_00889F64, buffer, 0x80) ? BulletType_FindPtr(buffer) : t1; }
        { BulletTypeClass* t2 = NukeDown; NukeDown = pINI->ReadString(SpecialWeaponsSection, "NukeDown", STR_00889F64, buffer, 0x80) ? BulletType_FindPtr(buffer) : t2; }
        { WarheadTypeClass* t3 = MutateWarhead; MutateWarhead = pINI->ReadString(SpecialWeaponsSection, "MutateWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t3; }
        { WarheadTypeClass* t4 = MutateExplosionWarhead; MutateExplosionWarhead = pINI->ReadString(SpecialWeaponsSection, "MutateExplosionWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t4; }
        { WarheadTypeClass* t5 = EMPulseWarhead; EMPulseWarhead = pINI->ReadString(SpecialWeaponsSection, "EMPulseWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t5; }
        { BulletTypeClass* t6 = EMPulseProjectile; EMPulseProjectile = pINI->ReadString(SpecialWeaponsSection, "EMPulseProjectile", STR_00889F64, buffer, 0x80) ? BulletType_FindPtr(buffer) : t6; }
        for (int i = 0; i < WarheadTypeCount; ++i) {
            WarheadTypeItems[i]->vf_25(pINI);
        }
        return true;
    }
    return false;
}
