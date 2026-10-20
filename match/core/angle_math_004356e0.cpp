// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// Retail entry points, global addresses, constants, and math operations were
// confirmed against gamemd.exe v1.001 instructions and data bytes.

// LIBRARY: GAMEMD 0x7C5F00 — MSVC x87 integer conversion helper emitted for casts.
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) — binary trigonometric helper.
extern double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) — binary math helper.
extern double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x007E1738 — constant 0.5.
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 — constant 0.00390625.
extern "C" const double DAT_007E1740;

// GLOBAL: GAMEMD 0x0089C4D8
extern "C" double DAT_0089C4D8;
// GLOBAL: GAMEMD 0x0089C500
extern "C" double DAT_0089C500;
// GLOBAL: GAMEMD 0x0089C4F8
extern "C" double DAT_0089C4F8;
// GLOBAL: GAMEMD 0x0089C550
extern "C" int DAT_0089C550;
// GLOBAL: GAMEMD 0x0089C508
extern "C" double DAT_0089C508;
// GLOBAL: GAMEMD 0x0089C520
extern "C" double DAT_0089C520;
// GLOBAL: GAMEMD 0x0089C544
extern "C" int DAT_0089C544;
// GLOBAL: GAMEMD 0x0089C4F0
extern "C" unsigned short DAT_0089C4F0;
// GLOBAL: GAMEMD 0x0089C4F2
extern "C" unsigned short DAT_0089C4F2;
// GLOBAL: GAMEMD 0x0089C510
extern "C" unsigned int DAT_0089C510;
// GLOBAL: GAMEMD 0x0089C514
extern "C" unsigned int DAT_0089C514;
// GLOBAL: GAMEMD 0x0089C518
extern "C" unsigned int DAT_0089C518;
// GLOBAL: GAMEMD 0x0089C540
extern "C" unsigned int DAT_0089C540;
// GLOBAL: GAMEMD 0x0089C538
extern "C" unsigned int DAT_0089C538;
// GLOBAL: GAMEMD 0x0089C53C
extern "C" unsigned int DAT_0089C53C;
// GLOBAL: GAMEMD 0x0089C4E0
extern "C" unsigned int DAT_0089C4E0;
// GLOBAL: GAMEMD 0x0089C4E4
extern "C" unsigned int DAT_0089C4E4;
// GLOBAL: GAMEMD 0x0089C4E8
extern "C" unsigned int DAT_0089C4E8;
// GLOBAL: GAMEMD 0x0089C4EC
extern "C" unsigned int DAT_0089C4EC;

// FUNCTION: GAMEMD 0x4356E0
extern "C" void FUN_004356E0()
{
    DAT_0089C550 = (int)(FUN_004CAD50(DAT_0089C4D8 - DAT_0089C500)
                         * DAT_007E1738 * DAT_0089C4F8);
}

// FUNCTION: GAMEMD 0x435720
extern "C" void FUN_00435720()
{
    DAT_0089C508 = FUN_004CADE0((double)DAT_0089C550 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x435750
extern "C" void FUN_00435750()
{
    DAT_0089C520 = FUN_004CADE0((double)(DAT_0089C550 * 2) / DAT_0089C4F8);
}

// FUNCTION: GAMEMD 0x435780
extern "C" void FUN_00435780()
{
    DAT_0089C544 = (int)(DAT_0089C550 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x4357B0
extern "C" void FUN_004357B0()
{
    DAT_0089C4F0 = 0;
    DAT_0089C4F2 = 0;
}

// FUNCTION: GAMEMD 0x4357C0
extern "C" void FUN_004357C0()
{
    DAT_0089C510 = 0;
    DAT_0089C514 = 0;
    DAT_0089C518 = 0;
}

// FUNCTION: GAMEMD 0x4357E0
extern "C" void FUN_004357E0()
{
    DAT_0089C540 = 0;
    DAT_0089C538 = 0x80;
    DAT_0089C53C = 0x80;
}

// FUNCTION: GAMEMD 0x435800
extern "C" void FUN_00435800()
{
    DAT_0089C4E0 = 0;
    DAT_0089C4E4 = 0;
    DAT_0089C4E8 = 0;
    DAT_0089C4EC = 0;
}
