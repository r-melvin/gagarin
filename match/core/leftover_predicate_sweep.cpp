// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Nine small guarded predicates across three shapes: a flag-gated
// out-parameter copy, a bool-selected float constant, and a null-guarded relay.
// Within a shape the bodies are byte-identical apart from the member offset,
// the float constant or the relayed call displacement, so each is written once
// as a macro and expanded per instantiation. Ordered ascending by retail
// address.

#include "leftover_predicate_sweep.h"

// FUNCTION: GAMEMD 0x0049BC80
GG_FLAGGET_BODY(0049BC80)

// FUNCTION: GAMEMD 0x0049BCA0
GG_FLAGGET_BODY(0049BCA0)

// FUNCTION: GAMEMD 0x0049BCC0
GG_FLAGGET_BODY(0049BCC0)

// FUNCTION: GAMEMD 0x006E4440
bool __stdcall FUN_006E4440(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DA10(p);
    return true;
}

// FUNCTION: GAMEMD 0x006E44C0
bool __stdcall FUN_006E44C0(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DA50(p);
    return true;
}

// FUNCTION: GAMEMD 0x006E4540
bool __stdcall FUN_006E4540(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DFF0(p);
    return true;
}

// FUNCTION: GAMEMD 0x00750060
GG_FLOATSEL_BODY(00750060, -0.25f)

// FUNCTION: GAMEMD 0x00750090
GG_FLOATSEL_BODY(00750090, 1.0f)

// FUNCTION: GAMEMD 0x007500B0
GG_FLOATSEL_BODY(007500B0, 2.0f)
