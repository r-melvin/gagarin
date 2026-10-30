// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The WorldDominationTour::Map block of retail .text (0x767CD0..0x769C4F):
// three of the unit's run-time initialisers, the MSFrameAnim slots, and the
// Map factory and members, in retail address order. Class names are the
// retail RTTI names: ".?AVMSFrameAnim@@" (vtable 0x7F7104, base MSAnim),
// ".?AVMap@WorldDominationTour@@" (0x7F7134, base ReferenceCounted) and
// ".?AV?$rc_ptr@VMap@WorldDominationTour@@@@" (0x7F712C).

#include "../FUNCTION.H"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB728B0
extern double DAT_00B728B0;
// GLOBAL: GAMEMD 0x7F70F0
const double DAT_007F70F0 = 60.0;

// GLOBAL: GAMEMD 0xB72900
extern double DAT_00B72900;
// GLOBAL: GAMEMD 0xB728E8
extern double DAT_00B728E8;
// GLOBAL: GAMEMD 0xB728F0
extern TuningCoordInit DAT_00B728F0;

// ---- surfaces --------------------------------------------------------------------------------------------------------



// GLOBAL: GAMEMD 0x8487BC
extern bool DAT_008487BC;
// GLOBAL: GAMEMD 0x8487BD
extern bool DAT_008487BD;

// FUNCTION: GAMEMD 0x72E450 (decl; reloc) -- __fastcall, (surface, rectangle, 1).
void FUN_0072E450(MouseSurfaceView* surface, RectangleStruct* area, int flag);

// ---- MSFrameAnim -----------------------------------------------------------------------------------------------------

// MSFrameAnim is the canonical class in match/_layout/ms_anim.h (its constructor and scalar deleting
// destructor are in ms_frame_anim_ctor.cpp); slots 4..6 are its own (0x767ED0, 0x767EF0, 0x767F80) and
// slots 1..3, 7 and 8 are MSAnim's.

// FUNCTION: GAMEMD 0x767ED0
bool MSFrameAnim::Update(MouseSurfaceView* context, RectangleStruct* out)
{
    if (DAT_008487BC)
        FUN_0072E450(context, out, 1);
    return false;
}

// FUNCTION: GAMEMD 0x767EF0
// The context is the destination surface (its slots 31 and 32 answer the
// extents); with no area the whole surface is used.
void MSFrameAnim::Draw(MouseSurfaceView* context, RectangleStruct* area)
{
    if (DAT_008487BD) {
        WDTSurface* surface = (WDTSurface*)context;
        int width = surface->vf_31();
        int height = surface->vf_32();
        if (area != 0) {
            RectangleStruct rect = *area;
            FUN_0072E450(context, &rect, 1);
        } else {
            RectangleStruct whole;
            whole.X = 0;
            whole.Y = 0;
            whole.Width = width;
            whole.Height = height;
            FUN_0072E450(context, &whole, 1);
        }
    }
}

// FUNCTION: GAMEMD 0x767F80
RectangleStruct MSFrameAnim::GetRect()
{
    RectangleStruct rect;
    rect.X = 0;
    rect.Y = 0;
    rect.Width = 640;
    rect.Height = 480;
    return rect;
}

// ---- WorldDominationTour::Map ----------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x889F64 -- the shared empty string.
extern const char DAT_00889F64[];



// FUNCTION: GAMEMD 0x5CB590 (decl; reloc) -- __fastcall, loads the named palette.
WDTPalette* FUN_005CB590(const Wstring& name);

// GLOBAL: GAMEMD 0x887308
extern WDTScreenSurface* DAT_00887308;
// GLOBAL: GAMEMD 0x88730C
extern WDTScreenSurface* DAT_0088730C;
// GLOBAL: GAMEMD 0x887310
extern WDTScreenSurface* DAT_00887310;


using WorldDominationTour::Map;

// FUNCTION: GAMEMD 0x767FB0
// The Map factory (hidden result pointer in ECX, the first argument in EDX).
rc_ptr<Map> FUN_00767FB0(int a, int b, int c)
{
    return rc_ptr<Map>(new Map(a, b, c));
}

// FUNCTION: GAMEMD 0x768000
// PARTIAL (11.8%). Retail calls the out-of-line VectorClass capacity
// constructor 0x76A7E0 for the territory list (`PUSH 0; PUSH 0; CALL`); cl
// inlines it and folds the zero capacity away under both /Ob1 and /Ob2, and
// the store schedule shifts after it. Member order and initialiser values are
// as retail.
Map::Map(int a, int b, int c)
    : unknown_08(a), unknown_0C(b), unknown_10(c),
      unknown_14(0), unknown_18(0), unknown_1C(0), unknown_20(0), unknown_24(0),
      Name(DAT_00889F64),
      unknown_44(0), unknown_48(0),
      unknown_64(0), unknown_68(false), unknown_6C(0), unknown_70(0), unknown_74(false), unknown_78(0)
{
}

