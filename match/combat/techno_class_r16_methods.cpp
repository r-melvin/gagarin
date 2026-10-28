// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TechnoClass members read off retail gamemd.exe v1.001 (Techno.CPP, code range
//   0x6f28a0-0x7108df), round 16. The overrides that the canonical TechnoClass already declares
//   are defined on it; the rest sit on TechnoView_r16, a plain derived view, so no shared header
//   changes. Functions are in ascending retail address order.
//   Address index: 0x707DD0, 0x70DC70.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"

// One row of the per-difficulty table in the rules, as far as the first flag byte.
struct TechnoRulesDifficulty_r16
{
    char Flag;   // +0x00
    char unknown_01[0x4F];
};
// The rules object, as far as the two members the cost weight reads.
struct TechnoRulesView_r16
{
    char unknown_0000[0x1450];
    int unknown_1450;   // +0x1450
    char unknown_1454[0x1582 - 0x1454];
    TechnoRulesDifficulty_r16 Difficulty[3];   // +0x1582, stride 0x50
};
GG_STATIC_ASSERT(offsetof(TechnoRulesView_r16, unknown_1450) == 0x1450);
GG_STATIC_ASSERT(offsetof(TechnoRulesView_r16, Difficulty) == 0x1582);
// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern TechnoRulesView_r16* DAT_008871E0_r16;

// A plain derived view of TechnoClass for the overrides the canonical class does not declare.
class TechnoView_r16 : public TechnoClass
{
public:
    virtual int vf_96();
};

// FUNCTION: GAMEMD 0x707DD0
// The weight of this object: its type's points, its own extra, and its passengers' when the
// house's difficulty or intelligence level counts them.
int TechnoView_r16::vf_96()
{
    int total = 0;
    if ((DAT_008871E0_r16->Difficulty[Owner->AIDifficulty].Flag != 0 ||
         Owner->IQLevel2 >= DAT_008871E0_r16->unknown_1450) &&
        Passengers.FirstPassenger != 0) {
        for (ObjectClass* passenger = reinterpret_cast<ObjectClass*>(Passengers.GetFirstPassenger());
             passenger != 0; passenger = reinterpret_cast<ObjectClass*>(passenger->NextObject)) {
            total += passenger->vf_96();
        }
    }
    return vf_33()->Points + vf_176() + total;
}

// FUNCTION: GAMEMD 0x70DC70
// Pick the turret for a weapon number (0 when it is out of range); chargers keep theirs.
void TechnoClass::FUN_0070DC70(int mode)
{
    if (!vf_33()->IsChargeTurret) {
        if (mode >= 0 && mode < 18) {
            CurrentTurretNumber = vf_33()->FUN_007178B0(mode);
            CurrentWeaponNumber = mode;
        } else {
            CurrentTurretNumber = vf_33()->FUN_007178B0(0);
            CurrentWeaponNumber = 0;
        }
    }
}
