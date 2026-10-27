// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Five TechnoTypeClass member bodies, independently checked at their entries.
// This retained filename is provisional grouping, not attested original TU ownership.
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"
#include "../combat/weapon_type_class.h"
#include <new.h>
#include <objidl.h>
#include "../_layout/ini_class.h"
#include "../platform/ccini_class_methods.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/type_list.h"



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

// FUNCTION: GAMEMD 0x711F00
int TechnoTypeClass::vf_33(HouseClass* house)
{
    if (house != 0) {
        const float typeCost = house->FUN_0050BDF0(this);
        const float houseCost = house->FUN_0050BEB0(this);
        return (int)(vf_43() * houseCost * typeCost);
    }
    return vf_43();
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

// Address-backed helper/global references used by the native asset path.
// Declaration: GAMEMD 0x7C9FF0 (LIBRARY; decl; reloc)
extern void __cdecl FUN_007C9FF0(char* out, const char* drive,
    const char* directory, const char* name, const char* extension);
// Declaration: GAMEMD 0x5B40B0 (decl; reloc)
extern SHPStruct* __fastcall FUN_005B40B0(const char* path, char flag);
// Declaration: GAMEMD 0x6263D0 (decl; reloc)
extern DynamicVectorClassLayout* __fastcall FUN_006263D0(char* paletteFile);
// Declaration: GAMEMD 0x7C8D20 (LIBRARY; decl; reloc)
extern int __cdecl FUN_007C8D20(const char* left, const char* right);
// GLOBAL: GAMEMD 0x00887180
extern CCINIClass DAT_00887180;
// GLOBAL: GAMEMD 0x0081834C
extern const char DAT_0081834C[];
// GLOBAL: GAMEMD 0x00889F64
extern const char DAT_00889F64[];
// STRING: GAMEMD 0x00843350
extern const char STR_CAMEO[]; // "Cameo"
// STRING: GAMEMD 0x00844530
extern const char STR_XXICON[]; // "XXICON"
// STRING: GAMEMD 0x00843344
extern const char STR_ALT_CAMEO[]; // "AltCameo"
// STRING: GAMEMD 0x00824254
extern const char STR_PALETTE[]; // "Palette"
// STRING: GAMEMD 0x008204FC
extern const char STR_DEFAULT_ICON[]; // "XXICON.SHP"

// FUNCTION: GAMEMD 0x7162F0
HRESULT __stdcall TechnoTypeClass::Load(IStream* stream)
{
    // The entry stream first dispatches Clear through each existing list's
    // slot +0x0C. It clears these 18 lists in native order before base Load.
    Dock.Clear();
    DebrisTypes.Clear();
    DebrisAnims.Clear();
    VoiceSelect.Clear();
    VoiceSelectEnslaved.Clear();
    VoiceSelectDeactivated.Clear();
    VoiceMove.Clear();
    VoiceAttack.Clear();
    VoiceSpecialAttack.Clear();
    VoiceDie.Clear();
    VoiceFeedback.Clear();
    MoveSound.Clear();
    DieSound.Clear();
    Explosion.Clear();
    DestroyAnim.Clear();
    Prerequisite.Clear();
    PrerequisiteOverride.Clear();
    DebrisMaximums.Clear();

    HRESULT result = ObjectTypeClass::Load(stream);
    if (result < 0) {
        return result;
    }

    // Native calls 0x6CF240 at 0x716435..0x7164F0 in this exact order,
    // before the first list constructor at 0x7164FB. The qualified call names
    // the known manager method while retaining the direct non-virtual target.
    DAT_00B0C110.SwizzleManagerClass::vf_4(&DeploysInto);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&UndeploysInto);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&PowersUnit);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NaturalParticleSystem);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&RefinerySmokeParticleSystem);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Spawns);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Enslaves);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&DeathWeapon);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AirstrikeTeamType);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&EliteAirstrikeTeamType);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&UnloadingClass);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&DeployingAnim);

#define LOAD_TYPED_LIST(field, ElementType) do { \
        new (&field) TypeList<ElementType>(); \
        int count; \
        ElementType item; \
        stream->Read(&count, 4, 0); \
        for (int i = 0; i < count; ++i) { \
            stream->Read(&item, 4, 0); \
            field.AddItem(item); \
        } \
    } while (0)

    // Each TypeList<T> placement construction reinstalls the RTTI-backed
    // specialization vtable and native empty-vector defaults. The list's
    // trailing unknown_18 dword is deliberately left untouched, as in retail.
    LOAD_TYPED_LIST(Dock, const BuildingTypeClass*);
    LOAD_TYPED_LIST(DebrisTypes, const VoxelAnimTypeClass*);
    LOAD_TYPED_LIST(DebrisAnims, const AnimTypeClass*);
    LOAD_TYPED_LIST(VoiceSelect, int);
    LOAD_TYPED_LIST(VoiceSelectEnslaved, int);
    LOAD_TYPED_LIST(VoiceSelectDeactivated, int);
    LOAD_TYPED_LIST(VoiceMove, int);
    LOAD_TYPED_LIST(VoiceAttack, int);
    LOAD_TYPED_LIST(VoiceSpecialAttack, int);
    LOAD_TYPED_LIST(VoiceDie, int);
    LOAD_TYPED_LIST(VoiceFeedback, int);
    LOAD_TYPED_LIST(MoveSound, int);
    LOAD_TYPED_LIST(DieSound, int);
    LOAD_TYPED_LIST(Explosion, const AnimTypeClass*);
    LOAD_TYPED_LIST(DestroyAnim, const AnimTypeClass*);
    LOAD_TYPED_LIST(DebrisMaximums, int);
    LOAD_TYPED_LIST(Prerequisite, int);
    LOAD_TYPED_LIST(PrerequisiteOverride, int);
    LOAD_TYPED_LIST(DamageParticleSystems, const ParticleSystemTypeClass*);
    LOAD_TYPED_LIST(DestroyParticleSystems, const ParticleSystemTypeClass*);
