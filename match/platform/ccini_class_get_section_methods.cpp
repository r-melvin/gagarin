// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x526810.

#include "ccini_class_get_section_methods.h"

// FUNCTION: GAMEMD 0x526810
//
// Find a section by name. The name is hashed, the cached entry answers when
// it still matches, and otherwise the table is sorted on demand and
// searched. The search runs twice because the first pass only decides
// whether the name is there at all; a name that is not gives back the
// shared empty section.
//
// PARTIAL (3.3% by position; 119 instructions against retail's 120, one
// push and one branch polarity apart). The hash with its inlined strlen,
// the sort-on-demand, the search call, the second inlined binary search and
// every exit match in form. Two things were load-bearing: all three zero
// returns and both found returns are routed through one shared label each,
// which is how retail lays them out; and the search key is written into the
// hash state's own first dword and passed from there, which is what keeps
// the frame at twelve bytes. The residual is that retail defers its EBP
// push into the second lookup where cl emits it in the prologue — the
// banked deferred-callee-saved-push class — and everything after the
// prologue is shifted by it.
Section_00526810* CCINI_00526810::GetSection(const char* name)
{
    if (name == 0) {
        goto missing;
    }

    {
        Crc_00526810 crc;
        crc.A = 0;
        crc.B = 0;
        crc.C = 0;
        int key = crc.Hash(name, strlen(name));

        if (Count == 0) {
            goto missing;
        }

        if (Cached == 0 || Cached->Key != key) {
            if (!IsSorted) {
                gg_qsort(Items, Count, 8, FUN_0052B720);
                Cached = 0;
                IsSorted = 1;
            }
            crc.A = key;
            Entry_00526810* found = FUN_0052B750(Items, Count, &crc.A);
            if (found == 0) {
                goto missing;
            }
            Cached = found;
        }

        if (Count != 0) {
            if (Cached != 0 && Cached->Key == key) {
                goto found;
            }
            if (!IsSorted) {
                gg_qsort(Items, Count, 8, FUN_0052B720);
                Cached = 0;
                IsSorted = 1;
            }
            int n = Count;
            Entry_00526810* base = Items;
            while (n > 0) {
                int half = n / 2;
                Entry_00526810* mid = base + half;
                if (mid->Key > key) {
                    n = half;
                } else {
                    if (mid->Key == key) {
                        if (mid != 0) {
                            Cached = mid;
                            goto found;
                        }
                        break;
                    }
                    base = mid + 1;
                    n = n + (-1 - half);
                }
            }
        }
        return DAT_00B7882C;

    found:
        return Cached->Section;
    }

missing:
    return 0;
}
