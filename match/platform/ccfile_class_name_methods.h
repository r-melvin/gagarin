// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp (consult-only, no LICENSE; every
//   offset reconfirmed numerically against the disasm below).
//
// Translation unit for two RawFileClass name/bias primitives:
//   0x65CAC0 RawFileClass::SetFileName  (virtual slot 2)
//   0x65D2B0 RawFileClass::Bias         (non-virtual helper)
//
// The FileClass hierarchy (the MIX/CD/raw file stack):
//   FileClass (abstract COM-ish base) -> RawFileClass -> ...
//
// Confirmed offsets (from the matched bodies):
//   RawFileClass::FilePointer       [ESI+0x0C]  (SetFileName/Bias write it)
//   RawFileClass::FileSize          [ESI+0x10]  (SetFileName/Bias write it)
//   RawFileClass::FileName          [ESI+0x18]  (SetFileName reads/writes it)
//   RawFileClass::FileNameAllocated [ESI+0x20]  (SetFileName reads/writes it)
// vtable slots dispatched through (FileClass declaration order):
//   HasHandle @ +0x18 (slot 6)  -- CALL [EDX+0x18] in Bias
//   CDCheck   @ +0x40 (slot 16) -- CALL [EAX+0x40] in SetFileName
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_NAME_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_NAME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled here as a 4-byte
// scalar (the matched code only uses its 32-bit width when forwarding).
typedef unsigned int FileAccessMode;

// CRT-ish primitives the matched bodies call through __cdecl with a single
// stack argument (ADD ESP,4 cleanup). Declared bodiless so cl emits a direct
// CALL that the differ normalises as a relocation.
//   GameFree   == 0x7C93E8 (free(block))
//   FUN_007D5408 == 0x7D5408 (strdup(str))
void  __cdecl GameFree(void* block);
char* __cdecl FUN_007D5408(const char* str);

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// the dispatched slots land at their confirmed offsets (HasHandle @ +0x18,
// CDCheck @ +0x40).
// ---------------------------------------------------------------------------
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
    virtual bool Open(FileAccessMode access);                      // slot 7  (+0x1C)
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

// ---------------------------------------------------------------------------
// RawFileClass — a real file in the game directory. SetFileName (slot 2) is
// matched here; Bias is a non-virtual helper. GetFileSize and Seek are called
// class-qualified (direct CALL, reloc).
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    virtual const char* SetFileName(const char* pFileName);  // GAMEMD 0x65CAC0 (matched here)
    virtual int  Seek(int offset, int mode);                 // GAMEMD 0x65CF00 (decl; direct call)
    virtual int  GetFileSize();                              // GAMEMD 0x65D0D0 (decl; direct call)

    void Bias(int offset, int length);   // GAMEMD 0x65D2B0 (matched here)

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

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, FilePointer)      == 0x0C);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileSize)         == 0x10);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)         == 0x18);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileNameAllocated)== 0x20);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_NAME_METHODS_H
