// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Sidebar-cluster layout views, address-scoped: every member below is
//   touched by an instruction of one of the entries in this module and is
//   pinned by an offsetof assert; everything else is modeled as padding.
//   Evidence read from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI. RTTI: SidebarClass (COL 0x8095B8, vtable 0x7F3058) derives
//   PowerClass -> RadarClass -> DisplayClass -> MapClass -> GScreenClass
//   (+ IGameMap, IUnknown); TabClass (COL 0x805EA0, vtable 0x7EDFB4, with the
//   INoticeSink subobject at +0x5518, vtable 0x7EDFAC) derives SidebarClass.
//
//   The class chain itself (PowerClass, SidebarClass, StripClass, TabClass)
//   is declared once in ui_display_chain.h; this header keeps the sidebar's
//   foreign objects, globals and button views.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CLASS_LAYOUT_H
#define GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CLASS_LAYOUT_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_display_chain.h"
#include "../tooltip_manager_shared.h"

// ---------------------------------------------------------------------------
// Shared call views
// ---------------------------------------------------------------------------

// A loaded .SHP file as returned by FileSystem::LoadWholeFileEx and
// MixFileClass::Retrieve; freed with operator delete.
struct SidebarShapeFile
{
    short unknown_00;
    short Width;                                // +0x02 (read by 0x6D02B0)
    short Height;                               // +0x04 (read by 0x6D02B0)
    short Frames;                               // +0x06
};
GG_STATIC_ASSERT(offsetof(SidebarShapeFile, Width) == 0x02);
GG_STATIC_ASSERT(offsetof(SidebarShapeFile, Height) == 0x04);
GG_STATIC_ASSERT(offsetof(SidebarShapeFile, Frames) == 0x06);

// FUNCTION: GAMEMD 0x4A38D0 (decl; reloc) -- FileSystem::LoadWholeFileEx,
// __fastcall(name, out owned).
SidebarShapeFile* __fastcall SidebarLoadWholeFileEx(const char* name, bool* owned);
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- MixFileClass::Retrieve,
// __fastcall(name, flag byte in DL).
SidebarShapeFile* __fastcall SidebarMixRetrieve(const char* name, unsigned char flag);

// A 256-entry RGB palette (0x300 bytes), copied by value with REP MOVSD.
struct SidebarPalette
{
    unsigned char Entries[0x300];
};
GG_STATIC_ASSERT(sizeof(SidebarPalette) == 0x300);

// FUNCTION: GAMEMD 0x72F4A0 (decl; reloc) -- returns the first palette.
SidebarPalette* __fastcall SidebarGetPalette1();
// FUNCTION: GAMEMD 0x72F4E0 (decl; reloc) -- returns the second palette.
SidebarPalette* __fastcall SidebarGetPalette2();

// ConvertClass: allocated with `PUSH 0x188; CALL 0x7C8E17` at 0x6A587B and
// 0x6A5A73, constructed by 0x48E740 (RET 0x14), destroyed through slot 0
// (PUSH 1; CALL [EAX]).
struct SidebarConvert
{
    // FUNCTION: GAMEMD 0x48E740 (decl; reloc) -- ConvertClass constructor.
    SidebarConvert(const SidebarPalette& a, const SidebarPalette& b, void* surface,
                   int c, int d);
    virtual ~SidebarConvert();
    char _data[0x188 - 4];
};
GG_STATIC_ASSERT(sizeof(SidebarConvert) == 0x188);

// GLOBAL: GAMEMD 0x87F6CC -- the first sidebar ConvertClass object.
extern SidebarConvert* ConvertA_0087F6CC;

// A RectangleStruct built in one expression: the strip setup assigns StripClass::Rect from such a temporary, which is
// what reproduces retail's store order (0x6A5310).
struct Obj_006A5310 : public RectangleStruct
{
    Obj_006A5310(int x, int y, int w, int h) { X = x; Y = y; Width = w; Height = h; }
};
GG_STATIC_ASSERT(sizeof(Obj_006A5310) == 0x10);

