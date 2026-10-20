// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x403870.

#include "small_misc33_methods.h"

// FUNCTION: GAMEMD 0x403870
// The scaled value is computed from the *stored* pair rather than the
// arguments - retail re-reads +0x00 and +0x04 after writing them, which is why
// the two loads sit between the stores and the multiply.
void Obj_00403870::FUN_00403870(int lo, int hi)
{
    *(volatile int*)&Current = lo;
    *(volatile int*)&CurrentHi = hi;
    *(volatile int*)&Original = lo;
    *(volatile int*)&OriginalHi = hi;

    *(__int64*)&Scaled = *(volatile __int64*)&Current * 10;
}
