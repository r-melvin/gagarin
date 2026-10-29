// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x578D80.
//
// Address index: 0x578D80

// GLOBAL: GAMEMD 0xAA1020 / 0xAA073C / 0xABB110 / 0xAA1050 / 0xAA10A0 / 0xABBEBC -- first iso-tile index of each tile set.
extern int DAT_00AA1020;
extern int DAT_00AA073C;
extern int DAT_00ABB110;
extern int DAT_00AA1050;
extern int DAT_00AA10A0;
extern int DAT_00ABBEBC;

// FUNCTION: GAMEMD 0x00578D80
// Whether a tile of the slope sets lets through the given facing. A tile in the 0x28-wide set always does;
// in each four-tile slope set only the first and fourth tiles refuse two of the facings; the 0x14-wide set
// always lets through; every other tile refuses.
bool __fastcall FUN_00578D80(int tile, int facing)
{
    if (tile >= DAT_00AA1020 && tile < DAT_00AA1020 + 0x28)
        return true;
    if (tile >= DAT_00AA073C && tile < DAT_00AA073C + 4) {
        if (tile == DAT_00AA073C || tile == DAT_00AA073C + 3) {
            if (facing == 0 || facing == 4)
                return false;
        }
        return true;
    }
    if (tile >= DAT_00ABB110 && tile < DAT_00ABB110 + 4) {
        if (tile == DAT_00ABB110 || tile == DAT_00ABB110 + 3) {
            if (facing == 1 || facing == 3)
                return false;
        }
        return true;
    }
    if (tile >= DAT_00AA1050 && tile < DAT_00AA1050 + 4) {
        if (tile == DAT_00AA1050 || tile == DAT_00AA1050 + 3) {
            if (facing == 0 || facing == 1)
                return false;
        }
        return true;
    }
    if (tile >= DAT_00AA10A0 && tile < DAT_00AA10A0 + 4) {
        if (tile == DAT_00AA10A0 || tile == DAT_00AA10A0 + 3) {
            if (facing == 2 || facing == 3)
                return false;
        }
        return true;
    }
    if (tile >= DAT_00ABBEBC && tile < DAT_00ABBEBC + 0x14)
        return true;
    return false;
}
