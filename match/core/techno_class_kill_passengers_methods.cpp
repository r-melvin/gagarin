// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x707CB0.

#include "techno_class_kill_passengers_methods.h"

// FUNCTION: GAMEMD 0x707CB0  TechnoClass::KillPassengers (__thiscall, ret 0x4)
// Empty a transport by killing everything inside it. Each passenger is first
// released from its team, then unlinked, then recursively emptied itself — a
// transport carrying a transport unwinds all the way down — before being
// destroyed through its own two virtuals.
//
// The empty check is hoisted out and the body is a do/while: retail tests
// NumPassengers once up front and again at the bottom of the loop, with the
// loop head at the GetFirstPassenger call rather than at the test.
void TechnoClass::KillPassengers(TechnoClass* source)
{
    if (Passengers.NumPassengers == 0)
        return;

    do
    {
        FootClass* first = Passengers.GetFirstPassenger();
        if (first->Team != 0)
            first->Team->LiberateMember(first, -1, 0);

        FootClass* passenger = Passengers.RemoveFirstPassenger();
        if (passenger != 0)
        {
            // Retail passes the passenger itself here, not `source`
            // (`PUSH ESI; MOV ECX,ESI; CALL 0x707CB0`); only the outer
            // virtual at +0xE0 receives the original killer.
            ((TechnoClass*)passenger)->KillPassengers((TechnoClass*)passenger);
            passenger->Slot_E0(source);
            passenger->Slot_F8();
        }
    }
    while (Passengers.NumPassengers != 0);
}

// The null-safe FootClass cast retail inlined at the loop's back edge: null
// stays null, anything without the AbstractClass foot bit (+0x14, mask 4)
// becomes null, so the walk stops at the first non-foot link. Written as a
// ternary the `object != 0` test lands as `CMP EAX,ECX; JZ ret` and the flag
// test as `TEST byte ptr [EAX+0x14],DL` (0x7104E0..0x7104E7).
static __inline FootClass* foot_cast_007104C0(void* object)
{
    return (object != 0 && (((FootClass*)object)->unknown_14 & 4) != 0)
               ? (FootClass*)object
               : 0;
}

// FUNCTION: GAMEMD 0x7104C0  TechnoClass::MarkPassengersAsExited (__thiscall)
// Walk the cargo chain clearing the open-topped flag, stopping at the first
// link that is not a foot-class object (the +0x14 flag word, mask 4). The chain
// is the shared object list, so the type test is what bounds it.
//
// The loop is a top-tested `while (passenger != 0)` whose body guards the
// store with its own `if (passenger != 0)` and advances through the checked
// cast. Retail keeps the body's guard (`CMP EAX,ECX; JZ 0x7104DD`) even
// though the cast has just proved it; VC6 keeps it too once the advance is
// the ternary cast above — the earlier do/while spellings with the null test
// in the loop condition let the optimiser delete it (33.3%).
void TechnoClass::MarkPassengersAsExited()
{
    FootClass* passenger = Passengers.GetFirstPassenger();
    while (passenger != 0)
    {
        if (passenger != 0)
            passenger->InOpenToppedTransport = false;
        passenger = foot_cast_007104C0(passenger->NextObject);
    }
}