// One 0x60-byte ShapeButtonClass object (the sidebar's static buttons: repair,
// sell, scroll up/down and the four tabs). sizeof pinned by the 0x60 stride of
// the tab records at 0xB07C48 (loop 0x6A541C) and of the button array at
// 0xB0C1C0 (0x6D1770). Only fields the entries of this module touch are named.
struct SidebarButton : public DisplayGadget
{
    char _pad004[0x0C - 4];                     // +0x04
    int X;                                      // +0x0C
    int Y;                                      // +0x10
    int Width;                                  // +0x14
    int Height;                                 // +0x18
    char _pad01C[0x1D - 0x1C];                  // +0x1C
    unsigned char At_1D;                        // +0x1D
    char _pad01E[0x20 - 0x1E];                  // +0x1E
    int At_20;                                  // +0x20
    int ID;                                     // +0x24
    char _pad028[0x2C - 0x28];                  // +0x28
    unsigned char At_2C;                        // +0x2C
    unsigned char IsOn;                         // +0x2D
    char _pad02E[0x30 - 0x2E];                  // +0x2E
    int At_30;                                  // +0x30
    char _pad034[0x40 - 0x34];                  // +0x34
    unsigned char At_40;                        // +0x40
    char _pad041[0x44 - 0x41];                  // +0x41
    int At_44;                                  // +0x44
    int At_48;                                  // +0x48
    unsigned char At_4C;                        // +0x4C
    char _pad04D[0x50 - 0x4D];                  // +0x4D
    void* At_50;                                // +0x50
    bool At_54;                                 // +0x54 (set when the button must be redrawn)
    char _pad055[0x58 - 0x55];                  // +0x55
    void* ShapeData;                            // +0x58
    char _pad05C[0x60 - 0x5C];                  // +0x5C

    // FUNCTION: GAMEMD 0x4E1450 (decl; reloc) -- GadgetClass::Enable.
    void Enable();
    // FUNCTION: GAMEMD 0x4E1470 (decl; reloc) -- GadgetClass::IsEnabled.
    bool IsEnabled() const;
    // FUNCTION: GAMEMD 0x5565F0 (decl; reloc) -- LinkClass::Zap.
    void Zap();
    // FUNCTION: GAMEMD 0x723EA0 (decl; reloc) -- ToggleClass::TurnOn.
    void TurnOn();
    // FUNCTION: GAMEMD 0x723EB0 (decl; reloc) -- ToggleClass::TurnOff.
    void TurnOff();
    // FUNCTION: GAMEMD 0x4E1460 (decl; reloc) -- GadgetClass::Disable.
    void Disable();
    // FUNCTION: GAMEMD 0x4E1A20 (decl; reloc) -- GadgetClass::SetPosition(x, y); RET 8.
    void SetPosition(int x, int y);
    // FUNCTION: GAMEMD 0x4E1A40 (decl; reloc) -- GadgetClass::SetDimension(w, h); RET 8.
    void SetDimension(int w, int h);
    // FUNCTION: GAMEMD 0x4E1960 (decl; reloc) -- GadgetClass::MarkRedraw.
    void MarkRedraw();
    // FUNCTION: GAMEMD 0x69DE00 (decl; reloc) -- set the shape; RET 0xC.
    void FUN_0069DE00(SidebarShapeFile* shape, int a, int b);
    // FUNCTION: GAMEMD 0x69DE70 (decl; reloc) -- ShapeButtonClass::ClearShape.
    void ClearShape();
    // FUNCTION: GAMEMD 0x69DEA0 (decl; reloc) -- ShapeButtonClass::SetLoadedStatus.
    void SetLoadedStatus(bool status);
    // FUNCTION: GAMEMD 0x69DEB0 (decl; reloc) -- ShapeButtonClass::Draw; RET 4.
    int Draw(int forced);
    // FUNCTION: GAMEMD 0x69E010 (decl; reloc) -- ShapeButtonClass::AI.
    bool AI();
    // FUNCTION: GAMEMD 0x69DFF0 (decl; reloc) -- ShapeButtonClass::StopFlashing.
    bool StopFlashing();
};
GG_STATIC_ASSERT(offsetof(SidebarButton, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(SidebarButton, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(SidebarButton, Width) == 0x14);
GG_STATIC_ASSERT(offsetof(SidebarButton, Height) == 0x18);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_1D) == 0x1D);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_20) == 0x20);
GG_STATIC_ASSERT(offsetof(SidebarButton, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(SidebarButton, IsOn) == 0x2D);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_30) == 0x30);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_40) == 0x40);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_44) == 0x44);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_50) == 0x50);
GG_STATIC_ASSERT(offsetof(SidebarButton, At_54) == 0x54);
GG_STATIC_ASSERT(offsetof(SidebarButton, ShapeData) == 0x58);
GG_STATIC_ASSERT(sizeof(SidebarButton) == 0x60);

