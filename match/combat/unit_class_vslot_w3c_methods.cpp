// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More UnitClass virtual overrides read off retail gamemd.exe v1.001 (vtable 0x7F5C70).
//   Functions are in ascending retail address order.
//   Address index: 0x740EF0 vf_147, 0x744100 vf_136, 0x73B0B0 vf_65, 0x744720 vf_56.

#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/tag_class.h"
#include "../core/frame_counter.h"
#include "../core/randomizer.h"

// The unit's slave manager, as far as the two calls the mission delay makes.
struct UnitSlaveManagerView
{
    // FUNCTION: GAMEMD 0x6B1020 (decl; reloc) -- whether the manager should wake now.
    bool FUN_006B1020();
    // FUNCTION: GAMEMD 0x6B0CC0 (decl; reloc) -- wakes the manager.
    void FUN_006B0CC0();
};

// GLOBAL: GAMEMD 0x8871E0 -- the rules.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// The mission control record, as far as the mission rate in minutes.
struct MissionControlClass
{
    char unknown_00[0x10];
    double Rate;   // +0x10
};
GG_STATIC_ASSERT(offsetof(MissionControlClass, Rate) == 0x10);

// GLOBAL: GAMEMD 0xB1CFB8 -- the cell passed with tag events when there is none.
extern CellStruct DAT_00B1CFB8;

// FUNCTION: GAMEMD 0x740EF0
// Drops out of harvesting: asks the radio contact to stand down or goes idle, then waits the
// mission rate.
int UnitClass::vf_147()
{
    void* contact = vf_330(reinterpret_cast<DynamicVectorClassLayout*>((char*)DAT_008871E0 + 0x850), 0, 0);
    IsHarvesting = false;
    if (contact == 0) {
        if (vf_330(reinterpret_cast<DynamicVectorClassLayout*>((char*)DAT_008871E0 + 0x850), 0, 1)) {
            EnterIdleMode(false, true);
        }
    } else if (vf_158(2, static_cast<RadioClass*>(contact)) == 1) {
        vf_122(7, false);
        return 1;
    }
    return (int)(FUN_005B3A00()->Rate * 900.0);
}

// FUNCTION: GAMEMD 0x744100
// A unit with a slave manager that is due to wake it waits the mission rate plus a little
// random time; otherwise the foot delay applies.
int UnitClass::vf_136()
{
    if (SlaveManager && DAT_008871E0->unknown_1790 + CurrentMissionStartTime < CurrentFrame) {
        if (static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B1020()) {
            static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B0CC0();
            int delay = (int)(FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    return FootClass::vf_136();
}

// FUNCTION: GAMEMD 0x744720
// Fires the attached tag's events (6: a source was given; then 0x30 and 0x1d) unless a
// hijacker is aboard and the tag is to be replaced; then the techno handling.
void UnitClass::vf_56(void* source)
{
    if (AttachedTag && (HijackerInfantryType == -1 || !AttachedTag->ShouldReplace())) {
        if (source) {
            AttachedTag->FUN_006E53A0(7, this, DAT_00B1CFB8, false, 0);
        }
        if (AttachedTag) {
            AttachedTag->FUN_006E53A0(0x30, this, DAT_00B1CFB8, false, 0);
        }
        if (AttachedTag) {
            AttachedTag->FUN_006E53A0(0x1d, this, DAT_00B1CFB8, false, 0);
        }
    }
    TechnoClass::vf_56(source);
}

// FUNCTION: GAMEMD 0x73B0B0
// Refuses while the tethered contact (a building doing its unload or deploy changes) is busy;
// otherwise the object handling, without the third argument.
bool UnitClass::vf_65(RectangleStruct* rect, bool force, int a3)
{
    if (IsTether) {
        TechnoClass* contact = FUN_0065AD40(0);
        if (contact->vf_11() == 6 && (contact->vf_97() == 0x10 || contact->QueuedMission == 0x10)) {
            if (contact->UnloadTimer.FUN_004A5110() || contact->UnloadTimer.FUN_004A5130() ||
                contact->UnloadTimer.FUN_004A51B0() || contact->UnloadTimer.FUN_004A51D0()) {
                return false;
            }
        }
    }
    return ObjectClass::vf_65(rect, force, 0);
}
