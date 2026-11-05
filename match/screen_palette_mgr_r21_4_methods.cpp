// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x72D9A0, 0x72DC20,
//   0x72DEF0, 0x72E1B0, 0x72EB50, 0x72F1D0, 0x72F350, 0x72F270, 0x730400, 0x730530 and 0x730670. Every instruction, offset and global below was read off the
//   retail disassembly with the local Ghidra CLI.
//
// Address index:
//   0x72D9A0  FUN_0072D9A0
//   0x72DC20  FUN_0072DC20
//   0x72DEF0  FUN_0072DEF0
//   0x72E1B0  FUN_0072E1B0
//   0x72EB50  FUN_0072EB50
//   0x72F1D0  FUN_0072F1D0
//   0x72F350  FUN_0072F350
//   0x72F270  FUN_0072F270
//   0x730400  FUN_00730400
//   0x730530  FUN_00730530
//   0x730670  FUN_00730670

#include "screen_palette_mgr_methods.h"
#include "scenario_class_methods.h"
#include "screen_palette_mgr_r21_4_methods.h"
#include "scenario_session_globals.h"
#include "palette_screen_globals.h"
#include "_rt/crt_allocator.h"




// FUNCTION: GAMEMD 0x5B4270 (decl; reloc) -- unload the named resource.
void FUN_005B4270(const char* name);


void FUN_0072EC70(int width, int height);
void FUN_0072EF60();
void FUN_0072EB50();
void FUN_00534E50();

// FUNCTION: GAMEMD 0x534DE0 (decl; reloc)
void FUN_00534DE0();


void FUN_0072DB00();

// FUNCTION: GAMEMD 0x72D9A0
//
// Load the four menu file blocks, then the fourth menu palette set and the
// three full-screen-menu palette sets.
void FUN_0072D9A0()
{
    FUN_0072DB00();
    ConvertClass_CreateFromFile(DAT_00844BE0, DAT_00B0FBBC.Palette, DAT_00B0FBBC.Convert);
    ConvertClass_CreateFromFile(DAT_00844D50, DAT_00B0FCB0.Palette, DAT_00B0FCB0.Convert);
    ConvertClass_CreateFromFile(DAT_00844D58, DAT_00B0FCB8.Palette, DAT_00B0FCB8.Convert);
    ConvertClass_CreateFromFile(DAT_00844D60, DAT_00B0FCC0.Palette, DAT_00B0FCC0.Convert);
}

// Load the four menu file blocks. At 640 wide the first set of file names is
// used, otherwise the second; each load reports through the allocated flag
// that sits beside the file block's owner. Retail expands this inline in
// 0x72D9A0 and also keeps an uncalled out-of-line copy at 0x72DB00.
// FUNCTION: GAMEMD 0x72DB00
void FUN_0072DB00()
{
    if (DAT_008A00A4 == 0x280) {
        DAT_00B0FB48 = FileSystem_LoadWholeFileEx(DAT_00844CB8, &DAT_00B0FCC8);
        DAT_00B0FB10 = FileSystem_LoadWholeFileEx(DAT_00844CC4, &DAT_00B0FCCA);
        DAT_00B0F9F8 = FileSystem_LoadWholeFileEx(DAT_00844CC8, &DAT_00B0FCCB);
        DAT_00B0FA6C = FileSystem_LoadWholeFileEx(DAT_00844CD0, &DAT_00B0FCCC);
    } else {
        DAT_00B0FB48 = FileSystem_LoadWholeFileEx(DAT_00844D4C, &DAT_00B0FCC8);
        DAT_00B0FB10 = FileSystem_LoadWholeFileEx(DAT_00844D54, &DAT_00B0FCCA);
        DAT_00B0F9F8 = FileSystem_LoadWholeFileEx(DAT_00844CCC, &DAT_00B0FCCB);
        DAT_00B0FA6C = FileSystem_LoadWholeFileEx(DAT_00844D5C, &DAT_00B0FCCC);
    }
}


// FUNCTION: GAMEMD 0x72DC20
//
// Release the four menu file blocks. Each block is deleted only when its
// allocated flag is set, through VC6's inline expansion of `delete` for a
// class with a non-virtual destructor; the block globals are nulled
// unconditionally.
void FUN_0072DC20()
{
    if (DAT_00B0FCC8) {
        WholeFileBlock* block = DAT_00B0FB48;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCC8 = false;
    }
    DAT_00B0FB48 = 0;
    if (DAT_00B0FCCA) {
        WholeFileBlock* block = DAT_00B0FB10;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCCA = false;
    }
    DAT_00B0FB10 = 0;
    if (DAT_00B0FCCB) {
        WholeFileBlock* block = DAT_00B0F9F8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCCB = false;
    }
    DAT_00B0F9F8 = 0;
    if (DAT_00B0FCCC) {
        WholeFileBlock* block = DAT_00B0FA6C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCCC = false;
    }
    DAT_00B0FA6C = 0;
}

