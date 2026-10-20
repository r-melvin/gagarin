// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x476D80: the cached flag is `CMP [ESI+0x40],BL` /
//   `MOV byte ptr [ESI+0x40],1`, the digest is `LEA ECX,[ESI+0x41]` /
//   `ADD ESI,0x41` with length 0x14. The stack hash engine at `[ESP+0x14]` is
//   laid out from its inline constructor: `[+0x04]=0`, `[+0x08]=0`,
//   `byte [+0x0C]=0`, `[+0x24..+0x34]` = the five SHA-1 seeds, `[+0x38]=0`,
//   `[+0x3C]=0`, `[+0x00]=0x7E4D78`; the frame gives it 0x80 bytes. The CRC
//   engine at `[ESP+0x08]` is three zeroed dwords. Method name from YRpp
//   (consult-only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E4D78 — the hash engine's vtable (installed inline).
extern char VT_007E4D78;

// The SHA-1 engine as built on the stack. Constructed inline by the caller,
// torn down by the out-of-line destructor.
struct SHA_00476D80
{
    char*         Vtable;         // +0x0000
    int           Length;         // +0x0004
    int           PartialCount;   // +0x0008
    char          IsCached;       // +0x000C
    char          _pad00D[3];     // +0x000D
    char          FinalResult[0x14]; // +0x0010
    unsigned int  Acc[5];         // +0x0024
    int           unknown_38;     // +0x0038
    int           unknown_3C;     // +0x003C
    char          Partial[0x40];  // +0x0040

    // FUNCTION: GAMEMD 0x69E9E0 (decl; reloc) — copy the digest out.
    void Result(void* out);
    // FUNCTION: GAMEMD 0x631C80 (decl; reloc) — destructor.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(SHA_00476D80, Length) == 0x04);
GG_STATIC_ASSERT(offsetof(SHA_00476D80, PartialCount) == 0x08);
GG_STATIC_ASSERT(offsetof(SHA_00476D80, IsCached) == 0x0C);
GG_STATIC_ASSERT(offsetof(SHA_00476D80, Acc) == 0x24);
GG_STATIC_ASSERT(offsetof(SHA_00476D80, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(SHA_00476D80, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(SHA_00476D80) == 0x80);

// The CRC engine: running CRC, staging word, staging index.
struct CRC_00476D80
{
    int CRC;       // +0x0000
    int Staging;   // +0x0004
    int Index;     // +0x0008

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) — feed a block, return the CRC.
    int FUN_004A1DE0(const void* data, int length);
};
GG_STATIC_ASSERT(sizeof(CRC_00476D80) == 0x0C);

struct CCINI_00476D80
{
    char          _pad000[0x40];   // +0x0000
    char          DigestValid;     // +0x0040
    unsigned char Digest[0x14];    // +0x0041

    // FUNCTION: GAMEMD 0x526470 (decl; reloc) — hash the whole INI into the
    // engine.
    void FUN_00526470(SHA_00476D80* sha);

    // FUNCTION: GAMEMD 0x476D80 — CCINIClass::GetCRC.
    int GetCRC();
};
GG_STATIC_ASSERT(offsetof(CCINI_00476D80, DigestValid) == 0x40);
GG_STATIC_ASSERT(offsetof(CCINI_00476D80, Digest) == 0x41);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H
