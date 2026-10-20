// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: original
//
// Calling a deep vtable slot that takes stack arguments.
//
// RA2's classes have vtables hundreds of slots deep, and most of those slots are
// __thiscall with arguments on the stack — `MOV EAX,[ESI]; PUSH b; PUSH a;
// CALL DWORD PTR [EAX+0x1E8]`. Neither of the obvious modelling choices
// reproduces that:
//
//   * A `__fastcall` function-pointer through a vtable struct (the idiom already
//     used in this tree for zero-argument slots) puts the first real argument in
//     EDX, so it emits a register load retail does not have.
//   * Declaring the class with enough `virtual` members to place the slot needs
//     hundreds of dummy declarations per class.
//
// What does work is typing the vtable slot as a *pointer to member function* of
// the owning class. VC6 then emits the memory-indirect call directly and passes
// the receiver in ECX with the arguments pushed — byte-identical to retail.
//
// One ordering rule makes or breaks it: the owning class must be a COMPLETE type
// before the member-function-pointer type is declared. Against a
// forward-declared class VC6 falls back to the generalised multiple-inheritance
// representation, an 8-byte pointer carrying a `this` adjustment, and emits
// `MOV ECX,[EDX+slot+4]; ADD ECX,EAX` before the call. Against a complete
// single-inheritance class it uses the 4-byte form and the adjustment vanishes.
//
// So the declaration order in a header using this is always:
//
//     struct Vtbl_XXX;                                  // forward
//     struct Obj_XXX { Vtbl_XXX* Vtbl; ... };           // complete
//     typedef int (Obj_XXX::*Fn_XXX)(int, int);         // now 4 bytes
//     struct Vtbl_XXX { char _pad[0x1E8]; Fn_XXX At_1E8; };
//
// and the call site is `(self->*self->Vtbl->At_1E8)(a, b);`.
#ifndef GG_MATCH_RT_GG_VSLOT_H
#define GG_MATCH_RT_GG_VSLOT_H
#endif  // GG_MATCH_RT_GG_VSLOT_H
