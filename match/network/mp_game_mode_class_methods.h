// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, global addresses and offsets read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x5D62C0. The two globals it reads,
//   0x00A8DA78 (Items) and 0x00A8DA84 (Count), sit at +0x04 and +0x10 of a
//   DynamicVectorClass, which pins the vector object to 0x00A8DA74. Address
//   binding cross-checked against YRpp, which knows
//   this only as MultiplayerGameMode::vt_entry_10.
// CLASS NAME CORRECTED (whole-image RTTI sweep):
// `MPGameModeClass` is YRpp's spelling and does not exist in this binary. The
// retail name is `MultiplayerGameMode` (TD 0x008307C0 shows the class inside
// `.?AV?$VectorClass@PAVMultiplayerGameMode@@@@`; its own table is 0x7EED60).
// 0x5D62C0 sits at slot 4 of 0x7EED60 AND of the derived tables Megawealth
// (0x7EE5F4), MultiplayerBattle (0x7EE184) and MultiplayerManBattle
// (0x7EE50C) -- present in the base's own table and inherited by the leaves,
// so MultiplayerGameMode is where it is declared.
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_METHODS_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// The array element. Only the field the sweep stamps is modelled, and it keeps
// a placeholder name: the bytes fix its offset but not its meaning. Note it is
// a *dword* store at an odd offset (`MOV dword ptr [EDX+0x6B],...`), so the
// containing struct is packed.
// Packed: the dword lands at an odd offset, so default 4-byte alignment would
// push it to +0x6C and break the assert below.
#pragma pack(push, 1)
struct MPGameModeEntry
{
    char _pad00[0x6B];   // +0x0000
    int  unknown_6B;     // +0x006B  (stamped with the entry's own index)

    int Classify() const;   // GAMEMD 0x696F10 __thiscall (declared; reloc)
    int FUN_00696F30();     // GAMEMD 0x696F30 __thiscall (declared; reloc)
    void FUN_00696F90(int value);   // GAMEMD 0x696F90 __thiscall RET 4 (declared; reloc)
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(MPGameModeEntry, unknown_6B) == 0x6B);

// GLOBAL: GAMEMD 0x00A8DA74
extern DynamicVectorClassLayout MPGameModeArray;

// MultiplayerGameMode is the canonical class in multiplayer_game_mode.h; slot 4
// (vf_4, 0x5D62C0) is declared there.
#include "multiplayer_game_mode.h"

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_METHODS_H
