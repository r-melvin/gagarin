// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at
//   0x6E57F0 / 0x6E5820 / 0x6E5850). Names cross-checked against YRpp
//   TagClass.h (consult-only; offsets reconfirmed numerically here).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E57F0  TagClass::NotifyGlobalChanged  (__fastcall)
//   FUNCTION: GAMEMD 0x6E5820  TagClass::NotifyLocalChanged   (__fastcall)
//   FUNCTION: GAMEMD 0x6E5850  TagClass::IsOnlyInstanceOfType (__thiscall)

#include "tag_class_notify_methods.h"

// FUNCTION: GAMEMD 0x6E57F0  (static __fastcall, idxGlobal in ECX)
// Broadcast a global-variable change to every live tag. The per-tag
// GlobalChanged forwarder is inlined to a direct FirstTrigger->GlobalChanged
// call; Array.Count is reloaded each iteration across the call.
void __fastcall TagClass::NotifyGlobalChanged(int idxGlobal)
{
    for (int i = 0; i < Array.Count; ++i) {
        ((TagClass**)Array.Items)[i]->FirstTrigger->GlobalChanged(idxGlobal);
    }
}

// FUNCTION: GAMEMD 0x6E5820  (static __fastcall, idxLocal in ECX)
void __fastcall TagClass::NotifyLocalChanged(int idxLocal)
{
    for (int i = 0; i < Array.Count; ++i) {
        ((TagClass**)Array.Items)[i]->FirstTrigger->LocalChanged(idxLocal);
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
