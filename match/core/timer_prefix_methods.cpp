// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "triple_timer_init_methods.h"
#include "../audio/audio_time_methods.h"

// FUNCTION: GAMEMD 0x407150
unsigned FUN_00407150(Timer_00401000* timer, int value)
{
    timer->Flags32 |= 1;
    timer->Target = value << 16;
    return timer->Flags32;
}
// FUNCTION: GAMEMD 0x407170
unsigned FUN_00407170(Timer_00401000* timer, int value)
{
    timer->Flags32 &= ~1;
    unsigned result = timer->Target;
    if (result == timer->Value) {
        __int64 reading = Unsorted_AudioGetTime();
        timer->unknown_18 = reading;
        result = (unsigned)reading;
    }
    timer->Target = value << 16;
    return result;
}

// FUNCTION: GAMEMD 0x4072B0
unsigned FUN_004072B0(Timer_00401000* timer)
{
    return timer->Target >> 16;
}
