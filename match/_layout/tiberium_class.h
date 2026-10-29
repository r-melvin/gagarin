// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing Value view extracted unchanged from economy/house_class_tib_methods.h.
// Retail 0x4F9610 and 0x684F3D read +0xB8; no complete object extent claimed.
#ifndef GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#define GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
class TiberiumClass : public AbstractTypeClass
{
public:
    // Stream overrides (vtable 0x7F5728); bodies in core/stream_w3_methods.cpp.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x7220D0
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);     // 7   0x7220A0
    virtual int vf_11();
    virtual int vf_12();
    // UIName (+0x60, read by CellClass::GetUIName 0x484FF0) is the AbstractTypeClass member.
    char           _pad98[0xB8 - 0x98];
    int            Value;         // +0xB8
    char           _padBC[0xC8 - 0xBC];
    int*           unknown_C8;    // +0xC8 one dword per entry
    char           unknown_CC[0xD4 - 0xCC];
    int            unknown_D4;    // +0xD4 entry count
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(TiberiumClass, UIName) == 0x60);
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);
#endif
