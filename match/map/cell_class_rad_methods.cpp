// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellView_00480A30 radiation / coordinate helpers, ordered ascending by retail address.
#include "cell_class_rad_methods.h"

// FUNCTION: GAMEMD 0x480A30  CellView_00480A30::GetCellCoords (__thiscall)
//   Returns the cell centre in world coords: (MapCoords.X*256+128,
//   MapCoords.Y*256+128, GetFloorHeight({128,128})).
CoordStruct* CellView_00480A30::GetCellCoords(CoordStruct* pBuffer) const
{
    // MapCoords (a CellStruct) is materialised into the same stack slot that
    // later serves as the {128,128} sub-cell Point2D handed to GetFloorHeight —
    // retail reuses that slot, so model it with an explicit overlay union.
    union { CellStruct mc; Point2D pt; } u;
    u.mc = this->MapCoords;
    int x = u.mc.X * 256 + 128;
    int y = u.mc.Y * 256 + 128;
    u.pt.X = 128;
    u.pt.Y = 128;
    int z = this->GetFloorHeight(u.pt);

    CoordStruct tmp;
    tmp.X = x;
    tmp.Y = y;
    tmp.Z = z;
    *pBuffer = tmp;
    return pBuffer;
}

// FUNCTION: GAMEMD 0x487D00  CellView_00480A30::RadLevel_Decrease (__thiscall)
//   RadLevel -= amount; clamp negatives to 0.0.
// PARTIAL (50.0%, 7/14). Retail keeps the subtraction result on the x87 stack
// across the branch and pops it once per arm - `FSTP ST0` in the clamp arm and
// `FSTP qword ptr [ECX+0xF0]` (a redundant re-store of the same value) in the
// pass-through arm - and writes the clamp as two immediate dword stores.
//
// Lift pass (2026-09-18) found the exact retail control flow: bind the
// subtraction to a named local, store it, and give the `if` an explicit `else`
// that re-stores the local:
//     double level = this->RadLevel - amount;
//     this->RadLevel = level;
//     if (0.0 > level) { this->RadLevel = 0.0; } else { this->RadLevel = level; }
// That form emits ALL 14 retail instructions in retail's order (multiset
// retail-only {}), including both per-arm FSTPs, and leaves exactly ONE extra
// instruction: cl 8804 materialises the 64-bit zero as `XOR EAX,EAX` plus two
// register stores where retail emits `MOV dword ptr [ECX+0xF0],0` /
// `MOV dword ptr [ECX+0xF4],0`. That single insertion shifts every later offset
// and scores 46.7%, below this variant's 50%, so the two-instruction-short form
// below is what stays committed. Spellings tried for the zero, all identical:
// `RadLevel = 0.0`, two `unsigned int` stores, two `volatile unsigned int`
// stores, `*(__int64*)&RadLevel = 0`. An `__asm` pair does emit the immediates
// but forces an EBP frame on the whole function (5.6%). Treat the zero
// materialisation as the 8447-vs-8804 "constants into registers" class; the
// control-flow shape above is the confirmed source shape.
void CellView_00480A30::RadLevel_Decrease(double amount)
{
    this->RadLevel -= amount;
    // 0.0 as the left operand makes cl emit `fld [0.0]; fcomp` (test ah,0x41),
    // matching retail's reversed compare against the still-stacked result.
    if (0.0 > this->RadLevel) {
        this->RadLevel = 0.0;
    }
}
