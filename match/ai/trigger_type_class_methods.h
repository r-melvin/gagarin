// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x726F50-0x727000), cross-checked
//   against YRpp TriggerTypeClass.h / TEventClass.h (consult-only; reconfirmed
//   numerically here).
//
// TriggerTypeClass event/action predicates — each walks the trigger's singly
// linked event list (FirstEvent @0xAC) or action list (FirstAction @0xB0),
// returning true if any node has the matching Kind (node Kind @0x2C, Next
// @0x28). The list nodes (TEventClass / TActionClass) both derive AbstractClass
// (0x24) and place Next@0x28, Kind@0x2c.
// Retail RTTI confirms the class key: TypeDescriptor 0x842D08 is named
// ".?AVTriggerTypeClass@@"; the hierarchy records AbstractTypeClass at offset 0.
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// A trigger event/action list node. Only the link (Next@0x28) and the
// discriminant Kind (@0x2c) are touched by these predicates.
struct TTriggerListNode
{
    char Next_NextEvent_pad[0x28];   // +0x00  AbstractClass base + ArrayIndex
    TTriggerListNode* Next;          // +0x28  NextEvent / NextAction
    int               Kind;          // +0x2c  EventKind / ActionKind
};

GG_STATIC_ASSERT(offsetof(TTriggerListNode, Next) == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Kind) == 0x2c);

class TriggerTypeClass : public AbstractTypeClass
{
public:
    bool HasCrossesVerticalLineEvent() const;    // GAMEMD 0x726F50
    bool HasCrossesHorizontalLineEvent() const;  // GAMEMD 0x726F80
    bool HasZoneEntryByEvent() const;            // GAMEMD 0x726FB0
    bool HasAllowWinAction() const;              // GAMEMD 0x726FE0

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

GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent)  == 0xac);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xb0);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H
