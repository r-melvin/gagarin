// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x408930.

#include "small_misc32_methods.h"

// Use direct member stores; no receiver aliases or volatile flag access.

// FUNCTION: GAMEMD 0x408930
// Rewind the cursor onto its source. The flag clear at the end is written once
// but appears in both arms of the disassembly - retail duplicates the tail
// rather than merging the paths.
void Cursor_00408930::FUN_00408930()
{
    Source_00408930* source = Source;

    unknown_2C = 0;
    unknown_0C = source;

    if (source != 0) {
        unknown_04 = source->Entries[Channel].First;
        unknown_08 = 0;
    } else {
        unknown_04 = 0;
        unknown_08 = 0;
    }

    Flags &= ~1;
}
