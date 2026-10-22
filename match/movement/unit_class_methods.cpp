// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70FBD0  UnitClass::IsDeactivated (__thiscall)
//   FUNCTION: GAMEMD 0x740DF0  UnitClass::FlagAttach    (__thiscall)
//   FUNCTION: GAMEMD 0x740E20  UnitClass::FlagRemove    (__thiscall)

#include "unit_class_methods.h"

// Mark() is ObjectClass's virtual at primary-vtable slot +0x124 (a one-arg
// __thiscall: ECX=this, the MarkType pushed). Retail emits the lean indirect
// `MOV EAX,[ECX]; PUSH 2; CALL [EAX+0x124]`. The layout spine models the object's
// vptrs as explicit DWORD fields (no C++ vtable), so a normal member call can't
// reach that slot. A __fastcall fn-pointer can't express the one-stack-arg
// __thiscall either (its 2nd arg would land in EDX). So we reinterpret `this`
// (offset 0 = the primary vptr) through a thin interface whose 74th virtual lands
// at vtable offset 0x124, and let VC6 emit the exact indirect call. The cast is a
// no-op (offset 0); no extra instruction is generated.
struct MarkInterface
{
#define GG_VPAD(n) virtual void gg_vslot##n() = 0;
    GG_VPAD(00) GG_VPAD(01) GG_VPAD(02) GG_VPAD(03) GG_VPAD(04) GG_VPAD(05) GG_VPAD(06)
    GG_VPAD(07) GG_VPAD(08) GG_VPAD(09) GG_VPAD(10) GG_VPAD(11) GG_VPAD(12) GG_VPAD(13)
    GG_VPAD(14) GG_VPAD(15) GG_VPAD(16) GG_VPAD(17) GG_VPAD(18) GG_VPAD(19) GG_VPAD(20)
    GG_VPAD(21) GG_VPAD(22) GG_VPAD(23) GG_VPAD(24) GG_VPAD(25) GG_VPAD(26) GG_VPAD(27)
    GG_VPAD(28) GG_VPAD(29) GG_VPAD(30) GG_VPAD(31) GG_VPAD(32) GG_VPAD(33) GG_VPAD(34)
    GG_VPAD(35) GG_VPAD(36) GG_VPAD(37) GG_VPAD(38) GG_VPAD(39) GG_VPAD(40) GG_VPAD(41)
    GG_VPAD(42) GG_VPAD(43) GG_VPAD(44) GG_VPAD(45) GG_VPAD(46) GG_VPAD(47) GG_VPAD(48)
    GG_VPAD(49) GG_VPAD(50) GG_VPAD(51) GG_VPAD(52) GG_VPAD(53) GG_VPAD(54) GG_VPAD(55)
    GG_VPAD(56) GG_VPAD(57) GG_VPAD(58) GG_VPAD(59) GG_VPAD(60) GG_VPAD(61) GG_VPAD(62)
    GG_VPAD(63) GG_VPAD(64) GG_VPAD(65) GG_VPAD(66) GG_VPAD(67) GG_VPAD(68) GG_VPAD(69)
    GG_VPAD(70) GG_VPAD(71) GG_VPAD(72)
#undef GG_VPAD
    virtual int Mark(int value) = 0;   // index 73 -> vtable offset 0x124
};

// FUNCTION: GAMEMD 0x70FBD0  (__thiscall)
// Retail loads the raw bool byte straight into AL with no 0/1 normalisation, so
// read it as a bool lvalue (`mov al,[ecx+0x1c8]; ret`), not via the unsigned-char
// member (which would force a `test`/`setne`).
bool UnitClass::IsDeactivated() const
{
    return *(const bool*)&Deactivated;
}

// FUNCTION: GAMEMD 0x740DF0  (__thiscall)
// Bind this unit to a house's flag (capture-the-flag). Only succeeds when a real
// house is given and no flag is already attached; then redraw and report true.
bool UnitClass::FlagAttach(int houseIndex)
{
    if (houseIndex != -1 && FlagHouseIndex == -1)
    {
        FlagHouseIndex = houseIndex;
        ((MarkInterface*)this)->Mark(2);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x740E20  (__thiscall)
// Detach the flag this unit was carrying, if any; redraw and report true.
bool UnitClass::FlagRemove()
{
    if (FlagHouseIndex != -1)
    {
        FlagHouseIndex = -1;
        ((MarkInterface*)this)->Mark(2);
        return true;
    }
    return false;
}
