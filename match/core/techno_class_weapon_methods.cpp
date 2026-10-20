// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm
//   0x70E1A0-0x70E1D7 len 0x38, 0x710550-0x710583 len 0x34). Names
//   cross-checked against YRpp TechnoClass.h / TechnoTypeClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70E1A0  TechnoClass::GetPrimaryWeapon       (__thiscall)
//   FUNCTION: GAMEMD 0x710550  TechnoClass::SetTargetForPassengers (__thiscall)
//
// Both bodies are virtual-dispatch heavy (slots +0x84, +0x3C8, +0x3F8). The
// dispatches are written as ordinary member-pointer calls through a modelled
// vtable struct, which is what emits retail's `MOV reg,[this]; CALL [reg+slot]`
// pair; the two direct calls carry their receiver in ECX and so are declared as
// members of their own classes.

#include "techno_class_weapon_methods.h"

// FUNCTION: GAMEMD 0x70E1A0  (__thiscall)
// The weapon a turreted unit is currently aiming with, or weapon zero for
// everything else.
//
// Retail has the GetWeapon dispatch twice, which reads as two call sites and is
// not: the source selects the index on the two arms of one test and calls once,
// and cl duplicates the short tail into both arms. Spelled as two returns the
// else arm folds its index to `PUSH 0` where retail materialises it with
// `XOR EAX,EAX; PUSH EAX` (68.2%); with one call and an else-assignment the
// index is a live variable in EAX on both paths, which is retail exactly.
// The index also has to be a named local rather than the member expression, or
// cl hoists the vtable load above it (40.9%).
WeaponStruct* TechnoClass::GetPrimaryWeapon()
{
    int weaponIndex;

    if ((this->*this->Vfptr->At_84)()->HasTurret()) {
        weaponIndex = this->CurrentWeaponNumber;
    } else {
        weaponIndex = 0;
    }
    return (this->*this->Vfptr->At_3F8)(weaponIndex);
}

// FUNCTION: GAMEMD 0x710550  (__thiscall)
// Hand a new target to every occupant of the transport. The walk stops at the
// end of the chain, and also as soon as a link turns up without the abstract
// flag bit that marks it as a live in-transport object.
//
// The loop has to be top-tested with the continuation condition negated into an
// early return. A `do`/`while` with the same condition as the latch peels the
// first iteration (51.9%) or, with the null test folded into the latch, leaves
// cl shrink-wrapping the EDI save into the loop arm where retail saves it in
// the prologue (70.0%). Hoisting the target copy above the list read, using the
// parameter directly, and a `for` over the link all hold 70.0%; a `for` with
// the lookahead in the body is 63.6%.
void TechnoClass::SetTargetForPassengers(AbstractClass* target)
{
    FootClass* passenger = this->Passengers.GetFirstPassenger();
    AbstractClass* newTarget = target;

    while (passenger != 0) {
        (passenger->*passenger->Vfptr->At_3C8)(newTarget);
        passenger = passenger->NextObject;
        if (passenger == 0 || (passenger->AbstractFlags & 4) == 0) {
            return;
        }
    }
}
