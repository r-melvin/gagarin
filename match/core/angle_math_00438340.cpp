// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 instruction bytes, function boundaries, call
// targets and referenced global addresses were confirmed by entry-bounded
// Ghidra disassembly and focused REA evidence in /tmp/gagarin_4383*.json.

#include <math.h>
#pragma intrinsic(pow)

// LIBRARY: GAMEMD 0x7C8FB0 — VC6 x87 _CIpow intrinsic emitted for pow.
// FUNCTION: GAMEMD 0x004CAC40 (decl; reloc) — one-double binary helper.
extern double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0x007E1708
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x007E1710
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1718
extern "C" const double DAT_007E1718;
// GLOBAL: GAMEMD 0x007E1720
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E3CD0
extern "C" const double DAT_007E3CD0;
// GLOBAL: GAMEMD 0x007E3CD8
extern "C" const double DAT_007E3CD8;

// GLOBAL: GAMEMD 0x0089C6A0
extern "C" double DAT_0089C6A0;
// GLOBAL: GAMEMD 0x0089C6A8
extern "C" double DAT_0089C6A8;
// GLOBAL: GAMEMD 0x0089C6D0
extern "C" double DAT_0089C6D0;
// GLOBAL: GAMEMD 0x0089C6D8
extern "C" double DAT_0089C6D8;
// GLOBAL: GAMEMD 0x0089C6F0
extern "C" double DAT_0089C6F0;
// GLOBAL: GAMEMD 0x0089C680
extern "C" double DAT_0089C680;

// FUNCTION: GAMEMD 0x00438340
extern "C" void FUN_00438340()
{
    DAT_0089C6A0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x00438370
extern "C" void FUN_00438370()
{
    DAT_0089C6F0 = DAT_0089C6A0 / DAT_007E3CD0;
}

// FUNCTION: GAMEMD 0x00438390
extern "C" void FUN_00438390()
{
    DAT_0089C6D8 = DAT_007E1718 / DAT_0089C6F0;
}

// FUNCTION: GAMEMD 0x004383B0
extern "C" void FUN_004383B0()
{
    DAT_0089C6D0 = DAT_007E3CD8 * DAT_007E1720;
}

// FUNCTION: GAMEMD 0x004383D0
extern "C" void FUN_004383D0()
{
    DAT_0089C6A8 = DAT_007E3CD8 * DAT_007E1728;
}

// FUNCTION: GAMEMD 0x004383F0
extern "C" void FUN_004383F0()
{
    DAT_0089C680 = DAT_007E3CD8 * DAT_007E1730;
}
