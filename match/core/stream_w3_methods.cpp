// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Stream save/load virtuals (primary slots 5-7) of several AbstractClass-derived
//   classes, read off retail gamemd.exe v1.001. Each class is a view that carries only
//   the members these bodies touch (offsets from the retail disassembly) and the
//   overrides that make it a concrete type. Functions are in ascending retail address order.

#include <new.h>
#include "../_layout/abstract_class.h"
#include "../_layout/abstract_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/tiberium_class.h"
#include "../_layout/tube_class.h"
#include "../core/vector_class.h"
#include "../combat/weapon_type_class.h"

// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// ---- SlaveManagerClass (vtable 0x7F31C8) ----------------------------------------------------

class SlaveManagerClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x6B1300
    virtual int vf_11();
    virtual int vf_12();
    char unknown_24[0x38 - 0x24];
    DynamicVectorClass<void*> SlaveNodes;   // +0x38 pointers to 0x14-byte records
};
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes) == 0x38);

// FUNCTION: GAMEMD 0x6B1300
// Writes the base state, the node count, then every node record.
HRESULT __stdcall SlaveManagerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = SlaveNodes.Count;
        hr = pStm->Write(&count, 4, 0);
        if (hr >= 0) {
            for (int i = 0; i < count; i++) {
                hr = pStm->Write(SlaveNodes.Items[i], 0x14, 0);
                if (hr < 0) {
                    break;
                }
            }
        }
    }
    return hr;
}

// ---- SpawnManagerClass (vtable 0x7F3650) ----------------------------------------------------

class SpawnManagerClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x6B80B0
    virtual int vf_11();
    virtual int vf_12();
    char unknown_24[0x38 - 0x24];
    DynamicVectorClass<void*> SpawnNodes;   // +0x38 pointers to 0x18-byte records
};
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnNodes) == 0x38);

// FUNCTION: GAMEMD 0x6B80B0
// Writes the base state, the node count, then every node record.
HRESULT __stdcall SpawnManagerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = SpawnNodes.Count;
        hr = pStm->Write(&count, 4, 0);
        if (hr >= 0) {
            for (int i = 0; i < count; i++) {
                hr = pStm->Write(SpawnNodes.Items[i], 0x18, 0);
                if (hr < 0) {
                    break;
                }
            }
        }
    }
    return hr;
}

// ---- TiberiumClass (vtable 0x7F5728) --------------------------------------------------------


// FUNCTION: GAMEMD 0x7220A0
// The base size plus the debris list's count and one dword per entry.
HRESULT __stdcall TiberiumClass::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    HRESULT hr = AbstractClass::GetSizeMax(pcbSize);
    if (hr >= 0) {
        pcbSize->LowPart += Debris.Count * 4 + 4;
        return 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x7220D0
// Writes the base state, the entry count, then each entry dword.
HRESULT __stdcall TiberiumClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = Debris.Count;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++) {
            pStm->Write(&Debris.Items[i], 4, 0);
        }
        return 0;
    }
    return hr;
}

// ---- TubeClass (vtable 0x7F59B0) ------------------------------------------------------------


// FUNCTION: GAMEMD 0x7281A0
// Re-establish the object after a stream load.
HRESULT __stdcall TubeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TubeClass(LoadTag());
    return 0;
}

// ---- WarheadTypeClass (vtable 0x7F6B30), as the view WarheadStreamView_0075E2C0 -----------------------------------------------------

class WarheadStreamView_0075E2C0 : public AbstractTypeClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x75E2C0
    virtual int vf_11();
    virtual int vf_12();
    char unknown_98[0x108 - 0x98];
    int* unknown_108;              // +0x108 one dword per entry
    char unknown_10C[0x114 - 0x10C];
    int unknown_114;               // +0x114 entry count
    char unknown_118[0x190 - 0x118];
    int* unknown_190;              // +0x190
    char unknown_194[0x19C - 0x194];
    int unknown_19C;               // +0x19C
    char unknown_1A0[0x1AC - 0x1A0];
    int* unknown_1AC;              // +0x1AC
    char unknown_1B0[0x1B8 - 0x1B0];
    int unknown_1B8;               // +0x1B8
};
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_108) == 0x108);
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_190) == 0x190);
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_19C) == 0x19C);
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_1AC) == 0x1AC);
GG_STATIC_ASSERT(offsetof(WarheadStreamView_0075E2C0, unknown_1B8) == 0x1B8);

// FUNCTION: GAMEMD 0x75E2C0
// Writes the base state, then three counted lists of dwords.
HRESULT __stdcall WarheadStreamView_0075E2C0::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = unknown_114;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++) {
            pStm->Write(&unknown_108[i], 4, 0);
        }
        count = unknown_19C;
        pStm->Write(&count, 4, 0);
        for (int j = 0; j < count; j++) {
            pStm->Write(&unknown_190[j], 4, 0);
        }
        count = unknown_1B8;
        pStm->Write(&count, 4, 0);
        for (int k = 0; k < count; k++) {
            pStm->Write(&unknown_1AC[k], 4, 0);
        }
        return 0;
    }
    return hr;
}

// ---- WeaponTypeClass (vtable 0x7F73B8) ------------------------------------------------------

// FUNCTION: GAMEMD 0x772EB0
// Writes the base state, then three counted lists of dwords.
HRESULT __stdcall WeaponTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = unknown_104;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++) {
            pStm->Write(&unknown_F8[i], 4, 0);
        }
        count = Reports.Count;
        pStm->Write(&count, 4, 0);
        for (int j = 0; j < count; j++) {
            pStm->Write(&Reports.Items[j], 4, 0);
        }
        count = unknown_E8;
        pStm->Write(&count, 4, 0);
        for (int k = 0; k < count; k++) {
            pStm->Write(&unknown_DC[k], 4, 0);
        }
        return 0;
    }
    return hr;
}
