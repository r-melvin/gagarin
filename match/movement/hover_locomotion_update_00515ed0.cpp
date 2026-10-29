// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   0x515ED0 disassembled from the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//   It sits inside the HoverLocomotionClass range of tu098_hover_locomotion_class.cpp and is
//   called from Process (0x514310); it lives in its own file so the matched Process body
//   keeps its out-of-line call.

#include <math.h>
#include <stdlib.h>
#include "hover_locomotion_class.h"
#include "../core/small_misc23_methods.h"
#include "../core/cell_step_tables.h"

// True when any component differs from the empty coordinate DAT_00A8F180.
static inline bool IsCoordSet(const LocoCoord& c)
{
    return c.X != DAT_00A8F180.X || c.Y != DAT_00A8F180.Y || c.Z != DAT_00A8F180.Z;
}

static inline int VectorLength(int dx, int dy, int dz)
{
    Triple3iLen delta;
    delta.a = dx;
    delta.b = dy;
    delta.c = dz;
    return delta.FUN_0041C380();
}

// Length of the vector from the foot's current position to HeadTo (the 0x41C380 helper).
inline int HoverLocomotionClass::LengthToHeadTo()
{
    HoverCoordView buffer;
    HoverCoordView* now = HoverUnitCoord(HoverFoot(LinkedTo), &buffer);
    return VectorLength(now->X - HeadTo.X, now->Y - HeadTo.Y, now->Z - HeadTo.Z);
}

// The same length to Destination_ with the square root taken inline.
inline int HoverLocomotionClass::SqrtLengthToDestination()
{
    HoverCoordView buffer;
    HoverCoordView* now = HoverUnitCoord(HoverFoot(LinkedTo), &buffer);
    int dx = now->X - Destination_.X;
    int dy = now->Y - Destination_.Y;
    int dz = now->Z - Destination_.Z;
    return (int)HoverSqrt((double)dy * dy + (double)dz * dz + (double)dx * dx);
}

// Facing for a bearing in radians (0 = east, counter-clockwise), as a 16-bit angle.
static inline HoverDirView DirFromAngle(double radians)
{
    HoverDirView result;
    result.Angle = (short)(int)((radians - 1.5707963267948966) * -10430.378350470453);
    return result;
}

// FUNCTION: GAMEMD 0x515ED0
// PARTIAL: 76.4%. Same 348-instruction multiset, control flow, frame and FPU sequences as retail; only
// register assignment differs (retail keeps the ILocomotion pointer in EBP, HeadTo in EDI, the facing
// pointer in EBX) plus the tail HeadTo copy registers and two swapped stack slots.
// Per-tick steering and speed update: turn toward the next waypoint, pick the target speed
// (half near the goal, full otherwise), ramp the speed factor towards it and, while moving
// off-cell, keep the object's body facing on the heading to the next cell.
void HoverLocomotionClass::Fun_00515ED0()
{
    if (IsMoving() && IsCoordSet(HeadTo)) {
        HoverDirView dir;
        {
            HoverCoordView buffer;
            HoverCoordView* here = HoverUnitCoord(HoverFoot(LinkedTo), &buffer);
            here->Fun_00517310(&HeadTo);
            dir = DirFromAngle(HoverAtan2((double)here->Y - HeadTo.Y, (double)HeadTo.X - here->X));
        }
        if (!Blocked)
            Facing.SetDesired(&dir);
        else
            Facing.Set(&dir);

        if ((IsPowered() && abs(0x2000) >= abs((short)(Facing.Current().Angle - dir.Angle)))
            || Blocked) {
            if ((!IsCoordSet(Destination_) && LengthToHeadTo() < 0x100)
                || (IsCoordSet(Destination_) && SqrtLengthToDestination() < 0x100)) {
                Speed = 0.5;
            } else {
                Speed = 1.0;
                if (Blocked)
                    SpeedFactor = 1.0;
            }
        } else {
            Speed = 0.0;
        }
        if (Speed > 0.0) {
            Field_58 = 1.0;
            HoverFootView* foot = HoverFoot(LinkedTo);
            if (foot->PathDirection0 != -1 && foot->PathDirection0 == foot->PathDirection1)
                Field_58 = DAT_008871E0->unknown_5D8;
        }
        double target = Field_58 * Speed;
        if (1.0 < target)
            target = 1.0;
        if (SpeedFactor < target) {
            double faster = 1.0 / (DAT_008871E0->unknown_5E0 * 900.0) + SpeedFactor;
            SpeedFactor = faster;
            if (faster >= target)
                faster = target;
            SpeedFactor = faster;
        }
        if (target < SpeedFactor) {
            double slower = SpeedFactor - 1.0 / (DAT_008871E0->unknown_5E8 * 900.0);
            SpeedFactor = slower;
            if (slower <= 0.0)
                slower = 0.0;
            SpeedFactor = slower;
        }
        if (Speed > 0.0 && !Blocked) {
            LocoCoord next = HeadTo;
            int path = HoverFoot(LinkedTo)->PathDirection0;
            if (path != -1 && path != 8) {
                const Point2D& step = DAT_0089F6D8[path & 7];
                next.X += step.X;
                next.Y += step.Y;
            }
            HoverCoordView buf4;
            HoverCoordView* at = HoverUnitCoord(HoverFoot(LinkedTo), &buf4);
            int atX = at->X;
            HoverDirView desired = DirFromAngle(HoverAtan2((double)at->Y - next.Y, (double)next.X - atX));
            HoverFoot(LinkedTo)->PrimaryFacing.SetDesired(&desired);
        }
    } else if (IsMoving() && !IsCoordSet(HeadTo)) {
        HoverFoot(LinkedTo)->Slot_544(1.0);
        Fun_005164D0(0);
        Fun_00514F70(1);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8F180
LocoCoord DAT_00A8F180;
// END defined globals
