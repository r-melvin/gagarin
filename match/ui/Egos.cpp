// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Egos.CPP. The name is the source-file string at 0x8207ec
//   in retail gamemd.exe v1.001, passed by the assert at 0x4c40e4 inside this object's
//   code range (0x4c35a0-0x4c4cff). Functions are in ascending retail address order.
//
// Builds a set of 256-byte colour remap tables from a palette and a list of
// 4-byte entries {index, colour, ratio, -}. The first 256 bytes map each
// entry's index byte to its table number (0xFF elsewhere); table n follows
// at +0x100 * (n + 1) and maps every colour to the palette entry nearest to
// it after blending towards the entry's colour by its ratio. The output is
// allocated when the caller passes none.
//
// The palette and colour views repeat the declarations in
// palette_rgb_blend_methods.cpp (bodies 0x626200 and 0x6612C0 live there and
// in its sibling view).

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/colorrgb_00661350.h"

#include "../_layout/colortable_00626070.h"
#include <wchar.h>
#include "ego_class.h"
#include "../core/header_tuning_globals.h"

struct RemapEntry
{
    unsigned char Index;        // +0x0
    unsigned char Color;        // +0x1
    unsigned char Ratio;        // +0x2
    unsigned char unknown_03;   // +0x3
};
GG_STATIC_ASSERT(sizeof(RemapEntry) == 4);   // entry pointer steps by 4


// Retail PAVEgoClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class EgoClass;

// VTABLE: GAMEMD 0x7E86FC -- VectorClass<EgoClass*>.
template class VectorClass<EgoClass*>;
typedef VectorClass<EgoClass*> GgEgoClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E86DC -- DynamicVectorClass<EgoClass*>.
template class DynamicVectorClass<EgoClass*>;
typedef DynamicVectorClass<EgoClass*> GgEgoClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EgoClass*) == 4);

// FUNCTION: GAMEMD 0x4C37D0
// Fills a 256-byte table for the 16 remappable colours: entries 1..240 are blended
// towards one palette colour and mapped to the nearest of palette entries 240..254;
// entry 0 and entries above 240 map to themselves. Returns the table.
unsigned char* __fastcall FUN_004C37D0(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    if (table != 0) {
        unsigned char* out = table;
        for (int i = 0; i < 256; i++) {
            if (i <= 240 && i != 0) {
                ColorRGB_00661350 blended = palette[i];
                blended.Blend(ratio, palette[color]);
                int best = -1;
                int bestDiff = 0;
                for (int k = 240; k < 255; k++) {
                    int diff = palette[k].Difference(blended);
                    if (best == -1 || diff < bestDiff) {
                        best = k;
                        bestDiff = diff;
                    }
                }
                *out++ = (unsigned char)best;
            } else {
                *out++ = (unsigned char)i;
            }
        }
    }
    return table;
}

// FUNCTION: GAMEMD 0x4C38E0
unsigned char* FUN_004c38e0(const ColorTable_00626070& palette, const RemapEntry* entries,
                            int count, unsigned char* buffer)
{
    if (count != 0 && entries != 0)
    {
        if (buffer == 0)
        {
            buffer = new unsigned char[(count + 1) * 256];
        }
        if (buffer != 0)
        {
            memset(buffer, 0xFF, 256);
            unsigned char* table = buffer + 256;
            for (int i = 0; i < count; i++)
            {
                buffer[entries[i].Index] = (unsigned char)i;
                int color_index = entries[i].Color;
                int ratio = entries[i].Ratio;
                ColorRGB_00661350 target = palette[color_index];
                table[0] = 0;
                for (int j = 1; j < 256; j++)
                {
                    ColorRGB_00661350 color = palette[j];
                    color.Blend(ratio, target);
                    table[j] = (unsigned char)palette.Nearest(color);
                }
                table += 256;
            }
        }
    }
    return buffer;
}

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x8A0EE8
extern double DAT_008A0EE8;
// GLOBAL: GAMEMD 0x7E86C8
const double DAT_007E86C8 = 60.0;

