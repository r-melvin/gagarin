// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4733A0.

#include "techno_class_passenger_methods.h"

// Inferred *inline* helper: "is this object a FootClass?". Its shape is fixed by
// the bytes at every one of the three test sites — `TEST reg,reg; JZ` (the null
// guard), then `MOV CL,[reg+0x14]; SHR CL,2; AND CL,1` (the bit-field read),
// then `MOV byte ptr [ESP+0xC],CL; JZ`. That byte store into the dead argument
// home slot is the return-value temporary of an inlined bool function with two
// `return`s; a plain bit test in a condition (`flags & 4`, a bool local, a
// one-return accessor, a `bool` bit-field) all fold to `TEST byte ptr,4` and
// never spill. Only this two-return form reproduces the spill.
static inline bool IsFootObj(PassengerObj* o)
{
    if (o == 0)
        return false;
    return o->IsFoot;
}

// FUNCTION: GAMEMD 0x4733A0
//
// Limbo the incoming passenger, then splice it in at the head: if it already
// trails a chain of foot passengers, walk to that chain's tail and hang the
// old first passenger off it; otherwise hang the old first passenger directly
// off the newcomer. Finally recount from the new head while the links are
// still foot objects.
//
// Every cast site is written as a *re-read* of the member (`x->NextObject`)
// rather than through a local: VC6 CSEs the reload and, unlike a variable it
// has already seen null-tested inside the helper, does not fold the second
// null test away. Retail has all three (null / bit / null) at each site.
//
// The chain walk is a top-tested `while (tail != 0)` over a cursor that is
// either the checked-cast next link or null: `tail = 0` on a failed cast
// (the null-safe cast's rejecting arm) lets VC6 thread the bit-test failure
// straight to the fallback link, the `break` on a null next link lands on
// retail's post-loop `TEST EAX,EAX; JZ`, and the loop closes with
// `MOV EAX,ECX; TEST EAX,EAX; JZ; JMP top` exactly. A do/while with the same
// tests, or a `for (;;)` with `tail = 0; break;`, rotates the exit test to
// the bottom (one `JMP` short, one `MOV/TEST/JNE` long, 15.3%).
void PassengerList::AddPassenger(PassengerObj* passenger)
{
    if (passenger == 0)
        return;
    (passenger->*(*(PassengerVtbl**)passenger)->Limbo)();

    PassengerFoot* tail = 0;
    if (IsFootObj(passenger->NextObject) && passenger->NextObject != 0)
        tail = (PassengerFoot*)passenger->NextObject;
    while (tail != 0) {
        if (tail->NextObject == 0)
            break;
        if (IsFootObj(tail->NextObject) && tail->NextObject != 0)
            tail = (PassengerFoot*)tail->NextObject;
        else
            tail = 0;
    }
    if (tail != 0)
        tail->NextObject = this->FirstPassenger;
    else
        passenger->NextObject = this->FirstPassenger;

    this->FirstPassenger = passenger;
    this->NumPassengers = 0;
    do
    {
        this->NumPassengers = this->NumPassengers + 1;
        if (!IsFootObj(passenger->NextObject))
            break;
        passenger = passenger->NextObject;
    }
    while (passenger != 0);
}
