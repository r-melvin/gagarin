// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Raw instructions and
// ABI are recorded in the paired header's REA Evidence IDs.
#include "record_lookup_00589680.h"

// FUNCTION: GAMEMD 0x589680
RecordEntry_00589680* RecordEntry_00589680::FUN_00589680()
{
    key0 = 0;
    key1 = 0;
    key2 = 0;
    key3 = 0;
    value8 = 0;
    unknown_0C = -1;
    return this;
}

// FUNCTION: GAMEMD 0x5896A0
int RecordTable_005896A0::FUN_005896A0(const RecordKey_005896A0* key)
{
    for (int i = 0; i < count; ++i) {
        const RecordEntry_00589680* entry = entries + i;
        if (entry->key0 == key->key0 &&
            entry->key1 == key->key1 &&
            entry->key2 == key->key2 &&
            entry->key3 == key->key3) {
            return i;
        }
    }
    return -1;
}
