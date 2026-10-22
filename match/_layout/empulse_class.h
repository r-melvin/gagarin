// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: primary vtable 0x7E87A8, TypeDescriptor ".?AVEMPulseClass@@" at
//   0x8208D0 (name at 0x8208D8). Size 0x34 from slot 12 (0x4C5AA0 returns
//   0x34); the fields from the constructor 0x4C52B0 (four argument stores and
//   the current frame) and the default constructor 0x4C5370.
#ifndef GG_MATCH_LAYOUT_EMPULSE_CLASS_H
#define GG_MATCH_LAYOUT_EMPULSE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "foot_class.h"   // CellStruct
#include "../core/vector_class.h"

class TechnoClass;
struct Obj_004A1D30;

// VTABLE: GAMEMD 0x7E87A8 (IPersistStream side)
// VTABLE: GAMEMD 0x7E878C (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E8784 (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E877C (INoticeSource side, +0x0C)
class EMPulseClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x4C52B0 (declaration)
    EMPulseClass(CellStruct cell, int radius, int duration, TechnoClass* source);
    // FUNCTION: GAMEMD 0x4C5370 (declaration)
    EMPulseClass();
    // FUNCTION: GAMEMD 0x4C53B0 (declaration; no-initialisation constructor)
    EMPulseClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x4C53E0 (declaration; destructor; slot 8 = 0x4C5AC0)
    virtual ~EMPulseClass();
    // FUNCTION: GAMEMD 0x4C54A0 (declaration)
    static void __stdcall FUN_004C54A0();
    // FUNCTION: GAMEMD 0x4C54E0 (decl; reloc) -- applies the pulse; RET 4.
    void FUN_004C54E0(TechnoClass* source);
    // FUNCTION: GAMEMD 0x4C58C0 (declaration)
    void FUN_004C58C0();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x4C5A30
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x4C5A80
    virtual int vf_11();                                                  // 11  0x4C5AB0
    virtual int vf_12();                                                  // 12  0x4C5AA0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x4C59A0

    CellStruct unknown_24;   // +0x24 the centre cell
    int        unknown_28;   // +0x28 the radius in cells
    int        unknown_2C;   // +0x2C the frame the pulse started
    int        unknown_30;   // +0x30 the duration in frames

    // GLOBAL: GAMEMD 0x8A3870
    static DynamicVectorClass<EMPulseClass*> Array;
};
GG_STATIC_ASSERT(offsetof(EMPulseClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(EMPulseClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(EMPulseClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(EMPulseClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(EMPulseClass) == 0x34);

#endif  // GG_MATCH_LAYOUT_EMPULSE_CLASS_H
