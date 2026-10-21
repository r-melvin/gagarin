// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; access addresses and widths were confirmed
// from each complete retail entry. The original owners and function names are
// unresolved; C linkage and void results are candidate ABI bindings only.
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(double) == 8);

// GLOBAL: GAMEMD 0x0089E220 (read as qword by 0x473570; .data)
extern "C" double DAT_0089E220;
// GLOBAL: GAMEMD 0x0089E270 (written/read as qword by 0x473570/0x473590; .data)
extern "C" double DAT_0089E270;
// GLOBAL: GAMEMD 0x0089E258 (written as qword by 0x473590; .data)
extern "C" double DAT_0089E258;
// GLOBAL: GAMEMD 0x0089E250 (written as qword by 0x4735B0; .data)
extern "C" double DAT_0089E250;
// GLOBAL: GAMEMD 0x0089E228 (written as qword by 0x4735D0; .data)
extern "C" double DAT_0089E228;
// GLOBAL: GAMEMD 0x0089E200 (written as qword by 0x4735F0; .data)
extern "C" double DAT_0089E200;

// GLOBAL: GAMEMD 0x007E4BF0 (read-only .rdata double 60.0)
extern "C" const double DAT_007E4BF0;
// GLOBAL: GAMEMD 0x007E4BF8 (read-only .rdata double 0.017453292519943295)
extern "C" const double DAT_007E4BF8;
// GLOBAL: GAMEMD 0x007E1718 (read-only .rdata double 1.0)
extern "C" const double DAT_007E1718;
// GLOBAL: GAMEMD 0x007E1720 (read-only .rdata double 45.0)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 (read-only .rdata double 60.0)
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 (read-only .rdata double 90.0)
extern "C" const double DAT_007E1730;

// FUNCTION: GAMEMD 0x00473570
extern "C" void FUN_00473570()
{
    DAT_0089E270 = DAT_0089E220 / DAT_007E4BF0;
}

// FUNCTION: GAMEMD 0x00473590
extern "C" void FUN_00473590()
{
    DAT_0089E258 = DAT_007E1718 / DAT_0089E270;
}

// FUNCTION: GAMEMD 0x004735B0
extern "C" void FUN_004735B0()
{
    DAT_0089E250 = DAT_007E4BF8 * DAT_007E1720;
}

// FUNCTION: GAMEMD 0x004735D0
extern "C" void FUN_004735D0()
{
    DAT_0089E228 = DAT_007E4BF8 * DAT_007E1728;
}

// FUNCTION: GAMEMD 0x004735F0
extern "C" void FUN_004735F0()
{
    DAT_0089E200 = DAT_007E4BF8 * DAT_007E1730;
}
