// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001, complete entry
// observations REA ev_86380bc90ec83ccd4917a7aa4329da4bbeb31a9a6622f3db6ead41fff4ed8859
// and ev_daf117f4f4a538e277f241285941c8833b9f3f7b120e786d55759f86109e75d2.
#ifndef GG_RECORD_LOOKUP_00589680_H
#define GG_RECORD_LOOKUP_00589680_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RecordEntry_00589680 {
    short key0; // +0x0
    short key1; // +0x2
    short key2; // +0x4
    short key3; // +0x6
    unsigned char value8; // +0x8
    char unknown_09[3];
    int unknown_0C; // +0xC
    RecordEntry_00589680* FUN_00589680();
};
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, key0) == 0x0);
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, key1) == 0x2);
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, key2) == 0x4);
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, key3) == 0x6);
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, value8) == 0x8);
GG_STATIC_ASSERT(offsetof(RecordEntry_00589680, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(RecordEntry_00589680) == 0x10);

struct RecordKey_005896A0 { short key0, key1, key2, key3; };
GG_STATIC_ASSERT(offsetof(RecordKey_005896A0, key0) == 0x0);
GG_STATIC_ASSERT(offsetof(RecordKey_005896A0, key1) == 0x2);
GG_STATIC_ASSERT(offsetof(RecordKey_005896A0, key2) == 0x4);
GG_STATIC_ASSERT(offsetof(RecordKey_005896A0, key3) == 0x6);
GG_STATIC_ASSERT(sizeof(RecordKey_005896A0) == 0x8);

struct RecordTable_005896A0 {
    char unknown_00[4];
    RecordEntry_00589680* entries; // +0x4
    char unknown_08[8];
    int count; // +0x10
    int FUN_005896A0(const RecordKey_005896A0* key);
};
GG_STATIC_ASSERT(offsetof(RecordTable_005896A0, entries) == 0x4);
GG_STATIC_ASSERT(offsetof(RecordTable_005896A0, count) == 0x10);
GG_STATIC_ASSERT(sizeof(RecordTable_005896A0) == 0x14);
#endif
