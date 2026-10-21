// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; facts below were checked against the retail
// instructions and PE section bytes. The original source names are unknown.
// C linkage and void results are ABI bindings, not recovered declarations.
// Address grouping does not establish original ownership or startup role.
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(double) == 8);

// GLOBAL: GAMEMD 0x0089E1A0 (read by 0x4731C0; writable .data storage)
extern "C" double DAT_0089E1A0;
// GLOBAL: GAMEMD 0x0089E1F0 (written by 0x4731C0; writable .data storage)
extern "C" double DAT_0089E1F0;
// GLOBAL: GAMEMD 0x0089E1D8 (written by 0x4731E0; writable .data storage)
extern "C" double DAT_0089E1D8;
// GLOBAL: GAMEMD 0x0089E1D0 (written by 0x473200; writable .data storage)
extern "C" double DAT_0089E1D0;
// GLOBAL: GAMEMD 0x0089E1A8 (written by 0x473220; writable .data storage)
extern "C" double DAT_0089E1A8;
// GLOBAL: GAMEMD 0x0089E180 (written by 0x473240; writable .data storage)
extern "C" double DAT_0089E180;

// GLOBAL: GAMEMD 0x007E4BE0 (double 60.0 in .rdata)
extern "C" const double DAT_007E4BE0;
// GLOBAL: GAMEMD 0x007E4BE8 (double 0.017453292519943295 in .rdata)
extern "C" const double DAT_007E4BE8;
// GLOBAL: GAMEMD 0x007E1718 (double 1.0 in .rdata)
extern "C" const double DAT_007E1718;
// GLOBAL: GAMEMD 0x007E1720 (double 45.0 in .rdata)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 (double 60.0 in .rdata)
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 (double 90.0 in .rdata)
extern "C" const double DAT_007E1730;

// FUNCTION: GAMEMD 0x004731C0
extern "C" void FUN_004731C0()
{
    DAT_0089E1F0 = DAT_0089E1A0 / DAT_007E4BE0;
}

// FUNCTION: GAMEMD 0x004731E0
extern "C" void FUN_004731E0()
{
    DAT_0089E1D8 = DAT_007E1718 / DAT_0089E1F0;
}

// FUNCTION: GAMEMD 0x00473200
extern "C" void FUN_00473200()
{
    DAT_0089E1D0 = DAT_007E4BE8 * DAT_007E1720;
}

// FUNCTION: GAMEMD 0x00473220
extern "C" void FUN_00473220()
{
    DAT_0089E1A8 = DAT_007E4BE8 * DAT_007E1728;
}

// FUNCTION: GAMEMD 0x00473240
extern "C" void FUN_00473240()
{
    DAT_0089E180 = DAT_007E4BE8 * DAT_007E1730;
}
