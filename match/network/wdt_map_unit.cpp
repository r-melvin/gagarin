// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The WorldDominationTour::Map block of retail .text (0x767CD0..0x769C4F):
// three of the unit's run-time initialisers, the MSFrameAnim slots, and the
// Map factory and members, in retail address order. Class names are the
// retail RTTI names: ".?AVMSFrameAnim@@" (vtable 0x7F7104, base MSAnim),
// ".?AVMap@WorldDominationTour@@" (0x7F7134, base ReferenceCounted) and
// ".?AV?$rc_ptr@VMap@WorldDominationTour@@@@" (0x7F712C).
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/header_tuning_globals.h"
#include "../core/string_class.h"
#include "../core/vector_class_operations.h"
#include "../map/msanim_family_methods.h"
#include "wdt_rc_ptr.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB728B0
extern double DAT_00B728B0;
// GLOBAL: GAMEMD 0x7F70F0
const double DAT_007F70F0 = 60.0;

// SYNTHETIC: GAMEMD 0x767CD0
// GLOBAL: GAMEMD 0xB72900
extern double DAT_00B72900;
// SYNTHETIC: GAMEMD 0x767CF0
// GLOBAL: GAMEMD 0xB728E8
extern double DAT_00B728E8;
// SYNTHETIC: GAMEMD 0x767E70
// GLOBAL: GAMEMD 0xB728F0
extern TuningCoordInit DAT_00B728F0;

// ---- surfaces --------------------------------------------------------------------------------------------------------

// The drawing surface as this unit reaches it: slot 10 (+0x28) takes a point
// and answers an int (0x769386), slots 31 and 32 (+0x7C, +0x80) answer the
// two extents (0x767F06/0x767F0F, 0x76935A/0x769370).
class WDTSurface
{
public:
    virtual ~WDTSurface();  // slot 0: freed through it by the map's destructor (0x7680D7)
    virtual void vf_1();  virtual void vf_2();  virtual void vf_3();
    virtual void vf_4();  virtual void vf_5();  virtual void vf_6();  virtual void vf_7();
    virtual void vf_8();  virtual void vf_9();
    virtual int  vf_10(const struct WDTPoint* point);
    virtual void vf_11(); virtual void vf_12(); virtual void vf_13(); virtual void vf_14();
    virtual void vf_15(); virtual void vf_16(); virtual void vf_17(); virtual void vf_18();
    virtual void vf_19(); virtual void vf_20(); virtual void vf_21(); virtual void vf_22();
    virtual void vf_23(); virtual void vf_24(); virtual void vf_25(); virtual void vf_26();
    virtual void vf_27(); virtual void vf_28(); virtual void vf_29(); virtual void vf_30();
    virtual int  vf_31();
    virtual int  vf_32();
};

struct WDTPoint
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(WDTPoint) == 8);

// GLOBAL: GAMEMD 0x8487BC
extern bool DAT_008487BC;
// GLOBAL: GAMEMD 0x8487BD
extern bool DAT_008487BD;

// FUNCTION: GAMEMD 0x72E450 (decl; reloc) -- __fastcall, (surface, rectangle, 1).
void FUN_0072E450(int surface, MSRect* area, int flag);

// ---- MSFrameAnim -----------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7F7104
// Slots 4..6 are its own (0x767ED0, 0x767EF0, 0x767F80); slots 1..3, 7 and 8
// are MSAnim's.
class MSFrameAnim : public MSAnim
{
public:
    virtual bool   Update(int context, MSRect* out);   // slot 4
    virtual void   Draw(int context, MSRect* area);    // slot 5
    virtual MSRect GetRect();                          // slot 6
};

// FUNCTION: GAMEMD 0x767ED0
bool MSFrameAnim::Update(int context, MSRect* out)
{
    if (DAT_008487BC)
        FUN_0072E450(context, out, 1);
    return false;
}

// FUNCTION: GAMEMD 0x767EF0
// The context is the destination surface (its slots 31 and 32 answer the
// extents); with no area the whole surface is used.
void MSFrameAnim::Draw(int context, MSRect* area)
{
    if (DAT_008487BD) {
        WDTSurface* surface = (WDTSurface*)context;
        int width = surface->vf_31();
        int height = surface->vf_32();
        if (area != 0) {
            MSRect rect = *area;
            FUN_0072E450(context, &rect, 1);
        } else {
            MSRect whole;
            whole.X = 0;
            whole.Y = 0;
            whole.Width = width;
            whole.Height = height;
            FUN_0072E450(context, &whole, 1);
        }
    }
}

// FUNCTION: GAMEMD 0x767F80
MSRect MSFrameAnim::GetRect()
{
    MSRect rect;
    rect.X = 0;
    rect.Y = 0;
    rect.Width = 640;
    rect.Height = 480;
    return rect;
}

// ---- WorldDominationTour::Map ----------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x889F64 -- the shared empty string.
extern const char DAT_00889F64[];

// Both owning name members use the native four-byte Wstring. The Map name
// is destroyed after its vectors (native call7B46F0 at7681C5).
// Polymorphic members the map owns: each is freed through slot 0 with 1
// (`PUSH 1; CALL [EAX]`, 0x7680D5/0x7680E2/0x768161 and 0x7692DC).
class WDTOwned
{
public:
    virtual ~WDTOwned();
};

