// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D6070.

#include "tactical_class_position_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local — the same inlined CoordsToScreen shape as
// match/renderer/tactical_class_coords_to_screen_methods.cpp (the address-taken
// local is what spills Y into the temporary's second slot and reloads it).
static inline Point2D_006D6070 IsoProject(const int* p)
{
    Point2D_006D6070 r;
    r.X = p[0] * 60 / 2;
    r.Y = p[0] * 30 / 2;
    r.X += p[1] * -60 / 2;
    r.Y += p[1] * 30 / 2;
    return r;
}

static inline Point2D_006D6070 CoordsToScreen(const Coord_006D6070* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D_006D6070 r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ_006D6070(pCoord->Z);
    return r;
}

// FUNCTION: GAMEMD 0x6D6070
//
// Move the tactical view so that the given world coordinate is its origin.
// The coordinate is projected to the iso screen point (CoordsToScreen inlined
// above, with the out-of-line AdjustForZ), taken relative to the view offset
// and back again on a register copy, then the copy is written to the clamp
// point and offered to the clamp helper; unless the game is in Armageddon mode
// the clamped point is what is kept. Both position pairs at +0xD64 and +0xD74
// take the point, the view is recomputed and the dirty byte at +0xD7D is set.
//
// PARTIAL (92.4%, 85/92). Every instruction is present in the same order; the
// residual is one stack slot. Retail's frame is 8 bytes: the inlined
// CoordsToScreen's return temporary, the iso projection's dead X spill, and
// the clamp point `pt` all share frame+0, so the post-divide X write-back
// (`MOV [ESP+0x10],ESI` after the AdjustForZ call) lands on `pt`. VC6 here
// gives the inlined helper's return value its own slot at frame+8
// (`SUB ESP,0x10`, `MOV [ESP+0x18],ESI`), which also moves `MOV ECX,EDI`
// ahead of the two X stores in the tail. Variants tried: plain int round trip
// (folds `- off + off` away, 44.6%); struct-valued Sub/Add helpers on the
// projection (accumulates into the offset register, 50.5-52.7%); member ops
// on the address-taken point itself (offset loads hoisted, 80.4-83.7%);
// scalar copies before the clamp (79.3%); a scoped block around the helper
// (80.4%); projecting straight into the clamp point with the ops on a copy
// (38.7-44.7%); assignment after declaration, and the out-pointer
// CoordsToScreen shape of the 0x6D1F10 sibling (both identical, 92.4%). This
// pass also tried `pos` declared ahead of `pt` (92.4%, no slot change) and the
// offset round trip moved into a by-value inline helper (79.3%). Filed as the
// recorded cl-8804 slot-merge class: cl refuses to overlap the inlined
// helper's return temporary with the address-taken local.
void Tactical_006D6070::SetTacticalPosition(const Coord_006D6070* pCoord)
{
    Point2D_006D6070 pt = CoordsToScreen(pCoord);
    Point2D_006D6070 pos = pt;
    pos.X -= this->Offset_B0.X;
    pos.Y -= this->Offset_B0.Y;
    pos.X += this->Offset_B0.X;
    pos.Y += this->Offset_B0.Y;
    pt = pos;
    if (this->FUN_006D8640(&pt) && DAT_00A8ED6B == 0) {
        pos = pt;
    }
    int x = pos.X;
    int y = pos.Y;

    this->TacticalPos.X = x;
    this->At_D74.X = x;
    this->TacticalPos.Y = y;
    this->At_D74.Y = y;
    this->FUN_006D8B30();
    this->At_D7D = 1;
}
