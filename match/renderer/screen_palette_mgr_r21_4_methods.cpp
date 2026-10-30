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
#include "../core/scenario_class_methods.h"

// GLOBAL: GAMEMD 0xB0FBE0 -- the screen resources are loaded.
extern char DAT_00B0FBE0_r21_4;
// GLOBAL: GAMEMD 0xB0FC10 -- eight raw blocks, stride 4.
extern void* DAT_00B0FC10_r21_4[8];

// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioClass* ScenarioInstance;
// GLOBAL: GAMEMD 0xB0FBE4 -- palette sets of the sidebar screen (stride 8).
extern PaletteSet DAT_00B0FBE4;
// GLOBAL: GAMEMD 0xB0FBEC
extern PaletteSet DAT_00B0FBEC;
// GLOBAL: GAMEMD 0xB0FBF4
extern PaletteSet DAT_00B0FBF4;
// GLOBAL: GAMEMD 0xB0FBFC
extern PaletteSet DAT_00B0FBFC;
// GLOBAL: GAMEMD 0xB0FC04
extern PaletteSet DAT_00B0FC04;
// GLOBAL: GAMEMD 0xB0FC0C -- the sidebar palettes are loaded.
extern char DAT_00B0FC0C_r21_4;
// GLOBAL: GAMEMD 0x844BF0 -- sidebar palette file names.
extern const char* DAT_00844BF0;
// GLOBAL: GAMEMD 0x844BF4
extern const char* DAT_00844BF4;
// GLOBAL: GAMEMD 0x844BF8
extern const char* DAT_00844BF8;
// GLOBAL: GAMEMD 0x844BFC
extern const char* DAT_00844BFC;
// GLOBAL: GAMEMD 0x844C00
extern const char* DAT_00844C00;
// GLOBAL: GAMEMD 0x844C04
extern const char* DAT_00844C04;
// GLOBAL: GAMEMD 0x844C08
extern const char* DAT_00844C08;
// GLOBAL: GAMEMD 0xA8EB84
extern int DAT_00A8EB84_r21_4;
// GLOBAL: GAMEMD 0xA8EB88
extern int DAT_00A8EB88_r21_4;

// FUNCTION: GAMEMD 0x72FA10 (decl; reloc)
void __cdecl FUN_0072FA10();
// FUNCTION: GAMEMD 0x72FC60 (decl; reloc)
void __fastcall FUN_0072FC60(int a, int b);

// FUNCTION: GAMEMD 0x5B4270 (decl; reloc) -- unload the named resource.
void FUN_005B4270(const char* name);

// GLOBAL: GAMEMD 0xB0FC30 -- sixteen raw blocks, stride 4.
extern void* DAT_00B0FC30_r21_4[16];

// FUNCTION: GAMEMD 0x72EC70 (decl; reloc) -- takes the screen width and height.
void FUN_0072EC70(int width, int height);
// FUNCTION: GAMEMD 0x72EF60 (decl; reloc)
void FUN_0072EF60();
// FUNCTION: GAMEMD 0x534DE0 (decl; reloc)
void FUN_00534DE0();

// GLOBAL: GAMEMD 0xB0FCC8 -- the four menu file blocks and their allocated flags.
extern bool DAT_00B0FCC8;
// GLOBAL: GAMEMD 0xB0FCCA
extern bool DAT_00B0FCCA;
// GLOBAL: GAMEMD 0xB0FCCB
extern bool DAT_00B0FCCB;
// GLOBAL: GAMEMD 0xB0FCCC
extern bool DAT_00B0FCCC;
// GLOBAL: GAMEMD 0xB0FB48
extern WholeFileBlock* DAT_00B0FB48;
// GLOBAL: GAMEMD 0xB0FB10
extern WholeFileBlock* DAT_00B0FB10;
// GLOBAL: GAMEMD 0xB0F9F8
extern WholeFileBlock* DAT_00B0F9F8;
// GLOBAL: GAMEMD 0xB0FA6C
extern WholeFileBlock* DAT_00B0FA6C;
// GLOBAL: GAMEMD 0x844CB8 -- file names for the 640-wide menu blocks.
extern const char* DAT_00844CB8;
// GLOBAL: GAMEMD 0x844CC4
extern const char* DAT_00844CC4;
// GLOBAL: GAMEMD 0x844CC8
extern const char* DAT_00844CC8;
// GLOBAL: GAMEMD 0x844CD0
extern const char* DAT_00844CD0;
// GLOBAL: GAMEMD 0x844D4C -- file names for the other menu resolutions.
extern const char* DAT_00844D4C;
// GLOBAL: GAMEMD 0x844D54
extern const char* DAT_00844D54;
// GLOBAL: GAMEMD 0x844CCC
extern const char* DAT_00844CCC;
// GLOBAL: GAMEMD 0x844D5C
extern const char* DAT_00844D5C;

// Load the four menu file blocks. At 640 wide the first set of file names is
// used, otherwise the second; each load reports through the allocated flag
// that sits beside the file block's owner. Retail expands this inline in
// 0x72D9A0 and also keeps an uncalled out-of-line copy at 0x72DB00; that
// copy is not matched here.
inline void LoadMenuFileBlocks()
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

