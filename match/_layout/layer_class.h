// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI ".?AVLayerClass@@" on the 10-slot table 0x7E6060: slots 0-6 are the
//   DynamicVectorClass<ObjectClass*> spine (slot 0 the LayerClass scalar
//   deleting destructor 0x4AEB50), slots 7-9 are LayerClass's own. LogicClass
//   (0x7E18FC, 11 slots) overrides slot 7 and adds slot 10.
#ifndef GG_MATCH_LAYOUT_LAYER_CLASS_H
#define GG_MATCH_LAYOUT_LAYER_CLASS_H

#include "../core/vector_class.h"

class ObjectClass;

// VTABLE: GAMEMD 0x7E6060
class LayerClass : public DynamicVectorClass<ObjectClass*>
{
public:
    // FUNCTION: GAMEMD 0x5519B0 (declaration; slot 7)
    virtual bool AddObject(ObjectClass* pObject, bool sorted);
    virtual void vf_8();    // 8  0x40CC00: calls Clear (slot 3)
    virtual void vf_9();    // 9  0x40CC10: bare RET
};

// LogicClass : LayerClass, RTTI ".?AVLogicClass@@" on the 11-slot table
// 0x7E18FC; it overrides slot 7 and adds slot 10 (not modelled here).
// VTABLE: GAMEMD 0x7E18FC
class LogicClass : public LayerClass
{
public:
    // FUNCTION: GAMEMD 0x55BAA0 (declaration; slot 7)
    virtual bool AddObject(ObjectClass* pObject, bool sorted);
};

// GLOBAL: GAMEMD 0x87F778 -- the one LogicClass object (retail loads its
// address as an immediate).
extern LogicClass DAT_0087F778;

#endif  // GG_MATCH_LAYOUT_LAYER_CLASS_H
