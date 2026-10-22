// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// Retail vtable 0x7F45C4 -> locator 0x80BCF0 -> descriptor 0x842CB0
// names .?AVTagTypeClass@@. Constructor writes at 0x6E5B78/82/88,
// allocation at 0x6E6366 and INI/predicate members pin this accessed layout.
// Original field names and complete COM virtual signatures remain unproven.
#ifndef GG_MATCH_LAYOUT_TAG_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TAG_TYPE_CLASS_H
#include "abstract_type_class.h"
#include "../core/vector_class.h"
class TriggerTypeClass;
struct Obj_004A1D30;
struct TagINI_006E6080;
struct CCINI_006E5ED0;
struct CCINI_006E5FE0;
class TagTypeClass;
// GLOBAL: GAMEMD 0xB0E780
// A namespace-scope object, not a class static: retail's atexit cleanup at
// 0x6E5B20 has no destruction guard, which VC6 emits for a static data member.
extern DynamicVectorClass<TagTypeClass*> TagTypes;
class TagTypeClass : public AbstractTypeClass
{
public:
    // Overrides of the slots AbstractClass leaves pure (primary table
    // slots 3, 5, 6, 11, 12; declarations only, bodies not modelled here).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6E63A0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6E6410
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6E6470
    virtual int vf_11();                                                  // 11  0x6E6490
    virtual int vf_12();                                                  // 12  0x6E64A0
    virtual void vf_10(void* target, bool removed);                       // 10  0x6E5E50
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6E63E0
    virtual int vf_16();                                                  // 16  0x6E64B0
    // FUNCTION: GAMEMD 0x6E5B60 (constructor declaration)
    TagTypeClass(const char* id);
    // The stream loader's in-place construction: only the four tables.
    TagTypeClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x6E5CA0 (declaration; destructor)
    ~TagTypeClass();
    // FUNCTION: GAMEMD 0x6E5DD0
    bool FUN_006E5DD0(TriggerTypeClass* trigger);
    // FUNCTION: GAMEMD 0x6E5E00
    bool FUN_006E5E00(TriggerTypeClass* trigger);
    // FUNCTION: GAMEMD 0x6E6310
    static TagTypeClass* FindOrAllocate(const char* id);
    int               unknown_98;           // +0x0098
    int               Persistence;          // +0x009C (store at 0x6E60E1)
    TriggerTypeClass* FirstTrigger;          // +0x00A0  (MOV ESI,[ECX+0xA0])

    // Additional methods, in retail address order.
    // FUNCTION: GAMEMD 0x6E5E70
    static TagTypeClass* FindByNameOrID(const char* name);
    // FUNCTION: GAMEMD 0x6E5ED0
    static void LoadFromINIList(CCINI_006E5ED0* ini);
    // FUNCTION: GAMEMD 0x6E5FE0
    static void SaveToINIList(CCINI_006E5FE0* ini);
    // FUNCTION: GAMEMD 0x6E6080
    bool ReadFromINI(TagINI_006E6080* ini);
    // FUNCTION: GAMEMD 0x6E6160
    bool WriteToINI(TagINI_006E6080* ini);
    int  GetFlags() const;                        // GAMEMD 0x6E61F0
    bool HasAllowWinAction() const;               // GAMEMD 0x6E6220
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x6E6250
    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x6E6280
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x6E62B0
    // FUNCTION: GAMEMD 0x6E62E0
    bool FUN_006E62E0(TriggerTypeClass* trigger) const;
};
GG_STATIC_ASSERT(offsetof(TagTypeClass, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(TagTypeClass, Persistence) == 0x9C);
GG_STATIC_ASSERT(offsetof(TagTypeClass, FirstTrigger) == 0xA0);
GG_STATIC_ASSERT(sizeof(TagTypeClass) == 0xA4);

#endif
