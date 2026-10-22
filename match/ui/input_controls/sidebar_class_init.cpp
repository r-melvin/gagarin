// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slots 5, 7 (one-time setup and reset); layout and evidence:
// sidebar_class_layout.h.

#include "sidebar_class_layout.h"

// GLOBAL: GAMEMD 0xB07BC0 -- the DARKEN.SHP shape.
extern SidebarShapeFile* DarkenShape_00B07BC0;

// GLOBAL: GAMEMD 0x87F6D0 -- the second sidebar ConvertClass object.
extern SidebarConvert* ConvertB_0087F6D0;
// GLOBAL: GAMEMD 0x887308 -- the surface handed to both constructors.
extern void* ConvertSurface_00887308;

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// GLOBAL: GAMEMD 0xA8B238 -- session game mode (3 and 4 enable the observer panel).
extern int GameMode_00A8B238;
// GLOBAL: GAMEMD 0xA80238 / 0xA8022C -- HouseClass::Array.Count / .Items.
extern int HouseCount_00A80238;
extern SidebarHouse** HouseItems_00A8022C;
// GLOBAL: GAMEMD 0xB054D4 -- colour scheme registry.
extern void** ColorRegistry_00B054D4;
// FUNCTION: GAMEMD 0x68CA50 (decl; reloc) -- colour scheme lookup by name.
void* __fastcall SidebarFindColor(const char* name, int flag);

// The nth player house that is neither defeated nor the observer nor a
// non-human one (inlined twice by 0x6A5310).
inline SidebarHouse* NthObservedHouse(int n)
{
    int found = 0;
    for (int i = 0; i < HouseCount_00A80238; ++i) {
        SidebarHouse* house = HouseItems_00A8022C[i];
        if (house != 0 && house->Type->At_1A6 != 1 && house != Observer_00AC1198
            && house->At_1EC != 0) {
            if (found == n) {
                return house;
            }
            ++found;
        }
    }
    return 0;
}

// Sum of the two 20-entry tallies of a house.
inline int HouseTotal(SidebarHouse* house)
{
    if (house == 0) {
        return 0;
    }
    int total = 0;
    int k;
    for (k = 0; k < 20; ++k) {
        total += house->At_53E4[k];
    }
    for (k = 0; k < 20; ++k) {
        total += house->At_5438[k];
    }
    return total;
}

inline int HouseValue(SidebarHouse* house)
{
    if (house == 0) {
        return 0;
    }
    return house->At_2F8 + house->At_2F4 + house->At_2F0 + house->At_2E8;
}

inline int HouseCredits(SidebarHouse* house)
{
    if (house != 0) {
        int credits = (house->Sub24.*house->Sub24.Vtbl->At_18)();
        if (credits >= 0) {
            return credits;
        }
    }
    return 0;
}

// Frees one loaded shape if this module owns its memory. A macro rather than
// an inline function: cl stops inlining a helper after about 22 expansions
// and retail has every one of the 23 written out.
#define FreeShape(shape, owned) \
    do { \
        if (owned) { \
            delete shape; \
            owned = false; \
        } \
    } while (0)

// FUNCTION: GAMEMD 0x6A5000
void SidebarClass::vf_05()
{
    PowerClass::vf_05();
    for (int i = 0; i < 4; ++i) {
        DarkenShape_00B07BC0 = SidebarMixRetrieve("DARKEN.SHP", 0);
    }
}

// FUNCTION: GAMEMD 0x6A5030
void SidebarClass::vf_07()
{
    PowerClass::vf_07();
    At_53A6 = 1;
    At_5515 = 0;
    At_5514 = 0;
    for (int i = 0; i < 4; ++i) {
        Strips[i].FUN_006A81B0();
    }
    unknown_539C = 0;
    At_53A0 = 0;
    vf_54(0);
}

