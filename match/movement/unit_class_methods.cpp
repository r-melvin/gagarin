// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70FBD0  UnitClass::IsDeactivated (__thiscall)
//   FUNCTION: GAMEMD 0x740DF0  UnitClass::FlagAttach    (__thiscall)
//   FUNCTION: GAMEMD 0x740E20  UnitClass::FlagRemove    (__thiscall)

#include "../_layout/unit_class.h"

// The redraw is ObjectClass primary slot 73 (vtable offset 0x124), called with 2.
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
        vf_73(2);
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
        vf_73(2);
        return true;
    }
    return false;
}
