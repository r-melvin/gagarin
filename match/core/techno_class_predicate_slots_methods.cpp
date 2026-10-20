// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm 0x6F7780
//   len 0x20, 0x7010D0 len 0x45, 0x701120 len 0x1A, 0x70C5A0 len 0xC,
//   0x70EFD0 len 0xE, 0x70F090 len 0x12, 0x70F850 len 0x33).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6F7780  TechnoClass::IsCloseEnoughToAttack  (__fastcall member)
//   FUNCTION: GAMEMD 0x7010D0  TechnoClass::IsGuardingWithLiveWeapon (__thiscall)
//   FUNCTION: GAMEMD 0x701120  TechnoClass::IsArmed                (__thiscall)
//   FUNCTION: GAMEMD 0x70C5A0  TechnoClass::IsCloakable            (__thiscall)
//   FUNCTION: GAMEMD 0x70EFD0  TechnoClass::IsUnderEMP             (__thiscall)
//   FUNCTION: GAMEMD 0x70F090  TechnoClass::CanAttackOnTheMove     (__thiscall)
//   FUNCTION: GAMEMD 0x70F850  TechnoClass::CancelAndGoIdle        (__thiscall)
//
// Seven adjacent TechnoClass virtual-slot bases. They share a receiver and a
// shape: read one member or one slot, and report a decision.

#include "techno_class_predicate_slots_methods.h"

// FUNCTION: GAMEMD 0x6F7780  (__thiscall)
// Is the target inside the range of the weapon this object would pick for it?
// One weapon selection feeding one range test, both on the same cached vtable.
bool TechnoClass::IsCloseEnoughToAttack(AbstractClass* target)
{
    return (this->*this->Vfptr->At_3A8)(target,
                                        (this->*this->Vfptr->At_2E4)(target));
}

// FUNCTION: GAMEMD 0x7010D0  (__thiscall)
// Is this object sitting on guard with a usable weapon, for the local player?
// Four gates: not switched off, owned by the house the human is playing,
// holding a turret weapon with a real WeaponType behind it, and not currently
// EMP-locked.
//
// The exit is `MOV AL,0x1` / `XOR AL,AL`, so the return type is bool.
//
// LEVER: the gates have to be NESTED with `return false` as the function's
// trailing fall-through, not written as four early `return false`s. Spelled as
// early returns the last gate folds into `TEST AL,AL; SETE AL` and the
// materialised `MOV AL,0x1` disappears (59.3%); inverting only the last gate
// does not help, because cl folds whichever negated test ends the function.
bool TechnoClass::IsGuardingWithLiveWeapon()
{
    if (!this->Deactivated) {
        if (this->Owner->IsControlledByCurrentPlayer()) {
            WeaponStruct* weapon = (this->*this->Vfptr->At_3F4)();
            if (weapon != 0 && weapon->WeaponType != 0) {
                if (!(this->*this->Vfptr->At_37C)()) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x701120  (__thiscall)
// Does this object have a weapon at all? The turret-weapon slot has to hand
// back a record, and the record has to name a WeaponType.
//
// The exit is `MOV EAX,0x1` / `XOR EAX,EAX` — five-byte immediate into the full
// register — so the return type is int, not bool. See the header note: the
// vtable map calls this slot `-> bool`, and the bytes say otherwise.
int TechnoClass::IsArmed()
{
    WeaponStruct* weapon = (this->*this->Vfptr->At_3F4)();

    if (weapon != 0 && weapon->WeaponType != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70C5A0  (__thiscall)
// Can this object cloak? The flag is a byte, and the `TEST AL,AL; SETNZ AL`
// normalisation is the char-to-bool conversion — a member already declared
// bool would return with a bare `MOV AL,[..]; RET`, which is exactly what the
// neighbouring accessor at 0x70C5B0 does.
//
// LEVER, measured over nine spellings in one probe compile: `return C != 0;`,
// the same through a named `unsigned char` local, a `char` member, an `int`
// member, and `char`/`int` return types ALL emit `MOV DL,[..]; XOR EAX,EAX;
// TEST DL,DL; SETNE AL` — five instructions against retail's four, because cl
// takes a fresh register and zeroes EAX. Only the two branching forms —
// `C ? true : false` and the explicit `if` below — reuse AL and reach retail's
// exact four. This is the concrete case behind the "never write
// `return a == b;`" rule: the bare comparison costs the zeroing instruction.
bool TechnoClass::IsCloakable()
{
    if (this->Cloakable) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x70EFD0  (__thiscall)
// Is an EMP still holding this object down? `SETG` is the signed test, so the
// remaining-lock counter is a signed int.
bool TechnoClass::IsUnderEMP()
{
    return this->EMPLockRemaining > 0;
}

// FUNCTION: GAMEMD 0x70F090  (__thiscall)
// Forwarded wholesale to the type: the object asks what it is, then asks the
// type whether that kind of thing may fire while moving. Retail tail-jumps
// (`JMP [EDX+0xa4]`) rather than calling, which is what cl emits when the
// dispatch is the whole return expression.
bool TechnoClass::CanAttackOnTheMove()
{
    TechnoTypeClass* type = (this->*this->Vfptr->At_84)();

    return (type->*type->Vfptr->At_A4)();
}

// FUNCTION: GAMEMD 0x70F850  (__thiscall)
// Drop everything and go idle: clear the movement destination, clear the combat
// target, forget the archived target, and force the object into mission 5.
void TechnoClass::CancelAndGoIdle()
{
    (this->*this->Vfptr->At_480)(0, true);
    (this->*this->Vfptr->At_3C8)(0);
    this->ArchiveTarget = 0;
    (this->*this->Vfptr->At_1F0)(5);
}