// FUNCTION: GAMEMD 0x72DDB0
//
// When the screen resources are not loaded yet: run the first setup, load the
// ten menu file blocks and the three audio/timer palette sets, size the
// screen resources and mark them loaded.
void FUN_0072DDB0()
{
    if (DAT_00B0FBE0 == 0) {
        FUN_00534E50();
        FUN_0072EB50();
        ConvertClass_CreateFromFile(DAT_00844BE4, DAT_00B0FBC8.Palette, DAT_00B0FBC8.Convert);
        ConvertClass_CreateFromFile(DAT_00844BE8, DAT_00B0FBD0.Palette, DAT_00B0FBD0.Convert);
        ConvertClass_CreateFromFile(DAT_00844BEC, DAT_00B0FBD8.Palette, DAT_00B0FBD8.Convert);
        FUN_0072EC70(DAT_008A00A4, DAT_008A00A8);
        DAT_00B0FBE0 = 1;
    }
}

// FUNCTION: GAMEMD 0x72DEF0
//
// When the screen resources are loaded: clear the flag, tear down the two
// resource groups, release the eight raw blocks in order (each pointer nulled
// after its release) and finish with the last teardown.
void FUN_0072DEF0()
{
    if (DAT_00B0FBE0 != 0) {
        DAT_00B0FBE0 = 0;
        FUN_0072EF60();
        FreeAudioTimerPairs();
        FUN_007C8B3D(DAT_00B0FC10_r21_4[0]);
        DAT_00B0FC10_r21_4[0] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[1]);
        DAT_00B0FC10_r21_4[1] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[2]);
        DAT_00B0FC10_r21_4[2] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[3]);
        DAT_00B0FC10_r21_4[3] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[4]);
        DAT_00B0FC10_r21_4[4] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[5]);
        DAT_00B0FC10_r21_4[5] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[6]);
        DAT_00B0FC10_r21_4[6] = 0;
        FUN_007C8B3D(DAT_00B0FC10_r21_4[7]);
        DAT_00B0FC10_r21_4[7] = 0;
        FUN_00534DE0();
    }
}

// FUNCTION: GAMEMD 0x72DFB0
//
// Release the screen resources, then load them again.
void FUN_0072DFB0()
{
    FUN_0072DEF0();
    FUN_0072DDB0();
}

// FUNCTION: GAMEMD 0x72E1B0
//
// Release the eight raw blocks (each pointer nulled after its release), then
// hand the two register arguments on to the screen resize routine.
void __fastcall FUN_0072E1B0(int width, int height)
{
    FUN_007C8B3D(DAT_00B0FC10_r21_4[0]);
    DAT_00B0FC10_r21_4[0] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[1]);
    DAT_00B0FC10_r21_4[1] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[2]);
    DAT_00B0FC10_r21_4[2] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[3]);
    DAT_00B0FC10_r21_4[3] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[4]);
    DAT_00B0FC10_r21_4[4] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[5]);
    DAT_00B0FC10_r21_4[5] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[6]);
    DAT_00B0FC10_r21_4[6] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[7]);
    DAT_00B0FC10_r21_4[7] = 0;
    FUN_0072EC70(width, height);
}


// Blank one border region: fill the rectangle (x, y, w, h) inside `rect` with black.
inline void FillBorderRegion(Surface* surface, RectangleStruct* rect, int x, int y, int w, int h)
{
    RectangleStruct area;
    area.X = x;
    area.Y = y;
    area.Width = w;
    area.Height = h;
    surface->FillRectEx(&area, rect, 0);
}

// FUNCTION: GAMEMD 0x72E920
//
// Draw the background shape at the first layout rectangle's corner, moved
// 0x50 to the right on screens 800 wide or more, clipped to the given
// rectangle.
void __fastcall FUN_0072E920(Surface* surface, RectangleStruct* clip)
{
    RectangleStruct* origin = DAT_00B0FC1C;
    Point2D position(0, 0);
    position.X = origin->X;
    position.Y = origin->Y;
    if (DAT_008A00A4 >= 0x320) {
        position.X += 0x50;
    }
    FUN_004AED70(surface, DAT_00B0FBA4.Convert, DAT_00B0FB00, 0, &position, clip, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0,
                 Point2D(0, 0));
}

// FUNCTION: GAMEMD 0x72EB50
//
// Load the ten menu file blocks in order; each load reports through its own
// allocated flag byte.
void FUN_0072EB50()
{
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
}

