// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | names consult-only
// Retail RTTI TypeDescriptor 0x842D08 names ".?AVTriggerTypeClass@@" and
// records AbstractTypeClass at offset zero. The 0xB4 allocation at 0x7275D0,
// constructor 0x726C80 and member-using functions pin the layout below.
// Existing descriptive names do not establish original private source spelling.
#ifndef GG_MATCH_LAYOUT_TRIGGER_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TRIGGER_TYPE_CLASS_H
#include <stddef.h>
#include "abstract_type_class.h"
#include "vector_class.h"
struct HouseTypeClass;
struct CCINI_007275D0;
struct CCINI_00727880;

// Read view of event/action list links and discriminants. Value is used only
// by event predicates; no complete concrete event/action layout is claimed.
struct TTriggerListNode
{
    unsigned char unknown_00[0x28];
    TTriggerListNode* Next;
    int Kind;
    unsigned char unknown_30[4];
    int Value;
};
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Next) == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Kind) == 0x2C);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Value) == 0x34);

class TriggerTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x726C80 (constructor declaration)
    TriggerTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x726F50
    bool HasCrossesVerticalLineEvent() const;
    // FUNCTION: GAMEMD 0x726F80
    bool HasCrossesHorizontalLineEvent() const;
    // FUNCTION: GAMEMD 0x726FB0
    bool HasZoneEntryByEvent() const;
    // FUNCTION: GAMEMD 0x726FE0
    bool HasAllowWinAction() const;
    // FUNCTION: GAMEMD 0x727010
    bool HasGlobalSetOrClearedEvent(int value) const;
    // FUNCTION: GAMEMD 0x727050
    bool HasLocalSetOrClearedEvent(int value) const;
    // FUNCTION: GAMEMD 0x727120
    static TriggerTypeClass* __fastcall FindByNameOrID(const char* name);
    // FUNCTION: GAMEMD 0x7271E0
    unsigned int GetFlags();
    // FUNCTION: GAMEMD 0x7275D0
    static void __fastcall LoadFromINIList(CCINI_007275D0* ini);
    // FUNCTION: GAMEMD 0x727880
    static void __fastcall SaveToINIList(CCINI_00727880* ini);
    // FUNCTION: GAMEMD 0x727AA0
    static TriggerTypeClass* __fastcall FindOrAllocate(const char* id);
    int ArrayIndex;
    unsigned char Difficulty[3];
    unsigned char Enabled;
    unsigned char unknown_A0;
    unsigned char unknown_A1[3];
    HouseTypeClass* House;
    TriggerTypeClass* NextTrigger;
    TTriggerListNode* FirstEvent;
    TTriggerListNode* FirstAction;
    // GLOBAL: GAMEMD 0x8B4178
    static DynamicVectorClassLayout Array;
};
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, ArrayIndex) == 0x98);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, Difficulty) == 0x9C);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, Enabled) == 0x9F);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, unknown_A1) == 0xA1);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, House) == 0xA4);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, NextTrigger) == 0xA8);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent) == 0xAC);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xB0);
GG_STATIC_ASSERT(sizeof(TriggerTypeClass) == 0xB4);
#endif