// One 0x38-byte cameo button (stride pinned by the *7*8 address arithmetic in
// 0x6A7D70 and the +0x38 pointer step in 0x6ABD30). A gadget with a vtable: the
// slots used are +0x48 (MarkRedraw) and +0x64 (SetPosition); the base-class Zap
// is called directly.
struct SidebarCameoVtbl;
struct SidebarCameoButton
{
    SidebarCameoVtbl* Vtbl;                     // +0x00
    int unknown_04;                             // +0x04
    int unknown_08;                             // +0x08
    int X;                                      // +0x0C
    int Y;                                      // +0x10
    int Width;                                  // +0x14
    int Height;                                 // +0x18
    char _pad01C[0x38 - 0x1C];                  // +0x1C
    // FUNCTION: GAMEMD 0x5565F0 (decl; reloc) -- LinkClass::Zap.
    void Zap();
};
typedef void (SidebarCameoButton::*SidebarCameoFn48)();
typedef void (SidebarCameoButton::*SidebarCameoFn64)(int x, int y);
struct SidebarCameoVtbl
{
    char _pad000[0x48];
    SidebarCameoFn48 At_48;                     // +0x48 MarkRedraw
    char _pad04C[0x64 - 0x4C];
    SidebarCameoFn64 At_64;                     // +0x64 SetPosition
};
GG_STATIC_ASSERT(offsetof(SidebarCameoVtbl, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(SidebarCameoVtbl, At_64) == 0x64);
GG_STATIC_ASSERT(offsetof(SidebarCameoButton, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(SidebarCameoButton, Height) == 0x18);
GG_STATIC_ASSERT(sizeof(SidebarCameoButton) == 0x38);

// ---------------------------------------------------------------------------
// House views (observer panel, 0x6A5310)
// ---------------------------------------------------------------------------

// HouseTypeClass (reached through HouseClass +0x34): one byte read.
struct SidebarHouseType
{
    char _pad000[0x1A6];
    unsigned char At_1A6;                       // +0x1A6
};
GG_STATIC_ASSERT(offsetof(SidebarHouseType, At_1A6) == 0x1A6);

// The COM-style sub-object at HouseClass +0x24: its slot at +0x18 is called
// __stdcall with the sub-object pointer pushed on the stack and returns a
// signed value.
struct SidebarHouseSub24Vtbl;
struct SidebarHouseSub24
{
    SidebarHouseSub24Vtbl* Vtbl;
};
typedef int (__stdcall SidebarHouseSub24::*SidebarHouseSub24Fn18)();
struct SidebarHouseSub24Vtbl
{
    char _pad000[0x18];
    SidebarHouseSub24Fn18 At_18;                // +0x18
};
GG_STATIC_ASSERT(offsetof(SidebarHouseSub24Vtbl, At_18) == 0x18);

// A record freed by the observer panel after its fields are copied out.
struct SidebarHouseRecord
{
    char _pad000[0x08];
    int At_08;                                  // +0x08
    int At_0C;                                  // +0x0C
    int At_10;                                  // +0x10
    char _pad014[0x1C - 0x14];
    int At_1C;                                  // +0x1C
    int At_20;                                  // +0x20
    char _pad024[0x30 - 0x24];
    int At_30;                                  // +0x30
};
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_08) == 0x08);
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_10) == 0x10);
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_20) == 0x20);
GG_STATIC_ASSERT(offsetof(SidebarHouseRecord, At_30) == 0x30);

// The data at HouseClass +0x1602A (an odd offset): FUN_0077DA50 returns a
// freshly allocated record.
struct SidebarHouseTail
{
    char _data[1];
    // FUNCTION: GAMEMD 0x77DA50 (decl; reloc)
    SidebarHouseRecord* FUN_0077DA50();
};

