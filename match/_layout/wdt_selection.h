// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WorldDominationTour::Selection (RTTI .?AVSelection@WorldDominationTour@@, vtable 0x7F72B4, base MSEngine): the
//   World Domination Tour screen, built on the stack by the factories 0x76ECD0 / 0x76ED10 through its constructor
//   0x76C290 (engine at +0x00, rc_ptr members from +0x48). That constructor calls the voice-animation factory 0x771800
//   with itself as the owner, so it is the object WorldDominationTour::Voices::Anim keeps at +0x1C. Only the members
//   the voice animation's slots and the helper 0x771620 touch are named.
#ifndef GG_MATCH_LAYOUT_WDT_SELECTION_H
#define GG_MATCH_LAYOUT_WDT_SELECTION_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ms_engine.h"

namespace WorldDominationTour {

// The polymorphic member at +0x3C0 (a queue of voice names); only its slot 3 is run.
struct SelectionQueue
{
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
};

// VTABLE: GAMEMD 0x7F72B4
class Selection : public MSEngine
{
public:
    // FUNCTION: GAMEMD 0x771620 (decl; reloc)
    void FUN_00771620();

    char           unknown_048[0x3AC - 0x48];
    MSTimer        Stopwatch;      // +0x3AC
    char           unknown_3B8[8];
    SelectionQueue Queue;          // +0x3C0
    char           unknown_3C4[12];
    int            Count;          // +0x3D0
};
GG_STATIC_ASSERT(offsetof(Selection, Stopwatch) == 0x3AC && offsetof(Selection, Queue) == 0x3C0
              && offsetof(Selection, Count) == 0x3D0);

}  // namespace WorldDominationTour

#endif  // GG_MATCH_LAYOUT_WDT_SELECTION_H
