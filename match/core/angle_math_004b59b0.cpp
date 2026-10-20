// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry-origin FILD/F MUL, helper call, and global store).
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
extern "C" double __cdecl FUN_004CADE0(double value);
// GLOBAL: GAMEMD 0x008A0860
extern "C" int DAT_008A0860;
// GLOBAL: GAMEMD 0x007E1740
extern "C" const double DAT_007E1740;
// GLOBAL: GAMEMD 0x008A0818
extern "C" double DAT_008A0818;
// GLOBAL: GAMEMD 0x008A0808
extern "C" const double DAT_008A0808;
// GLOBAL: GAMEMD 0x008A0830
extern "C" double DAT_008A0830;

// FUNCTION: GAMEMD 0x004B59B0
extern "C" void FUN_004B59B0()
{
    DAT_008A0818 = FUN_004CADE0(DAT_008A0860 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x004B59E0
extern "C" void FUN_004B59E0()
{
    DAT_008A0830 = FUN_004CADE0((double)(DAT_008A0860 * 2) / DAT_008A0808);
}
