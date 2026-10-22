// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x473F00: the base call `CALL 0x65D240` with `this`
//   in ECX (RawFileClass::SetFileTime, matched in
//   raw_file_class_time_methods.cpp); the name comes off vtable slot 1
//   (`CALL [EDX+0x4]`); the MIX lookup `CALL 0x5B4430` takes the name in
//   ECX, zero in EDX and three stacked words (the middle one the out
//   pointer); the found MIX file's name is `[EAX+0xC]`. The temporary file
//   object is a 0x6C-byte stack local built inline exactly as the 0x4739F0
//   constructor: base `CALL 0x47AA30`, the +0x58 buffer `CALL 0x43AD00(0,0)`,
//   `+0x64 = 0`, vtable 0x7E16B0, `+0x68 = 0`, then `CALL 0x47AE10(name)`;
//   its SetFileTime is slot 15 (`CALL [EDX+0x3C]`); the destructor chain
//   re-stores 0x7E16B0, zeroes +0x64, releases the buffer (`CALL 0x43AE50`),
//   stores the base vtable 0x7E1668 and calls the base destructor 0x431B80.
//   Class / method names from YRpp (names only).
//
// Retail has no exception frame around the temporary (plain `SUB ESP,0x70`,
// no FS:[0] registration). Under /GX, the tree's earlier flag set, a real
// constructor/
// destructor pair makes cl 12.00 emit the EH registration and an unwind
// funclet -- and `throw()` on every callee does not suppress it -- so the
// construction and destruction sequences are modelled as explicit
// `Construct` / `Destruct` members that the function calls in order.
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_SET_FILE_TIME_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_SET_FILE_TIME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// VTABLE: GAMEMD 0x7E16B0 -- CCFileClass.
extern char VT_007E16B0;
// VTABLE: GAMEMD 0x7E1668 -- CDFileClass (the base the destructor drops to).
extern char VT_007E1668;

// FUNCTION: GAMEMD 0x47AA30 (decl; reloc) -- the CDFileClass constructor.
void __fastcall FUN_0047AA30(void* self);
// FUNCTION: GAMEMD 0x43AE50 (decl; reloc) -- MemoryBuffer release.
void __fastcall FUN_0043AE50(void* buffer);
// FUNCTION: GAMEMD 0x431B80 (decl; reloc) -- the BufferIOFileClass destructor.
void __fastcall FUN_00431B80(void* self);

// The MIX archive record: only its file name at +0x0C is read.
struct Mix_00473F00
{
    char        _pad000[0x0C];   // +0x0000
    const char* FileName;        // +0x000C
};
GG_STATIC_ASSERT(offsetof(Mix_00473F00, FileName) == 0x0C);

// FUNCTION: GAMEMD 0x5B4430 (decl; reloc) -- MixFileClass::Offset: locate a
// file by name across the loaded archives; the archive comes back through
// the third argument.
bool __fastcall FUN_005B4430(const char* filename, void** data,
                             Mix_00473F00** mixfile, int* offset, int* length);

// MemoryBuffer (0x0C bytes): the (void*, int) constructor is out of line.
struct MemoryBuffer_00473F00
{
    void* Buffer;       // +0x0000
    int   Size;         // +0x0004
    char  Allocated;    // +0x0008
    char  _pad009[3];   // +0x0009

    // FUNCTION: GAMEMD 0x43AD00 (decl; reloc)
    void FUN_0043AD00(void* buffer, int size);
};
GG_STATIC_ASSERT(sizeof(MemoryBuffer_00473F00) == 0x0C);

// Declaration order matters -- see match/_rt/gg_vslot.h.
struct Vtbl_00473F00;

class CCFileClass
{
public:
    Vtbl_00473F00*        Vtbl;          // +0x0000
    char                  _pad004[0x54]; // +0x0004
    MemoryBuffer_00473F00 Buffer;        // +0x0058
    int                   Position;      // +0x0064
    int                   Availability;  // +0x0068

    // The 0x4739F0 constructor body: base, buffer, the two words and the
    // vtable, then the name through CDFileClass::SetFileName.
    void Construct(const char* filename)
    {
        FUN_0047AA30(this);
        this->Buffer.FUN_0043AD00(0, 0);
        this->Position     = 0;
        this->Vtbl         = (Vtbl_00473F00*)&VT_007E16B0;
        this->Availability = 0;
        this->FUN_0047AE10(filename);
    }

    // The destructor chain: this class's vtable, its one reset, the buffer
    // release, then the base vtable and the base destructor.
    void Destruct()
    {
        this->Vtbl     = (Vtbl_00473F00*)&VT_007E16B0;
        this->Position = 0;
        FUN_0043AE50(&this->Buffer);
        this->Vtbl     = (Vtbl_00473F00*)&VT_007E1668;
        FUN_00431B80(this);
    }

    // FUNCTION: GAMEMD 0x47AE10 (decl; reloc) -- CDFileClass::SetFileName.
    const char* FUN_0047AE10(const char* filename);

    // FUNCTION: GAMEMD 0x65D240 (decl; reloc) -- RawFileClass::SetFileTime,
    // the base implementation (matched in raw_file_class_time_methods.cpp).
    bool FUN_0065D240(unsigned long fileTime);

    // FUNCTION: GAMEMD 0x473F00
    bool SetFileTime(unsigned long fileTime);
};
GG_STATIC_ASSERT(offsetof(CCFileClass, Buffer) == 0x58);
GG_STATIC_ASSERT(offsetof(CCFileClass, Position) == 0x64);
GG_STATIC_ASSERT(offsetof(CCFileClass, Availability) == 0x68);
GG_STATIC_ASSERT(sizeof(CCFileClass) == 0x6C);

typedef const char* (CCFileClass::*Fn04_00473F00)();
typedef bool (CCFileClass::*Fn3C_00473F00)(unsigned long fileTime);

struct Vtbl_00473F00
{
    char          _pad000[0x04];          // +0x0000
    Fn04_00473F00 GetFileName;            // +0x0004  slot 1
    char          _pad008[0x3C - 0x08];   // +0x0008
    Fn3C_00473F00 SetFileTime;            // +0x003C  slot 15
};
GG_STATIC_ASSERT(offsetof(Vtbl_00473F00, GetFileName) == 0x04);
GG_STATIC_ASSERT(offsetof(Vtbl_00473F00, SetFileTime) == 0x3C);

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_SET_FILE_TIME_METHODS_H
