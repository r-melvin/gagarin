// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// DisplayClass scenario/help-text entries (layout and evidence: display_scenario.h).

#include "display_scenario.h"

// FUNCTION: GAMEMD 0x4ACE70
// Reads the [Map] part of a scenario: sizes, ground fill, theater, waypoints, tagged cells and the five packed
// sections (through an off-screen surface used as the scratch buffer). Slot 32, thiscall, one INI argument.
void DisplayClass::vf_32(DisplayScIni* ini)
{
    ini->FUN_00526B00();

    RectangleStruct fallbackSize;
    fallbackSize.Width = 50;
    fallbackSize.Height = 50;
    RectangleStruct mapSize;
    mapSize.X = 1;
    mapSize.Y = 1;
    mapSize = ini->FUN_00527CC0("Map", "Size", fallbackSize);
    vf_24();
    vf_28(&mapSize, 1, 0, 1);

    int level = ini->FUN_005276D0("Map", "Level", 0);
    DisplayScGround ground;
    ground.Second = DisplayScGround_00AA10B0;
    ground.Base = 0;
    char fill[32];
    ini->FUN_00528A10("Map", "Fill", "Clear", fill, 32);
    if (FUN_007C8D20(fill, "Water") == 0)
    {
        ground.Base = 3;
        ground.Second = DisplayScGround_00AA0738;
    }
    FUN_00578350();
    for (DisplayScCellObject* cell = FUN_00578290(); cell; cell = FUN_00578290())
    {
        cell->unknown_38 = DisplayScScenario_00A8B230->Random_218.FUN_0065C7E0(0, ground.Base) + ground.Second;
        cell->unknown_11B += (unsigned char)level;
        cell->unknown_11A = 0;
    }

    DisplayScScenario_00A8B230->Theater = ini->FUN_00475870("Map", "Theater", 0);
    vf_06(DisplayScScenario_00A8B230->Theater);
    DisplayScSession_00A8B238.FUN_0069AE90(0x3F);
    FUN_0048D080();
    int savedValue = DisplayScScenario_00A8B230->Value_214;
    FUN_0071DCA0(DisplayScScenario_00A8B230->Theater);
    if (DisplayScScenario_00A8B230->Theater == DisplayScTheater_00822CF8)
        FUN_00547110();
    else
        FUN_00545150(DisplayScScenario_00A8B230->Theater, 1);
    DisplayScScenario_00A8B230->Value_214 = savedValue + 10000;
    FUN_005FE620(DisplayScScenario_00A8B230->Theater);
    FUN_0045E970(DisplayScScenario_00A8B230->Theater);
    FUN_00427940(DisplayScScenario_00A8B230->Theater);
    FUN_006B5490(DisplayScScenario_00A8B230->Theater);
    DisplayScSession_00A8B238.FUN_0069AE90(0x41);
    FUN_0048D080();

    DisplayScScenario_00A8B230->FUN_0068BDC0(ini);
    if (!DisplayScScenario_00A8B230->FUN_0068BD80(DisplayScScenario_00A8B230->Waypoint_20C))
    {
        CellStruct center;
        center.X = center.Y = (short)((MapRect.Width + MapRect.Height) / 2);
        DisplayScScenario_00A8B230->FUN_0068BF50(DisplayScScenario_00A8B230->Waypoint_20C, center);
    }
    CellStruct start;
    CellStruct* found = DisplayScScenario_00A8B230->FUN_0068BCC0(
        &start, DisplayScScenario_00A8B230->Flag_1CB0 ? DisplayScScenario_00A8B230->Waypoint_210
                                                       : DisplayScScenario_00A8B230->Waypoint_20C);
    start = *found;
    DisplayScScenario_00A8B230->Cells_348E[3] = start;
    DisplayScScenario_00A8B230->Cells_348E[2] = DisplayScScenario_00A8B230->Cells_348E[3];
    DisplayScScenario_00A8B230->Cells_348E[1] = DisplayScScenario_00A8B230->Cells_348E[2];
    DisplayScScenario_00A8B230->Cells_348E[0] = DisplayScScenario_00A8B230->Cells_348E[1];
    DisplayScCoord center3;
    center3.X = start.X * 256 + 128;
    center3.Y = start.Y * 256 + 128;
    center3.Z = 0;
    DisplayScTactical_00887324->FUN_006D6070(&center3);

    int tagCount = ini->FUN_00526960("CellTags");
    for (int i = 0; i < tagCount; i++)
    {
        const char* key = ini->FUN_00526CC0("CellTags", i);
        char name[128];
        DisplayScTagType* tag;
        if (ini->FUN_00528A10("CellTags", key, DisplayScEmpty_00889F64, name, 128))
            tag = FUN_006E6310(name);
        else
            tag = 0;
        int packed = FUN_007C9BFD(key);
        CellStruct cell;
        if (DisplayScValue_00A8ED7C >= 4)
        {
            cell.X = (short)(packed % 1000);
            cell.Y = (short)(packed / 1000);
        }
        else
        {
            cell.X = (short)(packed % 128);
            cell.Y = (short)(packed / 128);
        }
        if (tag && FUN_005657A0(&cell)->unknown_3C == 0)
        {
            DisplayScTagInstance* instance = tag->FUN_006E52A0();
            if (instance)
            {
                instance->FUN_006E5560(cell);
                FUN_005657A0(&cell)->ReplaceTag(instance);
                CellTags.AddItem(cell);
            }
        }
    }
    DisplayScSession_00A8B238.FUN_0069AE90(0x43);
    FUN_0048D080();

    DisplayScSurface surface;
    surface.Init(640, 400);
    surface.Vtbl = &DisplayScVT_007E2104;
    surface.LockCount = 0;
    surface.BytesPerPixel = 2;
    surface.Pixels.Construct(0, 0x7D000);
    int size = surface.Height * surface.BytesPerPixel * surface.Width;
    void* pixels = surface.Pixels.Data;
    surface.LockCount++;
    surface.Vtbl = &DisplayScVT_007E2070;
    (surface.*surface.Vtbl->At_70)();
    (surface.*surface.Vtbl->At_74)();

    int got = ini->FUN_00526FB0(DisplayScPackName_007E6028[0], pixels, size);
    if (got > 0)
    {
        surface.LockCount++;
        void* data = surface.Pixels.Data;
        (surface.*surface.Vtbl->At_70)();
        (surface.*surface.Vtbl->At_74)();
        DisplayScBufferStraw straw;
        straw.ChainTo = 0;
        straw.ChainFrom = 0;
        straw.Vtable = &DisplayScVT_007E61F0;
        straw.Buffer.Construct(data, got);
        straw.Index = 0;
        straw.Vtable = &DisplayScVT_007E61E0;
        DisplayScMapPacks_0087F7E8.FUN_0056B5A0(&straw);
        surface.LockCount--;
        straw.Buffer.Clear();
        straw.Destroy();
    }

    pixels = surface.Pixels.Data;
    (surface.*surface.Vtbl->At_70)();
    (surface.*surface.Vtbl->At_74)();
    got = ini->FUN_00526FB0(DisplayScPackName_007E6028[1], pixels, size);
    if (got > 0)
    {
        surface.LockCount++;
        void* data = surface.Pixels.Data;
        (surface.*surface.Vtbl->At_70)();
        (surface.*surface.Vtbl->At_74)();
        DisplayScBufferStraw straw;
        straw.ChainTo = 0;
        straw.ChainFrom = 0;
        straw.Vtable = &DisplayScVT_007E61F0;
        straw.Buffer.Construct(data, got);
        straw.Index = 0;
        straw.Vtable = &DisplayScVT_007E61E0;
        DisplayScMapPacks_0087F7E8.FUN_0056B780(&straw);
        surface.LockCount--;
        straw.Buffer.Clear();
        straw.Destroy();
    }

    pixels = surface.Pixels.Data;
    (surface.*surface.Vtbl->At_70)();
    (surface.*surface.Vtbl->At_74)();
    got = ini->FUN_00526FB0(DisplayScPackName_007E6028[2], pixels, size);
    if (got > 0)
    {
        surface.LockCount++;
        void* data = surface.Pixels.Data;
        (surface.*surface.Vtbl->At_70)();
        (surface.*surface.Vtbl->At_74)();
        DisplayScBufferStraw straw;
        straw.ChainTo = 0;
        straw.ChainFrom = 0;
        straw.Vtable = &DisplayScVT_007E61F0;
        straw.Buffer.Construct(data, got);
        straw.Index = 0;
        straw.Vtable = &DisplayScVT_007E61E0;
        DisplayScMapPacks_0087F7E8.FUN_0056B8A0(&straw);
        surface.LockCount--;
        straw.Buffer.Clear();
        straw.Destroy();
    }

    pixels = surface.Pixels.Data;
    (surface.*surface.Vtbl->At_70)();
    (surface.*surface.Vtbl->At_74)();
    got = ini->FUN_00526FB0(DisplayScPackName_007E6028[3], pixels, size);
    if (got > 0)
    {
        surface.LockCount++;
        void* data = surface.Pixels.Data;
        (surface.*surface.Vtbl->At_70)();
        (surface.*surface.Vtbl->At_74)();
        DisplayScBufferStraw straw;
        straw.ChainTo = 0;
        straw.ChainFrom = 0;
        straw.Vtable = &DisplayScVT_007E61F0;
        straw.Buffer.Construct(data, got);
        straw.Index = 0;
        straw.Vtable = &DisplayScVT_007E61E0;
        DisplayScMapPacks_0087F7E8.FUN_0056B9A0(&straw);
        surface.LockCount--;
        straw.Buffer.Clear();
        straw.Destroy();
    }

    pixels = surface.Pixels.Data;
    (surface.*surface.Vtbl->At_70)();
    (surface.*surface.Vtbl->At_74)();
    got = ini->FUN_00526FB0(DisplayScPackName_007E6028[4], pixels, size);
    if (got > 0)
    {
        surface.LockCount++;
        void* data = surface.Pixels.Data;
        (surface.*surface.Vtbl->At_70)();
        (surface.*surface.Vtbl->At_74)();
        DisplayScBufferStraw straw;
        straw.ChainTo = 0;
        straw.ChainFrom = 0;
        straw.Vtable = &DisplayScVT_007E61F0;
        straw.Buffer.Construct(data, got);
        straw.Index = 0;
        straw.Vtable = &DisplayScVT_007E61E0;
        DisplayScMapPacks_0087F7E8.FUN_0056BAC0(&straw);
        surface.LockCount--;
        straw.Buffer.Clear();
        straw.Destroy();
    }

    surface.LockCount--;
    DisplayScSession_00A8B238.FUN_0069AE90(0x44);
    FUN_0048D080();

    bool flag = DisplayScFlag_00A8ED6B || DisplayScFlag_00A8ED5D;
    FUN_00546DA0(flag, DisplayScScenario_00A8B230->Flag_34BD);
    DisplayScSession_00A8B238.FUN_0069AE90(0x45);
    FUN_0048D080();

    LocalRect = ini->FUN_00527CC0("Map", "LocalSize", MapRect);
    Map_0087F7E8.vf_29(&LocalRect);
    DisplayScMapPacks_0087F7E8.FUN_00588990();
    DisplayScTheater_00822CF8 = DisplayScScenario_00A8B230->Theater;
    surface.Pixels.Clear();
}

