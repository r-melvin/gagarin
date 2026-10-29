// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x6A4780 (Load) and 0x6A4930 (scalar deleting destructor); the
//   +0x98 member is a DynamicVectorClass<int> (vtable 0x7E4DD8, base 0x7E4DB8) per the Save body.
//   Address index: 0x6A4780 SideClass::Load, 0x6A4930 SideClass deleting destructor.
//   The class is declared locally with its vector member spelled out; the shared layout header
//   keeps the raw words.

#include <new.h>
#include <objidl.h>
#include "../_layout/abstract_type_class.h"
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

class SideClass : public AbstractTypeClass
{
public:
    SideClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual ~SideClass();
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(struct Obj_004A1D30*);
    DynamicVectorClass<int> List; // +0x98
    int unknown_B0;
};
GG_STATIC_ASSERT(offsetof(SideClass, List) == 0x98);

// GLOBAL: GAMEMD 0x8B4120 -- the side registry.
extern DynamicVectorClass<SideClass*> DAT_008B4120;

// FUNCTION: GAMEMD 0x6A4780
// PARTIAL: 88% -- the two inlined DynamicVectorClass<int> constructions store the vptr first; retail
// stores CapacityIncrement, Count, then the vptr (explicit ctor arguments and member-initialiser forms tried).
HRESULT __stdcall SideClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) SideClass(AbstractNoInit());
    new (&List) DynamicVectorClass<int>();
    int count;
    pStm->Read(&count, 4, 0);
    for (int i = 0; i < count; i++) {
        int value;
        pStm->Read(&value, 4, 0);
        List.AddItem(value);
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x6A4930 -- the scalar deleting destructor (??_G) with this body inlined
SideClass::~SideClass()
{
    AnnounceExpiredPointer(1);
    DAT_008B4120.RemoveItem(this);
}
