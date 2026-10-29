// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Original translation unit Sidebar.CPP. The name is the source-file string at 0x83fac4
//   in retail gamemd.exe v1.001, passed by the assert at 0x6a9362 inside this object's
//   code range (0x6a4a20-0x6ac96f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
// The four argument forwarders, ordered ascending by retail address.
//
// SidebarClass slot 54 (show / hide the sidebar); layout and evidence:
// sidebar_class_layout.h.
//
// SidebarClass slot 16 (draw); layout and evidence: sidebar_class_layout.h.
//
// SidebarClass slots 5, 7 (one-time setup and reset); layout and evidence:
// sidebar_class_layout.h.
//
// SidebarClass slot 34 (reposition every sidebar gadget and re-register the
// tooltips); layout and evidence: sidebar_class_layout.h.
//
// SidebarClass slot 33 (tooltip text for a sidebar gadget id); layout and
// evidence: sidebar_class_layout.h. References the source path string
// D:\ra2mdpost\Sidebar.CPP at 0x83FAC4.
//
// SidebarClass::StripClass::SelectClass and SidebarClass::SBGadgetClass slots
// (layout and evidence: sidebar_select_class.h).

#include "../../core/vector_class_operations.h"
#include "../../_layout/session_class.h"
#include "../../core/mathtbl_init_shapes.h"
#include "../../core/deleting_dtor_sweep.h"
#include "../../network/transport/winsock_interface_class.h"
#include "../../_layout/pipe.h"
#include "../../_layout/straw.h"

#include "../../core/leftover_trivial_leaf_sweep.h"

#include "../../core/stdcall_forward_sweep.h"

#include "sidebar_class_layout.h"
#include "../shape_button_class.h"
#include "../../platform/ccini_class_small_readers_methods.h"
#include "../../combat/super_weapon_type_class_methods.h"

// GLOBAL: GAMEMD 0xA8D5F8 -- bit 1 set while the game is in a restricted mode.
#include "../../core/game_state_flags.h"

// FUNCTION: GAMEMD 0x5BF450 (decl; reloc) -- releases the pump list.
void FUN_005BF450();

#include "sidebar_class_layout.h"
#include "../tooltip_manager_shared.h"

// GLOBAL: GAMEMD 0x8809F4 -- clip rectangle, copied from the object at 0xB07DC8.
struct SidebarClipRect
{
    int X;
    int Y;
    int Width;
    int Height;
};
extern SidebarClipRect ClipRect_008809F4;
// GLOBAL: GAMEMD 0xB07DC8 -- source of the clip rectangle.
extern SidebarClipRect BackdropRect_00B07DC8;
// GLOBAL: GAMEMD 0xB0B518 -- accumulated "something was redrawn" flag.
// (SidebarTouched_00B0B518 in the layout header.)

