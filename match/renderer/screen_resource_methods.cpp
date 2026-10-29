// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The screen resource block between 0x72A6B0 and 0x72D9A0, in retail address order: the run-time initialisers of the
// block's globals, small rectangle helpers, and the load/release/query functions for the shell screens' whole-file
// blocks (0x4A38D0) and palette sets (0x72ADE0). No receiver is passed to any of these: each works on module-scope
// globals, so they are free functions (fastcall under /Gr).
//
// Each shell screen has the same nine functions over its own globals, in this order: load all (guarded by its
// loaded flag), release all, the loaded-flag getter, the palette getter, the convert getter, load the SHP block
// (only at width 800), load the palette set, release the SHP block, release the palette set. The flag, block, name
// and palette globals are per screen; offsets and the PaletteSet / ScreenPaletteRes layouts are asserted in
// screen_palette_mgr_methods.h. Rows already matched elsewhere (the convert getters, 0x72B9E0..0x72BA80,
// 0x72CAC0..0x72CB60 and the named family in screen_palette_mgr_methods.cpp) are not repeated here.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <math.h>
#pragma intrinsic(pow)
#include "screen_palette_mgr_methods.h"
#include "../_layout/geometry2d.h"
#include "../core/mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0x844B9C
extern const char* DAT_00844B9C;
// GLOBAL: GAMEMD 0x844BA0
extern const char* DAT_00844BA0;
// GLOBAL: GAMEMD 0x844BA4
extern const char* DAT_00844BA4;
// GLOBAL: GAMEMD 0x844BA8
extern const char* DAT_00844BA8;
// GLOBAL: GAMEMD 0x844BC4
extern const char* DAT_00844BC4;
// GLOBAL: GAMEMD 0x844BC8
extern const char* DAT_00844BC8;
// GLOBAL: GAMEMD 0x844BCC
extern const char* DAT_00844BCC;
// GLOBAL: GAMEMD 0x844BD0
extern const char* DAT_00844BD0;
// GLOBAL: GAMEMD 0x844BE0
extern const char* DAT_00844BE0;
// GLOBAL: GAMEMD 0x844BE4
extern const char* DAT_00844BE4;
// GLOBAL: GAMEMD 0x844D50
extern const char* DAT_00844D50;
// GLOBAL: GAMEMD 0x844D58
extern const char* DAT_00844D58;
// GLOBAL: GAMEMD 0x844D60
extern const char* DAT_00844D60;
// GLOBAL: GAMEMD 0x844BE8
extern const char* DAT_00844BE8;
// GLOBAL: GAMEMD 0x844BEC
extern const char* DAT_00844BEC;
// GLOBAL: GAMEMD 0x844C0C
extern const char* DAT_00844C0C;
// GLOBAL: GAMEMD 0x844C10
extern const char* DAT_00844C10;
// GLOBAL: GAMEMD 0x844C14
extern const char* DAT_00844C14;
// GLOBAL: GAMEMD 0x844C18
extern const char* DAT_00844C18;
// GLOBAL: GAMEMD 0x844C1C
extern const char* DAT_00844C1C;
// GLOBAL: GAMEMD 0x844C20
extern const char* DAT_00844C20;
// GLOBAL: GAMEMD 0x844C24
extern const char* DAT_00844C24;
// GLOBAL: GAMEMD 0x844C28
extern const char* DAT_00844C28;
// GLOBAL: GAMEMD 0x844C2C
extern const char* DAT_00844C2C;
// GLOBAL: GAMEMD 0x844C30
extern const char* DAT_00844C30;
// GLOBAL: GAMEMD 0x844C34
extern const char* DAT_00844C34;
// GLOBAL: GAMEMD 0x844C38
extern const char* DAT_00844C38;
// GLOBAL: GAMEMD 0x844C3C
extern const char* DAT_00844C3C;
// GLOBAL: GAMEMD 0x844C40
extern const char* DAT_00844C40;
// GLOBAL: GAMEMD 0x844C44
extern const char* DAT_00844C44;
// GLOBAL: GAMEMD 0x844C48
extern const char* DAT_00844C48;
// GLOBAL: GAMEMD 0x844C4C
extern const char* DAT_00844C4C;
// GLOBAL: GAMEMD 0x844C50
extern const char* DAT_00844C50;
// GLOBAL: GAMEMD 0x844C54
extern const char* DAT_00844C54;
// GLOBAL: GAMEMD 0x844C58
extern const char* DAT_00844C58;
// GLOBAL: GAMEMD 0x844C5C
extern const char* DAT_00844C5C;
// GLOBAL: GAMEMD 0x844C60
extern const char* DAT_00844C60;
// GLOBAL: GAMEMD 0x844C64
extern const char* DAT_00844C64;
// GLOBAL: GAMEMD 0x844C68
extern const char* DAT_00844C68;
// GLOBAL: GAMEMD 0x844C6C
extern const char* DAT_00844C6C;
// GLOBAL: GAMEMD 0x844C70
extern const char* DAT_00844C70;
// GLOBAL: GAMEMD 0x844C74
extern const char* DAT_00844C74;
// GLOBAL: GAMEMD 0x844C78
extern const char* DAT_00844C78;
// GLOBAL: GAMEMD 0x844C7C
extern const char* DAT_00844C7C;
// GLOBAL: GAMEMD 0x844C80
extern const char* DAT_00844C80;
// GLOBAL: GAMEMD 0x844C84
extern const char* DAT_00844C84;
// GLOBAL: GAMEMD 0x844C88
extern const char* DAT_00844C88;
// GLOBAL: GAMEMD 0x844C8C
extern const char* DAT_00844C8C;
// GLOBAL: GAMEMD 0x844C90
extern const char* DAT_00844C90;
// GLOBAL: GAMEMD 0x844C94
extern const char* DAT_00844C94;
// GLOBAL: GAMEMD 0x844C98
extern const char* DAT_00844C98;
// GLOBAL: GAMEMD 0x844C9C
extern const char* DAT_00844C9C;
// GLOBAL: GAMEMD 0x844CA0
extern const char* DAT_00844CA0;
// GLOBAL: GAMEMD 0x844CA4
extern const char* DAT_00844CA4;
// GLOBAL: GAMEMD 0x844CA8
extern const char* DAT_00844CA8;
// GLOBAL: GAMEMD 0x844CAC
extern const char* DAT_00844CAC;
// GLOBAL: GAMEMD 0x844CB0
extern const char* DAT_00844CB0;
// GLOBAL: GAMEMD 0x844CB4
extern const char* DAT_00844CB4;
// GLOBAL: GAMEMD 0x844CD4
extern const char* DAT_00844CD4;
// GLOBAL: GAMEMD 0x844CD8
extern const char* DAT_00844CD8;
// GLOBAL: GAMEMD 0x844CDC
extern const char* DAT_00844CDC;
// GLOBAL: GAMEMD 0x844CE0
extern const char* DAT_00844CE0;
// GLOBAL: GAMEMD 0x844CE4
extern const char* DAT_00844CE4;
// GLOBAL: GAMEMD 0x844CE8
extern const char* DAT_00844CE8;
// GLOBAL: GAMEMD 0x844CEC
extern const char* DAT_00844CEC;
// GLOBAL: GAMEMD 0x844CF0
extern const char* DAT_00844CF0;
// GLOBAL: GAMEMD 0x844CF4
extern const char* DAT_00844CF4;
// GLOBAL: GAMEMD 0x844CF8
extern const char* DAT_00844CF8;
// GLOBAL: GAMEMD 0x844D64
extern const char* DAT_00844D64;
// GLOBAL: GAMEMD 0x844D68
extern const char* DAT_00844D68;
// GLOBAL: GAMEMD 0x844D6C
extern const char* DAT_00844D6C;
// GLOBAL: GAMEMD 0x844D70
extern const char* DAT_00844D70;
// GLOBAL: GAMEMD 0x844D74
extern const char* DAT_00844D74;
// GLOBAL: GAMEMD 0x844D78
extern const char* DAT_00844D78;
// GLOBAL: GAMEMD 0x844D7C
extern const char* DAT_00844D7C;
// GLOBAL: GAMEMD 0x844D80
extern const char* DAT_00844D80;
// GLOBAL: GAMEMD 0x844D84
extern const char* DAT_00844D84;
// GLOBAL: GAMEMD 0x844D88
extern const char* DAT_00844D88;
// GLOBAL: GAMEMD 0x844D8C
extern const char* DAT_00844D8C;
// GLOBAL: GAMEMD 0x844D90
extern const char* DAT_00844D90;
// GLOBAL: GAMEMD 0x844D94
extern const char* DAT_00844D94;
// GLOBAL: GAMEMD 0x844D98
extern const char* DAT_00844D98;
// GLOBAL: GAMEMD 0x844D9C
extern const char* DAT_00844D9C;
// GLOBAL: GAMEMD 0x844DA0
extern const char* DAT_00844DA0;
// GLOBAL: GAMEMD 0x844DA4
extern const char* DAT_00844DA4;
// GLOBAL: GAMEMD 0x844DA8
extern const char* DAT_00844DA8;
// GLOBAL: GAMEMD 0x844DBC
extern const char* DAT_00844DBC;
// GLOBAL: GAMEMD 0x844DC0
extern const char* DAT_00844DC0;
// GLOBAL: GAMEMD 0x844DC4
extern const char* DAT_00844DC4;
// GLOBAL: GAMEMD 0x844DC8
extern const char* DAT_00844DC8;
// GLOBAL: GAMEMD 0x845530
extern const char DAT_00845530[];
// GLOBAL: GAMEMD 0x845540
extern const char DAT_00845540[];
// GLOBAL: GAMEMD 0x886FB0
extern RectangleStruct DAT_00886FB0;
// GLOBAL: GAMEMD 0x8A00A8
extern int DAT_008A00A8;
// GLOBAL: GAMEMD 0xA8EB7C
extern bool DAT_00A8EB7C;
// GLOBAL: GAMEMD 0xA8EB84
extern int DAT_00A8EB84;
// GLOBAL: GAMEMD 0xA8EB88
extern int DAT_00A8EB88;
// GLOBAL: GAMEMD 0xA8ED6B
extern bool DAT_00A8ED6B;
// GLOBAL: GAMEMD 0xAC10C8
extern int DAT_00AC10C8;
// GLOBAL: GAMEMD 0xB0F9DC
extern WholeFileBlock* DAT_00B0F9DC;
// GLOBAL: GAMEMD 0xB0F9E8
extern WholeFileBlock* DAT_00B0F9E8;
// GLOBAL: GAMEMD 0xB0FA04
extern WholeFileBlock* DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FA18
extern WholeFileBlock* DAT_00B0FA18;
// GLOBAL: GAMEMD 0xB0FA30
extern WholeFileBlock* DAT_00B0FA30;
// GLOBAL: GAMEMD 0xB0FA38
extern WholeFileBlock* DAT_00B0FA38;
// GLOBAL: GAMEMD 0xB0FA4C
extern WholeFileBlock* DAT_00B0FA4C;
// GLOBAL: GAMEMD 0xB0FA54
extern WholeFileBlock* DAT_00B0FA54;
// GLOBAL: GAMEMD 0xB0FA60
extern WholeFileBlock* DAT_00B0FA60;
// GLOBAL: GAMEMD 0xB0FA64
extern WholeFileBlock* DAT_00B0FA64;
// GLOBAL: GAMEMD 0xB0FA74
extern WholeFileBlock* DAT_00B0FA74;
// GLOBAL: GAMEMD 0xB0FAAC
extern WholeFileBlock* DAT_00B0FAAC;
// GLOBAL: GAMEMD 0xB0FAB8
extern WholeFileBlock* DAT_00B0FAB8;
// GLOBAL: GAMEMD 0xB0FAC0
extern WholeFileBlock* DAT_00B0FAC0;
// GLOBAL: GAMEMD 0xB0FAC4
extern WholeFileBlock* DAT_00B0FAC4;
// GLOBAL: GAMEMD 0xB0FACC
extern WholeFileBlock* DAT_00B0FACC;
// GLOBAL: GAMEMD 0xB0FAD0
extern WholeFileBlock* DAT_00B0FAD0;
// GLOBAL: GAMEMD 0xB0FAE8
extern WholeFileBlock* DAT_00B0FAE8;
// GLOBAL: GAMEMD 0xB0FAF8
extern WholeFileBlock* DAT_00B0FAF8;
// GLOBAL: GAMEMD 0xB0FB00
extern WholeFileBlock* DAT_00B0FB00;
// GLOBAL: GAMEMD 0xB0FB0C
extern WholeFileBlock* DAT_00B0FB0C;
// GLOBAL: GAMEMD 0xB0FB2C
extern WholeFileBlock* DAT_00B0FB2C;
// GLOBAL: GAMEMD 0xB0FB30
extern WholeFileBlock* DAT_00B0FB30;
// GLOBAL: GAMEMD 0xB0FB34
extern WholeFileBlock* DAT_00B0FB34;
// GLOBAL: GAMEMD 0xB0FB50
extern WholeFileBlock* DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FB54
extern WholeFileBlock* DAT_00B0FB54;
// GLOBAL: GAMEMD 0xB0FBA4
extern PaletteSet DAT_00B0FBA4;
// GLOBAL: GAMEMD 0xB0FBAC
extern bool DAT_00B0FBAC;
// GLOBAL: GAMEMD 0xB0FBE0
extern char DAT_00B0FBE0;
// GLOBAL: GAMEMD 0xB0FC0C
extern char DAT_00B0FC0C;
// GLOBAL: GAMEMD 0xB0FC10
extern void* DAT_00B0FC10;
// GLOBAL: GAMEMD 0xB0FC14
extern void* DAT_00B0FC14;
// GLOBAL: GAMEMD 0xB0FC18
extern void* DAT_00B0FC18;
// GLOBAL: GAMEMD 0xB0FC1C
extern void* DAT_00B0FC1C;
// GLOBAL: GAMEMD 0xB0FC20
extern void* DAT_00B0FC20;
// GLOBAL: GAMEMD 0xB0FC24
extern void* DAT_00B0FC24;
// GLOBAL: GAMEMD 0xB0FC28
extern void* DAT_00B0FC28;
// GLOBAL: GAMEMD 0xB0FC2C
extern void* DAT_00B0FC2C;
// GLOBAL: GAMEMD 0xB0FC70
extern bool DAT_00B0FC70;
// GLOBAL: GAMEMD 0xB0FC71
extern bool DAT_00B0FC71;
// GLOBAL: GAMEMD 0xB0FC72
extern bool DAT_00B0FC72;
// GLOBAL: GAMEMD 0xB0FC73
extern bool DAT_00B0FC73;
// GLOBAL: GAMEMD 0xB0FC74
extern PaletteSet DAT_00B0FC74;
// GLOBAL: GAMEMD 0xB0FC7C
extern bool DAT_00B0FC7C;
// GLOBAL: GAMEMD 0xB0FC80
extern WholeFileBlock* DAT_00B0FC80;
// GLOBAL: GAMEMD 0xB0FC84
extern WholeFileBlock* DAT_00B0FC84;
// GLOBAL: GAMEMD 0xB0FC88
extern WholeFileBlock* DAT_00B0FC88;
// GLOBAL: GAMEMD 0xB0FC8C
extern WholeFileBlock* DAT_00B0FC8C;
// GLOBAL: GAMEMD 0xB0FC90
extern bool DAT_00B0FC90;
// GLOBAL: GAMEMD 0xB0FC91
extern bool DAT_00B0FC91;
// GLOBAL: GAMEMD 0xB0FC92
extern bool DAT_00B0FC92;
// GLOBAL: GAMEMD 0xB0FC93
extern bool DAT_00B0FC93;
// GLOBAL: GAMEMD 0xB0FC94
extern bool DAT_00B0FC94;
// GLOBAL: GAMEMD 0xB0FC95
extern bool DAT_00B0FC95;
// GLOBAL: GAMEMD 0xB0FC96
extern bool DAT_00B0FC96;
// GLOBAL: GAMEMD 0xB0FC97
extern bool DAT_00B0FC97;
// GLOBAL: GAMEMD 0xB0FC98
extern bool DAT_00B0FC98;
// GLOBAL: GAMEMD 0xB0FC99
extern bool DAT_00B0FC99;
// GLOBAL: GAMEMD 0xB0FC9A
extern bool DAT_00B0FC9A;
// GLOBAL: GAMEMD 0xB0FC9B
extern bool DAT_00B0FC9B;
// GLOBAL: GAMEMD 0xB0FC9C
extern bool DAT_00B0FC9C;
// GLOBAL: GAMEMD 0xB0FC9D
extern bool DAT_00B0FC9D;
// GLOBAL: GAMEMD 0xB0FC9E
extern bool DAT_00B0FC9E;
// GLOBAL: GAMEMD 0xB0FCCD
extern bool DAT_00B0FCCD;
// GLOBAL: GAMEMD 0xB0FCCE
extern bool DAT_00B0FCCE;
// GLOBAL: GAMEMD 0xB0FCD0
extern PaletteSet DAT_00B0FCD0;
// GLOBAL: GAMEMD 0xB0FCD8
extern bool DAT_00B0FCD8;
// GLOBAL: GAMEMD 0xB0FCD9
extern bool DAT_00B0FCD9;
// GLOBAL: GAMEMD 0xB0FCDC
extern PaletteSet DAT_00B0FCDC;
// GLOBAL: GAMEMD 0xB0FCE4
extern bool DAT_00B0FCE4;
// GLOBAL: GAMEMD 0xB0FCE5
extern bool DAT_00B0FCE5;
// GLOBAL: GAMEMD 0xB0FCE8
extern PaletteSet DAT_00B0FCE8;
// GLOBAL: GAMEMD 0xB0FCF0
extern bool DAT_00B0FCF0;
// GLOBAL: GAMEMD 0xB0FCF1
extern bool DAT_00B0FCF1;
// GLOBAL: GAMEMD 0xB0FCF4
extern PaletteSet DAT_00B0FCF4;
// GLOBAL: GAMEMD 0xB0FCFC
extern bool DAT_00B0FCFC;
// GLOBAL: GAMEMD 0xB0FCFD
extern bool DAT_00B0FCFD;
// GLOBAL: GAMEMD 0xB0FD00
extern PaletteSet DAT_00B0FD00;
// GLOBAL: GAMEMD 0xB0FD08
extern bool DAT_00B0FD08;
// GLOBAL: GAMEMD 0xB0FD09
extern bool DAT_00B0FD09;
// GLOBAL: GAMEMD 0xB0FD0C
extern PaletteSet DAT_00B0FD0C;
// GLOBAL: GAMEMD 0xB0FD14
extern bool DAT_00B0FD14;
// GLOBAL: GAMEMD 0xB0FD15
extern bool DAT_00B0FD15;
// GLOBAL: GAMEMD 0xB0FD18
extern PaletteSet DAT_00B0FD18;
// GLOBAL: GAMEMD 0xB0FD20
extern bool DAT_00B0FD20;
// GLOBAL: GAMEMD 0xB0FD21
extern bool DAT_00B0FD21;
// GLOBAL: GAMEMD 0xB0FD24
extern PaletteSet DAT_00B0FD24;
// GLOBAL: GAMEMD 0xB0FD2C
extern bool DAT_00B0FD2C;
// GLOBAL: GAMEMD 0xB0FD2D
extern bool DAT_00B0FD2D;
// GLOBAL: GAMEMD 0xB0FD30
extern PaletteSet DAT_00B0FD30;
// GLOBAL: GAMEMD 0xB0FD50
extern bool DAT_00B0FD50;
// GLOBAL: GAMEMD 0xB0FD51
extern bool DAT_00B0FD51;
// GLOBAL: GAMEMD 0xB0FD54
extern PaletteSet DAT_00B0FD54;
// GLOBAL: GAMEMD 0xB0FD5C
extern bool DAT_00B0FD5C;
// GLOBAL: GAMEMD 0xB0FD5D
extern bool DAT_00B0FD5D;
// GLOBAL: GAMEMD 0xB0FD60
extern PaletteSet DAT_00B0FD60;
// GLOBAL: GAMEMD 0xB0FD68
extern int DAT_00B0FD68;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square-root helper, __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x7C8FB0 -- x87 _CIpow, emitted by VC6's pow intrinsic.

