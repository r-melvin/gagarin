// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x6F6F40, read instruction by instruction from gamemd.exe v1.001: converts a record's
// value at +8 into tens of rules units.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Record_006F6F40 {
    unsigned char unknown_00[8];
    int unknown_08;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Record_006F6F40, unknown_08) == 0x8);


// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// FUNCTION: GAMEMD 0x6F6F40
int __stdcall FUN_006F6F40(Record_006F6F40* record)
{
    return record->unknown_08 / DAT_008871E0->LeptonsPerSightIncrease * 10;
}
