// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4ACA10: the cell's flag word `[EAX+0x140]` (bit
//   0x100 tested as `TEST CH,1`), its signed level byte `MOVSX ECX,[EAX+0x11B]`,
//   the coordinate's Z `[ESI+0x8]`, the level height global `IMUL ECX,[0x8A0740]`,
//   and the map singleton as the immediate `MOV ECX,0x87F7E8`. The callee at
//   0x565730 reads `[EDI]`/`[EDI+4]` of its argument (a CoordStruct), and the
//   one at 0x481180 takes five stack arguments (out, coords, three bytes).
//   Names (PickInfantrySublocation, FindInfantrySubposition, GetCellAt, Level,
//   Flags) cross-checked against YRpp.
#ifndef GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// CellClass (partial) — only the members PickInfantrySublocation reads.
class CellClass
{
public:
    char _pad000[0x11B];            // +0x0000
    char Level;                     // +0x011B  signed (MOVSX)
    char _pad11C[0x140 - 0x11C];    // +0x011C
    int  Flags;                     // +0x0140  bit 0x100 = cell has a bridge

    // FUNCTION: GAMEMD 0x481180 (decl; reloc) — the sub-position search;
    // returned by value (hidden 12-byte result slot at [ESP+4]).
    CoordStruct FindInfantrySubposition(const CoordStruct& coords, bool ignoreContents,
                                        bool alt, bool useCellCoords);
};
GG_STATIC_ASSERT(offsetof(CellClass, Level) == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, Flags) == 0x140);

// GLOBAL: GAMEMD 0x8A0740 — the height of one cell level in leptons.
extern int DAT_008A0740;

// MapClass (partial) — no members are touched; only the singleton's address
// and one method matter here.
class MapClass
{
public:
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — the cell under a coordinate.
    CellClass* GetCellAt(const CoordStruct& coords);

    // FUNCTION: GAMEMD 0x4ACA10
    // A __thiscall member whose `this` goes unused (ECX is overwritten with the
    // singleton's address on the second instruction); the receiver is not a
    // stack argument, so `RET 0xC` covers the hidden result slot, the
    // coordinate reference and the flag. Written `static __stdcall` (the same
    // stack shape) VC6 schedules the result copy differently — see the .cpp.
    CoordStruct PickInfantrySublocation(const CoordStruct& coords, bool ignoreContents);
};

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F7E8`).
extern MapClass DAT_0087F7E8;

#endif  // GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H