// Slot 8: builds the sidebar's gadgets: positions the repair, sell, tab and scroll
// buttons, initialises the four strips and, for the multiplayer observer panel,
// gathers up to eight houses with their score tallies.
//
// PARTIAL (47.9%, 160/334; LCS 311/332 = 93.7%). Multiset delta: retail has `jmp`
// 1 and `jl` 1 that cl has as `mov`, `jne`, `cmp`, `jge` (loop-head shapes). Two
// causes: (1) cl's list scheduler hoists stores whose operands are ready (the zero
// kept in EBX, ECX) ahead of the byte/immediate stores, so the repair block and the
// tab loop store in a different order from retail's source order (e.g. `[ESI+0x24]=EBX`
// before `[ESI-0x7]=1`); (2) retail enters the observer loop with `JMP` over a
// per-iteration `XOR EBP,EBP`, ours rotates the loop. Variants tried: statement order of
// the repair block (all 24 permutations of X/1D/ID/Y), hill-climbing over every single
// move and swap of the repair, sell and tab-loop statements (no improvement beyond 47.9%),
// locals for the three loaded values, Rect constructor assignment (reproduces retail's
// `LEA EDX,[ESI+4]` rect base), ternary and early-return forms of the house helpers.
// FUNCTION: GAMEMD 0x6A5310
void SidebarClass::vf_08()
{
    int i;
    PowerClass::vf_08();
    FUN_006A5090();
    FUN_006A5130(0);
    if (!DAT_00A8ED6B) {
        int repairY = RepairY_00B0B4E0;
        int repairX = RepairX_00B0B4DC;
        SidebarConvert* convert = ConvertA_0087F6CC;
        RepairButton_00B0B3A0.At_1D = 1;
        RepairButton_00B0B3A0.ID = 0x65;
        RepairButton_00B0B3A0.X = repairX;
        RepairButton_00B0B3A0.Y = repairY;
        RepairButton_00B0B3A0.At_44 = -480;
        RepairButton_00B0B3A0.At_48 = 0;
        RepairButton_00B0B3A0.At_4C = 1;
        RepairButton_00B0B3A0.At_50 = convert;
        RepairButton_00B0B3A0.IsOn = 0;
        RepairButton_00B0B3A0.At_30 = 1;
        RepairButton_00B0B3A0.At_40 = 1;
        RepairButton_00B0B3A0.StopFlashing();

        SellButton_00B07DF8.X = RepairButton_00B0B3A0.X + SellOffset_00B0B4E4;
        SellButton_00B07DF8.At_1D = 1;
        SellButton_00B07DF8.ID = 0x66;
        SellButton_00B07DF8.Y = RepairButton_00B0B3A0.Y;
        SellButton_00B07DF8.At_44 = -480;
        SellButton_00B07DF8.At_48 = 0;
        SellButton_00B07DF8.At_4C = 1;
        SellButton_00B07DF8.At_50 = ConvertA_0087F6CC;
        SellButton_00B07DF8.IsOn = 0;
        SellButton_00B07DF8.At_30 = 1;
        SellButton_00B07DF8.At_40 = 1;
        SellButton_00B07DF8.StopFlashing();

        for (i = 0; i < 4; ++i) {
            SidebarButton& tab = TabButtons_00B07C48[i];
            tab.At_1D = 1;
            tab.ID = 0xCB + i;
            tab.X = TabStep_00B0B4F0 * i + TabX_00B0B4E8;
            tab.Y = TabY_00B0B4EC;
            tab.At_44 = -480;
            tab.At_48 = 0;
            tab.At_4C = 1;
            tab.At_50 = ConvertA_0087F6CC;
            tab.IsOn = 0;
            tab.At_30 = 2;
            tab.At_40 = 1;
            tab.Disable();
            tab.StopFlashing();
        }

        ScrollDownButton_00B0B328.At_1D = 1;
        ScrollDownButton_00B0B328.ID = 0xC9;
        ScrollDownButton_00B0B328.At_4C = 1;
        ScrollDownButton_00B0B328.At_50 = ConvertA_0087F6CC;
        ScrollDownButton_00B0B328.At_20 = 0x55;
        ScrollDownButton_00B0B328.StopFlashing();

        ScrollUpButton_00B0B408.At_1D = 1;
        ScrollUpButton_00B0B408.ID = 0xC8;
        ScrollUpButton_00B0B408.At_4C = 1;
        ScrollUpButton_00B0B408.At_50 = ConvertA_0087F6CC;
        ScrollUpButton_00B0B408.At_20 = 0x55;
        ScrollUpButton_00B0B408.StopFlashing();

        for (i = 0; i < 4; ++i) {
            StripClass& strip = Strips[i];
            strip.At_20 = StripX_00B0B4F4;
            strip.At_24 = StripY_00B0B4F8;
            strip.Rect = Obj_006A5310(0, 0, 0x3C, StripHeight_00B0B504);
            strip.FUN_006A8220(i);
        }

        vf_34();
        FUN_006A5130(1);
        if (At_53A5) {
            vf_54(0);
            vf_54(1);
        }

        Count = 0;
        if (GameMode_00A8B238 == 3 || GameMode_00A8B238 == 4) {
            Houses[0] = NthObservedHouse(0);
            do {
                SidebarHouse* house = Houses[Count];
                if (house == 0) {
                    break;
                }
                Totals[Count] = HouseTotal(house);
                Values[Count] = HouseValue(house);
                At_540C[Count] = HouseCredits(house);
                void* color;
                if (house == 0) {
                    color = SidebarFindColor("Grey", 1);
                } else if (house == Observer_00AC1198) {
                    color = SidebarFindColor("LightGrey", 1);
                } else if (house->At_1F5) {
                    color = SidebarFindColor("Grey", 1);
                } else {
                    color = ColorRegistry_00B054D4[house->At_16054];
                }
                Colors[Count] = color;
                At_544C[Count] = 0;
                At_546C[Count] = 0;
                At_548C[Count] = 0;
                At_54AC[Count] = 0;
                At_54CC[Count] = 0;
                At_54EC[Count] = 0;
                if (GameMode_00A8B238 == 4) {
                    SidebarHouseRecord* record = house->At_1602A.FUN_0077DA50();
                    if (record != 0) {
                        At_544C[Count] = record->At_1C;
                        At_546C[Count] = record->At_10;
                        At_548C[Count] = record->At_08;
                        At_54AC[Count] = record->At_0C;
                        At_54CC[Count] = record->At_20;
                        At_54EC[Count] = record->At_30;
                        delete record;
                    }
                }
                Count = Count + 1;
                Houses[Count] = NthObservedHouse(Count);
            } while (Count < 8);
        }
        At_550C = 0;
    }
}

