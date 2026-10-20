// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// The rocket locomotor's file-scope dynamic initialisers, ascending by address.
// Each body is what cl emits for one file-scope variable's initialiser, so each
// is a plain `void __cdecl` with the assignment as its whole content.

#include "rocket_locomotion_globals.h"

// The diagonal of a 256x256-lepton cell. The two squares are the same
// expression, so cl computes the power once and doubles it with `FADD ST,ST`.
// FUNCTION: GAMEMD 0x661CB0
void Init_DAT_00B04E20()
{
    DAT_00B04E20 = FUN_004CAC40(pow(256.0, 2.0) + pow(256.0, 2.0));
}

// The cell diagonal cut into sixtieths.
// FUNCTION: GAMEMD 0x661CE0
void Init_DAT_00B04E70()
{
    DAT_00B04E70 = DAT_00B04E20 / DAT_007F0B08;
}

// Its reciprocal, so the hot path multiplies instead of dividing.
// FUNCTION: GAMEMD 0x661D00
void Init_DAT_00B04E58()
{
    DAT_00B04E58 = 1.0 / DAT_00B04E70;
}

// Forty-five degrees in radians.
// FUNCTION: GAMEMD 0x661D20
void Init_DAT_00B04E50()
{
    DAT_00B04E50 = DAT_007F0B10 * 45.0;
}

// Sixty degrees in radians.
// FUNCTION: GAMEMD 0x661D40
void Init_DAT_00B04E28()
{
    DAT_00B04E28 = DAT_007F0B10 * 60.0;
}

// Ninety degrees in radians.
// FUNCTION: GAMEMD 0x661D60
void Init_DAT_00B04E00()
{
    DAT_00B04E00 = DAT_007F0B10 * 90.0;
}

// Half the cell diagonal projected through the thirty degrees between the first
// two angles, truncated to an integer number of leptons.
// FUNCTION: GAMEMD 0x661D80
void Init_DAT_00B04E78()
{
    DAT_00B04E78 = (int)(FUN_004CAD50(DAT_00B04E00 - DAT_00B04E28) * DAT_00B04E20 * 0.5);
}

// The angle that projection subtends across one cell.
// FUNCTION: GAMEMD 0x661DC0
void Init_DAT_00B04E30()
{
    DAT_00B04E30 = FUN_004CADE0(DAT_00B04E78 * 0.00390625);
}

// The angle twice that projection subtends across the cell diagonal.
// FUNCTION: GAMEMD 0x661DF0
void Init_DAT_00B04E48()
{
    DAT_00B04E48 = FUN_004CADE0((DAT_00B04E78 * 2) / DAT_00B04E20);
}

// Four times the projection, rounded rather than truncated.
// FUNCTION: GAMEMD 0x661E20
void Init_DAT_00B04E6C()
{
    DAT_00B04E6C = (int)(DAT_00B04E78 * 4 + 0.5);
}

// The word pair starts cleared.
// FUNCTION: GAMEMD 0x661E50
void Init_DAT_00B04E18()
{
    DAT_00B04E18.A = 0;
    DAT_00B04E18.B = 0;
}

// So does the triple the rocket locomotor seeds itself from.
// FUNCTION: GAMEMD 0x661E60
void Init_DAT_00B04E38()
{
    DAT_00B04E38.A = 0;
    DAT_00B04E38.B = 0;
    DAT_00B04E38.C = 0;
}

// The second triple starts at 0x80, 0x80, 0.
// FUNCTION: GAMEMD 0x661E80
void Init_DAT_00B04E60()
{
    DAT_00B04E60.A = 0x80;
    DAT_00B04E60.B = 0x80;
    DAT_00B04E60.C = 0;
}

// And the four-dword block starts cleared.
// FUNCTION: GAMEMD 0x661EA0
void Init_DAT_00B04E08()
{
    DAT_00B04E08.A = 0;
    DAT_00B04E08.B = 0;
    DAT_00B04E08.C = 0;
    DAT_00B04E08.D = 0;
}
