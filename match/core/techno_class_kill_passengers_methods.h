// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x707CB0. Three callee bindings come from YRpp
//   and are reconfirmed against the disassembly:
//   0x473430 = PassengersClass::RemoveFirstPassenger, 0x6EA870 =
//   TeamClass::LiberateMember, 0x707CB0 = TechnoClass::KillPassengers itself
//   (the recursive call at 0x707CF5 confirms it). 0x473450 is the out-of-line
//   PassengersClass::GetFirstPassenger — YRpp inlines that accessor, but retail
//   has a real function, called here and by MarkPassengersAsExited with the
//   same `ECX = this + 0x114`.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // TechnoClass::Passengers @0x114, FootClass::Team @0x5D4

class TeamClass
{
public:
    void LiberateMember(FootClass* foot, int idx, unsigned char count);  // GAMEMD 0x6EA870
};

#endif  // GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H
