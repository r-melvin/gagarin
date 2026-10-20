// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x46F810 and 0x46F880.

#include "house_index_lookup_methods.h"

// FUNCTION: GAMEMD 0x46F810
//
// Each of the four rejections gets its own `POP EDI; MOV EAX,-2; POP ESI; RET`
// in retail - four separate epilogues, so four separate `return -2` statements
// rather than one `||` chain, which would share a tail.
int __fastcall FUN_0046F810(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2BC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F20();
}

// FUNCTION: GAMEMD 0x46F880
//
// The same lookup against the second parallel table. Written out rather than
// shared.
int __fastcall FUN_0046F880(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2DC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F20();
}
