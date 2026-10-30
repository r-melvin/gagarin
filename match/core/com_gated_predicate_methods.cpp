// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41B920 and 0x41B980.

#include "com_gated_predicate_methods.h"
#include "../_layout/aircraft_class.h"
#include "../movement/loco_interfaces.h"
#include <comip.h>

GG_STATIC_ASSERT(offsetof(AircraftClass, Type) == 0x6C4);
GG_STATIC_ASSERT(offsetof(FootClass, Locomotor) == 0x674);
GG_STATIC_ASSERT(sizeof(((AircraftClass*)0)->Type) == 4);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->Locomotor) == 4);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->V3RocketType) == 4);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->DMislType) == 4);

// FUNCTION: GAMEMD 0x41B920
//
// Both `JZ`s jump into the interface block, so the two accepted types are the
// positive case and the fallback call is the fall-through - written as the
// negated guard with an early return, which is what puts the fallback first.
//
// The member read comes before the global read, and that order is load-bearing:
// declaring `rules` first lets VC6 hoist `MOV EAX,[0x8871E0]` above `PUSH ESI`
// and shift the entire function by one instruction. Touching `this` first
// anchors the prologue where retail has it.
//
// The interface pointer is loaded twice: once to test, once to call. That is
// the smart-pointer dereference inlined, not a redundant read, and writing it
// as a single held local costs the second load.
int AircraftClass_0041B920::FUN_0041B920()
{
    AircraftTypeClass* type = TypeIndex;
    RulesClass* rules = RulesInstance;

    if (type != rules->V3RocketType && type != rules->DMislType) {
        return FUN_004DE620();
    }

    if (Interface == 0) {
        FUN_007DC720(0x80004003);
    }

    return IFACE_CALL0B(Interface, 0x80) != 0;
}

// FUNCTION: GAMEMD 0x41B980
//
// The same shape with the other fallback and the answer inverted: retail's
// `INC EAX` after the `SBB` is `== 0` where the sibling's `NEG EAX` is `!= 0`.
bool AircraftClass::IsOnFloor() const
{
    AircraftTypeClass* type = Type;
    RulesClass* rules = RulesInstance;

    if (type != rules->V3RocketType && type != rules->DMislType) {
        return ObjectClass::IsOnFloor();
    }

    if (Locomotor == 0) {
        _com_issue_error(E_POINTER);
    }

    return static_cast<ILocomotion*>(Locomotor)->IsMovingNow() == 0;
}
