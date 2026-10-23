// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x484FF0, 0x485010, 0x485240,
//   0x487CE0),
//   cross-checked against YRpp (reconfirmed
//   numerically here). CellClass derives AbstractClass.
//
// CellClass — a single map cell. This TU models only the members touched by
// the three matched accessors:
//   * OverlayTypeIndex @0x44 (int)  — read by GetContainedTiberiumIndex
//   * MapCoords        @0x24 (CellStruct, 4 bytes) — written by SetMapCoords
//   * RadLevel         @0xF0 (double) — accumulated by RadLevel_Increase
// GetUIName reuses OverlayTypeIndex and the same 0x5FDD20 lookup as
// GetContainedTiberiumIndex, then indexes TiberiumClass::Array for the name.
#ifndef GG_MATCH_MAP_CELL_CLASS_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): copied as a single dword by
// SetMapCoords (mov edx,[eax]; mov [ecx+0x24],edx).
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Overlay-index -> tiberium-index lookup @0x5FDD20. Takes the overlay index in
// ECX (__fastcall single-int arg) and returns the tiberium index; declared
// (no body) so cl emits a relocatable tail-call. Confirmed from the disasm:
// GetContainedTiberiumIndex loads [ECX+0x44] into ECX then JMPs here.
int OverlayTypeIndexToTiberium(int idxOverlay);

// TiberiumClass — only the AbstractTypeClass UIName pointer at +0x60 is needed
// (GetUIName loads [EDX+0x60] from the array element). Full layout is P2.
class TiberiumClass
{
public:
    char           _pad00[0x60];   // +0x00  AbstractTypeClass prefix
    const wchar_t* UIName;         // +0x60
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, UIName) == 0x60);

// GLOBAL: GAMEMD 0x00B0F4EC — TiberiumClass::Array.Items (the vector object
// itself sits at 0x00B0F4E8; GetUIName reads the Items base directly).
extern TiberiumClass** TiberiumArrayItems;

// RulesClass shim — only the radiation ceiling is needed. GetRadLevel loads it
// with FILD, so it is an int in the rules even though the cell keeps a double.
struct RulesRadShim
{
    char _layout_pad_P2[0x180C];   // +0x0000
    int  RadLevelMax;              // +0x180C
};
GG_STATIC_ASSERT(offsetof(RulesRadShim, RadLevelMax) == 0x180C);

// GLOBAL: GAMEMD 0x008871E0 — pointer to the active RulesClass instance.
extern RulesRadShim* RulesGlobalPtr;

class CellClass
{
public:
    char       _base[0x24];                 // +0x00  AbstractClass (vtable + base)
    CellStruct MapCoords;                    // +0x24  written by SetMapCoords
    char       _pad28[0x44 - 0x28];          // +0x28
    int        OverlayTypeIndex;             // +0x44  read by GetContainedTiberiumIndex
    char       _pad48[0xF0 - 0x48];          // +0x48
    double     RadLevel;                     // +0xF0  accumulated by RadLevel_Increase

    // 0x484FF0
    const wchar_t* GetUIName() const;
    // 0x487CB0
    int GetRadLevel();
    // 0x485010
    int GetContainedTiberiumIndex() const;
    // 0x485240
    void SetMapCoords(CellStruct const* coords);
    // 0x487CE0
    void RadLevel_Increase(double amount);
};

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(CellClass, RadLevel) == 0xF0);

#endif  // GG_MATCH_MAP_CELL_CLASS_METHODS_H
