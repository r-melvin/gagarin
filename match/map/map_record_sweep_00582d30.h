// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Entry evidence:
// ev_c1fef0018070920fcd14be8f6785a552d4f8c9e7aed04cefbb1e880434e01666.
#ifndef GG_MAP_RECORD_SWEEP_00582D30_H
#define GG_MAP_RECORD_SWEEP_00582D30_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct MapRecordView_00582D30 {
    char unknown_00[8];
    char active;
    char unknown_09[7];
};
GG_STATIC_ASSERT(offsetof(MapRecordView_00582D30, active) == 0x08);
GG_STATIC_ASSERT(sizeof(MapRecordView_00582D30) == 0x10);

struct MapRecordSweepPrefix_00582D30 {
    char unknown_000[0x54];
    MapRecordView_00582D30* records;
    char unknown_058[8];
    int recordCount;

    // FUNCTION: GAMEMD 0x582D70 (decl; reloc); thiscall with record and int; callee RET 8.
    void FUN_00582D70(MapRecordView_00582D30* record, int argument);
    void FUN_00582D30(int argument);
};
GG_STATIC_ASSERT(offsetof(MapRecordSweepPrefix_00582D30, records) == 0x54);
GG_STATIC_ASSERT(offsetof(MapRecordSweepPrefix_00582D30, recordCount) == 0x60);
GG_STATIC_ASSERT(sizeof(MapRecordSweepPrefix_00582D30) == 0x64);
#endif