// FUNCTION: GAMEMD 0x72EC70
//
// Build the eight screen layout rectangles for a screen of the given width and
// height. Past 1024 wide (768 tall) the layout is centred on an 800x600 area;
// the 640x480 case takes the sizes of the first shape of each pair.
void __fastcall FUN_0072EC70(int width, int height)
{
    int left = 0;
    int right = width;
    if (width >= 0x400) {
        left = (width - 0x320) / 2;
        right = width - left;
    }
    int top = 0;
    int bottom = height;
    int bottomOuter = height;
    if (height >= 0x300) {
        top = (height - 0x258) / 2;
        bottom = height - top;
        bottomOuter = height - top * 2;
    }
    bool is640 = width == 0x280;
    bool is480 = height == 0x1E0;

    int w;
    int h;
    if (is640) {
        w = DAT_00B0FB50->Width;
    } else {
        w = DAT_00B0FA04->Width;
    }
    if (is480) {
        h = DAT_00B0FB50->Height;
    } else {
        h = DAT_00B0FA04->Height;
    }
    RectangleStruct* p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = left;
        p->Y = top;
        p->Width = w;
        p->Height = h;
        DAT_00B0FC1C = p;
    } else {
        DAT_00B0FC1C = 0;
    }

    int w20 = DAT_00B0FAF8->Width;
    int h20 = DAT_00B0FAF8->Height;
    int x20 = right - w20;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = x20;
        p->Y = top;
        p->Width = w20;
        p->Height = h20;
        DAT_00B0FC20 = p;
    } else {
        DAT_00B0FC20 = 0;
    }

    int h18 = DAT_00B0FAC0->Height;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = x20;
        p->Y = top;
        p->Width = w20;
        p->Height = h18;
        DAT_00B0FC18 = p;
    } else {
        DAT_00B0FC18 = 0;
    }

    int y24 = DAT_00B0FC20->Height + top;
    int h24 = DAT_00B0FA74->Height;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = x20;
        p->Y = y24;
        p->Width = w20;
        p->Height = h24;
    } else {
        p = 0;
    }
    DAT_00B0FC24 = p;
    RectangleStruct* r24 = p;

    int w10 = DAT_00B0FAC4->Width;
    int y10 = r24->Y;
    int h10 = DAT_00B0FAC4->Height;
    int x10 = r24->Width - w10 + r24->X;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = x10;
        p->Y = y10;
        p->Width = w10;
        p->Height = h10;
        DAT_00B0FC10 = p;
    } else {
        DAT_00B0FC10 = 0;
    }

    int w14 = DAT_00B0F9DC->Width;
    int h14 = DAT_00B0F9DC->Height;
    int y14 = DAT_00B0FC24->Height + DAT_00B0FC24->Y - h14;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = right - w14;
        p->Y = y14;
        p->Width = w14;
        p->Height = h14;
        DAT_00B0FC14 = p;
    } else {
        DAT_00B0FC14 = 0;
    }

    DAT_00B0FA20 = (bottomOuter - DAT_00B0FC20->Height) / DAT_00B0FC24->Height;
    int step = DAT_00B0FC24->Height * DAT_00B0FA20;
    int y28 = DAT_00B0FC24->Y + step;
    int w28 = DAT_00B0FA38->Width;
    int bottom28 = DAT_00B0FC20->Height + step;
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = right - w28;
        p->Y = y28;
        p->Width = w28;
        p->Height = bottomOuter - bottom28;
        DAT_00B0FC28 = p;
    } else {
        DAT_00B0FC28 = 0;
    }

    int w2c;
    int h2c;
    if (is640) {
        w2c = DAT_00B0FAE8->Width;
    } else {
        w2c = DAT_00B0FA54->Width;
    }
    if (is480) {
        h2c = DAT_00B0FAE8->Height;
    } else {
        h2c = DAT_00B0FA54->Height;
    }
    p = (RectangleStruct*)FUN_007C8E17(sizeof(RectangleStruct));
    if (p) {
        p->X = left;
        p->Y = bottom - h2c;
        p->Width = w2c;
        p->Height = h2c;
        DAT_00B0FC2C = p;
    } else {
        DAT_00B0FC2C = 0;
    }
}

