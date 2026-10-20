// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001, evidence IDs are in
// map_iterator_helpers_00578350.h. Bodies are translated from validated
// entry ranges.
#include "map_iterator_helpers_00578350.h"

// FUNCTION: GAMEMD 0x578350
void MapIterator_00578350::FUN_00578350()
{
    int count = cellCount;
    iterState = 1;
    iterCount = count;
    iterLast = count - 1;
    iterCursor = cellBase + count * 0x800 + 4;
}

// FUNCTION: GAMEMD 0x578850
void MapIterator_00578350::FUN_00578850()
{
    iterNext = stepBase + stepOffset + 1;
    iterLimit = cellCount - stepBase + stepOffset;
}

// FUNCTION: GAMEMD 0x578AC0
void ScreenRedraw_00578AC0::FUN_00578AC0()
{
    ++redrawCounter;
}

// FUNCTION: GAMEMD 0x578D60
unsigned char __fastcall FUN_00578D60(int value)
{
    int first = DAT_00ABAD28;
    if (value >= first && value < first + 0x2A) return 1;
    return 0;
}
