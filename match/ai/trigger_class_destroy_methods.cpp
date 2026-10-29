// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7265C0  TriggerClass::FireActions (__thiscall)
//   FUNCTION: GAMEMD 0x726720  TriggerClass::Destroy     (__thiscall)

#include "trigger_class_destroy_methods.h"

// FUNCTION: GAMEMD 0x7265C0  (__thiscall)
// Walks the trigger type's action list; each action is Execute()d against the
// trigger's owner house (HouseClass::FindByCountryIndex of the type's House).
// Returns whether at least one action executed.
bool TriggerClass::FireActions(ObjectClass* pObj, CellStruct location)
{
    if (this->Enabled && !this->Destroyed) {
        bool result = false;
        for (TActionClass* action = reinterpret_cast<TActionClass*>(this->Type->FirstAction); action != 0;
             action = action->unknown_28) {
            if (action->Execute(
                    HouseClass::FindByCountryIndex(this->Type->House->ArrayIndex),
                    pObj, this, location)) {
                result = true;
            }
        }
        return result;
    }
    return false;
}

// FUNCTION: GAMEMD 0x726720  (__thiscall)
// Marks the trigger as destroyed and appends it to the global destruction queue.
// The inlined AddItem reaches the virtual SetCapacity through the vector's own
// `this` (slot 2, [vtable+0x08]) on the constant global object; the header's
// AddItem carries the phrasing that keeps retail's register order (53.3% with
// the member re-read at each use and the split `index = Count; Count = index +
// 1;`, which sinks the vtable load below the pushes and emits an LEA).
void TriggerClass::Destroy()
{
    this->Destroyed = true;
    reinterpret_cast<TriggerPtrVector*>(&DAT_00B0F698)->AddItem(this);
}