// FUNCTION: GAMEMD 0x72EF60
//
// Release the ten menu file blocks. Each block is deleted only when its
// allocated flag is set; the block globals are nulled unconditionally.
void FUN_0072EF60()
{
    if (DAT_00B0FC95) {
        WholeFileBlock* block = DAT_00B0FAC4;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC95 = false;
    }
    DAT_00B0FAC4 = 0;
    if (DAT_00B0FC96) {
        WholeFileBlock* block = DAT_00B0F9DC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC96 = false;
    }
    DAT_00B0F9DC = 0;
    if (DAT_00B0FC97) {
        WholeFileBlock* block = DAT_00B0FAC0;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC97 = false;
    }
    DAT_00B0FAC0 = 0;
    if (DAT_00B0FC98) {
        WholeFileBlock* block = DAT_00B0FB50;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC98 = false;
    }
    DAT_00B0FB50 = 0;
    if (DAT_00B0FC99) {
        WholeFileBlock* block = DAT_00B0FA04;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC99 = false;
    }
    DAT_00B0FA04 = 0;
    if (DAT_00B0FC9A) {
        WholeFileBlock* block = DAT_00B0FAF8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9A = false;
    }
    DAT_00B0FAF8 = 0;
    if (DAT_00B0FC9B) {
        WholeFileBlock* block = DAT_00B0FA74;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9B = false;
    }
    DAT_00B0FA74 = 0;
    if (DAT_00B0FC9C) {
        WholeFileBlock* block = DAT_00B0FA38;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9C = false;
    }
    DAT_00B0FA38 = 0;
    if (DAT_00B0FC9D) {
        WholeFileBlock* block = DAT_00B0FAE8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9D = false;
    }
    DAT_00B0FAE8 = 0;
    if (DAT_00B0FC9E) {
        WholeFileBlock* block = DAT_00B0FA54;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9E = false;
    }
    DAT_00B0FA54 = 0;
}

// FUNCTION: GAMEMD 0x72F1D0
//
// Release the eight raw blocks, each pointer nulled after its release.
void FUN_0072F1D0()
{
    FUN_007C8B3D(DAT_00B0FC10_r21_4[0]);
    DAT_00B0FC10_r21_4[0] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[1]);
    DAT_00B0FC10_r21_4[1] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[2]);
    DAT_00B0FC10_r21_4[2] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[3]);
    DAT_00B0FC10_r21_4[3] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[4]);
    DAT_00B0FC10_r21_4[4] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[5]);
    DAT_00B0FC10_r21_4[5] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[6]);
    DAT_00B0FC10_r21_4[6] = 0;
    FUN_007C8B3D(DAT_00B0FC10_r21_4[7]);
    DAT_00B0FC10_r21_4[7] = 0;
}

void FUN_0072FBC0();

// FUNCTION: GAMEMD 0x72F270
//
// Run the sidebar pre-setup, load the sidebar palette sets, run the
// follow-up setup and mark the sidebar palettes loaded.
void FUN_0072F270()
{
    FUN_0072FA10();
    FUN_0072FBC0();
    FUN_0072FC60(DAT_00A8EB84, DAT_00A8EB88);
    DAT_00B0FC0C = 1;
}

// FUNCTION: GAMEMD 0x730400 (decl; reloc)
void FUN_00730400();
// FUNCTION: GAMEMD 0x730530 (decl; reloc)
void FUN_00730530();

void FUN_00730100();

// FUNCTION: GAMEMD 0x72F350
//
// Reload the sidebar: release the old palettes and blocks, clear the loaded
// flag, run the pre-setup, load the sidebar palette sets again, run the
// follow-up setup and mark the sidebar palettes loaded.
void FUN_0072F350()
{
    FUN_00730100();
    FUN_00730400();
    FUN_00730530();
    DAT_00B0FC0C = 0;
    FUN_0072FA10();
    FUN_0072FBC0();
    FUN_0072FC60(DAT_00A8EB84, DAT_00A8EB88);
    DAT_00B0FC0C = 1;
}

// FUNCTION: GAMEMD 0x72FA10
//
// Load the sixteen sidebar file blocks. The first four come from one of two
// sets of file names depending on the scenario mode (2 takes one set, anything
// else the other); the remaining twelve are fixed.
void __cdecl FUN_0072FA10()
{
    if (ScenarioInstance->unknown_34B8 == 2) {
        DAT_00B0FA68 = FileSystem_LoadWholeFileEx(DAT_00844D48, &DAT_00B0FCA5);
        DAT_00B0FAC8 = FileSystem_LoadWholeFileEx(DAT_00844D3C, &DAT_00B0FCA1);
        DAT_00B0FAD4 = FileSystem_LoadWholeFileEx(DAT_00844D40, &DAT_00B0FCA0);
        DAT_00B0FA50 = FileSystem_LoadWholeFileEx(DAT_00844D44, &DAT_00B0FCA2);
    } else {
        DAT_00B0FA68 = FileSystem_LoadWholeFileEx(DAT_00844D14, &DAT_00B0FCA5);
        DAT_00B0FAC8 = FileSystem_LoadWholeFileEx(DAT_00844D04, &DAT_00B0FCA1);
        DAT_00B0FAD4 = FileSystem_LoadWholeFileEx(DAT_00844D00, &DAT_00B0FCA0);
        DAT_00B0FA50 = FileSystem_LoadWholeFileEx(DAT_00844D08, &DAT_00B0FCA2);
    }
    DAT_00B0F9EC = FileSystem_LoadWholeFileEx(DAT_00844CFC, &DAT_00B0FC9F);
    DAT_00B0FB08 = FileSystem_LoadWholeFileEx(DAT_00844D0C, &DAT_00B0FCA3);
    DAT_00B0F9E0 = FileSystem_LoadWholeFileEx(DAT_00844D10, &DAT_00B0FCA4);
    DAT_00B0FA70 = FileSystem_LoadWholeFileEx(DAT_00844D18, &DAT_00B0FCA6);
    DAT_00B0FAFC = FileSystem_LoadWholeFileEx(DAT_00844D1C, &DAT_00B0FCA7);
    DAT_00B0FA00 = FileSystem_LoadWholeFileEx(DAT_00844D20, &DAT_00B0FCA8);
    DAT_00B0FA8C = FileSystem_LoadWholeFileEx(DAT_00844D24, &DAT_00B0FCA9);
    DAT_00B0FA48 = FileSystem_LoadWholeFileEx(DAT_00844D28, &DAT_00B0FCAA);
    DAT_00B0FA3C = FileSystem_LoadWholeFileEx(DAT_00844D2C, &DAT_00B0FCAB);
    DAT_00B0FA90 = (SidebarShapeFile*)FileSystem_LoadWholeFileEx(DAT_00844D30, &DAT_00B0FCAC);
    DAT_00B0FAA8 = FileSystem_LoadWholeFileEx(DAT_00844D34, &DAT_00B0FCAD);
    DAT_00B0FABC = FileSystem_LoadWholeFileEx(DAT_00844D38, &DAT_00B0FCAE);
}