// FUNCTION: GAMEMD 0x534E50 (decl; reloc)
void FUN_00534E50();
// FUNCTION: GAMEMD 0x534DE0 (decl; reloc)
void FUN_00534DE0();
// FUNCTION: GAMEMD 0x72EC70 (decl; reloc) -- takes the screen width and height.
void FUN_0072EC70(int width, int height);
// FUNCTION: GAMEMD 0x72EF60 (decl; reloc)
void FUN_0072EF60();
// FUNCTION: GAMEMD 0x730100 (decl; reloc)
void FUN_00730100();
// FUNCTION: GAMEMD 0x730400 (decl; reloc)
void FUN_00730400();
// FUNCTION: GAMEMD 0x730530 (decl; reloc)
void FUN_00730530();

void FUN_0072B130();
void FUN_0072D460(int sideIndex);

// Both palette sets at 0xB0FB94 and 0xB0FB9C, convert before palette for the second and palette before convert for the
// first; 0x72B530 expands this twice.
inline void ReleaseB0FB94Sets()
{
    if (DAT_00B0FB9C.Convert != 0) {
        DAT_00B0FB9C.Convert->vf_0(1);
        DAT_00B0FB9C.Convert = 0;
    }
    if (DAT_00B0FB9C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB9C.Palette);
        DAT_00B0FB9C.Palette = 0;
    }
    if (DAT_00B0FB94.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB94.Palette);
        DAT_00B0FB94.Palette = 0;
    }
    if (DAT_00B0FB94.Convert != 0) {
        DAT_00B0FB94.Convert->vf_0(1);
        DAT_00B0FB94.Convert = 0;
    }
}

