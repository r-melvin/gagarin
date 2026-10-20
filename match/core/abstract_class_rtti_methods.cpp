// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x40DCB0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x40DCB0  AbstractClass::GetRTTIName (__fastcall)
//   GLOBAL:   GAMEMD 0x00816EE0  RTTINames[74]
//   STRING:   GAMEMD 0x00817130  "Unknown"

#include "abstract_class_rtti_methods.h"

// FUNCTION: GAMEMD 0x40DCB0  AbstractClass::GetRTTIName (__fastcall)
// Linear scan rather than an index, because the table is keyed rather than
// dense. Retail walks a pointer over the Key fields while keeping the index in
// EDX for the Name load, and falls back to the literal that sits directly after
// the table.
const char* __fastcall AbstractClass::GetRTTIName(int rtti)
{
    for (int i = 0; i < RTTI_NAME_COUNT; i++) {
        if (RTTINames[i].Key == rtti)
            return RTTINames[i].Name;
    }

    return "Unknown";
}
