// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x473E50: the direct base call 0x65D1F0 on `this`,
//   the name slot `CALL [EDX+0x4]` feeding 0x5B4430 in ECX with EDX = 0 and
//   (&mix, 0, 0) pushed, the mix's `[EAX+0xC]` (its file name), the stack
//   file object at `[ESP+0x10]` running to the frame end (0x6C bytes) built
//   inline: 0x47AA30 on it, 0x43AD00 on +0x58 with (0, 0) pushed, 0x7E16B0
//   stored at +0x00, zeroes at +0x64 / +0x68, then 0x47AE10 with the name
//   pushed; the time slot `CALL [EDX+0x38]`; and the inline teardown that
//   stores 0x7E16B0, zeroes +0x64, releases +0x58 through 0x43AE50, stores
//   0x7E1668 and calls 0x431B80. Names from YRpp
//  ; every offset re-derived here
//   and consistent with match/platform/file_system_load_whole_methods.h and
//   match/core/small_misc38_methods.h (the 0x4739F0 constructor shape).
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_FILE_TIME_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_FILE_TIME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// MixFileClass — only the file name at +0xC is read.
struct Mix_00473E50
{
    char        _pad000[0xC];   // +0x0000
    const char* FileName;       // +0x000C
};
GG_STATIC_ASSERT(offsetof(Mix_00473E50, FileName) == 0xC);

// FUNCTION: GAMEMD 0x5B4430 (decl; reloc) — MixFileClass::Offset, __fastcall:
// the name in ECX, the data out-pointer in EDX, then the mix out-pointer, the
// offset out-pointer and the size out-pointer on the stack.
bool __fastcall MixFileClass_Offset(const char* name, void** data,
                                    Mix_00473E50** mix, int* offset, int* size);

// FUNCTION: GAMEMD 0x47AA30 (decl; reloc) — the base (CDFileClass) constructor.
void __fastcall FUN_0047AA30(void* self);
// FUNCTION: GAMEMD 0x43AE50 (decl; reloc) — release the buffer sub-object.
void __fastcall FUN_0043AE50(void* holder);
// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void __fastcall FUN_00431B80(void* self);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// The +0x58 buffer member's constructor takes both arguments on the stack.
struct Buffer_00473E50
{
    char _pad000[0x64 - 0x58];

    // FUNCTION: GAMEMD 0x43AD00 (decl; reloc)
    void FUN_0043AD00(int a, int b);
};
GG_STATIC_ASSERT(sizeof(Buffer_00473E50) == 0xC);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00473E50;

// CCFileClass — a file that may live inside a MIX archive.
struct CCFileClass
{
    Vtbl_00473E50*  Vtbl;       // +0x0000
    char            _pad004[0x58 - 0x04];
    Buffer_00473E50 Buffer;     // +0x0058
    int             Position;   // +0x0064
    int             Availability; // +0x0068

    // FUNCTION: GAMEMD 0x65D1F0 (decl; reloc) — RawFileClass::GetFileTime,
    // the base implementation called directly.
    unsigned long RawFileClass_GetFileTime();

    // FUNCTION: GAMEMD 0x47AE10 (decl; reloc) — CDFileClass::SetFileName.
    void FUN_0047AE10(const char* name);

    // The 0x4739F0 constructor body, inlined by retail at 0x473EA3: base
    // constructor, buffer constructor, Position (an initializer-list scalar,
    // stored before the vtable), this class's vtable, Availability (a body
    // store, after the vtable), then the name.
    void Construct(const char* name)
    {
        FUN_0047AA30(this);
        this->Buffer.FUN_0043AD00(0, 0);
        this->Position = 0;
        this->Vtbl = (Vtbl_00473E50*)&VT_007E16B0;
        this->Availability = 0;
        this->FUN_0047AE10(name);
    }

    // FUNCTION: GAMEMD 0x473E50
    unsigned long GetFileTime();
};
GG_STATIC_ASSERT(offsetof(CCFileClass, Buffer)       == 0x58);
GG_STATIC_ASSERT(offsetof(CCFileClass, Position)     == 0x64);
GG_STATIC_ASSERT(offsetof(CCFileClass, Availability) == 0x68);
GG_STATIC_ASSERT(sizeof(CCFileClass) == 0x6C);

typedef const char*  (CCFileClass::*Fn04_00473E50)();   // GetFileName
typedef unsigned long (CCFileClass::*Fn38_00473E50)();  // GetFileTime

struct Vtbl_00473E50
{
    char          _pad000[0x04];         // +0x0000
    Fn04_00473E50 GetFileName;           // +0x0004
    char          _pad008[0x38 - 0x08];  // +0x0008
    Fn38_00473E50 GetFileTime;           // +0x0038
};
GG_STATIC_ASSERT(offsetof(Vtbl_00473E50, GetFileName) == 0x04);
GG_STATIC_ASSERT(offsetof(Vtbl_00473E50, GetFileTime) == 0x38);

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_FILE_TIME_METHODS_H
