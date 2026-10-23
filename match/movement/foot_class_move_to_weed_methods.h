// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4DDB90: `[ESI+0x5A4]` (Destination in the committed
//   FootClass spine), the __thiscall helper 0x4DD890 taking a hidden return
//   pointer plus the radius (`PUSH EAX; PUSH ECX; CALL`), the invalid-cell
//   global compared word-wise (`CMP AX,[0x8B3D88]` / `CMP DX,[0x8B3D8A]`),
//   the coordinate slot `CALL [EAX+0x48]` with one pushed out-pointer, the
//   map singleton as the immediate `MOV ECX,0x87F7E8` feeding CALL 0x5657A0
//   (MapClass::GetCellAt), and the destination slot `CALL [EDI+0x480]` with
//   (cell, 1) pushed. Names from YRpp;
//   every offset re-derived here.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass: Destination @0x5A4; CoordStruct; CellStruct
#include "../_layout/cell_class.h"

extern CellStruct DAT_008B3D88;

struct Map_004DDB90
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass* GetCellAt(CellStruct const& cell);
};
extern Map_004DDB90 DAT_0087F7E8;

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H
