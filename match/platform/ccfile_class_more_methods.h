// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp (consult-only, no
//   LICENSE; every offset reconfirmed numerically against the disasm below).
//
// Translation unit for two more FileClass-hierarchy primitives:
//   0x4A3890 FileClass::ReadWholeFile  (non-virtual helper)
//   0x65D150 RawFileClass::CreateFile  (virtual slot 3)
//
// The FileClass hierarchy (the MIX/CD/raw file stack):
//   FileClass (abstract COM-ish base) -> RawFileClass -> ...
//
// Confirmed offsets (from the matched bodies):
//   RawFileClass::FileSize  [ESI+0x10]   (0x65D150 CreateFile: CMP [ESI+0x10],-1)
// vtable slots dispatched through (FileClass declaration order):
//   Exists      @ +0x14 (slot 5)  -- CALL [EAX+0x14] in ReadWholeFile
//   Open        @ +0x1C (slot 7)  -- CALL [EDX+0x1C] in CreateFile
//   ReadBytes   @ +0x24 (slot 9)  -- CALL [EAX+0x24] in ReadWholeFile
//   Seek        @ +0x28 (slot 10) -- CALL [EAX+0x28] in CreateFile
//   GetFileSize @ +0x2C (slot 11) -- CALL [EDX+0x2C] in ReadWholeFile
//   Close       @ +0x34 (slot 13) -- CALL [EAX+0x34] in CreateFile
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_MORE_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled here as a 4-byte
// scalar (the matched code only uses its 32-bit width when forwarding).
typedef unsigned int FileAccessMode;

// The YR global allocator (operator new == YRMemory::Allocate @ 0x7C8E17). Used
// by ReadWholeFile; declared bodiless so cl emits a direct CALL (reloc-normalised
// by the differ). __cdecl, single size argument, returns the new block.
void* __cdecl GameAllocate(size_t size);

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// the dispatched slots land at their confirmed offsets. ReadWholeFile is the
// non-virtual helper defined here. Open is modelled INT-returning because the
// CreateFile caller tests the full EAX (TEST EAX,EAX), not AL.
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

    void* ReadWholeFile();   // GAMEMD 0x4A3890 (matched here)

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

// ---------------------------------------------------------------------------
// RawFileClass — a real file in the game directory. CreateFile (slot 3 override)
// is matched here; it reads FileSize @ +0x10.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    virtual int CreateFile();    // GAMEMD 0x65D150 (matched here)

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

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, FileSize) == 0x10);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_MORE_METHODS_H
