// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//
//   The shell/loading-screen palette resource manager: fourteen small free
//   functions at 0x72B230-0x72F140 that acquire and release palette/convert
//   pairs held in module-scope globals. Every address, offset and stride below
//   was read numerically off the user's retail gamemd.exe v1.001 through the
//   local Ghidra CLI; the semantic names came from the user's own behavioural
//   reimplementation (`core/screen_palette_mgr*.cpp`,
//   `core/sidebar_shp_palette_mgr.cpp`) and are a naming cross-check only —
//   that project is a 64-bit Vulkan reimplementation and contributed nothing to
//   the bytes, layout or conventions recovered here.
//
//   PaletteSet (8 bytes) — confirmed three independent ways:
//     * every call to 0x72ADE0 in this family passes EDX = P and the single
//       stack argument = P+4, e.g. `MOV EDX,0xb0fb7c; PUSH 0xb0fb80` at
//       0x72B3F2 and `MOV EDX,0xb0fd48; PUSH 0xb0fd4c` at 0x72BCD0. 0x72ADE0
//       is ConvertClass::CreateFromFile(name, ColorStruct*&, ConvertClass*&)
//       (already matched in convert_class_create_methods.cpp), so P+0 is the
//       palette pointer and P+4 the convert pointer;
//     * the teardown at P+0 is always `PUSH; CALL 0x7C8B3D; ADD ESP,4` (a raw
//       block release — a palette buffer) and the teardown at P+4 is always
//       `MOV EAX,[ECX]; PUSH 1|3; CALL dword ptr [EAX]` (vtable slot 0, the
//       deleting destructor — a polymorphic object);
//     * the sets are laid out contiguously with an 8-byte stride:
//       0xB0FB5C/0xB0FB64/0xB0FB6C/0xB0FB74 (0x72B230),
//       0xB0FB7C/0xB0FB84/0xB0FB8C (0x72B3E0),
//       0xB0FCB0/0xB0FCB8/0xB0FCC0 (0x72DCF0),
//       0xB0FBC8/0xB0FBD0/0xB0FBD8 (0x72F140).
//
//   ScreenPaletteRes (0xC bytes) — the two query-screen blocks at 0xB0FD38 and
//   0xB0FD44 are 0xC apart, and within each block 0x72BCA0/0x72BCF0 and
//   0x72BE80/0x72BED0 touch +0x00 as a byte passed by address to 0x4A38D0's
//   out-flag parameter, +0x01 as a byte flag set to 1 on load and 0 on release,
//   +0x04 as the palette pointer and +0x08 as the convert pointer. The two
//   bytes at +0x02/+0x03 are never referenced (natural padding before the
//   pointer at +0x04).
#ifndef GG_MATCH_RENDERER_SCREEN_PALETTE_MGR_METHODS_H
#define GG_MATCH_RENDERER_SCREEN_PALETTE_MGR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Callees (declarations only; the diff harness normalises the relocations).
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — operator delete / free, __cdecl.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x69E500 (decl; reloc) — the non-virtual destructor of the
// object 0x4A38D0 hands back (`MOV ECX,ESI; CALL 0x69E500; PUSH ESI;
// CALL 0x7C8B3D` at 0x72BD0F and 0x72D7A6 is VC6's inline expansion of
// `delete p` for a class with a non-virtual destructor).
struct WholeFileBlock
{
    void FUN_0069E500();
};

// FUNCTION: GAMEMD 0x4A38D0 (decl; reloc) — FileSystem::LoadWholeFileEx,
// __fastcall, name in ECX and the "allocated" out-flag in EDX. Modelled
// independently here so this TU stands alone; agrees with
// match/platform/file_system_load_whole_methods.h (not edited).
WholeFileBlock* FileSystem_LoadWholeFileEx(const char* fileName,
                                           bool* allocated);

// A palette buffer: 0x100 three-byte entries, released with a bare
// `FUN_007C8B3D` (see convert_class_create_methods.h, 0x72ADE0).
struct ColorStruct_Res
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
GG_STATIC_ASSERT(sizeof(ColorStruct_Res) == 3);

