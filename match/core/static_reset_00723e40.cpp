// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 at 0x723E40 zeros four absolute-address dwords.

// GLOBAL: GAMEMD 0xB0F598
extern "C" unsigned int DAT_00B0F598;
// GLOBAL: GAMEMD 0xB0F59C
extern "C" unsigned int DAT_00B0F59C;
// GLOBAL: GAMEMD 0xB0F5A0
extern "C" unsigned int DAT_00B0F5A0;
// GLOBAL: GAMEMD 0xB0F5A4
extern "C" unsigned int DAT_00B0F5A4;

// FUNCTION: GAMEMD 0x723E40
extern "C" void FUN_00723E40()
{
    DAT_00B0F598 = 0;
    DAT_00B0F59C = 0;
    DAT_00B0F5A0 = 0;
    DAT_00B0F5A4 = 0;
}
