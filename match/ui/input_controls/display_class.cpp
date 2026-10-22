// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// DisplayClass entries (layout and evidence: display_class.h).

#include "display_class.h"

// FUNCTION: GAMEMD 0x4A8850
void DisplayClass::vf_05()
{
    MapClass::vf_05();
    DisplayPlaceShape_008A03FC = FUN_005B40B0("PLACE.SHP", false);
    DisplayShadowShape_008A072C = FUN_005B40B0("SHADOW.SHP", false);
    RectangleStruct scratch;
    RectangleStruct rect = *FUN_0072AD20(&scratch);
    vf_42(&rect);
}

// FUNCTION: GAMEMD 0x4A8960
void DisplayClass::vf_42(const RectangleStruct* rect)
{
    FUN_004068E0("Set_View_Dimensions(%d,%d,%d,%d)\n", rect->X, rect->Y, rect->Width, rect->Height);
    DisplayViewRect_00886FA0.Origin.X = rect->X;
    DisplayViewRect_00886FA0.Origin.Y = rect->Y;
    DisplayViewRect_00886FA0.Width = rect->Width;
    DisplayViewRect_00886FA0.Height = rect->Height;
    if (DisplayTactical_00887324)
    {
        DisplayTactical_00887324->FUN_006D5F60(&DisplayViewRect_00886FA0);
        WWMouseClassInstance->vf_3();
        if (DisplayZBuffer_00887644)
        {
            FUN_004068E0("Deleting ZBuffer\n");
            DisplayZBuffer* old = DisplayZBuffer_00887644;
            if (old)
            {
                old->ReleaseSurface();
                delete old;
            }
            DisplayZBuffer_00887644 = 0;
        }
        DisplayZBuffer_00887644 = new DisplayZBuffer(DisplayViewRect_00886FA0);
        DisplayZBuffer_00887644->unknown_24 = 0x8000;
        FUN_004068E0("Allocating ZBuffer (%dx%d)\n", DisplayViewRect_00886FA0.Width, DisplayViewRect_00886FA0.Height);
        if (DisplayABuffer_0087E8A4)
        {
            FUN_004068E0("Deleting ABuffer\n");
            DisplayABuffer* old = DisplayABuffer_0087E8A4;
            if (old)
            {
                old->ReleaseSurface();
                delete old;
            }
            DisplayABuffer_0087E8A4 = 0;
        }
        DisplayABuffer_0087E8A4 = new DisplayABuffer(DisplayViewRect_00886FA0);
        FUN_004068E0("Allocating ABuffer (%dx%d)\n", DisplayViewRect_00886FA0.Width, DisplayViewRect_00886FA0.Height);
        WWMouseClassInstance->vf_4();
    }
    Map_0087F7E8.vf_34();
    DisplayViewRectCopy_008A0704.Origin.X = DisplayViewRect_00886FA0.Origin.X;
    DisplayViewRectCopy_008A0704.Origin.Y = DisplayViewRect_00886FA0.Origin.Y;
    DisplayViewRectCopy_008A0704.Width = DisplayViewRect_00886FA0.Width;
    DisplayViewRectCopy_008A0704.Height = DisplayViewRect_00886FA0.Height;
    if (ToolTipManager_Instance)
    {
        ToolTip tip;
        tip.field_18 = false;
        tip.GadgetID = 500;
        tip.Text = 0;
        tip.Bounds.X = DisplayViewRect_00886FA0.Origin.X;
        tip.Bounds.Y = DisplayViewRect_00886FA0.Origin.Y;
        tip.Bounds.Width = DisplayViewRect_00886FA0.Width;
        tip.Bounds.Height = DisplayViewRect_00886FA0.Height;
        ToolTipManager_Instance->Remove(500);
        ToolTipManager_Instance->Add(tip);
    }
    DisplayMessageList_00A8BC60.FUN_005D3A60(DisplayViewRect_00886FA0.Origin.X + 3, DisplayViewRect_00886FA0.Origin.Y, 6, 0x62, 0xE,
                                             -1, -1, 0, 0x14, 0x62, DisplayViewRect_00886FA0.Width - 6);
    DisplayMessageList_00A8BC60.FUN_005D4AD0(DisplayViewRect_00886FA0.Width);
    FUN_004068E0("Set_View_Dimensions(exit)\n");
}

