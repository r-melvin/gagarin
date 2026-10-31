// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x41A9E0 (ghidra CLI).
//
// AircraftClass movement-check helper: the base TechnoClass answer (slot 240) wins when non-zero; a loaded
// transport with nobody aboard answers 1; otherwise a non-fighter whose turret facing differs from the
// direction to the target by more than half a quadrant answers 2.
//
// Address index: 0x41A9E0

#include <stdlib.h>
#include "../_layout/aircraft_class.h"

// FUNCTION: GAMEMD 0x41A9E0
int AircraftClass::FUN_0041A9E0(AbstractClass* target, int a2, int a3)
{
    int result = TechnoClass::vf_240(target, a2, a3);
    if (result != 0)
        return result;
    if (HasPassengers && Passengers.FirstPassenger == 0)
        return 1;
    DirStruct scratch;
    DirStruct turret = *SecondaryFacing.FUN_004C93D0(&scratch);
    if (vf_07() == 0) {
        DirStruct* toTarget = FUN_005F3DB0(&scratch, target);
        short diff = (short)(turret.Raw - toTarget->Raw);
        if (abs(0x800) < abs(diff))
            return 2;
    }
    return 0;
}