struct SelectFactory;
struct SelectTechnoType;
struct SelectTechno;
struct SelectSuper;

// HouseClass: only what the sidebar entries read.
struct SidebarHouse
{
    char _pad000[0x24];
    SidebarHouseSub24 Sub24;                    // +0x0024
    char _pad028[0x30 - 0x28];
    int ArrayIndex;                             // +0x0030
    SidebarHouseType* Type;                     // +0x0034
    char _pad038[0x1EC - 0x38];
    unsigned char At_1EC;                       // +0x01EC
    char _pad1ED[0x1F5 - 0x1ED];
    unsigned char At_1F5;                       // +0x01F5
    char _pad1F6[0x258 - 0x1F6];
    SelectSuper** Supers;                       // +0x0258
    char _pad25C[0x264 - 0x25C];
    unsigned int SuperCount;                    // +0x0264
    char _pad268[0x2E8 - 0x268];
    int At_2E8;                                 // +0x02E8
    char _pad2EC[4];
    int At_2F0;                                 // +0x02F0
    int At_2F4;                                 // +0x02F4
    int At_2F8;                                 // +0x02F8
    char _pad2FC[0x53E4 - 0x2FC];
    int At_53E4[20];                            // +0x53E4
    int At_5434;                                // +0x5434 (gap, unused)
    int At_5438[20];                            // +0x5438
    char _pad5488[0x1602A - 0x5488];
    SidebarHouseTail At_1602A;                  // +0x1602A
    char _pad1602B[0x16054 - 0x1602B];
    int At_16054;                               // +0x16054

    // FUNCTION: GAMEMD 0x500510 (decl; reloc) -- HouseClass::GetPrimaryFactory; RET 0xC.
    SelectFactory* GetPrimaryFactory(int type, unsigned char naval, int category) const;
    // FUNCTION: GAMEMD 0x5005B0 (decl; reloc) -- RET 0xC.
    void FUN_005005B0(int type, unsigned char flag, int category);
    // FUNCTION: GAMEMD 0x500700 (decl; reloc) -- RET 0xC.
    bool FUN_00500700(int type, unsigned char flag, int category);
    // FUNCTION: GAMEMD 0x50B370 (decl; reloc) -- RET 4.
    bool FUN_0050B370(SelectTechnoType* type);
    // FUNCTION: GAMEMD 0x4FB840 (decl; reloc) -- RET 8; called on the player with (target, object).
    void FUN_004FB840(SelectTechno* target, SelectTechno* object);
};
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_1602A) == 0x1602A);
GG_STATIC_ASSERT(offsetof(SidebarHouse, Sub24) == 0x24);
GG_STATIC_ASSERT(offsetof(SidebarHouse, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(SidebarHouse, Type) == 0x34);
GG_STATIC_ASSERT(offsetof(SidebarHouse, Supers) == 0x258);
GG_STATIC_ASSERT(offsetof(SidebarHouse, SuperCount) == 0x264);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_1EC) == 0x1EC);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_1F5) == 0x1F5);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_2E8) == 0x2E8);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_2F0) == 0x2F0);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_2F4) == 0x2F4);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_2F8) == 0x2F8);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_53E4) == 0x53E4);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_5438) == 0x5438);
GG_STATIC_ASSERT(offsetof(SidebarHouse, At_16054) == 0x16054);

// ---------------------------------------------------------------------------
// Sidebar globals and the map singleton
// ---------------------------------------------------------------------------

// StripClass and its 0x34-byte cameo entries are declared in ui_display_chain.h.

// The map singleton is a static object at 0x87F7E8 (Map_0087F7E8, ui_display_chain.h). This second view of it
// remains for the two button-list calls that pass a cameo button, which is not yet typed as a gadget.
struct SidebarMap
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4F4410 (decl; reloc) -- add a button to the list.
    void AddButton(SidebarCameoButton* button);
    // FUNCTION: GAMEMD 0x4F4450 (decl; reloc) -- take a button off the list.
    void FUN_004F4450(SidebarCameoButton* button);
};
// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance.
extern SidebarMap MapInstance_0087F7E8;

// PowerClass and its bases are declared in ui_display_chain.h.

