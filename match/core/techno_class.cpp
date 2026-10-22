// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (consult-only, no LICENSE; each
//   offset/slot reconfirmed against the binary in techno_class.h).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x473430   PassengersClass::RemoveFirstPassenger (__thiscall)
//   FUNCTION: GAMEMD 0x473460   PassengersClass::GetTotalSize         (__thiscall)
//   FUNCTION: GAMEMD 0x4734B0   PassengersClass::RemovePassenger      (__thiscall)
//   FUNCTION: GAMEMD 0x473500   PassengersClass::IndexOf              (__thiscall)
//   FUNCTION: GAMEMD 0x4598A0   TechnoClass::IsAbsorbAllowed          (__thiscall)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol  (CRT double->long; excluded from target)

#include "techno_class.h"

// FUNCTION: GAMEMD 0x473430  (__thiscall)
// Detach and return the head of the passenger list (clearing its NextObject).
FootClass* PassengersClass::RemoveFirstPassenger()
{
    FootClass* first = this->FirstPassenger;
    if (first == NULL) {
        return first;
    }
    this->FirstPassenger = first->NextObject;
    first->NextObject = NULL;
    --this->NumPassengers;
    return first;
}

// FUNCTION: GAMEMD 0x473460  (__thiscall)
// Sum (int-truncated) of GetTechnoType()->Size over up to NumPassengers nodes.
int PassengersClass::GetTotalSize() const
{
    int total = 0;
    int count = this->NumPassengers;
    if (this->FirstPassenger != NULL) {
        FootClass* cur = this->FirstPassenger;
        if (cur != NULL) {
            for (int i = 0; i < count; ++i) {
                if (cur == NULL) {
                    break;
                }
                total = (int)(total + cur->GetTechnoType()->Size);
                cur = cur->NextObject;
            }
        }
    }
    return total;
}

// FUNCTION: GAMEMD 0x4734B0  (__thiscall)
// Unlink pPassenger from the singly linked passenger list.
//
// PARTIAL: written as an ordinary cursor advance. An earlier permuter-found
// pointer alias on the lookahead reached 34/34 only by steering register
// choice; it was removed as match steering and the remaining one-instruction
// difference (retail re-bases the next-link load on the new cursor) is
// accepted.
void PassengersClass::RemovePassenger(FootClass* pPassenger)
{
    FootClass* pCur;
    if (pPassenger != NULL && (pCur = this->FirstPassenger, pCur != NULL)) {
        FootClass* pNext = pCur->NextObject;
        if (pCur == pPassenger) {
            this->FirstPassenger = pNext;
            --this->NumPassengers;
            return;
        }
        while (pNext != NULL) {
            if (pPassenger == pNext) {
                pCur->NextObject = pCur->NextObject->NextObject;
                --this->NumPassengers;
                return;
            }
            pCur = pNext;
            pNext = pCur->NextObject;
        }
    }
}

// FUNCTION: GAMEMD 0x473500  (__thiscall)
// 1-based position of `candidate` in the passenger list, or 0 if not found.
// A link that has lost the in-transport flag ends the walk with no answer.
//
// The loop is a top-tested `while (1)`: retail increments at the top and
// closes with an unconditional back jump, and every rotated spelling -- `for`,
// a bottom-tested `do`/`while`, nested ifs, and five variations on a
// fully spelled-out goto skeleton -- sits at 8.3%, because cl peels the first
// increment and inverts the latch. The second half of the lever is the single
// exit: the flag-failure path clears the cursor and breaks rather than
// returning, so the zeroing and the `POP ESI; RET 4` are reached from every
// path, which is what keeps the cold block where retail has it. Earlier passes
// measured the peeled `while (1)` at 16.0% and an early return at 3.8%; both
// were missing this half.
int PassengersClass::IndexOf(FootClass* candidate) const
{
    FootClass* cur = this->FirstPassenger;
    int index = 0;

    if (cur != 0) {
        FootClass* target = candidate;

        while (1) {
            ++index;
            if (cur == target) {
                break;
            }

            FootClass* next = cur->NextObject;

            if (next != 0) {
                if ((next->Field14 & 4) == 0) {
                    cur = 0;
                    break;
                }
                cur = next;
            }
            if (cur == 0) {
                break;
            }
        }
    }
    if (cur == 0) {
        index = 0;
    }
    return index;
}

// FUNCTION: GAMEMD 0x4598A0  (__thiscall)
// True when either absorb flag byte on the object's type is set.
bool TechnoClass::IsAbsorbAllowed() const
{
    return this->Type->unknown_byte_16AE != 0 || this->Type->unknown_byte_16AF != 0;
}
