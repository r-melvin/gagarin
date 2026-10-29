// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The Egos.CPP block of retail .text (0x4C35B0..0x4C4D2F): three of the unit's
// run-time initialisers, the remap-table builder 0x4C3A20 and the EgoClass
// constructor and draw bodies, in retail address order. EgoClass is declared
// in ego_class.h.

#include <string.h>
#include <wchar.h>
#include "ego_class.h"
#include "../core/header_tuning_globals.h"

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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A0F58
void* DAT_008A0F58;
// END defined globals
