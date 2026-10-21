// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | names consult-only
// Retail vtable 0x7F45C4 -> locator 0x80BCF0 -> descriptor 0x842CB0
// names .?AVTagTypeClass@@. Constructor writes at 0x6E5B78/82/88,
// allocation at 0x6E6366 and INI/predicate members pin this accessed layout.
// Original field names and complete COM virtual signatures remain unproven.
#ifndef GG_MATCH_LAYOUT_TAG_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TAG_TYPE_CLASS_H
#include "abstract_type_class.h"
#include "vector_class.h"
class TriggerTypeClass;
struct TagINI_006E6080;
struct CCINI_006E5ED0;
struct CCINI_006E5FE0;
class TagTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x6E5B60 (constructor declaration)
    TagTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x6E6310
    static TagTypeClass* __fastcall FindOrAllocate(const char* id);
    // GLOBAL: GAMEMD 0xB0E780
    static DynamicVectorClassLayout Array;
    int               unknown_98;           // +0x0098
    int               Persistence;          // +0x009C (store at 0x6E60E1)
    TriggerTypeClass* FirstTrigger;          // +0x00A0  (MOV ESI,[ECX+0xA0])

    // Additional methods, in retail address order.
    // FUNCTION: GAMEMD 0x6E5E70
    static TagTypeClass* __fastcall FindByNameOrID(const char* name);
    // FUNCTION: GAMEMD 0x6E5ED0
    static void __fastcall LoadFromINIList(CCINI_006E5ED0* ini);
    // FUNCTION: GAMEMD 0x6E5FE0
    static void __fastcall SaveToINIList(CCINI_006E5FE0* ini);
    // FUNCTION: GAMEMD 0x6E6080
    bool ReadFromINI(TagINI_006E6080* ini);
    // FUNCTION: GAMEMD 0x6E6160
    bool WriteToINI(TagINI_006E6080* ini);
    int  GetFlags() const;                        // GAMEMD 0x6E61F0
    bool HasAllowWinAction() const;               // GAMEMD 0x6E6220
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x6E6250
    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x6E6280
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x6E62B0
};
GG_STATIC_ASSERT(offsetof(TagTypeClass, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(TagTypeClass, Persistence) == 0x9C);
GG_STATIC_ASSERT(offsetof(TagTypeClass, FirstTrigger) == 0xA0);
GG_STATIC_ASSERT(sizeof(TagTypeClass) == 0xA4);

#endif
