// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474810, 0x4750D0,
//   0x475260 and 0x4752E0.

#include "ccini_class_house_list_methods.h"

// FUNCTION: GAMEMD 0x474810
//
// Read a percentage and hand it back as an eight-bit fraction. The sentinel
// default of -1 distinguishes an absent key, which gives the caller's value
// back untouched; anything present is clamped into 0..100, scaled by 256,
// divided by 100 and clamped again at 255.
int CCINI_00474810::ReadPercentAsByte(const char* section, const char* key,
                                      int defaultValue)
{
    int value = ReadInteger(section, key, -1);

    if (value == -1) {
        return defaultValue;
    }

    value = value < 100 ? value : 100;
    value = value > 0 ? value : 0;
    value = value * 256 / 100;

    // Mutating the variable and returning it, rather than returning the
    // clamping ternary, is what puts retail's `MOV EAX,EDX` ahead of the
    // compare: the fallthrough return value has to be live before the test.
    // The ternary form sits at 93.3% with an identical multiset, and the
    // reversed ternary at 86.7%.
    if (value >= 255) {
        value = 255;
    }

    return value;
}

// FUNCTION: GAMEMD 0x4750D0
//
// Read a comma-separated list of house-type names and fold their masks
// together. An absent key gives the caller's value back; a present but
// empty one gives zero, which is why the accumulator and the fallback share
// one variable.
int CCINI_00474810::ReadHouseTypesList(const char* section, const char* key,
                                       int defaultValue)
{
    char buffer[128];
    int  result = defaultValue;

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        result = 0;

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70); token != 0;
             token = FUN_007C9CC2(0, STR_00817F70)) {
            result |= FUN_0048DEB0(token);
        }
    }

    return result;
}

// FUNCTION: GAMEMD 0x475260
//
// The same walk over house names, where the lookup yields a bit number
// rather than a ready-made mask.
int CCINI_00474810::ReadHousesList(const char* section, const char* key,
                                   int defaultValue)
{
    char buffer[128];
    int  result = defaultValue;

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        result = 0;

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70); token != 0;
             token = FUN_007C9CC2(0, STR_00817F70)) {
            result |= 1 << FUN_0050C170(token);
        }
    }

    return result;
}

// FUNCTION: GAMEMD 0x4752E0
//
// Write a house bit mask back out as a comma-separated list of house names.
// An empty mask, an empty registry and a mask that selects nothing are all
// silently successful without writing the key at all. The separator test
// reads the buffer's own first byte rather than carrying a flag, so the
// first name lands without a leading comma.
bool CCINI_00474810::WriteHousesList(const char* section, const char* key,
                                     unsigned int bits)
{
    char buffer[128];

    buffer[0] = '\0';

    if (bits != 0) {
        int count = DAT_00A80228.Count;

        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                House_004752E0* house = DAT_00A80228.Items[i];

                if (bits & (1 << house->Index)) {
                    if (buffer[0] != '\0') {
                        strcat(buffer, STR_00817F70);
                    }

                    strcat(buffer, house->Name);
                }
            }

            if (buffer[0] != '\0') {
                return WriteString(section, key, buffer);
            }
        }
    }

    return true;
}
