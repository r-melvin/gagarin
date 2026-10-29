// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x509140.

#include "house_class_factory_queues_methods.h"

// FUNCTION: GAMEMD 0x509140  HouseClass::Update_FactoriesQueues (__thiscall, ret 0xC)
//
// Something changed what this house is allowed to build, so the factory that
// serves the given category is re-checked: every queued type that is no longer
// buildable is slid out of the queue, and the item actually in production is
// either abandoned outright, suspended (repainting the player's sidebar tab),
// or resumed if it was only suspended by this same rule. A factory left with
// nothing in production and nothing queued is shut down.
void HouseClass::UpdateFactoriesQueues(int rtti, bool isNaval, int buildCat)
{
    FactoryClass* pFactory;

    switch (rtti) {
    case 7:
        if (buildCat == 5) {
            pFactory = this->Primary_ForDefenses;
        } else {
            pFactory = this->Primary_ForBuildings;
        }
        break;

    case 0x28:
        if (isNaval) {
            pFactory = this->Primary_ForShips;
        } else {
            pFactory = this->Primary_ForVehicles;
        }
        break;

    case 0x10:
        pFactory = this->Primary_ForInfantry;
        break;

    case 3:
        pFactory = this->Primary_ForAircraft;
        break;

    default:
        return;
    }

    if (pFactory == 0) {
        return;
    }

    int i = pFactory->QueuedObjects.Count;
    while (--i >= 0) {
        TechnoTypeClass* pType = const_cast<TechnoTypeClass*>(pFactory->QueuedObjects.Items[i]);
        if (pType->vf_37(true, false, true, this) == 0) {
            if (i < pFactory->QueuedObjects.Count) {
                pFactory->QueuedObjects.Count = pFactory->QueuedObjects.Count - 1;
                for (int j = i; j < pFactory->QueuedObjects.Count; j++) {
                    pFactory->QueuedObjects.Items[j] = pFactory->QueuedObjects.Items[j + 1];
                }
            }
        }
    }

    if (pFactory->Object != 0) {
        TechnoTypeClass* pType = pFactory->Object->vf_33();
        if (pType->vf_37(true, false, true, this) == 0) {
            pFactory->AbandonProduction();
            pFactory->StartProduction();
        } else {
            TechnoTypeClass* pType2 = pFactory->Object->vf_33();
            if (pType2->vf_37(true, true, true, this) == 0) {
                pFactory->Suspend(false);
                if (DAT_00A83D4C == this) {
                    DAT_0087F7E8.FUN_006A60A0(FUN_006ABCD0(rtti, buildCat, isNaval));
                }
            } else if (pFactory->IsSuspended && !pFactory->IsManual) {
                pFactory->Unsuspend(false);
            }
        }
    }

    if (pFactory->Object == 0 && pFactory->QueuedObjects.Count == 0) {
        delete pFactory;
    }
}
