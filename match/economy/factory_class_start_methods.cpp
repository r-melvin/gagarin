// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CA5A0.

#include "factory_class_start_methods.h"

// FUNCTION: GAMEMD 0x4CA5A0  FactoryClass::StartProduction (__thiscall)
// Pull the head of the production queue and hand it to the owning house. Bails
// if the queue is empty, if something is already being built, or if the factory
// is gated and not suspended. The unlink is the inline
// DynamicVectorClass::Delete(0): its bound test, the decrement and the shift
// loop that re-reads ActiveCount as its bound are all retail's.
void FactoryClass::StartProduction()
{
    if (QueuedObjects.Count() == 0)
        return;

    if (Object != 0)
        return;

    if (unknown_38 != 0 && !IsSuspended)
        return;

    TechnoTypeClass* type = QueuedObjects.Items[0];
    QueuedObjects.Delete(0);

    int result = type->Slot_40();
    if (result < 0)
        return;

    Owner->ProductionStarted(type->Slot_2C(result, type->unknown_CCE, 1));
}
