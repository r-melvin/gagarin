// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Member offsets and
//   globals reconfirmed numerically from the disasm at each method address;
//   field names cross-checked against YRpp MapClass.h / GScreenClass.h
//   (consult-only, no license).
//
//   Confirmed from disasm:
//     ObjectClass::IsInLogic   @ 0x98 (byte)  -- AddObject [ESI+0x98]
//     MapClass::Bitfield       @ 0x0c (int)   -- RedrawSidebar [ECX+0xc]
//     MapClass::MapRect.Width  @ 0xf4 (int)   -- CoordinatesLegal [ECX+0xf4]
//     MapClass::MapRect.Height @ 0xf8 (int)   -- CoordinatesLegal [ECX+0xf8]
//   MapClass derives GScreenClass (vptr@0,ScreenShakeX@4,ScreenShakeY@8,
//   Bitfield@0xc -> sizeof 0x10); MapRect lands at 0xEC, so Width@0xF4 /
//   Height@0xF8 (RectangleStruct = {X,Y,Width,Height}).
#ifndef GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass (IsInLogic @ 0x98)

// CellStruct — packed cell coordinate (two signed shorts). Self-guarded so
// other map TUs can reuse it.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);
#endif  // GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED

// GScreenClass::Instance @ 0x0087F7E8 — the single shared screen object whose
// vtable-less helper @ 0x00578AC0 (INC byte[this+0x1158]) is invoked by
// RedrawSidebar. Only the call shape matters; modelled as a one-method handle so
// cl emits `mov ecx, offset Instance` + `call` (both reloc-normalised).
struct GScreenClass
{
    void MarkToRedraw();   // retail 0x00578AC0 (not matched here)
};

// The global pointer dereferenced first in RedrawSidebar (@ 0x00887324). Its
// target carries a redraw flag at +0xD7D (byte). Partial model up to that byte.
struct SidebarRedrawTarget
{
    char          pad_00[0xD7D];
    unsigned char NeedsRedraw;   // +0xD7D
};
GG_STATIC_ASSERT(offsetof(SidebarRedrawTarget, NeedsRedraw) == 0xD7D);

// MapClass (partial) — only the members the three matched methods touch.
struct MapClass
{
    char pad_00[0x0C];
    int  Bitfield;                 // +0x0C  (default 2)
    char pad_10[0xF4 - 0x10];
    int  MapRectWidth;             // +0xF4  (MapRect.Width)
    int  MapRectHeight;            // +0xF8  (MapRect.Height)

    // 0x4F42D0 — unconditional `Bitfield = 2`, sibling of RedrawSidebar's
    // conditional set. No YRpp/seed-map name covers it; kept as a placeholder.
    void FUN_004F42D0();
    // 0x4F42F0
    void RedrawSidebar(int mode);
    // 0x55BAA0
    bool AddObject(ObjectClass* pObject, bool sorted);
    // 0x568300
    bool CoordinatesLegal(const CellStruct& cell) const;

    // Helper forwarded to by AddObject (retail 0x005519B0, this=MapClass).
    // Declared only so cl emits a reloc-normalised __thiscall call.
    bool SubmitObject(ObjectClass* pObject, bool sorted);
};

GG_STATIC_ASSERT(offsetof(MapClass, Bitfield)       == 0x0C);
GG_STATIC_ASSERT(offsetof(MapClass, MapRectWidth)   == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, MapRectHeight)  == 0xF8);

#endif  // GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H