// Load the five sidebar palette sets. The pair of files for the first two
// sets depends on the scenario mode (2 takes one assignment, anything else the
// other); the remaining three sets are fixed. Retail expands this inline in
// 0x72F270 and also keeps an out-of-line copy at 0x72FBC0 (called from
// 0x72F540).
// FUNCTION: GAMEMD 0x72FBC0
void FUN_0072FBC0()
{
    if (ScenarioInstance->unknown_34B8 == 2) {
        ConvertClass_CreateFromFile(DAT_00844BF8, DAT_00B0FBEC.Palette, DAT_00B0FBEC.Convert);
        ConvertClass_CreateFromFile(DAT_00844BFC, DAT_00B0FBF4.Palette, DAT_00B0FBF4.Convert);
    } else {
        ConvertClass_CreateFromFile(DAT_00844C00, DAT_00B0FBF4.Palette, DAT_00B0FBF4.Convert);
        ConvertClass_CreateFromFile(DAT_00844BF4, DAT_00B0FBEC.Palette, DAT_00B0FBEC.Convert);
    }
    ConvertClass_CreateFromFile(DAT_00844BF0, DAT_00B0FBE4.Palette, DAT_00B0FBE4.Convert);
    ConvertClass_CreateFromFile(DAT_00844C04, DAT_00B0FBFC.Palette, DAT_00B0FBFC.Convert);
    ConvertClass_CreateFromFile(DAT_00844C08, DAT_00B0FC04.Palette, DAT_00B0FC04.Convert);
}

// FUNCTION: GAMEMD 0x730100
//
// Release the sixteen sidebar file blocks. Each block is deleted only when its
// allocated flag is set; the block globals are nulled unconditionally.
void FUN_00730100()
{
    if (DAT_00B0FC9F) {
        WholeFileBlock* block = DAT_00B0F9EC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FC9F = false;
    }
    DAT_00B0F9EC = 0;
    if (DAT_00B0FCA0) {
        WholeFileBlock* block = DAT_00B0FAD4;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA0 = false;
    }
    DAT_00B0FAD4 = 0;
    if (DAT_00B0FCA1) {
        WholeFileBlock* block = DAT_00B0FAC8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA1 = false;
    }
    DAT_00B0FAC8 = 0;
    if (DAT_00B0FCA2) {
        WholeFileBlock* block = DAT_00B0FA50;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA2 = false;
    }
    DAT_00B0FA50 = 0;
    if (DAT_00B0FCA3) {
        WholeFileBlock* block = DAT_00B0FB08;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA3 = false;
    }
    DAT_00B0FB08 = 0;
    if (DAT_00B0FCA4) {
        WholeFileBlock* block = DAT_00B0F9E0;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA4 = false;
    }
    DAT_00B0F9E0 = 0;
    if (DAT_00B0FCA5) {
        WholeFileBlock* block = DAT_00B0FA68;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA5 = false;
    }
    DAT_00B0FA68 = 0;
    if (DAT_00B0FCA6) {
        WholeFileBlock* block = DAT_00B0FA70;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA6 = false;
    }
    DAT_00B0FA70 = 0;
    if (DAT_00B0FCA7) {
        WholeFileBlock* block = DAT_00B0FAFC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA7 = false;
    }
    DAT_00B0FAFC = 0;
    if (DAT_00B0FCA8) {
        WholeFileBlock* block = DAT_00B0FA00;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA8 = false;
    }
    DAT_00B0FA00 = 0;
    if (DAT_00B0FCA9) {
        WholeFileBlock* block = DAT_00B0FA8C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCA9 = false;
    }
    DAT_00B0FA8C = 0;
    if (DAT_00B0FCAA) {
        WholeFileBlock* block = DAT_00B0FA48;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCAA = false;
    }
    DAT_00B0FA48 = 0;
    if (DAT_00B0FCAB) {
        WholeFileBlock* block = DAT_00B0FA3C;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCAB = false;
    }
    DAT_00B0FA3C = 0;
    if (DAT_00B0FCAC) {
        WholeFileBlock* block = (WholeFileBlock*)DAT_00B0FA90;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCAC = false;
    }
    DAT_00B0FA90 = 0;
    if (DAT_00B0FCAD) {
        WholeFileBlock* block = DAT_00B0FAA8;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCAD = false;
    }
    DAT_00B0FAA8 = 0;
    if (DAT_00B0FCAE) {
        WholeFileBlock* block = DAT_00B0FABC;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCAE = false;
    }
    DAT_00B0FABC = 0;
}

