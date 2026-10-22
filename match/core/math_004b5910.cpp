// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry-origin x87 loads and stores).
// GLOBAL: GAMEMD 0x007E8248
extern "C" const double DAT_007E8248;
// GLOBAL: GAMEMD 0x007E1720
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x008A0838
extern "C" double DAT_008A0838;
// GLOBAL: GAMEMD 0x007E1728
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x008A0810
extern "C" double DAT_008A0810;
// GLOBAL: GAMEMD 0x007E1730
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x008A07E8
extern "C" double DAT_008A07E8;

// FUNCTION: GAMEMD 0x004B5910
extern "C" void FUN_004B5910()
{
    DAT_008A0838 = DAT_007E1720 * DAT_007E8248;
}

// FUNCTION: GAMEMD 0x004B5930
extern "C" void FUN_004B5930()
{
    DAT_008A0810 = DAT_007E1728 * DAT_007E8248;
}

// FUNCTION: GAMEMD 0x004B5950
extern "C" void FUN_004B5950()
{
    DAT_008A07E8 = DAT_007E1730 * DAT_007E8248;
}