// Slot 53: loads the sidebar art (SHP files) and builds the two convert objects.
// MATCHED (100.0%, 234/234).
// FUNCTION: GAMEMD 0x6A5840
void SidebarClass::vf_53()
{
    PowerClass::vf_53();

    SidebarPalette paletteA = *SidebarGetPalette1();
    if (ConvertA_0087F6CC) {
        delete ConvertA_0087F6CC;
        ConvertA_0087F6CC = 0;
    }
    ConvertA_0087F6CC = new SidebarConvert(paletteA, paletteA, ConvertSurface_00887308, 1, 0);

    SideShapes_00B0B468[7] = SidebarLoadWholeFileEx("GCLOCK2.SHP", &SideShapeOwned_00B0B488[7]);

    bool owned = false;
    SellButton_00B07DF8.FUN_0069DE00(SidebarLoadWholeFileEx("SELL.SHP", &owned), 0, 0);
    SellButton_00B07DF8.SetLoadedStatus(owned);
    SellButton_00B07DF8.At_50 = ConvertA_0087F6CC;

    RepairButton_00B0B3A0.FUN_0069DE00(SidebarLoadWholeFileEx("REPAIR.SHP", &owned), 0, 0);
    RepairButton_00B0B3A0.SetLoadedStatus(owned);
    RepairButton_00B0B3A0.At_50 = ConvertA_0087F6CC;

    char name[0x100];
    for (int i = 0; i < 4; ++i) {
        sprintf(name, "TAB%02d.SHP", i);
        TabButtons_00B07C48[i].FUN_0069DE00(SidebarLoadWholeFileEx(name, &owned), 0, 0);
        TabButtons_00B07C48[i].SetLoadedStatus(owned);
        TabButtons_00B07C48[i].At_50 = ConvertA_0087F6CC;
    }

    ScrollDownButton_00B0B328.FUN_0069DE00(SidebarLoadWholeFileEx("R-DN.SHP", &owned), 0, 0);
    ScrollDownButton_00B0B328.SetLoadedStatus(owned);
    ScrollDownButton_00B0B328.At_50 = ConvertA_0087F6CC;

    ScrollUpButton_00B0B408.FUN_0069DE00(SidebarLoadWholeFileEx("R-UP.SHP", &owned), 0, 0);
    ScrollUpButton_00B0B408.SetLoadedStatus(owned);
    ScrollUpButton_00B0B408.At_50 = ConvertA_0087F6CC;

    SideShapes_00B0B468[0] = SidebarLoadWholeFileEx("SIDE1.SHP", &SideShapeOwned_00B0B488[0]);
    SideShapes_00B0B468[1] = SidebarLoadWholeFileEx("SIDE2.SHP", &SideShapeOwned_00B0B488[1]);
    SideShapes_00B0B468[2] = SidebarLoadWholeFileEx("SIDE3.SHP", &SideShapeOwned_00B0B488[2]);
    SideShapes_00B0B468[3] = SidebarLoadWholeFileEx("ADDON.SHP", &SideShapeOwned_00B0B488[3]);

    SidebarPalette paletteB = *SidebarGetPalette2();
    if (ConvertB_0087F6D0) {
        delete ConvertB_0087F6D0;
        ConvertB_0087F6D0 = 0;
    }
    ConvertB_0087F6D0 = new SidebarConvert(paletteB, paletteB, ConvertSurface_00887308, 1, 0);

    ObsShapes_00B0B490[0] = SidebarLoadWholeFileEx("OBSALLI.SHP", &ObsShapeOwned_00B0B4CC[0]);
    ObsShapes_00B0B490[1] = SidebarLoadWholeFileEx("OBSSOVI.SHP", &ObsShapeOwned_00B0B4CC[1]);
    ObsShapes_00B0B490[2] = SidebarLoadWholeFileEx("OBSYURI.SHP", &ObsShapeOwned_00B0B4CC[2]);
    ObsShapes_00B0B490[3] = SidebarLoadWholeFileEx("RANI.SHP", &ObsShapeOwned_00B0B4CC[3]);
    ObsShapes_00B0B490[4] = SidebarLoadWholeFileEx("OBSI.SHP", &ObsShapeOwned_00B0B4CC[4]);
    ObsShapes_00B0B490[5] = SidebarLoadWholeFileEx("USAI.SHP", &ObsShapeOwned_00B0B4CC[5]);
    ObsShapes_00B0B490[6] = SidebarLoadWholeFileEx("JAPI.SHP", &ObsShapeOwned_00B0B4CC[6]);
    ObsShapes_00B0B490[7] = SidebarLoadWholeFileEx("FRAI.SHP", &ObsShapeOwned_00B0B4CC[7]);
    ObsShapes_00B0B490[8] = SidebarLoadWholeFileEx("GERI.SHP", &ObsShapeOwned_00B0B4CC[8]);
    ObsShapes_00B0B490[9] = SidebarLoadWholeFileEx("GBRI.SHP", &ObsShapeOwned_00B0B4CC[9]);
    ObsShapes_00B0B490[10] = SidebarLoadWholeFileEx("DJBI.SHP", &ObsShapeOwned_00B0B4CC[10]);
    ObsShapes_00B0B490[11] = SidebarLoadWholeFileEx("ARBI.SHP", &ObsShapeOwned_00B0B4CC[11]);
    ObsShapes_00B0B490[12] = SidebarLoadWholeFileEx("LATI.SHP", &ObsShapeOwned_00B0B4CC[12]);
    ObsShapes_00B0B490[13] = SidebarLoadWholeFileEx("RUSI.SHP", &ObsShapeOwned_00B0B4CC[13]);
    ObsShapes_00B0B490[14] = SidebarLoadWholeFileEx("YRII.SHP", &ObsShapeOwned_00B0B4CC[14]);
}

