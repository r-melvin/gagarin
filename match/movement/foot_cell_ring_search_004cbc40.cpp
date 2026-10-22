// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Full entry disassembly read from retail gamemd.exe v1.001, 0x4CBC40 to
//   its last RET 0x14 at 0x4CBEE2. The only caller (0x6EA0D0) invokes it on
//   the team member it walks through FootClass::NextTeamMember (+0x5D8).
//   The ring walk starts at the eight-way direction nearest the bearing from
//   `center` to `from`; each ring is walked along its straight sides, and the
//   first cell for which vtable slot 107 (ObjectClass::vf_107, 0x1AC) returns
//   zero is the result.
#include "../_layout/foot_class.h"
#include "../map/cell_flag_search_shared.h"

// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) -- two-argument arctangent, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);
// LIBRARY: GAMEMD 0x7C5F00 -- the double-to-int conversion behind (int).

// GLOBAL: GAMEMD 0x7E2820
extern const double DAT_007E2820;   // pi / 2
// GLOBAL: GAMEMD 0x7E2818
extern const double DAT_007E2818;   // angle scale (binary angle units per radian, negated)
// GLOBAL: GAMEMD 0x8B3B48
extern Cell DAT_008B3B48;           // the empty result

// A cell displaced by one of the eight one-cell steps.
inline CellStruct Displaced(const CellStruct& cell, const CellStruct& step)
{
    CellStruct result;
    result.X = cell.X + step.X;
    result.Y = cell.Y + step.Y;
    return result;
}

// FUNCTION: GAMEMD 0x4CBC40
Cell FootClass::FUN_004CBC40(CellStruct* from, CellStruct* center, int firstRadius, int endRadius)
{
    unsigned short angle = (int)((FUN_004CAE30((double)from->Y - (double)center->Y,
                                               (double)center->X - (double)from->X)
                                  - DAT_007E2820) * DAT_007E2818);
    unsigned int direction = ((((angle >> 12) + 1U) >> 1) ^ 0xFFFFFFFC) - 1;
    direction &= 7;

    for (int radius = firstRadius; radius < endRadius; ++radius) {
        CellStruct cell = *center;
        for (int step = radius; step > 0; --step)
            cell = Displaced(cell, DAT_0089F688[direction & 7]);

        if (direction & 1) {
            unsigned int facing = (direction + 3) & 7;
            for (int i = 0; i < radius * 2; ++i) {
                cell = Displaced(cell, DAT_0089F688[facing]);
                CellClass* target = DAT_0087F7E8.FUN_005657A0(&cell);
                if (vf_107(target, facing, -1, 0, 1) == 0) {
                    Cell found;
                    found.X = cell.X;
                    found.Y = cell.Y;
                    return found;
                }
            }
        } else {
            unsigned int facing = (direction + 2) & 7;
            for (int j = 0; j < radius; ++j) {
                cell = Displaced(cell, DAT_0089F688[facing]);
                CellClass* target = DAT_0087F7E8.FUN_005657A0(&cell);
                if (vf_107(target, facing, -1, 0, 1) == 0) {
                    Cell found;
                    found.X = cell.X;
                    found.Y = cell.Y;
                    return found;
                }
            }
            facing = (direction - 4) & 7;
            for (int k = 0; k < radius + 1; ++k) {
                cell = Displaced(cell, DAT_0089F688[facing]);
                CellClass* target = DAT_0087F7E8.FUN_005657A0(&cell);
                if (vf_107(target, facing, -1, 0, 1) == 0) {
                    Cell found;
                    found.X = cell.X;
                    found.Y = cell.Y;
                    return found;
                }
            }
        }
    }
    return DAT_008B3B48;
}
