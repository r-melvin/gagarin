// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Find-by-name walks, ordered ascending by retail address, written out longhand
// per the family rule.

#include "find_by_name_methods.h"

// FUNCTION: GAMEMD 0x41CAA0
int __fastcall FUN_0041CAA0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8B228; i++) {
            if (FUN_007C8D20(DAT_00A8B21C[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x427CB0
int __fastcall FUN_00427CB0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_008B4160; i++) {
            if (FUN_007C8D20(DAT_008B4154[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x45E760
int __fastcall FUN_0045E760(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x64, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x45E7B0
int __fastcall FUN_0045E7B0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}