// SYNTHETIC: GAMEMD 0x4C35D0
// GLOBAL: GAMEMD 0x8A0F38
double DAT_008A0F38 = DAT_008A0EE8 / DAT_007E86C8;
// SYNTHETIC: GAMEMD 0x4C35F0
// GLOBAL: GAMEMD 0x8A0F20
double DAT_008A0F20 = 1.0 / DAT_008A0F38;
// SYNTHETIC: GAMEMD 0x4C3770
// GLOBAL: GAMEMD 0x8A0F28
TuningCoordInit DAT_008A0F28(128, 128, 0);

// ---- the remap-table builder ---------------------------------------------------------------------------------------

// The palette and the 4-byte remap entries {index, colour, ratio, -} (as in remap_table_build_methods.cpp).
struct RemapPalette_004C3A20;
struct RemapEntry_004C3A20
{
    unsigned char Index;        // +0x0
    unsigned char Color;        // +0x1
    unsigned char Ratio;        // +0x2
    unsigned char unknown_03;   // +0x3
};
GG_STATIC_ASSERT(sizeof(RemapEntry_004C3A20) == 4);

// FUNCTION: GAMEMD 0x4C37D0 (decl; reloc) -- __fastcall, fills one 256-byte table.
void FUN_004C37D0(const RemapPalette_004C3A20& palette, unsigned char* table, int color, int ratio);

// FUNCTION: GAMEMD 0x4C3A20
unsigned char* FUN_004C3A20(const RemapPalette_004C3A20& palette, const RemapEntry_004C3A20* entries,
                            int count, unsigned char* buffer)
{
    if (count != 0 && entries != 0)
    {
        if (buffer == 0)
        {
            buffer = new unsigned char[(count + 1) * 256];
        }
        if (buffer != 0)
        {
            memset(buffer, 0xFF, 256);
            unsigned char* table = buffer + 256;
            for (int i = 0; i < count; i++)
            {
                buffer[entries[i].Index] = (unsigned char)i;
                FUN_004C37D0(palette, table, entries[i].Color, entries[i].Ratio);
                table += 256;
            }
        }
    }
    return buffer;
}

// ---- EgoClass ------------------------------------------------------------------------------------------------------

struct EgoRect
{
    int X;   // +0x00
    int Y;   // +0x04
    int W;   // +0x08
    int H;   // +0x0C
};

// The drawing surface (pointer global 0x887314): slot 2 copies a rectangle, slot 32 its height.
struct EgoSurface
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2(EgoRect* destRect, void* source, EgoRect* sourceRect, int a4, int a5);
    virtual void vf_3();  virtual void vf_4();  virtual void vf_5();  virtual void vf_6();
    virtual void vf_7();  virtual void vf_8();  virtual void vf_9();  virtual void vf_10();
    virtual void vf_11(); virtual void vf_12(); virtual void vf_13(); virtual void vf_14();
    virtual void vf_15(); virtual void vf_16(); virtual void vf_17(); virtual void vf_18();
    virtual void vf_19(); virtual void vf_20(); virtual void vf_21(); virtual void vf_22();
    virtual void vf_23(); virtual void vf_24(); virtual void vf_25(); virtual void vf_26();
    virtual void vf_27(); virtual void vf_28(); virtual void vf_29(); virtual void vf_30();
    virtual void vf_31();
    virtual int vf_32();
};
// GLOBAL: GAMEMD 0x887314
extern EgoSurface* DAT_00887314;
// GLOBAL: GAMEMD 0x8A00A4 -- the screen width.
extern int DAT_008A00A4;
// GLOBAL: GAMEMD 0x8A00A8 -- the screen height.
extern int DAT_008A00A8;
// GLOBAL: GAMEMD 0xA8ED80
extern bool DAT_00A8ED80;
// GLOBAL: GAMEMD 0x8A0F58
extern void* DAT_008A0F58;

