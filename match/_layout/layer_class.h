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
class AbstractClass;

// VTABLE: GAMEMD 0x7E6060
class LayerClass : public DynamicVectorClass<ObjectClass*>
{
public:
    // FUNCTION: GAMEMD 0x5519B0 (declaration; slot 7)
    virtual bool AddObject(ObjectClass* pObject, bool sorted);
    virtual void vf_8();    // 8  0x40CC00: calls Clear (slot 3)
    virtual void vf_9();    // 9  0x40CC10: bare RET
    // FUNCTION: GAMEMD 0x551A90 (non-virtual; sorted insert, full-width result)
    int SortedAdd(ObjectClass* pObject);
    // FUNCTION: GAMEMD 0x551A30
    void Sort();
    // FUNCTION: GAMEMD 0x551B90 (declaration; reads the layer from a stream)
    long Load(struct IStream* stream);
    // FUNCTION: GAMEMD 0x551B20 (declaration; writes the layer to a stream)
    long Save(struct IStream* stream);
};

// GLOBAL: GAMEMD 0x8A0360 -- draw-layer array; native5519B0 callers use24-byte stride.
// 55DBC3 passes its third element (8A0390) to551A30;6D9920 reads that element.
extern LayerClass DisplayLayers[];
GG_STATIC_ASSERT(sizeof(LayerClass) == 0x18);
GG_STATIC_ASSERT(offsetof(LayerClass, Items) == 4);
GG_STATIC_ASSERT(offsetof(LayerClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(LayerClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(LayerClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LayerClass, CapacityIncrement) == 0x14);

// LogicClass : LayerClass, RTTI ".?AVLogicClass@@" on the 11-slot table
// 0x7E18FC; it overrides slot 7 and adds PointerGotInvalid at slot 10.
// Native table slot 10 points to 0x55B880 (RET 8).
// VTABLE: GAMEMD 0x7E18FC
class LogicClass : public LayerClass
{
public:
    // FUNCTION: GAMEMD 0x55BAA0 (declaration; slot 7)
    virtual bool AddObject(ObjectClass* pObject, bool sorted);
    // FUNCTION: GAMEMD 0x55B880 (declaration; slot 10)
    virtual void PointerGotInvalid(AbstractClass* invalid, bool removed);
    // FUNCTION: GAMEMD 0x55BAE0
    void RemoveObject(ObjectClass* pObject);
};
GG_STATIC_ASSERT(sizeof(LogicClass) == 0x18);

// GLOBAL: GAMEMD 0x87F778 -- the one LogicClass object (retail loads its
// address as an immediate).
extern LogicClass DAT_0087F778;

// Slot positions read from pinned retail tables 0x7E6060 and 0x7E18FC.
// This plain record asserts table layout; actual emitted targets are verified
// separately against those tables.
struct LayerClassVtableLayoutEvidence {
    void* Destructor; void* Equals; void* SetCapacity; void* Clear;
    void* FindItemIndex; void* Slot5; void* Slot6; void* AddObject;
    void* Slot8; void* Slot9;
};
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Destructor) == 0x00);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Equals) == 0x04);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, SetCapacity) == 0x08);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Clear) == 0x0C);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, FindItemIndex) == 0x10);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Slot5) == 0x14);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Slot6) == 0x18);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, AddObject) == 0x1C);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Slot8) == 0x20);
GG_STATIC_ASSERT(offsetof(LayerClassVtableLayoutEvidence, Slot9) == 0x24);
GG_STATIC_ASSERT(sizeof(LayerClassVtableLayoutEvidence) == 0x28);
struct LogicClassVtableLayoutEvidence {
    LayerClassVtableLayoutEvidence LayerSlots;
    void* PointerGotInvalid;
};
GG_STATIC_ASSERT(offsetof(LogicClassVtableLayoutEvidence, LayerSlots) == 0);
GG_STATIC_ASSERT(offsetof(LogicClassVtableLayoutEvidence, PointerGotInvalid) == 0x28);
GG_STATIC_ASSERT(sizeof(LogicClassVtableLayoutEvidence) == 0x2C);

#endif  // GG_MATCH_LAYOUT_LAYER_CLASS_H
