// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; partial address-local ABI view for the capped 0x55A910 body.
// Address-local ABI view retained only for the capped 0x55A910 body.
#include "locomotion_class_iloco_methods.h"

// FUNCTION: GAMEMD 0x55A910  PowerOffView_0055A910::PowerOff (__stdcall, ret 0x4)
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
bool __stdcall PowerOffView_0055A910::PowerOff()
{
    Powered = false;
    return IsPowered();
}
