// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-bounded retail evidence: 0x43AF70 reads doubles at 0x89C820 and
// 0x7E3E78, then stores to 0x89C880; 0x43AF90 reads 0x7E1718 and 0x89C880,
// then stores to 0x89C868. Both complete entry spans are 19 bytes.
// The two 0x7E constants are in read-only .rdata; only observed arithmetic
// is modeled here, without claiming the original startup registration.
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(double) == 8);

extern "C" double DAT_0089C820; // GLOBAL: GAMEMD 0x0089C820
extern "C" const double DAT_007E3E78; // GLOBAL: GAMEMD 0x007E3E78
extern "C" double DAT_0089C880; // GLOBAL: GAMEMD 0x0089C880
extern "C" const double DAT_007E1718; // GLOBAL: GAMEMD 0x007E1718
extern "C" double DAT_0089C868; // GLOBAL: GAMEMD 0x0089C868

// FUNCTION: GAMEMD 0x43AF70
extern "C" void FUN_0043AF70()
{
    DAT_0089C880 = DAT_0089C820 / DAT_007E3E78;
}

// FUNCTION: GAMEMD 0x43AF90
extern "C" void FUN_0043AF90()
{
    DAT_0089C868 = DAT_007E1718 / DAT_0089C880;
}
