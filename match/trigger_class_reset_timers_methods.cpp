// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x726400.

#include "trigger_class_reset_timers_methods.h"

// FUNCTION: GAMEMD 0x726400
//
// Re-arm the trigger's timed events. Walking the type's event list with a
// running bit index, an elapsed-time event (13) rewinds the timer to its value
// in seconds (15 frames each) and a random-delay event (51) to half its value
// plus a random draw up to the value; either clears that event's bit in the
// occurred mask. Both kinds are tested independently, so the second test is
// evaluated even after the first matched.
// PARTIAL (73.5%; multiset identical, 68 vs 68).
// Retail loads the scenario pointer into a scratch register and forms the
// randomizer's sub-object address non-destructively with `LEA ECX,[EAX+0x218]`;
// calling through the member expression makes cl load the global straight into
// ECX and destroy it with `ADD ECX,0x218`. Binding the address to a local
// (`Random_00726400* rnd = &DAT_00A8B230->unknown_0218;`) gets 95.6%, but the local
// is a redundant alias that only steers the register allocator, so it is not
// used. Other spellings measured: the event value hoisted to a local 76.5%, a
// scenario pointer local 69.1%, the sum written without a `delay` local
// 22.1-23.5%.
//
// Retail also reads `event->Value` into EAX and pushes it BEFORE loading the
// scenario global; cl loads the global first and pushes the value out of EDX.
void TriggerClass::ResetTimers()
{
    int index = 0;

    for (TEvent_00726400* event = reinterpret_cast<TriggerType_00726400*>(this->Type)->FirstEvent; event != 0; event = event->NextEvent) {
        if (event->EventKind == 13) {
            this->Timer = CDTimer_00726400(event->Value * 15);
            this->OccuredEvents &= ~(1 << index);
        }
        if (event->EventKind == 51) {
            int delay = DAT_00A8B230->unknown_0218.RandomRanged(0, event->Value);
            int total = event->Value / 2 + delay;
            this->Timer = CDTimer_00726400(total * 15);
            this->OccuredEvents &= ~(1 << index);
        }
        ++index;
    }
}