// The colour-remap object. Only vtable slot 0 is exercised by this family:
// `MOV EAX,dword ptr [ECX]; PUSH 1; CALL dword ptr [EAX]` is the scalar
// deleting destructor and `PUSH 3` (0x72B230 only) its vector form.
struct ConvertClass_Res
{
    // VTABLE: GAMEMD slot 0 — scalar/vector deleting destructor.
    virtual void vf_0(int flags);
};

// FUNCTION: GAMEMD 0x72ADE0 (decl; reloc) — ConvertClass::CreateFromFile.
void ConvertClass_CreateFromFile(const char* pFilename,
                                 ColorStruct_Res*& pPalette,
                                 ConvertClass_Res*& pDestination);

// FUNCTION: GAMEMD 0x72D830 (decl; reloc) — load the multiplayer screen SHP for a side (ECX).
void FUN_0072D830(int sideIndex);

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------

struct PaletteSet
{
    ColorStruct_Res*  Palette;   // +0x00
    ConvertClass_Res* Convert;   // +0x04
};
GG_STATIC_ASSERT(offsetof(PaletteSet, Palette) == 0x00);
GG_STATIC_ASSERT(offsetof(PaletteSet, Convert) == 0x04);
GG_STATIC_ASSERT(sizeof(PaletteSet) == 0x08);

