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
// MATCHED 100% (was 56.0%). Two things had to be true at once, and each alone
// still reads as a wrong body:
//
//   * The shift loop's bound is the *member* `QueuedObjects_Count`, re-read on
//     every iteration (retail's `MOV ECX,[ESI+0x50]` inside the loop), not a
//     local copy. The store through `QueuedObjects_Items[i]` can alias the
//     member, so a faithful source cannot hoist it and neither does cl.
//   * The count read that feeds the guard and the decrement has to be a genuine
//     second load. Retail loads `[ESI+0x50]` twice, once for the empty-queue
//     guard at the top and again after `Items[0]` has been dereferenced; cl
//     common-subexpression-eliminates the two and hoists the surviving test
//     above the dereference, which shifts the whole unlink by one instruction
//     and is what capped every earlier spelling. Reading it through a volatile
//     lvalue pins the reload without changing anything else, and the
//     `LEA ECX,[EAX-1]` that keeps the original live then falls out of
//     `Count = count - 1`.
//
// Measured in two match_all batches: the previous local-count spelling 56.0%,
// member bound with an ordinary reload 12.0%, `i-1`/`i` indices 54.0%, the
// decrement in its own local 12.0%, members throughout 12.0%, a while-loop
// 12.0%, the forced reload with the loop bound also volatile 31.4%, the forced
// reload over the old local-count body 33.3%, and the forced reload with the
// member bound 100% (this spelling; the same with the decrement in a named
// local also reaches 100%).
void FactoryClass::StartProduction()
{
    if (QueuedObjects_Count == 0)
        return;

    if (Object != 0)
        return;

    if (unknown_38 != 0 && !IsSuspended)
        return;

    TechnoTypeClass* type = QueuedObjects_Items[0];

    int count = *(volatile int*)&QueuedObjects_Count;
    if (count > 0)
    {
        QueuedObjects_Count = count - 1;
        for (int i = 0; i < QueuedObjects_Count; i++)
            QueuedObjects_Items[i] = QueuedObjects_Items[i + 1];
    }

    int result = type->Slot_40();
    if (result < 0)
        return;

    Owner->ProductionStarted(type->Slot_2C(result, type->unknown_CCE, 1));
}
