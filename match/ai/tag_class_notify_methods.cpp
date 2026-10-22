// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at
//   0x6E57F0 / 0x6E5820 / 0x6E5850). Names cross-checked against YRpp
//   (offsets reconfirmed numerically here).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E57F0  TagClass::NotifyGlobalChanged  (__fastcall)
//   FUNCTION: GAMEMD 0x6E5820  TagClass::NotifyLocalChanged   (__fastcall)
//   FUNCTION: GAMEMD 0x6E5850  TagClass::IsOnlyInstanceOfType (__thiscall)

#include "../_layout/tag_class.h"
#include "trigger_class_methods.h"
GG_STATIC_ASSERT(offsetof(TagClass, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger) == 0x28);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Count) == 0x10);

// FUNCTION: GAMEMD 0x6E57F0  (static __fastcall, idxGlobal in ECX)
// Pass each tag's FirstTrigger pointer unchanged to 0x7263A0. The registry
// count is reloaded after the call. Original forwarding-method ownership is
// not established by this callsite.
void __fastcall TagClass::NotifyGlobalChanged(int idxGlobal)
{
    for (int i = 0; i < Array.Count; ++i) {
        static_cast<TriggerClass*>(((TagClass**)Array.Items)[i]->FirstTrigger)
            ->NotifyGlobalChanged(idxGlobal);
    }
}

// FUNCTION: GAMEMD 0x6E5820  (static __fastcall, idxLocal in ECX)
void __fastcall TagClass::NotifyLocalChanged(int idxLocal)
{
    for (int i = 0; i < Array.Count; ++i) {
        static_cast<TriggerClass*>(((TagClass**)Array.Items)[i]->FirstTrigger)
            ->NotifyLocalChanged(idxLocal);
    }
}

// FUNCTION: GAMEMD 0x6E5850  (__thiscall)
// True iff no other tag in the registry shares this tag's Type. Items/Count are
// hoisted (no call in the loop): retail walks Items by a +4 pointer stride with
// a separate counter, so the index form below lowers to the same walk.
bool TagClass::IsOnlyInstanceOfType() const
{
    for (int i = 0; i < Array.Count; ++i) {
        TagClass* tag = ((TagClass**)Array.Items)[i];
        if (tag != this && tag->Type == this->Type) {
            return false;
        }
    }
    return true;
}
