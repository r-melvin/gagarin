// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4C9530 and 0x4C95D0 against FacingClass::Current()
//   (0x4C93D0), whose body both inline.
//
// FacingClass distance-to-go helpers. Address index: 0x4C9530, 0x4C95D0.

#include <stdlib.h>   // abs (the /O2 intrinsic: CDQ; XOR; SUB)
#include "../_layout/facing_class.h"


// FUNCTION: GAMEMD 0x4C9530
// PARTIAL: 95.5% (64/67 instructions). Remaining delta: retail keeps the desired direction in
// ESI and subtracts the merged current value in the shared tail, then stores the low word of
// the result; this form spills the result to the stack first (3 instructions out of order).
// Tried: DirDifference(DesiredFacing, Current()) (68.7%), a local copy of the desired value
// (28.4%), calling the 0x4C95D0 form with &DesiredFacing (1.5%).
// How far the facing still has to turn: desired direction minus the current
// (interpolated) one. Zero when it is not rotating.
DirStruct FacingClass::FUN_004C9530() const
{
    DirStruct cur = Current();
    DirStruct result = DesiredFacing;
    result.Raw = (unsigned short)(result.Raw - cur.Raw);
    return result;
}
