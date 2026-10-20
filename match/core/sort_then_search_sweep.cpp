// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The five remaining sort-then-search lookups, ordered ascending by retail address.
//
// The phrasing lever here is the split between `Find` and `SearchSorted`.
// Written as one function -- the empty-table guard, the lazy sort and the
// search loop in a single body -- cl tail-merges the two `return 0` exits into
// one block, and because that block pops all three callee-saved registers, all
// three pushes move up into the prologue. Retail pushes only ESI at entry and
// sinks PUSH EBX / PUSH EDI to just before the search, which is exactly what cl
// emits once the loop lives in its own inline function with its own miss
// return. That one change takes the body from 25.9% to 100%; ten other
// spellings of the guard (`!Count`, `Count <= 0`, a hoisted count local,
// returning the count cast to the pointer type, an `if (Count != 0)` wrapper)
// and a flag bisection over /Ox, /Oy, /Ot /Og /Oi, /G5, /Gr and /Gy on and off
// all stay at 25.9%.

#include "sort_then_search_sweep.h"

// FUNCTION: GAMEMD 0x41C590
GG_SORT_SEARCH_BODY(41C590, int)

// FUNCTION: GAMEMD 0x52B4F0
GG_SORT_SEARCH_BODY(52B4F0, int)

// FUNCTION: GAMEMD 0x52B620
GG_SORT_SEARCH_BODY(52B620, int)

// FUNCTION: GAMEMD 0x55F6E0
GG_SORT_SEARCH_BODY(55F6E0, int)

// FUNCTION: GAMEMD 0x7107E0
GG_SORT_SEARCH_BODY(7107E0, int)

// The unsigned-key lookup at 0x724FC0 now lives on ToolTipTable.

