// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry-bounded x87 loads, calls and stores).
#include <math.h>
#pragma intrinsic(pow)
// LIBRARY: GAMEMD 0x007C8FB0 — VC6 x87 pow intrinsic runtime.
// Literal pool: retail 0x7E1708 = 2.0, 0x7E1710 = 256.0.

// FUNCTION: GAMEMD 0x004CAC40 (decl; reloc) — binary-verified one-double cdecl helper.
extern double __cdecl FUN_004CAC40(double value);
// GLOBAL: GAMEMD 0x007E8240
extern const double DAT_007E8240;
// GLOBAL: GAMEMD 0x008A0808
extern double DAT_008A0808;
// GLOBAL: GAMEMD 0x008A0858
extern double DAT_008A0858;
// GLOBAL: GAMEMD 0x007E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x008A0840
extern double DAT_008A0840;

// FUNCTION: GAMEMD 0x004B58A0
extern "C" void __stdcall FUN_004B58A0()
{
    DAT_008A0808 = FUN_004CAC40(2.0 * pow(256.0, 2.0));
}

// FUNCTION: GAMEMD 0x004B58D0
extern "C" void __stdcall FUN_004B58D0()
{
    DAT_008A0858 = DAT_008A0808 / DAT_007E8240;
}

// FUNCTION: GAMEMD 0x004B58F0
extern "C" void __stdcall FUN_004B58F0()
{
    DAT_008A0840 = DAT_007E1718 / DAT_008A0858;
}