// ---- Run-time initialised globals ------------------------------------------------------------------------------------
// In __xc order; each definition below produces one compiler-generated initialiser. Retail keeps the two constants it
// reads from memory (0x7F5BD0 = 60.0, 0x7F5BD8 = pi / 180) as named data; literal factors come from the shared pool.

// GLOBAL: GAMEMD 0x7F5BD0
const double DAT_007F5BD0 = 60.0;
// GLOBAL: GAMEMD 0x7F5BD8
const double DAT_007F5BD8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x72A690
// GLOBAL: GAMEMD 0xB0FA08
MathTblZero4 DAT_00B0FA08;

// SYNTHETIC: GAMEMD 0x72A6B0
// GLOBAL: GAMEMD 0xB0FA28
double DAT_00B0FA28 = FUN_004CAC40(2.0 * pow(256.0, 2.0));

// SYNTHETIC: GAMEMD 0x72A6E0
// GLOBAL: GAMEMD 0xB0FB40
double DAT_00B0FB40 = DAT_00B0FA28 / DAT_007F5BD0;

// SYNTHETIC: GAMEMD 0x72A700
// GLOBAL: GAMEMD 0xB0FAF0
double DAT_00B0FAF0 = 1.0 / DAT_00B0FB40;
// SYNTHETIC: GAMEMD 0x72A720
// GLOBAL: GAMEMD 0xB0FAE0
double DAT_00B0FAE0 = DAT_007F5BD8 * 45.0;
// SYNTHETIC: GAMEMD 0x72A740
// GLOBAL: GAMEMD 0xB0FA40
double DAT_00B0FA40 = DAT_007F5BD8 * 60.0;
// SYNTHETIC: GAMEMD 0x72A760
// GLOBAL: GAMEMD 0xB0F9F0
double DAT_00B0F9F0 = DAT_007F5BD8 * 90.0;
// SYNTHETIC: GAMEMD 0x72A780
// GLOBAL: GAMEMD 0xB0FB58
int DAT_00B0FB58 = (int)(FUN_004CAD50(DAT_00B0F9F0 - DAT_00B0FA40) * DAT_00B0FA28 * 0.5);
// SYNTHETIC: GAMEMD 0x72A7C0
// GLOBAL: GAMEMD 0xB0FA58
double DAT_00B0FA58 = FUN_004CADE0(DAT_00B0FB58 * 0.00390625);
// SYNTHETIC: GAMEMD 0x72A7F0
// GLOBAL: GAMEMD 0xB0FAB0
double DAT_00B0FAB0 = FUN_004CADE0((DAT_00B0FB58 * 2) / DAT_00B0FA28);
// SYNTHETIC: GAMEMD 0x72A820
// GLOBAL: GAMEMD 0xB0FB38
int DAT_00B0FB38 = (int)(DAT_00B0FB58 * 4 + 0.5);

// These objects are filled at run time: retail's __xc table lists initialisers that store constants, which VC6 emits
// only for a constructor call, so their types had constructors. The views below supply them.
struct ScreenCellInit
{
    short X;
    short Y;
    ScreenCellInit(short x, short y) { X = x; Y = y; }
};
struct ScreenCoordInit
{
    int X;
    int Y;
    int Z;
    ScreenCoordInit(int x, int y, int z) { X = x; Y = y; Z = z; }
};
struct ScreenColorInit
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    ScreenColorInit(unsigned char r, unsigned char g, unsigned char b) { R = r; G = g; B = b; }
};
GG_STATIC_ASSERT(sizeof(ScreenCellInit) == 4);
GG_STATIC_ASSERT(sizeof(ScreenCoordInit) == 12);
GG_STATIC_ASSERT(sizeof(ScreenColorInit) == 3);

// SYNTHETIC: GAMEMD 0x72A850
// GLOBAL: GAMEMD 0xB0FA24
ScreenCellInit DAT_00B0FA24(0, 0);
// SYNTHETIC: GAMEMD 0x72A860
// GLOBAL: GAMEMD 0xB0FA80
ScreenCoordInit DAT_00B0FA80(0, 0, 0);

// SYNTHETIC: GAMEMD 0x72A880
// GLOBAL: GAMEMD 0xB0FB20
ScreenCoordInit DAT_00B0FB20(128, 128, 0);
// SYNTHETIC: GAMEMD 0x72A8A0
// GLOBAL: GAMEMD 0xB0FB4C
ScreenColorInit DAT_00B0FB4C(255, 255, 0);
// SYNTHETIC: GAMEMD 0x72A8C0
// GLOBAL: GAMEMD 0xB0FA94
ScreenColorInit DAT_00B0FA94(0x48, 0, 0);
// SYNTHETIC: GAMEMD 0x72A8E0
// GLOBAL: GAMEMD 0xB0F9FC
ScreenColorInit DAT_00B0F9FC(0, 0x52, 0x75);
// SYNTHETIC: GAMEMD 0x72A900
// GLOBAL: GAMEMD 0xB0FB14
ScreenColorInit DAT_00B0FB14(0x48, 0, 0);
// SYNTHETIC: GAMEMD 0x72A920
// GLOBAL: GAMEMD 0xB0FB19
ScreenColorInit DAT_00B0FB19(0x48, 0, 0);
// SYNTHETIC: GAMEMD 0x72A940
// GLOBAL: GAMEMD 0xB0F9D8
ScreenColorInit DAT_00B0F9D8(0xA4, 0xD2, 0xFF);
// SYNTHETIC: GAMEMD 0x72A960
// GLOBAL: GAMEMD 0xB0FB04
ScreenColorInit DAT_00B0FB04(255, 255, 0);
// SYNTHETIC: GAMEMD 0x72A980
// GLOBAL: GAMEMD 0xB0FAA0
ScreenColorInit DAT_00B0FAA0(255, 255, 0);
// SYNTHETIC: GAMEMD 0x72A9A0
// GLOBAL: GAMEMD 0xB0FA1C
ScreenColorInit DAT_00B0FA1C(0, 0, 0);

// FUNCTION: GAMEMD 0x72A9C0
// Whole-struct copy that hands back the destination (caller at 0x552C3B).
Point2D* FUN_0072A9C0(Point2D* out, const Point2D* in)
{
    Point2D point = *in;
    *out = point;
    return out;
}

// FUNCTION: GAMEMD 0x72A9D0
void FUN_0072A9D0(Point2D* out, const Point2D* in)
{
    out->X = in->X;
    out->Y = in->Y;
}

// FUNCTION: GAMEMD 0x72A9E0
// Move the rectangle's origin by `amount` on both axes and shrink both sides by twice that.
void FUN_0072A9E0(RectangleStruct* rect, int amount)
{
    rect->X += amount;
    rect->Y += amount;
    rect->Width -= amount * 2;
    rect->Height -= amount * 2;
}

// FUNCTION: GAMEMD 0x72AA10
// The two-axis form of 0x72A9E0 (RET 4).
void FUN_0072AA10(RectangleStruct* rect, int dx, int dy)
{
    rect->X += dx;
    rect->Y += dy;
    rect->Width += -dx * 2;
    rect->Height += -dy * 2;
}