// FUNCTION: GAMEMD 0x6A5BF0
void SidebarClass::vf_50()
{
    PowerClass::vf_50();
    FreeShape(SideShapes_00B0B468[0], SideShapeOwned_00B0B488[0]);
    FreeShape(SideShapes_00B0B468[1], SideShapeOwned_00B0B488[1]);
    FreeShape(SideShapes_00B0B468[2], SideShapeOwned_00B0B488[2]);
    FreeShape(SideShapes_00B0B468[3], SideShapeOwned_00B0B488[3]);
    FreeShape(SideShapes_00B0B468[4], SideShapeOwned_00B0B488[4]);
    FreeShape(SideShapes_00B0B468[5], SideShapeOwned_00B0B488[5]);
    FreeShape(SideShapes_00B0B468[6], SideShapeOwned_00B0B488[6]);
    FreeShape(SideShapes_00B0B468[7], SideShapeOwned_00B0B488[7]);
    FreeShape(ObsShapes_00B0B490[0], ObsShapeOwned_00B0B4CC[0]);
    FreeShape(ObsShapes_00B0B490[1], ObsShapeOwned_00B0B4CC[1]);
    FreeShape(ObsShapes_00B0B490[2], ObsShapeOwned_00B0B4CC[2]);
    FreeShape(ObsShapes_00B0B490[3], ObsShapeOwned_00B0B4CC[3]);
    FreeShape(ObsShapes_00B0B490[5], ObsShapeOwned_00B0B4CC[5]);
    FreeShape(ObsShapes_00B0B490[6], ObsShapeOwned_00B0B4CC[6]);
    FreeShape(ObsShapes_00B0B490[7], ObsShapeOwned_00B0B4CC[7]);
    FreeShape(ObsShapes_00B0B490[8], ObsShapeOwned_00B0B4CC[8]);
    FreeShape(ObsShapes_00B0B490[9], ObsShapeOwned_00B0B4CC[9]);
    FreeShape(ObsShapes_00B0B490[10], ObsShapeOwned_00B0B4CC[10]);
    FreeShape(ObsShapes_00B0B490[11], ObsShapeOwned_00B0B4CC[11]);
    FreeShape(ObsShapes_00B0B490[12], ObsShapeOwned_00B0B4CC[12]);
    FreeShape(ObsShapes_00B0B490[13], ObsShapeOwned_00B0B4CC[13]);
    FreeShape(ObsShapes_00B0B490[4], ObsShapeOwned_00B0B4CC[4]);
    FreeShape(ObsShapes_00B0B490[14], ObsShapeOwned_00B0B4CC[14]);
    SellButton_00B07DF8.ClearShape();
    RepairButton_00B0B3A0.ClearShape();
    for (int i = 0; i < 4; ++i) {
        TabButtons_00B07C48[i].ClearShape();
    }
    ScrollDownButton_00B0B328.ClearShape();
    ScrollUpButton_00B0B408.ClearShape();
}
