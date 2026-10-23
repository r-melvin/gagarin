// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, offsets and the layer-array base read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4A9770: the object's
//   LastLayer as `MOV EAX,[EDI+0x94]` / `MOV dword ptr [EDI+0x94],-1`
//   (ObjectClass spine, reconfirmed below); the 24-byte layer stride from
//   `LEA EAX,[EAX+EAX*2]` + `[EAX*8+0x8A0360]`; the layer's Items at +0x04
//   and Count at +0x10; the vector virtual at [vptr+0x10] called with the
//   address of the stacked object (`LEA EAX,[ESP+0xC]; PUSH EAX`), i.e.
//   DynamicVectorClass::ID(const T*); and the fallback sweep from 0x8A0370
//   (layer 0's Count) in 0x18 steps up to 0x8A03E8 = five layers. The method
//   name is YRpp's DisplayClass::Remove.
#ifndef GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H
#define GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/object_class.h"

GG_STATIC_ASSERT(offsetof(ObjectClass, LastLayer) == 0x94);

// Declaration order matters -- see match/_rt/gg_vslot.h.
#include "../_layout/draw_layer_004a9770.h"

class DisplayClass
{
public:
    // FUNCTION: GAMEMD 0x4A9770
    void Remove(ObjectClass* object);
};

#endif  // GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H