// FUNCTION: GAMEMD 0x72AA40
// Load the in-game resources: five whole-file blocks and four palette sets, then (once, guarded by 0xB0FBE0) ten more
// blocks, three more palette sets and the 0x72EC70 setup for the current screen size.
void FUN_0072AA40()
{
    DAT_00B0FC80 = FileSystem_LoadWholeFileEx(DAT_00844C44, &DAT_00B0FC90);
    DAT_00B0FC84 = FileSystem_LoadWholeFileEx(DAT_00844C48, &DAT_00B0FC91);
    DAT_00B0FC88 = FileSystem_LoadWholeFileEx(DAT_00844C4C, &DAT_00B0FC92);
    DAT_00B0FC8C = FileSystem_LoadWholeFileEx(DAT_00844C50, &DAT_00B0FC93);
    DAT_00B0FACC = FileSystem_LoadWholeFileEx(DAT_00844C54, &DAT_00B0FC94);
    ConvertClass_CreateFromFile(DAT_00844BA4, DAT_00B0FB64.Palette, DAT_00B0FB64.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA0, DAT_00B0FB6C.Palette, DAT_00B0FB6C.Convert);
    ConvertClass_CreateFromFile(DAT_00844B9C, DAT_00B0FB5C.Palette, DAT_00B0FB5C.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA8, DAT_00B0FB74.Palette, DAT_00B0FB74.Convert);

    if (!DAT_00B0FBE0) {
        FUN_00534E50();
        DAT_00B0FAC4 = FileSystem_LoadWholeFileEx(DAT_00844CD4, &DAT_00B0FC95);
        DAT_00B0F9DC = FileSystem_LoadWholeFileEx(DAT_00844CD8, &DAT_00B0FC96);
        DAT_00B0FAC0 = FileSystem_LoadWholeFileEx(DAT_00844CDC, &DAT_00B0FC97);
        DAT_00B0FB50 = FileSystem_LoadWholeFileEx(DAT_00844CE0, &DAT_00B0FC98);
        DAT_00B0FA04 = FileSystem_LoadWholeFileEx(DAT_00844CE4, &DAT_00B0FC99);
        DAT_00B0FAF8 = FileSystem_LoadWholeFileEx(DAT_00844CE8, &DAT_00B0FC9A);
        DAT_00B0FA74 = FileSystem_LoadWholeFileEx(DAT_00844CEC, &DAT_00B0FC9B);
        DAT_00B0FA38 = FileSystem_LoadWholeFileEx(DAT_00844CF0, &DAT_00B0FC9C);
        DAT_00B0FAE8 = FileSystem_LoadWholeFileEx(DAT_00844CF4, &DAT_00B0FC9D);
        DAT_00B0FA54 = FileSystem_LoadWholeFileEx(DAT_00844CF8, &DAT_00B0FC9E);
        ConvertClass_CreateFromFile(DAT_00844BE4, DAT_00B0FBC8.Palette, DAT_00B0FBC8.Convert);
        ConvertClass_CreateFromFile(DAT_00844BE8, DAT_00B0FBD0.Palette, DAT_00B0FBD0.Convert);
        ConvertClass_CreateFromFile(DAT_00844BEC, DAT_00B0FBD8.Palette, DAT_00B0FBD8.Convert);
        FUN_0072EC70(DAT_008A00A4, DAT_008A00A8);
        DAT_00B0FBE0 = 1;
    }
}

// FUNCTION: GAMEMD 0x72AC40
// Release everything 0x72AA40 loaded, then the three later subsystems (0x730100, 0x730400, 0x730530).
void FUN_0072AC40()
{
    FUN_0072B130();
    FreeGamePalettePairs();
    if (DAT_00B0FBE0) {
        DAT_00B0FBE0 = 0;
        FUN_0072EF60();
        FreeAudioTimerPairs();
        FUN_007C8B3D(DAT_00B0FC10);
        DAT_00B0FC10 = 0;
        FUN_007C8B3D(DAT_00B0FC14);
        DAT_00B0FC14 = 0;
        FUN_007C8B3D(DAT_00B0FC18);
        DAT_00B0FC18 = 0;
        FUN_007C8B3D(DAT_00B0FC1C);
        DAT_00B0FC1C = 0;
        FUN_007C8B3D(DAT_00B0FC20);
        DAT_00B0FC20 = 0;
        FUN_007C8B3D(DAT_00B0FC24);
        DAT_00B0FC24 = 0;
        FUN_007C8B3D(DAT_00B0FC28);
        DAT_00B0FC28 = 0;
        FUN_007C8B3D(DAT_00B0FC2C);
        DAT_00B0FC2C = 0;
        FUN_00534DE0();
    }
    FUN_00730100();
    FUN_00730400();
    FUN_00730530();
    DAT_00B0FC0C = 0;
}

// FUNCTION: GAMEMD 0x72AD20
// The tactical view rectangle below the top bar: the 0x886FB0 rectangle moved to the origin, 0xA8 pixels in from the
// left unless either of the two flags at 0xA8EB7C/0xA8ED6B is set, and 0xA8 narrower and 0x20 shorter. Fills and
// returns the caller's rectangle (ECX; callers 0x560F9C and 0x642D8D use the returned EAX).
RectangleStruct* FUN_0072AD20(RectangleStruct* rect)
{
    RectangleStruct view = DAT_00886FB0;
    view.X = 0;
    view.Y = 0;
    if (!DAT_00A8EB7C && !DAT_00A8ED6B) {
        view.X = 0xA8;
    }
    view.Width -= 0xA8;
    view.Height -= 0x20;
    *rect = view;
    return rect;
}

// FUNCTION: GAMEMD 0x72AD90
// The same rectangle over the size pair at 0xA8EB84/0xA8EB88.
RectangleStruct* FUN_0072AD90(RectangleStruct* rect)
{
    RectangleStruct view;
    view.Width = DAT_00A8EB84;
    view.Height = DAT_00A8EB88;
    view.X = 0;
    view.Y = 0;
    if (!DAT_00A8EB7C && !DAT_00A8ED6B) {
        view.X = 0xA8;
    }
    view.Width -= 0xA8;
    view.Height -= 0x20;
    *rect = view;
    return rect;
}

// FUNCTION: GAMEMD 0x72AF10
// The unguarded first half of 0x72AA40.
void FUN_0072AF10()
{
    DAT_00B0FC80 = FileSystem_LoadWholeFileEx(DAT_00844C44, &DAT_00B0FC90);
    DAT_00B0FC84 = FileSystem_LoadWholeFileEx(DAT_00844C48, &DAT_00B0FC91);
    DAT_00B0FC88 = FileSystem_LoadWholeFileEx(DAT_00844C4C, &DAT_00B0FC92);
    DAT_00B0FC8C = FileSystem_LoadWholeFileEx(DAT_00844C50, &DAT_00B0FC93);
    DAT_00B0FACC = FileSystem_LoadWholeFileEx(DAT_00844C54, &DAT_00B0FC94);
    ConvertClass_CreateFromFile(DAT_00844BA4, DAT_00B0FB64.Palette, DAT_00B0FB64.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA0, DAT_00B0FB6C.Palette, DAT_00B0FB6C.Convert);
    ConvertClass_CreateFromFile(DAT_00844B9C, DAT_00B0FB5C.Palette, DAT_00B0FB5C.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA8, DAT_00B0FB74.Palette, DAT_00B0FB74.Convert);
}

// FUNCTION: GAMEMD 0x72AFD0
void FUN_0072AFD0()
{
    FUN_0072B130();
    FreeGamePalettePairs();
}

// FUNCTION: GAMEMD 0x72AFE0
ColorStruct_Res* FUN_0072AFE0()
{
    return DAT_00B0FB64.Palette;
}

// FUNCTION: GAMEMD 0x72B000
ColorStruct_Res* FUN_0072B000()
{
    return DAT_00B0FB6C.Palette;
}

// FUNCTION: GAMEMD 0x72B020
ColorStruct_Res* FUN_0072B020()
{
    return DAT_00B0FB5C.Palette;
}

// FUNCTION: GAMEMD 0x72B040
ColorStruct_Res* FUN_0072B040()
{
    return DAT_00B0FB74.Palette;
}

// FUNCTION: GAMEMD 0x72B060
void FUN_0072B060()
{
    DAT_00B0FC80 = FileSystem_LoadWholeFileEx(DAT_00844C44, &DAT_00B0FC90);
    DAT_00B0FC84 = FileSystem_LoadWholeFileEx(DAT_00844C48, &DAT_00B0FC91);
    DAT_00B0FC88 = FileSystem_LoadWholeFileEx(DAT_00844C4C, &DAT_00B0FC92);
    DAT_00B0FC8C = FileSystem_LoadWholeFileEx(DAT_00844C50, &DAT_00B0FC93);
    DAT_00B0FACC = FileSystem_LoadWholeFileEx(DAT_00844C54, &DAT_00B0FC94);
}

// FUNCTION: GAMEMD 0x72B0D0
void FUN_0072B0D0()
{
    ConvertClass_CreateFromFile(DAT_00844BA4, DAT_00B0FB64.Palette, DAT_00B0FB64.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA0, DAT_00B0FB6C.Palette, DAT_00B0FB6C.Convert);
    ConvertClass_CreateFromFile(DAT_00844B9C, DAT_00B0FB5C.Palette, DAT_00B0FB5C.Convert);
    ConvertClass_CreateFromFile(DAT_00844BA8, DAT_00B0FB74.Palette, DAT_00B0FB74.Convert);
}

// FUNCTION: GAMEMD 0x72B130
// Release the five blocks 0x72B060 loads.
void FUN_0072B130()
{
    if (DAT_00B0FC90) {
        WholeFileBlock* block = DAT_00B0FC80;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC90 = false;
    }
    DAT_00B0FC80 = 0;

    if (DAT_00B0FC91) {
        WholeFileBlock* block = DAT_00B0FC84;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC91 = false;
    }
    DAT_00B0FC84 = 0;

    if (DAT_00B0FC92) {
        WholeFileBlock* block = DAT_00B0FC88;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC92 = false;
    }
    DAT_00B0FC88 = 0;

    if (DAT_00B0FC93) {
        WholeFileBlock* block = DAT_00B0FC8C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC93 = false;
    }
    DAT_00B0FC8C = 0;

    if (DAT_00B0FC94) {
        WholeFileBlock* block = DAT_00B0FACC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC94 = false;
    }
    DAT_00B0FACC = 0;
}

// FUNCTION: GAMEMD 0x72B2F0
// File name for the screen width: one name at 640, another otherwise (caller 0x552F10 passes width, height and a
// third value that is not read; RET 4).
const char* FUN_0072B2F0(int width, int height, int value)
{
    const char* name = DAT_00844C34;
    if (width != 640) {
        name = DAT_00844C38;
    }
    return name;
}

// FUNCTION: GAMEMD 0x72B310
const char* FUN_0072B310(int width, int height, int value)
{
    const char* name = DAT_00844C3C;
    if (width != 640) {
        name = DAT_00844C40;
    }
    return name;
}

