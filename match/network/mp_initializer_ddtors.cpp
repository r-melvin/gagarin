// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// MultiplayerGameMode::InitializerBase and its Initializer<Mode> template.
// RTTI names the base ".?AVInitializerBase@MultiplayerGameMode@@" (vtable
// 0x7EEE74) and six instantiations, one per game mode. Every scalar deleting
// destructor stores the base vtable, frees the object when bit 0 of the flag
// is set, and returns `this`: the destructor is the base's empty virtual one.
// The bodies here are compiler output: the explicit instantiations below
// compile each Initializer<Mode> constructor, which emits the vtables and with
// them the `??_G` wrappers. Neither class touches a member in these bodies, so
// no layout is reconstructed.

#include "multiplayer_game_mode.h"

class MultiplayerBattle;
class MultiplayerManBattle;
class MultiplayerSiege;
class UnholyAlliance;
class FreeForAll;
class MPCooperative;

// MultiplayerGameMode::InitializerBase and Initializer<T> are declared in the
// canonical class (multiplayer_game_mode.h).

// SYNTHETIC: GAMEMD 0x5D7FD0
// MultiplayerGameMode::InitializerBase scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5D7FF0
// Initializer<MultiplayerBattle> (vtable 0x7EEEBC)
// SYNTHETIC: GAMEMD 0x5D8010
// Initializer<MultiplayerManBattle> (vtable 0x7EEEB0)
// SYNTHETIC: GAMEMD 0x5D8030
// Initializer<MultiplayerSiege> (vtable 0x7EEEA4)
// SYNTHETIC: GAMEMD 0x5D8050
// Initializer<UnholyAlliance> (vtable 0x7EEE98)
// SYNTHETIC: GAMEMD 0x5D8070
// Initializer<FreeForAll> (vtable 0x7EEE8C)
// SYNTHETIC: GAMEMD 0x5D8090
// Initializer<MPCooperative> (vtable 0x7EEE80)
template class MultiplayerGameMode::Initializer<MultiplayerBattle>;
template class MultiplayerGameMode::Initializer<MultiplayerManBattle>;
template class MultiplayerGameMode::Initializer<MultiplayerSiege>;
template class MultiplayerGameMode::Initializer<UnholyAlliance>;
template class MultiplayerGameMode::Initializer<FreeForAll>;
template class MultiplayerGameMode::Initializer<MPCooperative>;