// GLOBAL: GAMEMD 0x887368 -- the tooltip manager singleton (CCToolTip::Instance; CCToolTip is a ToolTipManager).
extern ToolTipManager* ToolTipManager_Instance;
// GLOBAL: GAMEMD 0xA8ED6B -- gates the shroud / sidebar initialisation.
extern unsigned char DAT_00A8ED6B;
// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern SidebarHouse* CurrentPlayer_00A83D4C;
// GLOBAL: GAMEMD 0xAC1198 -- HouseClass::Observer.
extern SidebarHouse* Observer_00AC1198;
// GLOBAL: GAMEMD 0x884CF8 -- observer-mode row limit.
extern int ObserverRowLimit_00884CF8;
// GLOBAL: GAMEMD 0x884B8F -- "sidebar needs a full redraw" byte.
extern unsigned char SidebarNeedsRedraw_00884B8F;
// GLOBAL: GAMEMD 0xB0B518 -- byte set when the sidebar surface was touched.
extern unsigned char SidebarTouched_00B0B518;

// The sidebar's static button objects (all 0x60-byte ShapeButtonClass views).
// GLOBAL: GAMEMD 0xB07DF8 -- the sell button.
extern SidebarButton SellButton_00B07DF8;
// GLOBAL: GAMEMD 0xB0B3A0 -- the repair button.
extern SidebarButton RepairButton_00B0B3A0;
// GLOBAL: GAMEMD 0xB07C48 -- the four tab buttons (stride 0x60).
extern SidebarButton TabButtons_00B07C48[4];
// GLOBAL: GAMEMD 0xB0B328 -- the scroll-down button (R-DN.SHP).
extern SidebarButton ScrollDownButton_00B0B328;
// GLOBAL: GAMEMD 0xB0B408 -- the scroll-up button (R-UP.SHP).
extern SidebarButton ScrollUpButton_00B0B408;

// GLOBAL: GAMEMD 0xB07E58 / 0xB04A10 -- two further gadgets handled with the buttons.
extern SidebarButton ExtraButton_00B07E58;
extern SidebarButton ExtraGadget_00B04A10;
// GLOBAL: GAMEMD 0xB07E80 -- the cameo buttons (0x38 bytes each, 60 per strip).
extern SidebarCameoButton CameoButtons_00B07E80[];

struct SidebarAreaRect
{
    int X;
    int Y;
    int Width;
    int Height;
};

// The sidebar surface (DSurface::Sidebar, GLOBAL 0x887300): slot +0x7C returns
// its width and slot +0x80 its height.
struct SidebarSurfaceVtbl;
struct SidebarSurfaceView
{
    SidebarSurfaceVtbl* Vtbl;
};
typedef int (SidebarSurfaceView::*SidebarSurfaceFn)();
struct SidebarSurfaceVtbl
{
    char _pad000[0x78];
    SidebarAreaRect* (SidebarSurfaceView::*At_78)(SidebarAreaRect* out);  // +0x78 clip rectangle
    SidebarSurfaceFn At_7C;                     // +0x7C width
    SidebarSurfaceFn At_80;                     // +0x80 height
};
GG_STATIC_ASSERT(offsetof(SidebarSurfaceVtbl, At_78) == 0x78);
GG_STATIC_ASSERT(offsetof(SidebarSurfaceVtbl, At_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(SidebarSurfaceVtbl, At_80) == 0x80);
// GLOBAL: GAMEMD 0x887300 -- DSurface::Sidebar.
extern SidebarSurfaceView* SidebarSurface_00887300;
// GLOBAL: GAMEMD 0x887314 -- the current drawing surface.
extern SidebarSurfaceView* CurrentSurface_00887314;

// Sidebar / tactical rectangles and area terms shared by the entries.
// GLOBAL: GAMEMD 0x886F90 -- sidebar rectangle {X, Y, Width, Height}.
extern SidebarAreaRect SidebarRect_00886F90;
// GLOBAL: GAMEMD 0x886FA0 -- tactical view rectangle.
extern SidebarAreaRect TacticalRect_00886FA0;
// GLOBAL: GAMEMD 0x886F9C / 0x886F94 -- sidebar area height and adjustment terms.
extern int DAT_00886F9C;
extern int DAT_00886F94;
// GLOBAL: GAMEMD 0xA8EB7C -- which side the sidebar is on (compared against 1 / non-zero).
extern unsigned char SidebarSideFlag_00A8EB7C;

// ScenarioClass: only the sidebar margin selector at +0x34B8 is read.
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
struct SidebarScenario
{
    char _pad000[0x34B8];
    int At_34B8;                                // +0x34B8
};
GG_STATIC_ASSERT(offsetof(SidebarScenario, At_34B8) == 0x34B8);
extern SidebarScenario* Scenario_00A8B230;

// RulesClass: only the sound ids the sidebar plays are read.
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
struct SidebarRules
{
    char _pad000[0x188];
    int Sound188;                               // +0x188
    int Sound18C;                               // +0x18C
    int Sound190;                               // +0x190
    int Sound194;                               // +0x194
    int Sound198;                               // +0x198
    char _pad19C[0x700 - 0x19C];
    int Sound700;                               // +0x700
    char _pad704[0x758 - 0x704];
    double At_758;                              // +0x758 (build-time scale)
};
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound188) == 0x188);
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound18C) == 0x18C);
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound190) == 0x190);
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound194) == 0x194);
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound198) == 0x198);
GG_STATIC_ASSERT(offsetof(SidebarRules, Sound700) == 0x700);
GG_STATIC_ASSERT(offsetof(SidebarRules, At_758) == 0x758);
extern SidebarRules* Rules_008871E0;
// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- VocClass::PlayGlobal(index, flags, volume, controller).
void* __fastcall SidebarPlayGlobal(int voc, unsigned int flags, float volume, void* controller);

