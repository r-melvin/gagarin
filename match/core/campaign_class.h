// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 46CB60/46CE10 construct the 0x3A0-byte object. RTTI-backed tables
// 7E4A28/7E4A0C/7E4A04/7E49FC retain AbstractTypeClass's COM subobjects.
#ifndef GG_MATCH_CORE_CAMPAIGN_CLASS_H
#define GG_MATCH_CORE_CAMPAIGN_CLASS_H
#include "../_layout/abstract_type_class.h"
#include "vector_class.h"
// VTABLE: GAMEMD 0x7E4A28
// VTABLE: GAMEMD 0x7E4A0C
// VTABLE: GAMEMD 0x7E4A04
// VTABLE: GAMEMD 0x7E49FC
class CampaignClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x46CB60
    CampaignClass(const char* name) throw();
    CampaignClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x46CC10
    virtual ~CampaignClass();
    // FUNCTION: GAMEMD 0x46CC90
    static int FindIndex(const char* name);
    // FUNCTION: GAMEMD 0x46CCD0
    virtual bool vf_25(CCINIClass* ini);
    // FUNCTION: GAMEMD 0x46CE10
    static void CreateFromINIList(CCINIClass* ini);
    // FUNCTION: GAMEMD 0x46CF80
    virtual HRESULT __stdcall GetClassID(CLSID* out);
    // FUNCTION: GAMEMD 0x46CFC0
    virtual void vf_13(Obj_004A1D30* crc);
    // FUNCTION: GAMEMD 0x46D000
    virtual HRESULT __stdcall Load(IStream* stream);
    // FUNCTION: GAMEMD 0x46D050
    virtual HRESULT __stdcall Save(IStream* stream, BOOL clearDirty);
    // FUNCTION: GAMEMD 0x46D070
    virtual int vf_12();
    // FUNCTION: GAMEMD 0x46D080
    virtual int vf_11();
    int idxCD;
    char Scenario[512];
    int FinalMovie;
    wchar_t Description[128];
};
GG_STATIC_ASSERT(offsetof(CampaignClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(CampaignClass, idxCD) == 0x98);
GG_STATIC_ASSERT(offsetof(CampaignClass, Scenario) == 0x9C);
GG_STATIC_ASSERT(offsetof(CampaignClass, FinalMovie) == 0x29C);
GG_STATIC_ASSERT(offsetof(CampaignClass, Description) == 0x2A0);
GG_STATIC_ASSERT(sizeof(((CampaignClass*)0)->idxCD) == 4);
GG_STATIC_ASSERT(sizeof(((CampaignClass*)0)->Scenario) == 512);
GG_STATIC_ASSERT(sizeof(((CampaignClass*)0)->FinalMovie) == 4);
GG_STATIC_ASSERT(sizeof(((CampaignClass*)0)->Description) == 256);
GG_STATIC_ASSERT(sizeof(CampaignClass) == 0x3A0);
// Gagarin diagnostic view of the native 27-slot primary table.
struct GgCampaignPrimarySlots
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
    void* slot_06;
    void* slot_07;
    void* slot_08;
    void* slot_09;
    void* slot_10;
    void* slot_11;
    void* slot_12;
    void* slot_13;
    void* slot_14;
    void* slot_15;
    void* slot_16;
    void* slot_17;
    void* slot_18;
    void* slot_19;
    void* slot_20;
    void* slot_21;
    void* slot_22;
    void* slot_23;
    void* slot_24;
    void* slot_25;
    void* slot_26;
};
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_00) == 0x0);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_01) == 0x4);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_02) == 0x8);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_03) == 0xC);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_10) == 0x28);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_11) == 0x2C);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_12) == 0x30);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_13) == 0x34);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_14) == 0x38);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_15) == 0x3C);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_16) == 0x40);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_17) == 0x44);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_18) == 0x48);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_19) == 0x4C);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_20) == 0x50);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_21) == 0x54);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_22) == 0x58);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_23) == 0x5C);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_24) == 0x60);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_25) == 0x64);
GG_STATIC_ASSERT(offsetof(GgCampaignPrimarySlots, slot_26) == 0x68);
GG_STATIC_ASSERT(sizeof(GgCampaignPrimarySlots) == 0x6C);
// GLOBAL: GAMEMD 0xA83CF8
extern DynamicVectorClass<CampaignClass*> CampaignArray;
// Native campaign append expansion; declared before other vector instantiations.
template<> inline bool DynamicVectorClass<CampaignClass*>::AddItem(CampaignClass* const& item);
#endif
