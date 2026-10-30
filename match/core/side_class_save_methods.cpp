// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x6A4710 and 0x6A48A0.
//
// SideClass bodies that serialise the +0x9C list (count at +0xA8).
// Address index: 0x6A4710 vf_13, 0x6A48A0 Save.

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/obj_004a1d30.h"
#include "vector_class_operations.h"

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

// FUNCTION: GAMEMD 0x6A4710
void SideClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_98.Count);
}

// FUNCTION: GAMEMD 0x6A48A0
HRESULT __stdcall SideClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        int count = unknown_98.Count;
        pStm->Write(&count, 4, 0);
        for (int i = 0; i < count; i++)
            pStm->Write(&unknown_98.Items[i], 4, 0);
        hr = 0;
    }
    return hr;
}
