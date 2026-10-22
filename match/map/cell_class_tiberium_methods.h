// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe via the local Ghidra CLI
//   (member-access disassembly at 0x485020 and 0x487690), cross-checked against
//   YRpp (reconfirmed numerically
//   here from the disasm). CellClass derives AbstractClass.
//
// CellClass — a single map cell. This TU models ONLY the members touched by the
// two matched methods:
//   * OverlayTypeIndex      @0x044 (int)            — read by GetContainedTiberiumValue
//   * OverlayData           @0x11E (unsigned char)  — read by GetContainedTiberiumValue
//   * ShroudCounter         @0x130 (int)            — bumped by IncreaseShroudCounter
//   * GapsCoveringThisCell  @0x134 (int)            — clamp ceiling for ShroudCounter
//   * Flags                 @0x140 (CellFlags/dword)— |= 0x20 by IncreaseShroudCounter
#ifndef GG_MATCH_MAP_CELL_CLASS_TIBERIUM_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_TIBERIUM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// TiberiumClass — only the Value field at +0xB8 is touched (read by
// GetContainedTiberiumValue: mov eax,[edx+0xb8]). The binary places Value at
// 0xB8 regardless of YRpp's nominal double-packing, so pad to it directly.
struct TiberiumClass
{
    char _pad[0xB8];   // +0x00  AbstractTypeClass base + leading int/double props
    int  Value;        // +0xB8
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);

// Global base pointer of the Tiberium array @ 0x00B0F4EC. The retail loads the
// dword there as a TiberiumClass** then indexes it: mov ecx,[0xb0f4ec];
// mov edx,[ecx+eax*4]. Declared (no definition) so cl emits a relocatable load.
extern TiberiumClass** TiberiumArrayItems;

// Overlay-index -> tiberium-index lookup @0x5FDD20. Takes the overlay index in
// ECX (__fastcall single-int arg), returns the tiberium index or -1. Declared
// (no body) so cl emits a relocatable call.
int __fastcall OverlayTypeIndexToTiberium(int idxOverlay);

// CellFlags is a 32-bit flag enum; modelling it as an enum makes cl materialise
// the |= as load / or al,0x20 / store (the byte-OR the retail emits).
enum CellFlags
{
    CellFlags_None = 0
};

struct CellClass
{
    char       _base[0x44];                  // +0x000  AbstractClass + leading props
    int        OverlayTypeIndex;             // +0x044
    char       _pad48[0x11E - 0x48];         // +0x048
    unsigned char OverlayData;               // +0x11E
    char       _pad11F[0x130 - 0x11F];       // +0x11F
    int        ShroudCounter;                // +0x130
    int        GapsCoveringThisCell;         // +0x134
    char       _pad138[0x140 - 0x138];       // +0x138
    CellFlags  Flags;                        // +0x140

    // 0x485020
    int GetContainedTiberiumValue() const;
    // 0x487690
    void IncreaseShroudCounter();
};

GG_STATIC_ASSERT(offsetof(CellClass, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(CellClass, OverlayData) == 0x11E);
GG_STATIC_ASSERT(offsetof(CellClass, ShroudCounter) == 0x130);
GG_STATIC_ASSERT(offsetof(CellClass, GapsCoveringThisCell) == 0x134);
GG_STATIC_ASSERT(offsetof(CellClass, Flags) == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_TIBERIUM_METHODS_H