// FUNCTION: GAMEMD 0x4AE4F0
const wchar_t* DisplayClass::vf_33(int id)
{
    if (id < 500 || id > 900)
        return 0;
    if (vf_26())
        return 0;

    int originX = DisplayScOrigin_00886FA0.X;
    int originY = DisplayScOrigin_00886FA0.Y;
    Point2D screen;
    {
        Point2D mouseTemp;
        Point2D* mouse = WWMouseClassInstance->vf_13(&mouseTemp);
        screen.X = mouse->X - originX;
        screen.Y = mouse->Y - originY;
    }

    DisplayScObject* object;
    CellStruct cell;
    DisplayScCoord coord;
    bool flagA;
    bool flagB;
    DisplayScMap_0087F7E8.FUN_00692300(screen, &cell, &coord, &object, &flagA, &flagB);

    if (DisplayScFlag_00A8F7D8)
    {
        _swprintf(DisplayScText_008A0630, L"(%d,%d)", coord.X / 256, coord.Y / 256);
        return DisplayScText_008A0630;
    }

    DisplayScCellObject* under = DisplayScMap_0087F7E8.FUN_00565730(coord);
    if (!(under->Flags & 8) && DisplayScDrawing_00B73550)
        return FUN_00734E60("TXT_SHADOW", 0, "D:\\ra2mdpost\\Display.CPP", 0x13B8);

    if (!object)
        return 0;

    DisplayScObject* selected;
    if (object->Flags14 & 1)
    {
        selected = object;
        if (!object->Flag41A)
        {
            if (object->Value220 == 2
                && !DisplayScMap_0087F7E8.FUN_00565730(object->vf_18())->FUN_004870D0(DisplayScHouse_00A83D4C->Index))
                return 0;
            if (object->vf_33()->Flag_0C9A)
                return 0;
        }
    }
    else
        selected = 0;

    if (!object)
        return 0;
    const wchar_t* text = object->vf_36();
    if (selected)
        return text;
    return FUN_005657A0(&cell)->FUN_00484FF0();
}
