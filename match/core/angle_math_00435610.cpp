// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// Retail entry points, global addresses, constants, and math operations were
// confirmed against gamemd.exe v1.001 instructions and data bytes.
#include <math.h>
#pragma intrinsic(pow)

// LIBRARY: GAMEMD 0x7C8FB0 — VC6 x87 _CIpow emitted for intrinsic pow.
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — binary square-root helper.
extern double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0x007E1710 — constant 256.0.
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1708 — constant 2.0.
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x007E3A88 — constant 60.0.
extern "C" const double DAT_007E3A88;
// GLOBAL: GAMEMD 0x007E1718 — constant 1.0.
extern "C" const double DAT_007E1718;
// GLOBAL: GAMEMD 0x007E3A90 — radians per degree (0.017453292519943295).
extern "C" const double DAT_007E3A90;
// GLOBAL: GAMEMD 0x007E1720 — constant 45.0.
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 — constant 60.0.
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 — constant 90.0.
extern "C" const double DAT_007E1730;

// GLOBAL: GAMEMD 0x0089C4F8
extern "C" double DAT_0089C4F8;
// GLOBAL: GAMEMD 0x0089C548
extern "C" double DAT_0089C548;
// GLOBAL: GAMEMD 0x0089C530
extern "C" double DAT_0089C530;
// GLOBAL: GAMEMD 0x0089C528
extern "C" double DAT_0089C528;
// GLOBAL: GAMEMD 0x0089C500
extern "C" double DAT_0089C500;
// GLOBAL: GAMEMD 0x0089C4D8
extern "C" double DAT_0089C4D8;

// FUNCTION: GAMEMD 0x435610
extern "C" void FUN_00435610()
{
    DAT_0089C4F8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x435640
extern "C" void FUN_00435640()
{
    DAT_0089C548 = DAT_0089C4F8 / DAT_007E3A88;
}

// FUNCTION: GAMEMD 0x435660
extern "C" void FUN_00435660()
{
    DAT_0089C530 = DAT_007E1718 / DAT_0089C548;
}

// FUNCTION: GAMEMD 0x435680
extern "C" void FUN_00435680()
{
    DAT_0089C528 = DAT_007E1720 * DAT_007E3A90;
}

// FUNCTION: GAMEMD 0x4356A0
extern "C" void FUN_004356A0()
{
    DAT_0089C500 = DAT_007E1728 * DAT_007E3A90;
}

// FUNCTION: GAMEMD 0x4356C0
extern "C" void FUN_004356C0()
{
    DAT_0089C4D8 = DAT_007E1730 * DAT_007E3A90;
}