// FUNCTION: GAMEMD 0x72B330
ColorStruct_Res* FUN_0072B330()
{
    return DAT_00B0FB7C.Palette;
}

// FUNCTION: GAMEMD 0x72B350
ColorStruct_Res* FUN_0072B350()
{
    return DAT_00B0FB84.Palette;
}

// FUNCTION: GAMEMD 0x72B370
ColorStruct_Res* FUN_0072B370()
{
    return DAT_00B0FB8C.Palette;
}

// FUNCTION: GAMEMD 0x72B4F0
ColorStruct_Res* FUN_0072B4F0()
{
    return DAT_00B0FB94.Palette;
}

// FUNCTION: GAMEMD 0x72B510
ColorStruct_Res* FUN_0072B510()
{
    return DAT_00B0FB9C.Palette;
}

// FUNCTION: GAMEMD 0x72B530
// Switch the 0xB0FB94 palette set between its two sources. State 0xB0FD68 records what is loaded (0 none,
// 1 the per-index palette, 2 the 0xAC10C8 alternative); a load of the other kind releases both sets first, and the
// index (0..9) picks the palette file.
// PARTIAL: 18.7% positional, 97.5% aligned (198/203). Retail reloads ECX from 0xB0FBA0 at the end of the state-1
// release and jumps past the shared reloads; this spelling loads both at the join. Nested ifs and an explicit
// state reset in the state-2 arm scored the same or lower.
void FUN_0072B530(int index)
{
    if (DAT_00B0FD68 == 1 && DAT_00AC10C8 != 0) {
        ReleaseB0FB94Sets();
    }
    if (DAT_00B0FD68 == 2 && DAT_00AC10C8 == 0) {
        ReleaseB0FB94Sets();
    }
    if (DAT_00B0FB94.Convert == 0) {
        DAT_00B0FD68 = 0;
    } else if (DAT_00B0FD68 != 0) {
        return;
    }

    if (DAT_00AC10C8 != 0) {
        ConvertClass_CreateFromFile(DAT_00844BC4, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
        DAT_00B0FD68 = 2;
        return;
    }
    if (index == 0) {
        ConvertClass_CreateFromFile(DAT_00844C0C, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 1) {
        ConvertClass_CreateFromFile(DAT_00844C1C, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 2) {
        ConvertClass_CreateFromFile(DAT_00844C10, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 3) {
        ConvertClass_CreateFromFile(DAT_00844C14, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 4) {
        ConvertClass_CreateFromFile(DAT_00844C28, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 5) {
        ConvertClass_CreateFromFile(DAT_00844C20, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 6) {
        ConvertClass_CreateFromFile(DAT_00844C18, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 7) {
        ConvertClass_CreateFromFile(DAT_00844C2C, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 8) {
        ConvertClass_CreateFromFile(DAT_00844C24, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    } else if (index == 9) {
        ConvertClass_CreateFromFile(DAT_00844C30, DAT_00B0FB94.Palette, DAT_00B0FB94.Convert);
    }
    DAT_00B0FD68 = 1;
}

// FUNCTION: GAMEMD 0x72B8E0
void FUN_0072B8E0()
{
    if (!DAT_00B0FD5D) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FB54 = FileSystem_LoadWholeFileEx(DAT_00844DC4, &DAT_00B0FD5C);
        }
        ConvertClass_CreateFromFile(DAT_00844DC8, DAT_00B0FD60.Palette, DAT_00B0FD60.Convert);
        DAT_00B0FD5D = true;
    }
}

// FUNCTION: GAMEMD 0x72B930
void FUN_0072B930()
{
    if (DAT_00B0FD5D) {
        if (DAT_00B0FD5C) {
            WholeFileBlock* block = DAT_00B0FB54;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD5C = false;
        }
        DAT_00B0FB54 = 0;

        if (DAT_00B0FD60.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD60.Palette);
            DAT_00B0FD60.Palette = 0;
        }
        if (DAT_00B0FD60.Convert != 0) {
            DAT_00B0FD60.Convert->vf_0(1);
            DAT_00B0FD60.Convert = 0;
        }
    }
    DAT_00B0FD5D = false;
}

// FUNCTION: GAMEMD 0x72B9B0
bool FUN_0072B9B0()
{
    return DAT_00B0FD5D;
}

// FUNCTION: GAMEMD 0x72B9C0
ColorStruct_Res* FUN_0072B9C0()
{
    return DAT_00B0FD60.Palette;
}

// FUNCTION: GAMEMD 0x72BAC0
void FUN_0072BAC0()
{
    if (!DAT_00B0FD51) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FB2C = FileSystem_LoadWholeFileEx(DAT_00844DBC, &DAT_00B0FD50);
        }
        ConvertClass_CreateFromFile(DAT_00844DC0, DAT_00B0FD54.Palette, DAT_00B0FD54.Convert);
        DAT_00B0FD51 = true;
    }
}

// FUNCTION: GAMEMD 0x72BB10
void FUN_0072BB10()
{
    if (DAT_00B0FD51) {
        if (DAT_00B0FD50) {
            WholeFileBlock* block = DAT_00B0FB2C;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD50 = false;
        }
        DAT_00B0FB2C = 0;

        if (DAT_00B0FD54.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD54.Palette);
            DAT_00B0FD54.Palette = 0;
        }
        if (DAT_00B0FD54.Convert != 0) {
            DAT_00B0FD54.Convert->vf_0(1);
            DAT_00B0FD54.Convert = 0;
        }
    }
    DAT_00B0FD51 = false;
}

// FUNCTION: GAMEMD 0x72BB90
bool FUN_0072BB90()
{
    return DAT_00B0FD51;
}

// FUNCTION: GAMEMD 0x72BBA0
ColorStruct_Res* FUN_0072BBA0()
{
    return DAT_00B0FD54.Palette;
}

// FUNCTION: GAMEMD 0x72BBC0
void FUN_0072BBC0()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FB2C = FileSystem_LoadWholeFileEx(DAT_00844DBC, &DAT_00B0FD50);
    }
}

// FUNCTION: GAMEMD 0x72BBF0
void FUN_0072BBF0()
{
    ConvertClass_CreateFromFile(DAT_00844DC0, DAT_00B0FD54.Palette, DAT_00B0FD54.Convert);
}

// FUNCTION: GAMEMD 0x72BC10
void FUN_0072BC10()
{
    if (DAT_00B0FD50) {
        WholeFileBlock* block = DAT_00B0FB2C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD50 = false;
    }
    DAT_00B0FB2C = 0;
}

// FUNCTION: GAMEMD 0x72BC60
void FUN_0072BC60()
{
    if (DAT_00B0FD54.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD54.Palette);
        DAT_00B0FD54.Palette = 0;
    }
    if (DAT_00B0FD54.Convert != 0) {
        DAT_00B0FD54.Convert->vf_0(1);
        DAT_00B0FD54.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72BD70
bool FUN_0072BD70()
{
    return DAT_00B0FD44.Loaded;
}

// FUNCTION: GAMEMD 0x72BD80
ColorStruct_Res* FUN_0072BD80()
{
    return DAT_00B0FD44.Set.Palette;
}

// FUNCTION: GAMEMD 0x72BDA0
void FUN_0072BDA0()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA98 = FileSystem_LoadWholeFileEx(DAT_00844DB4, &DAT_00B0FD44.Allocated);
    }
}

// FUNCTION: GAMEMD 0x72BDD0
void FUN_0072BDD0()
{
    ConvertClass_CreateFromFile(DAT_00844DB8, DAT_00B0FD44.Set.Palette, DAT_00B0FD44.Set.Convert);
}

// FUNCTION: GAMEMD 0x72BDF0
void FUN_0072BDF0()
{
    if (DAT_00B0FD44.Allocated) {
        WholeFileBlock* block = DAT_00B0FA98;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD44.Allocated = false;
    }
    DAT_00B0FA98 = 0;
}

// FUNCTION: GAMEMD 0x72BE40
void FUN_0072BE40()
{
    if (DAT_00B0FD44.Set.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD44.Set.Palette);
        DAT_00B0FD44.Set.Palette = 0;
    }
    if (DAT_00B0FD44.Set.Convert != 0) {
        DAT_00B0FD44.Set.Convert->vf_0(1);
        DAT_00B0FD44.Set.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72BF50
bool FUN_0072BF50()
{
    return DAT_00B0FD38.Loaded;
}

// FUNCTION: GAMEMD 0x72BF60
ColorStruct_Res* FUN_0072BF60()
{
    return DAT_00B0FD38.Set.Palette;
}

// FUNCTION: GAMEMD 0x72BF80
void FUN_0072BF80()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA9C = FileSystem_LoadWholeFileEx(DAT_00844DAC, &DAT_00B0FD38.Allocated);
    }
}

// FUNCTION: GAMEMD 0x72BFB0
void FUN_0072BFB0()
{
    ConvertClass_CreateFromFile(DAT_00844DB0, DAT_00B0FD38.Set.Palette, DAT_00B0FD38.Set.Convert);
}

// FUNCTION: GAMEMD 0x72BFD0
void FUN_0072BFD0()
{
    if (DAT_00B0FD38.Allocated) {
        WholeFileBlock* block = DAT_00B0FA9C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD38.Allocated = false;
    }
    DAT_00B0FA9C = 0;
}

// FUNCTION: GAMEMD 0x72C020
void FUN_0072C020()
{
    if (DAT_00B0FD38.Set.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD38.Set.Palette);
        DAT_00B0FD38.Set.Palette = 0;
    }
    if (DAT_00B0FD38.Set.Convert != 0) {
        DAT_00B0FD38.Set.Convert->vf_0(1);
        DAT_00B0FD38.Set.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C060
void FUN_0072C060()
{
    if (!DAT_00B0FD2D) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FA4C = FileSystem_LoadWholeFileEx(DAT_00844DA4, &DAT_00B0FD2C);
        }
        ConvertClass_CreateFromFile(DAT_00844DA8, DAT_00B0FD30.Palette, DAT_00B0FD30.Convert);
        DAT_00B0FD2D = true;
    }
}

