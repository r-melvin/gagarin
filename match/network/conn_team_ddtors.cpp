// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The MultiplayerTeam constructor and scalar deleting destructor (no base
// class in RTTI; the class is in multiplayer_team.h). NullModemConnClass's
// scalar deleting destructor now lives with its constructor in
// match/network/null_modem_conn_class.cpp.

#include "../FUNCTION.H"
#include "multiplayer_team.h"

// FUNCTION: GAMEMD 0x5D8C50
MultiplayerTeam::MultiplayerTeam(const Obj_007B66D0& name, int unknown)
    : unknown_04(name),
      unknown_08(unknown)
{
}

// SYNTHETIC: GAMEMD 0x5D8D50
// MultiplayerTeam scalar deleting destructor, emitted with the vtable
// 0x7EEEDC by the constructor above. The destructor is `inline` in this unit
// so that the wrapper carries its body as retail's does; the out-of-line
// copy 0x5D8C80, which the leaf destructors jump to, stays a declaration.
inline MultiplayerTeam::~MultiplayerTeam()
{
}
