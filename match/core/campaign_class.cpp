// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native campaign construction, INI, checksum and persistence bodies.
#include "campaign_class.h"
#include "vector_class_operations.h"
#include "../platform/ccini_class_methods.h"
#include "../_layout/obj_004a1d30.h"
#include <string.h>
#include <wchar.h>
#include <new.h>
// GLOBAL: GAMEMD 0x7E9900
extern const CLSID DAT_007E9900;
// GAMEMD 0x735060 (declaration; UTF16 conversion; body in core/w3r2_leaf_methods_d.cpp)
void __fastcall FUN_00735060(unsigned short*, const char*, int);

// Campaign's native append expansion preserves the growth increment as the
// accumulator; the generic vector implementation spells the same sum oppositely.
template<> inline bool DynamicVectorClass<CampaignClass*>::AddItem(CampaignClass* const& item)
{
    if (Count >= this->Capacity) {
        if (this->IsAllocated || !this->Capacity) {
            int grow = CapacityIncrement;
            if (grow <= 0) return false;
            grow += this->Capacity;
            if (!this->SetCapacity(grow, 0)) return false;
        } else return false;
    }
    int index = Count++;
    this->Items[index] = item;
    return true;
}

// Partial: best 84.8%, retained form 76.1%; standalone vptr/member stores
// differ in scheduling. The inlined factory is exact; further matching held.
// FUNCTION: GAMEMD 0x46CB60
CampaignClass::CampaignClass(const char* name) throw()
    : AbstractTypeClass(name), idxCD(-1), FinalMovie(-1)
{
    CampaignArray.AddItem(this);
    Scenario[0] = 0;
    wcscpy(Description, L"");
}

// FUNCTION: GAMEMD 0x46CC10
CampaignClass::~CampaignClass()
{
    AnnounceExpiredPointer(1);
    CampaignArray.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x46CC90
int CampaignClass::FindIndex(const char* name)
{
    for (int i = 0; i < CampaignArray.Count; ++i) {
        CampaignClass* entry = CampaignArray.Items[i];
        if (_strcmpi(entry->ID, name) == 0) return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x46CCD0
bool CampaignClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini)) {
        idxCD = ini->FUN_005276D0(ID, "CD", idxCD);
        FinalMovie = ini->FUN_004757D0(ID, "FinalMovie", FinalMovie);
        ini->FUN_00528A10(ID, "Scenario", Scenario, Scenario, 512);
        _strupr(Scenario);
        if (!ini->FUN_005295F0(ID, "DebugOnly", false)) {
            ini->FUN_00529160(ID, "Description", Description, 128);
        } else {
            char buffer[1024];
            ini->FUN_00528A10(ID, "Description", 0, buffer, 1024);
            strcat(buffer, " - for debug/testing");
            FUN_00735060(reinterpret_cast<unsigned short*>(Description), buffer, -1);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x46CE10
void CampaignClass::CreateFromINIList(CCINIClass* ini)
{
    int count = ini->GetKeyCount("Battles");
    for (int i = 0; i < count; ++i) {
        char buffer[32];
        ini->FUN_00528A10("Battles", ini->GetKeyName("Battles", i), "", buffer, sizeof(buffer));
        int index = FindIndex(buffer);
        CampaignClass* campaign;
        if (index == -1) campaign = new CampaignClass(buffer);
        else campaign = CampaignArray.Items[index];
        campaign->vf_25(ini);
    }
}

// FUNCTION: GAMEMD 0x46CF80
HRESULT __stdcall CampaignClass::GetClassID(CLSID* out)
{
    if (!out) return E_POINTER;
    *out = DAT_007E9900;
    return S_OK;
}

// FUNCTION: GAMEMD 0x46CFC0
void CampaignClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(idxCD);
    crc->FUN_004A1DB0(Scenario);
    crc->FUN_004A1D50(FinalMovie);
}

// FUNCTION: GAMEMD 0x46D000
HRESULT __stdcall CampaignClass::Load(IStream* stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (result >= 0) {
        new(this) CampaignClass(AbstractNoInit());
        result = S_OK;
    }
    return result;
}

// FUNCTION: GAMEMD 0x46D050
HRESULT __stdcall CampaignClass::Save(IStream* stream, BOOL clearDirty)
{
    HRESULT result = AbstractClass::Save(stream, clearDirty);
    if (result >= 0) result = S_OK;
    return result;
}

// FUNCTION: GAMEMD 0x46D070
int CampaignClass::vf_12() { return sizeof(CampaignClass); }
// FUNCTION: GAMEMD 0x46D080
int CampaignClass::vf_11() { return 0xA; }
// SYNTHETIC: GAMEMD 0x46D090
// CampaignClass scalar deleting destructor.