// FUNCTION: GAMEMD 0x72C0B0
void FUN_0072C0B0()
{
    if (DAT_00B0FD2D) {
        if (DAT_00B0FD2C) {
            WholeFileBlock* block = DAT_00B0FA4C;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD2C = false;
        }
        DAT_00B0FA4C = 0;

        if (DAT_00B0FD30.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD30.Palette);
            DAT_00B0FD30.Palette = 0;
        }
        if (DAT_00B0FD30.Convert != 0) {
            DAT_00B0FD30.Convert->vf_0(1);
            DAT_00B0FD30.Convert = 0;
        }
    }
    DAT_00B0FD2D = false;
}

// FUNCTION: GAMEMD 0x72C130
bool FUN_0072C130()
{
    return DAT_00B0FD2D;
}

// FUNCTION: GAMEMD 0x72C140
ColorStruct_Res* FUN_0072C140()
{
    return DAT_00B0FD30.Palette;
}

// FUNCTION: GAMEMD 0x72C160
void FUN_0072C160()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA4C = FileSystem_LoadWholeFileEx(DAT_00844DA4, &DAT_00B0FD2C);
    }
}

// FUNCTION: GAMEMD 0x72C190
void FUN_0072C190()
{
    ConvertClass_CreateFromFile(DAT_00844DA8, DAT_00B0FD30.Palette, DAT_00B0FD30.Convert);
}

// FUNCTION: GAMEMD 0x72C1B0
void FUN_0072C1B0()
{
    if (DAT_00B0FD2C) {
        WholeFileBlock* block = DAT_00B0FA4C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD2C = false;
    }
    DAT_00B0FA4C = 0;
}

// FUNCTION: GAMEMD 0x72C200
void FUN_0072C200()
{
    if (DAT_00B0FD30.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD30.Palette);
        DAT_00B0FD30.Palette = 0;
    }
    if (DAT_00B0FD30.Convert != 0) {
        DAT_00B0FD30.Convert->vf_0(1);
        DAT_00B0FD30.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C240
void FUN_0072C240()
{
    if (!DAT_00B0FD21) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FA30 = FileSystem_LoadWholeFileEx(DAT_00844D9C, &DAT_00B0FD20);
        }
        ConvertClass_CreateFromFile(DAT_00844DA0, DAT_00B0FD24.Palette, DAT_00B0FD24.Convert);
        DAT_00B0FD21 = true;
    }
}

// FUNCTION: GAMEMD 0x72C290
void FUN_0072C290()
{
    if (DAT_00B0FD21) {
        if (DAT_00B0FD20) {
            WholeFileBlock* block = DAT_00B0FA30;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD20 = false;
        }
        DAT_00B0FA30 = 0;

        if (DAT_00B0FD24.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD24.Palette);
            DAT_00B0FD24.Palette = 0;
        }
        if (DAT_00B0FD24.Convert != 0) {
            DAT_00B0FD24.Convert->vf_0(1);
            DAT_00B0FD24.Convert = 0;
        }
    }
    DAT_00B0FD21 = false;
}

// FUNCTION: GAMEMD 0x72C310
bool FUN_0072C310()
{
    return DAT_00B0FD21;
}

// FUNCTION: GAMEMD 0x72C320
ColorStruct_Res* FUN_0072C320()
{
    return DAT_00B0FD24.Palette;
}

// FUNCTION: GAMEMD 0x72C340
void FUN_0072C340()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA30 = FileSystem_LoadWholeFileEx(DAT_00844D9C, &DAT_00B0FD20);
    }
}

// FUNCTION: GAMEMD 0x72C370
void FUN_0072C370()
{
    ConvertClass_CreateFromFile(DAT_00844DA0, DAT_00B0FD24.Palette, DAT_00B0FD24.Convert);
}

// FUNCTION: GAMEMD 0x72C390
void FUN_0072C390()
{
    if (DAT_00B0FD20) {
        WholeFileBlock* block = DAT_00B0FA30;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD20 = false;
    }
    DAT_00B0FA30 = 0;
}

// FUNCTION: GAMEMD 0x72C3E0
void FUN_0072C3E0()
{
    if (DAT_00B0FD24.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD24.Palette);
        DAT_00B0FD24.Palette = 0;
    }
    if (DAT_00B0FD24.Convert != 0) {
        DAT_00B0FD24.Convert->vf_0(1);
        DAT_00B0FD24.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C420
void FUN_0072C420()
{
    if (!DAT_00B0FD15) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FA64 = FileSystem_LoadWholeFileEx(DAT_00844D94, &DAT_00B0FD14);
        }
        ConvertClass_CreateFromFile(DAT_00844D98, DAT_00B0FD18.Palette, DAT_00B0FD18.Convert);
        DAT_00B0FD15 = true;
    }
}

// FUNCTION: GAMEMD 0x72C470
void FUN_0072C470()
{
    if (DAT_00B0FD15) {
        if (DAT_00B0FD14) {
            WholeFileBlock* block = DAT_00B0FA64;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD14 = false;
        }
        DAT_00B0FA64 = 0;

        if (DAT_00B0FD18.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD18.Palette);
            DAT_00B0FD18.Palette = 0;
        }
        if (DAT_00B0FD18.Convert != 0) {
            DAT_00B0FD18.Convert->vf_0(1);
            DAT_00B0FD18.Convert = 0;
        }
    }
    DAT_00B0FD15 = false;
}

// FUNCTION: GAMEMD 0x72C4F0
bool FUN_0072C4F0()
{
    return DAT_00B0FD15;
}

// FUNCTION: GAMEMD 0x72C500
ColorStruct_Res* FUN_0072C500()
{
    return DAT_00B0FD18.Palette;
}

// FUNCTION: GAMEMD 0x72C520
void FUN_0072C520()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA64 = FileSystem_LoadWholeFileEx(DAT_00844D94, &DAT_00B0FD14);
    }
}

// FUNCTION: GAMEMD 0x72C550
void FUN_0072C550()
{
    ConvertClass_CreateFromFile(DAT_00844D98, DAT_00B0FD18.Palette, DAT_00B0FD18.Convert);
}

// FUNCTION: GAMEMD 0x72C570
void FUN_0072C570()
{
    if (DAT_00B0FD14) {
        WholeFileBlock* block = DAT_00B0FA64;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD14 = false;
    }
    DAT_00B0FA64 = 0;
}

// FUNCTION: GAMEMD 0x72C5C0
void FUN_0072C5C0()
{
    if (DAT_00B0FD18.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD18.Palette);
        DAT_00B0FD18.Palette = 0;
    }
    if (DAT_00B0FD18.Convert != 0) {
        DAT_00B0FD18.Convert->vf_0(1);
        DAT_00B0FD18.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C600
void FUN_0072C600()
{
    if (!DAT_00B0FD09) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FB0C = FileSystem_LoadWholeFileEx(DAT_00844D8C, &DAT_00B0FD08);
        }
        ConvertClass_CreateFromFile(DAT_00844D90, DAT_00B0FD0C.Palette, DAT_00B0FD0C.Convert);
        DAT_00B0FD09 = true;
    }
}

// FUNCTION: GAMEMD 0x72C650
void FUN_0072C650()
{
    if (DAT_00B0FD09) {
        if (DAT_00B0FD08) {
            WholeFileBlock* block = DAT_00B0FB0C;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD08 = false;
        }
        DAT_00B0FB0C = 0;

        if (DAT_00B0FD0C.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD0C.Palette);
            DAT_00B0FD0C.Palette = 0;
        }
        if (DAT_00B0FD0C.Convert != 0) {
            DAT_00B0FD0C.Convert->vf_0(1);
            DAT_00B0FD0C.Convert = 0;
        }
    }
    DAT_00B0FD09 = false;
}

// FUNCTION: GAMEMD 0x72C6D0
bool FUN_0072C6D0()
{
    return DAT_00B0FD09;
}

// FUNCTION: GAMEMD 0x72C6E0
ColorStruct_Res* FUN_0072C6E0()
{
    return DAT_00B0FD0C.Palette;
}

// FUNCTION: GAMEMD 0x72C700
void FUN_0072C700()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FB0C = FileSystem_LoadWholeFileEx(DAT_00844D8C, &DAT_00B0FD08);
    }
}

// FUNCTION: GAMEMD 0x72C730
void FUN_0072C730()
{
    ConvertClass_CreateFromFile(DAT_00844D90, DAT_00B0FD0C.Palette, DAT_00B0FD0C.Convert);
}

// FUNCTION: GAMEMD 0x72C750
void FUN_0072C750()
{
    if (DAT_00B0FD08) {
        WholeFileBlock* block = DAT_00B0FB0C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD08 = false;
    }
    DAT_00B0FB0C = 0;
}

// FUNCTION: GAMEMD 0x72C7A0
void FUN_0072C7A0()
{
    if (DAT_00B0FD0C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD0C.Palette);
        DAT_00B0FD0C.Palette = 0;
    }
    if (DAT_00B0FD0C.Convert != 0) {
        DAT_00B0FD0C.Convert->vf_0(1);
        DAT_00B0FD0C.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C7E0
void FUN_0072C7E0()
{
    if (!DAT_00B0FCFD) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0F9E8 = FileSystem_LoadWholeFileEx(DAT_00844D84, &DAT_00B0FCFC);
        }
        ConvertClass_CreateFromFile(DAT_00844D88, DAT_00B0FD00.Palette, DAT_00B0FD00.Convert);
        DAT_00B0FCFD = true;
    }
}

// FUNCTION: GAMEMD 0x72C830
void FUN_0072C830()
{
    if (DAT_00B0FCFD) {
        if (DAT_00B0FCFC) {
            WholeFileBlock* block = DAT_00B0F9E8;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FCFC = false;
        }
        DAT_00B0F9E8 = 0;

        if (DAT_00B0FD00.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD00.Palette);
            DAT_00B0FD00.Palette = 0;
        }
        if (DAT_00B0FD00.Convert != 0) {
            DAT_00B0FD00.Convert->vf_0(1);
            DAT_00B0FD00.Convert = 0;
        }
    }
    DAT_00B0FCFD = false;
}

