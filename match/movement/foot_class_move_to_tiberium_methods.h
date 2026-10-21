// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4DCFE0: Destination `[ESI+0x5A4]` (agrees with
//   match/_layout/foot_class.h), the cell-search slot `[EAX+0x338]` (hidden
//   4-byte buffer plus the two arguments, RET 0xC), GetCoords `[EAX+0x48]`
//   (hidden 12-byte buffer `LEA ECX,[ESP+0x8]`), SetDestination `[EDI+0x480]`
//   called with (cell, 1), `MOV ECX,0x87F7E8` feeding CALL 0x5657A0
//   (MapClass::GetCellAt) and the word-wise compare against 0x8B3D88/0x8B3D8A
//   (the "no cell" sentinel). The method name is YRpp's FootClass::MoveToTiberium
//   (name only). The address-scoped receiver retains binary-backed offsets
//   and virtual calls; it does not model the complete FootClass hierarchy.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_TIBERIUM_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_TIBERIUM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_004DCFE0
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_004DCFE0) == 4);

struct Coord_004DCFE0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_004DCFE0) == 0xC);

struct CellClass_004DCFE0;

struct Map_004DCFE0
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_004DCFE0* GetCellAt(Cell_004DCFE0 const& cell);
};

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F7E8`).
extern Map_004DCFE0 MapInstance_004DCFE0;

// GLOBAL: GAMEMD 0x8B3D88 — the "no cell" CellStruct sentinel.
extern Cell_004DCFE0 NoCell_004DCFE0;

// Declaration order per match/_rt/gg_vslot.h.
struct Vtbl_004DCFE0;

struct Obj_004DCFE0
{
    Vtbl_004DCFE0* Vtbl;                   // +0x0000
    char           _pad004[0x5A4 - 0x4];   // +0x0004
    void*          Destination;            // +0x05A4

    // FUNCTION: GAMEMD 0x4DCFE0 — FootClass::MoveToTiberium.
    bool MoveToTiberium(int radius, int scanClose);
};
GG_STATIC_ASSERT(offsetof(Obj_004DCFE0, Destination) == 0x5A4);

typedef Coord_004DCFE0* (Obj_004DCFE0::*Fn48_004DCFE0)(Coord_004DCFE0* out);
typedef Cell_004DCFE0* (Obj_004DCFE0::*Fn338_004DCFE0)(Cell_004DCFE0* out, int radius, int scanClose);
typedef void (Obj_004DCFE0::*Fn480_004DCFE0)(CellClass_004DCFE0* target, int flag);

struct Vtbl_004DCFE0
{
    char            _pad000[0x48];            // +0x0000
    Fn48_004DCFE0   GetCoords;                // +0x0048
    char            _pad04C[0x338 - 0x4C];    // +0x004C
    Fn338_004DCFE0  At_338;                   // +0x0338
    char            _pad33C[0x480 - 0x33C];   // +0x033C
    Fn480_004DCFE0  SetDestination;           // +0x0480
};
GG_STATIC_ASSERT(offsetof(Vtbl_004DCFE0, GetCoords)      == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_004DCFE0, At_338)         == 0x338);
GG_STATIC_ASSERT(offsetof(Vtbl_004DCFE0, SetDestination) == 0x480);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_MOVE_TO_TIBERIUM_METHODS_H
