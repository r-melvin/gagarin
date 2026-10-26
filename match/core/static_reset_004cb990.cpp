// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include <math.h>
#pragma intrinsic(pow)

// Retail instructions at 0x4CB990 confirm four zeroed dword globals.

// GLOBAL: GAMEMD 0x8B3B38
extern "C" unsigned int DAT_008B3B38;
// GLOBAL: GAMEMD 0x8B3B3C
extern "C" unsigned int DAT_008B3B3C;
// GLOBAL: GAMEMD 0x8B3B40
extern "C" unsigned int DAT_008B3B40;
// GLOBAL: GAMEMD 0x8B3B44
extern "C" unsigned int DAT_008B3B44;

// FUNCTION: GAMEMD 0x4CB990
extern "C" void FUN_004CB990()
{
    DAT_008B3B38 = 0;
    DAT_008B3B3C = 0;
    DAT_008B3B40 = 0;
    DAT_008B3B44 = 0;
}

// GLOBAL: GAMEMD 0x8B3B50
extern "C" double DAT_008B3B50;
// GLOBAL: GAMEMD 0x8B3BA0
extern "C" double DAT_008B3BA0;
// GLOBAL: GAMEMD 0x8B3B88
extern "C" double DAT_008B3B88;
// GLOBAL: GAMEMD 0x7E89A8
extern "C" const double DAT_007E89A8;
// GLOBAL: GAMEMD 0x7E1718
// GLOBAL: GAMEMD 0x7E89B0
extern "C" const double DAT_007E89B0;
// GLOBAL: GAMEMD 0x7E1720
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x8B3B80
extern "C" double DAT_008B3B80;

// GLOBAL: GAMEMD 0x7E1710 — retail constant 256.0.
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1708 — retail constant 2.0.
extern "C" const double DAT_007E1708;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — square-root helper.
extern double __cdecl FUN_004CAC40(double value);
// LIBRARY: GAMEMD 0x7C8FB0 — x87 _CIpow; emitted by VC6's pow intrinsic.

// FUNCTION: GAMEMD 0x4CB9B0
// sqrt(2 * 256^2): retail loads 256 and 2 onto the x87 stack, calls
// _CIpow, doubles the result, and passes it to the square-root helper.
extern "C" void FUN_004CB9B0()
{
    DAT_008B3B50 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x4CB9E0
extern "C" void FUN_004CB9E0()
{
    DAT_008B3BA0 = DAT_008B3B50 / DAT_007E89A8;
}

// FUNCTION: GAMEMD 0x4CBA00
extern "C" void FUN_004CBA00()
{
    DAT_008B3B88 = 1.0 / DAT_008B3BA0;
}

// FUNCTION: GAMEMD 0x4CBA20
extern "C" void FUN_004CBA20()
{
    DAT_008B3B80 = DAT_007E1720 * DAT_007E89B0;
}
