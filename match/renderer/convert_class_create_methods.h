// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x72ADE0:
//     __fastcall with the file name in ECX, the palette out-reference in EDX
//     (`MOV EBX,EDX`, later re-read as `MOV EBX,[ESP+0x14]` inside the loop and
//     dereferenced by `ADD ECX,dword ptr [EBX]`), and the convert out-reference
//     as the single stack argument (`MOV EDX,[ESP+0x84]; MOV [EDX],EAX`;
//     RET 0x4).
//     The 0x6C-byte stack file object sits at [ESP+0x18] on entry, is built by
//     CALL 0x4739F0 (name pushed), read by CALL 0x4A3890, and torn down inline
//     exactly as at 0x6B5490 (0x7E16B0 at +0, +0x64 zeroed, CALL 0x43AE50 on
//     +0x58, 0x7E1668 at +0, CALL 0x431B80).
//     The palette block is 0x300 bytes (`PUSH 0x300` into 0x7C8E17) zero-filled
//     three bytes at a time over 0x100 iterations, so an entry is a 3-byte
//     ColorStruct and the palette is 0x100 of them; the destination index is
//     `i % 256` (`AND ECX,0x800000FF` + the signed fix-up) scaled by
//     `LEA ECX,[ECX+ECX*2]`.
//     The convert object is 0x188 bytes (`PUSH 0x188`) and its constructor
//     0x48E740 is called with (palette, palette, [0x887310], 1, 0).
//   The file object agrees with match/map/smudge_type_class_load_methods.h and
//   match/ui/preview_class_pcx_methods.h (neither edited; re-derived here so the
//   TU stands alone). Names cross-checked against YRpp
//   (every offset reconfirmed above).
#ifndef GG_MATCH_RENDERER_CONVERT_CLASS_CREATE_METHODS_H
#define GG_MATCH_RENDERER_CONVERT_CLASS_CREATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void __fastcall FUN_00431B80(void* self);
// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new, __cdecl.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — operator delete / free, __cdecl.
extern "C" void  __cdecl FUN_007C8B3D(void* block);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// CCFileClass on the stack (0x6C): only the pieces this function touches.
struct File_0072ADE0
{
    char*  Vtbl;                      // +0x0000
    char   _pad004[0x58 - 0x04];
    char   Sub58[0x64 - 0x58];        // +0x0058  the released sub-object
    int    Reset64;                   // +0x0064
    char   _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — constructor from a name.
    File_0072ADE0* FUN_004739F0(const char* name);
    // FUNCTION: GAMEMD 0x4A3890 (decl; reloc) — read the whole file.
    void* ReadWholeFile();
};
GG_STATIC_ASSERT(offsetof(File_0072ADE0, Sub58) == 0x58);
GG_STATIC_ASSERT(offsetof(File_0072ADE0, Reset64) == 0x64);
GG_STATIC_ASSERT(sizeof(File_0072ADE0) == 0x6C);

// One palette entry: three bytes, written as one struct store (a word for R/G
// plus a byte for B) at 0x72AE91.
struct ColorStruct_0072ADE0
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

};
GG_STATIC_ASSERT(sizeof(ColorStruct_0072ADE0) == 3);

// GLOBAL: GAMEMD 0x887310 — the surface the convert is built against.
extern void* DAT_00887310;

struct ConvertClass
{
    char _pad000[0x188];

    // FUNCTION: GAMEMD 0x48E740 (decl; reloc) — the constructor, spelled as an
    // ordinary __thiscall member returning `this` so the allocate/test/
    // construct expansion can be written out by hand (a real `new T(...)`
    // drags in a /GX EH frame retail does not have).
    ConvertClass* FUN_0048E740(ColorStruct_0072ADE0* palette,
                               ColorStruct_0072ADE0* eightBitPalette,
                               void* surface, int shadeCount, char skipBlitters);

    // FUNCTION: GAMEMD 0x72ADE0
    static void __fastcall CreateFromFile(const char* pFilename,
                                          ColorStruct_0072ADE0*& pPalette,
                                          ConvertClass*& pDestination);
};
GG_STATIC_ASSERT(sizeof(ConvertClass) == 0x188);

#endif  // GG_MATCH_RENDERER_CONVERT_CLASS_CREATE_METHODS_H
