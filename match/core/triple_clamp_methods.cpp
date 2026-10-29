// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Clamp of the third component of a three-integer record to a lower bound taken
// from a global object that is queried with the record (global at 0x87F7E8,
// query 0x578080). The record is returned through the hidden pointer (RET 8).
struct Triple_00747EB0 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
};
#include "../_layout/map_0087f7e8.h"
struct Obj_00747EB0 {
    Triple_00747EB0 FUN_00747EB0(const Triple_00747EB0* value);
};
// FUNCTION: GAMEMD 0x00747EB0
Triple_00747EB0 Obj_00747EB0::FUN_00747EB0(const Triple_00747EB0* value)
{
    Triple_00747EB0 local = *value;
    if (local.unknown_08 < DAT_0087F7E8.FUN_00578080(&local))
        local.unknown_08 = DAT_0087F7E8.FUN_00578080(&local);
    return local;
}
