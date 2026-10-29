// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Display.CPP. The name is the source-file string at 0x8201a8
//   in retail gamemd.exe v1.001, passed by the assert at 0x4ae5e7 inside this object's
//   code range (0x4a8440-0x4af32f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
// DisplayClass entries (layout and evidence: display_class.h).
//
// DisplayClass command entries (view and evidence: display_command.h).
//
// DisplayClass cell reveal family, vtable slots 36..39 (layout and evidence: display_reveal.h).
//
// DisplayClass scenario/help-text entries (layout and evidence: display_scenario.h).

#include "../../_layout/object_class.h"
#include "../../core/mathtbl_init_shapes.h"
#include "../../_layout/house_class.h"
#include "../../_layout/cell.h"
#include "../../core/leftover_trivial_leaf_sweep.h"

#include "../../map/map_class_next_object_methods.h"

#include "../../map/map_class_waypoint_mode_methods.h"

#include "../../map/trivial_tu067_methods.h"

#include "../display_class_active_foundation_methods.h"

#include "display_class.h"

#include "display_command.h"

// Recolours the palette entries the highlight cycles through: eight consecutive entries filled from the colour ring,
// starting `offset` entries into it.
inline void DisplayCmdFillPalette(int offset)
{
    unsigned short* dest = static_cast<unsigned short*>(DAT_0087F6C8->ColorTable) + 1;
    for (int i = 0; i < 8; i++)
    {
        ColorStruct c = DisplayCmdRing_00885180[(i + offset) % 256];
        *dest++ = DisplayCmdPack(c.R, c.G, c.B);
    }
}

inline int DisplayCmdHouseRingOffset(int index)
{
    if (index == -1)
        return 0;
    return (index % 12) << 3;
}

// The sum the placement code hands to its cell queries (offset + clicked cell, a by-value operator+ inlined).
inline DisplayCmdObject* DisplayCmdAsBuilding(DisplayCmdObject* p)
{
    if (p == 0)
        return 0;
    return p->WhatAmI() == 6 ? p : 0;
}

inline CellStruct CellStructSum(const CellStruct& a, const CellStruct& b)
{
    CellStruct r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}

#include "display_reveal.h"

#include "display_scenario.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E6018
extern const double DAT_007E6018;
// GLOBAL: GAMEMD 0x8A0400
extern double DAT_008A0400;

// SYNTHETIC: GAMEMD 0x004A8470
// GLOBAL: GAMEMD 0x008A0738
double DAT_008A0738 = DAT_008A0400 / DAT_007E6018;

// SYNTHETIC: GAMEMD 0x004A8490
// GLOBAL: GAMEMD 0x008A0628
double DAT_008A0628 = DAT_007E1718 / DAT_008A0738;

// SYNTHETIC: GAMEMD 0x004A8610
// GLOBAL: GAMEMD 0x008A0720
MathTblCoord DAT_008A0720;

struct DisplayLayerStatics {
    // GLOBAL: GAMEMD 0x008A0360 -- the five draw layers (guard byte 0x008A03E1 bit 0).
    static LayerClass Layers[5];
};
struct DisplayButtonStatics {
    // GLOBAL: GAMEMD 0x008A06F8 -- the tactical button (guard byte 0x008A03E0 bit 0).
    static DisplayTacticalGadget_008A06F8 Button;
};
// SYNTHETIC: GAMEMD 0x004A8630 -- initialiser of Layers
// SYNTHETIC: GAMEMD 0x004A8680 -- guarded exit stub of Layers
LayerClass DisplayLayerStatics::Layers[5];
// SYNTHETIC: GAMEMD 0x004A86E0 -- initialiser of Button
// SYNTHETIC: GAMEMD 0x004A8710 -- guarded exit stub of Button
// SYNTHETIC: GAMEMD 0x004AEBB0 -- implicit scalar deleting destructor of the button's class (slot 0)
DisplayTacticalGadget_008A06F8 DisplayButtonStatics::Button;

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
        LayerClass* layer = &DisplayLayerStatics::Layers[i];
        layer->Clear();
    }
}

