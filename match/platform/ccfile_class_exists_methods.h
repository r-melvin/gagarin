// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x65CBF0: `[ESI+0x18]` (the name, the
//   null guard and the CreateFileA argument), `[ESI+0x14]` (the handle, stored
//   straight from CreateFileA and compared against INVALID_HANDLE_VALUE), the
//   slots `CALL [EAX+0x18]` / `CALL [EDX+0x18]` (HasHandle, twice) and
//   `CALL [EDI+0x40]` (CDCheck with GetLastError, 0, name), the direct
//   `CALL 0x65CB50` (RawFileClass::Open with 1) and the IAT calls
//   `[0x7E11BC]` CreateFileA, `[0x7E11E0]` CloseHandle, `[0x7E1200]`
//   GetLastError. YRpp CCFileClass.h consulted for the method name only
//   (consult-only, no LICENSE); the map binds 0x65CBF0 to CCFileClass::Exists,
//   the bytes are RawFileClass's (see raw_file_class_open_methods.h for the
//   same reasoning about 0x65CB50). The class is redeclared locally in the
//   proven slot order of match/platform/ccfile_class.h.
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_EXISTS_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_EXISTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned int FileAccessMode;

// KERNEL32 through the IAT (retail: `CALL [0x7E11BC]` / `[0x7E11E0]` /
// `[0x7E1200]`), so dllimport keeps every call indirect.
extern "C" __declspec(dllimport) void* __stdcall CreateFileA(
    const char* fileName, unsigned long desiredAccess, unsigned long shareMode,
    void* securityAttributes, unsigned long creationDisposition,
    unsigned long flagsAndAttributes, void* templateFile);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* handle);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError();

// FileClass — abstract base, virtuals in retail vtable order so HasHandle
// lands at +0x18, Close at +0x34 and CDCheck at +0x40.
class FileClass
{
public:
    virtual ~FileClass();                                          // slot 0  (+0x00)
    virtual const char* GetFileName() const;                       // slot 1  (+0x04)
    virtual const char* SetFileName(const char* pFileName);        // slot 2  (+0x08)
    virtual int  CreateFile();                                     // slot 3  (+0x0C)
    virtual int  DeleteFile();                                     // slot 4  (+0x10)
    virtual bool Exists(int forced);                               // slot 5  (+0x14)
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
    // FUNCTION: GAMEMD 0x65CB50 (decl; reloc)
    virtual int  Open(FileAccessMode access);
    // FUNCTION: GAMEMD 0x65CBF0
    virtual bool Exists(int forced);
    // FUNCTION: GAMEMD 0x65CCA0 — inlined into Exists at 0x65CC22..0x65CC8D.
    virtual void Close();

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

// The Close body (retail 0x65CCA0) is defined inline here so that the explicit
// `RawFileClass::Close()` call in Exists is inlined the way retail shows it.
inline void RawFileClass::Close()
{
    if (HasHandle()) {
        if (!CloseHandle(Handle)) {
            CDCheck(GetLastError(), 0, FileName);
        }
        Handle = (void*)-1;
    }
}

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_EXISTS_METHODS_H
