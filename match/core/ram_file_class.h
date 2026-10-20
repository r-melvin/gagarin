// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | private-ref-cross-check
//   Layout, vtable slot order and every member offset were read numerically off
//   the user's retail gamemd.exe v1.001 through the local Ghidra CLI. The two
//   RTTI type descriptors reached from the vtables (0x839620 ".?AVRAMFileClass@@"
//   and 0x815DE0 ".?AVFileClass@@") are what name the classes.
//   EA's GPLv3 Red Alert 1 release (CODE/RAMFILE.H, CODE/RAMFILE.CPP,
//   CODE/WWFILE.H) is consulted as a naming and algorithm-shape reference only;
//   no line of it is transcribed and every fact below is re-derived from the
//   binary. The private-reference seed row core/raw_file_class.cpp supplied the initial
//   hint that this address cluster is a file facility; it is not a source of
//   bytes, layout or convention.
//
// RAMFileClass is Westwood's "a buffer pretending to be a file" adapter: it
// implements the abstract FileClass interface over a caller-supplied memory
// block, so code written against the file API can read and write a buffer.
// This is a pure utility file, unchanged in shape from the RA1 generation.
//
// The two vtables:
//   VTABLE: GAMEMD 0x7F0874   RAMFileClass  (17 slots; RTTI at 0x7F0870)
//   VTABLE: GAMEMD 0x7F08BC   FileClass     (17 slots; RTTI at 0x7F08B8)
// FileClass's slots 1-13 and 16 hold the shared pure-virtual stub 0x4C9150;
// only slot 0 (the deleting destructor), slot 14 (Get_Date_Time) and slot 15
// (Set_Date_Time) carry real bodies, which is exactly RA1's FileClass.
//
// Slot order, read off 0x7F0874 word by word:
//   0  0x65C5A0 deleting destructor   9  0x65C3A0 Read
//   1  0x65C550 File_Name            10  0x65C420 Seek
//   2  0x65C560 Set_Name             11  0x65C4A0 Size
//   3  0x65C2E0 Create               12  0x65C4B0 Write
//   4  0x65C300 Delete               13  0x65C540 Close
//   5  0x65C320 Is_Available         14  0x65C570 Get_Date_Time
//   6  0x65C330 Is_Open              15  0x65C580 Set_Date_Time
//   7  0x65C350 Open(rights)         16  0x65C590 Error
//   8  0x65C340 Open(name, rights)
// Slot 7 is the one-argument Open and slot 8 forwards to it through slot 7
// (`CALL dword ptr [EAX+0x1C]`), which is MSVC's reverse ordering of an
// overload set: the two Opens are declared name-first below and land that way.
//
// Return widths are taken off the exit instructions, not off any signature:
// Create/Delete/Open leave a dword (`MOV EAX,1` / `XOR EAX,EAX`), while
// Is_Available, Is_Open and Set_Date_Time leave only AL (`MOV AL,1`,
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
// maxoffset. That is SEEK_SET=0, SEEK_CUR=1, SEEK_END=2.
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

// The two vtables, declared as bare external symbols so the hand-written
// deleting destructor can seat them itself. cl 8804 never expands an explicit
// `p->~T()` call, so the destructor retail has inlined into that thunk cannot
// be reached through the destructor; storing the vptr directly emits the same
// `MOV dword ptr [ESI],<reloc>` and the differ normalises the relocation.
// VTABLE: GAMEMD 0x7F0874   RAMFileClass
// VTABLE: GAMEMD 0x7F08BC   FileClass
extern "C" char GG_VTABLE_RAMFILECLASS_7F0874;
extern "C" char GG_VTABLE_FILECLASS_7F08BC;

// The abstract file interface. RA2 carries one byte of its own at +4 that the
// RA1 declaration does not have: the RAMFileClass constructor stores DL (zero)
// there ahead of every derived member store, which is the base constructor
// inlined, so the byte belongs to the base and is zero-initialised.
class FileClass
{
public:
    // Both are defined in-class: retail has no standalone body for either, so
    // they exist only to be inlined into the derived constructor and destructor.
    FileClass() : unknown_04(0) {}
    ~FileClass() throw() {}

