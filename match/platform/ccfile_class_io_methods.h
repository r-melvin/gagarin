// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp (consult-only, no
//   LICENSE; every offset reconfirmed numerically against the disasm below).
//
// Translation unit for the CCFileClass buffered-IO primitives:
//   0x473AE0 WriteBytes, 0x473BA0 Seek, 0x473C00 GetFileSize.
//
// The FileClass hierarchy (the MIX/CD/raw file stack):
//   FileClass (abstract COM-ish base) -> RawFileClass -> BufferIOFileClass
//   -> CDFileClass -> CCFileClass.
//
// Confirmed offsets (reconfirmed from the matched bodies):
//   CCFileClass::Buffer (MemoryBuffer.Buffer) [ECX+0x58]  (all three methods)
//   CCFileClass::Buffer.Size                  [ECX+0x5C]  (Seek/GetFileSize)
//   CCFileClass::Position                     [ECX+0x64]  (Seek)
// vtable slots dispatched through (FileClass declaration order):
//   GetFileName @ +0x04 (slot 1)  -- CALL [EDI+0x4] in WriteBytes/GetFileSize
//   CDCheck     @ +0x40 (slot 16) -- CALL [EDI+0x40] in WriteBytes
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_IO_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_IO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled here as a 4-byte
// scalar (the matched code only uses its 32-bit width when forwarding).
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// GetFileName lands at slot +0x04 and CDCheck at slot +0x40. Only the slots the
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
// RawFileClass — a real file in the game directory.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
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
// Exists/Seek/GetFileSize/WriteBytes (the retail base implementations the
// matched bodies tail- or fall-through-call) are declared bodiless; cl emits a
// direct CALL that the differ normalises as a reloc.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    virtual bool Exists(bool writeShared);                        // GAMEMD 0x431F10 (decl; reloc)
    virtual int  Seek(int offset, int mode);                      // GAMEMD 0x4324B0 (decl; reloc)
    virtual int  GetFileSize();                                   // GAMEMD 0x4325A0 (decl; reloc)
    virtual int  WriteBytes(void* pBuffer, int nBytes);          // GAMEMD 0x432050 (decl; reloc)

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
// CDFileClass — a file fetched from a CD search path.
// ---------------------------------------------------------------------------
class CDFileClass : public BufferIOFileClass
{
public:
    bool IsDisabled;        // +0x54
private:
    char padding_55[3];     // +0x55
};

// ---------------------------------------------------------------------------
// CCFileClass — a file inside a MIX archive (the in-memory buffered case).
// ---------------------------------------------------------------------------
class CCFileClass : public CDFileClass
{
public:
    virtual int Seek(int offset, int mode);                       // GAMEMD 0x473BA0 (matched)
    virtual int GetFileSize();                                    // GAMEMD 0x473C00 (matched)
    virtual int WriteBytes(void* pBuffer, int nBytes);            // GAMEMD 0x473AE0 (matched)

    MemoryBuffer Buffer;      // +0x58
    int          Position;    // +0x64 (signed: Seek clamps via signed compares)
    unsigned int Availability;// +0x68
};

// MixFileClass::Offset @ 0x5B4430 (static __fastcall in YRpp; declared bodiless
// here so cl emits a direct CALL the differ normalises as a reloc). The matched
// disasm passes ECX=name, EDX=0 and stack args 0,0,&length.
bool __fastcall MixFileClass_Offset(const char* name, void* data, void* mixfile,
                                    int offset, int* length);

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(CCFileClass, Buffer)   == 0x58);
GG_STATIC_ASSERT(offsetof(CCFileClass, Position) == 0x64);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_IO_METHODS_H
