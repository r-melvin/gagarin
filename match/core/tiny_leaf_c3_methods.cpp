// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// A two-call sequence: the second call is a tail jump. Both callees take
// no arguments and are bound by address.

void FUN_0072DC20();
void FUN_0072DCF0();

// FUNCTION: GAMEMD 0x72DAA0
void FUN_0072DAA0()
{
    FUN_0072DC20();
    FUN_0072DCF0();
}