// Sidebar layout metrics (ints at 0xB0B4DC..0xB0B510), read by the setup and
// reposition entries.
// GLOBAL: GAMEMD 0xB0B4DC / 0xB0B4E0 -- repair button X / Y.
extern int RepairX_00B0B4DC;
extern int RepairY_00B0B4E0;
// GLOBAL: GAMEMD 0xB0B4E4 -- sell button X offset from the repair button.
extern int SellOffset_00B0B4E4;
// GLOBAL: GAMEMD 0xB0B4E8 / 0xB0B4EC / 0xB0B4F0 -- first tab X, tab Y, tab X step.
extern int TabX_00B0B4E8;
extern int TabY_00B0B4EC;
extern int TabStep_00B0B4F0;
// GLOBAL: GAMEMD 0xB0B4F4 / 0xB0B4F8 / 0xB0B4FC / 0xB0B500 / 0xB0B504 -- strip X, strip Y,
// cameo column step, cameo row step, strip height.
extern int StripX_00B0B4F4;
extern int StripY_00B0B4F8;
extern int ColumnStep_00B0B4FC;
extern int RowStep_00B0B500;
extern int StripHeight_00B0B504;
// GLOBAL: GAMEMD 0xB0B508 / 0xB0B50C / 0xB0B510 -- scroll button X / Y / up-button X offset.
extern int ScrollX_00B0B508;
extern int ScrollY_00B0B50C;
extern int ScrollUpOffset_00B0B510;

// Loaded sidebar art: pointer arrays and their "owned, must be freed" flag
// arrays (the flag of entry k sits 0x20 bytes after the pointer of entry 0
// for the first set, 0x3C for the second; see 0x6A5840 / 0x6A5BF0).
// GLOBAL: GAMEMD 0xB0B468 / 0xB0B488
extern SidebarShapeFile* SideShapes_00B0B468[8];
extern bool SideShapeOwned_00B0B488[8];
// GLOBAL: GAMEMD 0xB0B490 / 0xB0B4CC
extern SidebarShapeFile* ObsShapes_00B0B490[15];
extern bool ObsShapeOwned_00B0B4CC[15];

// SidebarClass (VTABLE 0x7F3058) is declared in ui_display_chain.h.

// A rectangle {X, Y, Width, Height} read through a global pointer by the tab
// bar setup (0x6D02B0, 0x6D03A0). Copied field by field into a local.
struct SidebarTabRect
{
    int X;
    int Y;
    int Width;
    int Height;
};
GG_STATIC_ASSERT(sizeof(SidebarTabRect) == 0x10);

// TabClass (VTABLE 0x7EDFB4, INoticeSink at +0x5518) is declared in ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CLASS_LAYOUT_H