#undef LOAD_TYPED_LIST

    // Swizzle every pointer-list element after all list reads, then the
    // WeaponType pointer at offset zero in each of 18 WeaponStruct entries.
#define SWIZZLE_POINTER_LIST(field) do { \
        for (int i = 0; i < field.Count; ++i) { \
            DAT_00B0C110.SwizzleManagerClass::vf_4(&field.Items[i]); \
        } \
    } while (0)
    SWIZZLE_POINTER_LIST(Dock);
    SWIZZLE_POINTER_LIST(Explosion);
    SWIZZLE_POINTER_LIST(DestroyAnim);
    SWIZZLE_POINTER_LIST(DebrisTypes);
    SWIZZLE_POINTER_LIST(DebrisAnims);
    for (int weaponIndex = 0; weaponIndex < 18; ++weaponIndex) {
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Weapon[weaponIndex].WeaponType);
    }
    for (int eliteWeaponIndex = 0; eliteWeaponIndex < 18; ++eliteWeaponIndex) {
        DAT_00B0C110.SwizzleManagerClass::vf_4(&EliteWeapon[eliteWeaponIndex].WeaponType);
    }
    SWIZZLE_POINTER_LIST(DamageParticleSystems);
    SWIZZLE_POINTER_LIST(DestroyParticleSystems);
#undef SWIZZLE_POINTER_LIST

    // Native asset resolution sequence: inherited Image, Cameo with ID
    // fallback, AltCameo, then PaletteFile and Palette.
    char imagePath[0x100];
    char cameoPath[0x100];
    FUN_007C9FF0(imagePath, 0, 0, ImageFile, DAT_0081834C);
    Image = FUN_005B40B0(imagePath, 0);

    DAT_00887180.FUN_00528A10(ImageFile, STR_CAMEO, STR_XXICON,
                               cameoPath, sizeof(cameoPath));
    if (FUN_007C8D20(cameoPath, STR_XXICON) == 0) {
        DAT_00887180.FUN_00528A10(ID, STR_CAMEO, STR_XXICON,
                                   cameoPath, sizeof(cameoPath));
    }
    FUN_007C9FF0(imagePath, 0, 0, cameoPath, DAT_0081834C);
    Cameo = FUN_005B40B0(imagePath, 0);
    if (Cameo == 0) {
        Cameo = FUN_005B40B0(STR_DEFAULT_ICON, 0);
    }

    DAT_00887180.FUN_00528A10(ImageFile, STR_ALT_CAMEO, DAT_00889F64,
                               cameoPath, sizeof(cameoPath));
    FUN_007C9FF0(imagePath, 0, 0, cameoPath, DAT_0081834C);
    AltCameo = FUN_005B40B0(imagePath, 0);

    DAT_00887180.FUN_00528A10(ImageFile, STR_PALETTE, DAT_00889F64,
                               PaletteFile, 0x20);
    if (PaletteFile[0] != 0) {
        Palette = FUN_006263D0(PaletteFile);
    }
    return S_OK;
}

// FUNCTION: GAMEMD 0x7170A0
HRESULT __stdcall TechnoTypeClass::GetSizeMax(ULARGE_INTEGER* size)
{
    HRESULT result = ObjectTypeClass::GetSizeMax(size);
    if (result < 0) {
        return result;
    }

    size->LowPart = size->LowPart + 4 + VoiceSelect.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSelectEnslaved.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSelectDeactivated.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceMove.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceAttack.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceSpecialAttack.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceDie.Count * 4;
    size->LowPart = size->LowPart + 4 + VoiceFeedback.Count * 4;
    size->LowPart = size->LowPart + 4 + MoveSound.Count * 4;
    size->LowPart = size->LowPart + 4 + DieSound.Count * 4;
    size->LowPart = size->LowPart + 4 + Explosion.Count * 4;
    size->LowPart = size->LowPart + 4 + DestroyAnim.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisTypes.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisAnims.Count * 4;
    size->LowPart = size->LowPart + 4 + Dock.Count * 4;
    size->LowPart = size->LowPart + 4 + DebrisMaximums.Count * 4;
    size->LowPart = size->LowPart + 4 + DamageParticleSystems.Count * 4;
    size->LowPart = size->LowPart + 4 + DestroyParticleSystems.Count * 4;
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
