// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm of each
//   address below). Lies inside the Techno.CPP code range 0x6F28A0-0x7108DF.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6F78D0   TechnoClass::vf_237
//   FUNCTION: GAMEMD 0x6FCD40   TechnoClass::vf_232
//   FUNCTION: GAMEMD 0x700D10   TechnoClass::vf_196
//   FUNCTION: GAMEMD 0x701140   TechnoClass::vf_37
//   FUNCTION: GAMEMD 0x701410   TechnoClass::vf_259
//   FUNCTION: GAMEMD 0x7036C0   TechnoClass::vf_279
//   FUNCTION: GAMEMD 0x708B40   TechnoClass::vf_176
//   FUNCTION: GAMEMD 0x708BC0   TechnoClass::vf_173
//   FUNCTION: GAMEMD 0x708C10   TechnoClass::vf_193
//   FUNCTION: GAMEMD 0x708FC0   TechnoClass::vf_218
//   FUNCTION: GAMEMD 0x70ADA0   TechnoClass::vf_175
//   FUNCTION: GAMEMD 0x70C620   TechnoClass::vf_172
//   FUNCTION: GAMEMD 0x710670   TechnoClass::vf_229

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/foot_class.h"
#include "randomizer.h"
#include "../_layout/rules_class.h"
#include "../_layout/tactical.h"
#include "../_layout/building_class.h"

// FUNCTION: GAMEMD 0x750E20 (decl; reloc) -- play a positional sound; RET 4.
void __fastcall FUN_00750E20(int sound, CoordStruct* where, int unused);

// FUNCTION: GAMEMD 0x6B7100 / 0x6B7BB0 (decl; reloc) -- SpawnManager teardown steps.
class SpawnManagerClass {
public:
    void FUN_006B7100();
    void FUN_006B7BB0();
};

// Rules fields read here that the shared RulesClass layout has not named yet.
struct RulesView_DF4 {
    char unknown_000[0x1C4];
    int  unknown_1C4;
    char unknown_1C8[0x628 - 0x1C8];
    int  unknown_628;
    char unknown_62C[0x6A0 - 0x62C];
    int  unknown_6A0;
    char unknown_6A4[0xDF4 - 0x6A4];
    int  unknown_DF4;
};
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_628) == 0x628);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_6A0) == 0x6A0);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_1C4) == 0x1C4);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_DF4) == 0xDF4);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- play a sound at a coordinate; index in ECX,
// coordinate in EDX, RET 4.
void __fastcall FUN_007509E0(int index, const CoordStruct& where, int controller);

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// GLOBAL: GAMEMD 0xB0EA50
extern int DAT_00B0EA50;

// GLOBAL: GAMEMD 0x886B88
extern Randomizer DAT_00886B88;

// GLOBAL: GAMEMD 0x7E2800
extern const double DAT_007E2800;

// FUNCTION: GAMEMD 0x6F78D0
// Attack the target using whichever weapon is current: slot 234 (in range of
// that weapon) when the weapon type has the byte flag at +0x136, else slot 235.
bool TechnoClass::vf_237(AbstractClass* target)
{
    int weapon = vf_250();
    WeaponStruct* ws = vf_254(weapon);
    if (ws && ws->WeaponType && *((char*)ws->WeaponType + 0x136)) {
        return vf_234(target, weapon);
    }
    return IsCloseEnoughToAttack(target);
}