// FUNCTION: GAMEMD 0x4A8930
void DisplayClass::vf_08()
{
    GScreenClass::vf_08();
    if (!DisplayFlag_00A8ED6B)
    {
        DisplayButtonStatics::Button.LinkClass::Zap();
        AddButton((DisplayGadget*)&DisplayButtonStatics::Button);
    }
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

// FUNCTION: GAMEMD 0x4A8BF0
//
// Put a building footprint under the cursor. Any footprint already shown is
// erased at its current place, the offset is reset, and a new foundation is
// copied into the display's own static buffer, its size queried and halved
// to centre it, and the new footprint drawn.
//
// PARTIAL (49.4%, 43/87). The erase call with its by-value cell temporary,
// the offset reset from the global, the trailing null arm, the
// function-local static with its guard byte, atexit registration and
// `REP MOVSD` copy, the size query and the final draw all match. The
// residual is the halving: retail keeps the size pair in a frame slot,
// decrements both halves in place (`DEC word ptr [ESP+0x10]` twice) and
// then reloads the whole pair as a dword and negates it before sign
// extending the low half, where cl 8804 keeps the pair in registers and
// negates after sign extension; that also costs the second four-byte frame
// slot (`PUSH ECX` instead of `SUB ESP,8`), which shifts every later
// displacement. Tried: the halved cell as a by-value temporary and as a
// named local written member-wise, the null arm as an early return and as a
// trailing else, and the size query's result read through the returned
// pointer versus the out buffer.
void Display_004A8BF0::SetActiveFoundation(Foundation_004A8BF0* foundation)
{
    if (Active != 0) {
        RedrawFoundation(MakeCell_004A8BF0(Offset.X + unknown_1174.X,
                                           Offset.Y + unknown_1174.Y), 0);
    }

    Offset = DAT_008A03F8;
    if (foundation != 0) {
        static Foundation_004A8BF0 copy;
        copy = *foundation;
        Active = &copy;

        Cell_004A8BF0 size;
        Cell_004A8BF0 span = *GetFoundationSize(&size, &copy);
        span.X--;
        span.Y--;

        Cell_004A8BF0 half;
        half.X = (short)(-span.X / 2);
        half.Y = (short)(-span.Y / 2);
        Offset = half;

        RedrawFoundation(MakeCell_004A8BF0(unknown_1174.X + Offset.X,
                                           unknown_1174.Y + Offset.Y), 1);
    } else {
        Active = 0;
    }
}

// FUNCTION: GAMEMD 0x4A8D40
// Empty function.
void __cdecl FUN_004A8D40()
{
}

// FUNCTION: GAMEMD 0x4A8EA0
// Empty function.
void __cdecl FUN_004A8EA0()
{
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

// FUNCTION: GAMEMD 0x4A9890
bool DisplayClass::vf_36(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool wasClear = !(c->Flags140 & 2);
    bool changed = !((c->Flags140 & 2) && (c->Flags12C & 8));
    bool first = changed;
    c->Flags140 = (c->Flags140 & ~0x40) | 2;
    c->Flags12C |= 8;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;

    v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;

    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DAT_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags12C & 0x10))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 0);
            if (r == -1)
            {
                if (!(nc->Flags12C & 8))
                    vf_36(&n, house);
                else
                {
                    nc->Flags12C |= 0x10;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DAT_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 0);
                        if (b != mc->Layer0Value)
                        {
                            mc->Layer0Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags12C & 8))
                vf_36(&n, house);
            else if (r >= 0 && r != nc->Layer0Value)
            {
                nc->Layer0Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }

        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags140 & 1))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 1);
            if (r == -1)
            {
                if (!(nc->Flags140 & 2))
                    vf_36(&n, house);
                else
                {
                    nc->Flags140 |= 1;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DAT_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 1);
                        if (b != mc->Layer1Value)
                        {
                            mc->Layer1Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags140 & 2))
                vf_36(&n, house);
            else if (r >= 0 && r != nc->Layer1Value)
            {
                nc->Layer1Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (changed)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    if ((c->Flags140 & 2) && wasClear && (DAT_00A8B230->unknown_0000 & 0x1000))
        c->CleanFog_00486BF0();
    return changed;
}

// FUNCTION: GAMEMD 0x4A9CA0
bool DisplayClass::vf_37(CellStruct* cell, DisplayHouse* house, bool increase)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool wasClear = !(c->Flags140 & 2);
    bool changed = !((c->Flags140 & 2) && (c->Flags12C & 8));
    bool first = changed;
    c->Flags140 = (c->Flags140 & ~0x40) | 2;
    if (increase)
        c->IncreaseShroudCounter_00487690();
    else
        c->ReduceShroudCounter_00487630();

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;

    v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;

    if (changed)
    {
        DisplayProjector_00887324->FUN_006DA7D0(c);
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    }
    if ((c->Flags140 & 2) && wasClear && (DAT_00A8B230->unknown_0000 & 0x1000))
        c->CleanFog_00486BF0();
    return changed;
}

