// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5117D0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x5117D0  HouseTypeClass::FindIndexOfName (__fastcall)
//   GLOBAL:   GAMEMD 0x00A83C98  HouseTypeClass::Array
//   STRING:   GAMEMD 0x0081C008  "<random>"

#include "house_type_class_find_methods.h"

// FUNCTION: GAMEMD 0x5117D0  HouseTypeClass::FindIndexOfName (__fastcall)
// Resolve a country by either its INI ID or its display name. The sentinel
// "<random>" answers -2 so callers can distinguish "pick one" from "not found".
//
// Two details are taken from the bytes rather than from what the code ought to
// do: `name` is dereferenced by the first compare and only null-checked
// afterwards, and the argument order flips between the sentinel compare
// (name first) and the array compares (the candidate's string first).
int __fastcall HouseTypeClass::FindIndexOfName(const char* name)
{
    if (_stricmp(name, "<random>") == 0)
        return -2;

    if (name != 0) {
        for (int i = 0; i < HouseTypeArray.Count; i++) {
            HouseTypeClass* type = ((HouseTypeClass**)HouseTypeArray.Items)[i];

            if (_stricmp(type->Name, name) == 0 || _stricmp(type->ID, name) == 0)
                return type->ArrayIndex2;
        }
    }

    return -1;
}
