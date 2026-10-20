// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm at 0x551A30 /
//   0x55BAE0). Member offsets and the two indirect vtable dispatches are
//   reconfirmed numerically from the disassembly; signatures cross-checked
//   against YRpp MapClass.h (consult-only, no LICENSE).
//
// LayerClass : DynamicVectorClassLayout   (the per-layer object list)
// LogicClass : LayerClass                          (the global logic layer)
//   Sort()         @0x551A30  one bubble pass, ascending by element GetYSort()
//   RemoveObject() @0x55BAE0  drop pObject from the layer, compacting in place
#ifndef GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"   // DynamicVectorClassLayout (Items@0x4, Count@0x10)
#include "../_layout/object_class.h"   // ObjectClass (IsInLogic@0x98)

GG_STATIC_ASSERT(offsetof(ObjectClass, IsInLogic) == 0x98);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Count) == 0x10);

// LayerClass adds the layer-specific virtuals (AddObject, RemoveAll, ...) and a
// non-virtual Sort. The base vtable pointer is modelled as plain data by the
// vector spine, so a virtual dispatch on `this` is issued via the minimal
// abstract interface below (real-virtual => exact __thiscall with a stack arg).
struct LayerClass : DynamicVectorClassLayout
{
    void Sort();
};

struct LogicClass : LayerClass
{
    void RemoveObject(ObjectClass* pObject);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H
