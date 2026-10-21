// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x641DB0:
//     PreviewClass  ImageSurface at [EDI+0x0] (MOV ECX,[EDI] / MOV [EDI],EAX).
//     the 0x6C-byte stack file object at [ESP+0xC], built by CALL 0x4739F0
//     (name pushed), probed by CALL 0x473C50 with a pushed 0, and torn down
//     inline exactly as at 0x6B5490: 0x7E16B0 stored at +0, +0x64 zeroed,
//     CALL 0x43AE50 on +0x58, 0x7E1668 stored at +0, CALL 0x431B80 on +0.
//     Surface vtable slots, all read off the retail indirect calls:
//       [EAX+0x00] the scalar deleting destructor (PUSH 1)
//       [EAX+0x04] blit-from  (PUSH 1; PUSH 0; PUSH src)
//       [EAX+0x18] clear      (PUSH 0)
//       [EAX+0x7C] width      (no arguments)
//       [EAX+0x80] height     (no arguments)
//     The allocated surface is 0x24 bytes (PUSH 0x24 into 0x7C8E17) and its
//     constructor 0x4BA5A0 takes (width, height, 1, 0) — width lands at
//     [ESI+0x4] and height at [ESI+0x8] inside that constructor.
//   The file object agrees with match/map/smudge_type_class_load_methods.h and
//   match/platform/file_system_load_whole_methods.h (neither edited; re-derived
//   here so the TU stands alone). Names cross-checked against YRpp
//   PreviewClass.h (consult-only; NO LICENSE; every offset reconfirmed above).
#ifndef GG_MATCH_UI_PREVIEW_CLASS_PCX_METHODS_H
#define GG_MATCH_UI_PREVIEW_CLASS_PCX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void __fastcall FUN_00431B80(void* self);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// CCFileClass on the stack (0x6C): only the pieces this function touches.
struct File_00641DB0
{
    char*  Vtbl;                      // +0x0000
    char   _pad004[0x58 - 0x04];
    char   Sub58[0x64 - 0x58];        // +0x0058  the released sub-object
    int    Reset64;                   // +0x0064
    char   _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — constructor from a name.
    File_00641DB0* FUN_004739F0(const char* name);
    // FUNCTION: GAMEMD 0x473C50 (decl; reloc) — CCFileClass::Exists.
    bool Exists(int writeShared);
};
GG_STATIC_ASSERT(offsetof(File_00641DB0, Sub58) == 0x58);
GG_STATIC_ASSERT(offsetof(File_00641DB0, Reset64) == 0x64);
GG_STATIC_ASSERT(sizeof(File_00641DB0) == 0x6C);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00641DB0;

// The 0x24-byte surface: both the object the PCX loader hands back and the one
// this function allocates.
struct Surface_00641DB0
{
    Vtbl_00641DB0* Vtbl;      // +0x0000
    char _pad004[0x24 - 0x04];

    // FUNCTION: GAMEMD 0x4BA5A0 (decl; reloc) — the constructor, spelled as an
    // ordinary __thiscall member returning `this` so the allocate/test/construct
    // expansion can be written out by hand (a real ctor called through `new`
    // drags in a /GX EH frame retail does not have).
    Surface_00641DB0* FUN_004BA5A0(int width, int height, char a, char b);
};
GG_STATIC_ASSERT(sizeof(Surface_00641DB0) == 0x24);

typedef void* (Surface_00641DB0::*Fn000_00641DB0)(char freeFlag);
typedef void  (Surface_00641DB0::*Fn004_00641DB0)(Surface_00641DB0* src, int a, int b);
typedef void  (Surface_00641DB0::*Fn018_00641DB0)(int colour);
typedef int   (Surface_00641DB0::*Fn07C_00641DB0)();
typedef int   (Surface_00641DB0::*Fn080_00641DB0)();

struct Vtbl_00641DB0
{
    Fn000_00641DB0 At_000;                 // +0x0000
    Fn004_00641DB0 At_004;                 // +0x0004
    char _pad008[0x18 - 0x08];
    Fn018_00641DB0 At_018;                 // +0x0018
    char _pad01C[0x7C - 0x1C];
    Fn07C_00641DB0 At_07C;                 // +0x007C
    Fn080_00641DB0 At_080;                 // +0x0080
};
GG_STATIC_ASSERT(offsetof(Vtbl_00641DB0, At_004) == 0x4);
GG_STATIC_ASSERT(offsetof(Vtbl_00641DB0, At_018) == 0x18);
GG_STATIC_ASSERT(offsetof(Vtbl_00641DB0, At_07C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Vtbl_00641DB0, At_080) == 0x80);

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new, __cdecl.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

// FUNCTION: GAMEMD 0x630310 (decl; reloc) — Read_PCX_File(file, palette,
// buffer, size); the file arrives in ECX and the palette in EDX.
Surface_00641DB0* __fastcall FUN_00630310(File_00641DB0* file, char* palette,
                                          void* buffer, long size);

struct PreviewClass
{
    Surface_00641DB0* ImageSurface;   // +0x0000

    // FUNCTION: GAMEMD 0x641DB0
    bool ReadPCXPreview(const char* lpFile);
};
GG_STATIC_ASSERT(offsetof(PreviewClass, ImageSurface) == 0x0);

#endif  // GG_MATCH_UI_PREVIEW_CLASS_PCX_METHODS_H
