// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x69DE70 / 0x6CFD40),
//   cross-checked against YRpp ShapeButtonClass.h (consult-only, no LICENSE;
//   each offset reconfirmed against the user's binary below).
//
// ShapeButtonClass — a sidebar/UI shape (SHP) button. This TU adds ClearShape
// (frees the cached shape) and the static GetButton(index) table lookup. Only
// the members these two functions touch are modelled; the full
// ShapeButtonClass : ToggleClass layout is P2 work, so the base is padded.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_MORE_METHODS_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_MORE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

struct SHPStruct;

// ---------------------------------------------------------------------------
// ShapeButtonClass (partial)
//
// Members confirmed numerically from the two target functions:
//   Width          int   @0x14 (MOV [ESI+0x14], EBX  cleared by ClearShape)
//   Height         int   @0x18 (MOV [ESI+0x18], EBX  cleared by ClearShape)
//   ShapeData      void* @0x58 (read, freed, then nulled by ClearShape)
//   IsShapeLoaded  bool  @0x5c (gate + cleared by ClearShape)
// The whole object is 0x60 bytes — GetButton indexes an array with element
// stride 96 (LEA [eax+eax*2]; SHL 5), so the layout below pads to exactly 0x60.
// ---------------------------------------------------------------------------
struct ShapeButtonClass
{
    void ClearShape();                                       // GAMEMD 0x69DE70 __thiscall
    static ShapeButtonClass* __fastcall GetButton(int index);// GAMEMD 0x6CFD40 __fastcall

    char       _pad00[0x14];   // +0x00 : unknown ToggleClass/base bytes
    int        Width;          // +0x14
    int        Height;         // +0x18
    char       _pad1c[0x58 - 0x1c]; // +0x1c : unknown bytes up to ShapeData
    SHPStruct* ShapeData;      // +0x58
    bool       IsShapeLoaded;  // +0x5c
    char       _pad5d[0x60 - 0x5d]; // +0x5d : tail padding to a 0x60 object
};

GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Width) == 0x14);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Height) == 0x18);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ShapeData) == 0x58);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsShapeLoaded) == 0x5c);
GG_STATIC_ASSERT(sizeof(ShapeButtonClass) == 0x60);

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_MORE_METHODS_H