    // Slot 0 of both vtables is the scalar deleting destructor. It is modelled
    // as an ordinary virtual holding the hand-written thunk rather than as a
    // `virtual ~FileClass()`: cl 8804 always calls the destructor out of line
    // from its own `??_G`, where retail has it expanded, and a non-virtual
    // destructor is one cl will expand. The slot is occupied either way, so
    // every `CALL dword ptr [EAX+n]` below keeps retail's index.
    // FUNCTION: GAMEMD 0x65C610
    virtual void* DeletingDtor(unsigned int flags);

    virtual const char* File_Name() const = 0;
    virtual const char* Set_Name(const char* filename) = 0;
    virtual int Create() = 0;
    virtual int Delete() = 0;
    virtual bool Is_Available(int forced) = 0;
    virtual bool Is_Open() const = 0;
    virtual int Open(const char* filename, int rights) = 0;
    virtual int Open(int rights) = 0;
    virtual long Read(void* buffer, long size) = 0;
    virtual long Seek(long pos, int dir) = 0;
    virtual long Size() = 0;
    virtual long Write(const void* buffer, long size) = 0;
    virtual void Close() = 0;
    virtual unsigned long Get_Date_Time();
    virtual bool Set_Date_Time(unsigned long datetime);
    virtual void Error(int error, int canretry, const char* filename) = 0;

    unsigned char unknown_04;   // +0x04  zeroed by the base constructor
};

class RAMFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65C250
    RAMFileClass(void* buffer, int len);
    // FUNCTION: GAMEMD 0x65C2A0
    ~RAMFileClass() throw();

    virtual void* DeletingDtor(unsigned int flags);
    virtual const char* File_Name() const;
    virtual const char* Set_Name(const char* filename);
    virtual int Create();
    virtual int Delete();
    virtual bool Is_Available(int forced);
    virtual bool Is_Open() const;
    virtual int Open(const char* filename, int rights);
    virtual int Open(int rights);
    virtual long Read(void* buffer, long size);
    virtual long Seek(long pos, int dir);
    virtual long Size();
    virtual long Write(const void* buffer, long size);
    virtual void Close();
    virtual unsigned long Get_Date_Time();
    virtual bool Set_Date_Time(unsigned long datetime);
    virtual void Error(int error, int canretry, const char* filename);

    char* Buffer;         // +0x08  the block the "file" lives in
    int   MaxLength;      // +0x0C  capacity of that block
    int   Length;         // +0x10  bytes of it that count as file contents
    int   Offset;         // +0x14  current read/write position
    int   Access;         // +0x18  the mode Open was given
    bool  IsOpen;         // +0x1C
    bool  IsAllocated;    // +0x1D  did the constructor allocate Buffer?
};

// Offsets confirmed numerically: the constructor at 0x65C250 stores the buffer
// pointer to [ESI+8], the length to [ESI+0xC] and [ESI+0x10], zero to
// [ESI+0x14], one to [ESI+0x18] and zero bytes to [ESI+0x1C] and [ESI+0x1D];
// Is_Open is `MOV AL,byte ptr [ECX+0x1C]`; Size is `MOV EAX,[ECX+0x10]`; Seek
// reads MaxLength from [ESI+0xC]; the destructor tests [ESI+0x1D].
GG_STATIC_ASSERT(offsetof(FileClass, unknown_04) == 0x04 &&
                 sizeof(FileClass) == 0x08);
GG_STATIC_ASSERT(offsetof(RAMFileClass, Buffer) == 0x08 &&
                 offsetof(RAMFileClass, MaxLength) == 0x0C &&
                 offsetof(RAMFileClass, Length) == 0x10 &&
                 offsetof(RAMFileClass, Offset) == 0x14 &&
                 offsetof(RAMFileClass, Access) == 0x18 &&
                 offsetof(RAMFileClass, IsOpen) == 0x1C &&
                 offsetof(RAMFileClass, IsAllocated) == 0x1D &&
                 sizeof(RAMFileClass) == 0x20);

#endif  // GG_MATCH_CORE_RAM_FILE_CLASS_H
