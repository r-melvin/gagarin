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
// STATUS: EXACT. The last residual was an entry-sequence swap: retail tests
// the incoming count register before copying it (`TEST EDX,EDX; PUSH EDI;
// MOV ESI,EDX`). That is the shape cl gives when the window size is its own
// local seeded from the `count` parameter (`for (n = count; n > 0;)`); with
// the parameter itself as the loop variable it copies first and tests the
// copy. See GG_SORTED_PAIR_SEARCH_BODY in the header.

#include "sorted_pair_search_family_methods.h"
#include "_layout/index.h"

class AbstractClass;

// FUNCTION: GAMEMD 0x004D2F00
GG_SORTED_PAIR_SEARCH_BODY(004D2F00, SortedEntry_004D2F00, int)

// FUNCTION: GAMEMD 0x00523440
// The binary search of IndexClass<int, AbstractClass*> (see _layout/index.h) over its sorted node array, out of line.
template<>
IndexClass<int, AbstractClass*>::NodeElement* __fastcall
IndexClass<int, AbstractClass*>::FUN_00523440(NodeElement* base, int count, const NodeElement* key)
{
    int n;
    for (n = count; n > 0;) {
        int half = n / 2;
        NodeElement* mid = base + half;
        if (mid->ID > key->ID) {
            n = half;
        } else {
            if (mid->ID == key->ID) {
                return mid;
            }
            base = mid + 1;
            n = n - 1 - half;
        }
    }
    return 0;
}

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