// FUNCTION: GAMEMD 0x4A88C0
void DisplayClass::vf_07()
{
    MapClass::vf_07();
    Pending = 0;
    unknown_11A8 = 0;
    unknown_11AC = -1;
    CurrentFoundation = 0;
    unknown_11B8 = -1;
    RepairMode = false;
    unknown_11CF = false;
    unknown_11D0 = false;
    SellMode = false;
    PowerMode = false;
    for (int i = 0; i < 5; i++)
    {
        DisplayLayerVec* layer = &DisplayLayers_008A0360[i];
        layer->vf_03();
    }
}

// FUNCTION: GAMEMD 0x4A8930
void DisplayClass::vf_08()
{
    GScreenClass::vf_08();
    if (!DisplayFlag_00A8ED6B)
    {
        DisplayButton_008A06F8.FUN_005565F0();
        AddButton(&DisplayButton_008A06F8);
    }
}

// FUNCTION: GAMEMD 0x4A9700
void DisplayClass::vf_10(int* key, Point2D* where)
{
    GScreenClass::vf_10(key, where);
}

// FUNCTION: GAMEMD 0x4A9840
bool DisplayClass::vf_41(int a, int* b, bool c)
{
    int value = *b;
    if (value == 0)
    {
        if (!c)
            return false;
    }
    else if (!c)
    {
        return DisplayTactical_00887324->FUN_006DA230(a) != -1;
    }
    DisplayTactical_00887324->FUN_006D8530(a, value);
    return true;
}

// FUNCTION: GAMEMD 0x4AC310
void DisplayClass::vf_45(const Point2D* where)
{
    if (!RepairMode && !PowerMode && !SellMode && unknown_11B8 == -1 && !unknown_11A8)
    {
        unknown_11D0 = true;
        DragStart = *where;
        DragCurrent = *where;
    }
}

// FUNCTION: GAMEMD 0x4AE6B0
void DisplayClass::vf_34()
{
    if (DisplayWindow_00B73554)
    {
        CloseWindow(DisplayWindow_00B73554);
        DisplayWindow_00B73554 = 0;
    }
}

// FUNCTION: GAMEMD 0x4AE6F0
long DisplayClass::vf_30(IStream* stream)
{
    long result;
    for (int i = 0; i < 5; i++)
    {
        DisplayLayerVec* layer = &DisplayLayers_008A0360[i];
        result = layer->Load(stream);
    }
    return result;
}

// FUNCTION: GAMEMD 0x4AE720
long DisplayClass::vf_31(IStream* stream)
{
    long result;
    for (int i = 0; i < 5; i++)
    {
        DisplayLayerVec* layer = &DisplayLayers_008A0360[i];
        result = layer->Save(stream);
        if (result < 0)
            break;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4AEAD0
void DisplayClass::vf_35()
{
    if (DisplayTactical_00887324)
        DisplayTactical_00887324->FUN_006DA160();
    unknown_11CF = false;
    unknown_11D0 = false;
    DisplayFlag_00A8ED9D = true;
    vf_18(0, false);
}

// FUNCTION: GAMEMD 0x4AC380
void DisplayClass::vf_47(const Point2D* where)
{
    if (unknown_11CF && !WaypointMode && !BeaconMode)
    {
        int w = DisplayViewRect_00886FA0.Width;
        int h = DisplayViewRect_00886FA0.Height;
        Point2D pt = DisplayViewRect_00886FA0.Origin;
        int x = where->X;
        int y = where->Y;
        if (x < 0)
            x = 0;
        if (x >= w)
            x = w - 1;
        if (y < 0)
            y = 0;
        if (y >= h)
            y = h - 1;
        pt.X = x;
        pt.Y = y;
        if (x != DragCurrent.X || y != DragCurrent.Y)
        {
            DisplayTactical_00887324->unknown_D7D = true;
            DisplayTactical_00887324->FUN_006D9FC0(&pt);
        }
    }
    else if (unknown_11D0)
    {
        Point2D* start = &DragStart;
        int dx = where->X - start->X;
        int dy = where->Y - start->Y;
        if ((int)FUN_004CAC40((double)dx * dx + (double)dy * dy) > 4)
        {
            unknown_11CF = true;
            unknown_11D0 = false;
            if (!WaypointMode && !BeaconMode)
            {
                DisplayTactical_00887324->unknown_D7D = true;
                DisplayTactical_00887324->FUN_006D9F80(start);
                Map_0087F7E8.vf_19(0, 0);
            }
        }
    }
}
