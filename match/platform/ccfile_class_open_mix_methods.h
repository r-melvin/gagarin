// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x473D10: the unconditional close slot
//   `CALL [EAX+0x34]`, the mode test `TEST byte [ESP+0x20],2`, the buffered
//   probe 0x431F10 with 0 pushed, the four zeroed frame locals handed to
//   0x5B4430 (name in ECX, data in EDX, then mix / offset / size pushed),
//   the mix's `[EAX+0xC]` file name, the slots `[EDX+0x20]` (name, 1) and
//   `[EAX+0x28]` (0, 0), `[EDX+0x4]` GetFileName and `[EAX+0x8]`
//   SetFileName, the byte `[ESI+0x54]` raised and cleared around the
//   rename, the two 0x65D2B0 calls, the buffer sub-object at `[ESI+0x58]`
//   with 0x43AD00, and `[ESI+0x64]` (Position) zeroed. Offsets agree with
//   match/platform/ccfile_class_file_time_methods.h (Buffer 0x58, Position
//   0x64, Availability 0x68, sizeof 0x6C) and with the +0x54 flag in
//   match/platform/ccfile_class_set_name_methods.h. Names cross-checked
//   against YRpp (consult-only; NO LICENSE).
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_OPEN_MIX_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_OPEN_MIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// MixFileClass — only the archive's own file name at +0xC is read.
struct Mix_00473D10
{
    char        _pad000[0xC];   // +0x0000
    const char* FileName;       // +0x000C
};
GG_STATIC_ASSERT(offsetof(Mix_00473D10, FileName) == 0xC);

// FUNCTION: GAMEMD 0x5B4430 (decl; reloc) — MixFileClass::Offset, __fastcall:
// the name in ECX, the data out-pointer in EDX, then the mix, offset and size
// out-pointers on the stack.
bool __fastcall MixFileClass_Offset_00473D10(const char* name, void** data,
                                             Mix_00473D10** mix, int* offset,
                                             int* size);

struct CCFile_00473D10;


// LIBRARY: GAMEMD 0x7D5408 (decl; reloc) — CRT strdup.
extern "C" char* __cdecl gg_strdup(const char* s);
// FUNCTION: GAMEMD 0x7C93E8 (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* p);

// The +0x58 buffer sub-object; its setter takes both arguments on the stack
// and is reached through a pointer that retail null-tests first.
struct Buffer_00473D10
{
    char _pad000[0x64 - 0x58];

    // FUNCTION: GAMEMD 0x43AD00 (decl; reloc) — adopt(buffer, size).
    void FUN_0043AD00(void* buffer, int size);
};
GG_STATIC_ASSERT(sizeof(Buffer_00473D10) == 0xC);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00473D10;

// CCFileClass — a file that may live inside a MIX archive.
struct CCFile_00473D10
{
    Vtbl_00473D10*  Vtbl;         // +0x0000
    char            _pad004[0x50];  // +0x0004
    unsigned char   IsDisabled;   // +0x0054
    char            _pad055[3];   // +0x0055
    Buffer_00473D10 Buffer;       // +0x0058
    int             Position;     // +0x0064
    int             Availability; // +0x0068

    // FUNCTION: GAMEMD 0x47AAB0 (decl; reloc) — CDFileClass::Open, the base
    // implementation this one falls back to, called directly with the mode
    // pushed.
    int FUN_0047AAB0(unsigned int mode);

    // FUNCTION: GAMEMD 0x65D2B0 (decl; reloc) — the raw-file position
    // setter, called directly with both arguments pushed.
    void FUN_0065D2B0(int a, int b);

    // FUNCTION: GAMEMD 0x431F10 (decl; reloc) — the buffered-IO base probe,
    // called directly (not through the vtable) with its flag pushed.
    bool FUN_00431F10(int flag);

    // FUNCTION: GAMEMD 0x473D10 — CCFileClass::Open.
    int Open(unsigned int mode);
};
GG_STATIC_ASSERT(offsetof(CCFile_00473D10, IsDisabled)   == 0x54);
GG_STATIC_ASSERT(offsetof(CCFile_00473D10, Buffer)       == 0x58);
GG_STATIC_ASSERT(offsetof(CCFile_00473D10, Position)     == 0x64);
GG_STATIC_ASSERT(offsetof(CCFile_00473D10, Availability) == 0x68);
GG_STATIC_ASSERT(sizeof(CCFile_00473D10) == 0x6C);

typedef const char* (CCFile_00473D10::*Fn04_00473D10)();
typedef void        (CCFile_00473D10::*Fn08_00473D10)(const char* name);
typedef int         (CCFile_00473D10::*Fn20_00473D10)(const char* name, int flag);
typedef void        (CCFile_00473D10::*Fn28_00473D10)(int a, int b);
typedef void        (CCFile_00473D10::*Fn34_00473D10)();

struct Vtbl_00473D10
{
    char          _pad000[0x04];         // +0x0000
    Fn04_00473D10 GetFileName;           // +0x0004
    Fn08_00473D10 SetFileName;           // +0x0008
    char          _pad00C[0x20 - 0x0C];  // +0x000C
    Fn20_00473D10 At_20;                 // +0x0020
    char          _pad024[0x28 - 0x24];  // +0x0024
    Fn28_00473D10 At_28;                 // +0x0028
    char          _pad02C[0x34 - 0x2C];  // +0x002C
    Fn34_00473D10 Close;                 // +0x0034
};
GG_STATIC_ASSERT(offsetof(Vtbl_00473D10, GetFileName) == 0x04);
GG_STATIC_ASSERT(offsetof(Vtbl_00473D10, SetFileName) == 0x08);
GG_STATIC_ASSERT(offsetof(Vtbl_00473D10, At_20)       == 0x20);
GG_STATIC_ASSERT(offsetof(Vtbl_00473D10, At_28)       == 0x28);
GG_STATIC_ASSERT(offsetof(Vtbl_00473D10, Close)       == 0x34);

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_OPEN_MIX_METHODS_H
