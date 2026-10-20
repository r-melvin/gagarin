// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x43A770.

#include "stream_write_array_methods.h"

// FUNCTION: GAMEMD 0x413850
long Owner_00413850::FUN_00413850(Stream_0043A770* stream)
{
    // The counter is initialised before the cursor and advanced before it too -
    // retail is `XOR EBP,EBP; LEA EDI,[ECX+4]` and `INC EBP; ADD EDI,0x18`.
    // Declaring the cursor first, or advancing it in the body, swaps each pair.
    int n = 0;

    IntVector_00413850* vector = Vectors;

    for (; n < 0x190; n++, vector++) {
        int count = vector->Count;

        long hr = STREAM_WRITE_0043A770(stream, &count, 4);

        if (hr < 0) {
            return hr;
        }

        for (int i = 0; i < count; i++) {
            hr = STREAM_WRITE_0043A770(stream, &vector->Items[i], 4);

            if (hr < 0) {
                return hr;
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x43A770
long Owner_0043A770::FUN_0043A770(Stream_0043A770* stream, void* context)
{
    if (stream == 0) {
        return 0x80004003;
    }

    int count = Count;

    long hr = STREAM_WRITE_0043A770(stream, &count, 4);

    if (hr >= 0) {
        for (int i = 0; i < count; i++) {
            Element_0043A770* element = Items[i];

            hr = ELEMENT_SAVE_0043A770(element, stream, context);

            if (hr < 0) {
                return hr;
            }
        }

        return 0;
    }

    return hr;
}
