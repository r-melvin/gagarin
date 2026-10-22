// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   RTTI: primary vtable 0x7E2A50 (".?AVAITriggerTypeClass@@"), with the
//   IRTTITypeInfo / INoticeSink / INoticeSource tables 0x7E2A34 / 0x7E2A2C /
//   0x7E2A24 stored by the constructor 0x41E350. AbstractTypeClass base (the
//   constructor chains 0x410800, the destructor 0x4109C0). Size 0x110 from
//   slot 12 (0x41FFE0) and the allocation in 0x41F2E0 (PUSH 0x110).
//   Every field below is written by the constructor 0x41E350; the three
//   pointers at +0xD8/+0xDC/+0xE0 are swizzled by Load 0x41E540 and set by
//   0x41FD30/0x41FD40/0x41FD50; the 0x20-byte block at +0xE4 is cleared with
//   one REP STOSD of 8 dwords. Names that other units already use for these
//   offsets (ConditionObject, Number, ComparatorOperand, IsGlobal, IsEnabled,
//   the weights and the two counters) were cross-checked against YRpp and
//   confirmed by the readers named beside them; the rest are placeholders.
//   Several older per-function views (ai/ai_trigger_*_methods.h) declare
//   partial structs under the same class name; they are not merged here.
#ifndef GG_MATCH_LAYOUT_AI_TRIGGER_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_AI_TRIGGER_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../core/vector_class.h"

class AITriggerTypeClass;
class TechnoTypeClass;
class TeamTypeClass;
class CCINIClass;
struct AITriggerHouse;
class HouseClass;

// The condition block at +0xE4. 0x41EC90 compares a count against Number
// with the operator in ComparatorOperand (0..5).
struct AITriggerCondition
{
    int Number;             // +0x00 (CMP EAX,[EDI+0xE4] @0x41EE18)
    int ComparatorOperand;  // +0x04 (switch on [EDI+0xE8] @0x41ED80)
    int unknown_08[6];      // +0x08
};
GG_STATIC_ASSERT(sizeof(AITriggerCondition) == 0x20);

// GLOBAL: GAMEMD 0xA8B200
// A namespace-scope object, as TagTypes in tag_type_class.h.
extern DynamicVectorClass<AITriggerTypeClass*> AITriggerTypes;

// VTABLE: GAMEMD 0x7E2A50 (IPersistStream side, 27 slots)
// VTABLE: GAMEMD 0x7E2A34 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E2A2C (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E2A24 (INoticeSource side, +0x0C)
class AITriggerTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x41E350 (declaration)
    AITriggerTypeClass(const char* id);
    // The stream loader's in-place construction: only the four tables.
    AITriggerTypeClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x41E480 (declaration; destructor; slot 8 = 0x41FFF0)
    virtual ~AITriggerTypeClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x41E500
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x41E540
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x41E5C0
    virtual int vf_11();                                                  // 11  0x41FFD0
    virtual int vf_12();                                                  // 12  0x41FFE0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x41E5E0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x41F580
    virtual bool vf_26(CCINIClass* ini);                                  // 26  0x41FB10

    // FUNCTION: GAMEMD 0x41EC90 (declaration)
    bool FUN_0041EC90(AITriggerHouse* calling, AITriggerHouse* target);
    // FUNCTION: GAMEMD 0x41F030 (declaration)
    bool FUN_0041F030(AITriggerHouse* calling, AITriggerHouse* target) const;
    // FUNCTION: GAMEMD 0x41F080 (declaration)
    bool FUN_0041F080(AITriggerHouse* calling, AITriggerHouse* target) const;
    // FUNCTION: GAMEMD 0x41F0D0 (decl; reloc) -- defined in ai/ai_trigger_charged_methods.cpp.
    bool IronCurtainCharged(HouseClass* callingHouse, HouseClass* targetHouse) const;
    // FUNCTION: GAMEMD 0x41F180 (decl; reloc) -- defined in ai/ai_trigger_charged_methods.cpp.
    bool ChronoSphereCharged(HouseClass* callingHouse, HouseClass* targetHouse) const;
    // FUNCTION: GAMEMD 0x41F2E0 (declaration)
    static void FUN_0041F2E0(CCINIClass* ini, int isGlobal);
    // FUNCTION: GAMEMD 0x41FD60 (decl; reloc) -- defined in ai/ai_trigger_register_methods.cpp.
    void RegisterSuccess();
    // FUNCTION: GAMEMD 0x41FE20 (decl; reloc) -- defined in ai/ai_trigger_register_methods.cpp.
    void RegisterFailure();
    // FUNCTION: GAMEMD 0x41FEE0 (declaration; `this` unused, RET 0xC)
    bool FUN_0041FEE0(TeamTypeClass* team, AITriggerHouse* first, AITriggerHouse* second);
    // FUNCTION: GAMEMD 0x41FD30 (declaration)
    void FUN_0041FD30(TechnoTypeClass* object);
    // FUNCTION: GAMEMD 0x41FD40 (declaration)
    void FUN_0041FD40(TeamTypeClass* team);
    // FUNCTION: GAMEMD 0x41FD50 (declaration)
    void FUN_0041FD50(TeamTypeClass* team);

    int                  unknown_98;        // +0x98 the condition kind (0..7; CRC switch @0x41E634)
    int                  IsGlobal;          // +0x9C (1 also sets IsEnabled @0x41F3B2)
    int                  unknown_A0;        // +0xA0
    bool                 IsEnabled;         // +0xA4
    unsigned char        _pad_A5[3];        // +0xA5
    int                  unknown_A8;        // +0xA8 (-1 from the constructor)
    int                  unknown_AC;        // +0xAC
    int                  unknown_B0;        // +0xB0
    unsigned char        _pad_B4[4];        // +0xB4
    double               Weight_Current;    // +0xB8 (1.0 from the constructor)
    double               Weight_Minimum;    // +0xC0
    double               Weight_Maximum;    // +0xC8
    bool                 unknown_D0;        // +0xD0
    bool                 unknown_D1;        // +0xD1
    bool                 unknown_D2;        // +0xD2 (true from the constructor)
    bool                 unknown_D3;        // +0xD3 (true)
    bool                 unknown_D4;        // +0xD4 (true)
    unsigned char        _pad_D5[3];        // +0xD5
    TechnoTypeClass*     ConditionObject;   // +0xD8
    TeamTypeClass*       unknown_DC;        // +0xDC the first team (FUN_0041FEE0's argument)
    TeamTypeClass*       unknown_E0;        // +0xE0
    AITriggerCondition   Condition;         // +0xE4
    int                  Successes;         // +0x104
    int                  Attempts;          // +0x108
    int                  unknown_10C;       // +0x10C
};
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_98)      == 0x98);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, IsGlobal)        == 0x9C);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_A0)      == 0xA0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, IsEnabled)       == 0xA4);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_A8)      == 0xA8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_AC)      == 0xAC);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_B0)      == 0xB0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Current)  == 0xB8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Minimum)  == 0xC0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Maximum)  == 0xC8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_D0)      == 0xD0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_D4)      == 0xD4);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, ConditionObject) == 0xD8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_DC)      == 0xDC);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, unknown_E0)      == 0xE0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Condition)       == 0xE4);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Successes)       == 0x104);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Attempts)        == 0x108);
GG_STATIC_ASSERT(sizeof(AITriggerTypeClass)                    == 0x110);

#endif  // GG_MATCH_LAYOUT_AI_TRIGGER_TYPE_CLASS_H
