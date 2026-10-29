// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x458750; the same sequence is inlined in the
//   BuildingClass update body (building_class_update.cpp).

#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../core/rules_class.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// FUNCTION: GAMEMD 0x458750
//
// Restart the cash-production timer from the type's delay, then, unless the
// owner is a passive multiplayer house and provided the building is active,
// credit (positive amount) or debit (negative amount) the owner.
void BuildingClass::FUN_00458750()
{
    CashProductionTimer = CDTimerClass(Type->ProduceCashDelay);

    if (!((HouseTypeClass*)Owner->Type)->MultiplayPassive && vf_212()) {
        if (Type->ProduceCashAmount > 0)
            Owner->GiveMoney(Type->ProduceCashAmount);
        else
            Owner->FUN_004F9790(-Type->ProduceCashAmount);
    }
}

// FUNCTION: GAMEMD 0x452670
//
// Whether the upgrade type may be attached to this building for the house:
// the house must own the building and the upgrade must name this building's
// type. A slot of -1 is accepted while the building is below its type's upgrade
// cap; otherwise (and for slots 1 to 3) the building must carry no upgrade yet.
bool BuildingClass::FUN_00452670(BuildingTypeClass* upgrade, HouseClass* house)
{
    if (house == Owner && _stricmp(upgrade->PowersUpBuilding, Type->ID) == 0) {
        int level = upgrade->PowersUpToLevel;
        if (level != -1) {
            if (level <= 0 || level > 3) {
                return false;
            }
        } else if (UpgradeLevel < Type->Upgrades) {
            return true;
        }
        if (!UpgradeLevel) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4504F0
//
// Record the prism stage, its target and the type's firing delay, drop animation
// slot 3, then start slot 0xA (damaged name once health is at the yellow threshold).
void BuildingClass::FUN_004504F0(int stage, const CoordStruct* target)
{
    DelayBeforeFiring = Type->DelayedFireDelay;
    PrismStage = stage;
    PrismTargetCoords = *target;

    DestroyNthAnim(3);

    int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    const char* animName;
    if (damaged) {
        animName = Type->BuildingAnim[0xA].Damaged;
    } else {
        animName = Type->BuildingAnim[0xA].Anim;
    }
    if (animName && *animName) {
        PlayAnim(animName, 0xA, damaged, false, 0);
    }
}

// The overpowerer list at +0x66C holds TechnoClass pointers.
static inline TechnoClass*& OverpowererAt(DynamicVectorClassLayout& list, int index)
{
    return ((TechnoClass**)list.Items)[index];
}

// FUNCTION: GAMEMD 0x450590
//
// Drop every overpowering unit whose target is no longer this building, then
// recompute IsOverpowered: three or more overpowerers always count; one or two
// count only on a fully powered house whose building has power.
void BuildingClass::FUN_00450590()
{
    for (int i = Overpowerers.Count - 1; i >= 0; i--) {
        if (OverpowererAt(Overpowerers, i)->Target != this) {
            if (i < Overpowerers.Count) {
                Overpowerers.Count--;
                for (int j = i; j < Overpowerers.Count; j++) {
                    OverpowererAt(Overpowerers, j) = OverpowererAt(Overpowerers, j + 1);
                }
            }
        }
    }

    int count = Overpowerers.Count;
    if (count < 3) {
        if (Owner->GetPowerPercentage() == DAT_007E1718 && HasPower && count >= 1) {
            IsOverpowered = true;
        } else {
            IsOverpowered = false;
        }
    } else {
        IsOverpowered = true;
    }
}

// FUNCTION: GAMEMD 0x454730
//
// Drop animation slot 0x13, then restart each slot whose record is flagged in
// the type, choosing the damaged name once health is at the yellow threshold.
void BuildingClass::FUN_00454730()
{
    DestroyNthAnim(0x13);

    for (int slot = 0; slot < 0x15; slot++) {
        if (Type->BuildingAnim[slot].PoweredSpecial) {
            int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
            const char* animName;
            if (damaged) {
                animName = Type->BuildingAnim[slot].Damaged;
            } else {
                animName = Type->BuildingAnim[slot].Anim;
            }
            if (animName && *animName) {
                PlayAnim(animName, slot, damaged, false, 0);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x454930
//
// Start animation slot 0x13 (damaged name once health is at the yellow
// threshold), then drop every slot whose record is flagged in the type.
void BuildingClass::FUN_00454930()
{
    int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    const char* animName;
    if (damaged) {
        animName = Type->BuildingAnim[0x13].Damaged;
    } else {
        animName = Type->BuildingAnim[0x13].Anim;
    }
    if (animName && *animName) {
        PlayAnim(animName, 0x13, damaged, false, 0);
    }

    for (int slot = 0; slot < 0x15; slot++) {
        if (Type->BuildingAnim[slot].PoweredSpecial) {
            DestroyNthAnim(slot);
        }
    }
}
