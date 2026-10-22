// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Table bases, the four sentinel globals and both call targets are read
//   numerically off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x46F810 and 0x46F880. Neither entry point is bound by YRpp.
//
// Two index-keyed lookups over the same object array at 0xA8DA90. Each asks the
// object a yes/no question; on yes it answers from its own parallel table
// (0xA8B2BC and 0xA8B2DC respectively), and on no it rejects four specific
// object identities with -2 before falling back to a second query. Apart from
// the parallel table the two are identical.
#ifndef GG_MATCH_CORE_HOUSE_INDEX_LOOKUP_METHODS_H
#define GG_MATCH_CORE_HOUSE_INDEX_LOOKUP_METHODS_H

struct Entry_0046F810
{
    // FUNCTION: GAMEMD 0x5E9440 (decl; reloc) — the gate, __thiscall, byte
    // result. Its body is matched in match/economy/netshare_slot_nodes.cpp.
    bool FUN_005E9440();
    // FUNCTION: GAMEMD 0x696F20 (decl; reloc) — the fallback. Declared as a member so the
    // tail position stays a `CALL` rather than becoming a `JMP`.
    int FUN_00696F20();
};

// GLOBAL: GAMEMD 0xA8DA90 — the object array, indexed by the argument.
extern Entry_0046F810* DAT_00A8DA90[];
// GLOBAL: GAMEMD 0xA8B2BC — the parallel table 0x46F810 answers from.
extern int DAT_00A8B2BC[];
// GLOBAL: GAMEMD 0xA8B2DC — the parallel table 0x46F880 answers from.
extern int DAT_00A8B2DC[];

// The four rejected identities. They are not contiguous (0xAC11A4..0xAC11AC is
// skipped), so they are four separate globals rather than an array.
extern Entry_0046F810* DAT_00AC119C;   // GLOBAL: GAMEMD 0xAC119C
extern Entry_0046F810* DAT_00AC11A0;   // GLOBAL: GAMEMD 0xAC11A0
extern Entry_0046F810* DAT_00AC11B0;   // GLOBAL: GAMEMD 0xAC11B0
extern Entry_0046F810* DAT_00AC11B4;   // GLOBAL: GAMEMD 0xAC11B4

// FUNCTION: GAMEMD 0x46F810
int FUN_0046F810(int index);
// FUNCTION: GAMEMD 0x46F880
int FUN_0046F880(int index);

#endif  // GG_MATCH_CORE_HOUSE_INDEX_LOOKUP_METHODS_H
