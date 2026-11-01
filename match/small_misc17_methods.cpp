// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc17_methods.h"

// FUNCTION: GAMEMD 0x4103E0
// Fills the two consecutive out slots in order: the provider's +4 view, then
// a null second slot.
long __stdcall FUN_004103E0(Provider_004103E0* provider, void** out)
{
    if (out == 0) {
        return 0x80004003;
    }

    *out++ = SLOT_30(provider) + 4;
    *out = 0;

    return 0;
}

