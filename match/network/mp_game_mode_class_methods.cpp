// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D62C0.

#include "mp_game_mode_class_methods.h"

// FUNCTION: GAMEMD 0x5D62C0  MultiplayerGameMode::vt_entry_10 (__thiscall)
// Number every entry in the global array with its own index, except the ones
// the 0x696F10 classifier reports as -3, which get -1 instead. Retail reloads
// both the Items base and the Count on every iteration — the classifier call
// can mutate the vector, so neither can be cached — and always reports success.
//
// `this` is unused; the name is YRpp's placeholder for vtable slot 10.
bool MultiplayerGameMode::vt_entry_10()
{
    for (int i = 0; i < MPGameModeArray.Count; i++) {
        if (((MPGameModeEntry**)MPGameModeArray.Items)[i]->Classify() == -3) {
            ((MPGameModeEntry**)MPGameModeArray.Items)[i]->unknown_6B = -1;
        } else {
            ((MPGameModeEntry**)MPGameModeArray.Items)[i]->unknown_6B = i;
        }
    }
    return true;
}
