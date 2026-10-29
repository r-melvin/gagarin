// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off retail gamemd.exe v1.001 at 0x50E010 / 0x50E280: the powered-centre
//   count at house +0x2D8, the control bytes at +0x1EC/+0x1ED, the techno array at 0xA8EC78,
//   techno Owner +0x21C / InLimbo +0x81 / type slot 33, Reactivate 0x70FBE0, and the EVA line
//   at 0x824FE4. Mirrors LostPoweredCenter (0x50E0E0).

#include "../_layout/house_class.h"
#include "../_layout/session_class.h"
#include "../_layout/techno_class.h"
#include "../core/vector_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8EC78
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x752700 (decl; reloc) -- plays an EVA line by name.
void FUN_00752700(const char* name, int a, int b);

// HouseClass::IsControlledByCurrentPlayer (0x50B6F0) as retail expands it inline here.
static inline bool ControlledByCurrentPlayer(HouseClass* house)
{
    if (Session_00A8B238.GameMode == 0) {
        return house->IsHumanPlayer || house->IsInPlayerControl;
    }
    return house == CurrentPlayer;
}

// FUNCTION: GAMEMD 0x50E010
// One more powering centre. When the count reaches one every on-map techno of this house
// whose type is `type` is reactivated, walking the techno array from the top; if any was,
// and the house is the local player's, the "robot tanks back online" EVA line plays.
void HouseClass::FUN_0050E010(TechnoTypeClass* type)
{
    if (++PoweredUnitCenters == 1 && type != 0) {
        bool found = false;
        for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
            TechnoClass* techno = DAT_00A8EC78.Items[i];
            if (techno->Owner == this && techno->vf_33() == type && !techno->InLimbo) {
                techno->Reactivate();
                found = true;
            }
        }
        if (found && DAT_00A8E9A0 && ControlledByCurrentPlayer(this) && DAT_00A8E7AC == 0) {
            FUN_00752700("EVA_RobotTanksBackOnline", -1, -1);
        }
    }
}

// FUNCTION: GAMEMD 0x50E280
// Reactivate every on-map techno of this house whose type is `type`, walking the techno array
// from the top, then play the "robot tanks back online" EVA line for the local player.
void HouseClass::FUN_0050E280(TechnoTypeClass* type)
{
    if (type != 0) {
        bool found = false;
        for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
            TechnoClass* techno = DAT_00A8EC78.Items[i];
            if (techno->Owner == this && techno->vf_33() == type && !techno->InLimbo) {
                techno->Reactivate();
                found = true;
            }
        }
        if (found && DAT_00A8E9A0 && ControlledByCurrentPlayer(this) && DAT_00A8E7AC == 0) {
            FUN_00752700("EVA_RobotTanksBackOnline", -1, -1);
        }
    }
}
