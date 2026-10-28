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
#include "../core/vector_class.h"

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

class TiberiumClass : public AbstractTypeClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x7220D0
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);     // 7   0x7220A0
    virtual int vf_11();
    virtual int vf_12();
    char unknown_98[0xC8 - 0x98];
    int* unknown_C8;               // +0xC8 one dword per entry
    char unknown_CC[0xD4 - 0xCC];
    int unknown_D4;                // +0xD4 entry count
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_D4) == 0xD4);

// FUNCTION: GAMEMD 0x7220A0
// The base size plus a count and one dword per entry.
HRESULT __stdcall TiberiumClass::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    HRESULT hr = AbstractClass::GetSizeMax(pcbSize);
    if (hr >= 0) {
        pcbSize->LowPart += unknown_D4 * 4 + 4;
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
        int count = unknown_D4;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++) {
            pStm->Write(&unknown_C8[i], 4, 0);
        }
        return 0;
    }
    return hr;
}

// ---- TubeClass (vtable 0x7F59B0) ------------------------------------------------------------

class TubeClass : public AbstractClass
{
public:
    // The stream loader's in-place construction: the base only (retail 0x410170).
    struct LoadTag {};
    TubeClass(LoadTag) {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);                     // 5   0x7281A0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
};

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

// ---- WarheadTypeClass (vtable 0x7F6B30) -----------------------------------------------------

class WarheadTypeClass : public AbstractTypeClass
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
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_108) == 0x108);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_190) == 0x190);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_19C) == 0x19C);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_1AC) == 0x1AC);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_1B8) == 0x1B8);

// FUNCTION: GAMEMD 0x75E2C0
// Writes the base state, then three counted lists of dwords.
HRESULT __stdcall WarheadTypeClass::Save(IStream* pStm, BOOL fClearDirty)
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

class WeaponTypeClass : public AbstractTypeClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x772EB0
    virtual int vf_11();
    virtual int vf_12();
    char unknown_98[0xC0 - 0x98];
    int* unknown_C0;               // +0xC0 one dword per entry
    char unknown_C4[0xCC - 0xC4];
    int unknown_CC;                // +0xCC entry count
    char unknown_D0[0xDC - 0xD0];
    int* unknown_DC;               // +0xDC
    char unknown_E0[0xE8 - 0xE0];
    int unknown_E8;                // +0xE8
    char unknown_EC[0xF8 - 0xEC];
    int* unknown_F8;               // +0xF8
    char unknown_FC[0x104 - 0xFC];
    int unknown_104;               // +0x104
};
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_C0) == 0xC0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_CC) == 0xCC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_104) == 0x104);

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
        count = unknown_CC;
        pStm->Write(&count, 4, 0);
        for (int j = 0; j < count; j++) {
            pStm->Write(&unknown_C0[j], 4, 0);
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
