// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x431E80:
//     BufferIOFileClass::unknown_bool_27 [EDI+0x27] (MOV byte [EDI+0x27],0 @0x431EEB)
//     BufferIOFileClass::unknown_bool_29 [EDI+0x29] (MOV AL,[EDI+0x29] @0x431E91)
//   vtable slot dispatched: GetFileName +0x04 (CALL [EAX+0x4] @0x431E86,
//     0x431E9E, 0x431EDC, 0x431EFB).
//   Direct (class-qualified) CALLs -> normalised relocs:
//     BufferIOFileClass::Commit      0x431DD0 (CALL @0x431EE6)
//     RawFileClass::SetFileName      0x65CAC0 (CALL @0x431EF2)
//   The member run mirrors the already-confirmed layout in
//   match/platform/ccfile_class.h (not edited; re-declared here so the TU
//   stands alone); YRpp consulted for names only.
#ifndef GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_NAME_METHODS_H
#define GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_NAME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar (only its width matters for the slot signatures here).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// GetFileName lands at slot +0x04 and SetFileName at +0x08.
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
    virtual int Open(FileAccessMode access);                      // slot 7  (+0x1C)
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
// RawFileClass — a real file in the game directory. Its SetFileName is the
// base implementation BufferIOFileClass::SetFileName forwards to (direct CALL).
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65CAC0 (decl; reloc)
    virtual const char* SetFileName(const char* pFileName);
    // FUNCTION: GAMEMD 0x65CF00 (decl; reloc) — RawFileClass::Seek.
    virtual int  Seek(int offset, int mode);

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

// ---------------------------------------------------------------------------
// BufferIOFileClass — a file with an in-memory read buffer. SetFileName
// (slot 2) is matched here.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    // FUNCTION: GAMEMD 0x431E80
    virtual const char* SetFileName(const char* pFileName);
    // FUNCTION: GAMEMD 0x4324B0 — BufferIOFileClass::Seek.
    virtual int  Seek(int offset, int mode);

    // FUNCTION: GAMEMD 0x431DD0 (decl; reloc) — flush the write-back buffer.
    int Commit();

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

GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)              == 0x18);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_27)  == 0x27);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_29)  == 0x29);
GG_STATIC_ASSERT(sizeof(BufferIOFileClass) == 0x54);

#endif  // GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_NAME_METHODS_H
