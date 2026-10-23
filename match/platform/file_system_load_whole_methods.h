// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4A38D0: the file name arrives in ECX and the
//   out-flag in EDX (`MOV EBX,EDX; MOV byte ptr [EBX],0`), the stack file
//   object sits at `[ESP+0x0C]` and runs to the frame end (0x6C bytes), the
//   three virtuals dispatched are `CALL [EAX+0x14]` (one pushed argument, AL
//   result), `CALL [EDX+0x2C]` (no arguments, EAX result) and
//   `CALL [EAX+0x24]` (two pushed arguments). The inline teardown stores
//   0x7E16B0 at +0x00, zeroes +0x64, releases the sub-object at +0x58 through
//   0x43AE50, stores 0x7E1668 at +0x00 and calls 0x431B80. Names from YRpp
//  ; every offset re-derived here.
#ifndef GG_MATCH_PLATFORM_FILE_SYSTEM_LOAD_WHOLE_METHODS_H
#define GG_MATCH_PLATFORM_FILE_SYSTEM_LOAD_WHOLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) — MixFileClass::Retrieve, __fastcall
// with the force flag in DL.
void* FUN_005B40B0(const char* name, unsigned char force);

// LIBRARY: GAMEMD 0x7C8E17 (decl; reloc) — the allocator (operator new,
// __cdecl; caller pops).
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void FUN_00431B80(void* self);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_004A38D0;

struct File_004A38D0
{
    Vtbl_004A38D0* Vtbl;              // +0x0000
    char           _pad004[0x58 - 0x04];
    char           Sub58[0x64 - 0x58];// +0x0058  the released sub-object
    int            Reset64;           // +0x0064
    char           _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — constructor from a name.
    File_004A38D0* FUN_004739F0(const char* name);
};
GG_STATIC_ASSERT(offsetof(File_004A38D0, Sub58) == 0x58);
GG_STATIC_ASSERT(offsetof(File_004A38D0, Reset64) == 0x64);
GG_STATIC_ASSERT(sizeof(File_004A38D0) == 0x6C);

typedef bool (File_004A38D0::*Fn14_004A38D0)(int writeShared);
typedef int  (File_004A38D0::*Fn24_004A38D0)(void* buffer, int size);
typedef int  (File_004A38D0::*Fn2C_004A38D0)();

struct Vtbl_004A38D0
{
    char           _pad000[0x14];    // +0x0000
    Fn14_004A38D0  At_14;            // +0x0014  Exists(writeShared)
    char           _pad018[0x24 - 0x18];
    Fn24_004A38D0  At_24;            // +0x0024  ReadBytes(buffer, size)
    char           _pad028[0x2C - 0x28];
    Fn2C_004A38D0  At_2C;            // +0x002C  GetFileSize()
};
GG_STATIC_ASSERT(offsetof(Vtbl_004A38D0, At_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Vtbl_004A38D0, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Vtbl_004A38D0, At_2C) == 0x2C);

// FUNCTION: GAMEMD 0x4A38D0 — FileSystem::LoadWholeFileEx (static).
void* FileSystem_LoadWholeFileEx(const char* fileName, bool* allocated);

#endif  // GG_MATCH_PLATFORM_FILE_SYSTEM_LOAD_WHOLE_METHODS_H
