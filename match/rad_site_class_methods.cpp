// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x65B4C0  RadSiteClass::SetBaseCell  (__thiscall)
//   FUNCTION: GAMEMD 0x65B4D0  RadSiteClass::SetSpread    (__thiscall)
//   FUNCTION: GAMEMD 0x65B4F0  RadSiteClass::SetRadLevel  (__thiscall)
//   FUNCTION: GAMEMD 0x65B510  RadSiteClass::GetRadLevel  (__thiscall)

#include "rad_site_class_methods.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"

extern RulesClass* RulesInstance;  // GLOBAL: GAMEMD 0x008871E0

// FUNCTION: GAMEMD 0x65B4C0  (__thiscall)
// Set the center cell (copied as a single dword).
void RadSiteClass::SetBaseCell(CellStruct* pCell)
{
    BaseCell = *pCell;
}

// FUNCTION: GAMEMD 0x65B4D0  (__thiscall)
// Set the spread in cells; also derives SpreadInLeptons = nCells*256 + 128.
void RadSiteClass::SetSpread(int nCells)
{
    Spread = nCells;
    SpreadInLeptons = (nCells << 8) + 0x80;
}

// FUNCTION: GAMEMD 0x65B4F0  (__thiscall)
// Set the rad level and the duration values derived from the rules multiple.
void RadSiteClass::SetRadLevel(int nRadLevel)
{
    RadLevel = nRadLevel;
    int duration = RulesInstance->RadDurationMultiple * nRadLevel;
    RadDuration = duration;
    RadTimeLeft = duration;
}

// FUNCTION: GAMEMD 0x65B510  (__thiscall)
// Current applied rad level: scaled by remaining time over total duration.
int RadSiteClass::GetRadLevel()
{
    int duration = RadDuration;
    if (duration <= 0)
        return 0;
    return RadTimeLeft * RadLevel / duration;
}

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x65B8F0
// The radiation this site puts on a cell: falls off linearly with the distance to the centre.
double RadSiteClass::FUN_0065B8F0(CellStruct* cell)
{
    CellClass* centre = DAT_0087F7E8.FUN_005657A0(&BaseCell);
    CellClass* target = DAT_0087F7E8.FUN_005657A0(cell);
    CoordStruct from = centre->vf_18();
    CoordStruct to = target->vf_18();
    CoordStruct diff;
    diff.X = from.X - to.X;
    diff.Z = from.Z - to.Z;
    diff.Y = from.Y - to.Y;
    int distance = (int)FUN_004CAC40((double)diff.X * diff.X + (double)diff.Y * diff.Y + (double)diff.Z * diff.Z);
    double result = 0.0;
    if (distance <= SpreadInLeptons) {
        result = (double)(SpreadInLeptons - distance) / SpreadInLeptons * RadLevel;
    }
    return result;
}
