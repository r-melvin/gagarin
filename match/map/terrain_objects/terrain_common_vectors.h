// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The seven-slot VectorClass / DynamicVectorClass shape every pointer array of the terrain-objects
//   module uses (OverlayClass::Array 0xA8EC50, OverlayTypeClass::Array 0xA83D80, SmudgeClass::Array
//   0xA8B1E0, SmudgeTypeClass::Array 0xA8EC18, TerrainTypeClass::Array 0xA8E318, TerrainClass::Array
//   0xA8E988). Layout and slot order are those of match/core/vector_class.h; the inlined AddItem /
//   RemoveItem reach SetCapacity (slot 2, [vptr+8]) and FindItemIndex (slot 4, [vptr+0x10]) through the
//   same vtable slots as retail.
//
// The arrays are the canonical match/core VectorClass<T> / DynamicVectorClass<T> (retail's RTTI names
// them VectorClass<OverlayClass*>, DynamicVectorClass<SmudgeClass*>, ...). The retail compiler expanded
// AddItem (and the index lookup) in several different shapes in different bodies, and VC6 compiles each
// source shape to different instructions (register choice and load order of Count / Capacity), so the
// shapes are NOT interchangeable. They are kept as distinctly named inline helpers, one per proven shape:
//   AddItem             one short-circuit condition, Capacity loaded into a local first (Overlay /
//                       Smudge / Terrain object constructors, Smudge type constructor). The Terrain
//                       object constructors' variant that stores through an index local compiles to
//                       the same bytes, so they use this member too.
//   AddItemEarlyOut     early returns, Count compared with Capacity before the local is read, element
//                       stored through an index local (OverlayTypeClass constructor)
//   AddItemSlotEarlyOut early returns, element address formed first (`T* slot = &Items[Count++]`;
//                       TerrainTypeClass constructor)
// The two early-out shapes were tried against each other's constructors and both regress, so they stay
// separate. FindIndex (a plain loop with a single `return -1` exit) serves every family; the variant
// that leaves the loop through a label compiles to the same bytes.
// These stay free helpers rather than canonical members: the canonical DynamicVectorClass::AddItem
// (vector_class_mutation.h) regresses the Overlay / Smudge / Terrain / IsometricTile constructors (97-99%),
// the early-out shapes have no canonical member, and the canonical FindItemIndex is the virtual slot, not
// the inline lookup. RemoveItem is the canonical member (vector_class_operations.h): identical bytes.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H

#include "terrain_common_types.h"
#include "../../core/vector_class.h"
#include "../../core/vector_class_operations.h"

// The helpers take the vector and reach SetCapacity through its vtable slot 2, exactly as the inlined
// member bodies did.
// DynamicVectorClass::AddItem, inlined by the original.
template <class T> inline bool MapObjAddItem(DynamicVectorClass<T>* v, const T& item)
{
    int cap = v->Capacity;
    if (v->Count < cap
        || ((v->IsAllocated || cap == 0)
            && v->CapacityIncrement > 0
            && v->SetCapacity(v->CapacityIncrement + cap, 0))) {
        (*v)[v->Count++] = item;
        return true;
    }
    return false;
}

// The same operation in the shape the OverlayTypeClass constructor's expansion has: early returns,
// Count loaded before Capacity.
template <class T> inline bool MapObjAddItemEarlyOut(DynamicVectorClass<T>* v, const T& item)
{
    if (v->Count >= v->Capacity) {
        int cap = v->Capacity;
        if (!v->IsAllocated && cap != 0)
            return false;
        if (v->CapacityIncrement <= 0)
            return false;
        if (!v->SetCapacity(v->CapacityIncrement + cap, 0))
            return false;
    }
    int index = v->Count++;
    v->Items[index] = item;
    return true;
}

// The TerrainTypeClass constructor's shape: early returns, the element address formed first.
template <class T> inline bool MapObjAddItemSlotEarlyOut(DynamicVectorClass<T>* v, const T& item)
{
    if (v->Count >= v->Capacity) {
        if (!v->IsAllocated && v->Capacity != 0)
            return false;
        if (v->CapacityIncrement <= 0)
            return false;
        if (!v->SetCapacity(v->CapacityIncrement + v->Capacity, 0))
            return false;
    }
    T* slot = &v->Items[v->Count++];
    *slot = item;
    return true;
}

// The non-virtual lookup retail expands inline where it names the class explicitly.
template <class T> inline int MapObjFindIndex(const DynamicVectorClass<T>* v, const T& item)
{
    int i;
    for (i = 0; i < v->Count; ++i) {
        if (v->Items[i] == item)
            return i;
    }
    return -1;
}
GG_STATIC_ASSERT(sizeof(VectorClass<OverlayClass*>) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<OverlayClass*>) == 0x18);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H
