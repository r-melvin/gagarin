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
#include "../_rt/gg_static_assert.h"

// Global operator new (GAMEMD 0x7C8E17) — declared so the explicit allocation
// in GetInstance emits the (relocation-normalised) cdecl call.
void* __cdecl operator new(size_t size);

// TriggerTypeClass — only the global-set/cleared predicate is modelled here; it
// is a separate retail __thiscall taking the global index and returning bool.
struct TriggerTypeClass
{
    bool HasGlobalSetOrClearedEvent(int idxGlobal) const;  // GAMEMD 0x727010
};

// TriggerClass — sizeof 0x48 so `new TriggerClass(...)` emits operator new(0x48).
// Only Type (@0x24) and AttachedTrigger (@0x28) are named; the rest is opaque.
struct TriggerClass
{
    // FUNCTION: GAMEMD 0x725FA0 (declaration; native constructor)
    TriggerClass(TriggerTypeClass* type);

    char              _pad0[0x24];      // +0x00  (AbstractClass base; modelled in P2)
    TriggerTypeClass* Type;             // +0x24
    TriggerClass*     AttachedTrigger;  // +0x28
    char              _pad2c[0x48 - 0x2C]; // +0x2C  (unknown remainder; size to 0x48)

    // Out-of-line ctor (GAMEMD 0x725FA0) — modelled as a plain __thiscall
    // stand-in (no body) so it is called directly, without the new-expression
    // exception-unwind funclet that an actual C++ constructor would emit.
    TriggerClass* Construct(TriggerTypeClass* pType);  // GAMEMD 0x725FA0

    bool HasGlobalSetOrClearedEvent(int idxGlobal) const;       // GAMEMD 0x726350
    static TriggerClass* __fastcall GetInstance(TriggerTypeClass* pType); // GAMEMD 0x726630
};

GG_STATIC_ASSERT(offsetof(TriggerClass, Type)            == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, AttachedTrigger) == 0x28);
GG_STATIC_ASSERT(sizeof(TriggerClass)                    == 0x48);

// DynamicVectorClass<TriggerClass*> — the global `TriggerClass::Array`.
// Base @0xA8EAE8 (vtable). Confirmed offsets from the disasm:
//   +0x04 Items (DAT_00A8EAEC),  +0x10 Count (DAT_00A8EAF8).
struct TriggerVectorClass
{
    void*          vtable;             // +0x00
    TriggerClass** Items;             // +0x04
    int            Capacity;          // +0x08
    char           IsInitialized;     // +0x0C
    char           IsAllocated;       // +0x0D
    char           _pad_0E[2];        // +0x0E
    int            Count;             // +0x10
    int            CapacityIncrement; // +0x14
};

GG_STATIC_ASSERT(offsetof(TriggerVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TriggerVectorClass, Count) == 0x10);

// GLOBAL: GAMEMD 0xA8EAE8 — TriggerClass::Array.
extern TriggerVectorClass TriggerArray;

#endif  // GG_MATCH_AI_TRIGGER_CLASS_MORE_METHODS_H
