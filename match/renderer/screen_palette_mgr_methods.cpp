// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x72B230, 0x72B390,
//   0x72B3E0, 0x72B460, 0x72B820, 0x72B870, 0x72BCA0, 0x72BCF0, 0x72BE80,
//   0x72BED0, 0x72D730, 0x72D780, 0x72DCF0 and 0x72F140. Semantic names are a
//   cross-check only (see the header); every instruction, offset and
//   global below was re-derived from the retail disassembly.

#include "screen_palette_mgr_methods.h"

// FUNCTION: GAMEMD 0x72B230
//
// Release the four in-game palette sets. Each set drops its palette buffer
// through the raw block release and its convert through vtable slot 0 with the
// vector flag (`PUSH 3`), then nulls both globals. The sets are released out of
// address order — 0xB0FB6C, 0xB0FB64, 0xB0FB5C, 0xB0FB74 — which is why this is
// written flat rather than as a loop or a shared helper.
void __cdecl FreeGamePalettePairs()
{
    if (DAT_00B0FB6C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB6C.Palette);
        DAT_00B0FB6C.Palette = 0;
    }
    if (DAT_00B0FB6C.Convert != 0) {
        DAT_00B0FB6C.Convert->vf_0(3);
        DAT_00B0FB6C.Convert = 0;
    }

    if (DAT_00B0FB64.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB64.Palette);
        DAT_00B0FB64.Palette = 0;
    }
    if (DAT_00B0FB64.Convert != 0) {
        DAT_00B0FB64.Convert->vf_0(3);
        DAT_00B0FB64.Convert = 0;
    }

    if (DAT_00B0FB5C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB5C.Palette);
        DAT_00B0FB5C.Palette = 0;
    }
    if (DAT_00B0FB5C.Convert != 0) {
        DAT_00B0FB5C.Convert->vf_0(3);
        DAT_00B0FB5C.Convert = 0;
    }

    if (DAT_00B0FB74.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB74.Palette);
        DAT_00B0FB74.Palette = 0;
    }
    if (DAT_00B0FB74.Convert != 0) {
        DAT_00B0FB74.Convert->vf_0(3);
        DAT_00B0FB74.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72B390
//
// Swap the loading screen's second palette set for a different variant: drop
// whatever is loaded (convert first, then palette buffer) and rebuild the pair
// from the supplied file name. The name arrives in ECX and is handed straight
// on to CreateFromFile in ECX, so this is __fastcall with a single register
// parameter that survives the two releases in EDI.
void __fastcall ReloadLoadingScreenVariant(const char* name)
{
    if (DAT_00B0FB84.Convert != 0) {
        DAT_00B0FB84.Convert->vf_0(1);
        DAT_00B0FB84.Convert = 0;
    }
    if (DAT_00B0FB84.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB84.Palette);
        DAT_00B0FB84.Palette = 0;
    }
    ConvertClass_CreateFromFile(name, DAT_00B0FB84.Palette, DAT_00B0FB84.Convert);
}

// FUNCTION: GAMEMD 0x72B3E0
//
// Build the three loading-screen palette sets if they are not already present.
// The presence test is on the convert pointer of each set. The middle set's
// file name depends on the side index; retail tail-merges the three arms onto
// one CALL, which is why this is spelled as three separate calls rather than a
// name selected into a local.
void __fastcall EnsureLoadingScreenPalettes(int sideIndex)
{
    if (DAT_00B0FB7C.Convert == 0) {
        ConvertClass_CreateFromFile(DAT_00844BAC, DAT_00B0FB7C.Palette,
                                    DAT_00B0FB7C.Convert);
    }

    if (DAT_00B0FB84.Convert == 0) {
        if (sideIndex == 0) {
            ConvertClass_CreateFromFile(DAT_00844BB0, DAT_00B0FB84.Palette,
                                        DAT_00B0FB84.Convert);
        } else if (sideIndex == 1) {
            ConvertClass_CreateFromFile(DAT_00844BB4, DAT_00B0FB84.Palette,
                                        DAT_00B0FB84.Convert);
        } else {
            ConvertClass_CreateFromFile(DAT_00844BB8, DAT_00B0FB84.Palette,
                                        DAT_00B0FB84.Convert);
        }
    }

    if (DAT_00B0FB8C.Convert == 0) {
        ConvertClass_CreateFromFile(DAT_00844BBC, DAT_00B0FB8C.Palette,
                                    DAT_00B0FB8C.Convert);
    }
}

