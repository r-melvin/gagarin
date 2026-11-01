// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry-origin disassembly 0x589290..0x589362. | YRpp-cross-check
#include "vector_search_00589290.h"
// FUNCTION: GAMEMD 0x589290
bool SearchVector8_00589290::Remove(int index)
{
    // Retail tests the upper bound only.
    if (index < Count) {
        --Count;
        for (int i = index; i < Count; ++i) Data[i] = Data[i + 1];
        return true;
    }
    return false;
}
// FUNCTION: GAMEMD 0x589300
// REA: ev_b81a01a29b2e7a1048fa4701ed2337aa73616f3f127d13bbb455ae8729ab8b03.
// PARTIAL: 37/42 instructions (88.1%). The right-hand iterator is based at
// +4 rather than retail +2, changing three compares and a branch encoding.
// Source forms and flag bisection retained /O2. A validated 120-second
// permuter run made 1988 iterations (baseline score 20), with no improvement.
bool SearchVector16_00589300::Equals(const SearchVector16_00589300& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) {
            if (Data[i].unknown_00 != other.Data[i].unknown_00) return false;
            if (Data[i].unknown_02 != other.Data[i].unknown_02) return false;
            if (Data[i].unknown_04 != other.Data[i].unknown_04) return false;
            if (Data[i].unknown_06 != other.Data[i].unknown_06) return false;
        }
        return true;
    }
    return false;
}
