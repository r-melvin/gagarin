// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x43A350, 0x43A440 and 0x43A9C0 in the user's gamemd.exe v1.001.
//   /Ob2: the scalar deleting destructor 0x43A9C0 expands the destructor.
//
// NeuronClass construction and destruction. Address index: 0x43A350 constructor,
// 0x43A440 destructor, 0x43A9C0 scalar deleting destructor.

#include <new.h>
#include "../_layout/neuron_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/frame_counter.h"
#include "vector_class_operations.h"
#include "vector_add_item_free.h"

// GLOBAL: GAMEMD 0xB0C110 -- the pointer-swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// GLOBAL: GAMEMD 0xB0F670 -- the class-wide list shared by several AbstractClass-derived types.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;

// FUNCTION: GAMEMD 0x43A350
NeuronClass::NeuronClass() : unknown_24(0), unknown_28(0), unknown_2C(0), unknown_30(CurrentFrame)
{
    DynamicVectorAddItemFree(&Array, this);
    DynamicVectorAddItemFree(&DAT_00B0F670, this);
}

// FUNCTION: GAMEMD 0x43A440
NeuronClass::~NeuronClass()
{
    DAT_00B0F670.RemoveItem(this);
    Array.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x43A540
HRESULT __stdcall NeuronClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) NeuronClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_28);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_24);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2C);
    return 0;
}

// FUNCTION: GAMEMD 0x43A9A0
int NeuronClass::vf_11()
{
    return 0x3C;
}

// FUNCTION: GAMEMD 0x43A9B0
int NeuronClass::vf_12()
{
    return 0x38;
}

// SYNTHETIC: GAMEMD 0x43A9C0 -- NeuronClass scalar deleting destructor (slot 8), the destructor expanded in place.