// FUNCTION: GAMEMD 0x4A9DD0
// CAPPED at 44.6% (176 vs 177 instructions; multiset delta: retail has 1 `mov` where cl has `xor`+`jmp`).
// Retail keeps the cell pointer in EBX and the outer loop counter in memory ([esp+0x18]), with the first flag
// copy stored three times as bytes (one of them in the dead stack slot of the first argument); cl keeps the
// counter in EBX and the cell pointer in EDI, so every register after the prologue is named differently.
// Variants tried: single flag variable; three separately computed flags; chained three-way assignment in each
// declaration order (the one kept: three byte stores, no register copy); counter declared at function scope;
// extra uses of the cell pointer; flag loaded into a local first.
bool DisplayClass::vf_38(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool ret, fog, changed;
    ret = fog = changed = !(c->Flags140 & 2);
    c->Flags140 = (c->Flags140 & ~0x40) | 2;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;
    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DAT_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags140 & 1))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 1);
            if (r == -1)
            {
                if (!(nc->Flags140 & 2))
                    vf_38(&n, house);
                else
                {
                    nc->Flags140 |= 1;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = n + DAT_0089F688[j & 7];
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 1);
                        if (b != mc->Layer1Value)
                        {
                            mc->Layer1Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags140 & 2))
                vf_38(&n, house);
            else if (r >= 0 && r != nc->Layer1Value)
            {
                nc->Layer1Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (ret)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, changed);
    if ((c->Flags140 & 2) && fog && (DAT_00A8B230->unknown_0000 & 0x1000))
        c->CleanFog_00486BF0();
    return ret;
}

// FUNCTION: GAMEMD 0x4AA050
bool DisplayClass::vf_39(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool changed = !(c->Flags12C & 8);
    bool first = changed;
    c->Flags12C |= 8;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;
    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DAT_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags12C & 0x10))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 0);
            if (r == -1)
            {
                if (!(nc->Flags12C & 8))
                    vf_39(&n, house);
                else
                {
                    nc->Flags12C |= 0x10;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DAT_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 0);
                        if (b != mc->Layer0Value)
                        {
                            mc->Layer0Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags12C & 8))
                vf_39(&n, house);
            else if (r >= 0 && r != nc->Layer0Value)
            {
                nc->Layer0Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (changed)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    return changed;
}

// FUNCTION: GAMEMD 0x4AA2B0  MapClass::NextObject
//
// Tab-cycling: walk the three ordered layers and return the first selectable
// techno after `current`, wrapping round to the first selectable one found
// when `current` was last (or null). The techno view of the object is formed
// branchlessly from the flag bit before the first virtual, because it has to
// survive that call.
Obj_004AA2B0* Map_004AA2B0::NextObject(Obj_004AA2B0* current)
{
    Obj_004AA2B0* first = 0;
    bool found = false;
    if (current == 0)
        found = true;

    for (int n = 0; n < 3; ++n) {
        for (int i = 0; i < DAT_008A0360[DAT_00820030[n]].Count; ++i) {
            Obj_004AA2B0* obj = DAT_008A0360[DAT_00820030[n]].Items[i];
            if (obj != 0) {
                Obj_004AA2B0* techno = (obj->AbstractFlags & 1) ? obj : 0;
                if ((obj->*obj->Vptr->At_64)() && techno != 0
                    && (techno->*techno->Vptr->At_13C)()) {
                    if (first == 0)
                        first = obj;
                    if (found)
                        return obj;
                    if (current == obj)
                        found = true;
                }
            }
        }
    }
    return first;
}

// FUNCTION: GAMEMD 0x4AAD20
void __stdcall FUN_004AAD20(int)
{
}

// FUNCTION: GAMEMD 0x4AAD30
void DisplayClass::vf_49(int)
{
    if (DisplayCmdIsFlagged(Pending))
    {
        Pending = 0;
        unknown_11A8 = 0;
        unknown_11AC = -1;
        SetActiveFoundation_004A8BF0(0);
    }
    else if (RepairMode)
        SetRepairMode_004AC8C0(0);
    else if (SellMode)
        SetSellMode_004AC660(0);
    else if (PowerMode)
        SetPowerMode_004AC820(0);
    else if (unknown_11B8 != -1)
        unknown_11B8 = -1;
    else if (WaypointMode)
        SetWaypointMode_004AC700(0, 0);
    else if (BeaconMode)
        SetBeaconMode_004AC960(0);
    else
        UnselectAll_0048DC90();
    vf_18(0, DisplayCmdFlag_00884D44);
}

