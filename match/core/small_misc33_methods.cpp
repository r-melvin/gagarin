// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x403870.

#include "small_misc33_methods.h"

// FUNCTION: GAMEMD 0x403870
// The scaled value is computed from the *stored* pair rather than the
// arguments - retail re-reads +0x00 and +0x04 after writing them, which is why
// the two loads sit between the stores and the multiply. PARTIAL: with
// ordinary stores VC6 reuses the arguments instead of re-reading the members;
// the volatile accesses that forced the reload were removed as match steering.
void Obj_00403870::FUN_00403870(int lo, int hi)
{
    Current = lo;
    CurrentHi = hi;
    Original = lo;
    OriginalHi = hi;

    *(__int64*)&Scaled = *(__int64*)&Current * 10;
}
