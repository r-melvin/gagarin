// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The one MultiplayerTeam class and its RTTI-named leaves, read off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI:
//     0x7EEEDC `.?AVMultiplayerTeam@@`             (3 slots, no base class)
//     0x7EE6C8 `.?AVMultiplayerObserverTeam@@`
//     0x7EE7E4 `.?AVMultiplayerSiegeDefenderTeam@@`
//     0x7EE7F4 `.?AVMultiplayerSiegeAttackerTeam@@`
//   sizeof 0xC (PUSH 0xC; operator new at 0x5CA9B2). The constructor 0x5D8C50
//   copies a Obj_007B66D0 to +0x04 (0x7B6720) and stores its second
//   argument at +0x08; the out-of-line destructor 0x5D8C80 stores the vtable
//   and tail-jumps to the Obj_007B66D0 destructor 0x7B6760. The deleting
//   destructor 0x5D8D50 carries that body inline.
#ifndef GG_MATCH_NETWORK_MULTIPLAYER_TEAM_H
#define GG_MATCH_NETWORK_MULTIPLAYER_TEAM_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/wide_string_class.h"

// VTABLE: GAMEMD 0x7EEEDC
class MultiplayerTeam
{
public:
    // FUNCTION: GAMEMD 0x5D8C50 (decl; reloc) -- RET 8.
    MultiplayerTeam(const Obj_007B66D0& name, int unknown);
    // FUNCTION: GAMEMD 0x5D8C80 (decl; reloc) -- slot 0 through ??_G 0x5D8D50.
    virtual ~MultiplayerTeam();
    // FUNCTION: GAMEMD 0x5D8C90 (decl) -- slot 1; one argument, bool.
    virtual bool vf_1(int playerIndex);
    // FUNCTION: GAMEMD 0x5D8CB0 (decl) -- slot 2.
    virtual void vf_2();

    Obj_007B66D0 unknown_04;   // +0x04
    int             unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(MultiplayerTeam, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(MultiplayerTeam, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(MultiplayerTeam) == 0xC);

// VTABLE: GAMEMD 0x7EE6C8
class MultiplayerObserverTeam : public MultiplayerTeam
{
public:
    // FUNCTION: GAMEMD 0x5C9470 (decl; reloc)
    MultiplayerObserverTeam();
};
GG_STATIC_ASSERT(sizeof(MultiplayerObserverTeam) == 0xC);

// VTABLE: GAMEMD 0x7EE7E4
class MultiplayerSiegeDefenderTeam : public MultiplayerTeam
{
public:
    // FUNCTION: GAMEMD 0x5CAE10 (declaration)
    MultiplayerSiegeDefenderTeam();
    // FUNCTION: GAMEMD 0x5CAE60 (declaration; slot 0 through ??_G 0x5CAF10)
    virtual ~MultiplayerSiegeDefenderTeam();
    virtual bool vf_1(int playerIndex);                                    // 1  0x5CAE70
};
GG_STATIC_ASSERT(sizeof(MultiplayerSiegeDefenderTeam) == 0xC);

// VTABLE: GAMEMD 0x7EE7F4
class MultiplayerSiegeAttackerTeam : public MultiplayerTeam
{
public:
    // FUNCTION: GAMEMD 0x5CAEB0 (declaration)
    MultiplayerSiegeAttackerTeam();
    // FUNCTION: GAMEMD 0x5CAF00 (declaration; slot 0 through ??_G 0x5CAF40)
    virtual ~MultiplayerSiegeAttackerTeam();
};
GG_STATIC_ASSERT(sizeof(MultiplayerSiegeAttackerTeam) == 0xC);

#endif  // GG_MATCH_NETWORK_MULTIPLAYER_TEAM_H
