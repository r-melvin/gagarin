// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x408930. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC32_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC32_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "aligned_alloc_methods.h"

// Eight-byte entries starting at +0x20 of the source, indexed by the cursor's
// own channel number - `[EAX + ESI*8 + 0x20]` gives both the stride and the base.
typedef Aligned_00408D80 Source_00408930;

class FileClass;
struct Cursor_00408930
{
    char* unknown_00;
    int               unknown_04;   // +0x0004
    int               unknown_08;   // +0x0008
    Source_00408930*  unknown_0C;   // +0x000C
    // volatile: the stream threads 0x53E070 (CreateThread @0x53DF2A) and
    // 0x407680 (@0x407610) update this channel word in 0x409100 (@0x4091AC)
    // and 0x4091C0 (@0x40924A); this body clears bit 0 on the caller's thread
    // (0x408840, called @0x53E381 and @0x407B0F).
    volatile int      Flags;        // +0x0010
    int               Channel;      // +0x0014
    int unknown_18;
    int unknown_1C;
    int unknown_20;
    int unknown_24;
    Source_00408930*  Source;       // +0x0028
    int               unknown_2C;   // +0x002C
    unsigned unknown_30;
    int unknown_34;
    // Thread 0x53E070 (CreateThread @0x53DF2A) writes at0x409127;
    // callers read at0x409320. Stream thread0x407680 is created@0x407610.
    volatile int unknown_38;
    int unknown_3C;
    // FUNCTION: GAMEMD 0x408EE0
    int __fastcall FUN_00408EE0(void* buffer, unsigned count);
    // FUNCTION: GAMEMD 0x408F80
    int __fastcall FUN_00408F80(FileClass* file, int count, int* transferred);
    // FUNCTION: GAMEMD 0x409030
    int __fastcall FUN_00409030(void* file, int count, int* transferred);
    // FUNCTION: GAMEMD 0x409100
    int FUN_00409100();
    // FUNCTION: GAMEMD 0x4091C0
    int __fastcall FUN_004091C0(int count);
    // FUNCTION: GAMEMD 0x4092B0
    int FUN_004092B0();
    // FUNCTION: GAMEMD 0x409310 (decl; reloc)
    int FUN_00409310();
    // FUNCTION: GAMEMD 0x409340
    void* FUN_00409340();

    // FUNCTION: GAMEMD 0x408930
    void FUN_00408930();
};
GG_STATIC_ASSERT(offsetof(Cursor_00408930, Channel) == 0x14);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, Source) == 0x28);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_2C) == 0x2C);

GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(Cursor_00408930) == 0x40);
#endif  // GG_MATCH_CORE_SMALL_MISC32_METHODS_H