// FUNCTION: GAMEMD 0x7680C0
// Native member teardown follows palette/surface releases. The existing
// canonical vector destructors already preserve the complete native body.
Map::~Map()
{
    delete unknown_24;
    delete unknown_14;
    for (int i = 0; i < Palettes.Count; i++) {
        delete Palettes.Items[i];
    }
    DAT_00887310->vf_6(0);
    DAT_0088730C->vf_6(0);
    DAT_00887308->vf_1(DAT_0088730C, 0, 1);
    delete unknown_78;
}

// FUNCTION: GAMEMD 0x7691E0
// The palette registered under `name`, loaded and registered on first use.
WDTPalette* Map::FUN_007691E0(const Wstring& name)
{
    for (int i = 0; i < Palettes.Count; i++) {
        if (Palettes.Items[i]->Name == name)
            return Palettes.Items[i]->Palette;
    }
    WDTPalette* palette = FUN_005CB590(name);
    if (palette != 0) {
        Palettes.AddItem(new AnimationPalette(name, palette));
    }
    return palette;
}

// FUNCTION: GAMEMD 0x7692B0
Map::AnimationPalette::AnimationPalette(const Wstring& name, WDTPalette* palette)
    : Name(name), Palette(palette)
{
}

// FUNCTION: GAMEMD 0x7692D0
Map::AnimationPalette::~AnimationPalette()
{
    delete Palette;
}

// FUNCTION: GAMEMD 0x7692F0
void Map::FUN_007692F0(WDTMapView* view, WDTMapArg* arg)
{
    if (unknown_18 != 0) {
        arg->FUN_007714B0(0, 1, 0);
        view->FUN_005D1DF0(unknown_18, 300000);
    }
    if (unknown_1C != 0)
        unknown_1C->vf_1(1);
}

// FUNCTION: GAMEMD 0x769330
// The surface's answer at a map-relative point, or -1 outside its extents.
// PARTIAL (79.5%; mnemonic multiset identical). Retail loads the surface's
// table into EAX for slot 31 and EDX for slots 32 and 10; cl swaps them at all
// three calls. Tried: the early-return form, unsigned extents, and an
// aggregate-initialised local -- all 79.5%.
int Map::FUN_00769330(const WDTPoint* point)
{
    WDTPoint local;
    local.X = point->X - unknown_44;
    local.Y = point->Y - unknown_48;
    if (local.X >= 0 && local.X < unknown_24->vf_31() && local.Y >= 0 && local.Y < unknown_24->vf_32())
        return unknown_24->vf_10(&local);
    return -1;
}

// FUNCTION: GAMEMD 0x7693A0
void Map::FUN_007693A0(WDTMapView* view, bool on)
{
    if (unknown_74 != on) {
        unknown_74 = on;
        unknown_64->FUN_005CC6A0((on && unknown_68) ? unknown_70 : unknown_6C);
        view->FUN_005D26C0(&unknown_54);
        view->FUN_005D1E50();
    }
}

// FUNCTION: GAMEMD 0x7693F0
void Map::FUN_007693F0(WDTMapView* view, bool on)
{
    if (unknown_68 != on) {
        unknown_68 = on;
        unknown_64->FUN_005CC6A0((unknown_74 && on) ? unknown_70 : unknown_6C);
        view->FUN_005D26C0(&unknown_54);
        view->FUN_005D1E50();
    }
}

// FUNCTION: GAMEMD 0x769440
int Map::FUN_00769440(const WDTPoint* point)
{
    if (point->X >= unknown_54.X && point->X < unknown_54.X + unknown_54.Width
        && point->Y >= unknown_54.Y && point->Y < unknown_54.Y + unknown_54.Height)
        return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x769540
// Clamp: values above 29 become 255.
int FUN_00769540(unsigned int value)
{
    if (value > 0x1D)
        value = 0xFF;
    return value;
}

// SYNTHETIC: GAMEMD 0x769D90 -- rc_ptr<Map>::`scalar deleting destructor' (compiler-emitted for the
// rc_ptr<Map> this TU instantiates)
// SYNTHETIC: GAMEMD 0x769C00
// Map scalar deleting destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8487BC
bool DAT_008487BC = true;
// GLOBAL: GAMEMD 0x8487BD
bool DAT_008487BD = true;
// GLOBAL: GAMEMD 0x887310
WDTScreenSurface* DAT_00887310;
// END defined globals
