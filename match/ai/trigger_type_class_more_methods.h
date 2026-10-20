// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x727010 / 0x727050), cross-checked
//   against YRpp TriggerTypeClass.h / TEventClass.h (consult-only; reconfirmed
//   numerically here).
//
// TriggerTypeClass global/local-variable event predicates. Each walks the
// trigger's singly linked event list (FirstEvent @0xAC; node Next @0x28,
// EventKind @0x2c, Value @0x34) and returns true iff some event both has the
// matching set/cleared Kind AND carries the requested variable index in Value:
//   HasGlobalSetOrClearedEvent  — kinds 0x1b (global set) / 0x1c (global clear)
//   HasLocalSetOrClearedEvent   — kinds 0x24 (local  set) / 0x25 (local  clear)
//
// This is the "-more" split of trigger_type_class_methods.h. To keep the TU
// self-contained (one .h + one .cpp) it re-states the same binding plus the
// Value @0x34 node member these two predicates additionally touch.
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// A trigger event list node (TEventClass). These predicates touch the link
// (NextEvent @0x28), the discriminant (EventKind @0x2c) and the payload
// (Value @0x34 — the global/local variable index).
struct TTriggerEventNode
{
    char              _base[0x28];   // +0x00  AbstractClass(0x24) + ArrayIndex
    TTriggerEventNode* Next;         // +0x28  NextEvent
    int               Kind;          // +0x2c  EventKind
    void*             TeamType;      // +0x30  TeamType (untouched here)
    int               Value;         // +0x34  variable index
};

GG_STATIC_ASSERT(offsetof(TTriggerEventNode, Next)  == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerEventNode, Kind)  == 0x2c);
GG_STATIC_ASSERT(offsetof(TTriggerEventNode, Value) == 0x34);

struct TriggerTypeClass : AbstractTypeClass
{
    bool HasGlobalSetOrClearedEvent(int value) const;  // GAMEMD 0x727010
    bool HasLocalSetOrClearedEvent(int value) const;   // GAMEMD 0x727050

    // AbstractTypeClass occupies [0x00..0x97]. Only FirstEvent is touched here.
    int                ArrayIndex;    // +0x98
    bool               Difficulty[3]; // +0x9c
    bool               Enabled;       // +0x9f
    bool               MustTransfer;  // +0xa0
    unsigned char      align_A1[3];   // +0xa1
    void*              House;         // +0xa4
    TriggerTypeClass*  NextTrigger;   // +0xa8
    TTriggerEventNode* FirstEvent;    // +0xac
    void*              FirstAction;   // +0xb0
};

GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent) == 0xac);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H
