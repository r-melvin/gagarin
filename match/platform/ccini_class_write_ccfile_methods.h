// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x474430: the file pipe at `[ESP+0x0C]` is built
//   inline (`[+0x0C]=file` first, then `[+0x04]=0`, `[+0x08]=0`,
//   `byte [+0x10]=0`, `[+0x00]=0x7E4DA0`) and torn down by 0x7BA420; the SHA
//   pipe at `[ESP+0x20]` is the same 0x80-byte inline construction as the
//   GetCRC sibling (`[+0x04]=0`, `[+0x08]=0`, `byte [+0x0C]=0`, the five
//   seeds at `[+0x24..+0x34]`, `[+0x38]=0`, `[+0x3C]=0`, `[+0x00]=0x7E4D78`)
//   and is torn down by 0x631C80. On the INI the digest flag is
//   `MOV byte ptr [ESI+0x40],1` and the digest `LEA EDI,[ESI+0x41]` with
//   length 0x14. The section name "Digest" is the literal at 0x81BFE0.
//   Method name from YRpp (consult-only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_CCFILE_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_CCFILE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E4DA0 — the file pipe's vtable (installed inline).
extern char VT_007E4DA0;
// VTABLE: GAMEMD 0x7E4D78 — the hash pipe's vtable (installed inline).
extern char VT_007E4D78;
// STRING: GAMEMD 0x81BFE0 — "Digest".
extern const char STR_0081BFE0[];

// The pipe base: vtable plus the two chain links.
struct Pipe_00474430
{
    char* Vtable;            // +0x0000
    int   ChainTo;           // +0x0004
    int   ChainFrom;         // +0x0008
};
GG_STATIC_ASSERT(sizeof(Pipe_00474430) == 0x0C);

struct File_00474430;

// The file-backed pipe as built on the stack: constructed inline by the
// caller, torn down out of line.
struct FilePipe_00474430 : Pipe_00474430
{
    File_00474430* File;     // +0x000C
    char           HasOpened;  // +0x0010
    char           _pad011[3]; // +0x0011

    // FUNCTION: GAMEMD 0x7BA420 (decl; reloc) — destructor.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(FilePipe_00474430, File) == 0x0C);
GG_STATIC_ASSERT(offsetof(FilePipe_00474430, HasOpened) == 0x10);
GG_STATIC_ASSERT(sizeof(FilePipe_00474430) == 0x14);

// The SHA-1 pipe as built on the stack (same shape as in
// match/platform/ccini_class_crc_methods.h; re-declared so this TU stands
// alone).
struct SHAPipe_00474430 : Pipe_00474430
{
    char          IsCached;        // +0x000C
    char          _pad00D[3];      // +0x000D
    char          FinalResult[0x14]; // +0x0010
    unsigned int  Acc[5];          // +0x0024
    int           Length;          // +0x0038
    int           PartialCount;    // +0x003C
    char          Partial[0x40];   // +0x0040

    // FUNCTION: GAMEMD 0x69E9E0 (decl; reloc) — copy the digest out.
    void Result(void* out);
    // FUNCTION: GAMEMD 0x631C80 (decl; reloc) — destructor.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(SHAPipe_00474430, IsCached) == 0x0C);
GG_STATIC_ASSERT(offsetof(SHAPipe_00474430, Acc) == 0x24);
GG_STATIC_ASSERT(offsetof(SHAPipe_00474430, Length) == 0x38);
GG_STATIC_ASSERT(offsetof(SHAPipe_00474430, PartialCount) == 0x3C);
GG_STATIC_ASSERT(sizeof(SHAPipe_00474430) == 0x80);

struct CCINI_00474430
{
    char          _pad000[0x40];   // +0x0000
    char          DigestValid;     // +0x0040
    unsigned char Digest[0x14];    // +0x0041

    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc) — Clear(section, key).
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526470 (decl; reloc) — Save(pipe): write the whole
    // INI into the pipe, returns the byte count.
    int Save(Pipe_00474430* pipe);
    // FUNCTION: GAMEMD 0x526E80 (decl; reloc) — PutUUBlock(section, block,
    // length).
    bool PutUUBlock(const char* section, const void* block, int length);

    // FUNCTION: GAMEMD 0x474430 — CCINIClass::WriteCCFile.
    int WriteCCFile(File_00474430* file, bool withDigest);
};
GG_STATIC_ASSERT(offsetof(CCINI_00474430, DigestValid) == 0x40);
GG_STATIC_ASSERT(offsetof(CCINI_00474430, Digest) == 0x41);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_CCFILE_METHODS_H
