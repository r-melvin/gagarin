// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5896F0 and 0x5899E0. A table of
//   0x24-byte records (storage at +0x04, count at +0x08, enable flag at +0x0C) compared as a
//   whole and searched for a record by its word at +0x18 and dword at +0x1C.
//
// Address index: 0x5896F0 0x5899E0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TableRecord_005896F0
{
    char  unknown_00[0x18];
    short Key18;           // +0x18
    short unknown_1A;
    int   Key1C;           // +0x1C
    char  unknown_20[4];
};
GG_STATIC_ASSERT(offsetof(TableRecord_005896F0, Key18) == 0x18);
GG_STATIC_ASSERT(offsetof(TableRecord_005896F0, Key1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(TableRecord_005896F0) == 0x24);

struct RecordTable_005896F0
{
    int                   unknown_00;
    TableRecord_005896F0* Items;    // +0x04
    int                   Count;    // +0x08
    bool                  Enabled;  // +0x0C

    bool FUN_005896F0(const RecordTable_005896F0& other) const;
    int  FUN_005899E0(const TableRecord_005896F0* record) const;
};
GG_STATIC_ASSERT(offsetof(RecordTable_005896F0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RecordTable_005896F0, Count) == 0x08);
GG_STATIC_ASSERT(offsetof(RecordTable_005896F0, Enabled) == 0x0C);

// FUNCTION: GAMEMD 0x5896F0
// Same number of records, each with the same word and dword keys.
// PARTIAL (89.2%): identical instruction multiset; retail loads the other table's
// storage pointer before this table's, cl loads them the other way round. Tried:
// swapped operands, split conditions, explicit walking pointers.
bool RecordTable_005896F0::FUN_005896F0(const RecordTable_005896F0& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) {
            if (Items[i].Key18 != other.Items[i].Key18
                || Items[i].Key1C != other.Items[i].Key1C) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5899E0
// Index of the record with the given keys, or -1; zero when the table is disabled.
int RecordTable_005896F0::FUN_005899E0(const TableRecord_005896F0* record) const
{
    if (!Enabled) {
        return 0;
    }
    for (int i = 0; i < Count; ++i) {
        if (Items[i].Key18 == record->Key18 && Items[i].Key1C == record->Key1C) {
            return i;
        }
    }
    return -1;
}
