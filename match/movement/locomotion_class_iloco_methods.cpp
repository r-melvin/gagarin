// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55A710 / 0x55A910 /
//   0x55A930 / 0x55A940 / 0x55ABA0 / 0x55ABB0 / 0x55AD00 via the local Ghidra
//   disassembly. Slots and offsets confirmed (see the header).
//
// LocomotionClass — the shared ILocomotion defaults that every concrete
// locomotor inherits unless it overrides them. Functions ordered ascending by
// retail address.

#include "locomotion_class_iloco_methods.h"

// FUNCTION: GAMEMD 0x55A710  LocomotionClass::LinkToObject (__stdcall, ret 0x8)
// ILocomotion slot 3. Binds the locomotor to its FootClass; both the owner and
// the link start out as the same object.
long __stdcall LocomotionClass::LinkToObject(FootClass* object)
{
    LinkedTo = object;
    Owner = object;
    return 0;                       // S_OK
}

// FUNCTION: GAMEMD 0x55A910  LocomotionClass::PowerOff (__stdcall, ret 0x4)
// ILocomotion slot 23. Drops the powered flag and reports the new state back
// through the vtable (`CALL [ECX+0x60]` — slot 24, IsPowered), so an override
// that redefines "powered" still gets the last word.
//
// PARTIAL 66.7% (4/6 instructions). Semantics, both operands and the vtable
// slot are exact; only two adjacent instructions are swapped — retail is
// `MOV byte [EAX+0xC],0; MOV ECX,[EAX]` and VC6 emits `MOV ECX,[EAX];
// MOV byte [EAX+0xC],0`, i.e. it hoists the vptr load above the flag store.
// Pure scheduling, not semantics. Ruled out as causes: compiler build (this TU
// is compiled by the retail-matching SP3 c2.dll build 8447), instruction
// tuning (/G3 /G4 /G5 /G6 all identical or worse), and phrasing (local temp,
// explicit `this->`, `= 0`, guarded store, `volatile` store, and an empty
// `_asm` barrier — best of those was still 66.7%, several far worse). Treated
// as a documented partial rather than papered over with a naked-asm body.
bool __stdcall LocomotionClass::PowerOff()
{
    Powered = false;
    return IsPowered();
}

// FUNCTION: GAMEMD 0x55A930  LocomotionClass::IsPowered (__stdcall, ret 0x4)
// ILocomotion slot 24.
bool __stdcall LocomotionClass::IsPowered()
{
    return Powered;
}

// FUNCTION: GAMEMD 0x55A940  LocomotionClass::IsIonSensitive (__stdcall, ret 0x4)
// ILocomotion slot 25. Base locomotors ignore the ion storm.
bool __stdcall LocomotionClass::IsIonSensitive()
{
    return false;
}

// FUNCTION: GAMEMD 0x55ABA0  LocomotionClass::ZAdjust (__stdcall, ret 0x4)
// ILocomotion slot 14. No vertical draw offset by default.
int __stdcall LocomotionClass::ZAdjust()
{
    return 0;
}

// FUNCTION: GAMEMD 0x55ABB0  LocomotionClass::ZGradient (__stdcall, ret 0x4)
// ILocomotion slot 15. The default gradient constant is 2.
int __stdcall LocomotionClass::ZGradient()
{
    return 2;
}

// FUNCTION: GAMEMD 0x55AD00  LocomotionClass::CanFire (__stdcall, ret 0x4)
// ILocomotion slot 35. Returns FireError 0 — the locomotor never blocks firing.
int __stdcall LocomotionClass::CanFire()
{
    return 0;
}
