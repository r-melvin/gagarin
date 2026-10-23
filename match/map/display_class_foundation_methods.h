// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4A94F0 / 0x4A95A0. FoundationBoundsSize walks a
//   list of 4-byte short pairs terminated by (0x7FFF, 0x7FFF) (`CMP AX,0x7FFF`
//   / `CMP [EDX+2],AX`, `ADD EDX,4`) and hands its 4-byte result back through
//   the hidden return pointer (`MOV [EAX],ECX` then `RET 8` with EAX = that
//   pointer); `this` is never read. MarkFoundation takes the same list from
//   `[EDI+0x117C]`, compares the base cell against the global pair at
//   0x8A03F8, and flips bit 1 of `[EAX+0x12C]` on each legal cell. The two
//   MapClass calls are 0x568300 (CoordinatesLegal) and 0x5657A0 (GetCellAt).
//   Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_DISPLAY_CLASS_FOUNDATION_METHODS_H
#define GG_MATCH_MAP_DISPLAY_CLASS_FOUNDATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// The retail sum is two 16-bit adds into a fresh pair (`ADD DX,[EBP]` /
// `ADD AX,[EBP+2]`), built in one slot and then copied into the local that
// is passed on: CellStruct::operator+ (_layout/cell.h) inlined.

// GLOBAL: GAMEMD 0x8A03F8 — the "no cell" sentinel pair MarkFoundation refuses.
extern CellStruct DAT_008A03F8;

// Only the flags dword at +0x12C is touched here.
class CellClass
{
public:
    char _pad000[0x12C];   // +0x0000
    int  Flags;            // +0x012C  bit 1 = foundation-marked
};
GG_STATIC_ASSERT(offsetof(CellClass, Flags) == 0x12C);

// DisplayClass (MapClass base included); only CurrentFoundationData at
// +0x117C and the two inherited cell queries are used.
class DisplayClass
{
public:
    char              _pad000[0x117C];        // +0x0000
    CellStruct const* CurrentFoundationData;  // +0x117C

    // FUNCTION: GAMEMD 0x568300 (decl; reloc) — MapClass::CoordinatesLegal.
    bool CoordinatesLegal(CellStruct const& cell) const;
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass* GetCellAt(CellStruct const& cell) const;

    // FUNCTION: GAMEMD 0x4A94F0
    CellStruct FoundationBoundsSize(CellStruct const* foundation) const;
    // FUNCTION: GAMEMD 0x4A95A0
    void MarkFoundation(CellStruct const* baseCell, bool mark);
};
GG_STATIC_ASSERT(offsetof(DisplayClass, CurrentFoundationData) == 0x117C);

#endif  // GG_MATCH_MAP_DISPLAY_CLASS_FOUNDATION_METHODS_H
