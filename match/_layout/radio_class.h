// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: RadioClass ctor FUN_0x0065A750 (chains MissionClass ctor
//   FUN_0x005B2DA0 at offset 0). Field offsets read from its init writes:
//   RadioLinks vptr @0xE0 (param[0x38]), RadioLinks.Items @0xE4 (param[0x39],
//   operator_new(4)), RadioLinks.Capacity @0xE8 (param[0x3A]=1),
//   RadioLinks.IsAllocated @0xEC (byte param[0x3B]=1); LastCommands[0..2]
//   @0xD4/0xD8/0xDC (param[0x35..0x37]=0). RadioLinks ends at 0xF0 ->
//   sizeof(RadioClass)==0xF0. Cross-checked vs YRpp RadioClass.h.
//
// RadioClass — base of every object that can hold radio links (docked units,
// transports, mind-control, etc.). Derives MissionClass at offset 0 and adds
// the radio command history + the link vector from 0xD4.
#ifndef GG_MATCH_LAYOUT_RADIO_CLASS_H
#define GG_MATCH_LAYOUT_RADIO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "mission_class.h"
#include "vector_class.h"

class TechnoClass;  // RadioLinks element type (used by-pointer only)

// RadioClass  (0xD4..0xEF, sizeof = 0xF0)
struct RadioClass : MissionClass
{
    // Radio-link queries/mutators (defined in core/radio_class_methods.cpp).
    // Non-virtual; declaring them here does not change the layout.
    bool ContainsLink(const TechnoClass* pLink) const;  // GAMEMD 0x65AD50
    int  FindLinkIndex(const TechnoClass* pLink) const;  // GAMEMD 0x65AD90
    bool HasFreeLink() const;                            // GAMEMD 0x65ADC0
    bool HasFreeLinkFor(RadioClass* who) const;          // GAMEMD 0x65ADF0
    bool HasAnyLink() const;                             // GAMEMD 0x65AE30
    void SetLinkCount(int count);                        // GAMEMD 0x65AE60

    int         LastCommands[3];   // +0xD4  (RadioCommand enum x3)
    VectorClassLayout RadioLinks;        // +0xE0  (0x10; docked units etc.)
};

GG_STATIC_ASSERT(offsetof(RadioClass, LastCommands) == 0xD4);
GG_STATIC_ASSERT(offsetof(RadioClass, RadioLinks)   == 0xE0);
GG_STATIC_ASSERT(sizeof(RadioClass)                 == 0xF0);

#endif  // GG_MATCH_LAYOUT_RADIO_CLASS_H
