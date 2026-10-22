// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x552490: `CMP dword [ESI+0xC],1` (the mode word),
//   `MOV EAX,[ESI+0x10]` / `MOV [ESI+0x10],ECX` (the pending counter),
//   `MOV EDX,[ESI+0x14]` (the working buffer), `MOV ECX,[ESI+0x18]` (the
//   second buffer, whose payload starts 4 bytes in), `MOV EDX,[ESI+0x1C]`
//   (the block size), `MOV EDI,[ESI+0x20]` (the extra margin added to the
//   block size when the compressed block is staged at the far end of the
//   buffer), and the 4-byte block header taken by `LEA EBX,[ESI+0x24]` and
//   read half-wise as `MOV CX,word [ESI+0x24]` (compressed count) and
//   `MOV DX,word [ESI+0x26]` (uncompressed count), both zero-extended.
//   Conventions read off the call sites: 0x6C98E0 is `MOV ECX,ESI; CALL`
//   with two pushed arguments (__thiscall base Get); 0x551E50 and 0x551C60
//   both set ECX and EDX with a single pushed dword (__fastcall); 0x7CA090
//   is the __cdecl CRT memmove (three pushes plus `ADD ESP,0xC`). The class
//   name comes from the RTTI type descriptor ".?AVLCWStraw@@".
#ifndef GG_MATCH_PLATFORM_STRAWS_GET_METHODS_H
#define GG_MATCH_PLATFORM_STRAWS_GET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7CA090 (decl; reloc) — CRT memmove, called out of line.
extern "C" void* __cdecl memmove(void* destination, const void* source, unsigned int count);

// The 4-byte block header that prefixes every compressed block.
struct BlockHeader_00552490
{
    unsigned short PackedSize;     // +0x00
    unsigned short UnpackedSize;   // +0x02
};
GG_STATIC_ASSERT(sizeof(BlockHeader_00552490) == 4);

// FUNCTION: GAMEMD 0x551E50 (decl; reloc) — compressor (src, dest, count),
// __fastcall (source in ECX, destination in EDX, count pushed), returns the
// compressed length in AX.
unsigned int __fastcall FUN_00551E50(const void* source, void* destination,
                                     unsigned int count);
// FUNCTION: GAMEMD 0x551C60 (decl; reloc) — decompressor (src, dest, 0),
// __fastcall (source in ECX, destination in EDX, the third argument pushed
// as a literal zero here).
void __fastcall FUN_00551C60(const void* source, void* destination, int length);

struct Straw_00552490
{
    char                 _pad000[0xC];    // +0x0000  vtable + the base Straw
    int                  Control;         // +0x000C  1 = decompressing
    int                  Counter;         // +0x0010  bytes still pending
    char*                Buffer;          // +0x0014
    char*                Buffer2;         // +0x0018
    int                  BlockSize;       // +0x001C
    int                  SafetyMargin;    // +0x0020
    BlockHeader_00552490 Header;     // +0x0024

    // FUNCTION: GAMEMD 0x6C98E0 (decl; reloc) — Straw::Get, the base-class
    // pull that this straw chains to (__thiscall, two pushed arguments).
    int Get_006C98E0(void* buffer, int length);

    // FUNCTION: GAMEMD 0x552490
    int Get(void* dest, int slen);
};
GG_STATIC_ASSERT(offsetof(Straw_00552490, Control)      == 0x0C);
GG_STATIC_ASSERT(offsetof(Straw_00552490, Counter)      == 0x10);
GG_STATIC_ASSERT(offsetof(Straw_00552490, Buffer)       == 0x14);
GG_STATIC_ASSERT(offsetof(Straw_00552490, Buffer2)      == 0x18);
GG_STATIC_ASSERT(offsetof(Straw_00552490, BlockSize)    == 0x1C);
GG_STATIC_ASSERT(offsetof(Straw_00552490, SafetyMargin) == 0x20);
GG_STATIC_ASSERT(offsetof(Straw_00552490, Header)  == 0x24);

#endif  // GG_MATCH_PLATFORM_STRAWS_GET_METHODS_H
