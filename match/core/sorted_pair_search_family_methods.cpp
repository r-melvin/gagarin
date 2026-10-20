// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these seven functions binary-searches a sorted array of
//   eight-byte (key, value) entries for a key the caller passes by address,
//   returning the matching entry or a null pointer. Six instantiations are
//   byte-identical with no relocation at all; the seventh, 0x725070, differs
//   in exactly one byte (JLE against JBE) because its key is unsigned.
//   Ordered ascending by retail address.
//
// STATUS: PARTIAL, 94.3% (33/35 instructions, multiset identical). The only
// residual is a two-position scheduling swap in the entry sequence: retail
// tests the incoming count register before copying it (`TEST EDX,EDX;
// PUSH EDI; MOV ESI,EDX`) while cl copies first and tests the copy
// (`MOV ESI,EDX; PUSH EDI; TEST ESI,ESI`). Everything from the key load
// onwards is exact. Eleven spellings were measured in two match_all runs —
// `while (count > 0)`, `while (0 < count)`, `while (count >= 1)`,
// `for (; count > 0; )`, an `if`-guarded do/while, an early `return 0` guard,
// a do/while over a separate loop counter, and four spellings of the window
// shrink — and every structurally correct one lands on exactly 94.3% or
// worse; the guarded do/while forms collapse to 55.6%.
//
// A later pass added the ninth and tenth batches' boundary levers and they do
// not reach it either: the loop moved into a free inline helper behind an
// explicit wrapper (0.0%), the same helper with a forwarding return (5.6%),
// the count tested without a relational operator (88.6%), the window length
// copied into its own variable behind an early guard (91.4%), and the shrink
// written as the remaining upper half (94.3%). Seventeen structurally correct
// spellings now agree on 94.3%, which puts this residual in the same class as
// the stream-save family's: a two-position entry-sequence swap that the
// source side does not appear to reach.

#include "sorted_pair_search_family_methods.h"

// FUNCTION: GAMEMD 0x004D2F00
GG_SORTED_PAIR_SEARCH_BODY(004D2F00, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x00523440
GG_SORTED_PAIR_SEARCH_BODY(00523440, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x0052B6D0
GG_SORTED_PAIR_SEARCH_BODY(0052B6D0, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x0052B750
GG_SORTED_PAIR_SEARCH_BODY(0052B750, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x005FC120
GG_SORTED_PAIR_SEARCH_BODY(005FC120, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x00710890
GG_SORTED_PAIR_SEARCH_BODY(00710890, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x00725070
GG_SORTED_PAIR_SEARCH_BODY(00725070, SortedEntryU_00725070, unsigned int)
