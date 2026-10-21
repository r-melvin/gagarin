// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x726350 + 0x726630), cross-checked
//   against YRpp TriggerClass.h (consult-only; reconfirmed numerically here).
//
// Two further TriggerClass entry points:
//   0x726350  HasGlobalSetOrClearedEvent(int idxGlobal) const
//             Delegates to the TriggerTypeClass-side predicate (@0x727010) for
//             this trigger's Type (@0x24) and, when present, its AttachedTrigger
//             (@0x28) chain link's Type.
//   0x726630  GetInstance(TriggerTypeClass*)  (static, __fastcall — arg in ECX)
//             Linear-scans the global TriggerClass::Array (@0xA8EAE8) for an
//             entry whose Type (@0x24) matches; otherwise allocates a fresh one
//             via operator new(0x48) + the out-of-line ctor (@0x725FA0).
//
// Confirmed from the disasm:
//   mov ecx,[esi+0x24]      -> Type
//   mov eax,[esi+0x28]      -> AttachedTrigger
//   mov edx,[0x00A8EAF8]    -> Array.Count     (base 0xA8EAE8 +0x10)
//   mov edi,[0x00A8EAEC]    -> Array.Items      (base 0xA8EAE8 +0x04)
//   cmp esi,[ebx+0x24]      -> Items[i]->Type == pType
//   push 0x48 ; call 0x7C8E17 -> operator new(sizeof TriggerClass == 0x48)
//   call 0x725FA0           -> TriggerClass::TriggerClass(TriggerTypeClass*)
#ifndef GG_MATCH_AI_TRIGGER_CLASS_MORE_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_class.h"
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8E17 -- allocation target used by native GetInstance.
void* __cdecl operator new(size_t size);

// TriggerTypeClass — only the global-set/cleared predicate is modelled here; it
// is a separate retail __thiscall taking the global index and returning bool.
class TriggerTypeClass
{
public:
    bool HasGlobalSetOrClearedEvent(int idxGlobal) const;  // GAMEMD 0x727010
};

// GetInstance uses the shared 0x48-byte TriggerClass declaration.


GG_STATIC_ASSERT(offsetof(TriggerClass, Type)            == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, AttachedTrigger) == 0x28);
GG_STATIC_ASSERT(sizeof(TriggerClass)                    == 0x48);

#endif  // GG_MATCH_AI_TRIGGER_CLASS_MORE_METHODS_H
