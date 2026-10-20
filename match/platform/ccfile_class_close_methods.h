// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp CCFileClass.h (consult-only, no LICENSE; every
//   offset reconfirmed numerically against the disassembly below).
//
// Translation unit: the two FileClass-hierarchy "close/time" primitives:
//   BufferIOFileClass::Close   (GAMEMD 0x4325C0)
//   RawFileClass::GetFileTime  (GAMEMD 0x65D1F0)
//
// This header re-states the FileClass hierarchy locally (rather than reusing
// match/platform/ccfile_class.h) because both methods are virtual *overrides*
// not declared in that header (RawFileClass::GetFileTime, BufferIOFileClass's
// private commit helper), and a C++ class cannot be reopened to add members.
// The layout/vtable ordering is identical and self-guarded by GG_STATIC_ASSERT.
//
// Confirmed offsets (from the matched bodies):
//   RawFileClass::Handle               [ECX+0x14]  (0x65D1F0 GetFileTime)
//   BufferIOFileClass::flag_25         [ESI+0x25]  (0x4325C0 Close)
//   BufferIOFileClass::flag_26         [ESI+0x26]  (0x4325C0 Close)
//   BufferIOFileClass::flag_29         [ESI+0x29]  (0x4325C0 Close)
//   BufferIOFileClass::unknown_50      [ESI+0x50]  (0x4325C0 Close)
// vtable slots (FileClass declaration order): Close @ +0x34 (slot 13) — the
//   inlined self-dispatch CALL [EAX+0x34] in BufferIOFileClass::Close.
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar (the matched code only relies on its 32-bit width).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// Close lands at slot +0x34 and GetFileTime at slot +0x38. Slots that the
// matched code does not dispatch through only pin their indices.
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
    virtual int  ReadBytes(void* pBuffer, int nBytes);            // slot 9  (+0x24)
    virtual int  Seek(int offset, int mode);                       // slot 10 (+0x28)
    virtual int  GetFileSize();                                    // slot 11 (+0x2C)
    virtual int  WriteBytes(void* pBuffer, int nBytes);           // slot 12 (+0x30)
    virtual void Close();                                          // slot 13 (+0x34)
    virtual unsigned long GetFileTime();                           // slot 14 (+0x38)
    virtual bool SetFileTime(unsigned long fileTime);             // slot 15 (+0x3C)
    virtual void CDCheck(unsigned long code, bool b, const char* f);// slot 16 (+0x40)

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
    virtual void Close();                       // GAMEMD 0x65CCA0 (decl; base call)
    virtual unsigned long GetFileTime();        // GAMEMD 0x65D1F0 (matched here)

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
// BufferIOFileClass — a file with an in-memory read buffer.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    virtual void Close();                       // GAMEMD 0x4325C0 (matched here)

    // Private commit/flush helper (GAMEMD 0x431DD0). Declared only; the matched
    // Close body dispatches to it via a direct CALL (relocation-normalised).
    bool Commit();

    bool flag_24;   // +0x24
    bool flag_25;   // +0x25
    bool flag_26;   // +0x26
    bool flag_27;   // +0x27
    bool flag_28;   // +0x28
    bool flag_29;   // +0x29
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

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)            == 0x14);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, flag_25)      == 0x25);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, flag_26)      == 0x26);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, flag_29)      == 0x29);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_50)   == 0x50);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_CLOSE_METHODS_H
