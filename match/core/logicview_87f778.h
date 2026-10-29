// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_CORE_LOGICVIEW_87F778_H_H
#define GG_MATCH_CORE_LOGICVIEW_87F778_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class ObjectClass;

struct LogicView_87F778
{
    // FUNCTION: GAMEMD 0x55BAE0 (declaration) -- remove an object from the logic list.
    void FUN_0055BAE0(ObjectClass* object);
    // FUNCTION: GAMEMD 0x55BAA0 (declaration) -- add an object to the logic list.
    void FUN_0055BAA0(ObjectClass* object, bool a2);
};

#endif
