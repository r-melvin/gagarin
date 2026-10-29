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
//   FUNCTION: GAMEMD 0x703770   TechnoClass::vf_280
//   FUNCTION: GAMEMD 0x70BE80   TechnoClass::vf_165
//   FUNCTION: GAMEMD 0x70EE30   TechnoClass::vf_272
//   FUNCTION: GAMEMD 0x70EF00   TechnoClass::vf_230
//   FUNCTION: GAMEMD 0x708EB0   TechnoClass::vf_216
//   FUNCTION: GAMEMD 0x708B40   TechnoClass::vf_176
//   FUNCTION: GAMEMD 0x708BC0   TechnoClass::vf_173
//   FUNCTION: GAMEMD 0x708C10   TechnoClass::vf_193
//   FUNCTION: GAMEMD 0x708FC0   TechnoClass::vf_218
//   FUNCTION: GAMEMD 0x707E60   TechnoClass::vf_199
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
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "frame_counter.h"

// Null-tolerant "as FootClass" casts, as retail inlined them into callers that
// pass `this` (the null test is in the retail bytes at 0x6FCD67 / 0x700D13).
static inline bool IsFootObject(TechnoClass* object)
{
    return object && object->Flags.IsFoot;
}

static inline FootClass* AsFootByRtti(TechnoClass* object)
{
    if (object && object->vf_11() == 1) {
        return (FootClass*)object;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x750E20 (decl; reloc) -- play a positional sound; RET 4.
void __fastcall FUN_00750E20(int sound, CoordStruct* where, int unused);

// FUNCTION: GAMEMD 0x6B7100 / 0x6B7BB0 (decl; reloc) -- SpawnManager teardown steps.
#include "../_layout/spawn_manager_class.h"

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
    char unknown_DF8[0x16E0 - 0xDF8];
    double unknown_16E0;
    char unknown_16E8[0x17E9 - 0x16E8];
    unsigned char unknown_17E9;
};
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_16E0) == 0x16E0);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_17E9) == 0x17E9);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_628) == 0x628);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_6A0) == 0x6A0);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_1C4) == 0x1C4);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_DF4) == 0xDF4);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- play a sound at a coordinate; index in ECX,
// coordinate in EDX, RET 4.
void __fastcall FUN_007509E0(int index, const CoordStruct& where, int controller);

// GLOBAL: GAMEMD 0xA83D84 -- table of type records indexed by a cell's overlay type.
struct OverlayRecord_00A83D84 {
    char unknown_000[0x2B5];
    unsigned char unknown_2B5;
};
extern OverlayRecord_00A83D84** DAT_00A83D84;

// FUNCTION: GAMEMD 0x4870F0 (decl; reloc) -- cell test taking an object's +0x30 link.
class CellView_004870F0 {
public:
    bool FUN_004870F0(void* link);
};

// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* DAT_00A83D4C;

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// GLOBAL: GAMEMD 0xB0EA50
extern int DAT_00B0EA50;

// GLOBAL: GAMEMD 0x886B88
extern Randomizer DAT_00886B88;