// FUNCTION: GAMEMD 0x730400
//
// Release the five sidebar palette sets in the order of their file names:
// palette buffer, then the named resource, then the convert object.
void FUN_00730400()
{
    if (DAT_00B0FC04.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FC04.Palette);
        DAT_00B0FC04.Palette = 0;
    }
    FUN_005B4270(DAT_00844C08);
    if (DAT_00B0FC04.Convert != 0) {
        DAT_00B0FC04.Convert->vf_0(1);
        DAT_00B0FC04.Convert = 0;
    }
    if (DAT_00B0FBFC.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBFC.Palette);
        DAT_00B0FBFC.Palette = 0;
    }
    FUN_005B4270(DAT_00844C04);
    if (DAT_00B0FBFC.Convert != 0) {
        DAT_00B0FBFC.Convert->vf_0(1);
        DAT_00B0FBFC.Convert = 0;
    }
    if (DAT_00B0FBF4.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBF4.Palette);
        DAT_00B0FBF4.Palette = 0;
    }
    FUN_005B4270(DAT_00844C00);
    if (DAT_00B0FBF4.Convert != 0) {
        DAT_00B0FBF4.Convert->vf_0(1);
        DAT_00B0FBF4.Convert = 0;
    }
    if (DAT_00B0FBE4.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBE4.Palette);
        DAT_00B0FBE4.Palette = 0;
    }
    FUN_005B4270(DAT_00844BF0);
    if (DAT_00B0FBE4.Convert != 0) {
        DAT_00B0FBE4.Convert->vf_0(1);
        DAT_00B0FBE4.Convert = 0;
    }
    if (DAT_00B0FBEC.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBEC.Palette);
        DAT_00B0FBEC.Palette = 0;
    }
    FUN_005B4270(DAT_00844BF4);
    if (DAT_00B0FBEC.Convert != 0) {
        DAT_00B0FBEC.Convert->vf_0(1);
        DAT_00B0FBEC.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x730530
//
// Release the sixteen raw blocks, each pointer nulled after its release.
void FUN_00730530()
{
    FUN_007C8B3D(DAT_00B0FC30_r21_4[0]);
    DAT_00B0FC30_r21_4[0] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[1]);
    DAT_00B0FC30_r21_4[1] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[2]);
    DAT_00B0FC30_r21_4[2] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[3]);
    DAT_00B0FC30_r21_4[3] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[4]);
    DAT_00B0FC30_r21_4[4] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[5]);
    DAT_00B0FC30_r21_4[5] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[6]);
    DAT_00B0FC30_r21_4[6] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[7]);
    DAT_00B0FC30_r21_4[7] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[8]);
    DAT_00B0FC30_r21_4[8] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[9]);
    DAT_00B0FC30_r21_4[9] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[10]);
    DAT_00B0FC30_r21_4[10] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[11]);
    DAT_00B0FC30_r21_4[11] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[12]);
    DAT_00B0FC30_r21_4[12] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[13]);
    DAT_00B0FC30_r21_4[13] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[14]);
    DAT_00B0FC30_r21_4[14] = 0;
    FUN_007C8B3D(DAT_00B0FC30_r21_4[15]);
    DAT_00B0FC30_r21_4[15] = 0;
}

