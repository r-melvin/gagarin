// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x554AA0-0x554AE5), cross-checked
//   against YRpp (reconfirmed numerically from the disasm).
//
// LightSourceClass — extra (ChangeLevels) binding. Models only the members the
// ChangeLevels method touches: LightIntensity@0x24, the TintStruct LightTint
// (Red@0x28, Green@0x2c, Blue@0x30) and the Activated flag@0x48.
#ifndef GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H
#define GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


#include "../_layout/light_source_class.h"

GG_STATIC_ASSERT(offsetof(LightSourceClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(LightSourceClass, TintRed) == 0x28);
GG_STATIC_ASSERT(offsetof(LightSourceClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(LightSourceClass, Activated)      == 0x48);

#endif  // GG_MATCH_RENDERER_LIGHT_SOURCE_CLASS_MORE_H
