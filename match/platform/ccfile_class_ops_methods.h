// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp (consult-only, no LICENSE; every
//   offset reconfirmed numerically against the disasm below).
//
// Translation unit for two FileClass-hierarchy file operations:
//   0x47AF10 CDFileClass::OpenEx     (slot 8 of the CDFileClass vtable @0x7E1668)
//   0x65D190 RawFileClass::DeleteFile(slot 4 of the same vtable)
//
// The FileClass hierarchy (the MIX/CD/raw file stack):
//   FileClass (abstract COM-ish base) -> RawFileClass -> BufferIOFileClass
//   -> CDFileClass -> CCFileClass.
//
// Confirmed offsets (reconfirmed from the matched bodies):
//   RawFileClass::FileName  [ESI+0x18]  (OpenEx null-guard, DeleteFile)
//   CDFileClass::IsDisabled [ESI+0x54]  (OpenEx)
// vtable slots dispatched through (FileClass declaration order):
//   SetFileName @ +0x08 (slot 2)  -- CALL [EDX+0x8]  in OpenEx
//   DeleteFile  @ +0x10 (slot 4)  -- this vtable slot holds 0x65D190
//   Exists      @ +0x14 (slot 5)  -- CALL [EAX+0x14] in DeleteFile
//   Close       @ +0x34 (slot 13) -- CALL [EAX+0x34] in DeleteFile
//   CDCheck     @ +0x40 (slot 16) -- CALL [EAX+0x40] / CALL [EDI+0x40]
// Direct (class-qualified) base CALLs in OpenEx -> normalised relocs:
//   BufferIOFileClass::Close       0x4325C0
//   BufferIOFileClass::SetFileName 0x431E80
//   BufferIOFileClass::Open        0x431F70
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_OPS_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_OPS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled here as a 4-byte
// scalar (the matched code only uses its 32-bit width when comparing/forwarding).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// SetFileName lands at slot +0x08 and CDCheck at slot +0x40. Only the slots the
// matched code dispatches through are load-bearing; the rest pin their indices.
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
// RawFileClass — a real file in the game directory. DeleteFile (slot 4) is
// defined in this TU; it tail-uses FileName @ +0x18.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    virtual int DeleteFile();    // GAMEMD 0x65D190 (matched here; slot 4 override)

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
// BufferIOFileClass — a file with an in-memory read buffer. The class-qualified
// Close/Open/SetFileName (the retail base implementations CDFileClass::OpenEx
// invokes via direct CALL) are declared bodiless; cl emits a direct CALL that
// the differ normalises as a reloc.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    virtual const char* SetFileName(const char* pFileName);       // GAMEMD 0x431E80 (decl; reloc)
    virtual bool Open(FileAccessMode access);                     // GAMEMD 0x431F70 (decl; reloc)
    virtual void Close();                                         // GAMEMD 0x4325C0 (decl; reloc)

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

// ---------------------------------------------------------------------------
// CDFileClass — a file fetched from a CD search path. OpenEx (slot 8) is defined
// in this TU; it reads IsDisabled @ +0x54.
// ---------------------------------------------------------------------------
class CDFileClass : public BufferIOFileClass
{
public:
    virtual bool OpenEx(const char* pFileName, FileAccessMode a); // GAMEMD 0x47AF10 (matched here)

    bool IsDisabled;        // +0x54
private:
    char padding_55[3];     // +0x55
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)  == 0x18);
GG_STATIC_ASSERT(offsetof(CDFileClass, IsDisabled) == 0x54);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_OPS_METHODS_H
