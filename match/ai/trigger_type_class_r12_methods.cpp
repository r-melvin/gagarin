// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TriggerTypeClass pointer-expiry notification, read off retail gamemd.exe v1.001.
//   Address index: 0x727090.

#include "../_layout/trigger_type_class.h"

// An event or action in one of the trigger's lists: a polymorphic object with its link at +0x28.
class TriggerNodeView_r12
{
public:
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void vf_0C();
    virtual void vf_10();
    virtual void vf_14();
    virtual void vf_18();
    virtual void vf_1C();
    virtual void vf_20();
    virtual void vf_24();
    virtual void vf_28(void* target, bool removed);     // 10: pointer expired
    char unknown_04[0x28 - 0x04];
    TriggerNodeView_r12* Next;                          // +0x28
};
GG_STATIC_ASSERT(offsetof(TriggerNodeView_r12, Next) == 0x28);

// FUNCTION: GAMEMD 0x727090
// Drops the next-trigger link if it is the expired object, and passes the notice to every action
// and event, unlinking either list head if it is the expired object.
void TriggerTypeClass::vf_10(void* target, bool removed)
{
    if (NextTrigger && (void*)NextTrigger == target) {
        NextTrigger = NextTrigger->NextTrigger;
    }
    TriggerNodeView_r12* node;
    for (node = (TriggerNodeView_r12*)FirstAction; node; node = node->Next) {
        node->vf_28(target, true);
    }
    if ((void*)FirstAction == target) {
        FirstAction = FirstAction->Next;
    }
    for (node = (TriggerNodeView_r12*)FirstEvent; node; node = node->Next) {
        node->vf_28(target, true);
    }
    if ((void*)FirstEvent == target) {
        FirstEvent = FirstEvent->Next;
    }
}
