// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// GScreenClass entries (layout and evidence: display_gscreen.h).

#include <string.h>
#include "display_gscreen.h"

#pragma intrinsic(memcmp)

// FUNCTION: GAMEMD 0x40D230
unsigned long __stdcall GScreenClass::AddRef()
{
    return 1;
}

// FUNCTION: GAMEMD 0x40D240
unsigned long __stdcall GScreenClass::Release()
{
    return 1;
}

// FUNCTION: GAMEMD 0x4F4220
// Expansion row (neighbour, not an assigned address): VC6 emits the vtable and the scalar deleting destructor 0x4F4C00 only
// in a translation unit that defines a constructor, so the constructor is taken here.
GScreenClass::GScreenClass()
    : unknown_04(0), unknown_08(0), RedrawFlag(2)
{
}

// SYNTHETIC: GAMEMD 0x4F4C00
// GScreenClass scalar deleting destructor, emitted from the inline destructor in ui_display_chain.h.

// FUNCTION: GAMEMD 0x4F4240
long __stdcall GScreenClass::QueryInterface(const DisplayGuid* riid, void** ppv)
{
    if (ppv == 0)
        return 0x80004003;
    if (memcmp(riid, &IID_IUnknown_007F7C90, sizeof(DisplayGuid)) != 0
        && memcmp(riid, &IID_GScreen_007EA6E8, sizeof(DisplayGuid)) != 0)
        return 0x80004002;
    *ppv = this;
    AddRef();
    return 0;
}

// FUNCTION: GAMEMD 0x4F42B0
void GScreenClass::vf_06(int)
{
    vf_07();
    vf_08();
}

// FUNCTION: GAMEMD 0x4F4320
void GScreenClass::Input(int* key, int* x, int* y)
{
    *x = WWMouseClassInstance->vf_11();
    *y = WWMouseClassInstance->vf_12();
    if (DisplayButtonList_00A8EF54)
    {
        if (DisplayButtonList_00A8EF54->IsActive())
            FlagToRedraw(0);
        DisplaySurface* saved = DisplaySurface_00887314;
        DisplaySurface_00887314 = DisplaySurface_0088730C;
        *key = DisplayButtonList_00A8EF54->Input();
        DisplaySurface_00887314 = saved;
    }
    else
    {
        *key = DisplayKeyboard_0087F770->FUN_0054F000() & 0xFFFF;
        if (*key)
            *key = DisplayKeyboard_0087F770->FUN_0054F050() & 0xFFFF;
    }
    Point2D where;
    where.X = *x;
    where.Y = *y;
    vf_10(key, &where);
}

// FUNCTION: GAMEMD 0x4F43F0
bool GScreenClass::IsButtonListHead(DisplayGadget* gadget)
{
    return DisplayButtonList_00A8EF54 == gadget->GetHead();
}

// FUNCTION: GAMEMD 0x4F4410
bool GScreenClass::AddButton(DisplayGadget* gadget)
{
    if (IsButtonListHead(gadget))
        return false;
    if (DisplayButtonList_00A8EF54)
        gadget->AppendTo(DisplayButtonList_00A8EF54);
    else
        DisplayButtonList_00A8EF54 = gadget;
    return true;
}

// FUNCTION: GAMEMD 0x4F4450
bool GScreenClass::vf_13(DisplayGadget* gadget)
{
    if (!IsButtonListHead(gadget))
        return false;
    DisplayButtonList_00A8EF54 = gadget->Unlink();
    return true;
}

// FUNCTION: GAMEMD 0x4F45B0
void GScreenClass::vf_17()
{
    if (DisplayFlag_008A0DF0 && DisplayLayer_008A0E08)
    {
        if (DisplayDevice_008A0DF8->BeginScene() == 0)
        {
            if (DisplayLayer_008A0E08->FUN_004A33A0(0) == 0)
            {
                if (DisplayLayer_008A0E0C && DisplayLayer_008A0E0C->FUN_004A33A0(0) != 0)
                    goto endScene;
                if (DisplayLayer_008A0E10)
                {
                    if (DisplayLayer_008A0E0C)
                    {
                        DisplayTriangle first(0x80, 0x80, 0x80);
                        DisplayTriangle second(0x80, 0x80, 0x80);
                        first.SetVertex(0, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
                        first.SetVertex(1, 0.0f, 255.0f, 0.01f, 0.0f, 1.0f);
                        first.SetVertex(2, 255.0f, 255.0f, 0.01f, 1.0f, 1.0f);
                        second.SetVertex(0, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
                        second.SetVertex(1, 255.0f, 255.0f, 0.01f, 1.0f, 1.0f);
                        second.SetVertex(2, 255.0f, 0.0f, 0.01f, 1.0f, 0.0f);
                        DisplayLayer_008A0E10->FUN_004A3840(&first);
                        DisplayLayer_008A0E10->FUN_004A3840(&second);
                    }
                    DisplayLayer_008A0E10->FUN_004A3660(DisplaySurface_0088731C->unknown_1C);
                }
            }
        endScene:
            DisplayDevice_008A0DF8->EndScene();
        }
    }
    if (!DisplayFlag_00A9FA94)
    {
        FUN_004F4780(false, DisplaySurface_0088731C, 0);
        DisplayFlag_00A9FA94 = false;
    }
}

// FUNCTION: GAMEMD 0x4F4BB0
void GScreenClass::vf_10(int*, Point2D*)
{
    if (DisplayCurrentFrame_00A8ED84 & 1)
        return;
    if (unknown_04 < 0)
        unknown_04 = -1 - unknown_04;
    else if (unknown_04 > 0)
        unknown_04 = 1 - unknown_04;
    if (unknown_08 < 0)
        unknown_08 = -1 - unknown_08;
    else if (unknown_08 > 0)
        unknown_08 = 1 - unknown_08;
}