struct EgoFont
{
    // FUNCTION: GAMEMD 0x433ED0 (decl; reloc) -- RET 8.
    int FUN_00433ED0(const wchar_t* text, int flag);
};
// FUNCTION: GAMEMD 0x4A60D0 (decl; reloc) -- __fastcall, the font for a set of print flags.
EgoFont* FUN_004A60D0(int flags);
// FUNCTION: GAMEMD 0x6211D0 (decl; reloc) -- __fastcall text print.
void FUN_006211D0(int color, int unknown, EgoRect* rect, const wchar_t* text, int length,
                  int align, int a7, void* a8, int a9);

// FUNCTION: GAMEMD 0x4C3C90
EgoClass::EgoClass(int a1, int y, const wchar_t* text, int flags)
{
    unknown_04 = a1;
    Y = y;
    Flags = flags;
    Text = (wchar_t*)operator new((wcslen(text) + 1) * sizeof(wchar_t));
    wcscpy(Text, text);
}

// FUNCTION: GAMEMD 0x4C3D00
void EgoClass::FUN_004C3D00(bool force)
{
    if ((Y < DAT_00887314->vf_32() && Y > DAT_00887314->vf_32() - 52)
        || (Y >= -16 && Y <= 32) || force)
    {
        EgoRect rect;
        rect.X = (DAT_008A00A4 - 520) / 2;
        rect.W = 520;
        rect.Y = Y;
        rect.H = DAT_008A00A8;
        int align = 0;
        if (Flags & 0x100) {
            align = 1;
        } else if (Flags & 0x200) {
            align = 4;
        }
        if (DAT_00A8ED80) {
            FUN_006211D0(0x80FFFF, 0, &rect, Text, wcslen(Text), align, 0, DAT_008A0F58, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x4C3DD0
void EgoClass::FUN_004C3DD0(void* surface)
{
    EgoFont* font = FUN_004A60D0(Flags);
    font->FUN_00433ED0(Text, 0);
    EgoRect rect;
    rect.X = 0;
    rect.Y = Y;
    rect.W = DAT_008A00A4;
    rect.H = 18;
    DAT_00887314->vf_2(&rect, surface, &rect, 0, 1);
}

// FUNCTION: GAMEMD 0x4C3AD0
// Fills a 256-byte table: every palette colour blended towards one palette colour,
// then mapped to its nearest palette entry. Returns the table (null when none was given).
unsigned char* __fastcall FUN_004C3AD0(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    if (table != 0) {
        for (int i = 0; i < 256; i++) {
            ColorRGB_00661350 blended = palette[i];
            blended.Blend(ratio, palette[color]);
            table[i] = (unsigned char)palette.Nearest(blended);
        }
    }
    return table;
}

// FUNCTION: GAMEMD 0x4C3B60
// The same table with entry 0 pinned to 0 (colour 0 stays transparent).
unsigned char* __fastcall FUN_004C3B60(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    ColorRGB_00661350 target = palette[color];
    table[0] = 0;
    for (int i = 1; i < 256; i++) {
        ColorRGB_00661350 blended = palette[i];
        blended.Blend(ratio, target);
        table[i] = (unsigned char)palette.Nearest(blended);
    }
    return table;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C49A0
// DynamicVectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C49D0
// DynamicVectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C49F0
// VectorClass<EgoClass*>::Slot6

// FUNCTION: GAMEMD 0x4C4A00
// VectorClass<EgoClass*>::operator==

// FUNCTION: GAMEMD 0x4C4A40
// VectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4AF0
// VectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C4B20
// VectorClass<EgoClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C4B60
// VectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C4B80
// DynamicVectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4C30
// DynamicVectorClass<EgoClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C4C60
// VectorClass<EgoClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C4CB0
// DynamicVectorClass<EgoClass*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A0F58
void* DAT_008A0F58;
// END defined globals
