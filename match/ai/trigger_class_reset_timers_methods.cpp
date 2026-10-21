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
// PARTIAL (95.6%, up from 73.5%; multiset identical, 68 vs 68).
// The lever: bind the randomizer's ADDRESS to a local
// (`Random_00726400* rnd = &DAT_00A8B230->Random;`) instead of calling
// through `DAT_00A8B230->Random.RandomRanged(...)`. Retail loads the scenario
// pointer into a scratch register and forms the sub-object address
// non-destructively with `LEA ECX,[EAX+0x218]`; calling through the member
// expression makes cl load the global straight into ECX and destroy it with
// `ADD ECX,0x218`. Measured across seven spellings of the same arm: the
// address local 95.6%, the event value hoisted to a local 76.5%, a scenario
// pointer local 69.1%, `(&DAT_00A8B230->Random)->RandomRanged(...)` written
// inline 73.5%, the sum written without a `delay` local 22.1-23.5%.
//
// Residual is three instructions of scheduling: retail reads `event->Value`
// into EAX and pushes it BEFORE loading the scenario global; cl loads the
// global first and pushes the value out of EDX. Naming the argument in a
// local ahead of the address local inverts it the wrong way (72.1-92.6%),
// and a volatile-qualified read of the global costs the LEA again (88.2%).
void TriggerClass::ResetTimers()
{
    int index = 0;

    for (TEvent_00726400* event = reinterpret_cast<TriggerType_00726400*>(this->Type)->FirstEvent; event != 0; event = event->NextEvent) {
        if (event->EventKind == 13) {
            this->Timer = CDTimer_00726400(event->Value * 15);
            this->OccuredEvents &= ~(1 << index);
        }
        if (event->EventKind == 51) {
            Random_00726400* rnd = &DAT_00A8B230->Random;
            int delay = rnd->RandomRanged(0, event->Value);
            int total = event->Value / 2 + delay;
            this->Timer = CDTimer_00726400(total * 15);
            this->OccuredEvents &= ~(1 << index);
        }
        ++index;
    }
}
