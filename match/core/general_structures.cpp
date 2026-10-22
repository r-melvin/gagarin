// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (each offset/address reconfirmed against the user's binary below).
//
// Translation unit: BasePlanningCellContainer growth + qsort comparator.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x510860  BasePlanningCellContainer::AddCapacity (__thiscall)
//   FUNCTION: GAMEMD 0x5108F0  BasePlanningCellContainer::Comparator  (__cdecl)
//   LIBRARY:  GAMEMD 0x7C8E17  operator new / malloc  (CRT; array new/delete)
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete / free (CRT; array new/delete)

#include "general_structures.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x510860  (__thiscall)
//
// Grow the cell array by `additionalCapacity` slots, preserving the existing
// Count elements. Reject a negative request; reject allocation failure. On
// success: copy the live elements, free the old buffer, publish the new buffer
// and capacity, and clear the Unknown_10 cursor.
//
// MATCHED (100%, 56/56) as plain C++. The allocation is an array new of
// BasePlanningCell, which has an (empty) default constructor: retail's
// otherwise unexplained `DEC EBX; MOV [ESP+0x14],EBX` is the counter of the
// element-construction loop, whose empty body cl removes while keeping the
// counter's store. A raw operator new call instead gives 1.8%. The success
// arms are nested so both failures fall through to the one trailing
// `return false`, as in retail.
// ---------------------------------------------------------------------------
bool BasePlanningCellContainer::AddCapacity(int additionalCapacity)
{
    if (additionalCapacity >= 0) {
        int newCapacity = Capacity + additionalCapacity;
        BasePlanningCell* newItems = new BasePlanningCell[newCapacity];
        if (newItems != 0) {
            int i = 0;
            if (Count > 0) {
                do {
                    newItems[i] = Items[i];
                    ++i;
                } while (i < Count);
            }
            delete[] Items;
            Items = newItems;
            Capacity += additionalCapacity;
            Unknown_10 = 0;
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5108F0  (__cdecl)
//
// qsort comparator over BasePlanningCell::Weight (the leading int of each
// element). Ascending: 0 when equal, +1 when a > b, -1 when a < b.
//
// MATCHED (100%, 16/16). This was recorded as a phrasing-invariant setcc-tail
// delta and is not one. Retail emits `setge dl; dec; and -2; inc` and the
// ternary written `(wa >= wb) ? 1 : -1` emits the mirror `setl dl; dec; and 2;
// dec` (81.2%). The lever is which arm carries the negative literal: writing
// the *less-than* test with -1 in the true arm, `(wa < wb) ? -1 : 1`, makes cl
// keep the comparison as written and invert the arithmetic instead, which is
// retail's tail exactly. Spelling the tail out by hand as
// `((wa >= wb) - 1 & -2) + 1` also reaches 100%, so the two forms are the same
// codegen path. Eight other spellings stay at 81.2% (`>` ternary, nested ifs,
// a named bool, a named int result, the loads written inline) and two are
// worse: `1 - 2 * (wa < wb)` is 62.5% and inverting the equality guard to
// `if (wa != wb) return ...` is 43.8%.
// ---------------------------------------------------------------------------
int __cdecl BasePlanningCellContainer::Comparator(const void* a, const void* b)
{
    int wa = *(const int*)a;
    int wb = *(const int*)b;
    if (wa == wb)
        return 0;
    return (wa < wb) ? -1 : 1;
}