// FUNCTION: GAMEMD 0x72C8B0
bool FUN_0072C8B0()
{
    return DAT_00B0FCFD;
}

// FUNCTION: GAMEMD 0x72C8C0
ColorStruct_Res* FUN_0072C8C0()
{
    return DAT_00B0FD00.Palette;
}

// FUNCTION: GAMEMD 0x72C8E0
void FUN_0072C8E0()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0F9E8 = FileSystem_LoadWholeFileEx(DAT_00844D84, &DAT_00B0FCFC);
    }
}

// FUNCTION: GAMEMD 0x72C910
void FUN_0072C910()
{
    ConvertClass_CreateFromFile(DAT_00844D88, DAT_00B0FD00.Palette, DAT_00B0FD00.Convert);
}

// FUNCTION: GAMEMD 0x72C930
void FUN_0072C930()
{
    if (DAT_00B0FCFC) {
        WholeFileBlock* block = DAT_00B0F9E8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCFC = false;
    }
    DAT_00B0F9E8 = 0;
}

// FUNCTION: GAMEMD 0x72C980
void FUN_0072C980()
{
    if (DAT_00B0FD00.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD00.Palette);
        DAT_00B0FD00.Palette = 0;
    }
    if (DAT_00B0FD00.Convert != 0) {
        DAT_00B0FD00.Convert->vf_0(1);
        DAT_00B0FD00.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72C9C0
void FUN_0072C9C0()
{
    if (!DAT_00B0FCF1) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FA60 = FileSystem_LoadWholeFileEx(DAT_00844D7C, &DAT_00B0FCF0);
        }
        ConvertClass_CreateFromFile(DAT_00844D80, DAT_00B0FCF4.Palette, DAT_00B0FCF4.Convert);
        DAT_00B0FCF1 = true;
    }
}

// FUNCTION: GAMEMD 0x72CA10
void FUN_0072CA10()
{
    if (DAT_00B0FCF1) {
        if (DAT_00B0FCF0) {
            WholeFileBlock* block = DAT_00B0FA60;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FCF0 = false;
        }
        DAT_00B0FA60 = 0;

        if (DAT_00B0FCF4.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FCF4.Palette);
            DAT_00B0FCF4.Palette = 0;
        }
        if (DAT_00B0FCF4.Convert != 0) {
            DAT_00B0FCF4.Convert->vf_0(1);
            DAT_00B0FCF4.Convert = 0;
        }
    }
    DAT_00B0FCF1 = false;
}

// FUNCTION: GAMEMD 0x72CA90
bool FUN_0072CA90()
{
    return DAT_00B0FCF1;
}

// FUNCTION: GAMEMD 0x72CAA0
ColorStruct_Res* FUN_0072CAA0()
{
    return DAT_00B0FCF4.Palette;
}

// FUNCTION: GAMEMD 0x72CBA0
// The WAITCYLO screen: unlike its neighbours it loads its SHP at every resolution and names its files through
// in-image string arrays rather than through name pointers.
void FUN_0072CBA0()
{
    if (!DAT_00B0FC7C) {
        DAT_00B0FAD0 = FileSystem_LoadWholeFileEx(DAT_00845540, &DAT_00B0FC73);
        ConvertClass_CreateFromFile(DAT_00845530, DAT_00B0FC74.Palette, DAT_00B0FC74.Convert);
        DAT_00B0FC7C = true;
    }
}

// FUNCTION: GAMEMD 0x72CBE0
void FUN_0072CBE0()
{
    if (DAT_00B0FC7C) {
        if (DAT_00B0FC73) {
            WholeFileBlock* block = DAT_00B0FAD0;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FC73 = false;
        }
        DAT_00B0FAD0 = 0;

        if (DAT_00B0FC74.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FC74.Palette);
            DAT_00B0FC74.Palette = 0;
        }
        if (DAT_00B0FC74.Convert != 0) {
            DAT_00B0FC74.Convert->vf_0(1);
            DAT_00B0FC74.Convert = 0;
        }
    }
    DAT_00B0FC7C = false;
}

// FUNCTION: GAMEMD 0x72CC60
bool FUN_0072CC60()
{
    return DAT_00B0FC7C;
}

// FUNCTION: GAMEMD 0x72CC70
ColorStruct_Res* FUN_0072CC70()
{
    return DAT_00B0FC74.Palette;
}

// FUNCTION: GAMEMD 0x72CC90
void FUN_0072CC90()
{
    DAT_00B0FAD0 = FileSystem_LoadWholeFileEx(DAT_00845540, &DAT_00B0FC73);
}

// FUNCTION: GAMEMD 0x72CCB0
void FUN_0072CCB0()
{
    ConvertClass_CreateFromFile(DAT_00845530, DAT_00B0FC74.Palette, DAT_00B0FC74.Convert);
}

// FUNCTION: GAMEMD 0x72CCD0
void FUN_0072CCD0()
{
    if (DAT_00B0FC73) {
        WholeFileBlock* block = DAT_00B0FAD0;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC73 = false;
    }
    DAT_00B0FAD0 = 0;
}

// FUNCTION: GAMEMD 0x72CD20
void FUN_0072CD20()
{
    if (DAT_00B0FC74.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FC74.Palette);
        DAT_00B0FC74.Palette = 0;
    }
    if (DAT_00B0FC74.Convert != 0) {
        DAT_00B0FC74.Convert->vf_0(1);
        DAT_00B0FC74.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72CD60
void FUN_0072CD60()
{
    if (!DAT_00B0FCE5) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FAAC = FileSystem_LoadWholeFileEx(DAT_00844D74, &DAT_00B0FCE4);
        }
        ConvertClass_CreateFromFile(DAT_00844D78, DAT_00B0FCE8.Palette, DAT_00B0FCE8.Convert);
        DAT_00B0FCE5 = true;
    }
}

// FUNCTION: GAMEMD 0x72CDB0
void FUN_0072CDB0()
{
    if (DAT_00B0FCE5) {
        if (DAT_00B0FCE4) {
            WholeFileBlock* block = DAT_00B0FAAC;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FCE4 = false;
        }
        DAT_00B0FAAC = 0;

        if (DAT_00B0FCE8.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FCE8.Palette);
            DAT_00B0FCE8.Palette = 0;
        }
        if (DAT_00B0FCE8.Convert != 0) {
            DAT_00B0FCE8.Convert->vf_0(1);
            DAT_00B0FCE8.Convert = 0;
        }
    }
    DAT_00B0FCE5 = false;
}

// FUNCTION: GAMEMD 0x72CE30
bool FUN_0072CE30()
{
    return DAT_00B0FCE5;
}

// FUNCTION: GAMEMD 0x72CE40
ColorStruct_Res* FUN_0072CE40()
{
    return DAT_00B0FCE8.Palette;
}

// FUNCTION: GAMEMD 0x72CE60
void FUN_0072CE60()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FAAC = FileSystem_LoadWholeFileEx(DAT_00844D74, &DAT_00B0FCE4);
    }
}

// FUNCTION: GAMEMD 0x72CE90
void FUN_0072CE90()
{
    ConvertClass_CreateFromFile(DAT_00844D78, DAT_00B0FCE8.Palette, DAT_00B0FCE8.Convert);
}

// FUNCTION: GAMEMD 0x72CEB0
void FUN_0072CEB0()
{
    if (DAT_00B0FCE4) {
        WholeFileBlock* block = DAT_00B0FAAC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCE4 = false;
    }
    DAT_00B0FAAC = 0;
}

// FUNCTION: GAMEMD 0x72CF00
void FUN_0072CF00()
{
    if (DAT_00B0FCE8.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCE8.Palette);
        DAT_00B0FCE8.Palette = 0;
    }
    if (DAT_00B0FCE8.Convert != 0) {
        DAT_00B0FCE8.Convert->vf_0(1);
        DAT_00B0FCE8.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72CF40
void FUN_0072CF40()
{
    if (!DAT_00B0FCD9) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FA18 = FileSystem_LoadWholeFileEx(DAT_00844D6C, &DAT_00B0FCD8);
        }
        ConvertClass_CreateFromFile(DAT_00844D70, DAT_00B0FCDC.Palette, DAT_00B0FCDC.Convert);
        DAT_00B0FCD9 = true;
    }
}

// FUNCTION: GAMEMD 0x72CF90
void FUN_0072CF90()
{
    if (DAT_00B0FCD9) {
        if (DAT_00B0FCD8) {
            WholeFileBlock* block = DAT_00B0FA18;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FCD8 = false;
        }
        DAT_00B0FA18 = 0;

        if (DAT_00B0FCDC.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FCDC.Palette);
            DAT_00B0FCDC.Palette = 0;
        }
        if (DAT_00B0FCDC.Convert != 0) {
            DAT_00B0FCDC.Convert->vf_0(1);
            DAT_00B0FCDC.Convert = 0;
        }
    }
    DAT_00B0FCD9 = false;
}

// FUNCTION: GAMEMD 0x72D010
bool FUN_0072D010()
{
    return DAT_00B0FCD9;
}

// FUNCTION: GAMEMD 0x72D020
ColorStruct_Res* FUN_0072D020()
{
    return DAT_00B0FCDC.Palette;
}

// FUNCTION: GAMEMD 0x72D040
void FUN_0072D040()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA18 = FileSystem_LoadWholeFileEx(DAT_00844D6C, &DAT_00B0FCD8);
    }
}

// FUNCTION: GAMEMD 0x72D070
void FUN_0072D070()
{
    ConvertClass_CreateFromFile(DAT_00844D70, DAT_00B0FCDC.Palette, DAT_00B0FCDC.Convert);
}

// FUNCTION: GAMEMD 0x72D090
void FUN_0072D090()
{
    if (DAT_00B0FCD8) {
        WholeFileBlock* block = DAT_00B0FA18;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCD8 = false;
    }
    DAT_00B0FA18 = 0;
}

