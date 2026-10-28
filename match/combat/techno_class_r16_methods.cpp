// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TechnoClass members read off retail gamemd.exe v1.001 (Techno.CPP, code range
//   0x6f28a0-0x7108df), round 16. The overrides that the canonical TechnoClass already declares
//   are defined on it; the rest sit on TechnoView_r16, a plain derived view, so no shared header
//   changes. Functions are in ascending retail address order.
//   Address index: 0x707DD0, 0x708E00, 0x70B1D0.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"

// An infantry-like object, as far as the one test the voice choice makes.
struct TechnoInfantryView_r16
{
    // FUNCTION: GAMEMD 0x522510 (decl; reloc)
    bool FUN_00522510();
};

// The map object, as far as the reveal call.
struct TechnoMapView_r16
{
    // FUNCTION: GAMEMD 0x5678E0 (decl; reloc) -- reveal the area around a coordinate for a house.
    void FUN_005678E0(CoordStruct* where, int range, HouseClass* house, int a4, int a5, int a6,
                      int a7, int a8);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern TechnoMapView_r16 DAT_0087F7E8_r16;

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

// FUNCTION: GAMEMD 0x708E00
// Speak the deploy or undeploy voice of the type, if it has one, then clear the pending flag.
void TechnoClass::vf_219()
{
    if (unknown_bool_4F8 == 0) {
        if (this != 0 && vf_11() == 15) {
            TechnoInfantryView_r16* infantry =
                vf_11() == 15 ? reinterpret_cast<TechnoInfantryView_r16*>(this) : 0;
            if (infantry->FUN_00522510()) {
                if (vf_33()->VoiceUndeploy != -1) {
                    vf_213(vf_33()->VoiceUndeploy);
                    unknown_bool_4F8 = false;
                    return;
                }
                unknown_bool_4F8 = false;
                return;
            }
        }
        if (vf_33()->VoiceDeploy != -1) {
            vf_213(vf_33()->VoiceDeploy);
        }
    }
    unknown_bool_4F8 = false;
}

// FUNCTION: GAMEMD 0x70B1D0
// Reveal the area last seen by this object, for the given house or its owner.
void TechnoClass::vf_291(int a1, int a2, bool a3, HouseClass* a4)
{
    if (IsInPlayfield) {
        HouseClass* owner = Owner;
        if (!owner->Type->MultiplayPassive) {
            if (unknown_bool_250) {
                int range = LastSightRange;
                unknown_bool_250 = false;
                if (range) {
                    if (a3 && a4) {
                        DAT_0087F7E8_r16.FUN_005678E0(&LastSightCoords, range, a4, a1, a2, 0, 1, 1);
                    } else if (range) {
                        DAT_0087F7E8_r16.FUN_005678E0(&LastSightCoords, range, owner, a1, a2, 0, 1, 1);
                    }
                }
            } else if (a3) {
                int range = LastSightRange;
                if (range && a4) {
                    DAT_0087F7E8_r16.FUN_005678E0(&LastSightCoords, range, a4, a1, a2, 0, 1, 1);
                }
            }
        }
    }
}
