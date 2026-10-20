// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// Retail v1.001 menu resource helpers. File identities are read from retail
// filename pointers; function names remain address-based pending stronger evidence.
#include "screen_palette_mgr_methods.h"

// GLOBAL: GAMEMD 0x844DC4
extern const char* DAT_00844DC4;
// GLOBAL: GAMEMD 0x844DC8
extern const char* DAT_00844DC8;
// GLOBAL: GAMEMD 0x844D7C
extern const char* DAT_00844D7C;
// GLOBAL: GAMEMD 0x844D80
extern const char* DAT_00844D80;
// GLOBAL: GAMEMD 0xB0FB54
extern WholeFileBlock* DAT_00B0FB54;
// GLOBAL: GAMEMD 0xB0FA60
extern WholeFileBlock* DAT_00B0FA60;
// GLOBAL: GAMEMD 0xB0FD5C
extern bool DAT_00B0FD5C;
// GLOBAL: GAMEMD 0xB0FCF0
extern bool DAT_00B0FCF0;
// GLOBAL: GAMEMD 0xB0FD60
extern PaletteSet DAT_00B0FD60;
// GLOBAL: GAMEMD 0xB0FCF4
extern PaletteSet DAT_00B0FCF4;

// FUNCTION: GAMEMD 0x72B9E0
// WOLSoundOptions.shp: the whole-file block is only used at width 800.
void __cdecl FUN_0072B9E0()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FB54 = FileSystem_LoadWholeFileEx(DAT_00844DC4, &DAT_00B0FD5C);
    }
}

// FUNCTION: GAMEMD 0x72BA10
// WOLSoundOptions.PAL. EDX addresses +0, stack argument addresses +4.
void __cdecl FUN_0072BA10()
{
    ConvertClass_CreateFromFile(DAT_00844DC8, DAT_00B0FD60.Palette, DAT_00B0FD60.Convert);
}

// FUNCTION: GAMEMD 0x72BA30
void __cdecl FUN_0072BA30()
{
    if (DAT_00B0FD5C) {
        WholeFileBlock* block = DAT_00B0FB54;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FD5C = false;
    }
    DAT_00B0FB54 = 0;
}

// FUNCTION: GAMEMD 0x72BA80
// Convert deletion uses retail vtable slot 0; PaletteSet offsets are asserted
// in screen_palette_mgr_methods.h and confirmed at these two global addresses.
void __cdecl FUN_0072BA80()
{
    if (DAT_00B0FD60.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FD60.Palette);
        DAT_00B0FD60.Palette = 0;
    }
    if (DAT_00B0FD60.Convert != 0) {
        DAT_00B0FD60.Convert->DeleteThis(1);
        DAT_00B0FD60.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72CAC0
// MnScrnLMyInformation.shp: the whole-file block is only used at width 800.
void __cdecl FUN_0072CAC0()
{
    if (DAT_008A00A4 == 800) {
        DAT_00B0FA60 = FileSystem_LoadWholeFileEx(DAT_00844D7C, &DAT_00B0FCF0);
    }
}

// FUNCTION: GAMEMD 0x72CAF0
// MnScrnLMyInformation.PAL. EDX addresses +0, stack argument addresses +4.
void __cdecl FUN_0072CAF0()
{
    ConvertClass_CreateFromFile(DAT_00844D80, DAT_00B0FCF4.Palette, DAT_00B0FCF4.Convert);
}

// FUNCTION: GAMEMD 0x72CB10
void __cdecl FUN_0072CB10()
{
    if (DAT_00B0FCF0) {
        WholeFileBlock* block = DAT_00B0FA60;
        if (block != 0) {
            block->FUN_0069E500();
            FUN_007C8B3D(block);
        }
        DAT_00B0FCF0 = false;
    }
    DAT_00B0FA60 = 0;
}

// FUNCTION: GAMEMD 0x72CB60
// Convert deletion uses retail vtable slot 0; PaletteSet offsets are asserted
// in screen_palette_mgr_methods.h and confirmed at these two global addresses.
void __cdecl FUN_0072CB60()
{
    if (DAT_00B0FCF4.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCF4.Palette);
        DAT_00B0FCF4.Palette = 0;
    }
    if (DAT_00B0FCF4.Convert != 0) {
        DAT_00B0FCF4.Convert->DeleteThis(1);
        DAT_00B0FCF4.Convert = 0;
    }
}
