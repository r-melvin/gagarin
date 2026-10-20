// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, widths and initial values read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x431B20.
//
// A constructor that writes every field by hand. Two constants are materialised
// up front - `OR EDX,0xFFFFFFFF` for the -1 fields and `XOR ECX,ECX` for the
// zeros - and shared across the whole block, which is why they are emitted
// before anything else. The vtable goes in last.
//
// The field widths come straight off the stores: `MOV word ptr` at +0x1C and
// +0x1E, `MOV byte ptr` at +0x04, +0x20 and +0x24..+0x29, dwords elsewhere.
#ifndef GG_MATCH_CORE_CTOR_431B20_METHODS_H
#define GG_MATCH_CORE_CTOR_431B20_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern char VT_007E3A2C;   // VTABLE: GAMEMD 0x7E3A2C

struct Obj_00431B20
{
    char*          Vtable;      // +0x0000
    char           field_04;    // +0x0004
    char           _pad005[0x3];
    int            field_08;    // +0x0008
    int            field_0C;    // +0x000C
    int            field_10;    // +0x0010
    int            field_14;    // +0x0014
    int            field_18;    // +0x0018
    short          field_1C;    // +0x001C
    short          field_1E;    // +0x001E
    char           field_20;    // +0x0020
    char           _pad021[0x3];
    char           field_24;    // +0x0024
    char           field_25;    // +0x0025
    char           field_26;    // +0x0026
    char           field_27;    // +0x0027
    char           field_28;    // +0x0028
    char           field_29;    // +0x0029
    char           _pad02A[0x2];
    int            field_2C;    // +0x002C
    int            field_30;    // +0x0030
    int            field_34;    // +0x0034
    int            field_38;    // +0x0038
    int            field_3C;    // +0x003C
    int            field_40;    // +0x0040
    int            field_44;    // +0x0044
    int            field_48;    // +0x0048
    int            field_4C;    // +0x004C
    int            field_50;    // +0x0050

    // FUNCTION: GAMEMD 0x431B20
    Obj_00431B20* FUN_00431B20();
};
GG_STATIC_ASSERT(offsetof(Obj_00431B20, field_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_00431B20, field_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_00431B20, field_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Obj_00431B20, field_50) == 0x50);

#endif  // GG_MATCH_CORE_CTOR_431B20_METHODS_H
