// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x662240.
//
//   Address index: 0x662240

#include "rocket_locomotion_globals.h"
#include "rocket_locomotion.h"

// FUNCTION: GAMEMD 0x662240
// PARTIAL: 88.9%. Same instructions as retail; the two squares are summed in the other
// register order (retail squares dx first into ECX, dy second into EAX).
// Pitch of the line from the foot to the destination: atan(rise / run), or
// straight down (-pi/2) when the run is zero.
double RocketLocomotionClass::FUN_00662240()
{
    LocoCoord here = ((RocketFootView*)LinkedTo)->Location;
    LocoCoord d;
    d.X = Destination_.X - here.X;
    d.Y = Destination_.Y - here.Y;
    d.Z = Destination_.Z - here.Z;
    double run = FUN_004CAC40((double)(d.Y * d.Y + d.X * d.X));
    if (run > 0.0)
        return FUN_004CADE0(d.Z / run);
    return -1.5707963267948966;
}
