// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Four TechnoTypeClass member bodies, independently checked at their entries.
// This retained filename is provisional grouping, not attested original TU ownership.
#include "../_layout/techno_type_class.h"
#include "../_layout/rules_class.h"
#include "../combat/weapon_type_class.h"

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;

// FUNCTION: GAMEMD 0x711E90
bool TechnoTypeClass::vf_41()
{
    if (Weapon[0].WeaponType == 0 || PreventAttackMove != 0) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x711EC0
int TechnoTypeClass::vf_28()
{
    if (bools_C8C[13] != 0) {
        if (DAT_00A8B238 == 0) {
            return OwnerFlags;
        }
        return 0x7FFFFFFF;
    }
    return OwnerFlags;
}

// FUNCTION: GAMEMD 0x711EE0
int TechnoTypeClass::vf_34()
{
    return (int)(Cost * RulesInstance->unknown_1748 * 0.9);
}

// FUNCTION: GAMEMD 0x7120D0
int TechnoTypeClass::vf_44()
{
    int quotient = vf_43();
    quotient /= Strength / RulesInstance->unknown_16CC;
    const int scaled = (int)(quotient * RulesInstance->unknown_16D0);
    if (scaled <= 1) {
        return 1;
    }
    return scaled;
}

// FUNCTION: GAMEMD 0x712120
int TechnoTypeClass::vf_45()
{
    return RulesInstance->unknown_16CC;
}

// FUNCTION: GAMEMD 0x716290
int TechnoTypeClass::vf_29()
{
    switch (PipScale) {
    case 4:
        return 10;
    case 1:
        return Ammo;
    case 5:
        return Weapon[0].WeaponType->Damage;
    case 2:
        return vf_11() == 0x10 ? 3 : 5;
    case 3:
        return Passengers;
    default:
        return 0;
    }
}

// FUNCTION: GAMEMD 0x7170A0
HRESULT __stdcall TechnoTypeClass::GetSizeMax(ULARGE_INTEGER* size)
{
    HRESULT result = ObjectTypeClass::GetSizeMax(size);
    if (result < 0) {
        return result;
    }

    size->LowPart = size->LowPart + 4 + VoiceSelect.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSelectEnslaved.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSelectDeactivated.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceMove.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceAttack.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSpecialAttack.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceDie.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceFeedback.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + MoveSound.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DieSound.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + Explosion.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DestroyAnim.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisTypes.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisAnims.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + Dock.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisMaximums.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DamageParticleSystems.Vector.Count * 4;
    size->LowPart = size->LowPart + 4 + DestroyParticleSystems.Vector.Count * 4;
    return S_OK;
}

// FUNCTION: GAMEMD 0x717800
int TechnoTypeClass::vf_47()
{
    if (FlightLevel == -1) {
        return RulesInstance->unknown_7B4;
    }
    return FlightLevel;
}