// FUNCTION: GAMEMD 0x72B460
//
// Release the three loading-screen palette sets in address order, palette
// buffer before convert within each set. Six null tests against a shared zero
// register is what makes cl form one here rather than storing immediates.
void __cdecl FreeLoadingScreenPalettes()
{
    if (DAT_00B0FB7C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB7C.Palette);
        DAT_00B0FB7C.Palette = 0;
    }
    if (DAT_00B0FB7C.Convert != 0) {
        DAT_00B0FB7C.Convert->vf_0(1);
        DAT_00B0FB7C.Convert = 0;
    }

    if (DAT_00B0FB84.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB84.Palette);
        DAT_00B0FB84.Palette = 0;
    }
    if (DAT_00B0FB84.Convert != 0) {
        DAT_00B0FB84.Convert->vf_0(1);
        DAT_00B0FB84.Convert = 0;
    }

    if (DAT_00B0FB8C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB8C.Palette);
        DAT_00B0FB8C.Palette = 0;
    }
    if (DAT_00B0FB8C.Convert != 0) {
        DAT_00B0FB8C.Convert->vf_0(1);
        DAT_00B0FB8C.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72B820
//
// The multiplayer-lobby twin of 0x72B390: drop the secondary lobby set and
// rebuild it from the supplied file name, which arrives and leaves in ECX.
void __fastcall ReloadMpLobbySecondaryPalette(const char* name)
{
    if (DAT_00B0FB9C.Convert != 0) {
        DAT_00B0FB9C.Convert->vf_0(1);
        DAT_00B0FB9C.Convert = 0;
    }
    if (DAT_00B0FB9C.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FB9C.Palette);
        DAT_00B0FB9C.Palette = 0;
    }
    ConvertClass_CreateFromFile(name, DAT_00B0FB9C.Palette, DAT_00B0FB9C.Convert);
}

// FUNCTION: GAMEMD 0x72B870
//
// Release both multiplayer-lobby palette sets. The secondary set (0xB0FB9C) is
// torn down convert-first, matching the order 0x72B820 uses before it rebuilds
// it, and the primary set (0xB0FB94) palette-first. That asymmetry is in the
// retail instruction order and is the reason no shared release helper is used.
void __cdecl FreeMpLobbyPalettes()
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

// FUNCTION: GAMEMD 0x72BCA0
//
// Load the auto-login query screen once. At 800-pixel width an extra whole-file
// block is slurped through 0x4A38D0, whose "did I allocate this" out-flag is the
// byte at the head of the resource block; the palette/convert pair is then built
// from a second file name and the block is marked loaded.
void __cdecl EnsureAutoLoginQueryPalette()
{
    if (!DAT_00B0FD44.Loaded) {
        if (DAT_008A00A4 == 0x320) {
            DAT_00B0FA98 = FileSystem_LoadWholeFileEx(DAT_00844DB4,
                                                      &DAT_00B0FD44.Allocated);
        }
        ConvertClass_CreateFromFile(DAT_00844DB8, DAT_00B0FD44.Set.Palette,
                                    DAT_00B0FD44.Set.Convert);
        DAT_00B0FD44.Loaded = true;
    }
}

// FUNCTION: GAMEMD 0x72BCF0
//
// Release everything 0x72BCA0 acquired. The whole-file block is deleted only
// when the block owns it (the out-flag byte), through VC6's inline expansion of
// `delete` for a class with a non-virtual destructor; its global is nulled
// unconditionally afterwards.
//
// Phrasing note: the loaded flag is cleared on BOTH paths. Retail's opening
// `JZ 0x72BD5A` lands on the flag store at +0x6A rather than on the epilogue
// at +0x70, so the clear sits after the guarded block, not inside it. With it
// inside, the body is otherwise instruction-for-instruction correct and the
// only residual is that one jump target (97.2%).
void __cdecl FreeAutoLoginQueryPalette()
{
    if (DAT_00B0FD44.Loaded) {
        if (DAT_00B0FD44.Allocated) {
            WholeFileBlock* block = DAT_00B0FA98;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD44.Allocated = false;
        }
        DAT_00B0FA98 = 0;

        if (DAT_00B0FD44.Set.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD44.Set.Palette);
            DAT_00B0FD44.Set.Palette = 0;
        }
        if (DAT_00B0FD44.Set.Convert != 0) {
            DAT_00B0FD44.Set.Convert->vf_0(1);
            DAT_00B0FD44.Set.Convert = 0;
        }
    }
    DAT_00B0FD44.Loaded = false;
}

// FUNCTION: GAMEMD 0x72BE80
//
// The quickmatch screen's copy of 0x72BCA0, over the resource block one 0xC
// stride lower.
void __cdecl EnsureQuickmatchPalette()
{
    if (!DAT_00B0FD38.Loaded) {
        if (DAT_008A00A4 == 0x320) {
            DAT_00B0FA9C = FileSystem_LoadWholeFileEx(DAT_00844DAC,
                                                      &DAT_00B0FD38.Allocated);
        }
        ConvertClass_CreateFromFile(DAT_00844DB0, DAT_00B0FD38.Set.Palette,
                                    DAT_00B0FD38.Set.Convert);
        DAT_00B0FD38.Loaded = true;
    }
}

// FUNCTION: GAMEMD 0x72BED0
//
// The quickmatch screen's copy of 0x72BCF0, including the loaded flag being
// cleared outside the guarded block.
void __cdecl FreeQuickmatchPalette()
{
    if (DAT_00B0FD38.Loaded) {
        if (DAT_00B0FD38.Allocated) {
            WholeFileBlock* block = DAT_00B0FA9C;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FD38.Allocated = false;
        }
        DAT_00B0FA9C = 0;

        if (DAT_00B0FD38.Set.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FD38.Set.Palette);
            DAT_00B0FD38.Set.Palette = 0;
        }
        if (DAT_00B0FD38.Set.Convert != 0) {
            DAT_00B0FD38.Set.Convert->vf_0(1);
            DAT_00B0FD38.Set.Convert = 0;
        }
    }
    DAT_00B0FD38.Loaded = false;
}

