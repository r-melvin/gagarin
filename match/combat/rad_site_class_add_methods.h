// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x65B530-0x65B579), cross-checked
//   against YRpp RadSiteClass.h / RulesClass.h (consult-only; reconfirmed
//   numerically here). Layout mirrors match/combat/rad_site_class_methods.h.
//
// RadSiteClass::Add - bump the rad level by a new contribution: read the
// currently-applied level (float-scaled by time-left over duration), tear the
// site down, raise RadLevel, re-derive the duration pair from the rules
// multiple, and re-activate.
#ifndef GG_MATCH_COMBAT_RAD_SITE_CLASS_ADD_H
#define GG_MATCH_COMBAT_RAD_SITE_CLASS_ADD_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct - map cell coordinate (short X, short Y); 4 bytes.
struct CellStruct
{
    short X;
    short Y;
};

// RulesClass::Instance pointer @0x008871E0; Add reads the RadDurationMultiple
// member @0x1804 (load of [0x8871E0] then [edx+0x1804]). Only that is modelled.
struct RulesClass
{
    char _pad0[0x1804];   // +0x0000
    int  RadDurationMultiple; // +0x1804
};

extern RulesClass* RulesInstance;  // GLOBAL: GAMEMD 0x008871E0

struct RadSiteClass
{
    void Add(int nRadLevel);   // GAMEMD 0x65B530 __thiscall

    // Retail callees we do not match here - declared (no body) so cl emits a
    // normalised relative call.
    void Deactivate();         // GAMEMD 0x65BB50 __thiscall
    void Activate();           // GAMEMD 0x65B580 __thiscall

    // AbstractClass base + the LightSource pointer occupy [0x00..0x3F]; their
    // full decomposition is P2. Only members our method touches are modelled.
    char       _base[0x40];     // +0x00
    CellStruct BaseCell;        // +0x40
    int        Spread;          // +0x44
    int        SpreadInLeptons; // +0x48
    int        RadLevel;        // +0x4C
    char       _pad1[0x6C - 0x50]; // +0x50
    int        RadDuration;     // +0x6C
    int        RadTimeLeft;     // +0x70
};

GG_STATIC_ASSERT(offsetof(RadSiteClass, RadLevel)        == 0x4C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadDuration)     == 0x6C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadTimeLeft)     == 0x70);
GG_STATIC_ASSERT(offsetof(RulesClass,   RadDurationMultiple) == 0x1804);

#endif  // GG_MATCH_COMBAT_RAD_SITE_CLASS_ADD_H
