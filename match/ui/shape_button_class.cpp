// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Flag bisection: /GX adds exception-unwind code absent from the complete
// 0x69DDC0 destructor. Omitting it reproduces that body; all other methods
// in this TU are reverified with this same flag set.
//   Definitions are ordered by their retail addresses. Layouts, call sites,
//   globals and callee conventions are confirmed by the user's retail
//   gamemd.exe v1.001; YRpp is a naming reference only.
//
// FUNCTION: GAMEMD 0x69DE70 ShapeButtonClass::ClearShape (__thiscall)
// FUNCTION: GAMEMD 0x69DEA0 ShapeButtonClass::SetLoadedStatus (__thiscall)
// FUNCTION: GAMEMD 0x69DFC0 ShapeButtonClass::StartFlashing (__thiscall)
// FUNCTION: GAMEMD 0x69DFF0 ShapeButtonClass::StopFlashing (__thiscall)
// FUNCTION: GAMEMD 0x69E010 ShapeButtonClass::AI (__thiscall)
// FUNCTION: GAMEMD 0x6CFCC0 ShapeButtonClass::FindIndex (__fastcall)
// FUNCTION: GAMEMD 0x6CFD40 ShapeButtonClass::GetButton (__fastcall)
// FUNCTION: GAMEMD 0x6D09C0 ShapeButtonClass::SetToolTip (__fastcall)
// LIBRARY: GAMEMD 0x7C8B3D GameDelete

// SYNTHETIC: GAMEMD 0x4B57F0
// ShapeButtonClass::`scalar deleting destructor'

#include "shape_button_class.h"
#include "shape_button_class_support.h"
#include <string.h>  // strcmp (intrinsic under /O2)

// Retail caller at 0x69DE82 uses push arg; call; add esp,4.
void __cdecl GameDelete(void* block);

// FUNCTION: GAMEMD 0x0069DDC0
// Complete raw span is 0x39 bytes, ending at RET 0x69DDF8. Ghidra's
// function body omits the cleanup after GameDelete; retain that full tail.
ShapeButtonClass::~ShapeButtonClass()
{
    if (IsShapeLoaded && ShapeData != 0) {
        GameDelete(ShapeData);
        ShapeData = 0;
        IsShapeLoaded = false;
        Width = 0;
        Height = 0;
    }
}

// FUNCTION: GAMEMD 0x69DE70
void ShapeButtonClass::ClearShape()
{
    if (this->IsShapeLoaded && this->ShapeData != 0)
    {
        GameDelete(this->ShapeData);
        this->ShapeData = 0;
        this->IsShapeLoaded = 0;
        this->Width = 0;
        this->Height = 0;
    }
}

// FUNCTION: GAMEMD 0x69DEA0
void ShapeButtonClass::SetLoadedStatus(bool status)
{
    this->IsShapeLoaded = status;
}

// FUNCTION: GAMEMD 0x69DFC0
bool ShapeButtonClass::StartFlashing(int nDelay, int nInitDelay, bool bStart)
{
    if (this->FlashDelay == 0)
    {
        this->FlashDelay = nDelay;
        this->FlashCounter = nDelay + nInitDelay;
        this->IsToFlash = bStart;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x69DFF0
bool ShapeButtonClass::StopFlashing()
{
    if (this->FlashDelay != 0)
    {
        this->IsToFlash = 0;
        this->FlashCounter = 0;
        this->FlashDelay = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x69E010
bool ShapeButtonClass::AI()
{
    if (this->IsDisabled != 0)
    {
        if (this->FlashDelay != 0)
        {
            this->IsToFlash = 0;
            this->FlashCounter = 0;
            this->FlashDelay = 0;
            return true;
        }
    }
    else if (this->FlashCounter != 0)
    {
        if (--this->FlashCounter == 0)
        {
            this->IsToFlash = (this->IsToFlash == 0);
            this->FlashCounter = this->FlashDelay;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6CFCC0
int ShapeButtonClass::FindIndex(const char* name)
{
    int index = 0;
    const char* const* p;
    for (p = CommandNames; (int)p < (int)(CommandNames + 11); ++p)
    {
        if (strcmp(*p, name) == 0)
            return index;
        ++index;
    }
    return DefaultCommandIndex;
}

// FUNCTION: GAMEMD 0x6CFD40
ShapeButtonClass* ShapeButtonClass::GetButton(int index)
{
    int slot = ButtonIndexTable[index];
    if (slot >= 0 && slot < 0x19)
        return &ButtonArray[slot];
    return 0;
}

// FUNCTION: GAMEMD 0x6D09C0
void ShapeButtonClass::SetToolTip(ShapeButtonClass* pButton,
                                  const char* tip)
{
    if (pButton)
    {
        ToolTip tooltip;
        tooltip.Text = tip;
        tooltip.field_18 = false;
        tooltip.GadgetID = pButton->ID;
        tooltip.Bounds.X = pButton->X;
        tooltip.Bounds.Y = pButton->Y;
        tooltip.Bounds.Width = pButton->Width;
        tooltip.Bounds.Height = pButton->Height;
        ToolTipManager_Instance->Remove(tooltip.GadgetID);
        ToolTipManager_Instance->Add(tooltip);
    }
}
