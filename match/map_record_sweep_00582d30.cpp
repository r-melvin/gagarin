// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Complete entry
// Evidence: ev_c1fef0018070920fcd14be8f6785a552d4f8c9e7aed04cefbb1e880434e01666.
#include "map_record_sweep_00582d30.h"

// FUNCTION: GAMEMD 0x582D30
void MapRecordSweepPrefix_00582D30::FUN_00582D30(int argument)
{
    for (int index = 0; index < recordCount; ++index) {
        MapRecordView_00582D30* record = records + index;
        if (record->active != 0) {
            FUN_00582D70(record, argument);
        }
    }
}
