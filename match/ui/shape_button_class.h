// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   ShapeButtonClass member offsets and object size are confirmed by retail
//   gamemd.exe v1.001 instructions at 0x69DE70, 0x69DEA0, 0x69DFC0,
//   0x69DFF0, 0x69E010, and 0x6D09C0. GetButton at 0x6CFD40 indexes
//   elements with a 0x60-byte stride. The prefix is opaque; base-class
//   inheritance consolidation is pending evidence-backed base layouts.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SHPStruct;

struct ShapeButtonClass
{
    // Declarations follow ascending retail function address.
    void ClearShape();                                                   // 0x69DE70
    void SetLoadedStatus(bool status);                                   // 0x69DEA0
    bool StartFlashing(int nDelay, int nInitDelay, bool bStart);         // 0x69DFC0
    bool StopFlashing();                                                 // 0x69DFF0
    bool AI();                                                           // 0x69E010
    static int __fastcall FindIndex(const char* name);                   // 0x6CFCC0
    static ShapeButtonClass* __fastcall GetButton(int index);            // 0x6CFD40
    static void __fastcall SetToolTip(ShapeButtonClass* pButton,
                                     const char* tip);                   // 0x6D09C0

    // Opaque object prefix. The RTTI chain identifies bases, but their
    // layouts have not yet been consolidated into this declaration.
    char unknown_00[0x0C];
    int X;                          // +0x0C, SetToolTip
    int Y;                          // +0x10, SetToolTip
    int Width;                      // +0x14, ClearShape / SetToolTip
    int Height;                     // +0x18, ClearShape / SetToolTip
    char unknown_1C[2];
    bool field_1e;                  // +0x1E, AI
    char unknown_1F[5];
    unsigned int ID;                // +0x24, SetToolTip
    char unknown_28[0x0C];
    bool IsToFlash;                 // +0x34, AI / flashing methods
    char unknown_35[3];
    int FlashDelay;                 // +0x38, AI / flashing methods
    int FlashCounter;               // +0x3C, AI / flashing methods
    char unknown_40[0x18];
    SHPStruct* ShapeData;           // +0x58, ClearShape
    bool IsShapeLoaded;             // +0x5C, ClearShape / SetLoadedStatus
    char unknown_5D[3];
};

GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Width) == 0x14);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Height) == 0x18);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, field_1e) == 0x1E);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_1F) == 0x1F);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsToFlash) == 0x34);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_35) == 0x35);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashDelay) == 0x38);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashCounter) == 0x3C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ShapeData) == 0x58);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsShapeLoaded) == 0x5C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_5D) == 0x5D);
GG_STATIC_ASSERT(sizeof(ShapeButtonClass) == 0x60);

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_H
