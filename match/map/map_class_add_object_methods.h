// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5519B0: `[ESI]` vtable then `CALL [EDX+8]`,
//   `[ESI+0x4]` items (indexed `[EDX+EAX*4]`), `[ESI+0x8]` capacity,
//   `[ESI+0xD]` allocated byte, `[ESI+0x10]` count, `[ESI+0x14]` increment.
//   The sorted path is the call to 0x551A90 (`NEG EAX; SBB EAX,EAX; NEG EAX`
//   on its full-width result). The class name (LayerClass, a
//   DynamicVectorClass<ObjectClass*>) and the method name (AddObject) are
//   cross-checked against YRpp; the sorted insert's name is not.
#ifndef GG_MATCH_MAP_MAP_CLASS_ADD_OBJECT_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_ADD_OBJECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class ObjectClass;

// Retail RTTI names this class at 0x816B10 (`.?AVLayerClass@@`), and the
// hierarchy metadata at 0x7FA918 references that TypeDescriptor. LayerClass —
// one draw layer's object list, a DynamicVectorClass<ObjectClass*>.
// Slot +0x08 is Resize(newCapacity, array): two stack arguments, `this` in ECX,
// a byte result tested with `TEST AL,AL`.
class LayerClass
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    ObjectClass** Items;       // +0x0004
    int   Capacity;            // +0x0008
    char  unknown_0C[0x1];
    char  IsAllocated;         // +0x000D
    char  unknown_0E[0x10 - 0x0E];
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // FUNCTION: GAMEMD 0x551A90 (decl; reloc) — insert keeping the layer
    // sorted; full-width result (`MOV EAX,1` / `XOR EAX,EAX`).
    int SortedAdd(ObjectClass* object);

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the AddObject
    // call site; the element is stored straight from the argument slot. The
    // index is bound before the increment (`LEA ECX,[EAX+1]`), unlike the
    // `Count++` shape of CellClass::ReplaceTag (0x485250), which retail
    // compiled to `MOV EAX,ECX; INC ECX`.
    bool AddItem(ObjectClass* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count;
            ObjectClass** items = Items;
            Count = index + 1;
            items[index] = item;
            return true;
        }
        return false;
    }

    // FUNCTION: GAMEMD 0x5519B0
    bool AddObject(ObjectClass* object, bool sorted);
};
GG_STATIC_ASSERT(offsetof(LayerClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(LayerClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(LayerClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LayerClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(LayerClass, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(LayerClass) == 0x18);
GG_STATIC_ASSERT(sizeof(ObjectClass*) == 4);

#endif  // GG_MATCH_MAP_MAP_CLASS_ADD_OBJECT_METHODS_H