// GLOBAL: GAMEMD 0x7E27F8
extern double DAT_007E27F8;

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
    FootClass* foot = AsFootByRtti(this);
    if (foot) {
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
    vf_33()->vf_46(Owner, 0);
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
    if (!(IsFootObject(this) && ((FootClass*)this)->IsAttackedByLocomotor)) {
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

// FUNCTION: GAMEMD 0x70EF00
// Whether the weapon chosen against the target may be used on it. Needs a
// weapon type; the byte flag at +0x138 on that type gates every case except the
// RTTI-0x24 target, where the rules flag at +0x17E9 can stand in for it. A cell
// target also qualifies through its overlay record's byte at +0x2B5; an object
// target qualifies when slot 49 is true and slot 52(true) is null.
bool TechnoClass::vf_230(AbstractClass* target)
{
    WeaponStruct* ws = vf_254(vf_185(target));
    char* weaponType = (char*)ws->WeaponType;
    if (weaponType) {
        if (target->vf_11() == 0x24) {
            if (((RulesView_DF4*)RulesInstance)->unknown_17E9 || weaponType[0x138]) {
                return true;
            }
            return false;
        }
        if (weaponType[0x138]) {
            if (target->vf_11() == 0xB) {
                int overlay = ((CellClass*)target)->OverlayTypeIndex;
                if (overlay != -1 && DAT_00A83D84[overlay]->unknown_2B5) {
                    return true;
                }
            }
            if (target && target->Flags.unknown_14_1) {
                ObjectClass* object = (ObjectClass*)target;
                if (object->vf_49() && !object->vf_52(true)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x70EE30
// False when the frame falls in the 0x48..0x77 window of the 256-frame cycle
// started at DisguiseCreationFrame, or when the cell under this object refuses
// the other object's +0x30 link. True otherwise, and always true while the blink
// timer is running and the owner is not the current player.
bool TechnoClass::vf_272(ObjectClass* a1)
{
    if (DisguiseBlinkTimer.GetTimeLeft() == 0 || Owner->IsControlledByCurrentPlayer()) {
        if (Owner->IsControlledByCurrentPlayer() && vf_49()) {
            int phase = (CurrentFrame - (int)DisguiseCreationFrame + 0x40) % 256;
            if (phase >= 0x48 && phase <= 0x77) {
                return false;
            }
        } else {
            CellView_004870F0* cell = (CellView_004870F0*)vf_111();
            if (vf_49() && cell && !cell->FUN_004870F0(a1->NextObject)) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x70BE80
// Periodic self-heal gate: true on the frames that divide evenly by the rules'
// heal interval when the object is damaged (alive and below full strength),
// provided its type self-heals or its veteran/elite rank grants it.
bool TechnoClass::vf_165()
{
    if (!vf_33()->SelfHealing) {
        bool allowed = false;
        if (Veterancy.FUN_0074FF90() || Veterancy.FUN_00750010()) {
            TechnoTypeClass* type = vf_33();
            if (Veterancy.FUN_0074FF90() && type->VeteranAbilities._raw[9]) {
                allowed = true;
            } else if (Veterancy.FUN_00750010() &&
                       (type->VeteranAbilities._raw[9] || type->EliteAbilities._raw[9])) {
                allowed = true;
            }
        }
        if (!allowed) {
            return false;
        }
    }
    double base = ((RulesView_DF4*)RulesInstance)->unknown_16E0;
    int interval = (int)(base * DAT_007E27F8);
    if (CurrentFrame % interval != 0) {
        return false;
    }
    int health = Health;
    if (health == vf_33()->Strength) {
        return false;
    }
    bool damaged = health != 0;
    return damaged;
}

// FUNCTION: GAMEMD 0x703770
// Begin cloaking from the uncloaked or fully-decloaking states: run slot 55 with
// false, enter state 1, restart the cloak progress stage from zero at the
// type's cloaking speed counting up, and (unless silent) play the rules sound
// at this location. Then, if this object is selected and not the local
// player's, run slot 84.
void TechnoClass::vf_280(bool silent)
{
    if (CloakState == 0 || CloakState == 3) {
        vf_55(false);
        CloakState = 1;
        CloakProgress.Value = 0;
        CloakProgress.SetRate(vf_33()->CloakingSpeed);
        CloakProgress.Step = 1;
        if (!silent) {
            CoordStruct where = Location;
            FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_6A0, where, 0);
        }
        if (Owner != DAT_00A83D4C && IsSelected) {
            vf_84();
        }
    }
}

// FUNCTION: GAMEMD 0x708EB0
// Play a randomly chosen select voice through slot 213: from the type's
// enslaved list when this has a slave owner, else its deactivated list when
// deactivated, else its normal select list. Does nothing for an empty list.
void TechnoClass::vf_216()
{
    if (SlaveOwner) {
        TypeList<int>* voices = &vf_33()->VoiceSelectEnslaved;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelectEnslaved;
            vf_213(list.Items[r % list.Count]);
        }
    } else if (Deactivated) {
        TypeList<int>* voices = &vf_33()->VoiceSelectDeactivated;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelectDeactivated;
            vf_213(list.Items[r % list.Count]);
        }
    } else {
        TypeList<int>* voices = &vf_33()->VoiceSelect;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelect;
            vf_213(list.Items[r % list.Count]);
        }
    }
}

// FUNCTION: GAMEMD 0x707E60
// Range for a guard/scan mode: -1 stays -1; mode 0 is the type's GuardRange
// unless slot 204 is true; other modes use twice the type's GuardRange (or, if
// that is zero, twice the larger of slot 90 for modes 0 and 1), clamped to
// 0x1000 (and to at least 0x700 for mode 2, at least 0 otherwise).
int TechnoClass::vf_199(int mode)
{
    if (mode == -1) {
        return -1;
    }
    if (mode == 0) {
        bool blocked = vf_204();
        if (vf_33()->GuardRange && !blocked) {
            return vf_33()->GuardRange;
        }
        return 0;
    }
    int range = vf_33()->GuardRange;
    if (!range) {
        range = vf_90(0) > vf_90(1) ? vf_90(0) : vf_90(1);
    }
    range += range;
    if (mode == 2) {
        if (range < 0x700) {
            return 0x700;
        }
        if (range > 0x1000) {
            return 0x1000;
        }
    } else {
        if (range < 0) {
            return 0;
        }
        if (range > 0x1000) {
            range = 0x1000;
        }
    }
    return range;
}
