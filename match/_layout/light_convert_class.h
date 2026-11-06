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

class RGBClass;
struct HeaderByte3;
class Surface;

class LightConvertClass
{
public:
    // FUNCTION: GAMEMD 0x555DA0 (decl; reloc) -- the 0x1B4-byte object built at 0x544F37 / 0x545056 (operator new 0x1B4).
    LightConvertClass(const HeaderByte3* palette, const RGBClass* secondPalette, Surface* surface, int red, int green,
                      int blue, bool tint, bool flag, int level);
    virtual ~LightConvertClass();   // slot 0: the scalar deleting destructor, called with flag 1 at 0x549C9C / 0x545019
    char unknown_04[0x190];
    int  unknown_194;   // +0x194 use counter
    int  unknown_198;   // +0x198 compared with the first light value at 0x544EF8
    int  unknown_19C;   // +0x19C compared with the second light value at 0x544F00
    int  unknown_1A0;   // +0x1A0 compared with the third light value at 0x544F08
    char unknown_1A4[0x1B4 - 0x1A4];
};
GG_STATIC_ASSERT(offsetof(LightConvertClass, unknown_194) == 0x194);
GG_STATIC_ASSERT(offsetof(LightConvertClass, unknown_198) == 0x198);
GG_STATIC_ASSERT(offsetof(LightConvertClass, unknown_1A0) == 0x1A0);
GG_STATIC_ASSERT(sizeof(LightConvertClass) == 0x1B4);

#endif  // GG_MATCH_LAYOUT_LIGHT_CONVERT_CLASS_H
