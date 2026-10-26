// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TagClass ctor FUN_0x006E4DE0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0).
//   Size 0x38 is supported by allocation-size and constructor evidence;
//   the layout is pinned below with a sizeof assertion.
//   RTTI: primary vtable 0x7F44E0 -> COL 0x80BBA0 -> TypeDescriptor
//   0x8249E8, whose name at 0x8249F0 is ".?AVTagClass@@".
//   Cross-read against YRpp: 6 named members claimed, 6 confirmed.
//   No disagreement found.
//
// TagClass — a live map tag binding triggers to objects. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_TAG_CLASS_H
#define GG_MATCH_LAYOUT_TAG_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "foot_class.h"   // CellStruct

class TagTypeClass;
class TriggerClass;
class ObjectClass;
struct Obj_004A1D30;

// Retail TypeDescriptor 0x8249E8 names ".?AVTagClass@@".
class TagClass : public AbstractClass
{
public:
    // Overrides of the slots AbstractClass leaves pure (primary table
    // slots 3, 5, 6, 11, 12; declarations only, bodies not modelled here).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6E56A0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6E5730
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6E57A0
    virtual int vf_11();                                                  // 11  0x6E58A0
    virtual int vf_12();                                                  // 12  0x6E5890
    virtual void vf_10(void* target, bool removed);                       // 10  0x6E5610
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6E56E0
    // FUNCTION: GAMEMD 0x6E4DE0 (declaration; constructor)
    TagClass(TagTypeClass* type);
    // The stream loader's in-place construction: only the four tables.
    TagClass(const AbstractNoInit& noInit) : AbstractClass(noInit) {}
    // FUNCTION: GAMEMD 0x6E4F60 (declaration; destructor)
    ~TagClass();
    // FUNCTION: GAMEMD 0x6E5230
    void Destroy();
    // FUNCTION: GAMEMD 0x6E52A0
    static TagClass* GetInstance(TagTypeClass* type);
    // FUNCTION: GAMEMD 0x6E5290
    bool FUN_006E5290() const;
    // FUNCTION: GAMEMD 0x6E52F0
    CellStruct* FUN_006E52F0(CellStruct* out) const;
    // FUNCTION: GAMEMD 0x6E5300
    bool HasCrossesVerticalLineEvent() const;
    // FUNCTION: GAMEMD 0x6E5320
    bool HasCrossesHorizontalLineEvent() const;
    // FUNCTION: GAMEMD 0x6E5340
    bool HasZoneEntryByEvent() const;
    // FUNCTION: GAMEMD 0x6E5360
    int FUN_006E5360() const;
    // FUNCTION: GAMEMD 0x6E5380
    bool ContainsTrigger(TriggerClass* trigger) const;
    // FUNCTION: GAMEMD 0x6E53A0
    bool FUN_006E53A0(int event, ObjectClass* object, CellStruct cell, bool flag, int arg);
    // FUNCTION: GAMEMD 0x6E5560
    void FUN_006E5560(CellStruct value);
    // FUNCTION: GAMEMD 0x6E5570
    static void __stdcall DeleteAll();
    // FUNCTION: GAMEMD 0x6E55A0
    void FUN_006E55A0(int index);
    // FUNCTION: GAMEMD 0x6E57C0
    bool ShouldReplace() const;
    // FUNCTION: GAMEMD 0x6E57F0
    static void NotifyGlobalChanged(int idxGlobal);
    // FUNCTION: GAMEMD 0x6E5820
    static void NotifyLocalChanged(int idxLocal);
    // FUNCTION: GAMEMD 0x6E5850
    bool IsOnlyInstanceOfType() const;

    // FUNCTION: GAMEMD 0x6E58B0
    void* FUN_006E58B0(unsigned int flags);

    TagTypeClass* Type;            // +0x24 ctor = arg1 @0x006E4DF0
    TriggerClass* FirstTrigger;    // +0x28 ctor @0x006E4DF3
    int           InstanceCount;   // +0x2C ctor @0x006E4DF6
    CellStruct    DefaultCoords;   // +0x30 ctor MOV [ESI+0x30],EAX(=[0x00B0E700]) @0x006E4DFE
    bool          Destroyed;       // +0x34 ctor @0x006E4E01
    bool          IsExecuting;     // +0x35 ctor @0x006E4E04
    unsigned char unknown_36[2];   // +0x36 unclassified tail bytes; closes the object at 0x38
    // GLOBAL: GAMEMD 0xB0E720 -- loader-zero registry storage.
    static DynamicVectorClassLayout Array;
};

GG_STATIC_ASSERT(offsetof(TagClass, Type)          == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger)  == 0x28);
GG_STATIC_ASSERT(offsetof(TagClass, InstanceCount) == 0x2C);
GG_STATIC_ASSERT(offsetof(TagClass, DefaultCoords) == 0x30);
// Setter 0x6E5560 stores its packed coordinate argument as one DWORD.
GG_STATIC_ASSERT(sizeof(((TagClass*)0)->DefaultCoords) == 4);
GG_STATIC_ASSERT(offsetof(TagClass, Destroyed)     == 0x34);
GG_STATIC_ASSERT(offsetof(TagClass, IsExecuting)   == 0x35);
GG_STATIC_ASSERT(sizeof(TagClass)                  == 0x38);

// VTABLE: GAMEMD 0x007F44E0  TagClass
// VTABLE: GAMEMD 0x007F44C4  TagClass::(+0x04)
// VTABLE: GAMEMD 0x007F44BC  TagClass::(+0x08)
// VTABLE: GAMEMD 0x007F44B4  TagClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_TAG_CLASS_H
