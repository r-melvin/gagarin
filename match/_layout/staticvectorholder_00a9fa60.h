// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_STATICVECTORHOLDER_00A9FA60_H_H
#define GG_MATCH__LAYOUT_STATICVECTORHOLDER_00A9FA60_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../vector_class_operations.h"

class AnimClass;

struct StaticVectorHolder_00A9FA60 {
    // GLOBAL: GAMEMD 0x00A9FA60
    static DynamicVectorClass<const AnimClass*> DAT_00A9FA60;
};

#endif
