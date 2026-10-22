// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CA5A0.

#include "factory_class_start_methods.h"

// FUNCTION: GAMEMD 0x4CA5A0  FactoryClass::StartProduction (__thiscall)
// Pull the head of the production queue and hand it to the owning house. Bails
// if the queue is empty, if something is already being built, or if the factory
// is gated and not suspended. The unlink is DynamicVectorClass::RemoveItem(0)
// written out inline.
//
// PARTIAL, 56.0% (28/50). Retail reloads the count from the member after
// dereferencing Items[0] and re-reads the member as the loop bound; this
// local-count body reads it once (a member-bound loop scores 12.0%).
void FactoryClass::StartProduction()
{
    if (QueuedObjects_Count == 0)
        return;

    if (Object != 0)
        return;

    if (unknown_38 != 0 && !IsSuspended)
        return;

    TechnoTypeClass* type = QueuedObjects_Items[0];

    int count = QueuedObjects_Count;
    if (count > 0)
    {
        count--;
        QueuedObjects_Count = count;
        for (int i = 0; i < count; i++)
            QueuedObjects_Items[i] = QueuedObjects_Items[i + 1];
    }

    int result = type->Slot_40();
    if (result < 0)
        return;

    Owner->ProductionStarted(type->Slot_2C(result, type->unknown_CCE, 1));
}