// FUNCTION: GAMEMD 0x4AAE90
void DisplayClass::vf_46(CellStruct* cell, int a2, DisplayCmdAbstract* target, int a4, bool a5)
{
    DisplayCmdAbstract* object = 0;
    unknown_11D0 = false;
    if (target)
    {
        object = target;
        DisplayCmdTechno* techno = target->FUN_0040DD70();
        if (techno)
        {
            if (techno->WhatAmI() != 6 || !techno->Type->unknown_1701)
            {
                if (!DisplayCmdFlag_00A8ED6B)
                    techno->unknown_431 = true;
            }
        }
    }
    else if (cell->X != DisplayCmdNoCell_008A03F8.X || cell->Y != DisplayCmdNoCell_008A03F8.Y)
    {
        object = DisplayCmdMap_0087F7E8.GetCellAt_005657A0(cell);
    }

    if (WaypointMode && WaypointCoord && !DisplayCmdPlayer_00A83D4C->GetPlanningWaypointAt_005023B0(cell)
        && DisplayCmdMap_0087F7E8.IsWithinUsableArea_00578460(cell, 1))
    {
        DisplayCmdVec3* where = WaypointCoord;
        where->X = (cell->X << 8) + 0x80;
        where->Y = (cell->Y << 8) + 0x80;
        where->Z = 0;
        DisplayCmdCellObj* cellObj = DisplayCmdMap_0087F7E8.GetCellAt_005657A0(cell);
        WaypointCoord->Z = ((cellObj->Flags140 & 0x100) ? DisplayCmdZBias_008A0730 : 0)
                         + DisplayCmdMap_0087F7E8.GetZPos_00578080(WaypointCoord);
    }

    int action;
    if (DisplayCmdPlayer_00A83D4C->GetPlanningWaypointAt_005023B0(cell))
    {
        switch (a4)
        {
        case 1:
        case 2:
            action = 0x2D;
            break;
        case 3:
        case 9:
        case 11:
            action = 0x32;
            break;
        case 5:
        case 6:
            action = 0x31;
            break;
        default:
            action = a4;
            break;
        }
    }
    else
        action = a4;

    if (!SavedColor.R && !SavedColor.G && !SavedColor.B)
    {
        unsigned short pixel = static_cast<unsigned short*>(DAT_0087F6C8->ColorTable)[1];
        ColorStruct c;
        c.R = (pixel >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
        c.G = (pixel >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
        c.B = (pixel >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
        SavedColor = c;
    }

    switch (action)
    {
    case 0x2C:
    case 0x30:
    case 0x31:
        DisplayCmdFillPalette(DisplayCmdHouseRingOffset(DisplayCmdPlayer_00A83D4C->unknown_20C));
        break;
    case 0x2A:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x32:
    case 0x33:
    {
        int colourIndex = -1;
        ColorStruct colour;
        DisplayCmdPlayer_00A83D4C->GetPlanningWaypointProperties_00502460(
            DisplayCmdPlayer_00A83D4C->GetPlanningWaypointAt_005023B0(cell), &colourIndex, &colour);
        if (!WaypointMode)
            DisplayCmdPlayer_00A83D4C->unknown_20C = colourIndex;
        DisplayCmdFillPalette(DisplayCmdHouseRingOffset(colourIndex));
        break;
    }
    default:
        static_cast<unsigned short*>(DAT_0087F6C8->ColorTable)[1] = DisplayCmdPack(SavedColor.R, SavedColor.G, SavedColor.B);
        DisplayCmdFillPalette(0);
        if (!WaypointMode)
            DisplayCmdPlayer_00A83D4C->unknown_20C = -1;
        break;
    }

    int cursor = FUN_0070F0B0(action, cell, target);
    // BEGIN CURSOR
    if (a2)
    {
        switch (cursor)
        {
        case 1: case 5:
        vf_18(0x12, a5);
        return;
        case 2:
        {
            DisplayCmdObject* first;
            if (DisplayCmdSelCount_00A8ECC8 && DisplayCmdIsFlagged(first = DisplayCmdSelItems_00A8ECBC[0])
                && first->vf_33()->unknown_C8D)
            {
                vf_18(0x12, a5);
                return;
            }
            vf_18(0x13, a5);
            return;
        }
        case 0x0A: case 0x0F: case 0x20:
        vf_18(0x23, a5);
        return;
        case 0x0C: case 0x0D: case 0x0E:
        vf_18(0x20, a5);
        return;
        case 0x11: case 0x1B: case 0x21: case 0x22: case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2E: case 0x2F: case 0x31: case 0x33:
        vf_18(0x3C, a5);
        return;
        case 0x14:
        vf_18(0x35, a5);
        return;
        case 0x1A:
        vf_18(FUN_00731CC0(), a5);
        return;
        case 0x1E:
        vf_18(0x1C, a5);
        return;
        case 0x1F: case 0x24:
        vf_18(0x1A, a5);
        return;
        case 0x25:
        vf_18(0x39, a5);
        return;
        case 0x26:
        vf_18(0x32, a5);
        return;
        case 0x27: case 0x28:
        vf_18(0x3A, a5);
        return;
        case 0x29: case 0x41:
        vf_18(0x2F, a5);
        return;
        case 0x32:
        vf_18(0x3C, a5);
        // fall through
        case 0x3C:
        vf_18(0x4E, a5);
        return;
        case 0x39:
        vf_18(0x3B, a5);
        return;
        case 0x3D:
        vf_18(0x11, a5);
        return;
        case 0x3E: case 0x3F:
        vf_18(FUN_00731CB0(), a5);
        return;
        case 0x42:
        vf_18(0x53, a5);
        return;
        case 0x43:
        vf_18(0x55, a5);
        return;
        case 0x44:
        vf_18(0x51, a5);
        return;
        case 0x45:
        vf_18(0x4F, a5);
        return;
        case 0x46:
        vf_18(0x50, a5);
        return;
        case 0x48:
        vf_18(0x54, a5);
        return;
        case 0:
        default:
        vf_18(0, a5);
        return;
        }
    }
    else
    {
        switch (cursor)
        {
        case 1:
        vf_18(0x12, a5);
        return;
        case 2: case 0x36:
        vf_18(0x13, a5);
        return;
        case 3: case 9: case 0x0B: case 0x23:
        vf_18(0x19, a5);
        return;
        case 4: case 0x34:
        vf_18(0x1B, a5);
        return;
        case 5:
        {
            if (object && DisplayCmdSelCount_00A8ECC8 == 1 && DisplayCmdIsFlagged(DisplayCmdSelItems_00A8ECBC[0])
                && DisplayCmdSelItems_00A8ECBC[0]->vf_235(object))
            {
                vf_18(0x14, a5);
                return;
            }
        }
        // fall through to the next arm
        case 6:
        vf_18(0x15, a5);
        return;
        case 7: case 8: case 0x3D:
        vf_18(0x11, a5);
        return;
        case 0x0A:
        vf_18(0x22, a5);
        return;
        case 0x0C:
        vf_18(0x1E, a5);
        return;
        case 0x0D:
        vf_18(0x1F, a5);
        return;
        case 0x0E:
        vf_18(0x20, a5);
        return;
        case 0x0F: case 0x20:
        vf_18(0x23, a5);
        return;
        case 0x10: case 0x37: case 0x38: case 0x40:
        vf_18(0x34, a5);
        return;
        case 0x11: case 0x1B: case 0x21: case 0x22: case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2E: case 0x2F: case 0x31: case 0x32: case 0x33:
        vf_18(0x3C, a5);
        return;
        case 0x14:
        vf_18(0x35, a5);
        return;
        case 0x1A:
        vf_18(FUN_00731CC0(), a5);
        return;
        case 0x1C:
        return;
        case 0x1D:
        vf_18(0x21, a5);
        return;
        case 0x1E:
        vf_18(0x1C, a5);
        return;
        case 0x1F:
        vf_18(0x1A, a5);
        return;
        case 0x25:
        vf_18(0x39, a5);
        return;
        case 0x26:
        vf_18(0x32, a5);
        return;
        case 0x27: case 0x28:
        vf_18(0x3A, a5);
        return;
        case 0x29: case 0x41:
        vf_18(0x2F, a5);
        return;
        case 0x35:
        vf_18(0x26, a5);
        return;
        case 0x39:
        vf_18(0x3B, a5);
        return;
        case 0x3C:
        vf_18(0x4E, a5);
        return;
        case 0x3E: case 0x3F:
        vf_18(FUN_00731CB0(), a5);
        return;
        case 0x42:
        vf_18(0x53, a5);
        return;
        case 0x43:
        vf_18(0x55, a5);
        return;
        case 0x44:
        vf_18(0x51, a5);
        return;
        case 0x45:
        vf_18(0x4F, a5);
        return;
        case 0x46:
        vf_18(0x50, a5);
        return;
        case 0x47:
        vf_18(0x52, a5);
        return;
        case 0x48:
        vf_18(0x54, a5);
        return;
        default:
        vf_18(0, a5);
        return;
        }
    }
    // END CURSOR
}

// FUNCTION: GAMEMD 0x4AB9B0
// Mouse-up / command dispatch for the current action: confirms a pending placement or turns the clicked object and
// action into a queued event.
void DisplayClass::vf_48(int, CellStruct* cell, DisplayCmdObject* target, int action, bool a5)
{
    if (target && DisplayCmdFlag_00A8ED5C && DisplayCmdFlag_00A8E9A0 && !DisplayCmdFlag_00A8ED6B)
    {
        if (target->vf_26(0, 0) == 5)
            target = 0;
    }

    if (Pending)
    {
        if (unknown_11A8->WhatAmI() == 7)
        {
            CellStruct at = CellStructSum(*cell, FoundationOffset);
            CanPlace = FUN_004A8EB0(unknown_11A8, unknown_11AC, CurrentFoundation, at);
        }
        if (unknown_11A8->WhatAmI() == 7 && target && target->WhatAmI() == 6
            && target->FUN_00452670(unknown_11A8, DisplayCmdPlayer_00A83D4C))
            CanPlace = true;

        if (CanPlace && unknown_1181)
        {
            DisplayCmdTechnoTypeView* techType = (DisplayCmdTechnoTypeView*)FUN_007CAAE4(
                unknown_11A8, 0, TypeDesc_ObjectTypeClass_00817F78, TypeDesc_TechnoTypeClass_00817F98, 0);
            bool flag = techType && techType->unknown_CCE;
            CellStruct at = CellStructSum(*cell, FoundationOffset);
            DisplayCmdObject* pending = Pending;
            DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0xB, pending->WhatAmI(),
                                                 unknown_11A8->vf_16(flag, &at)));
            FUN_00734270(DisplayCmdAsBuilding(Pending));
            if (!DisplayCmdFlag_00A8ED6B)
            {
                SavedType = unknown_11A8;
                SavedPending = Pending;
                SavedCell = *cell;
                SavedOffset = FoundationOffset;
                SavedFoundation = CurrentFoundation;
                SavedField = unknown_11AC;
                if (SavedType)
                    DisplayCmdMap_0087F7E8.FUN_004A8D50(SavedType->vf_36(1));
                DisplayCmdMap_0087F7E8.SetActiveFoundation_004A8BF0(0);
                DisplayCmdValue_0088098C = 0;
                DisplayCmdValue_00880990 = 0;
                DisplayCmdValue_00880994 = -1;
            }
            FUN_00731CF0();
            return;
        }
        FUN_00752700(DisplayCmdCue_0082012C, -1, -1);
        FUN_00731CF0();
        return;
    }

    int proceed = 0;
    if (unknown_11CF)
    {
        DAT_00887324->unknown_D7D = true;
        if (!DisplayCmdKeyboard_0087F770->FUN_0054F5C0(0x10))
        {
            if (DAT_00887324->FUN_006DA080())
                UnselectAll_0048DC90();
            else
                proceed = 1;
        }
        DAT_00887324->FUN_006D9FF0(&FUN_004AC2B0);
        FUN_0070D150();
        unknown_11CF = false;
        vf_18(0, a5);
        unknown_11D0 = false;
        DisplayCmdFlag_00A8ED9D = true;
        if (!proceed)
        {
            FUN_00731CF0();
            return;
        }
    }

    if (action == 8)
    {
        if (target && DisplayCmdSelCount_00A8ECC8
            && DisplayCmdSelItems_00A8ECBC[0]->GetOwner()->FUN_0050B6F0())
        {
            if (target->unknown_83)
            {
                if (FUN_00732D00())
                {
                    DisplayCmdSub* sub = &target->vf_34()->Sub;
                    sub->FUN_00732600();
                }
                else
                    target->vf_84();
            }
            else
            {
                if (FUN_00732D00())
                {
                    DisplayCmdSub* sub = &target->vf_34()->Sub;
                    sub->FUN_007327D0();
                }
                else
                    target->vf_83();
            }
            goto process;
        }
        action = 7;
        goto actionSeven;
    }
    if (action == 7)
    {
    actionSeven:
        if (target)
            goto selectTarget;
        goto done;
    }
    if (action == 0)
    {
        if (!target)
            goto done;
        if (!target->vf_78())
            goto done;
        if (target->unknown_83)
            goto done;
    selectTarget:
        if (target->WhatAmI() != 6 || target->Owner->FUN_0050B6F0() || target->unknown_6ED != 0xF
            || target->vf_202())
        {
            UnselectAll_0048DC90();
            if (FUN_00732D00())
            {
                DisplayCmdSub* sub = &target->vf_34()->Sub;
                sub->FUN_007327D0();
            }
            else
                target->vf_83();
            vf_18(0, a5);
            FUN_0070D150();
        }
    }

    if (action == 0x3D)
    {
        DisplayCmdCellObj* cellObj = DisplayCmdMap_0087F7E8.GetCellAt_005657A0(cell);
        DisplayCmdVec3 where;
        where.X = (cell->X << 8) + 0x80;
        where.Y = (cell->Y << 8) + 0x80;
        where.Z = cellObj->unknown_11B * DisplayCmdScale_008A0740;
        DisplayCmdMarker_0089C3B0.FUN_00430F70(where);
        goto done;
    }
    if (action == 0)
        goto done;
    if (action == 7)
        goto done;
    if (!(action == 8 || action == 0xA || action == 0xC || action == 0xD || action == 0xE || action == 0xF
          || action == 0x21 || action == 0x22 || action == 0x14 || action == 0x25 || action == 0x45
          || action == 0x46 || action == 0x26 || action == 0x27 || action == 0x28 || action == 0x29
          || action == 0x41 || action == 0x42 || action == 0x43 || action == 0x44 || action == 0x48
          || action == 0x3A || action == 0x3C))
    {
        bool first = FUN_00639040();
        bool second = FUN_00639130();
        if (!first || !second)
            goto done;
    }

process:
    FUN_004AE750(target, *cell, action);
    FUN_0070D150();
    if (action == 0x21)
    {
        if (target->WhatAmI() == 6)
        {
            if (target->unknown_660)
                DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 2, DisplayCmdTarget(target)));
            else
                DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 1, DisplayCmdTarget(target)));
        }
    }
    else if (action == 0x3C)
    {
        if (!DisplayCmdValue_00A8B538)
        {
            DisplayCmdCellObj* cellObj = DisplayCmdMap_0087F7E8.GetCellAt_005657A0(cell);
            DisplayCmdVec3 where;
            where.X = (cell->X << 8) + 0x80;
            where.Y = (cell->Y << 8) + 0x80;
            where.Z = cellObj->unknown_11B * DisplayCmdScale_008A0740;
            DisplayCmdMarker_0089C3B0.FUN_00430BA0(DisplayCmdPlayer_00A83D4C->unknown_30, where, -1);
        }
        DisplayCmdMap_0087F7E8.SetBeaconMode_004AC960(0);
        vf_18(0, a5);
    }
    else if (action == 0xA)
    {
        if (target->WhatAmI() == 6)
            DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0x15, DisplayCmdTarget(target)));
    }
    else if (action == 0xD)
    {
        if (target)
        {
            int kind = target->WhatAmI();
            if (kind > 0 && kind <= 2)
                DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0x16, DisplayCmdTarget(target)));
        }
    }
    else if (action == 0xC)
    {
        if (target)
            DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0x16, DisplayCmdTarget(target)));
        else
            DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0x17, *cell));
    }

    {
        DisplayCmdActionInfo* info = FUN_006CEEB0(action);
        if (info)
            DisplayCmdQueueEvent(DisplayCmdEvent(DisplayCmdPlayer_00A83D4C->unknown_30, 0x12, info->unknown_98, *cell));
    }

