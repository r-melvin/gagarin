// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7248C0.

#include "tooltip_manager_find_methods.h"

// FUNCTION: GAMEMD 0x7248C0
//
// Look a tool tip up by key and, when the caller wants it, copy it out. The
// lookup is expanded twice because it is asked once for the answer and once
// for the data; a key that vanished between the two hands back the default
// tip rather than failing.
//
// PARTIAL (15.2%, 132 instructions against retail's 119). The entry guard,
// the cache hit, the sort-on-demand with its qsort arguments, the binary
// search body and the 28-byte copy from either the entry's data or the
// default all match in form, and asking the first expansion only whether
// the key is present (a bool-returning twin of the lookup) is what makes
// retail's first copy branch straight to the common tail instead of
// materialising the entry pointer. The residual is that cl 8804 duplicates
// the copy block and an epilogue across the second expansion's return
// paths where retail shares them, and it spells the span update as a
// compare where retail folds it into an add. Tried: both expansions as the
// pointer-returning lookup (5.8%, 120 instructions, one apart in count but
// with the value materialised), a single shared exit versus an early
// return for the miss, and the span update written as `n - half - 1` and
// as `n + (-1 - half)` (identical).
bool ToolTip_007248C0::Find(unsigned int key, ToolTipData_007248C0* out)
{
    if (Contains(key)) {
        if (out != 0) {
            ToolTipData_007248C0* source;
            if (Lookup(key) != 0) {
                source = Cached->Data;
            } else {
                source = DAT_00B78820;
            }
            *out = *source;
        }
        return true;
    }
    return false;
}