// FUNCTION: GAMEMD 0x72D730
//
// Load the multiplayer screen once: pull its SHP set in, then build the screen
// palette from the side-dependent file name. Unlike 0x72B3E0, retail keeps one
// push/EDX/CALL run here with only the name selected per arm, so this is
// written as a `const char* name` local rather than as three separate calls;
// the three-call spelling duplicates the push and the EDX load into every arm
// and scores 28.0%.
void __fastcall EnsureMpScreenPalette(int sideIndex)
{
    if (!DAT_00B0FBB8) {
        FUN_0072D830(sideIndex);
        const char* name;
        if (sideIndex == 0) {
            name = DAT_00844BD4;
        } else if (sideIndex == 1) {
            name = DAT_00844BD8;
        } else {
            name = DAT_00844BDC;
        }
        ConvertClass_CreateFromFile(name, DAT_00B0FBB0.Palette,
                                    DAT_00B0FBB0.Convert);
        DAT_00B0FBB8 = true;
    }
}

// FUNCTION: GAMEMD 0x72D780
//
// Release the multiplayer screen. Same shape as 0x72BCF0 except that the loaded
// flag, the ownership flag and the file block live in three unrelated globals
// rather than in one contiguous block, and the loaded flag is cleared at the top
// of the guarded region rather than at the bottom.
void __cdecl FreeMpScreenPalette()
{
    if (DAT_00B0FBB8) {
        DAT_00B0FBB8 = false;

        if (DAT_00B0FC7D) {
            WholeFileBlock* block = DAT_00B0FB1C;
            if (block != 0) {
                block->FUN_0069E500();
                FUN_007C8B3D(block);
            }
            DAT_00B0FC7D = false;
        }
        DAT_00B0FB1C = 0;

        if (DAT_00B0FBB0.Palette != 0) {
            FUN_007C8B3D(DAT_00B0FBB0.Palette);
            DAT_00B0FBB0.Palette = 0;
        }
        if (DAT_00B0FBB0.Convert != 0) {
            DAT_00B0FBB0.Convert->vf_0(1);
            DAT_00B0FBB0.Convert = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x72DCF0
//
// Release the three full-screen-menu palette sets plus the fourth set that sits
// away from them at 0xB0FBBC, all in address order and palette before convert.
void __cdecl FreeFsMenuPalettes()
{
    if (DAT_00B0FCB0.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCB0.Palette);
        DAT_00B0FCB0.Palette = 0;
    }
    if (DAT_00B0FCB0.Convert != 0) {
        DAT_00B0FCB0.Convert->vf_0(1);
        DAT_00B0FCB0.Convert = 0;
    }

    if (DAT_00B0FCB8.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCB8.Palette);
        DAT_00B0FCB8.Palette = 0;
    }
    if (DAT_00B0FCB8.Convert != 0) {
        DAT_00B0FCB8.Convert->vf_0(1);
        DAT_00B0FCB8.Convert = 0;
    }

    if (DAT_00B0FCC0.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FCC0.Palette);
        DAT_00B0FCC0.Palette = 0;
    }
    if (DAT_00B0FCC0.Convert != 0) {
        DAT_00B0FCC0.Convert->vf_0(1);
        DAT_00B0FCC0.Convert = 0;
    }

    if (DAT_00B0FBBC.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBBC.Palette);
        DAT_00B0FBBC.Palette = 0;
    }
    if (DAT_00B0FBBC.Convert != 0) {
        DAT_00B0FBBC.Convert->vf_0(1);
        DAT_00B0FBBC.Convert = 0;
    }
}

// FUNCTION: GAMEMD 0x72F140
//
// Release the three sidebar audio/timer palette sets, address order, palette
// before convert.
void __cdecl FreeAudioTimerPairs()
{
    if (DAT_00B0FBC8.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBC8.Palette);
        DAT_00B0FBC8.Palette = 0;
    }
    if (DAT_00B0FBC8.Convert != 0) {
        DAT_00B0FBC8.Convert->vf_0(1);
        DAT_00B0FBC8.Convert = 0;
    }

    if (DAT_00B0FBD0.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBD0.Palette);
        DAT_00B0FBD0.Palette = 0;
    }
    if (DAT_00B0FBD0.Convert != 0) {
        DAT_00B0FBD0.Convert->vf_0(1);
        DAT_00B0FBD0.Convert = 0;
    }

    if (DAT_00B0FBD8.Palette != 0) {
        FUN_007C8B3D(DAT_00B0FBD8.Palette);
        DAT_00B0FBD8.Palette = 0;
    }
    if (DAT_00B0FBD8.Convert != 0) {
        DAT_00B0FBD8.Convert->vf_0(1);
        DAT_00B0FBD8.Convert = 0;
    }
}
