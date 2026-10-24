// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Two signed coordinates interpolated with a float weight, truncated by
// retail __ftol0x7C5F00. No original translation-unit or type name claimed.
#include "../_layout/pair_006d9f80.h"
// FUNCTION: GAMEMD 0x75F5C0
Pair_006D9F80* __fastcall FUN_0075F5C0(Pair_006D9F80* output,
    const Pair_006D9F80* first, const Pair_006D9F80* second, float weight)
{
    double inverse = 1.0 - weight;
    Pair_006D9F80 value;
    value.unknown_00 = (int)(first->unknown_00 * inverse + second->unknown_00 * weight);
    value.unknown_04 = (int)(first->unknown_04 * inverse + second->unknown_04 * weight);
    *output = value;
    return output;
}