// The member at +0x1C: slot 1 is reached with one argument (0x769327).
class WDTMember_1C
{
public:
    virtual void vf_0();
    virtual void vf_1(int arg);
};

// The object 0x7692F0 and the two show/hide setters drive (their first argument).
class WDTMapView
{
public:
    // FUNCTION: GAMEMD 0x5D1DF0 (decl; reloc)
    void FUN_005D1DF0(void* item, int time);
    // FUNCTION: GAMEMD 0x5D1E50 (decl; reloc)
    void FUN_005D1E50();
    // FUNCTION: GAMEMD 0x5D26C0 (decl; reloc)
    void FUN_005D26C0(const struct WDTRect* area);
};

// The second argument of 0x7692F0.
class WDTMapArg
{
public:
    // FUNCTION: GAMEMD 0x7714B0 (decl; reloc)
    void FUN_007714B0(int a, int b, int c);
};

// The member at +0x64.
class WDTMember_64
{
public:
    // FUNCTION: GAMEMD 0x5CC6A0 (decl; reloc)
    void FUN_005CC6A0(int value);
};

struct WDTRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(WDTRect) == 0x10);

// The palette object an AnimationPalette holds (freed through slot 0).
class WDTPalette : public WDTOwned
{
};

// FUNCTION: GAMEMD 0x5CB590 (decl; reloc) -- __fastcall, loads the named palette.
WDTPalette* FUN_005CB590(const Wstring& name);

// Screen surfaces released by the map's destructor.
class WDTScreenSurface
{
public:
    virtual void vf_0();
    virtual void vf_1(WDTScreenSurface* other, int a, int b);
    virtual void vf_2();  virtual void vf_3();  virtual void vf_4();  virtual void vf_5();
    virtual void vf_6(int arg);
};
// GLOBAL: GAMEMD 0x887308
extern WDTScreenSurface* DAT_00887308;
// GLOBAL: GAMEMD 0x88730C
extern WDTScreenSurface* DAT_0088730C;
// GLOBAL: GAMEMD 0x887310
extern WDTScreenSurface* DAT_00887310;

namespace WorldDominationTour {

class Territory;

// VTABLE: GAMEMD 0x7F7134
// Size 0xD4: the factory 0x767FB0 allocates 0xD4 bytes. Slot 0 is the
// deleting destructor 0x769C00; slots 1 and 2 are ReferenceCounted's.
class Map : public ReferenceCounted
{
public:
    // Named by the retail RTTI of its vector, "PAUAnimationPalette@Map@WorldDominationTour".
    struct AnimationPalette
    {
        AnimationPalette(const Wstring& name, WDTPalette* palette);
        ~AnimationPalette();

        Wstring Name;      // +0x00
        WDTPalette* Palette;   // +0x04
    };

    Map(int a, int b, int c);
    virtual ~Map();

    WDTPalette* FUN_007691E0(const Wstring& name);
    void FUN_007692F0(WDTMapView* view, WDTMapArg* arg);
    int FUN_00769330(const WDTPoint* point);
    void FUN_007693A0(WDTMapView* view, bool on);
    void FUN_007693F0(WDTMapView* view, bool on);
    int FUN_00769440(const WDTPoint* point);

    int unknown_08;                                    // +0x08
    int unknown_0C;                                    // +0x0C
    int unknown_10;                                    // +0x10
    WDTOwned* unknown_14;                              // +0x14
    void* unknown_18;                                  // +0x18
    WDTMember_1C* unknown_1C;                          // +0x1C
    int unknown_20;                                    // +0x20
    WDTSurface* unknown_24;                            // +0x24
    Wstring Name;                                    // +0x28
    DynamicVectorClass<rc_ptr<Territory> > Territories;  // +0x2C
    int unknown_44;                                    // +0x44
    int unknown_48;                                    // +0x48
    int unknown_4C;                                    // +0x4C
    int unknown_50;                                    // +0x50
    WDTRect unknown_54;                                // +0x54
    WDTMember_64* unknown_64;                          // +0x64
    bool unknown_68;                                   // +0x68
    int unknown_6C;                                    // +0x6C
    int unknown_70;                                    // +0x70
    bool unknown_74;                                   // +0x74
    WDTOwned* unknown_78;                              // +0x78
    char unknown_7C[0xBC - 0x7C];                      // +0x7C
    DynamicVectorClass<AnimationPalette*> Palettes;    // +0xBC
};
GG_STATIC_ASSERT(offsetof(Map, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Map, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Map, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Map, Name) == 0x28);
GG_STATIC_ASSERT(offsetof(Map, Territories) == 0x2C);
GG_STATIC_ASSERT(offsetof(Map, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(Map, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Map, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(Map, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Map, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(Map, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(Map, Palettes) == 0xBC);
GG_STATIC_ASSERT(sizeof(Map) == 0xD4);
GG_STATIC_ASSERT(offsetof(Map::AnimationPalette, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(Map::AnimationPalette, Palette) == 0x04);
GG_STATIC_ASSERT(sizeof(Map::AnimationPalette) == 0x08);

}  // namespace WorldDominationTour

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
