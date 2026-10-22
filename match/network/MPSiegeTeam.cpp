// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPSiegeTeam.cpp. The name is the source-file string at 0x82fff4
//   in retail gamemd.exe v1.001, passed by the assert at 0x5cae16 inside this object's
//   code range (0x5cac20-0x5cb18f). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// The MPSiegeTeam.cpp block of retail .text (0x5CAC20..0x5CB18F; the unit's
// own path at 0x82FFF4 names it): three of the unit's run-time initialisers
// and the MultiplayerSiegeDefenderTeam / MultiplayerSiegeAttackerTeam
// constructors, destructors and the defender's slot 1, in retail address
// order. Both classes are declared in multiplayer_game_mode.h.
//
// STRING: GAMEMD 0x82FFE4 "MP:DefenderTeam"
// STRING: GAMEMD 0x830044 "MP:AttackerTeam"

#include "multiplayer_game_mode.h"
#include "transport/conn_types.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xABFAA0
extern double DAT_00ABFAA0;
// GLOBAL: GAMEMD 0x7EE7D0
const double DAT_007EE7D0 = 60.0;

// ---- the siege teams -----------------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x82FFF4 -- this unit's build path, handed to the label lookup.
extern const char DAT_0082FFF4[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised
// text; __fastcall with the file and line on the stack, RET 8.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// SYNTHETIC: GAMEMD 0x5CAC50
// GLOBAL: GAMEMD 0xABFAF0
double DAT_00ABFAF0 = DAT_00ABFAA0 / DAT_007EE7D0;

// SYNTHETIC: GAMEMD 0x5CAC70
// GLOBAL: GAMEMD 0xABFAD8
double DAT_00ABFAD8 = 1.0 / DAT_00ABFAF0;

// SYNTHETIC: GAMEMD 0x5CADF0
// GLOBAL: GAMEMD 0xABFAE0
TuningCoordInit DAT_00ABFAE0(128, 128, 0);

// FUNCTION: GAMEMD 0x5CAE10
MultiplayerSiegeDefenderTeam::MultiplayerSiegeDefenderTeam()
    : MultiplayerTeam(FUN_00734E60("MP:DefenderTeam", 0, DAT_0082FFF4, 6), 1)
{
}

// FUNCTION: GAMEMD 0x5CAE60
MultiplayerSiegeDefenderTeam::~MultiplayerSiegeDefenderTeam()
{
}

// FUNCTION: GAMEMD 0x5CAE70
//
// A player may join the defenders only while no other player is on team 1.
//
// PARTIAL (67.9%; mnemonic multiset identical). Retail keeps the player count
// in EDX and walks the item pointer in ESI; VC6 here picks the opposite pair.
// Tried: the operand order of the index test (64.3%), a `continue` on the
// caller's own index (64.3%); a cached count/items local would be an alias.
bool MultiplayerSiegeDefenderTeam::vf_1(int playerIndex)
{
    for (int i = 0; i < PlayerCount_00A8DA84; i++) {
        if (playerIndex != i && Players_00A8DA78[i]->unknown_6B == 1) {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5CAEB0
MultiplayerSiegeAttackerTeam::MultiplayerSiegeAttackerTeam()
    : MultiplayerTeam(FUN_00734E60("MP:AttackerTeam", 0, DAT_0082FFF4, 0x16), 1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CAF00
MultiplayerSiegeAttackerTeam::~MultiplayerSiegeAttackerTeam()
{
}
