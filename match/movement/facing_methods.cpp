// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4C9480  FacingClass::IsRotating    (__thiscall)
//   FUNCTION: GAMEMD 0x4C94B0  FacingClass::IsRotatingCW  (__thiscall)
//   FUNCTION: GAMEMD 0x4C94F0  FacingClass::IsRotatingCCW (__thiscall)

#include "facing_methods.h"

// FUNCTION: GAMEMD 0x4C9480  (__thiscall)
// Rotating == the rate-of-turn is positive AND the count-down timer still has
// frames left.
bool FacingClass::IsRotating() const
{
    return (short)ROT.Raw > 0 && RotationTimer.GetTimeLeft();
}

// FUNCTION: GAMEMD 0x4C94B0  (__thiscall)
// Clockwise == rotating, and the signed direction delta is strictly positive.
bool FacingClass::IsRotatingCW() const
{
    // IsRotating() is inlined by retail; expand it inline here so our /Ob1
    // build reproduces the branch sequence rather than emitting a CALL.
    if (!((short)ROT.Raw > 0 && RotationTimer.GetTimeLeft()))
        return false;
    return Difference() > 0;
}

// FUNCTION: GAMEMD 0x4C94F0  (__thiscall)
// Counter-clockwise == rotating, and the signed direction delta is strictly
// negative.
bool FacingClass::IsRotatingCCW() const
{
    if (!((short)ROT.Raw > 0 && RotationTimer.GetTimeLeft()))
        return false;
    return Difference() < 0;
}
