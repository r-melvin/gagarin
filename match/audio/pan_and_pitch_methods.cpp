// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40A6D0.

#include "pan_and_pitch_methods.h"

// FUNCTION: GAMEMD 0x40A6D0
//
// Push this voice's three continuous parameters down to the sink: volume from a
// 0..100 curve, pan from a curve indexed either side of its own base, and rate
// from the second timer scaled per hundred.
//
// PARTIAL (96.4%, 54/56) — identical multiset, one adjacent swap. Retail zeroes
// the return value before restoring EDI; VC6 puts the `XOR EAX,EAX` between the
// two pops. Naming the zero in a local before or after the last call makes no
// difference.
//
// The single-exit accumulator lever (declare the result above the test and
// assign the default on an else arm, which restores the entry save on the cold
// return block) was measured here and does not apply: there is no cold return
// block, the `XOR` is in the only epilogue, and five further spellings scored
// the same 96.4% in one compile — `int result = 0;` declared at the top and
// returned; the result assigned from the pan call on both arms of the
// `pan < 0` test and re-zeroed before the return; the result zeroed between
// the rate computation and the last call; the zero bound to a local after the
// last call; and a `volatile int zero = 0;` carrier, which is 3.4% (it homes
// the zero to the stack). None of these tested spellings reaches the interleave.
// A five-minute decomp-permuter run (four local workers, original body baseline
// validated through the VC6 adapter) also found no better candidate: score 220
// throughout. Keep the readable C++ partial; no assembly workaround is retained.
//
// The pan index is biased by 0x64 so it straddles zero, and the two halves are
// not symmetrical: a negative index reads the table below its base directly,
// while a positive one reads the same distance below and negates the result. That
// is why retail computes `0x816510 - index*4` by hand on the positive path
// instead of indexing forwards.
int Voice_0040A6D0::FUN_0040A6D0()
{
    Aux_0040A6D0* aux = this->Aux;

    aux->Sink->Vptr->At_3C(aux->Sink,
                           DAT_00816380[(this->Timers.First.Value >> 16) * 100 >> 14]);

    int pan = ((this->Timers.Third.Value >> 16) * 200 >> 14) - 0x64;
    if (pan < 0) {
        aux->Sink->Vptr->At_40(aux->Sink, DAT_00816510[pan]);
    } else {
        aux->Sink->Vptr->At_40(aux->Sink, -DAT_00816510[-pan]);
    }

    int rate = FUN_00401190(&this->Timers, aux->Settings->At_184);
    aux->Sink->Vptr->At_44(aux->Sink, rate);
    return 0;
}
