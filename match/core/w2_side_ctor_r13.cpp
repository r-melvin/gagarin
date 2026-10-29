// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x6A4550 (SideClass constructor from an id): AbstractTypeClass constructor,
//   the +0x98 list built as a TypeList<int> (vtable 0x7E4DD8), the unique id assignment through the
//   IRTTITypeInfo side, and the append to the side registry at 0x8B4120.
//   Address index: 0x6A4550 SideClass::SideClass(const char*).
//   The class is declared locally with its list member spelled out; the shared layout header keeps raw words.

#include <objidl.h>
#include "../_layout/abstract_type_class.h"
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"
#include "type_list.h"

class SideClass : public AbstractTypeClass
{
public:
    SideClass(const char* id);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual ~SideClass();
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(struct Obj_004A1D30*);
    TypeList<int> List; // +0x98
    int unknown_B0;
};
GG_STATIC_ASSERT(offsetof(SideClass, List) == 0x98);

// GLOBAL: GAMEMD 0x8B4120 -- the side registry.
extern DynamicVectorClass<SideClass*> DAT_008B4120;

// FUNCTION: GAMEMD 0x6A4550
// Constructs the side from its id: base constructor, empty list, unique id assignment, registration.
SideClass::SideClass(const char* id) : AbstractTypeClass(id)
{
    vf_rtti_5();
    DynamicVectorClass<SideClass*>& v = DAT_008B4120;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = this;
}
