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
void House_00509140::UpdateFactoriesQueues(int rtti, bool isNaval, int buildCat)
{
    Factory_00509140* pFactory;

    switch (rtti) {
    case 7:
        if (buildCat == 5) {
            pFactory = this->At_53CC;
        } else {
            pFactory = this->At_53BC;
        }
        break;

    case 0x28:
        if (isNaval) {
            pFactory = this->At_53B8;
        } else {
            pFactory = this->At_53B4;
        }
        break;

    case 0x10:
        pFactory = this->At_53B0;
        break;

    case 3:
        pFactory = this->At_53AC;
        break;

    default:
        return;
    }

    if (pFactory == 0) {
        return;
    }

    int i = pFactory->QueuedObjects.Count;
    while (--i >= 0) {
        TechnoType_00509140* pType = pFactory->QueuedObjects.Items[i];
        if ((pType->*pType->Vtbl->At_94)(1, 0, 1, this) == 0) {
            if (i < pFactory->QueuedObjects.Count) {
                pFactory->QueuedObjects.Count = pFactory->QueuedObjects.Count - 1;
                for (int j = i; j < pFactory->QueuedObjects.Count; j++) {
                    pFactory->QueuedObjects.Items[j] = pFactory->QueuedObjects.Items[j + 1];
                }
            }
        }
    }

    if (pFactory->Object != 0) {
        TechnoType_00509140* pType =
            (pFactory->Object->*pFactory->Object->Vtbl->GetTechnoType)();
        if ((pType->*pType->Vtbl->At_94)(1, 0, 1, this) == 0) {
            pFactory->FUN_004C9FF0();
            pFactory->FUN_004CA5A0();
        } else {
            TechnoType_00509140* pType2 =
                (pFactory->Object->*pFactory->Object->Vtbl->GetTechnoType)();
            if ((pType2->*pType2->Vtbl->At_94)(1, 1, 1, this) == 0) {
                pFactory->FUN_004C9E60(0);
                if (DAT_00A83D4C == this) {
                    DAT_0087F7E8.FUN_006A60A0(FUN_006ABCD0(rtti, buildCat, isNaval));
                }
            } else if (pFactory->IsSuspended && !pFactory->IsManual) {
                pFactory->FUN_004C9EA0(0);
            }
        }
    }

    if (pFactory->Object == 0 && pFactory->QueuedObjects.Count == 0) {
        (pFactory->*pFactory->Vtbl->At_20)(1);
    }
}