// Number of cameo rows that fit in the sidebar (expanded inline by 0x6A6C30).
inline int SidebarRowCount()
{
    int margin = 0x1A;
    if (DAT_00A8B230->unknown_34B8) {
        margin = 0x12;
    }
    return (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50;
}

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- draw a shape: surface in ECX, convert
// in EDX, fourteen stack arguments (RET 0x38).
void SidebarDrawShape(SidebarSurfaceView* surface, SidebarConvert* convert,
                      SidebarShapeFile* shape, int frame, Point2D* position,
                      SidebarAreaRect* bounds, int flags, int a6, int a7, int a8,
                      int zAdjust, int a10, int a11, int a12, Point2D offset);

// One 0x400-flag shape draw at (0, y) on the sidebar surface; expanded inline by 0x6A6C30.
inline void DrawSidebarShape(int shape, int frame, int y, SidebarAreaRect* bounds)
{
    Point2D position;
    position.X = 0;
    position.Y = y;
    Point2D offset(0, 0);
    SidebarDrawShape(SidebarSurface_00887300, ConvertA_0087F6CC, SideShapes_00B0B468[shape], frame,
                     &position, bounds, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

#include "sidebar_class_layout.h"

// GLOBAL: GAMEMD 0xB07BC0 -- the DARKEN.SHP shape.
extern SidebarShapeFile* DarkenShape_00B07BC0;

// GLOBAL: GAMEMD 0x87F6D0 -- the second sidebar ConvertClass object.
extern SidebarConvert* ConvertB_0087F6D0;
// GLOBAL: GAMEMD 0x887308 -- the surface handed to both constructors.
extern void* ConvertSurface_00887308;

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// GLOBAL: GAMEMD 0xA80238 / 0xA8022C -- HouseClass::Array.Count / .Items.
extern int HouseCount_00A80238;
extern SidebarHouse** HouseItems_00A8022C;
// GLOBAL: GAMEMD 0xB054D4 -- colour scheme registry.
extern void** ColorRegistry_00B054D4;

// FUNCTION: GAMEMD 0x68CA50 (decl; reloc) -- colour scheme lookup by name.
void* SidebarFindColor(const char* name, int flag);

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

#include "sidebar_class_layout.h"
#include "../tooltip_manager_shared.h"

#include "sidebar_class_layout.h"

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* SidebarLoadString(const char* label, int* out, const char* file, int line);

extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0xB079B0 -- shared tooltip formatting buffer.
extern wchar_t TipBuffer_00B079B0[];

// Slot 33: tooltip text for a sidebar gadget id.
//
// PARTIAL (30.4%, 45/148; LCS 85/130 = 65.4%). Multiset delta: retail has one `sete`
// that cl lacks (retail materialises `!IsEnabled()` with `TEST; SETE; TEST; JE`) and ours
// has the per-case copies of the disabled-text block (retail shares one block, laid
// out directly after the first case, with the later cases jumping back to it). Variants:
// one shared check after the chain (9.2%), per-case inline `DisabledTip` (kept), a
// labelled shared check (14.6%, registers match retail but the shared block is still
// laid out last).
// A tooltip for a disabled button reads "<tip>\n(<disabled>)".
inline const wchar_t* DisabledTip(const SidebarButton* button, const wchar_t* text)
{
    if (!button->IsEnabled()) {
        wchar_t* disabled = SidebarLoadString("Tip:Disabled", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13F4);
        swprintf(TipBuffer_00B079B0, L"%s\n(%s)", text, disabled);
        return TipBuffer_00B079B0;
    }
    return text;
}

#include "sidebar_select_class.h"

// ---------------------------------------------------------------------------
// SelectClass::Action (0x6AAD00): left / right click on a build entry
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x48DCD0 (decl; reloc) -- TechnoTypeClass::GetByTypeAndIndex.
SelectTechnoType* SelectGetByTypeAndIndex(int type, int index);

// FUNCTION: GAMEMD 0x752700 (decl; reloc) -- VoxClass::Play(name, a, b).
void SelectVoxPlay(const char* name, int a, int b);


// FUNCTION: GAMEMD 0x40DD70 (decl; reloc) -- WhatAmIHolder check on the placement object.
void* SelectCheckPlacement(void* object);

// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) -- MapClass::UnselectAll.
void SelectUnselectAll();

// LIBRARY: GAMEMD 0x7C5F00 is the compiler's float-to-int helper (_ftol).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern SidebarHouse* SelectPlayer_00A83D4C;
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern SidebarRules* SelectRules_008871E0;
// GLOBAL: GAMEMD 0x88098C / 0x880990 / 0x880994 / 0x8809A0 / 0x88099A..0x88099C -- placement state.
#include "../../_layout/placement_object.h"
extern int PlacementIndex_00880994;
extern int PendingSuper_008809A0;
extern unsigned char PlacementFlagA_0088099A;
extern unsigned char PlacementFlagB_0088099B;
extern unsigned char PlacementFlagC_0088099C;
// GLOBAL: GAMEMD 0xB07DD8 -- cell handed to a placement event.
extern int PlacementCell_00B07DD8;
// GLOBAL: GAMEMD 0xA8B550 -- build speed percentage.
extern int BuildSpeed_00A8B550;
// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int CurrentFrame_00A8ED84;
// GLOBAL: GAMEMD 0x880D68 -- per-strip "needs redraw" byte of the map's strips (stride 0xF94).
extern unsigned char StripRedraw_00880D68[];

// The outgoing event queue (0xA802C8 count, 0xA802D0 tail, 0xA802D4 list, 0xA83A54 timestamps).
extern int EventCount_00A802C8;
extern int EventTail_00A802D0;
extern SelectEvent EventList_00A802D4[128];
extern unsigned long EventTime_00A83A54[128];

inline void SelectEvent::Queue()
{
    if (EventCount_00A802C8 < 0x80) {
        EventList_00A802D4[EventTail_00A802D0] = *this;
        EventTime_00A83A54[EventTail_00A802D0] = timeGetTime();
        EventTail_00A802D0 = (EventTail_00A802D0 + 1) & 0x7F;
        EventCount_00A802C8 = EventCount_00A802C8 + 1;
    }
}

#include "../sidebar_class_set_tab_methods.h"

#include "../sidebar_class_techno_destroyed_methods.h"

// SidebarClass::GetObjectTabIdx expanded inline here — the same compare chain
// matched out of line at 0x6ABC60; written as an if-chain in source order,
// because a switch over these values becomes a jump table.
static inline int GetObjectTabIdx_006A5F20(int abs, int idxType)
{
    if (abs == ABS_INFANTRYTYPE_006A5F20 || abs == ABS_UNITTYPE_006A5F20)
        return 2;

    if (abs == ABS_UNIT_006A5F20 || abs == ABS_INFANTRY_006A5F20
        || abs == ABS_AIRCRAFT_006A5F20 || abs == ABS_BUILDING_006A5F20)
        return 3;

    if (abs == ABS_BUILDINGTYPE_006A5F20 || abs == ABS_AIRCRAFTTYPE_006A5F20)
        return IsBuildCat5_006A5F20(abs, idxType) == 5;

    if (abs == ABS_BUILDINGTYPE2_006A5F20 || abs == ABS_ABSTRACTTYPE_006A5F20
        || abs == ABS_SUPERWEAPON_006A5F20)
        return 1;

    return -1;
}

#include "../trivial_tu211_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F2F30
extern const double DAT_007F2F30;
// GLOBAL: GAMEMD 0xB07DE0
extern double DAT_00B07DE0;
// GLOBAL: GAMEMD 0xA8E340
extern int DAT_00A8E340;

// SYNTHETIC: GAMEMD 0x006A4A50
// GLOBAL: GAMEMD 0x00B0B398
double DAT_00B0B398 = DAT_00B07DE0 / DAT_007F2F30;

// SYNTHETIC: GAMEMD 0x006A4A70
// GLOBAL: GAMEMD 0x00B0B320
double DAT_00B0B320 = DAT_007E1718 / DAT_00B0B398;

// SYNTHETIC: GAMEMD 0x006A4BF0
// GLOBAL: GAMEMD 0x00B0B388
MathTblCoord DAT_00B0B388;

// REA Evidence: ev_2ae381b14ec2843cc91bb4231572d98ff6eb01c68dc88b2d17c3a381358b4d14
// CFG-closed retail span [0x6A4E60, 0x6A4F11), 0xB1 bytes. TabClass constructor 0x6CFE20
// calls this with its original ECX receiver before initializing the TabClass subobject.
// FUNCTION: GAMEMD 0x6A4E60
SidebarClass::SidebarClass()
{
    unknown_539C = 0;
    At_53A0 = 0;
    unknown_53A4 = false;
    At_53A5 = false;
    At_53A6 = true;
    unknown_53A8[0] = 0;
    At_5514 = 0;
    At_5515 = 0;

    unsigned char local;
    for (int i = 0; i < 4; ++i) {
        Strips[i].FUN_006A80A0(&local);
    }
}

// REA Evidence: ev_1dd5458f92702204515ba913680947a6074d3d7212c547bcbcf63868c928ef9d
// CFG-closed retail span [0x6A4F20, 0x6A4FF0), 0xD0 bytes; the RET 4 ends at 0x6A4FED.
// Constructor calls the tagged DisplayClass initializer, three canonical vector forms,
// two canonical elapsed timers, Obj_00405B00::FUN_00405BE0, and four StripClass elements.
// FUNCTION: GAMEMD 0x6A4F20
SidebarClass::SidebarClass(const Obj_005BDF70& noInit)
    : PowerClass(noInit)
{
}

// FUNCTION: GAMEMD 0x6A4FF0
void __stdcall FUN_006A4FF0(int)
{
}

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

// FUNCTION: GAMEMD 0x6A5090
void SidebarClass::FUN_006A5090()
{
    if (DAT_00A8B230->unknown_34B8 == 0) {
        SellOffset_00B0B4E4 = 0x40;
        TabStep_00B0B4F0 = 0x1D;
        ColumnStep_00B0B4FC = 0x3F;
        int y = DAT_00886F94 + 8;
        RepairY_00B0B4E0 = y;
        y += 0x1F;
        TabY_00B0B4EC = y;
        y += 0x1E;
        StripY_00B0B4F8 = y;
        return;
    }

    int y;
    if (DAT_00A8B230->unknown_34B8 == 1) {
        y = DAT_00886F94 + 7;
    } else {
        y = DAT_00886F94;
        y += 7;
    }
    RepairY_00B0B4E0 = y;
    y += 0x20;
    TabY_00B0B4EC = y;
    y += 0x1E;
    SellOffset_00B0B4E4 = 0x34;
    TabStep_00B0B4F0 = 0x20;
    StripY_00B0B4F8 = y;
    ColumnStep_00B0B4FC = 0x40;
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
        if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
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
                if (Session_00A8B238.GameMode == 4) {
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

// FUNCTION: GAMEMD 0x6A5F20  SidebarClass::OnTechnoDestroyed (__thiscall, ret 4)
//
// Something the player owned has just gone away. If the sidebar is up and the
// object belongs to the tab currently on show — and losing it costs the player
// that cameo — the tab's strip is flagged for a redraw. A building that is not
// on the current tab still dirties the buildings strip when its owner marks it
// as one that changes what can be built. Either way the sidebar is marked
// dirty and a repaint is asked for, with the repaint deadline pushed two
// frames out when it has already lapsed.
void Sidebar_006A5F20::OnTechnoDestroyed(Techno_006A5F20* obj)
{
    if (this->At_53A5 == 0) {
        return;
    }
    if (obj == 0) {
        return;
    }

    TechnoType_006A5F20* type = (obj->*obj->Vtbl->GetTechnoType)();
    if (PlayerPtr_006A5F20 == 0) {
        return;
    }

    int abs = (obj->*obj->Vtbl->WhatAmI)();
    int tab = GetObjectTabIdx_006A5F20(abs, (obj->*obj->Vtbl->At_40)());

    int active = this->ActiveTabIndex;
    if (tab == active) {
        if (PlayerPtr_006A5F20->FUN_0050B370(type)) {
            this->At_53A6 = 1;
            this->Tabs[this->ActiveTabIndex].At_3C = 1;
            MapInstance_006A5F20.FlagToRedraw(0);
            if (this->At_53A0 <= CurrentFrame) {
                this->At_53A0 = CurrentFrame + 2;
            }
        }
    } else if (abs == ABS_BUILDINGTYPE_006A5F20) {
        if (obj->At_520->At_16CB != 0 && active == 3) {
            this->At_53A6 = 1;
            // Taking the strip's address into a local is what keeps the
            // dirty-byte store above the repaint call's argument setup: with
            // the constant-folded `this->Tabs[3].At_3C = 1;` cl hoists the
            // PUSH/MOV ECX pair above it. The first arm needs no such anchor
            // because its index arithmetic already sits between the two.
            Strip_006A5F20* strip = &this->Tabs[3];
            strip->At_3C = 1;
            MapInstance_006A5F20.FlagToRedraw(0);
            if (this->At_53A0 <= CurrentFrame) {
                this->At_53A0 = CurrentFrame + 2;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x6A5ED0
void SidebarClass::FUN_006A5ED0()
{
    At_53A6 = 1;
    Strips[unknown_539C].At_3C = 1;
    Map_0087F7E8.FlagToRedraw(0);
    if (At_53A0 <= CurrentFrame_00A8ED84) {
        At_53A0 = CurrentFrame_00A8ED84 + 2;
    }
}

// FUNCTION: GAMEMD 0x6A60E0
void SidebarClass::FUN_006A60E0(int tab)
{
    if (tab == unknown_539C) {
        At_53A6 = 1;
        Strips[unknown_539C].At_3C = 1;
        Map_0087F7E8.FlagToRedraw(0);
        if (At_53A0 <= CurrentFrame_00A8ED84) {
            At_53A0 = CurrentFrame_00A8ED84 + 2;
        }
    }
}

// FUNCTION: GAMEMD 0x6A6220
unsigned char SidebarClass::FUN_006A6220(int mode)
{
    unsigned char previous = At_5515;
    if (mode == -1) {
        mode = !previous;
    }
    switch (mode) {
    case 1:
        At_5515 = 1;
        break;
    default:
        At_5515 = 0;
        break;
    }
    if (previous != At_5515) {
        FlagToRedraw(0);
        At_53A6 = 1;
        if (!At_5515) {
            vf_18(0, 0);
        }
    }
    return previous;
}

// FUNCTION: GAMEMD 0x6A6290
unsigned char SidebarClass::FUN_006A6290(int mode)
{
    unsigned char previous = At_5514;
    if (mode == -1) {
        mode = !previous;
    }
    switch (mode) {
    case 1:
        At_5514 = 1;
        break;
    default:
        At_5514 = 0;
        break;
    }
    if (previous != At_5514) {
        FlagToRedraw(0);
        At_53A6 = 1;
        if (!At_5514) {
            vf_18(0, 0);
        }
    }
    return previous;
}

// Slot 16: draws the sidebar: backdrop shapes, the buttons, the open/close animation
// frames and the current strip, then folds the buttons' redraw flags into one.
//
// PARTIAL 9.9%. The shape drawer's last two arguments are one point passed by value
// (the source of retail's register zeros). Remaining: retail loads the backdrop
// rectangle after the callee-saved pushes, ours before, and the register choice of the
// zero registers. The shape draws are expanded from an inline helper. Earlier
// attempts: open-coded draws, the inline helper (kept), a zero local.
// FUNCTION: GAMEMD 0x6A6C30
void SidebarClass::vf_16(bool forced)
{
    ClipRect_008809F4 = BackdropRect_00B07DC8;
    SidebarSurfaceView* previous = CurrentSurface_00887314;
    CurrentSurface_00887314 = SidebarSurface_00887300;
    bool drewBackground = false;
    SidebarAreaRect bounds;
    bounds.Height = (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_80)();
    bounds.Width = (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_7C)();
    bounds.X = 0;
    bounds.Y = 0;
    if (forced || At_53A6 || At_53A7) {
        forced = true;
    } else {
        forced = false;
    }
    if (At_53A5 && forced && !DAT_00A8ED6B) {
        if (At_53A7) {
            drewBackground = true;
            DrawSidebarShape(0, 0, DAT_00886F94, &bounds);
            int y = StripY_00B0B4F8;
            for (int i = 0; i < SidebarRowCount(); ++i) {
                DrawSidebarShape(1, 0, y, &bounds);
                y += SideShapes_00B0B468[1]->Height;
            }
            DrawSidebarShape(2, 0, y, &bounds);
            DrawSidebarShape(3, 0, SideShapes_00B0B468[2]->Height + y, &bounds);
        }
        SellButton_00B07DF8.Draw(drewBackground);
        RepairButton_00B0B3A0.Draw(drewBackground);
        for (int j = 0; j < 4; ++j) {
            TabButtons_00B07C48[j].Draw(1);
        }
        ScrollDownButton_00B0B328.Draw(drewBackground);
        ScrollUpButton_00B0B408.Draw(drewBackground);
        if (unknown_5398 != 0) {
            DrawSidebarShape(4, unknown_5394, StripY_00B0B4F8, &bounds);
            DrawSidebarShape(5, unknown_5394, StripY_00B0B4F8, &bounds);
            DrawSidebarShape(6, unknown_5394, StripY_00B0B4F8, &bounds);
        }
        SidebarTouched_00B0B518 = 1;
    }
    Strips[unknown_539C].FUN_006A9540(At_53A7);
    PowerClass::vf_16(forced || drewBackground);
    if (SellButton_00B07DF8.At_54) {
        SellButton_00B07DF8.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (RepairButton_00B0B3A0.At_54) {
        RepairButton_00B0B3A0.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    for (int k = 0; k < 4; ++k) {
        if (TabButtons_00B07C48[k].At_54) {
            TabButtons_00B07C48[k].At_54 = false;
            SidebarTouched_00B0B518 = 1;
        }
    }
    if (ScrollDownButton_00B0B328.At_54) {
        ScrollDownButton_00B0B328.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (ScrollUpButton_00B0B408.At_54) {
        ScrollUpButton_00B0B408.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (ToolTipManager_Instance) {
        ToolTipManager_Instance->Draw(true);
    }
    FUN_006A70E0(SidebarTouched_00B0B518 || At_53A7);
    At_53A6 = false;
    At_53A7 = false;
    CurrentSurface_00887314 = previous;
}

// FUNCTION: GAMEMD 0x6A7590
//
// PARTIAL (94.9%, 93/98; instruction multiset identical). The only residual
// delta is the sidebar margin constant, and it is the failure class already
// banked for the same formula in match/ui/sidebar_class_scroll_methods.cpp
// (0x6A6A00): retail loads the scenario flag into EAX, tests it, and then
// materialises MOV EAX,0x1A between the TEST and the JZ, while cl 12.00.8804
// hoists the constant above the flag load and tests the flag in EDX. That TU
// already records the exhausted variant list (if/else either way, ternary,
// `-= 8`, `0x1A - (flag ? 8 : 0)`, a flag/bool local read first, the flag
// reused as the margin variable, and an inlined helper — the ternary/helper
// and subtraction forms all go branchless NEG/SBB/AND), so it was not re-run
// here; two further spellings were re-run on this TU anyway — the flag itself
// bound as the margin variable and then overwritten per arm, in both arm
// orders (`if (margin != 0) margin = 0x12; else margin = 0x1A;` and the
// equal-case-first mirror) — and both go branchless (NEG/SBB/AND/ADD, 69.4%),
// which is worse than the hoisted constant. Every other instruction in this
// function is exact.
//
// SidebarClass::SetTab — switch the sidebar to another build tab. Selecting the
// tab that is already active does nothing. Otherwise the old tab record is
// unselected, its strip is cleared and all sixty of its cameo buttons are taken
// off the map's button list; the new tab becomes active and is marked selected;
// and as many of the new strip's buttons as fit in the sidebar (the same
// 50-pixel row arithmetic as SidebarClass::Scroll, two cameos per row) are
// refreshed and put back on the list. The sidebar is then flagged for a full
// redraw and rebuilt.
void Sidebar_006A7590::SetTab(int tab)
{
    if (tab == this->ActiveTabIndex) {
        return;
    }

    DAT_00B07C48[this->ActiveTabIndex].FUN_00723EB0();

    Strip_006A7590* strip = &this->Tabs[this->ActiveTabIndex];
    strip->IsSelected = 0;
    for (int i = 0; i < 60; i++) {
        MapInstance_006A7590.FUN_004F4450(&DAT_00B07E80[strip->RowBlock * 60 + i]);
    }

    this->ActiveTabIndex = tab;
    DAT_00B07C48[tab].FUN_00723EA0();

    strip = &this->Tabs[this->ActiveTabIndex];
    strip->IsSelected = 1;

    int margin = 0x1A;
    if (ScenarioInstance_006A7590->At_34B8) {
        margin = 0x12;
    }
    int count = ((DAT_00886F9C - DAT_00B0B4F8 - margin - 7 + DAT_00886F94) / 50) * 2;

    for (int j = 0; j < count; j++) {
        DAT_00B07E80[strip->RowBlock * 60 + j].FUN_005565F0();
        MapInstance_006A7590.FUN_004F4410(&DAT_00B07E80[strip->RowBlock * 60 + j]);
    }

    DAT_00884B8F = 1;
    this->FUN_006A6610();
    this->At_53A7 = 1;
}

// FUNCTION: GAMEMD 0x6A7760
void __stdcall FUN_006A7760(int index)
{
    // Retail steps 0x60 bytes from 0xB07C48 before calling ShapeButtonClass::StopFlashing.
    ((ShapeButtonClass*)&TabButtons_00B07C48[index])->StopFlashing();
}

// Slot 54: shows or hides the sidebar (-1 toggles); registers or removes every gadget
// and rebuilds the visible cameo buttons.
//
// PARTIAL (86.0%, 197/229). Same instruction multiset as retail. Two differences:
// (1) retail pushes EBP and EDI only after the `changed` test (`JE 0x6A8078` skips the
// pops), cl pushes them together with EBX before it; (2) retail loads the scenario flag
// into EAX before `MOV EAX,0x1A`, cl hoists the constant above the flag load.
// Variants tried: the changed flag as a nested `if`, as an early `return changed`
// (worse: separate epilogue), as an int, recomputed at the end, `== true`; the margin
// as local flag, if/else both ways, negated test.
// FUNCTION: GAMEMD 0x6A7D70
bool SidebarClass::vf_54(int control)
{
    bool old = At_53A5;
    if (DAT_00A8D5F8 & 2) {
        if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5) {
            return old;
        }
    }
    if (control != -1) {
        At_53A5 = (control == 1);
    } else {
        At_53A5 = (old == 0);
    }
    bool changed = At_53A5 != old;
    if (changed) {
        FUN_00652E50(At_53A5);
        if (At_53A5) {
            vf_34();
            At_53A6 = 1;
            SellButton_00B07DF8.Zap();
            AddButton(&SellButton_00B07DF8);
            RepairButton_00B0B3A0.Zap();
            AddButton(&RepairButton_00B0B3A0);
            for (int i = 0; i < 4; ++i) {
                TabButtons_00B07C48[i].Zap();
                TabButtons_00B07C48[i].At_2C = 0;
                AddButton(&TabButtons_00B07C48[i]);
            }
            ScrollDownButton_00B0B328.Zap();
            Map_0087F7E8.AddButton(&ScrollDownButton_00B0B328);
            ScrollUpButton_00B0B408.Zap();
            Map_0087F7E8.AddButton(&ScrollUpButton_00B0B408);
            ExtraButton_00B07E58.Zap();
            AddButton(&ExtraButton_00B07E58);
            ExtraGadget_00B04A10.Zap();
            AddButton(&ExtraGadget_00B04A10);
            for (int j = 0; j < 4; ++j) {
                Strips[j].TopRowIndex = 0;
                if (Strips[j].CameoCount > 0) {
                    TabButtons_00B07C48[j].Enable();
                }
            }
            TabButtons_00B07C48[unknown_539C].TurnOn();
            StripClass* strip = &Strips[unknown_539C];
            strip->At_1C = 1;
            int margin = 0x1A;
            if (DAT_00A8B230->unknown_34B8) {
                margin = 0x12;
            }
            int rows = (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50 * 2;
            for (int k = 0; k < rows; ++k) {
                CameoButtons_00B07E80[strip->RowBase * 60 + k].Zap();
                MapInstance_0087F7E8.AddButton(&CameoButtons_00B07E80[strip->RowBase * 60 + k]);
            }
            SidebarNeedsRedraw_00884B8F = 1;
            FUN_006A6610();
            FlagToRedraw(2);
        } else {
            FUN_005BF450();
            vf_13(&SellButton_00B07DF8);
            vf_13(&RepairButton_00B0B3A0);
            vf_13(&ExtraButton_00B07E58);
            for (int i = 0; i < 4; ++i) {
                vf_13(&TabButtons_00B07C48[i]);
            }
            vf_13(&ScrollDownButton_00B0B328);
            vf_13(&ScrollUpButton_00B0B408);
            StripClass* strip = &Strips[unknown_539C];
            for (int k = 0; k < 60; ++k) {
                MapInstance_0087F7E8.FUN_004F4450(&CameoButtons_00B07E80[strip->RowBase * 60 + k]);
            }
            vf_13(&ExtraGadget_00B04A10);
            FlagToRedraw(2);
        }
    }
    return changed;
}

// FUNCTION: GAMEMD 0x6A8080
int __fastcall FUN_006A8080(int index)
{
    return ColumnStep_00B0B4FC * index;
}

// FUNCTION: GAMEMD 0x6A8090
int __fastcall FUN_006A8090(int index)
{
    return RowStep_00B0B500 * index + 1;
}

// FUNCTION: GAMEMD 0x6A80A0
StripClass* StripClass::FUN_006A80A0(void* unknown_00)
{
    this->unknown_00 = 0;
    this->unknown_04 = false;
    int currentFrame = CurrentFrame_00A8ED84;
    this->unknown_14 = 0;
    this->Timer.StartFrame = currentFrame;
    this->Timer.TimeLeft = 0;
    this->unknown_18 = 1;
    this->At_20 = 0;
    this->At_24 = 0;
    this->Rect.X = BackdropRect_00B07DC8.X;
    this->Rect.Y = BackdropRect_00B07DC8.Y;
    this->Rect.Width = BackdropRect_00B07DC8.Width;
    this->Rect.Height = BackdropRect_00B07DC8.Height;
    this->RowBase = 0;
    this->At_3C = 1;
    this->unknown_3D = 0;
    this->unknown_3E = 0;
    this->unknown_3F = 0;
    this->unknown_40 = -1;
    this->TopRowIndex = 0;
    this->At_48 = 0;
    this->unknown_4C = 0;
    this->unknown_50 = 0;
    this->CameoCount = 0;

    SidebarCameo* cameo = Cameos;
    int count = 0x4B;
    do {
        cameo->unknown_14 = 0;
        cameo->unknown_18.Bytes.Low = 0;
        cameo->unknown_1C = 0;
        cameo->unknown_24 = CurrentFrame_00A8ED84;
        cameo->unknown_28 = 0;
        cameo->unknown_2C = 1;
        ++cameo;
        --count;
    } while (count != 0);

    cameo = Cameos;
    count = 0x4B;
    do {
        cameo->unknown_00 = 0;
        cameo->unknown_04.Bytes[0] = 0;
        cameo->unknown_04.Bytes[1] = 0;
        cameo->unknown_04.Bytes[2] = 0;
        cameo->unknown_04.Bytes[3] = 0;
        cameo->unknown_08 = 0;
        cameo->Pointer = 0;
        ++cameo;
        --count;
    } while (count != 0);
    return this;
}

// FUNCTION: GAMEMD 0x6A8160
// Calls other functions.
int __stdcall FUN_006A8160(int a1)
{
    int c0 = FUN_005B40B0(DAT_0083F92C, 0);
    DAT_00B07BC0 = c0;
    return c0;
}

// FUNCTION: GAMEMD 0x6A8180
int __stdcall FUN_006A8180(unsigned int index)
{
    if (index < (unsigned int)SuperWeaponTypeClass_Array.Count) {
        return (int)SuperWeaponTypeClass_Array.Items[index]->SidebarImage;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6A8B10
// Calls other functions.
void FUN_006A8B10(Obj_006A8B10* a1, int a2)
{
    a1->unknown_3C = 1;
    FUN_004F42F0(DAT_0087F7E8, a2, 0);
}

// Slot 31: click handling on a build entry: queues the production / hold / cancel /
// place events, plays the EVA lines and keeps the build timer of the entry current;
// super weapon entries (type 0x1F) arm or fire the weapon.
//
// CAPPED at 2.5% positional (22/879; LCS 483/879 = 54.9%, up from 251 = 28.6%). Retail frame
// is 0x9C, ours 0x90; that one-line difference shifts every later offset, so the positional
// score is low even though the structure now follows retail (879 vs 861 instructions).
// Multiset delta: retail-only mov 8, lea 6, or 3, test 1, push 1, jne 1, jmp 1, jle 1;
// ours-only add, cmp, jge, je. Attempts (five, caps are final):
//  1. first pass with `strip`, `entry`, `player` locals: 5.7%, LCS 28.6%.
//  2. regular arm first: worse, reverted, then re-applied with 4.
//  3. the event-queue append as an inline member `SelectEvent::Queue()` (the form the
//     coordinator suggested): byte-identical output to the free function.
//  4. drop the `strip`/`entry`/`player` locals (retail reloads Owner, the entry offset and
//     the house global each time), `type != 0x1F` regular arm first, `factory != 0` arm
//     first: 4.7%, LCS 55.1%.
//  5. pass the tech type's byte flag At_CCE unconverted (callee parameters are
//     `unsigned char`, matching retail's zero-extended byte push): removes the five `setne`
//     and four `test` (multiset delta now 22 instructions), 2.5% positional, LCS 54.9%.
// Also tried and dropped: one function-scope SelectEvent (frame 0x100, worse) and a named
// constant for the repeated -1 (no change; retail keeps -1 in ECX across the compare and the
// store through `or ecx,-1`). The previous layout (shared locals) scored higher positionally
// (5.7%) only by alignment luck. Open: retail lays the hold arm of the `factory != 0` branch
// after the super-weapon arm, which source order does not reproduce.
// FUNCTION: GAMEMD 0x6AAD00
int SidebarSelectClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (Owner == 0) {
        return 1;
    }
    int index = unknown_30 + Owner->TopRowIndex * 2;
    int item = Owner->Entries[index].Item;
    int type = Owner->Entries[index].Type;
    int category = Owner->Entries[index].Category;
    SelectFactory* factory = Owner->Entries[index].Factory;
    Map_0087F7E8.vf_19(0, 0);
    bool shift = (modifier & 1) != 0;
    if (index < Owner->CameoCount) {
        if (type != 0x1F) {
            SelectTechnoType* technoType = SelectGetByTypeAndIndex(type, item);
            if (technoType != 0) {
                if (flags & 8) {
                    flags &= ~8;
                }
                if (flags & 0x10) {
                    if (factory != 0) {
                        if (PlacementObject_0088098C != 0 && SelectCheckPlacement(PlacementObject_0088098C) != 0) {
                            PlacementObject_0088098C = 0;
                            PlacementType_00880990 = 0;
                            PlacementIndex_00880994 = -1;
                            Map_0087F7E8.SetActiveFoundation_004A8BF0(0);
                        }
                        if (factory->Object == 0 || factory->At_70 != 0) {
                            VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                            SelectVoxPlay("EVA_Canceled", -1, -1);
                            SelectEvent event;
                            if (shift) {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x2E, type, item, technoType->At_CCE)->Queue();
                            } else {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x10, type, item, technoType->At_CCE)->Queue();
                            }
                        } else {
                            VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                            SelectVoxPlay("EVA_OnHold", -1, -1);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xF, type, item, technoType->At_CCE)->Queue();
                            StripRedraw_00880D68[Owner->RowBase * 0xF94] = 1;
                        }
                    } else {
                        if (Owner->Entries[index].State == 1) {
                            Owner->Entries[index].State = 2;
                            Owner->At_3C = 1;
                            Map_0087F7E8.FlagToRedraw(0);
                            VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                            SelectVoxPlay("EVA_OnHold", -1, -1);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xF, type, item, technoType->At_CCE)->Queue();
                        }
                        SelectFactory* primary = SelectPlayer_00A83D4C->GetPrimaryFactory(type, technoType->At_CCE, category);
                        if (primary != 0 && primary->IsQueued(technoType)) {
                            VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                            SelectEvent event;
                            if (shift) {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x2E, type, item, technoType->At_CCE)->Queue();
                            } else {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x10, type, item, technoType->At_CCE)->Queue();
                            }
                        }
                    }
                }
                if (flags & 1) {
                    if (factory != 0 && (factory->Object == 0 || factory->At_70 != 0)) {
                        if (factory->IsDone()) {
                            SelectTechno* object = factory->FUN_004CA160();
                            if (object == 0) {
                                if (factory->GetOriginalBalance() != -1) {
                                    PendingSuper_008809A0 = 1;
                                }
                            } else {
                                VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                                SelectTechno* target = (object->*object->Vtbl->At_190)(0, 0);
                                if (target == 0) {
                                    SelectEvent event;
                                    event.Construct((object->*object->Vtbl->At_38)(), 0x10, type, item, technoType->At_CCE)->Queue();
                                    SelectVoxPlay("EVA_UnableToComply", -1, -1);
                                } else if ((object->*object->Vtbl->At_2C)() == 6) {
                                    SelectPlayer_00A83D4C->FUN_004FB840(target, object);
                                } else {
                                    SelectEvent event;
                                    event.ConstructAt((object->*object->Vtbl->At_38)(), 0xB, type, -1, technoType->At_CCE, &PlacementCell_00B07DD8)->Queue();
                                }
                            }
                        } else {
                            VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                            SelectVoxPlay(type == 0x10 ? "EVA_Training" : "EVA_Building", -1, -1);
                            SelectTechnoType* current = SelectGetByTypeAndIndex(Owner->Entries[index].Type, Owner->Entries[index].Item);
                            bool currentFlag = current != 0 && current->At_CCE != 0;
                            SelectPlayer_00A83D4C->FUN_005005B0(type, technoType->At_CCE, category);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xE, Owner->Entries[index].Type, Owner->Entries[index].Item, currentFlag)->Queue();
                            Owner->Entries[index].State = 1;
                            int progress = 0;
                            if (Owner->Entries[index].Factory != 0) {
                                progress = Owner->Entries[index].Factory->GetProgress();
                            }
                            if (Owner->Entries[index].State == 1 && Owner->Entries[index].Progress > progress) {
                                progress = (progress + Owner->Entries[index].Progress) / 2;
                            }
                            Owner->Entries[index].Progress = progress;
                            int frames = factory->GetBuildTimeFrames() + 1;
                            Owner->Entries[index].TimerStart = CurrentFrame_00A8ED84;
                            Owner->Entries[index].TimerDelay = frames;
                            Owner->Entries[index].Frames = frames;
                            Owner->At_3C = 1;
                            Map_0087F7E8.FlagToRedraw(0);
                            SidebarNeedsRedraw_00884B8F = 1;
                        }
                    } else {
                        SelectFactory* primary = SelectPlayer_00A83D4C->GetPrimaryFactory(type, technoType->At_CCE, category);
                        SelectTechnoType* current = SelectGetByTypeAndIndex(Owner->Entries[index].Type, Owner->Entries[index].Item);
                        bool currentFlag = current != 0 && current->At_CCE != 0;
                        bool canBuild = SelectPlayer_00A83D4C->FUN_0050B370(current);
                        bool progressing = false;
                        bool queued = false;
                        if (primary != 0) {
                            progressing = (primary->Object != 0 && primary->At_70 == 0) == false || primary->At_58 != 0 || primary->At_50 > 0;
                        }
                        if (!progressing && type != 7 && !canBuild) {
                            SelectVoxPlay(type == 0x10 ? "EVA_Training" : "EVA_Building", -1, -1);
                        }
                        if (progressing && type == 7) {
                            SelectVoxPlay("EVA_UnableToComply", -1, -1);
                        } else {
                            bool ready = SelectPlayer_00A83D4C->FUN_00500700(type, technoType->At_CCE, category);
                            if (!canBuild) {
                                VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                                if (primary == 0 && !ready) {
                                    SelectPlayer_00A83D4C->FUN_005005B0(type, technoType->At_CCE, category);
                                    queued = true;
                                }
                                SelectEvent event;
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xE, Owner->Entries[index].Type, Owner->Entries[index].Item, currentFlag)->Queue();
                            }
                            if ((queued || !ready) && !progressing && !canBuild) {
                                Owner->Entries[index].State = 1;
                                Owner->At_3C = 1;
                                Map_0087F7E8.FlagToRedraw(0);
                                SelectTechnoType* target = SelectGetByTypeAndIndex(type, Owner->Entries[index].Item);
                                if (target != 0) {
                                    int cost = (target->*target->Vtbl->At_84)(SelectPlayer_00A83D4C);
                                    int scaled = cost * BuildSpeed_00A8B550 / 54;
                                    if ((SelectPlayer_00A83D4C->Sub24.*SelectPlayer_00A83D4C->Sub24.Vtbl->At_18)() >= scaled) {
                                        if ((target->*target->Vtbl->At_94)(1, 0, 0, SelectPlayer_00A83D4C)) {
                                            int time = (target->*target->Vtbl->At_88)();
                                            if ((target->*target->Vtbl->At_2C)() == 7 && target->At_1571) {
                                                time = (int)(time * SelectRules_008871E0->At_758);
                                            }
                                            int frames = time;
                                            if (frames < 0xF) {
                                                frames = 0xF;
                                            }
                                            int steps = frames / 54;
                                            if (steps * 54 < 0xF) {
                                                ++steps;
                                            }
                                            if (steps < 1) {
                                                steps = 1;
                                            } else if (steps > 0xFF) {
                                                steps = 0xFF;
                                            }
                                            Owner->Entries[index].Progress = 0;
                                            Owner->Entries[index].Frames = steps;
                                            Owner->Entries[index].TimerStart = CurrentFrame_00A8ED84;
                                            Owner->Entries[index].TimerDelay = steps;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (item != -1) {
                if (flags & 8) {
                    flags &= ~8;
                }
                if (flags & 0x10) {
                    PendingSuper_008809A0 = -1;
                }
                if ((flags & 1) && (unsigned int)item < SelectPlayer_00A83D4C->SuperCount) {
                    VocClass::PlayGlobal(SelectRules_008871E0->Sound18C, 1.0f, 0x2000, 0);
                    SelectSuper* super = SelectPlayer_00A83D4C->Supers[item];
                    if (super->CanFire()) {
                        if (super->Type->At_BC == 0) {
                            SelectEvent event;
                            struct { short x; short y; } cell = { 0, 0 };
                            event.ConstructSpecial(SelectPlayer_00A83D4C->ArrayIndex, 0x12, super->Type->At_98, &cell)->Queue();
                        } else {
                            PlacementObject_0088098C = 0;
                            PlacementType_00880990 = 0;
                            PlacementIndex_00880994 = -1;
                            Map_0087F7E8.SetActiveFoundation_004A8BF0(0);
                            Map_0087F7E8.SetRepairMode_004AC8C0(0);
                            Map_0087F7E8.SetSellMode_004AC660(0);
                            PlacementFlagA_0088099A = 0;
                            PlacementFlagB_0088099B = 0;
                            PlacementFlagC_0088099C = 0;
                            PendingSuper_008809A0 = item;
                            SelectUnselectAll();
                            SelectVoxPlay("EVA_SelectTarget", -1, -1);
                        }
                    } else {
                        super->FUN_006CC070();
                    }
                }
            }
        }
    } else {
        flags = 0;
    }
    ControlClass::Action(flags, key, 0);
    return 1;
}

// FUNCTION: GAMEMD 0x6AB990
void SidebarSelectClass::v70()
{
    ToolTipManager_Instance->SaveTimerDelay();
    ToolTipManager_Instance->SetTimerDelay(0);
    Hover = 1;
    Owner->At_3C = 1;
    Map_0087F7E8.FlagToRedraw(0);
    SidebarNeedsRedraw_00884B8F = 1;
    SelectHoverChanged_00B0B518 = 1;
}

// FUNCTION: GAMEMD 0x6AB9E0
void SidebarSelectClass::v74()
{
    ToolTipManager_Instance->RestoreTimeDelay();
    Hover = 0;
    Owner->At_3C = 1;
    Map_0087F7E8.FlagToRedraw(0);
    SidebarNeedsRedraw_00884B8F = 1;
    SelectHoverChanged_00B0B518 = 1;
}

// FUNCTION: GAMEMD 0x6ABA20
// Branching.
int Obj_006ABA20::FUN_006ABA20()
{
    return unknown_34 != 0 && DAT_00A8ED9C == 0;
}

// FUNCTION: GAMEMD 0x6ABA40
int SidebarSBGadgetClass::Action(unsigned flags, unsigned* key, int modifier)
{
    Map_0087F7E8.vf_19(0, 0);
    return 1;
}

// FUNCTION: GAMEMD 0x6ABAC0
// Returns a comparison result.
bool Obj_006ABAC0::FUN_006ABAC0() const
{
    return unknown_54 > 0;
}

// FUNCTION: GAMEMD 0x6ABC40
// Branching.
int __cdecl FUN_006ABC40()
{
    if (Session_00A8B238.GameMode != 0)
    {
        DAT_00A8EDA0 = 8;
    }
    return Session_00A8B238.GameMode;
}

// GLOBAL: GAMEMD 0xB0B468 is declared in the layout header (SideShapes).
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- SidebarMixRetrieve, declared in the layout header too.

// Slot 34: repositions every sidebar gadget for the current layout (including the
// 2-column cameo grid) and re-registers all tooltips.
//
// PARTIAL (98.1%, 318/323, multiset identical). The side-flag placement is two calls
// under if/else (retail pushes `bottom`, then branches to `PUSH 0` or the sum); a ternary
// argument compiled branch-free. Remaining: (1) the vertical extent `Y + Height` loads in
// the other operand order; (2) the row-count subtraction order and the strip top's
// register (retail subtracts the margin before the strip top, in EBX). Variants tried:
// the tooltip store orders (hill-climbed per block), the strip loop as pointer and int
// index, the cameo column increment in the loop header and body, the row count as five
// expression and temporary forms, the side flag as ternary / preset local, the row count reassociated five ways, the margin
// as a ternary (95.7%).
// FUNCTION: GAMEMD 0x6ABD30
void SidebarClass::vf_34()
{
    PowerClass::vf_34();
    FUN_006A5130(0);
    if (SideShapes_00B0B468[0] == 0) {
        SideShapes_00B0B468[0] = SidebarMixRetrieve("SIDEGDI1.SHP", 0);
        SideShapes_00B0B468[1] = SidebarMixRetrieve("SIDEGDI2.SHP", 0);
        SideShapes_00B0B468[2] = SidebarMixRetrieve("SIDEGDI3.SHP", 0);
    }

    ExtraButton_00B07E58.SetPosition(SidebarRect_00886F90.X + 0x10, TacticalRect_00886FA0.Y);
    ExtraButton_00B07E58.MarkRedraw();
    int bottom = ExtraGadget_00B04A10.Y + ExtraGadget_00B04A10.Height;
    if (SidebarSideFlag_00A8EB7C) {
        ExtraButton_00B07E58.SetPosition(TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width, bottom);
    } else {
        ExtraButton_00B07E58.SetPosition(0, bottom);
    }
    ExtraButton_00B07E58.SetDimension(
        (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_7C)(),
        (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_80)() - bottom);

    RepairButton_00B0B3A0.SetPosition(RepairX_00B0B4DC, RepairY_00B0B4E0);
    RepairButton_00B0B3A0.MarkRedraw();
    RepairButton_00B0B3A0.At_44 = -SidebarRect_00886F90.X;
    SellButton_00B07DF8.SetPosition(SellOffset_00B0B4E4 + RepairButton_00B0B3A0.X,
                                    RepairButton_00B0B3A0.Y);
    SellButton_00B07DF8.MarkRedraw();
    SellButton_00B07DF8.At_44 = -SidebarRect_00886F90.X;
    for (int i = 0; i < 4; ++i) {
        TabButtons_00B07C48[i].SetPosition(TabStep_00B0B4F0 * i + TabX_00B0B4E8, TabY_00B0B4EC);
        TabButtons_00B07C48[i].MarkRedraw();
        TabButtons_00B07C48[i].At_44 = -SidebarRect_00886F90.X;
    }
    ScrollDownButton_00B0B328.SetPosition(ScrollX_00B0B508, ScrollY_00B0B50C);
    ScrollDownButton_00B0B328.MarkRedraw();
    ScrollDownButton_00B0B328.At_44 = -SidebarRect_00886F90.X;
    ScrollUpButton_00B0B408.SetPosition(ScrollUpOffset_00B0B510 + ScrollX_00B0B508, ScrollY_00B0B50C);
    ScrollUpButton_00B0B408.MarkRedraw();
    ScrollUpButton_00B0B408.At_44 = -SidebarRect_00886F90.X;

    int margin = 0x1A;
    if (DAT_00A8B230->unknown_34B8) {
        margin = 0x12;
    }
    int rows = (DAT_00886F9C - margin - StripY_00B0B4F8 + DAT_00886F94 - 7) / 50;
    int slots = rows * 2;
    for (int strip = 0; strip < 4; ++strip) {
        SidebarCameoButton* cameo = &CameoButtons_00B07E80[strip * 60];
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < 2; ++column, ++cameo) {
                (cameo->*cameo->Vtbl->At_64)(ColumnStep_00B0B4FC * column + StripX_00B0B4F4,
                                             RowStep_00B0B500 * row + StripY_00B0B4F8 + 1);
                (cameo->*cameo->Vtbl->At_48)();
            }
        }
    }

    if (ToolTipManager_Instance != 0) {
        ToolTip tip;
        tip.field_18 = false;
        for (int i = 0; i < 4; ++i) {
            tip.Bounds.X = TabButtons_00B07C48[i].X;
            tip.Bounds.Y = TabButtons_00B07C48[i].Y;
            tip.GadgetID = 0xCB + i;
            tip.Text = 0;
            tip.Bounds.Width = TabButtons_00B07C48[i].Width;
            tip.Bounds.Height = TabButtons_00B07C48[i].Height;
            ToolTipManager_Instance->Remove(tip.GadgetID);
            ToolTipManager_Instance->Add(tip);
        }
        for (int j = 0; j < 60; ++j) {
            ToolTipManager_Instance->Remove(0x3E8 + j);
        }
        for (int k = 0; k < slots; ++k) {
            tip.GadgetID = 0x3E8 + k;
            tip.Bounds.X = CameoButtons_00B07E80[k].X;
            tip.Bounds.Y = CameoButtons_00B07E80[k].Y;
            tip.Bounds.Width = CameoButtons_00B07E80[k].Width;
            tip.Text = 0;
            tip.Bounds.Height = CameoButtons_00B07E80[k].Height;
            tip.field_18 = true;
            ToolTipManager_Instance->Add(tip);
        }
        tip.Bounds.X = SellButton_00B07DF8.X;
        tip.field_18 = false;
        tip.GadgetID = 0x66;
        tip.Text = "TXT_SELL_MODE";
        tip.Bounds.Y = SellButton_00B07DF8.Y;
        tip.Bounds.Width = SellButton_00B07DF8.Width;
        tip.Bounds.Height = SellButton_00B07DF8.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = RepairButton_00B0B3A0.X;
        tip.GadgetID = 0x65;
        tip.Text = "TXT_REPAIR_MODE";
        tip.Bounds.Y = RepairButton_00B0B3A0.Y;
        tip.Bounds.Width = RepairButton_00B0B3A0.Width;
        tip.Bounds.Height = RepairButton_00B0B3A0.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = ScrollUpButton_00B0B408.X;
        tip.GadgetID = 0xC8;
        tip.Text = 0;
        tip.Bounds.Y = ScrollUpButton_00B0B408.Y;
        tip.Bounds.Width = ScrollUpButton_00B0B408.Width;
        tip.Bounds.Height = ScrollUpButton_00B0B408.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = ScrollDownButton_00B0B328.X;
        tip.GadgetID = 0xC9;
        tip.Text = 0;
        tip.Bounds.Y = ScrollDownButton_00B0B328.Y;
        tip.Bounds.Width = ScrollDownButton_00B0B328.Width;
        tip.Bounds.Height = ScrollDownButton_00B0B328.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
    }
}

// FUNCTION: GAMEMD 0x6AC210
const wchar_t* SidebarClass::vf_33(int id)
{
    const wchar_t* text = PowerClass::vf_33(id);
    if (text != 0) {
        return text;
    }
    if (id == 0xC8) {
        text = SidebarLoadString("Tip:ScrollUp", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13CD);
        return DisabledTip(&ScrollUpButton_00B0B408, text);
    }
    if (id == 0xC9) {
        text = SidebarLoadString("Tip:ScrollDown", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13D3);
        return DisabledTip(&ScrollDownButton_00B0B328, text);
    }
    if (id >= 0xCB && id < 0xCF) {
        int tab = id - 0xCB;
        if (tab == 0) {
            text = SidebarLoadString("Tip:Tab1", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DB);
        } else if (tab == 1) {
            text = SidebarLoadString("Tip:Tab2", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DD);
        } else if (tab == 2) {
            text = SidebarLoadString("Tip:Tab3", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DF);
        } else if (tab == 3) {
            text = SidebarLoadString("Tip:Tab4", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13E1);
        }
        return DisabledTip(&TabButtons_00B07C48[tab], text);
    }
    int margin = 0x1A;
    if (DAT_00A8B230->unknown_34B8) {
        margin = 0x12;
    }
    if (id >= 1000) {
        int rows = (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50;
        if (id < 1000 + rows * 2) {
            return Strips[unknown_539C].FUN_006A92E0(id - 1000);
        }
    }
    return text;
}

// FUNCTION: GAMEMD 0x6AC3E0
int __cdecl FUN_006AC3E0()
{
    return SidebarRowCount();
}

// FUNCTION: GAMEMD 0x6AC430
int __cdecl FUN_006AC430()
{
    return SidebarRowCount() * 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6AC5D0
void Sidebar_006D1800::FUN_006AC5D0(void* arg)
{
    FUN_006568A0(arg);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6AC5E0
void Sidebar_006D1800::FUN_006AC5E0(void* arg)
{
    FUN_00656AC0(arg);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6AC780
void* Obj_6AC780::FUN_6AC780(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6AC7A0
void* Obj_6AC7A0::FUN_6AC7A0(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// REA Evidence: ev_5aa6e42dac161c3cab96320d4b05f5004758d3f4436f42d8ed931b3b6df535fc
// CFG-closed retail span [0x6AC7C0, 0x6AC7E1), 0x21 bytes; 10 instructions, RET at 0x6AC7E0.
// Writes +0x14=0, +0x18 low byte=0, +0x1C=CurrentFrame, +0x24=0, +0x28=0, +0x2C=1;
// bytes +0x00..+0x13 and +0x20..+0x23 are untouched.
// FUNCTION: GAMEMD 0x6AC7C0
SidebarCameo::SidebarCameo()
{
    unknown_14 = 0;
    unknown_18.Bytes.Low = 0;
    unknown_1C = CurrentFrame_00A8ED84;
    unknown_24 = 0;
    unknown_28 = 0;
    unknown_2C = 1;
}

// SYNTHETIC: GAMEMD 0x6AC7F0
// The compiler-emitted scalar deleting destructor follows the ordinary constructor
// in this original translation unit; its bytes are checked against retail.

// FUNCTION: GAMEMD 0x6AC840
DisplayClass::DisplayClass(const Obj_005BDF70& noInit)
    : MapClass(noInit)
{
    SavedColor.R = 0;
    SavedColor.G = 0;
    SavedColor.B = 0;
}

// FUNCTION: GAMEMD 0x6AC870
SidebarCameo* __fastcall FUN_006AC870(SidebarCameo* cameo)
{
    cameo->unknown_00 = 0;
    cameo->unknown_04.Bytes[0] = 0;
    cameo->unknown_08 = CurrentFrame_00A8ED84;
    cameo->unknown_10 = 0;
    cameo->unknown_14 = 0;
    cameo->unknown_18.Word = 1;
    return cameo;
}

// The capacity constructor of a growable vector over an 8-byte plain element
// (no element constructor, so the allocation has no counter header); the
// explicit instantiation also emits the other members, which are not claimed.
struct Elem_006AC8D0 { int unknown_00; int unknown_04; Elem_006AC8D0() {} bool operator==(const Elem_006AC8D0& o) const { return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04; } bool operator!=(const Elem_006AC8D0& o) const { return !(*this == o); } };

// FUNCTION: GAMEMD 0x006AC8D0
// DynamicVectorClass<Elem_006AC8D0>::DynamicVectorClass
template class DynamicVectorClass<Elem_006AC8D0>;
