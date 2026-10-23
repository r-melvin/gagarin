// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Layout, vtable slot order and every member offset were read numerically off
//   the user's retail gamemd.exe v1.001 through the local Ghidra CLI. The two
//   RTTI type descriptors reached from the vtables (0x839620 ".?AVRAMFileClass@@"
//   and 0x815DE0 ".?AVFileClass@@") are what name the classes. Virtual method
//   names follow the YRpp FileClass slot names, checked slot by slot against
//   the vtable below and against each body's behaviour.
//
// RAMFileClass implements the abstract FileClass interface over a memory
// block: the constructor takes a buffer and a length, and every slot reads,
// writes or seeks within that block.
//
// The two vtables:
//   VTABLE: GAMEMD 0x7F0874   RAMFileClass  (17 slots; RTTI at 0x7F0870)
//   VTABLE: GAMEMD 0x7F08BC   FileClass     (17 slots; RTTI at 0x7F08B8)
// FileClass's slots 1-13 and 16 hold the shared pure-virtual stub 0x4C9150;
// only slot 0 (the deleting destructor), slot 14 (GetFileTime) and slot 15
// (SetFileTime) carry real bodies.
//
// Slot order, read off 0x7F0874 word by word:
//   0  0x65C5A0 deleting destructor   9  0x65C3A0 Read
//   1  0x65C550 GetFileName            10  0x65C420 Seek
//   2  0x65C560 SetFileName             11  0x65C4A0 Size
//   3  0x65C2E0 Create               12  0x65C4B0 Write
//   4  0x65C300 Delete               13  0x65C540 Close
//   5  0x65C320 Exists         14  0x65C570 GetFileTime
//   6  0x65C330 HasHandle              15  0x65C580 SetFileTime
//   7  0x65C350 Open(rights)         16  0x65C590 Error
//   8  0x65C340 Open(name, rights)
// Slots7/8 are Open/OpenEx;65C340 calls slot7 at+1C.
//
// Return widths are taken off the exit instructions, not off any signature:
// Create/Delete/Open leave a dword (`MOV EAX,1` / `XOR EAX,EAX`), while
// Exists, HasHandle and SetFileTime leave only AL (`MOV AL,1`,
// `MOV AL,byte ptr [ECX+0x1C]`, `XOR AL,AL`), so those three are bool.
#ifndef GG_MATCH_CORE_RAM_FILE_CLASS_H
#define GG_MATCH_CORE_RAM_FILE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Access mode bits, read off the code: Open stores its argument at +0x18 and
// clears Length only when it equals 2; Seek tests bit 1 of +0x18 to pick
// MaxLength over Length; Read tests bit 0.
#define GG_FILE_READ  1
#define GG_FILE_WRITE 2

// Seek origins, read off the switch at 0x65C442: the `SUB EAX,0` arm assigns
// pos outright, the first `DEC EAX` arm adds to Offset, the second bases on
// limit. That is SEEK_SET=0, SEEK_CUR=1, SEEK_END=2.
#define GG_SEEK_SET 0
#define GG_SEEK_CUR 1
#define GG_SEEK_END 2

// Game heap primitives. Declared, never defined: cl emits a relocated CALL and
// the differ normalises the target.
// LIBRARY: GAMEMD 0x7C8E17  operator new / malloc  (push size; call; add esp,4)
// LIBRARY: GAMEMD 0x7C8B3D  operator delete / free (push ptr;  call; add esp,4)
// LIBRARY: GAMEMD 0x7CA090  memmove                (3 args, cdecl)
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
extern "C" void  __cdecl FUN_007C8B3D(void* block);
extern "C" void* __cdecl FUN_007CA090(void* dest, const void* src, unsigned int count);

#include "../platform/ccfile_class.h"

class RAMFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65C250
    RAMFileClass(void* buffer, int len);
    // FUNCTION: GAMEMD 0x65C2A0
    ~RAMFileClass() throw();

    virtual const char* GetFileName() const;
    virtual const char* SetFileName(const char* filename);
    virtual int CreateFile();
    virtual int DeleteFile();
    virtual bool Exists(bool forced);
    virtual bool HasHandle();
    virtual int Open(FileAccessMode rights);
    virtual int OpenEx(const char* filename, FileAccessMode rights);
    virtual int ReadBytes(void* buffer, int size);
    virtual int Seek(int pos, int dir);
    virtual int GetFileSize();
    virtual int WriteBytes(void* buffer, int size);
    virtual void Close();
    virtual unsigned long GetFileTime();
    virtual bool SetFileTime(unsigned long datetime);
    virtual void CDCheck(unsigned long error, bool retry, const char* filename);

    char* Buffer;         // +0x08  the block the "file" lives in
    int   MaxLength;      // +0x0C  capacity of that block
    int   Length;         // +0x10  bytes of it that count as file contents
    int   Offset;         // +0x14  current read/write position
    int   Access;         // +0x18  the mode Open was given
    bool  Opened;         // +0x1C
    bool  IsAllocated;    // +0x1D  did the constructor allocate Buffer?
};

// Offsets confirmed numerically: the constructor at 0x65C250 stores the buffer
// pointer to [ESI+8], the length to [ESI+0xC] and [ESI+0x10], zero to
// [ESI+0x14], one to [ESI+0x18] and zero bytes to [ESI+0x1C] and [ESI+0x1D];
// HasHandle is `MOV AL,byte ptr [ECX+0x1C]`; Size is `MOV EAX,[ECX+0x10]`; Seek
// reads MaxLength from [ESI+0xC]; the destructor tests [ESI+0x1D].
GG_STATIC_ASSERT(offsetof(FileClass, SkipCDCheck) == 0x04 &&
                 sizeof(FileClass) == 0x08);
GG_STATIC_ASSERT(offsetof(RAMFileClass, Buffer) == 0x08 &&
                 offsetof(RAMFileClass, MaxLength) == 0x0C &&
                 offsetof(RAMFileClass, Length) == 0x10 &&
                 offsetof(RAMFileClass, Offset) == 0x14 &&
                 offsetof(RAMFileClass, Access) == 0x18 &&
                 offsetof(RAMFileClass, Opened) == 0x1C &&
                 offsetof(RAMFileClass, IsAllocated) == 0x1D &&
                 sizeof(RAMFileClass) == 0x20);

#endif  // GG_MATCH_CORE_RAM_FILE_CLASS_H
