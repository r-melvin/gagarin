// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, offsets and the layer-array base read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4A9720. ObjectClass's
//   LastLayer @0x94 comes from the committed P2 spine and is reconfirmed here
//   (`CMP dword ptr [ESI+0x94],-1`). The layer array's 24-byte stride is what
//   `LEA EDX,[EDI+EDI*2]` + `LEA ECX,[EDX*8+0x8A0360]` encodes — 3*8 — which is
//   exactly sizeof(DynamicVectorClass).
#ifndef GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H
#define GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"

// LayerClass — the per-draw-layer object list. Layout-compatible with
// DynamicVectorClass (sizeof 0x18); only the insert entry point is needed.
class LayerClass
{
public:
    void* _vtable;            // +0x00
    void* Items;              // +0x04
    int   Capacity;           // +0x08
    int   IsAllocated;        // +0x0C
    int   Count;              // +0x10
    int   CapacityIncrement;  // +0x14

    bool AddItem(ObjectClass* object, bool sorted);  // GAMEMD 0x5519B0 (declared; reloc)
};
GG_STATIC_ASSERT(sizeof(LayerClass) == 0x18);

// GLOBAL: GAMEMD 0x008A0360 — the draw-layer array.
extern LayerClass DisplayLayers[];

// InWhichLayer() — ObjectClass virtual at primary-vtable slot +0x78, dispatched
// through the same __fastcall-fn-pointer idiom the rest of the tree uses so VC6
// reproduces `MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0x78]`.
typedef int (__fastcall* InWhichLayerFunc)(ObjectClass*);
#define OBJ_IN_WHICH_LAYER(obj) ((*(InWhichLayerFunc*)(*(char**)(obj) + 0x78))(obj))

class DisplayClass
{
public:
    void Submit(ObjectClass* object);   // GAMEMD 0x4A9720 (matched)
    void Remove(ObjectClass* object);   // GAMEMD 0x4A9770 (declared; reloc)
};

#endif  // GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H
