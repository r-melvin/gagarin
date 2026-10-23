// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x65D0D0:
//     FilePointer [ESI+0x0C] (SUB EAX,ECX @0x65D113 / 0x65D13E)
//     FileSize    [ESI+0x10] (CMP EAX,-1 @0x65D0D9; stores @0x65D116/0x65D140)
//     Handle      [ESI+0x14] (PUSH ECX @0x65D0EB -> GetFileSize)
//     FileName    [ESI+0x18] (PUSH EDX @0x65D0FF -> CDCheck)
//   vtable slots dispatched: HasHandle +0x18 (CALL [EAX+0x18] @0x65D0E0),
//     Open +0x1C (CALL [EAX+0x1C] @0x65D122), GetFileSize +0x2C
//     (CALL [EDX+0x2C] @0x65D12D), Close +0x34 (CALL [EAX+0x34] @0x65D136),
//     CDCheck +0x40 (CALL [EBX+0x40] @0x65D10B).
//   Imports: IAT 0x7E1120 KERNEL32 GetFileSize, IAT 0x7E1200 GetLastError.
//   The member run mirrors the already-confirmed layout in
//   match/platform/ccfile_class.h (not edited; re-declared here so the TU
//   stands alone); YRpp consulted for names only.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_SIZE_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_SIZE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar (the matched body only pushes the literal 1 == Read through it).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// the dispatched slots land at their confirmed offsets. Open is declared as
// returning int here: retail tests its result with TEST EAX,EAX (full width),
// whereas HasHandle is tested with TEST AL,AL (bool).
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
    virtual int  Open(FileAccessMode access);                      // slot 7  (+0x1C)
    virtual int OpenEx(const char* pFileName, FileAccessMode a);  // slot 8  (+0x20)
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
// RawFileClass — a real file in the game directory. GetFileSize (slot 11) is
// matched here.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65D0D0
    virtual int  GetFileSize();

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

GG_STATIC_ASSERT(offsetof(RawFileClass, FilePointer) == 0x0C);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileSize)    == 0x10);
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)      == 0x14);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)    == 0x18);
GG_STATIC_ASSERT(sizeof(RawFileClass) == 0x24);

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_SIZE_METHODS_H