// FUNCTION: GAMEMD 0x700D10
// False when this is an RTTI-1 object that either has a tube index with slot
// 313 true, or is under EMP; true otherwise.
bool TechnoClass::vf_196()
{
    if (this && vf_11() == 1) {
        FootClass* foot = (FootClass*)this;
        if ((foot->TubeIndex >= 0 && foot->vf_313()) || IsUnderEMP()) {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x701140
// For an RTTI-6 object whose type is Repairable: true when Health differs from
// the type's Strength.
bool TechnoClass::vf_37()
{
    if (vf_11() != 6) {
        return false;
    }
    return vf_33()->Repairable && Health != vf_34()->Strength;
}

// FUNCTION: GAMEMD 0x708C10
// Store the global at 0xB0EA50 through the second argument and return 0.
int TechnoClass::vf_193(int a1, int* out)
{
    *out = DAT_00B0EA50;
    return 0;
}

// FUNCTION: GAMEMD 0x70ADA0
// Forward the owner house to the type's slot 46 with a zero second argument.
void TechnoClass::vf_175()
{
    vf_33()->vf_46((int)Owner, 0);
}

// FUNCTION: GAMEMD 0x708BC0
// Fraction of the type's storage capacity currently held (0.0 when the type
// has no storage).
double TechnoClass::vf_173()
{
    if (vf_33()->Storage) {
        double held = Tiberium.GetTotalAmount();
        return held / vf_33()->Storage;
    }
    return DAT_007E2800;
}

// FUNCTION: GAMEMD 0x708FC0
// Play a randomly chosen entry of the type's VoiceMove list through slot 213;
// does nothing when the list is empty.
void TechnoClass::vf_218()
{
    TypeList<int>* voices = &vf_33()->VoiceMove;
    if (voices->Count) {
        unsigned int r = DAT_00886B88.Random();
        TypeList<int>& list = vf_33()->VoiceMove;
        vf_213(list.Items[r % list.Count]);
    }
}

// FUNCTION: GAMEMD 0x710670
// Add the object to the passenger list and, if one was given and the type has
// an enter-transport sound, play it at this object's location.
void TechnoClass::vf_229(FootClass* passenger)
{
    Passengers.AddPassenger(passenger);
    if (passenger && vf_33()->EnterTransportSound != -1) {
        CoordStruct where = Location;
        FUN_00750E20(vf_33()->EnterTransportSound, &where, 0);
    }
}

// FUNCTION: GAMEMD 0x6FCD40
// Stand down: clear the target, clear the destination, set slot 160 to 3.
// Then, unless this is a foot object that is being carried by a locomotor,
// tear down the spawn manager (if any) and run slot 55 with true. Finish with
// slot 84.
void TechnoClass::vf_232()
{
    vf_242(0);
    SetDestination(0, true);
    vf_160(3);
    if (!(this && Flags.IsFoot && ((FootClass*)this)->IsAttackedByLocomotor)) {
        if (SpawnManager) {
            ((SpawnManagerClass*)SpawnManager)->FUN_006B7100();
            ((SpawnManagerClass*)SpawnManager)->FUN_006B7BB0();
        }
        vf_55(true);
    }
    vf_84();
}

// FUNCTION: GAMEMD 0x708B40
// The threat value of this object: for an RTTI-6 object with a positive slot
// 258 value, that value times the rules multiplier at +0xDF4; otherwise the
// type's ThreatPosed (the bunker-linked partner's when there is one). Zero when
// there is no type.
int TechnoClass::vf_176()
{
    TechnoTypeClass* type = vf_33();
    if (type) {
        if (vf_11() == 6) {
            if (vf_258() > 0) {
                int multiplier = ((RulesView_DF4*)RulesInstance)->unknown_DF4;
                return vf_258() * multiplier;
            }
            if (BunkerLinkedItem) {
                return BunkerLinkedItem->vf_33()->ThreatPosed;
            }
        }
        return type->ThreatPosed;
    }
    return 0;
}

static inline bool CellsDiffer(const CellStruct& a, const CellStruct& b)
{
    return a.X != b.X || a.Y != b.Y;
}

// FUNCTION: GAMEMD 0x70C620
// True when the cell under this object's location is not the cell that
// slot 110 reports.
bool TechnoClass::vf_172()
{
    CoordStruct where = Location;
    CellStruct here = DAT_00887324->FUN_006D6410(&where);
    return CellsDiffer(here, vf_110());
}

// FUNCTION: GAMEMD 0x701410
// Restore to full strength: run slot 73 with 2, set Health and EstimatedHealth
// to the type's Strength and, for an RTTI-6 (building) object, refresh its
// damaged-state animations and play the rules sound at its coordinate.
void TechnoClass::vf_259()
{
    vf_73(2);
    int strength = vf_33()->Strength;
    Health = strength;
    EstimatedHealth = strength;
    if (vf_11() == 6) {
        vf_103(0);
        ((BuildingClass*)this)->ToggleDamagedAnims(
            GetHealthPercentage() <= RulesInstance->ConditionYellow);
        FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_1C4, vf_18(), 0);
    }
}

// FUNCTION: GAMEMD 0x7036C0
// Begin decloaking from the cloaked or cloaking states: enter state 3, restart
// the cloak progress stage from the rules' step count at the type's cloaking
// speed, and (unless silent) play the rules sound at this location.
void TechnoClass::vf_279(bool silent)
{
    if (CloakState == 2 || CloakState == 1) {
        CloakState = 3;
        CloakProgress.Value = ((RulesView_DF4*)RulesInstance)->unknown_628 - 1;
        CloakProgress.SetRate(vf_33()->CloakingSpeed);
        CloakProgress.Step = -1;
        if (!silent) {
            CoordStruct where = Location;
            FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_6A0, where, 0);
        }
    }
}