struct ScreenPaletteRes
{
    bool       Allocated;    // +0x00  out-flag handed to 0x4A38D0
    bool       Loaded;       // +0x01  guard for the whole block
    char       _pad002[2];   // +0x02  never referenced
    PaletteSet Set;          // +0x04
};
GG_STATIC_ASSERT(offsetof(ScreenPaletteRes, Allocated) == 0x00);
GG_STATIC_ASSERT(offsetof(ScreenPaletteRes, Loaded) == 0x01);
GG_STATIC_ASSERT(offsetof(ScreenPaletteRes, Set) == 0x04);
GG_STATIC_ASSERT(offsetof(ScreenPaletteRes, Set) + offsetof(PaletteSet, Convert) == 0x08);
GG_STATIC_ASSERT(sizeof(ScreenPaletteRes) == 0x0C);

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x8A00A4 — the horizontal screen resolution (compared to
// 0x320 = 800 at 0x72BCA9 and 0x72BE89).
extern int DAT_008A00A4;

// GLOBAL: GAMEMD 0x844BAC — loading-screen palette file names.
extern const char* DAT_00844BAC;
// GLOBAL: GAMEMD 0x844BB0
extern const char* DAT_00844BB0;
// GLOBAL: GAMEMD 0x844BB4
extern const char* DAT_00844BB4;
// GLOBAL: GAMEMD 0x844BB8
extern const char* DAT_00844BB8;
// GLOBAL: GAMEMD 0x844BBC
extern const char* DAT_00844BBC;
// GLOBAL: GAMEMD 0x844BD4 — multiplayer-screen palette file names.
extern const char* DAT_00844BD4;
// GLOBAL: GAMEMD 0x844BD8
extern const char* DAT_00844BD8;
// GLOBAL: GAMEMD 0x844BDC
extern const char* DAT_00844BDC;
// GLOBAL: GAMEMD 0x844DAC — quickmatch screen file names.
extern const char* DAT_00844DAC;
// GLOBAL: GAMEMD 0x844DB0
extern const char* DAT_00844DB0;
// GLOBAL: GAMEMD 0x844DB4 — auto-login query screen file names.
extern const char* DAT_00844DB4;
// GLOBAL: GAMEMD 0x844DB8
extern const char* DAT_00844DB8;

// GLOBAL: GAMEMD 0xB0FA98 — the auto-login query screen's whole-file block.
extern WholeFileBlock* DAT_00B0FA98;
// GLOBAL: GAMEMD 0xB0FA9C — the quickmatch screen's whole-file block.
extern WholeFileBlock* DAT_00B0FA9C;
// GLOBAL: GAMEMD 0xB0FB1C — the multiplayer screen's whole-file block.
extern WholeFileBlock* DAT_00B0FB1C;

// GLOBAL: GAMEMD 0xB0FB5C — in-game palette sets (four, stride 8).
extern PaletteSet DAT_00B0FB5C;
// GLOBAL: GAMEMD 0xB0FB64
extern PaletteSet DAT_00B0FB64;
// GLOBAL: GAMEMD 0xB0FB6C
extern PaletteSet DAT_00B0FB6C;
// GLOBAL: GAMEMD 0xB0FB74
extern PaletteSet DAT_00B0FB74;

// GLOBAL: GAMEMD 0xB0FB7C — loading-screen palette sets (three, stride 8).
extern PaletteSet DAT_00B0FB7C;
// GLOBAL: GAMEMD 0xB0FB84
extern PaletteSet DAT_00B0FB84;
// GLOBAL: GAMEMD 0xB0FB8C
extern PaletteSet DAT_00B0FB8C;

// GLOBAL: GAMEMD 0xB0FB94 — multiplayer-lobby palette sets (two, stride 8).
extern PaletteSet DAT_00B0FB94;
// GLOBAL: GAMEMD 0xB0FB9C
extern PaletteSet DAT_00B0FB9C;

// GLOBAL: GAMEMD 0xB0FBB0 — the multiplayer-screen palette set.
extern PaletteSet DAT_00B0FBB0;
// GLOBAL: GAMEMD 0xB0FBB8 — the multiplayer-screen loaded flag.
extern bool DAT_00B0FBB8;
// GLOBAL: GAMEMD 0xB0FC7D — the multiplayer-screen file-block allocated flag.
extern bool DAT_00B0FC7D;

// GLOBAL: GAMEMD 0xB0FBBC — the fourth full-screen-menu palette set.
extern PaletteSet DAT_00B0FBBC;

// GLOBAL: GAMEMD 0xB0FBC8 — audio/timer palette sets (three, stride 8).
extern PaletteSet DAT_00B0FBC8;
// GLOBAL: GAMEMD 0xB0FBD0
extern PaletteSet DAT_00B0FBD0;
// GLOBAL: GAMEMD 0xB0FBD8
extern PaletteSet DAT_00B0FBD8;

// GLOBAL: GAMEMD 0xB0FCB0 — full-screen-menu palette sets (three, stride 8).
extern PaletteSet DAT_00B0FCB0;
// GLOBAL: GAMEMD 0xB0FCB8
extern PaletteSet DAT_00B0FCB8;
// GLOBAL: GAMEMD 0xB0FCC0
extern PaletteSet DAT_00B0FCC0;

// GLOBAL: GAMEMD 0xB0FD38 — the quickmatch screen resource block.
extern ScreenPaletteRes DAT_00B0FD38;
// GLOBAL: GAMEMD 0xB0FD44 — the auto-login query screen resource block.
extern ScreenPaletteRes DAT_00B0FD44;

// ---------------------------------------------------------------------------
// The family
// ---------------------------------------------------------------------------

void __cdecl FreeGamePalettePairs();                                  // 0x72B230
void ReloadLoadingScreenVariant(const char* name);         // 0x72B390
void EnsureLoadingScreenPalettes(int sideIndex);           // 0x72B3E0
void __cdecl FreeLoadingScreenPalettes();                             // 0x72B460
void ReloadMpLobbySecondaryPalette(const char* name);      // 0x72B820
void __cdecl FreeMpLobbyPalettes();                                   // 0x72B870
void __cdecl EnsureAutoLoginQueryPalette();                           // 0x72BCA0
void __cdecl FreeAutoLoginQueryPalette();                             // 0x72BCF0
void __cdecl EnsureQuickmatchPalette();                               // 0x72BE80
void __cdecl FreeQuickmatchPalette();                                 // 0x72BED0
void EnsureMpScreenPalette(int sideIndex);                 // 0x72D730
void __cdecl FreeMpScreenPalette();                                   // 0x72D780
void __cdecl FreeFsMenuPalettes();                                    // 0x72DCF0
void __cdecl FreeAudioTimerPairs();                                   // 0x72F140

#endif  // GG_MATCH_RENDERER_SCREEN_PALETTE_MGR_METHODS_H