done:
    unknown_11D0 = false;
    FUN_00731CF0();
}

// GLOBAL: GAMEMD 0x822CF2
extern bool DAT_00822CF2;

// FUNCTION: GAMEMD 0x4AC2B0
// ECX-only callable; original member/free spelling remains unproved.
void __fastcall FUN_004AC2B0(ObjectClass* object)
{
    HouseClass* owner = object->vf_15();
    if (owner && owner->IsControlledByCurrentPlayer() &&
        object->vf_78() && object->vf_79() && !object->InLimbo &&
        object->vf_83())
        DAT_00822CF2 = false;
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

// FUNCTION: GAMEMD 0x4AC380
// PARTIAL (95.1%): only the frame size differs (retail SUB ESP,0x10, ours 8);
// the drag delta as a Point2D local closed the store order. Tried: copying the
// whole view rect (79.4%), `pt` at function scope (95.1%).
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
        Point2D d;
        d.X = where->X - start->X;
        d.Y = where->Y - start->Y;
        if ((int)FUN_004CAC40((double)d.X * d.X + (double)d.Y * d.Y) > 4)
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

// FUNCTION: GAMEMD 0x4AC700  MapClass::SetWaypointMode (__thiscall, ret 0x8)
//
// The waypoint cursor-mode setter, same tri-state as the sell/repair/power
// ones (-1 toggles, 0 clears, 1 sets, anything else leaves it alone). On a
// real change the other four mode flags are cleared and the local player is
// asked for a waypoint slot. Entering the mode with no slot available (and,
// unless `somebool`, no slot already remembered on the player) leaves the
// mode off and drops the parked record; otherwise the mode is entered and
// the slot is remembered unless `somebool`. Leaving the mode hands the parked
// 12-byte record back through the +0x11BC receiver and shows the mouse.
void Map_004AC700::SetWaypointMode(int mode, bool somebool)
{
    bool want = WaypointMode;

    switch (mode) {
    case -1:
        want = !want;
        break;
    case 0:
        want = false;
        break;
    case 1:
        want = (bool)mode;
        break;
    }

    if (want != WaypointMode && unknown_11A8 == 0)
    {
        RepairMode = false;
        SellMode = false;
        TogglePowerMode = false;
        PlaceBeaconMode = false;

        int slot = CurrentPlayer_004AC700->FUN_005090A0();

        if (want)
        {
            if (slot == -1 && (!somebool || CurrentPlayer_004AC700->At_20C == -1)) {
                WaypointMode = false;
                Slot_50();
                At_11BC = 0;
                return;
            }
            WaypointMode = true;
            if (!somebool) {
                CurrentPlayer_004AC700->At_20C = slot;
            }
            ModeEntered_004AC700();
            return;
        }

        WaypointMode = false;
        Slot_50();

        Coord_004AC700* out = At_11BC;
        if (out) {
            *out = At_11C0;
            At_11BC = 0;
            (DAT_00887640->*DAT_00887640->Vtbl->At_10)();
        }
    }
}

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
    Session_00A8B238.FUN_0069AE90(0x3F);
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
    Session_00A8B238.FUN_0069AE90(0x41);
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
                CellTags.AddItem(Cell(cell.X, cell.Y));
            }
        }
    }
    Session_00A8B238.FUN_0069AE90(0x43);
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
    Session_00A8B238.FUN_0069AE90(0x44);
    FUN_0048D080();

    bool flag = DisplayScFlag_00A8ED6B || DisplayScFlag_00A8ED5D;
    FUN_00546DA0(flag, DisplayScScenario_00A8B230->Flag_34BD);
    Session_00A8B238.FUN_0069AE90(0x45);
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
                && !DisplayScMap_0087F7E8.FUN_00565730(object->vf_18())->FUN_004870D0(DAT_00A83D4C->ArrayIndex))
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AE6B0
void DisplayClass::vf_34()
{
    if (DisplayWindow_00B73554)
    {
        CloseWindow(DisplayWindow_00B73554);
        DisplayWindow_00B73554 = 0;
    }
}

