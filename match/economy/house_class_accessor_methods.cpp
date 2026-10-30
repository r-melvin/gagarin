// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F9950 / 0x4F9B50 /
//   0x50B730 / 0x50BD10 / 0x50D9E0 / 0x50D9F0 / 0x50E1B0 via the local Ghidra
//   disassembly. Member offsets confirmed numerically (see the header).
//
// HouseClass accessor leaves. Functions ordered ascending by retail address.

#include "house_class_accessor_methods.h"


// FUNCTION: GAMEMD 0x50B730  HouseClass::IsControlledByHuman (__thiscall)
// Outside a campaign only the explicit human-player flag counts; inside one, a
// house the player has been handed control of counts too.
//
// Phrasing is load-bearing here. The GameMode test has to come first so VC6
// reads the global into EAX and schedules `MOV AL,[ECX+0x1EC]` *between* the
// TEST and the JNZ (retail's exact sequence); leading with the flag instead puts
// the global in EDX. The second half has to stay `result = result || ...` rather
// than `return a || b`, because the assignment form materialises the bool in AL
// (`XOR AL,AL` / `MOV AL,1`) while the return-expression form widens to EAX.
bool HouseClass::IsControlledByHuman() const
{
    if (Session_00A8B238.GameMode != 0) {          // anything but GameMode::Campaign
        return IsHumanPlayer;
    }
    bool result = IsHumanPlayer;
    result = result || IsInPlayerControl;
    return result;
}

