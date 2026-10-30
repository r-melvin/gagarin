// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WorldDominationTour::Map (RTTI ".?AVMap@WorldDominationTour@@", vtable 0x7F7134, base ReferenceCounted) and
//   the helper views its members point at, lifted out of wdt_map_unit.cpp so the screen unit WDTSel.cpp reads
//   the same definition.
#ifndef GG_MATCH_NETWORK_WDT_MAP_H
#define GG_MATCH_NETWORK_WDT_MAP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/string_class.h"
#include "../core/vector_class.h"
#include "wdt_rc_ptr.h"
#include "../_layout/geometry2d.h"

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

// Screen surfaces released by the map's destructor.
class WDTScreenSurface
{
public:
    virtual void vf_0();
    virtual void vf_1(WDTScreenSurface* other, int a, int b);
    virtual void vf_2(const RectangleStruct* destination, WDTScreenSurface* source, const RectangleStruct* area, int a, int b);
    virtual void vf_3();  virtual void vf_4();  virtual void vf_5();
    virtual void vf_6(int arg);
};

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
    RectangleStruct unknown_7C;                        // +0x7C
    RectangleStruct unknown_8C;                        // +0x8C
    RectangleStruct unknown_9C;                        // +0x9C
    RectangleStruct unknown_AC;                        // +0xAC
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
GG_STATIC_ASSERT(offsetof(Map, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Map, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Map, Palettes) == 0xBC);
GG_STATIC_ASSERT(sizeof(Map) == 0xD4);
GG_STATIC_ASSERT(offsetof(Map::AnimationPalette, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(Map::AnimationPalette, Palette) == 0x04);
GG_STATIC_ASSERT(sizeof(Map::AnimationPalette) == 0x08);

}  // namespace WorldDominationTour

#endif
