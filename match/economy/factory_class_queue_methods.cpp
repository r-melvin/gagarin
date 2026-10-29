// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp
//   (every offset reconfirmed against the binary in the header).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4CA620   FactoryClass::RemoveOneFromQueue  (__thiscall)
//   FUNCTION: GAMEMD 0x4CA670   FactoryClass::CountTotal          (__thiscall)

#include "factory_class_queue_methods.h"

// FUNCTION: GAMEMD 0x4CA620  (__thiscall)
// Find pItem in the queue (genuine virtual FindItemIndex via [vtbl+0x10]); if
// present, shift the tail down over its slot (inlined RemoveItem) and report
// true, otherwise false.
bool FactoryClass::RemoveOneFromQueue(TechnoTypeClass const* pItem)
{
    int idx = this->QueuedObjects.FindItemIndex(pItem);
    if (idx != -1)
        return this->QueuedObjects.Delete(idx);
    return false;
}

// FUNCTION: GAMEMD 0x4CA670  (__thiscall)
// Total of this type both in production and queued: one for the in-production
// Object whose GetTechnoType() matches, plus every queued entry equal to pType.
int FactoryClass::CountTotal(TechnoTypeClass const* pType) const
{
    int count = 0;
    if (this->Object && this->Object->vf_33() == pType)
        count = 1;
    for (int i = 0; i < this->QueuedObjects.Count; ++i)
    {
        if (this->QueuedObjects.Items[i] == pType)
            ++count;
    }
    return count;
}
