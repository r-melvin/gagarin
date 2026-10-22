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
//   (cell, 1) pushed. Names from YRpp FootClass.h / MapClass.h
//   (consult-only, NO LICENSE); every offset re-derived here.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/foot_class.h"   // FootClass: Destination @0x5A4; CoordStruct; CellStruct

// A 2D cell coordinate with a user-declared constructor: that is what makes
// VC6 return it through a hidden pointer (a POD of this size would come back in
// EAX), which is how retail's helper at 0x4DD890 hands it back.
struct Cell_004DDB90
{
    short X;   // +0x00
    short Y;   // +0x02
    Cell_004DDB90() {}
};
GG_STATIC_ASSERT(sizeof(Cell_004DDB90) == 4);

// GLOBAL: GAMEMD 0x8B3D88 — the "no cell" sentinel the helper returns.
extern CellStruct DAT_008B3D88;

// The map singleton — only GetCellAt is reached (declared; reloc).
struct Map_004DDB90
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    void* GetCellAt(Cell_004DDB90 const& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_004DDB90 DAT_0087F7E8;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct WeedVtbl;

// No-data host over the committed FootClass spine; layout identical.
struct FootWeed : FootClass
{
    // FUNCTION: GAMEMD 0x4DD890 (decl; reloc) — find a weed cell within
    // `radius` of this object; the sentinel when there is none.
    Cell_004DDB90 FindWeedCell(int radius);

    // FUNCTION: GAMEMD 0x4DDB90
    bool MoveToWeed(int radius);
};

typedef CoordStruct* (IPersistStream::*Fn048_Weed)(CoordStruct* out);
typedef void         (IPersistStream::*Fn480_Weed)(void* dest, bool unk);

struct WeedVtbl
{
    char       _pad000[0x48];            // +0x0000
    Fn048_Weed GetCoords;                // +0x0048
    char       _pad04C[0x480 - 0x4C];    // +0x004C
    Fn480_Weed SetDestination;           // +0x0480
};
GG_STATIC_ASSERT(offsetof(WeedVtbl, GetCoords)      == 0x48);
GG_STATIC_ASSERT(offsetof(WeedVtbl, SetDestination) == 0x480);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_WEED_METHODS_H
