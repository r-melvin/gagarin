// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x476340 and
//   0x476420.

#include "ccini_class_triplet_readers_methods.h"

// FUNCTION: GAMEMD 0x476340
//
// Read three floats from one comma-separated key. The caller's default is
// copied into the result up front and each token overwrites one field, so
// an absent key returns the default unchanged — retail copy-propagates that
// arm straight from the caller's own triple rather than from the copy.
FloatTriple CCINI_00476340::ReadFloatTriple(const char* section, const char* key,
                                            const FloatTriple& defaultValue)
{
    FloatTriple value = defaultValue;
    char        buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        value.X = (float)FUN_007C9D66(FUN_007C9CC2(buffer, STR_00817F70));
        value.Y = (float)FUN_007C9D66(FUN_007C9CC2(0, STR_00817F70));
        value.Z = (float)FUN_007C9D66(FUN_007C9CC2(0, STR_00817F70));

        return value;
    }

    // Returning the caller's own triple here, rather than falling out of the
    // if with the copy, is what parks the failure arm in the cold tail and
    // keeps the copy in memory: a single trailing `return value` leaves the
    // copy in registers and scores zero, and an inverted early-return form
    // makes the failure arm the fallthrough and scores 38.1%.
    return defaultValue;
}

// FUNCTION: GAMEMD 0x476420
//
// The integer form of the same reader. The three parsed values stay in
// registers rather than going through the local, which is why the callee
// saves one more register than the float form does.
IntTriple CCINI_00476340::ReadIntTriple(const char* section, const char* key,
                                        const IntTriple& defaultValue)
{
    IntTriple value = defaultValue;
    char      buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        value.X = FUN_007C9BFD(FUN_007C9CC2(buffer, STR_00817F70));
        value.Y = FUN_007C9BFD(FUN_007C9CC2(0, STR_00817F70));
        value.Z = FUN_007C9BFD(FUN_007C9CC2(0, STR_00817F70));

        return value;
    }

    return defaultValue;
}
