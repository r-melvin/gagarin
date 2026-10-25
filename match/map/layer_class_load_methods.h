// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x551B90: the stream vtable slot `[EAX+0xC]`
//   / `[EDX+0xC]` (IStream::Read, the stream pushed as the first argument);
//   on this the vector members `[ESI+0x4]` Items, `[ESI+0x8]` Capacity,
//   `[ESI+0xD]` IsAllocated, `[ESI+0x10]` Count, `[ESI+0x14]`
//   CapacityIncrement and the slot `[EDX+0x8]` (Resize, two pushed
//   arguments, byte result); the swizzle queue call `PUSH &Items[i]; PUSH
//   0xB0C110; CALL 0x6CF240`. The element count is read into the dead pStm
//   parameter slot and each element into the one frame local. The receiver
//   is a LayerClass: DisplayClass::Load (0x4AE6F0, DisplayClass vtable slot
//   30) calls this on each layer of the array at 0x8A0360, 0x18 bytes apart.
//   YRpp names 0xB0C110 SwizzleManagerClass (name only); the
//   body is the DynamicVectorClass<T*> load.
#ifndef GG_MATCH_MAP_LAYER_CLASS_LOAD_METHODS_H
#define GG_MATCH_MAP_LAYER_CLASS_LOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/swizzle_manager_class.h"

typedef long HRESULT;

// Minimal IStream: only the vtable order matters. COM methods are __stdcall,
// so `this` is the first stacked argument (PUSH pStm; CALL [vtbl+0xC]).
struct IStream_00551B90
{
    virtual long          __stdcall QueryInterface(const void* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                     // +0x04
    virtual unsigned long __stdcall Release() = 0;                                    // +0x08
    virtual long          __stdcall Read(void* pv, unsigned long cb,
                                         unsigned long* pcbRead) = 0;                 // +0x0C
};

// LayerClass, a DynamicVectorClass<ObjectClass*>. Slot +0x08 is
// Resize(newCapacity, array).
class LayerClass
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    void** Items;              // +0x0004
    int    Capacity;           // +0x0008
    char   _pad0C[0x1];        // +0x000C
    char   IsAllocated;        // +0x000D
    char   _pad0E[0x10 - 0x0E];// +0x000E
    int    Count;              // +0x0010
    int    CapacityIncrement;  // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at 0x551BE6. The
    // index is `index = Count; Count = index + 1;` so the increment becomes
    // retail's LEA, and the grown size is `CapacityIncrement + cap` with the
    // capacity bound to a local.
    bool AddItem(void* const& item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(CapacityIncrement + cap, 0))) {
            int index = Count;
            Count = index + 1;
            Items[index] = item;
            return true;
        }
        return false;
    }

    // FUNCTION: GAMEMD 0x551B90 — LayerClass::Load.
    HRESULT Load(IStream_00551B90* pStm);
};
GG_STATIC_ASSERT(offsetof(LayerClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(LayerClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(LayerClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LayerClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(LayerClass, CapacityIncrement) == 0x14);

#endif  // GG_MATCH_MAP_LAYER_CLASS_LOAD_METHODS_H
