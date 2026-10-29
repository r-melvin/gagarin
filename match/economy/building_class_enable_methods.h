// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452410. Two callee bindings come from YRpp
//   and are reconfirmed against the disassembly:
//   0x554A60 = LightSourceClass::Activate (so the pointer at +0x614 is a light
//   source) and 0x4533A0 = BuildingClass::CreateEndPost.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"

#include "../_layout/light_source_class.h"

void AnimClass_Enable(AnimClass* anim);

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H
