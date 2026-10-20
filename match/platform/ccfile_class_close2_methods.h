// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp CCFileClass.h (consult-only, no LICENSE; every
//   offset reconfirmed numerically against the disassembly below).
//
// Translation unit: RawFileClass::Close (GAMEMD 0x65CCA0).
//
// Self-contained restatement of the FileClass hierarchy (same vtable ordering
// as match/platform/ccfile_class_close_methods.h, self-guarded by
// GG_STATIC_ASSERT) so this override TU compiles independently.
//
// Confirmed from the matched body (0x65CCA0):
//   RawFileClass::Handle    [ESI+0x14]  (param_1[5])  -> CloseHandle arg, set -1
//   RawFileClass::FileName  [ESI+0x18]  (param_1[6])  -> CDCheck arg
// vtable slots (FileClass declaration order):
//   HasHandle @ +0x18 (slot 6)  — CALL [EAX+0x18]
//   CDCheck   @ +0x40 (slot 16) — CALL [EDI+0x40]
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE2_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE2_METHODS_H

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar (the matched code only relies on its 32-bit width).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// HasHandle lands at slot +0x18 and CDCheck at slot +0x40.
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
    virtual void CDCheck(unsigned long code, BOOL b, const char* f);// slot 16 (+0x40)

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

// ---------------------------------------------------------------------------
// RawFileClass — a real file in the game directory.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    virtual void Close();                       // GAMEMD 0x65CCA0 (matched here)

    FileAccessMode FileAccess;   // +0x08
    int   FilePointer;           // +0x0C
    int   FileSize;              // +0x10
    HANDLE Handle;               // +0x14
    const char* FileName;        // +0x18
    short unknown_short_1C;      // +0x1C
    short unknown_short_1E;      // +0x1E
    bool  FileNameAllocated;     // +0x20
private:
    char  padding_21[3];         // +0x21
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)   == 0x14);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName) == 0x18);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE2_METHODS_H
