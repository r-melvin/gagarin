// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4741F0: the stack FileStraw (vtable 0x7E4D90 at
//   +0, ChainTo +4, ChainFrom +8, File +0xC, HasOpened +0x10, destructor
//   0x7BA590) handed to Load 0x525A60 with the second flag; `[ESI+0x40]`
//   (DigestValid) cleared and set, `[ESI+0x41]` (Digest) as the SHA result
//   target; GetUUBlock 0x526FB0 ("Digest" at 0x81BFE0, 0x14 bytes into a
//   frame buffer), Clear 0x5257C0, the stack SHAPipe (vtable 0x7E4D78, the
//   five SHA-1 seeds, Save 0x526470, Result 0x69E9E0, destructor 0x631C80)
//   and the five-dword `REPE CMPSD` digest compare. Same shapes as the
//   WriteCCFile twin in match/platform/ccini_class_write_ccfile_methods.h.
//   Names cross-checked against YRpp CCINIClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_READ_CCFILE_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_READ_CCFILE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E4D90 -- external address binding for FileStraw call view.
extern char VT_007E4D90;
// VTABLE: GAMEMD 0x7E4D78 -- external address binding for SHAPipe call view.
extern char VT_007E4D78;
// STRING: GAMEMD 0x81BFE0 -- "Digest".
extern const char STR_0081BFE0[];

struct Pipe_004741F0
{
    char* Vtable;            // +0x0000
    int   ChainTo;           // +0x0004
    int   ChainFrom;         // +0x0008
};
GG_STATIC_ASSERT(offsetof(Pipe_004741F0, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(Pipe_004741F0, ChainTo) == 4);
GG_STATIC_ASSERT(offsetof(Pipe_004741F0, ChainFrom) == 8);
GG_STATIC_ASSERT(sizeof(Pipe_004741F0) == 0x0C);

struct File_004741F0;

// FileStraw — the read-side twin of FilePipe.
struct FileStraw_004741F0 : Pipe_004741F0
{
    File_004741F0* File;       // +0x000C
    char           HasOpened;  // +0x0010
    char           _pad011[3]; // +0x0011

    // FUNCTION: GAMEMD 0x7BA590 (decl; reloc) — destructor.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(FileStraw_004741F0, File) == 0x0C);
GG_STATIC_ASSERT(offsetof(FileStraw_004741F0, HasOpened) == 0x10);
GG_STATIC_ASSERT(sizeof(FileStraw_004741F0) == 0x14);

struct SHAPipe_004741F0 : Pipe_004741F0
{
    char          IsCached;          // +0x000C
    char          _pad00D[3];        // +0x000D
    char          FinalResult[0x14]; // +0x0010
    unsigned int  Acc[5];            // +0x0024
    int           Length;            // +0x0038
    int           PartialCount;      // +0x003C
    char          Partial[0x40];     // +0x0040

    // FUNCTION: GAMEMD 0x69E9E0 (decl; reloc) — copy the digest out.
    void Result(void* out);
    // FUNCTION: GAMEMD 0x631C80 (decl; reloc) — destructor.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, ChainTo) == 4);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, ChainFrom) == 8);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, IsCached) == 0x0C);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, Acc) == 0x24);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, Length) == 0x38);
GG_STATIC_ASSERT(offsetof(SHAPipe_004741F0, PartialCount) == 0x3C);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(SHAPipe_004741F0) == 0x80);

struct CCINI_004741F0
{
    char          _pad000[0x40];   // +0x0000
    char          DigestValid;     // +0x0040
    unsigned char Digest[0x14];    // +0x0041

    // FUNCTION: GAMEMD 0x525A60 (decl; reloc) — Load(straw, flag): read the
    // whole INI from the straw, returns the load status.
    int Load(Pipe_004741F0* straw, bool flag);
    // FUNCTION: GAMEMD 0x526FB0 (decl; reloc) — GetUUBlock(section, block,
    // length): returns the decoded length, 0 when the section is absent.
    int GetUUBlock(const char* section, void* block, int length);
    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc) — Clear(section, key).
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526470 (decl; reloc) — Save(pipe).
    int Save(Pipe_004741F0* pipe);

    // FUNCTION: GAMEMD 0x4741F0 — CCINIClass::ReadCCFile.
    int ReadCCFile(File_004741F0* file, bool withDigest, bool flag);
    // FUNCTION: GAMEMD 0x474320 -- caller-supplied stream ABI view; original name unknown.
    int FUN_00474320(Pipe_004741F0* straw, bool withDigest, bool flag);
};
GG_STATIC_ASSERT(offsetof(CCINI_004741F0, DigestValid) == 0x40);
GG_STATIC_ASSERT(offsetof(CCINI_004741F0, Digest) == 0x41);
GG_STATIC_ASSERT(sizeof(((CCINI_004741F0*)0)->Digest) == 0x14);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_READ_CCFILE_METHODS_H