// FUNCTION: GAMEMD 0x72D0E0
void FUN_0072D0E0()
{
    if (DAT_00B0FCDC.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCDC.Palette);
        DAT_00B0FCDC.Palette = 0;
    }
    if (DAT_00B0FCDC.Convert != 0) {
        DAT_00B0FCDC.Convert->vf_0(1);
        DAT_00B0FCDC.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72D120
void FUN_0072D120()
{
    if (!DAT_00B0FCCE) {
        if (DAT_008A00A4 == 800) {
            DAT_00B0FAB8 = FileSystem_LoadWholeFileEx(DAT_00844D64, &DAT_00B0FCCD);
        }
        ConvertClass_CreateFromFile(DAT_00844D68, DAT_00B0FCD0.Palette, DAT_00B0FCD0.Convert);
        DAT_00B0FCCE = true;
    }
}

// FUNCTION: GAMEMD 0x72D170
void FUN_0072D170()
{
    if (DAT_00B0FCCE) {
        if (DAT_00B0FCCD) {
            WholeFileBlock* block = DAT_00B0FAB8;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FCCD = false;
        }
        DAT_00B0FAB8 = 0;

        if (DAT_00B0FCD0.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FCD0.Palette);
            DAT_00B0FCD0.Palette = 0;
        }
        if (DAT_00B0FCD0.Convert != 0) {
            DAT_00B0FCD0.Convert->vf_0(1);
            DAT_00B0FCD0.Convert = 0;
        }
    }
    DAT_00B0FCCE = false;
}

// FUNCTION: GAMEMD 0x72D1F0
bool FUN_0072D1F0()
{
    return DAT_00B0FCCE;
}

// FUNCTION: GAMEMD 0x72D200
ColorStruct_Res* FUN_0072D200()
{
    return DAT_00B0FCD0.Palette;
}

// FUNCTION: GAMEMD 0x72D220
void FUN_0072D220()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FAB8 = FileSystem_LoadWholeFileEx(DAT_00844D64, &DAT_00B0FCCD);
    }
}

// FUNCTION: GAMEMD 0x72D250
void FUN_0072D250()
{
    ConvertClass_CreateFromFile(DAT_00844D68, DAT_00B0FCD0.Palette, DAT_00B0FCD0.Convert);
}

// FUNCTION: GAMEMD 0x72D270
void FUN_0072D270()
{
    if (DAT_00B0FCCD) {
        WholeFileBlock* block = DAT_00B0FAB8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCCD = false;
    }
    DAT_00B0FAB8 = 0;
}

// FUNCTION: GAMEMD 0x72D2C0
void FUN_0072D2C0()
{
    if (DAT_00B0FCD0.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCD0.Palette);
        DAT_00B0FCD0.Palette = 0;
    }
    if (DAT_00B0FCD0.Convert != 0) {
        DAT_00B0FCD0.Convert->vf_0(1);
        DAT_00B0FCD0.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72D300
// Load the side-dependent multiplayer screen once (guard 0xB0FBAC): its blocks via 0x72D460, then its palette set.
void FUN_0072D300(int sideIndex)
{
    if (!DAT_00B0FBAC) {
        FUN_0072D460(sideIndex);
        const char* name;
        if (sideIndex == 0) {
            name = DAT_00844BC8;
        } else if (sideIndex == 1) {
            name = DAT_00844BCC;
        } else {
            name = DAT_00844BD0;
        }
        ConvertClass_CreateFromFile(name, DAT_00B0FBA4.Palette, DAT_00B0FBA4.Convert);
        DAT_00B0FBAC = true;
    }
}

// FUNCTION: GAMEMD 0x72D350
void FUN_0072D350()
{
    if (DAT_00B0FBAC) {
        DAT_00B0FBAC = false;

        if (DAT_00B0FC70) {
            WholeFileBlock* block = DAT_00B0FB34;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FC70 = false;
        }
        DAT_00B0FB34 = 0;

        if (DAT_00B0FC71) {
            WholeFileBlock* block = DAT_00B0FB00;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FC71 = false;
        }
        DAT_00B0FB00 = 0;

        if (DAT_00B0FC72) {
            WholeFileBlock* block = DAT_00B0FB30;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FC72 = false;
        }
        DAT_00B0FB30 = 0;

        if (DAT_00B0FBA4.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FBA4.Palette);
            DAT_00B0FBA4.Palette = 0;
        }
        if (DAT_00B0FBA4.Convert != 0) {
            DAT_00B0FBA4.Convert->vf_0(1);
            DAT_00B0FBA4.Convert = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x72D430
bool FUN_0072D430()
{
    return DAT_00B0FBAC;
}

// FUNCTION: GAMEMD 0x72D440
ColorStruct_Res* FUN_0072D440()
{
    return DAT_00B0FBA4.Palette;
}

// FUNCTION: GAMEMD 0x72D460
// Load the three side- and resolution-dependent multiplayer blocks.
void FUN_0072D460(int sideIndex)
{
    if (sideIndex == 0) {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C58, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C60, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C68, &DAT_00B0FC72);
        } else {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C5C, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C64, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C6C, &DAT_00B0FC72);
        }
    } else if (sideIndex == 1) {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C70, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C78, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C80, &DAT_00B0FC72);
        } else {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C74, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C7C, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C84, &DAT_00B0FC72);
        }
    } else {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C88, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C90, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C98, &DAT_00B0FC72);
        } else {
            DAT_00B0FB34 = FileSystem_LoadWholeFileEx(DAT_00844C8C, &DAT_00B0FC70);
            DAT_00B0FB00 = FileSystem_LoadWholeFileEx(DAT_00844C94, &DAT_00B0FC71);
            DAT_00B0FB30 = FileSystem_LoadWholeFileEx(DAT_00844C9C, &DAT_00B0FC72);
        }
    }
}

// FUNCTION: GAMEMD 0x72D610
void FUN_0072D610(int sideIndex)
{
    const char* name;
    if (sideIndex == 0) {
        name = DAT_00844BC8;
    } else if (sideIndex == 1) {
        name = DAT_00844BCC;
    } else {
        name = DAT_00844BD0;
    }
    ConvertClass_CreateFromFile(name, DAT_00B0FBA4.Palette, DAT_00B0FBA4.Convert);
}

// FUNCTION: GAMEMD 0x72D650
// Release the three blocks 0x72D460 loads.
void FUN_0072D650()
{
    if (DAT_00B0FC70) {
        WholeFileBlock* block = DAT_00B0FB34;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC70 = false;
    }
    DAT_00B0FB34 = 0;

    if (DAT_00B0FC71) {
        WholeFileBlock* block = DAT_00B0FB00;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC71 = false;
    }
    DAT_00B0FB00 = 0;

    if (DAT_00B0FC72) {
        WholeFileBlock* block = DAT_00B0FB30;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC72 = false;
    }
    DAT_00B0FB30 = 0;
}

// FUNCTION: GAMEMD 0x72D6F0
void FUN_0072D6F0()
{
    if (DAT_00B0FBA4.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBA4.Palette);
        DAT_00B0FBA4.Palette = 0;
    }
    if (DAT_00B0FBA4.Convert != 0) {
        DAT_00B0FBA4.Convert->vf_0(1);
        DAT_00B0FBA4.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72D800
bool FUN_0072D800()
{
    return DAT_00B0FBB8;
}

// FUNCTION: GAMEMD 0x72D810
ColorStruct_Res* FUN_0072D810()
{
    return DAT_00B0FBB0.Palette;
}

// FUNCTION: GAMEMD 0x72D830
// Load the multiplayer screen's side- and resolution-dependent block (called by 0x72D730 with the side in ECX).
void FUN_0072D830(int sideIndex)
{
    if (sideIndex == 0) {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CA0, &DAT_00B0FC7D);
        } else {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CA4, &DAT_00B0FC7D);
        }
    } else if (sideIndex == 1) {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CA8, &DAT_00B0FC7D);
        } else {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CAC, &DAT_00B0FC7D);
        }
    } else {
        if (DAT_008A00A4 == 640) {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CB0, &DAT_00B0FC7D);
        } else {
            DAT_00B0FB1C = FileSystem_LoadWholeFileEx(DAT_00844CB4, &DAT_00B0FC7D);
        }
    }
}

// FUNCTION: GAMEMD 0x72D8D0
void FUN_0072D8D0(int sideIndex)
{
    const char* name;
    if (sideIndex == 0) {
        name = DAT_00844BD4;
    } else if (sideIndex == 1) {
        name = DAT_00844BD8;
    } else {
        name = DAT_00844BDC;
    }
    ConvertClass_CreateFromFile(name, DAT_00B0FBB0.Palette, DAT_00B0FBB0.Convert);
}

// FUNCTION: GAMEMD 0x72D910
void FUN_0072D910()
{
    if (DAT_00B0FC7D) {
        WholeFileBlock* block = DAT_00B0FB1C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC7D = false;
    }
    DAT_00B0FB1C = 0;
}

// FUNCTION: GAMEMD 0x72D960
void FUN_0072D960()
{
    if (DAT_00B0FBB0.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBB0.Palette);
        DAT_00B0FBB0.Palette = 0;
    }
    if (DAT_00B0FBB0.Convert != 0) {
        DAT_00B0FBB0.Convert->vf_0(1);
        DAT_00B0FBB0.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72DBC0
// Load the four palette sets of the fourth full-screen menu.
void FUN_0072DBC0()
{
    ConvertClass_CreateFromFile(DAT_00844BE0, DAT_00B0FBBC.Palette, DAT_00B0FBBC.Convert);
    ConvertClass_CreateFromFile(DAT_00844D50, DAT_00B0FCB0.Palette, DAT_00B0FCB0.Convert);
    ConvertClass_CreateFromFile(DAT_00844D58, DAT_00B0FCB8.Palette, DAT_00B0FCB8.Convert);
    ConvertClass_CreateFromFile(DAT_00844D60, DAT_00B0FCC0.Palette, DAT_00B0FCC0.Convert);
}
