// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Entry69E430 initializes the0x24-byte resource allocated by5B40B0.
// Identity remains unknown; the fields retain address-based names.
#include "../_layout/obj_0069e430.h"
#include "../platform/ccfile_class.h"
#include <string.h>

// GLOBAL: GAMEMD 0x0083F870
extern unsigned int DAT_0083F870;
// GLOBAL: GAMEMD 0x00B077B0
extern Obj_0069E430* DAT_00B077B0;
extern const char STR_0083F874[]; // STRING: GAMEMD 0x0083F874 (decl; reloc)

// FUNCTION: GAMEMD 0x69E430
Obj_0069E430::Obj_0069E430(const char* name)
{
    unknown_14 = DAT_0083F870;
    ++DAT_0083F870;
    unknown_08 = _strdup(name);
    unknown_10 = 0;
    unknown_0C = 0;
    unknown_02 = 0;
    unknown_04 = 0;
    unknown_06 = 0;
    CCFileClass file(unknown_08);
    if (file.Exists(false))
        file.ReadBytes(this, 8);
    // Retail evaluates this comparison and discards its result.
    _stricmp(unknown_08, STR_0083F874);
    unknown_00 = 0xFFFF;
    unknown_18 = DAT_00B077B0;
    unknown_1C = 0;
    if (DAT_00B077B0)
        DAT_00B077B0->unknown_1C = this;
    DAT_00B077B0 = this;
    unknown_20 = 0;
}
