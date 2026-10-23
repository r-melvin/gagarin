// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x65CDD0:
//     unknown_0C   [ESI+0x0C] (ADD ECX,EBP @0x65CE98; SUB EAX,[ESI+0xC] @0x65CEDE)
//     unknown_10  [ESI+0x10] (CMP [ESI+0x10],-1 @0x65CE42; stored @0x65CEE1)
//     Handle      [ESI+0x14] (-> WriteFile / SetFilePointer)
//     FileName    [ESI+0x18] (-> CDCheck)
//   vtable slots dispatched: HasHandle +0x18, Open +0x1C (pushed 2 == Write),
//     Close +0x34, CDCheck +0x40 (with 9 == EBADF on a closed handle).
//   Imports: IAT 0x7E11A0 KERNEL32 WriteFile, IAT 0x7E1200 GetLastError
//   (loaded into EBX, called twice), IAT 0x7E11C0 SetFilePointer (loaded
//   into EDI, called twice from the two inlined Raw_Seek(0, SEEK_CUR)).
//   Same class run as match/platform/raw_file_class_read_bytes_methods.h
//   (re-declared here so the TU stands alone); YRpp consulted
//   for the method name only. This is the raw-file layer exactly as
//   ReadBytes was: the seek is done straight on the handle, not via slot 10.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_WRITE_BYTES_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_WRITE_BYTES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned int FileAccessMode;

// FileClass — abstract base, virtuals in exact retail vtable order.
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
    virtual int  WriteBytes(const void* pBuffer, int nBytes);      // slot 12 (+0x30)
    virtual void Close();                                          // slot 13 (+0x34)
    virtual unsigned long GetFileTime();                           // slot 14 (+0x38)
    virtual bool SetFileTime(unsigned long fileTime);              // slot 15 (+0x3C)
    virtual void CDCheck(unsigned long code, bool b, const char* f);// slot 16 (+0x40)

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

// RawFileClass — a real file in the game directory. WriteBytes (slot 12) is
// matched here; the raw seek is expanded inline twice.
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65CDD0
    virtual int  WriteBytes(const void* pBuffer, int nBytes);

    FileAccessMode FileAccess;   // +0x08
    int   unknown_0C;             // +0x0C  (YRpp: FilePointer)
    int   unknown_10;            // +0x10  (YRpp: FileSize)
    void* Handle;                // +0x14
    const char* FileName;        // +0x18
    short unknown_short_1C;      // +0x1C
    short unknown_short_1E;      // +0x1E
    bool  FileNameAllocated;     // +0x20
private:
    char  padding_21[3];         // +0x21

    // RawFileClass::Raw_Seek, inlined at both call sites: EBADF (9) through
    // CDCheck on a closed handle, the Win32 error on a failed SetFilePointer.
    int RawSeek(int offset, int mode);
};

GG_STATIC_ASSERT(offsetof(RawFileClass, unknown_0C)   == 0x0C);
GG_STATIC_ASSERT(offsetof(RawFileClass, unknown_10)  == 0x10);
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)      == 0x14);
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)    == 0x18);
GG_STATIC_ASSERT(sizeof(RawFileClass) == 0x24);

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_WRITE_BYTES_METHODS_H
