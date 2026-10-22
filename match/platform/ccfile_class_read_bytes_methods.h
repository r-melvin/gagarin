// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x473B10 (member-access + virtual-call
//   disassembly), cross-checked against YRpp (every offset reconfirmed numerically against the disasm):
//     CCFileClass::Buffer.Buffer  [ESI+0x58]  (TEST EDX,EDX @0x473B32; ADD ECX,EDX)
//     CCFileClass::Buffer.Size    [ESI+0x5C]  (MOV EAX,[ESI+0x5C] @0x473B39)
//     CCFileClass::Position       [ESI+0x64]  (MOV ECX,[ESI+0x64] @0x473B36, +=)
//   vtable slots (FileClass declaration order, same as ccfile_class.h):
//     HasHandle @ +0x18 (slot 6)  -- CALL [EAX+0x18] @0x473B19, TEST AL,AL
//     Open      @ +0x1C (slot 7)  -- CALL [EDX+0x1C] @0x473B26, TEST EAX,EAX
//     Close     @ +0x34 (slot 13) -- CALL [EDX+0x34] @0x473B6D / 0x473B93
//   Base implementation BufferIOFileClass::ReadBytes @0x4322A0 called direct
//   (CALL @0x473B84); the copy is an out-of-line CRT memcpy @0x7CA090.
//
// The class stack is redeclared here (as every ccfile_class_*.h TU does) so the
// TU stands alone; the facts match match/platform/ccfile_class.h.
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_READ_BYTES_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_READ_BYTES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"

typedef unsigned int FileAccessMode;

// CRT memcpy @0x7CA090. Retail calls it out of line (CALL, not the /Oi
// REP MOVSD expansion), so the .cpp disables the intrinsic with
// `#pragma function(memcpy)`.
extern "C" void* __cdecl memcpy(void* destination, const void* source, unsigned int count);



// FileClass — abstract base, virtuals in exact retail vtable order. Open is
// typed int here: retail tests its result with a full-width TEST EAX,EAX.
class FileClass
{
public:
    virtual ~FileClass();                                          // slot 0  (+0x00)
    virtual const char* GetFileName() const;                       // slot 1  (+0x04)
    virtual const char* SetFileName(const char* pFileName);        // slot 2  (+0x08)
    virtual int  CreateFile();                                     // slot 3  (+0x0C)
    virtual int  DeleteFile();                                     // slot 4  (+0x10)
    virtual bool Exists(bool writeShared);                         // slot 5  (+0x14)
    virtual bool HasHandle();                                      // slot 6  (+0x18)
    virtual int  Open(FileAccessMode access);                      // slot 7  (+0x1C)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a);  // slot 8  (+0x20)
    virtual int  ReadBytes(void* pBuffer, int nBytes);             // slot 9  (+0x24)
    virtual int  Seek(int offset, int mode);                       // slot 10 (+0x28)
    virtual int  GetFileSize();                                    // slot 11 (+0x2C)
    virtual int  WriteBytes(void* pBuffer, int nBytes);            // slot 12 (+0x30)
    virtual void Close();                                          // slot 13 (+0x34)
    virtual unsigned long GetFileTime();                           // slot 14 (+0x38)
    virtual bool SetFileTime(unsigned long fileTime);              // slot 15 (+0x3C)
    virtual void CDCheck(unsigned long code, bool b, const char* f);// slot 16 (+0x40)

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

class RawFileClass : public FileClass
{
public:
    FileAccessMode FileAccess;   // +0x08
    int   FilePointer;           // +0x0C
    int   FileSize;              // +0x10
    void* Handle;                // +0x14
    const char* FileName;        // +0x18
    short unknown_short_1C;      // +0x1C
    short unknown_short_1E;      // +0x1E
    bool  FileNameAllocated;     // +0x20
private:
    char  padding_21[3];         // +0x21
};

class BufferIOFileClass : public RawFileClass
{
public:
    // FUNCTION: GAMEMD 0x4322A0 (decl; reloc) — the unbuffered base read.
    virtual int  ReadBytes(void* pBuffer, int nBytes);

    bool unknown_bool_24;   // +0x24
    bool unknown_bool_25;   // +0x25
    bool unknown_bool_26;   // +0x26
    bool unknown_bool_27;   // +0x27
    bool unknown_bool_28;   // +0x28
    bool unknown_bool_29;   // +0x29
private:
    char padding_2A[2];     // +0x2A
public:
    unsigned int unknown_2C;   // +0x2C
    unsigned int unknown_30;   // +0x30
    unsigned int unknown_34;   // +0x34
    unsigned int unknown_38;   // +0x38
    unsigned int unknown_3C;   // +0x3C
    unsigned int unknown_40;   // +0x40
    int unknown_int_44;        // +0x44
    int unknown_int_48;        // +0x48
    unsigned int unknown_4C;   // +0x4C
    unsigned int unknown_50;   // +0x50
};

class CDFileClass : public BufferIOFileClass
{
public:
    bool IsDisabled;        // +0x54
private:
    char padding_55[3];     // +0x55
};

class CCFileClass : public CDFileClass
{
public:
    // FUNCTION: GAMEMD 0x473B10
    virtual int ReadBytes(void* pBuffer, int nBytes);

    MemoryBuffer Buffer;      // +0x58
    int          Position;    // +0x64 (signed: the clamp is a JGE)
    unsigned int Availability;// +0x68
};
GG_STATIC_ASSERT(offsetof(CCFileClass, Buffer)       == 0x58);
GG_STATIC_ASSERT(offsetof(CCFileClass, Position)     == 0x64);
GG_STATIC_ASSERT(offsetof(CCFileClass, Availability) == 0x68);

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_READ_BYTES_METHODS_H
