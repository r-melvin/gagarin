// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   LightConvertClass, the palette-light object (a CellClass holds one at +0x34). This is the
//   canonical definition: per-TU views (scenario_class_lighting_recalc_methods.h's
//   LightConvert_0053AD00 and the forward-declared uses) should fold onto it. The class is
//   polymorphic (0x53AD00 calls vtable slot 1); the vtable and the members below +0x194 are
//   not typed yet. Proven so far: 0x47BB60 decrements the dword at +0x194 (guarded by the
//   byte at 0xA8E9A0) and 0x484A80 / 0x484A90 step it.
#ifndef GG_MATCH_LAYOUT_LIGHT_CONVERT_CLASS_H
#define GG_MATCH_LAYOUT_LIGHT_CONVERT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class LightConvertClass
{
public:
    char unknown_00[0x194];
    int  unknown_194;   // +0x194 use counter
};
GG_STATIC_ASSERT(offsetof(LightConvertClass, unknown_194) == 0x194);

#endif  // GG_MATCH_LAYOUT_LIGHT_CONVERT_CLASS_H