// GLOBAL: GAMEMD 0x844BE0 -- menu palette file names.
extern const char* DAT_00844BE0;
// GLOBAL: GAMEMD 0x844D50
extern const char* DAT_00844D50;
// GLOBAL: GAMEMD 0x844D58
extern const char* DAT_00844D58;
// GLOBAL: GAMEMD 0x844D60
extern const char* DAT_00844D60;

// FUNCTION: GAMEMD 0x72D9A0
//
// Load the four menu file blocks, then the fourth menu palette set and the
// three full-screen-menu palette sets.
void FUN_0072D9A0()
{
    LoadMenuFileBlocks();
    ConvertClass_CreateFromFile(DAT_00844BE0, DAT_00B0FBBC.Palette, DAT_00B0FBBC.Convert);
    ConvertClass_CreateFromFile(DAT_00844D50, DAT_00B0FCB0.Palette, DAT_00B0FCB0.Convert);
    ConvertClass_CreateFromFile(DAT_00844D58, DAT_00B0FCB8.Palette, DAT_00B0FCB8.Convert);
    ConvertClass_CreateFromFile(DAT_00844D60, DAT_00B0FCC0.Palette, DAT_00B0FCC0.Convert);
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

// FUNCTION: GAMEMD 0x72DEF0
//
// When the screen resources are loaded: clear the flag, tear down the two
// resource groups, release the eight raw blocks in order (each pointer nulled
// after its release) and finish with the last teardown.
void FUN_0072DEF0()
{
    if (DAT_00B0FBE0_r21_4 != 0) {
        DAT_00B0FBE0_r21_4 = 0;
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
// GLOBAL: GAMEMD 0xB0FAC4
extern WholeFileBlock* DAT_00B0FAC4;
// GLOBAL: GAMEMD 0xB0F9DC
extern WholeFileBlock* DAT_00B0F9DC;
// GLOBAL: GAMEMD 0xB0FAC0
extern WholeFileBlock* DAT_00B0FAC0;
// GLOBAL: GAMEMD 0xB0FB50
extern WholeFileBlock* DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FA04
extern WholeFileBlock* DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FAF8
extern WholeFileBlock* DAT_00B0FAF8;
// GLOBAL: GAMEMD 0xB0FA74
extern WholeFileBlock* DAT_00B0FA74;
// GLOBAL: GAMEMD 0xB0FA38
extern WholeFileBlock* DAT_00B0FA38;
// GLOBAL: GAMEMD 0xB0FAE8
extern WholeFileBlock* DAT_00B0FAE8;
// GLOBAL: GAMEMD 0xB0FA54
extern WholeFileBlock* DAT_00B0FA54;
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

// Load the five sidebar palette sets. The pair of files for the first two
// sets depends on the scenario mode (2 takes one assignment, anything else the
// other); the remaining three sets are fixed. Retail expands this inline in
// 0x72F270 and also keeps an out-of-line copy at 0x72FBC0 (called from
// 0x72F540); that copy belongs to its caller's owner and is not matched here.
inline void LoadSidebarPaletteSets()
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

// FUNCTION: GAMEMD 0x72F270
//
// Run the sidebar pre-setup, load the sidebar palette sets, run the
// follow-up setup and mark the sidebar palettes loaded.
void FUN_0072F270()
{
    FUN_0072FA10();
    LoadSidebarPaletteSets();
    FUN_0072FC60(DAT_00A8EB84_r21_4, DAT_00A8EB88_r21_4);
    DAT_00B0FC0C_r21_4 = 1;
}

// FUNCTION: GAMEMD 0x730400 (decl; reloc)
void FUN_00730400();
// FUNCTION: GAMEMD 0x730530 (decl; reloc)
void FUN_00730530();

// FUNCTION: GAMEMD 0x730100 (decl; reloc)
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
    DAT_00B0FC0C_r21_4 = 0;
    FUN_0072FA10();
    LoadSidebarPaletteSets();
    FUN_0072FC60(DAT_00A8EB84_r21_4, DAT_00A8EB88_r21_4);
    DAT_00B0FC0C_r21_4 = 1;
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
    LoadSidebarPaletteSets();
}

// BEGIN defined globals (define_globals.py)
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
void* DAT_00B0FC10_r21_4[8];
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
// GLOBAL: GAMEMD 0xA8EB84
int DAT_00A8EB84_r21_4;
// GLOBAL: GAMEMD 0xA8EB88
int DAT_00A8EB88_r21_4;
// GLOBAL: GAMEMD 0xB0F9DC
WholeFileBlock* DAT_00B0F9DC;
// GLOBAL: GAMEMD 0xB0FA04
WholeFileBlock* DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FAF8
WholeFileBlock* DAT_00B0FAF8;
// GLOBAL: GAMEMD 0xB0FB50
WholeFileBlock* DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FBE0
char DAT_00B0FBE0_r21_4;
// GLOBAL: GAMEMD 0xB0FBE4
PaletteSet DAT_00B0FBE4;
// GLOBAL: GAMEMD 0xB0FBEC
PaletteSet DAT_00B0FBEC;
// GLOBAL: GAMEMD 0xB0FBF4
PaletteSet DAT_00B0FBF4;
// GLOBAL: GAMEMD 0xB0FBFC
PaletteSet DAT_00B0FBFC;
// GLOBAL: GAMEMD 0xB0FC04
PaletteSet DAT_00B0FC04;
// GLOBAL: GAMEMD 0xB0FC0C
char DAT_00B0FC0C_r21_4;
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
// GLOBAL: GAMEMD 0x844FFC
extern const char STR_00844FFC[];
// GLOBAL: GAMEMD 0x84500C
extern const char STR_0084500C[];
// GLOBAL: GAMEMD 0x84501C
extern const char STR_0084501C[];
// GLOBAL: GAMEMD 0x845028
extern const char STR_00845028[];
// GLOBAL: GAMEMD 0x845034
extern const char STR_00845034[];
// GLOBAL: GAMEMD 0x845104
extern const char STR_00845104[];
// GLOBAL: GAMEMD 0x845110
extern const char STR_00845110[];
// GLOBAL: GAMEMD 0x84511C
extern const char STR_0084511C[];
// GLOBAL: GAMEMD 0x845128
extern const char STR_00845128[];
// GLOBAL: GAMEMD 0x845138
extern const char STR_00845138[];
// GLOBAL: GAMEMD 0x845144
extern const char STR_00845144[];
// GLOBAL: GAMEMD 0x845150
extern const char STR_00845150[];
// GLOBAL: GAMEMD 0x84515C
extern const char STR_0084515C[];
// GLOBAL: GAMEMD 0x84516C
extern const char STR_0084516C[];
// GLOBAL: GAMEMD 0x845178
extern const char STR_00845178[];
// GLOBAL: GAMEMD 0x845188
extern const char STR_00845188[];
// GLOBAL: GAMEMD 0x845198
extern const char STR_00845198[];
// GLOBAL: GAMEMD 0x8451A4
extern const char STR_008451A4[];
// GLOBAL: GAMEMD 0x8451C8
extern const char STR_008451C8[];
// GLOBAL: GAMEMD 0x8453E8
extern const char STR_008453E8[];
// GLOBAL: GAMEMD 0x8453F4
extern const char STR_008453F4[];
// GLOBAL: GAMEMD 0x845404
extern const char STR_00845404[];
// GLOBAL: GAMEMD 0x845414
extern const char STR_00845414[];
// GLOBAL: GAMEMD 0x845420
extern const char STR_00845420[];
// GLOBAL: GAMEMD 0x84542C
extern const char STR_0084542C[];
// GLOBAL: GAMEMD 0x845460
extern const char STR_00845460[];
// GLOBAL: GAMEMD 0x844FFC
extern const char STR_00844FFC[];
// GLOBAL: GAMEMD 0x84500C
extern const char STR_0084500C[];
// GLOBAL: GAMEMD 0x84501C
extern const char STR_0084501C[];
// GLOBAL: GAMEMD 0x845028
extern const char STR_00845028[];
// GLOBAL: GAMEMD 0x845034
extern const char STR_00845034[];
// GLOBAL: GAMEMD 0x845104
extern const char STR_00845104[];
// GLOBAL: GAMEMD 0x845110
extern const char STR_00845110[];
// GLOBAL: GAMEMD 0x84511C
extern const char STR_0084511C[];
// GLOBAL: GAMEMD 0x845128
extern const char STR_00845128[];
// GLOBAL: GAMEMD 0x845138
extern const char STR_00845138[];
// GLOBAL: GAMEMD 0x845144
extern const char STR_00845144[];
// GLOBAL: GAMEMD 0x845150
extern const char STR_00845150[];
// GLOBAL: GAMEMD 0x84515C
extern const char STR_0084515C[];
// GLOBAL: GAMEMD 0x84516C
extern const char STR_0084516C[];
// GLOBAL: GAMEMD 0x845178
extern const char STR_00845178[];
// GLOBAL: GAMEMD 0x845188
extern const char STR_00845188[];
// GLOBAL: GAMEMD 0x845198
extern const char STR_00845198[];
// GLOBAL: GAMEMD 0x8451A4
extern const char STR_008451A4[];
// GLOBAL: GAMEMD 0x8451C8
extern const char STR_008451C8[];
// GLOBAL: GAMEMD 0x8453E8
extern const char STR_008453E8[];
// GLOBAL: GAMEMD 0x8453F4
extern const char STR_008453F4[];
// GLOBAL: GAMEMD 0x845404
extern const char STR_00845404[];
// GLOBAL: GAMEMD 0x845414
extern const char STR_00845414[];
// GLOBAL: GAMEMD 0x845420
extern const char STR_00845420[];
// GLOBAL: GAMEMD 0x84542C
extern const char STR_0084542C[];
// GLOBAL: GAMEMD 0x845460
extern const char STR_00845460[];
// END defined globals
