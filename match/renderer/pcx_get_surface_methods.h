// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6BA140: the 4-byte string key built in the first
//   parameter's home slot by 0x7B4630 (`LEA ECX,[ESP+0xC]` with the name
//   pushed) and torn down by 0x7B46F0 on both exits; the function-scope
//   static at 0xB0B948 (guard byte 0xB0B930 bit 0, teardown thunk 0x6BA220
//   registered through atexit 0x7C978A) whose first dword is zeroed by its
//   constructor and again before the lookup; the table's Count `[ESI+0x4]`,
//   the hash function pointer `CALL [ESI+0x18]` taking the key in ECX, the
//   bit width `[ESI+0xC]` (`SHL EDX,CL; DEC EDX; AND EDX,EAX`), the bucket
//   array `[ESI]` indexed `[EAX+EDX*4]`, the node's key compare 0x7B4780
//   (`PUSH &key; MOV ECX,node`), its next link `[ESI+0x308]`, its 0x304-byte
//   payload at +4 (`ADD ESI,4; MOV ECX,0xC1; REP MOVSD` into 0xB0B948) and
//   the 0x300-byte palette copied out from 0xB0B94C (`MOV ECX,0xC0`). The
//   method name and the palette type name are from YRpp (name only).
#ifndef GG_MATCH_RENDERER_PCX_GET_SURFACE_METHODS_H
#define GG_MATCH_RENDERER_PCX_GET_SURFACE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A heap-copied string key (one pointer). Constructed and destroyed through
// explicit calls so that no EH frame is registered under /GX.
struct PCXKey_006BA140
{
    char* Str;   // +0x00

    // FUNCTION: GAMEMD 0x7B4630 (decl; reloc) — build from a C string.
    void Construct(const char* name);
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc) — release the copy.
    void Destruct();
    // FUNCTION: GAMEMD 0x7B4780 (decl; reloc) — compare with another key.
    bool Equals(const PCXKey_006BA140* other);
};
GG_STATIC_ASSERT(sizeof(PCXKey_006BA140) == 4);

// 256 packed RGB triples.
struct BytePalette_006BA140
{
    unsigned char Bytes[0x300];
};
GG_STATIC_ASSERT(sizeof(BytePalette_006BA140) == 0x300);

// A cached PCX: its surface and palette.
struct PCXEntry_006BA140
{
    void*                 Surface;   // +0x000
    BytePalette_006BA140  Palette;   // +0x004
};
GG_STATIC_ASSERT(offsetof(PCXEntry_006BA140, Palette) == 0x004);
GG_STATIC_ASSERT(sizeof(PCXEntry_006BA140) == 0x304);

// The function-scope static that receives the hit. Its constructor zeroes
// the surface (the store inside the guard); the destructor is registered
// with atexit by the compiler.
struct PCXStatic_006BA140
{
    void*                 Surface;   // +0x000
    BytePalette_006BA140  Palette;   // +0x004

    PCXStatic_006BA140() { this->Surface = 0; }
    ~PCXStatic_006BA140();
};
GG_STATIC_ASSERT(sizeof(PCXStatic_006BA140) == 0x304);

// One hash-chain node: key, payload, next.
struct PCXNode_006BA140
{
    PCXKey_006BA140     Key;    // +0x000
    PCXEntry_006BA140   Data;   // +0x004
    PCXNode_006BA140*   Next;   // +0x308
};
GG_STATIC_ASSERT(offsetof(PCXNode_006BA140, Data) == 0x004);
GG_STATIC_ASSERT(offsetof(PCXNode_006BA140, Next) == 0x308);

// PCX — the hash table of loaded PCX files (YRpp PCX::Instance).
struct PCX
{
    PCXNode_006BA140** Table;      // +0x00  bucket heads
    int                Count;      // +0x04
    char               _pad08[4];  // +0x08
    int                Bits;       // +0x0C  log2 of the bucket count
    char               _pad10[8];  // +0x10
    unsigned int (__fastcall* Hash)(PCXKey_006BA140* key);   // +0x18

    // FUNCTION: GAMEMD 0x6BA140
    void* GetSurface(const char* filename, BytePalette_006BA140* palette);
};
GG_STATIC_ASSERT(offsetof(PCX, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(PCX, Bits) == 0x0C);
GG_STATIC_ASSERT(offsetof(PCX, Hash) == 0x18);

#endif  // GG_MATCH_RENDERER_PCX_GET_SURFACE_METHODS_H
