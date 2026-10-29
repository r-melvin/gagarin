// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob1
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   InfantryClass virtual slots matched against retail gamemd.exe v1.001 (round 23); disassembled
//   from each entry point. Same original translation unit as Infantry.cpp (0x517840-0x52348F).
//
// Address index: 0x51F330, 0x523250, 0x521B60, 0x522100, 0x522550

#include "../movement/loco_com.h"
#include "../_layout/infantry_class.h"
#include "../_layout/techno_class.h"
#include "../core/mission_class_methods.h"
#include "../core/randomizer.h"

// GLOBAL: GAMEMD 0xA8B230
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0x7E9AC0 -- CLSID of JumpjetLocomotionClass.
extern const CLSID DAT_007E9AC0;

// GLOBAL: GAMEMD 0x7EAF7C -- per-sequence table, 4 bytes an entry; the first byte is the one read.
extern const unsigned char DAT_007EAF7C[][4];

// FUNCTION: GAMEMD 0x51F330
// Slot 266: re-pick a target for this infantry. Keep the current target if it is still valid for
// the chosen weapon, else scan for a new one, and finally fall back to idle mode.
void InfantryClass::vf_266()
{
    int weapon = vf_185(0);
    if (Target && vf_234(Target, weapon))
        return;
    CoordStruct where = Location;
    AbstractClass* found = vf_241(1, &where, false);
    if ((Target || found) && (vf_242(found), found))
        return;
    if (CurrentMission != 5 && !vf_33()->bools_D94[0])
        EnterIdleMode(false, true);
}

// FUNCTION: GAMEMD 0x521B60
// Slot 128: true when the infantry is idle enough to be ordered about. Not while in mission 6 or
// 0x15, firing or falling; while moving, only in certain states; finally gated by its sequence's flag.
bool InfantryClass::vf_128()
{
    if (CurrentMission != 6 && CurrentMission != 0x15 && !IsFiring && !IsFallingDown) {
        if ((*(ILocomotionPtr*)&Locomotor)->IsMovingNow()
            && vf_97() != 5 && vf_97() != 0xF && (vf_97() != 1 || Target))
            return false;
        if (SequenceAnim == -1 || DAT_007EAF7C[SequenceAnim][0])
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x522100
// True when the type is a jumpjet type and its locomotor reports the jumpjet locomotor's class ID.
bool InfantryClass::FUN_00522100()
{
    if (!Type->bools_D94[0])
        return false;
    IPersistPtr persist(*(ILocomotionPtr*)&Locomotor);
    CLSID id;
    persist->GetClassID(&id);
    return IsEqualCLSID(id, DAT_007E9AC0);
}

// FUNCTION: GAMEMD 0x523250
// Slot 44: while riding in an open-topped transport, take the transporter's coordinate offset by this
// passenger's (negated) position in its cargo list; otherwise use the base TechnoClass answer.
CoordStruct InfantryClass::vf_44(int a1, CoordStruct a2)
{
    if (InOpenToppedTransport && Transporter) {
        int index = ((TechnoClass*)Transporter)->Passengers.IndexOf((FootClass*)this);
        if (index) {
            CoordStruct zero = { 0, 0, 0 };
            return ((TechnoClass*)Transporter)->vf_44(-index, zero);
        }
    }
    CoordStruct zero = { 0, 0, 0 };
    return TechnoClass::vf_44(a1, zero);
}

// FUNCTION: GAMEMD 0x522550
// Start deploying: a stationary infantry plays the deploy sequence and reports that sequence's second
// field; a moving one stops, flags itself to deploy and returns a delay from its mission rate plus a
// random 0-2.
int InfantryClass::FUN_00522550()
{
    if (!(*(ILocomotionPtr*)&Locomotor)->IsMoving()) {
        vf_342(0x1B, 0, 0);
        return Type->Sequence[0x1B].unknown_04;
    }
    (*(ILocomotionPtr*)&Locomotor)->StopMoving();
    ShouldDeploy = true;
    MissionControlClass* control = FUN_005B3A00();
    int delay = (int)(control->Rate * 900.0);
    return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}
