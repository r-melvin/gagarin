// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   ShapeButtonClass member offsets and object size are confirmed by retail
//   gamemd.exe v1.001 instructions at 0x69DE70, 0x69DEA0, 0x69DFC0,
//   0x69DFF0, 0x69E010, and 0x6D09C0. GetButton at 0x6CFD40 indexes
//   elements with a 0x60-byte stride. RTTI at vtable 0x7E8088 identifies
//   the ToggleClass -> ControlClass -> GadgetClass -> LinkClass base chain.
//   The constructor 0x69DD30 stores +0x34..+0x4C, +0x50 (from [0x87F6C4]), +0x55
//   and +0x58; Draw 0x69DEB0 reads +0x40..+0x55; slot 34 (+0x88) is
//   0x69DE00.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "toggle_class_methods.h"

struct SHPStruct;

// VTABLE: GAMEMD 0x7E8088
class ShapeButtonClass : public ToggleClass
{
public:
    // Retail slot 0 reaches deleting destructor 0x4B57F0, which calls 0x69DDC0.
    // FUNCTION: GAMEMD 0x69DDC0 (decl)
    virtual ~ShapeButtonClass();
    // FUNCTION: GAMEMD 0x69DEB0 (decl; slot 27 / +0x6C)
    virtual int Draw(int forced);
    // FUNCTION: GAMEMD 0x69DE00 (decl; slot 34 / +0x88, first ShapeButton slot)
    virtual void vf_34(SHPStruct* shape, int width, int height);

    // Recovered method declarations follow ascending retail function address.
    void ClearShape();                                                   // 0x69DE70
    void SetLoadedStatus(bool status);                                   // 0x69DEA0
    bool StartFlashing(int nDelay, int nInitDelay, bool bStart);         // 0x69DFC0
    bool StopFlashing();                                                 // 0x69DFF0
    bool AI();                                                           // 0x69E010
    static int FindIndex(const char* name);                   // 0x6CFCC0
    static ShapeButtonClass* GetButton(int index);            // 0x6CFD40
    static void SetToolTip(ShapeButtonClass* pButton,
                                     const char* tip);                   // 0x6D09C0

    // ToggleClass supplies the confirmed prefix through +0x33.
    bool IsToFlash;                 // +0x34, AI / flashing methods
    char unknown_35[3];
    int FlashDelay;                 // +0x38, AI / flashing methods
    int FlashCounter;               // +0x3C, AI / flashing methods
    unsigned char HasFrames;        // +0x40, Draw: pressed vs latched frame
    unsigned char unknown_41[3];
    int OffsetX;                    // +0x44, Draw: added to X
    int OffsetY;                    // +0x48, Draw: added to Y
    unsigned char UsesSidebarSurface; // +0x4C, Draw: [0x887300] instead of [0x887314]
    unsigned char unknown_4D[3];
    void* Convert;                  // +0x50, ctor stores [0x87F6C4]; 2nd argument of the 0x4AED70 blitter
    unsigned char unknown_54;       // +0x54, Draw sets 1
    unsigned char unknown_55;       // +0x55, ctor's last argument; Draw selects flag 0x800
    unsigned char unknown_56[2];
    SHPStruct* ShapeData;           // +0x58, ClearShape
    bool IsShapeLoaded;             // +0x5C, ClearShape / SetLoadedStatus
    char unknown_5D[3];
};

GG_STATIC_ASSERT(offsetof(ShapeButtonClass, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Width) == 0x14);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Height) == 0x18);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsDisabled) == 0x1E);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsToFlash) == 0x34);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_35) == 0x35);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashDelay) == 0x38);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashCounter) == 0x3C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, HasFrames) == 0x40);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, OffsetX) == 0x44);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, OffsetY) == 0x48);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, UsesSidebarSurface) == 0x4C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Convert) == 0x50);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_55) == 0x55);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ShapeData) == 0x58);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsShapeLoaded) == 0x5C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, unknown_5D) == 0x5D);
GG_STATIC_ASSERT(sizeof(ShapeButtonClass) == 0x60);

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_H