struct HWND__;
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam);
// FUNCTION: GAMEMD 0x004AE6D0
long __stdcall FUN_004AE6D0(HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam)
{
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AE6F0
long DisplayClass::vf_30(IStream* stream)
{
    long result;
    for (int i = 0; i < 5; i++)
    {
        LayerClass* layer = &DisplayLayerStatics::Layers[i];
        result = layer->Load(stream);
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AE720
long DisplayClass::vf_31(IStream* stream)
{
    long result;
    for (int i = 0; i < 5; i++)
    {
        LayerClass* layer = &DisplayLayerStatics::Layers[i];
        result = layer->Save(stream);
        if (result < 0)
            break;
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AEA20
// ECX is unused; one stack index and RET4. Original member/free scope unproved.
void __stdcall FUN_004AEA20(int index)
{
    DisplayCmdFillPalette(DisplayCmdHouseRingOffset(index));
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AEB30
// Stores several members; pops its stack arguments.
void Obj_004AEB30::FUN_004AEB30(int a1)
{
    unknown_11A0 = a1;
    unknown_119C = a1 != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AEBA0
// Returns zero. Vtable slot 17 of GadgetClass (RTTI) and 5 derived vtable(s).
int Obj_004AEBA0::FUN_004AEBA0() const
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AEBD0
// Empty function that pops its stack arguments. Vtable slot 16 of GScreenClass (RTTI) and 2 derived vtable(s).
void GScreenClass::vf_16(bool forced)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4AEBE0
// Returns a constant boolean. Vtable slot 26 of MapClass (RTTI) and 5 derived vtable(s).
bool MapClass::vf_26()
{
    return false;
}
