// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x65CB50: `[ESI+0x8]` (the stored
//   access mode), `[ESI+0xC]` / `[ESI+0x10]` (file pointer / size, the seek
//   guard), `[ESI+0x14]` (the handle, INVALID_HANDLE_VALUE when closed),
//   `[ESI+0x18]` (the name); slots `CALL [EAX+0x34]` (Close),
//   `CALL [EDX+0x40]` (CDCheck, with 2), `CALL [EAX+0x28]` (Seek). The
//   hierarchy and slot order are the committed model in
//   match/platform/ccfile_class.h (not editable here, so the class is
//   redeclared locally with the Open override it lacks); YRpp CCFileClass.h
//   consulted for names only (consult-only, no LICENSE). YRpp binds 0x65CB50
//   to CCFileClass::Open; the bytes touch RawFileClass members and call
//   CreateFileA directly, and the committed model already places
//   CCFileClass::Open at 0x47AAB0, so this is RawFileClass::Open.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned int FileAccessMode;

// KERNEL32 CreateFileA through the IAT (retail: `CALL [0x7E11BC]`), so
// dllimport keeps the call indirect.
extern "C" __declspec(dllimport) void* __stdcall CreateFileA(
    const char* fileName, unsigned long desiredAccess, unsigned long shareMode,
    void* securityAttributes, unsigned long creationDisposition,
    unsigned long flagsAndAttributes, void* templateFile);

// FileClass — abstract base, virtuals in retail vtable order so Seek lands at
// +0x28, Close at +0x34 and CDCheck at +0x40.
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

// RawFileClass — a real file on disk.
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65CB50
    virtual int  Open(FileAccessMode access);

    FileAccessMode FileAccess;   // +0x08
    int   FilePointer;           // +0x0C
    int   FileSize;              // +0x10
    void* Handle;                // +0x14
    const char* FileName;        // +0x18
};
GG_STATIC_ASSERT(offsetof(RawFileClass, FileAccess)  == 0x08);
GG_STATIC_ASSERT(offsetof(RawFileClass, FilePointer) == 0x0C);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileSize)    == 0x10);
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)      == 0x14);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)    == 0x18);

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H
