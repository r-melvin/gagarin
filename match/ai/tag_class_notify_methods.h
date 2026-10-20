// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E57F0-0x6E5888), cross-checked
//   against YRpp TagClass.h (consult-only; reconfirmed numerically here).
//
// TagClass static "notify" broadcasters + the IsOnlyInstanceOfType query.
//   * NotifyGlobalChanged / NotifyLocalChanged walk the static TagClass::Array
//     (a DynamicVectorClass<TagClass*> @ 0xB0E720) and, for every live tag,
//     forward the changed index to that tag's FirstTrigger (@ +0x28). The
//     per-tag TagClass::GlobalChanged / ::LocalChanged forwarders are inlined
//     by retail into a direct TriggerClass call (the callee self-null-checks).
//   * IsOnlyInstanceOfType scans the same array comparing each other tag's
//     Type (@ +0x24) to this->Type.
#ifndef GG_MATCH_AI_TAG_CLASS_NOTIFY_METHODS_H
#define GG_MATCH_AI_TAG_CLASS_NOTIFY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

struct TagTypeClass;   // Type pointer is compared by identity only.

// The per-trigger broadcast targets. Declared (no body) so cl emits a
// __thiscall call with a normalised relocation; their own matching is out of
// scope here.
//   GAMEMD 0x7263A0  TriggerClass::GlobalChanged(int)  __thiscall
//   GAMEMD 0x7263D0  TriggerClass::LocalChanged(int)   __thiscall
struct TriggerClass
{
    void GlobalChanged(int idxGlobal);   // GAMEMD 0x7263A0 __thiscall
    void LocalChanged(int idxLocal);     // GAMEMD 0x7263D0 __thiscall
};

// TagClass — only the two pointers the matched methods touch are modelled:
//   Type         @ +0x24  (`mov e?x,[e?x+0x24]` in IsOnlyInstanceOfType)
//   FirstTrigger @ +0x28  (`mov ecx,[ecx+0x28]` in the notify loops)
// The AbstractClass base below Type is padded.
struct TagClass
{
    char          _pad0[0x24];   // +0x00  AbstractClass base
    TagTypeClass* Type;          // +0x24
    TriggerClass* FirstTrigger;  // +0x28

    // Static instance registry @ 0xB0E720; Items @ +0x04, Count @ +0x10.
    static DynamicVectorClass Array;

    static void __fastcall NotifyGlobalChanged(int idxGlobal);   // GAMEMD 0x6E57F0
    static void __fastcall NotifyLocalChanged(int idxLocal);     // GAMEMD 0x6E5820

    bool IsOnlyInstanceOfType() const;                           // GAMEMD 0x6E5850
};

GG_STATIC_ASSERT(offsetof(TagClass, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger) == 0x28);

#endif  // GG_MATCH_AI_TAG_CLASS_NOTIFY_METHODS_H
