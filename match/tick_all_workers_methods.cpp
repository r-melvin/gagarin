// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x408270.

#include "tick_all_workers_methods.h"

// FUNCTION: GAMEMD 0x408270
//
// Walk the worker list once per frame. An entry that has never been ticked and
// has a worker attached gets kicked under the list's critical section; every
// entry's tick count is bumped whether it was kicked or not, so the kick
// happens exactly once per entry.
//
// PARTIAL (93.0%, 40/43). One register: retail bumps the tick count through
// EAX, VC6 through ECX. Instruction for instruction otherwise identical,
// including the reload of the count after the critical section rather than
// reusing the value the zero test read. Three phrasings of the increment
// (`x = x + 1`, `x++`, `++x`, and a local round-trip) all pick ECX, so the
// choice is not reachable from source — the register-naming class in section
// 4.8.
//
// PERMUTER FINDING (negative). decomp-permuter, base score 45 against a
// relocation floor of 30 (six relocated data operands), insertions =
// deletions = 0, so the whole delta is the three-instruction EAX/ECX triple.
// 127,088 candidates across two runs did not move it one point. The
// restart-from-best lever was not available here: the run never wrote a single
// improving candidate, which is itself the cleanest form of a flat negative. Seven further hand levers, one
// compile each: an `int*` alias on the count (the 0x43A600 lever), a double
// `int**` alias, a named copy, a double alias on the entry pointer, an
// `Entry_00408270**` alias on the receiver, a discarded-`0` comma (the 0x41C2E0
// lever) and `++entry->Ticks` -- all 93.0%, all byte-identical.
//
// The cause is legible and it is a NEW do-not-run sub-class: cl coalesces the
// increment's register with the `MOV ECX,ESI` it is about to emit for the
// following `__fastcall` advance at the bottom of the loop. The register is
// chosen by the call ABI, not by anything the increment's source can name,
// which is why no route-to-a-value lever reaches it. Record the class as "a
// register coalesced with a following fastcall receiver load".
//
// The requested bit is traded for the running bit rather than simply set, which
// is why the update is a mask-and-or on one read of the flags word.
void FUN_00408270()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    for (Entry_00408270* entry = FUN_004073C0(&DAT_0087E810); entry != 0;
         entry = FUN_004073E0(entry)) {

        if (entry->Ticks == 0 && entry->Worker != 0) {
            EnterCriticalSection(&DAT_0087E7F8);
            FUN_00402600(entry->Worker);
            if (entry->Flags & 1) {
                entry->Flags = entry->Flags & ~1 | 2;
            }
            LeaveCriticalSection(&DAT_0087E7F8);
        }

        entry->Ticks = entry->Ticks + 1;
    }
}
