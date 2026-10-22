// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// DisplayClass command entries (view and evidence: display_command.h).

#include "display_command.h"

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

// Recolours the palette entries the highlight cycles through: eight consecutive entries filled from the colour ring,
// starting `offset` entries into it.
inline void DisplayCmdFillPalette(int offset)
{
    unsigned short* dest = DisplayCmdPalOwner_0087F6C8->Palette + 1;
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
        unsigned short pixel = DisplayCmdPalOwner_0087F6C8->Palette[1];
        ColorStruct c;
        c.R = (pixel >> DisplayCmdRedShiftLeft_008A0DD0) << DisplayCmdRedShiftRight_008A0DD4;
        c.G = (pixel >> DisplayCmdGreenShiftLeft_008A0DE0) << DisplayCmdGreenShiftRight_008A0DE4;
        c.B = (pixel >> DisplayCmdBlueShiftLeft_008A0DD8) << DisplayCmdBlueShiftRight_008A0DDC;
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
        DisplayCmdPalOwner_0087F6C8->Palette[1] = DisplayCmdPack(SavedColor.R, SavedColor.G, SavedColor.B);
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
        DisplayCmdTactical_00887324->unknown_D7D = true;
        if (!DisplayCmdKeyboard_0087F770->FUN_0054F5C0(0x10))
        {
            if (DisplayCmdTactical_00887324->FUN_006DA080())
                UnselectAll_0048DC90();
            else
                proceed = 1;
        }
        DisplayCmdTactical_00887324->FUN_006D9FF0(&DisplayCmdObject::FUN_004AC2B0);
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
