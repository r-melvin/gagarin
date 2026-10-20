// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x69DEA0 / 0x69DFC0 /
//   0x69DFF0), cross-checked against YRpp ShapeButtonClass.h (consult-only, no
//   LICENSE; each offset reconfirmed against the user's binary below).
//
// ShapeButtonClass — a sidebar/UI shape (SHP) button. Only the flash-control
// accessors are modelled here; the full ShapeButtonClass : ToggleClass layout
// is P2 work, so the unknown base is padded to the first touched offset.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_METHODS_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ShapeButtonClass (partial)
//
// Members confirmed numerically from the three target functions:
//   IsToFlash      bool @0x34  (MOV [ECX/ESI+0x34], al  in Start/StopFlashing)
//   FlashDelay     int  @0x38  (MOV [ECX+0x38] read+write)
//   FlashCounter   int  @0x3c  (MOV [ECX+0x3c] write)
//   IsShapeLoaded  bool @0x5c  (MOV [ECX+0x5c], al  in SetLoadedStatus)
// ---------------------------------------------------------------------------
struct ShapeButtonClass
{
    // Declared ascending by retail address (reccmp/isle TU discipline).
    void SetLoadedStatus(bool status);                    // GAMEMD 0x69DEA0 __thiscall
    bool StartFlashing(int nDelay, int nInitDelay, bool bStart);  // GAMEMD 0x69DFC0 __thiscall
    bool StopFlashing();                                  // GAMEMD 0x69DFF0 __thiscall

    char  _pad0[0x34];     // +0x00 : unknown ToggleClass/base bytes
    bool  IsToFlash;       // +0x34
    char  _pad35[3];       // +0x35 : alignment to the next int
    int   FlashDelay;      // +0x38
    int   FlashCounter;    // +0x3c
    char  _pad40[0x5c - 0x40];  // +0x40 : unknown bytes up to IsShapeLoaded
    bool  IsShapeLoaded;   // +0x5c
};

GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsToFlash) == 0x34);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashDelay) == 0x38);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashCounter) == 0x3c);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsShapeLoaded) == 0x5c);

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_METHODS_H