// FUNCTION: GAMEMD 0x730670
//
// Run the 0x730400 setup, then load the sidebar palette sets.
void FUN_00730670()
{
    FUN_00730400();
    FUN_0072FBC0();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0FA20
int DAT_00B0FA20;
// GLOBAL: GAMEMD 0xB0F9E0
WholeFileBlock* DAT_00B0F9E0;
// GLOBAL: GAMEMD 0xB0F9EC
WholeFileBlock* DAT_00B0F9EC;
// GLOBAL: GAMEMD 0xB0FA00
WholeFileBlock* DAT_00B0FA00;
// GLOBAL: GAMEMD 0xB0FA3C
WholeFileBlock* DAT_00B0FA3C;
// GLOBAL: GAMEMD 0xB0FA48
WholeFileBlock* DAT_00B0FA48;
// GLOBAL: GAMEMD 0xB0FA50
WholeFileBlock* DAT_00B0FA50;
// GLOBAL: GAMEMD 0xB0FA68
WholeFileBlock* DAT_00B0FA68;
// GLOBAL: GAMEMD 0xB0FA70
WholeFileBlock* DAT_00B0FA70;
// GLOBAL: GAMEMD 0xB0FA8C
WholeFileBlock* DAT_00B0FA8C;
// GLOBAL: GAMEMD 0xB0FAA8
WholeFileBlock* DAT_00B0FAA8;
// GLOBAL: GAMEMD 0xB0FABC
WholeFileBlock* DAT_00B0FABC;
// GLOBAL: GAMEMD 0xB0FAC8
WholeFileBlock* DAT_00B0FAC8;
// GLOBAL: GAMEMD 0xB0FAD4
WholeFileBlock* DAT_00B0FAD4;
// GLOBAL: GAMEMD 0xB0FAFC
WholeFileBlock* DAT_00B0FAFC;
// GLOBAL: GAMEMD 0xB0FB08
WholeFileBlock* DAT_00B0FB08;
// GLOBAL: GAMEMD 0xB0FC9F
bool DAT_00B0FC9F;
// GLOBAL: GAMEMD 0xB0FCA0
bool DAT_00B0FCA0;
// GLOBAL: GAMEMD 0xB0FCA1
bool DAT_00B0FCA1;
// GLOBAL: GAMEMD 0xB0FCA2
bool DAT_00B0FCA2;
// GLOBAL: GAMEMD 0xB0FCA3
bool DAT_00B0FCA3;
// GLOBAL: GAMEMD 0xB0FCA4
bool DAT_00B0FCA4;
// GLOBAL: GAMEMD 0xB0FCA5
bool DAT_00B0FCA5;
// GLOBAL: GAMEMD 0xB0FCA6
bool DAT_00B0FCA6;
// GLOBAL: GAMEMD 0xB0FCA7
bool DAT_00B0FCA7;
// GLOBAL: GAMEMD 0xB0FCA8
bool DAT_00B0FCA8;
// GLOBAL: GAMEMD 0xB0FCA9
bool DAT_00B0FCA9;
// GLOBAL: GAMEMD 0xB0FCAA
bool DAT_00B0FCAA;
// GLOBAL: GAMEMD 0xB0FCAB
bool DAT_00B0FCAB;
// GLOBAL: GAMEMD 0xB0FCAC
bool DAT_00B0FCAC;
// GLOBAL: GAMEMD 0xB0FCAD
bool DAT_00B0FCAD;
// GLOBAL: GAMEMD 0xB0FCAE
bool DAT_00B0FCAE;
// GLOBAL: GAMEMD 0xB0F9F8
WholeFileBlock* DAT_00B0F9F8;
// GLOBAL: GAMEMD 0xB0FA38
WholeFileBlock* DAT_00B0FA38;
// GLOBAL: GAMEMD 0xB0FA54
WholeFileBlock* DAT_00B0FA54;
// GLOBAL: GAMEMD 0xB0FA6C
WholeFileBlock* DAT_00B0FA6C;
// GLOBAL: GAMEMD 0xB0FA74
WholeFileBlock* DAT_00B0FA74;
// GLOBAL: GAMEMD 0xB0FAC0
WholeFileBlock* DAT_00B0FAC0;
// GLOBAL: GAMEMD 0xB0FAC4
WholeFileBlock* DAT_00B0FAC4;
// GLOBAL: GAMEMD 0xB0FAE8
WholeFileBlock* DAT_00B0FAE8;
// GLOBAL: GAMEMD 0xB0FB10
WholeFileBlock* DAT_00B0FB10;
// GLOBAL: GAMEMD 0xB0FB48
WholeFileBlock* DAT_00B0FB48;
// GLOBAL: GAMEMD 0xB0FC10
extern void* DAT_00B0FC10_r21_4[8];
// GLOBAL: GAMEMD 0xB0FC30
void* DAT_00B0FC30_r21_4[16];
// GLOBAL: GAMEMD 0xB0FC95
bool DAT_00B0FC95;
// GLOBAL: GAMEMD 0xB0FC96
bool DAT_00B0FC96;
// GLOBAL: GAMEMD 0xB0FC97
bool DAT_00B0FC97;
// GLOBAL: GAMEMD 0xB0FC98
bool DAT_00B0FC98;
// GLOBAL: GAMEMD 0xB0FC99
bool DAT_00B0FC99;
// GLOBAL: GAMEMD 0xB0FC9A
bool DAT_00B0FC9A;
// GLOBAL: GAMEMD 0xB0FC9B
bool DAT_00B0FC9B;
// GLOBAL: GAMEMD 0xB0FC9C
bool DAT_00B0FC9C;
// GLOBAL: GAMEMD 0xB0FC9D
bool DAT_00B0FC9D;
// GLOBAL: GAMEMD 0xB0FC9E
bool DAT_00B0FC9E;
// GLOBAL: GAMEMD 0xB0FCC8
bool DAT_00B0FCC8;
// GLOBAL: GAMEMD 0xB0FCCA
bool DAT_00B0FCCA;
// GLOBAL: GAMEMD 0xB0FCCB
bool DAT_00B0FCCB;
// GLOBAL: GAMEMD 0xB0FCCC
bool DAT_00B0FCCC;
// GLOBAL: GAMEMD 0xB0F9DC
WholeFileBlock* DAT_00B0F9DC;
// GLOBAL: GAMEMD 0xB0FA04
WholeFileBlock* DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FAF8
WholeFileBlock* DAT_00B0FAF8;
// GLOBAL: GAMEMD 0xB0FB50
WholeFileBlock* DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FBE4
extern PaletteSet DAT_00B0FBE4;
// GLOBAL: GAMEMD 0xB0FBEC
extern PaletteSet DAT_00B0FBEC;
// GLOBAL: GAMEMD 0xB0FBF4
extern PaletteSet DAT_00B0FBF4;
// GLOBAL: GAMEMD 0xB0FBFC
extern PaletteSet DAT_00B0FBFC;
// GLOBAL: GAMEMD 0xB0FC04
extern PaletteSet DAT_00B0FC04;
// GLOBAL: GAMEMD 0xB0FC0C
char DAT_00B0FC0C;
// GLOBAL: GAMEMD 0x844FFC
extern const char STR_00844FFC[] = "FSBKGDLG.PAL";
// GLOBAL: GAMEMD 0x84500C
extern const char STR_0084500C[] = "FSBKGDLG.SHP";
// GLOBAL: GAMEMD 0x84501C
extern const char STR_0084501C[] = "FSSLG.PAL";
// GLOBAL: GAMEMD 0x845028
extern const char STR_00845028[] = "FSALG.PAL";
// GLOBAL: GAMEMD 0x845034
extern const char STR_00845034[] = "FSALG.SHP";
// GLOBAL: GAMEMD 0x845104
extern const char STR_00845104[] = "LWSCRNL.SHP";
// GLOBAL: GAMEMD 0x845110
extern const char STR_00845110[] = "LWSCRNS.SHP";
// GLOBAL: GAMEMD 0x84511C
extern const char STR_0084511C[] = "SDBTM.SHP";
// GLOBAL: GAMEMD 0x845128
extern const char STR_00845128[] = "SDBTNBKGD.SHP";
// GLOBAL: GAMEMD 0x845138
extern const char STR_00845138[] = "SDTP.SHP";
// GLOBAL: GAMEMD 0x845144
extern const char STR_00845144[] = "MNSCRNL.SHP";
// GLOBAL: GAMEMD 0x845150
extern const char STR_00845150[] = "MNSCRNS.SHP";
// GLOBAL: GAMEMD 0x84515C
extern const char STR_0084515C[] = "SDWRNTMP.SHP";
// GLOBAL: GAMEMD 0x84516C
extern const char STR_0084516C[] = "SDMPBTN.SHP";
// GLOBAL: GAMEMD 0x845178
extern const char STR_00845178[] = "SDBTNANM.SHP";
// GLOBAL: GAMEMD 0x845188
extern const char STR_00845188[] = "FSBKGDSM.SHP";
// GLOBAL: GAMEMD 0x845198
extern const char STR_00845198[] = "FSSLG.SHP";
// GLOBAL: GAMEMD 0x8451A4
extern const char STR_008451A4[] = "FSSSM.SHP";
// GLOBAL: GAMEMD 0x8451C8
extern const char STR_008451C8[] = "FSASM.SHP";
// GLOBAL: GAMEMD 0x8453E8
extern const char STR_008453E8[] = "YRII.PAL";
// GLOBAL: GAMEMD 0x8453F4
extern const char STR_008453F4[] = "OBSERVER.PAL";
// GLOBAL: GAMEMD 0x845404
extern const char STR_00845404[] = "RADARYURI.PAL";
// GLOBAL: GAMEMD 0x845414
extern const char STR_00845414[] = "UIBKGDY.PAL";
// GLOBAL: GAMEMD 0x845420
extern const char STR_00845420[] = "UIBKGD.PAL";
// GLOBAL: GAMEMD 0x84542C
extern const char STR_0084542C[] = "SIDEBAR.PAL";
// GLOBAL: GAMEMD 0x845460
extern const char STR_00845460[] = "FSSCRN.PAL";
// END defined globals
