// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x74CD60  VeinholeMonsterClass::GetVeinholeMonsterFrom (__fastcall)
//   FUNCTION: GAMEMD 0x74CDB0  VeinholeMonsterClass::GetVeinholeMonsterAt   (__fastcall)
//   FUNCTION: GAMEMD 0x74D450  VeinholeMonsterClass::LoadVeinholeArt        (__fastcall)

#include "veinhole_monster_class_methods.h"

// FUNCTION: GAMEMD 0x74CD60  (__fastcall)
// Scan the registry back-to-front for the monster whose home cell exactly
// matches pCell (compare the CellStruct X then Y).
VeinholeMonsterClass* __fastcall VeinholeMonsterClass::GetVeinholeMonsterFrom(CellStruct* pCell)
{
    int i = VeinholeArray.Count - 1;
    if (i >= 0)
    {
        do
        {
            VeinholeMonsterClass* m = ((VeinholeMonsterClass**)VeinholeArray.Items)[i];
            CellStruct* pos = &m->Position;
            if (pos->X == pCell->X && pos->Y == pCell->Y)
                return ((VeinholeMonsterClass**)VeinholeArray.Items)[i];
            --i;
        } while (i >= 0);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x74CDB0  (__fastcall)
// Scan the registry back-to-front for the monster whose per-cell affection map
// is set at pCell's linear index.
//
// The cell-index call sits inside the subscript expression rather than in a
// named local: VC6 then vacates the call result into ECX (`MOV ECX,EAX`) so
// the Items base can take EAX (`MOV EAX,[0xB1D294]`), which is also the base
// the found path re-indexes (`MOV EAX,[EAX+ESI*4]`). With `int idx = ...;`
// first, idx stays in EAX and Items goes to ECX, one `MOV` short and with the
// base/index roles of the `CMP byte ptr` swapped (32.0%).
VeinholeMonsterClass* __fastcall VeinholeMonsterClass::GetVeinholeMonsterAt(CellStruct* pCell)
{
    for (int i = VeinholeArray.Count - 1; i >= 0; --i)
    {
        if (((VeinholeMonsterClass**)VeinholeArray.Items)[i]->SpreadData[CellStructToIndex(pCell)] != 0)
            return ((VeinholeMonsterClass**)VeinholeArray.Items)[i];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x74D450  (__fastcall)
// Build the theater-specific filename "VEINHOLE.<ext>" and cache its SHP.
void __fastcall VeinholeMonsterClass::LoadVeinholeArt(int idxTheatre)
{
    char filename[32];
    sprintf(filename, "VEINHOLE.%s", TheaterArray[idxTheatre].Extension);
    VeinSHPData = LoadVeinholeSHP(filename, 0);
}
