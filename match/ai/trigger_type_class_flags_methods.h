// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x727120 / 0x7271E0), cross-checked
//   against YRpp TriggerTypeClass.h (consult-only; reconfirmed numerically here).
//
//   This binding mirrors match/ai/trigger_type_class_methods.h (same layout
//   spine), adding the two members touched by FindByNameOrID / GetFlags:
//     - the static lookup array TriggerTypeClass::Array (global @0x8B4178)
//     - ID (+0x24) / Name (+0x64) from AbstractTypeClass, NextTrigger (+0xA8),
//       FirstEvent (+0xAC), FirstAction (+0xB0).
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// A trigger event/action list node. Only the link (Next@0x28) and the
// discriminant Kind (@0x2c) are touched here.
struct TTriggerListNode
{
    char              Next_pad[0x28];   // +0x00  AbstractClass base + ArrayIndex
    TTriggerListNode* Next;             // +0x28  NextEvent / NextAction
    int               Kind;             // +0x2c  EventKind / ActionKind
};

GG_STATIC_ASSERT(offsetof(TTriggerListNode, Next) == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Kind) == 0x2c);

struct TriggerTypeClass : AbstractTypeClass
{
    // Static lookup: case-insensitive find by ID (+0x24) or Name (+0x64).
    static TriggerTypeClass* __fastcall FindByNameOrID(const char* name); // 0x727120

    // OR of the flag-bits contributed by every event/action in this trigger
    // and every trigger chained through NextTrigger.
    unsigned int GetFlags();                                              // 0x7271E0

    // AbstractTypeClass occupies [0x00..0x97]. Trigger-specific members follow.
    int               ArrayIndex;        // +0x98
    bool              Difficulty[3];     // +0x9c
    bool              Enabled;           // +0x9f
    bool              MustTransfer;      // +0xa0
    unsigned char     align_A1[3];       // +0xa1
    void*             House;             // +0xa4
    TriggerTypeClass* NextTrigger;       // +0xa8
    TTriggerListNode* FirstEvent;        // +0xac
    TTriggerListNode* FirstAction;       // +0xb0
};

GG_STATIC_ASSERT(offsetof(TriggerTypeClass, NextTrigger) == 0xa8);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent)  == 0xac);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xb0);

// DynamicVectorClass<TriggerTypeClass*> — the global TriggerTypeClass::Array.
// Base @0x8B4178 (vtable). Confirmed from the disasm:
//   +0x04 Items (DAT_008B417C), +0x10 Count (DAT_008B4188).
struct TriggerTypeVectorClass
{
    void*              vtable;             // +0x00
    TriggerTypeClass** Items;             // +0x04
    int                Capacity;          // +0x08
    char               IsInitialized;     // +0x0C
    char               IsAllocated;       // +0x0D
    char               _pad_0E[2];        // +0x0E
    int                Count;             // +0x10
    int                CapacityIncrement; // +0x14
};

GG_STATIC_ASSERT(offsetof(TriggerTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TriggerTypeVectorClass, Count) == 0x10);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H
