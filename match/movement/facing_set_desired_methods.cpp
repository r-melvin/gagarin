// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C9220.

#include <stdlib.h>   // abs (the /O2 intrinsic: CDQ; XOR; SUB)
#include "../_layout/facing_class.h"

// FUNCTION: GAMEMD 0x4C9220
//
// Start turning towards a new facing. A request for the facing already wanted
// is refused. Otherwise the rotation restarts from wherever the previous one
// had got to (Current() becomes StartFacing), the new target is recorded, and
// when a rate of turn is set the timer is restarted with the number of ROT
// steps between the two facings.
bool FacingClass::SetDesired(const DirStruct& facing)
{
    if (this->DesiredFacing.Raw != facing.Raw) {
        this->StartFacing = this->Current();
        this->DesiredFacing = facing;

        if ((short)this->ROT.Raw > 0) {
            short diff = (short)(this->DesiredFacing.Raw - this->StartFacing.Raw);
            this->RotationTimer = CDTimerClass(abs(diff) / (short)this->ROT.Raw);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4C93D0
// Four-byte direction value: copy the complete desired representation, adjust
// only its low direction word, and return through the caller's value slot.
DirStruct FacingClass::FUN_004C93D0() const
{
    if ((short)ROT.Raw > 0 && RotationTimer.GetTimeLeft() != 0) {
        short diff = (short)(DesiredFacing.Raw - StartFacing.Raw);
        short steps = (short)(abs(diff) / (short)ROT.Raw);
        DirStruct result = DesiredFacing;
        if (steps > 0) {
            result.Raw = (unsigned short)(result.Raw - (diff / steps) * RotationTimer.GetTimeLeft());
        }
        return result;
    }
    return DesiredFacing;
}

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

static inline DirStruct DirDifference(DirStruct a, DirStruct b)
{
    DirStruct r;
    r.Raw = (unsigned short)(a.Raw - b.Raw);
    return r;
}

// FUNCTION: GAMEMD 0x4C95D0
// Signed distance from the current (interpolated) direction to `other`.
DirStruct FacingClass::FUN_004C95D0(const DirStruct* other) const
{
    return DirDifference(*other, Current());
}
