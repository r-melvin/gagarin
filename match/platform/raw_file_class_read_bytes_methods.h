// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x65CCE0:
//     FileSize    [ESI+0x10] (CMP EAX,-1 @0x65CD1B; SUB ECX,EAX @0x65CD31)
//     Handle      [ESI+0x14] (MOV EDX,[ESI+0x14] @0x65CD48 -> ReadFile)
//     FileName    [ESI+0x18] (MOV EAX,[ESI+0x18] @0x65CD7E -> CDCheck)
//   vtable slots dispatched: HasHandle +0x18 (CALL [EAX+0x18] @0x65CCF3),
//     Open +0x1C (CALL [EDX+0x1C] @0x65CD00), Seek +0x28 (CALL [EAX+0x28]
//     @0x65CD27), Close +0x34 (CALL [EDX+0x34] @0x65CDBF), CDCheck +0x40
//     (CALL [EBX+0x40] @0x65CD8F).
//   Imports: IAT 0x7E111C KERNEL32 ReadFile, IAT 0x7E1200 GetLastError.
//   Global byte 0xB04BEC (TEST AL,AL @0x65CD76; cleared @0x65CDB1); YRpp
//   names it IsReadingAudioFile.
//   The member run mirrors the already-confirmed layout in
//   match/platform/ccfile_class.h (not edited; re-declared here so the TU
//   stands alone); YRpp consulted for names only.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_READ_BYTES_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_READ_BYTES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar (the matched body only pushes the literal 1 == Read through it).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// the dispatched slots land at their confirmed offsets. Open returns int:
// retail tests its result with TEST EAX,EAX; HasHandle with TEST AL,AL.
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
// RawFileClass — a real file in the game directory. ReadBytes (slot 9) is
// matched here.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65CCE0
    virtual int  ReadBytes(void* pBuffer, int nBytes);

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

GG_STATIC_ASSERT(offsetof(RawFileClass, FileSize)    == 0x10);
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)      == 0x14);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)    == 0x18);
GG_STATIC_ASSERT(sizeof(RawFileClass) == 0x24);

// GLOBAL: GAMEMD 0xB04BEC — set by the audio streamer while it owns the file;
// a failed ReadFile under it aborts quietly instead of raising CDCheck.
extern bool IsReadingAudioFile;

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_READ_BYTES_METHODS_H
