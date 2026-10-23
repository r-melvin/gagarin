// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//   /Ob2: the scalar deleting destructor 0x410C30 carries this destructor
//   inline, while 0x4109C0 also exists out of line for the derived
//   destructors (0x726E00, 0x6E5CA0, ...). Both call ~AbstractClass 0x4101F0.
// AbstractTypeClass destructor: unregister from the type registry at 0xA8E968
// (RTTI DynamicVectorClass<AbstractTypeClass*> per the existing view), whose
// slot +0x10 finds the item's index.
#include "../_layout/abstract_type_class.h"

// The registry, seen through the slot it calls (an ABI view, not the template).
class AbstractTypeRegistryView
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0C();
    virtual int FindItemIndex(AbstractTypeClass* const& item) const;
    AbstractTypeClass** Items;   // +0x04
    int Capacity;                // +0x08
    int unknown_0C;              // +0x0C
    int Count;                   // +0x10
};
GG_STATIC_ASSERT(offsetof(AbstractTypeRegistryView, Count) == 0x10);
// GLOBAL: GAMEMD 0xA8E968
extern AbstractTypeRegistryView DAT_00A8E968;

// FUNCTION: GAMEMD 0x4109C0
AbstractTypeClass::~AbstractTypeClass()
{
    AbstractTypeRegistryView* registry = &DAT_00A8E968;
    int index = registry->FindItemIndex(this);
    if (index != -1 && index < registry->Count) {
        --registry->Count;
        for (int i = index; i < registry->Count; ++i)
            registry->Items[i] = registry->Items[i + 1];
    }
}

// SYNTHETIC: GAMEMD 0x410C30 -- compiler-generated scalar deleting destructor.
