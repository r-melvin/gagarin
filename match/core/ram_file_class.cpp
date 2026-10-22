// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI. The private-reference
//   seed row core/raw_file_class.cpp named the cluster and nothing else.
//
// RAMFileClass — the FileClass interface implemented over a memory block.
// Bodies are ordered ascending by retail address.

#include "ram_file_class.h"

// Constructs the pseudo-file over `buffer`. The member initialisers land in
// declaration order and the vtable seat sinks below them, which is retail's
// order. When no buffer is supplied but a length is, the object allocates its
// own block and remembers that it owns it. The constructor's leading
// `CMP ECX,EDX` sets the flags that the later `JNZ` consumes, so the null test
// and the length test are one short-circuit condition.
// FUNCTION: GAMEMD 0x65C250
RAMFileClass::RAMFileClass(void* buffer, int len) :
    Buffer((char*)buffer),
    MaxLength(len),
    Length(len),
    Offset(0),
    Access(GG_FILE_READ),
    Opened(false),
    IsAllocated(false)
{
    if (buffer == 0 && len > 0) {
        Buffer = (char*)FUN_007C8E17(len);
        IsAllocated = true;
    }
}

// Closes the pseudo-file and releases the block if this object allocated it.
// The close is spelled as the flag store rather than as a Close() call: cl 8804
// devirtualises the call inside the destructor but will not inline a body it
// has not yet seen, and Close is defined further down the file in retail's
// address order, so the call survives. Retail has only the store.
// FUNCTION: GAMEMD 0x65C2A0
RAMFileClass::~RAMFileClass() throw()
{
    Opened = false;
    if (IsAllocated) {
        FUN_007C8B3D(Buffer);
        Buffer = 0;
        IsAllocated = false;
    }
}

// "Creating" a RAM file just declares its contents empty, which is only
// allowed while the file is closed.
// FUNCTION: GAMEMD 0x65C2E0
int RAMFileClass::CreateFile()
{
    if (!HasHandle()) {
        Length = 0;
        return true;
    }
    return false;
}

// Deleting is the same operation as creating for a buffer-backed file: the
// contents are forgotten. Retail emits the identical body.
// FUNCTION: GAMEMD 0x65C300
int RAMFileClass::DeleteFile()
{
    if (!HasHandle()) {
        Length = 0;
        return true;
    }
    return false;
}

// A RAM file is always present. The exit is `MOV AL,1`, so the result is one
// byte wide.
// FUNCTION: GAMEMD 0x65C320
bool RAMFileClass::Exists(int)
{
    return true;
}

// FUNCTION: GAMEMD 0x65C330
bool RAMFileClass::HasHandle() const
{
    return Opened;
}

// The file has no name, so the name is ignored and this forwards to the
// one-argument Open through the vtable.
// FUNCTION: GAMEMD 0x65C340
int RAMFileClass::OpenEx(const char*, int rights)
{
    return Open(rights);
}

// Opens the block for reading or writing. Opening for write discards whatever
// the block was holding. The result is the freshly set open flag read back
// through the vtable, which is where retail's `AND EAX,0xFF` comes from.
// FUNCTION: GAMEMD 0x65C350
int RAMFileClass::Open(int rights)
{
    if (Buffer == 0 || HasHandle()) {
        return false;
    }

    Offset = 0;
    Access = rights;
    Opened = true;

    switch (rights) {
        default:
        case GG_FILE_READ:
            break;

        case GG_FILE_WRITE:
            Length = 0;
            break;

        case GG_FILE_READ | GG_FILE_WRITE:
            break;
    }

    return HasHandle();
}

// Copies out of the block, clamped to whatever contents remain. A closed file
// is opened for the duration of the call and closed again afterwards, which is
// what the EBX flag carries; an open file must have been opened for reading.
// FUNCTION: GAMEMD 0x65C3A0
long RAMFileClass::ReadBytes(void* buffer, long size)
{
    if (Buffer == 0 || buffer == 0 || size == 0) {
        return 0;
    }

    bool openedHere = false;
    if (!HasHandle()) {
        Open(GG_FILE_READ);
        openedHere = true;
    } else {
        if ((Access & GG_FILE_READ) == 0) {
            return 0;
        }
    }

    int count = (size < (Length - Offset)) ? size : (Length - Offset);
    FUN_007CA090(buffer, &Buffer[Offset], count);
    Offset += count;

    if (openedHere) {
        Close();
    }

    return count;
}

// Moves the read/write position. The ceiling is the written length when
// reading and the whole block when writing, which is the `TEST AL,2` on the
// access mode; the position is then clamped into range and may extend the
// recorded length.
// FUNCTION: GAMEMD 0x65C420
long RAMFileClass::Seek(long pos, int dir)
{
    if (Buffer == 0 || !HasHandle()) {
        return Offset;
    }

    int limit = Length;
    if ((Access & GG_FILE_WRITE) != 0) {
        limit = MaxLength;
    }

    switch (dir) {
        case GG_SEEK_CUR:
            Offset += pos;
            break;

        case GG_SEEK_SET:
            Offset = 0 + pos;
            break;

        case GG_SEEK_END:
            Offset = limit + pos;
            break;
    }

    if (Offset < 0) Offset = 0;
    if (Offset > limit) Offset = limit;

    if (Offset > Length) {
        Length = Offset;
    }

    return Offset;
}

// FUNCTION: GAMEMD 0x65C4A0
long RAMFileClass::GetFileSize()
{
    return Length;
}

// Copies into the block, clamped to the space left. Mirrors Read: a closed
// file is opened for write and closed again, an open one must carry the write
// bit, and a write past the recorded length extends it.
// FUNCTION: GAMEMD 0x65C4B0
long RAMFileClass::WriteBytes(const void* buffer, long size)
{
    if (Buffer == 0 || buffer == 0 || size == 0) {
        return 0;
    }

    bool openedHere = false;
    if (!HasHandle()) {
        Open(GG_FILE_WRITE);
        openedHere = true;
    } else {
        if ((Access & GG_FILE_WRITE) == 0) {
            return 0;
        }
    }

    int room = MaxLength - Offset;
    int count = (size < room) ? size : room;
    FUN_007CA090(&Buffer[Offset], buffer, count);
    Offset += count;

    if (Offset > Length) {
        Length = Offset;
    }

    if (openedHere) {
        Close();
    }

    return count;
}

// Closing a RAM file only records that it is closed.
// FUNCTION: GAMEMD 0x65C540
void RAMFileClass::Close()
{
    Opened = false;
}

// The block has no filename, so a fixed placeholder is reported.
// STRING: GAMEMD 0x83963C
// FUNCTION: GAMEMD 0x65C550
const char* RAMFileClass::GetFileName() const
{
    return "UNKNOWN";
}

// Renaming is meaningless here; the current (fixed) name is returned through
// the vtable, which is retail's `MOV EAX,[ECX]; CALL dword ptr [EAX+4]`.
// FUNCTION: GAMEMD 0x65C560
const char* RAMFileClass::SetFileName(const char*)
{
    return GetFileName();
}

// A memory block has no timestamp.
// FUNCTION: GAMEMD 0x65C570
unsigned long RAMFileClass::GetFileTime()
{
    return 0;
}

// Setting the timestamp trivially succeeds. `MOV AL,1` on the exit is what
// makes this one byte wide where the base returns the same width.
// FUNCTION: GAMEMD 0x65C580
bool RAMFileClass::SetFileTime(unsigned long)
{
    return true;
}

// There is no error condition a RAM file can report. Three arguments of stack
// are still taken, which is retail's bare `RET 0xC`.
// FUNCTION: GAMEMD 0x65C590
void RAMFileClass::CDCheck(int, int, const char*)
{
}

// The scalar deleting destructor for RAMFileClass, hand-written because retail
// has the whole destructor expanded into the thunk: both vtable seats, the
// owned-block release and the conditional free of the object itself are one
// body. The two seats are written as direct vptr stores because cl 8804 never
// expands an explicit destructor call; the destructor's own out-of-line body at
// 0x65C2A0 above is the same code.
// FUNCTION: GAMEMD 0x65C5A0
void* RAMFileClass::DeletingDtor(unsigned int flags)
{
    *(void**)this = (void*)&GG_VTABLE_RAMFILECLASS_7F0874;

    Opened = false;
    if (IsAllocated) {
        FUN_007C8B3D(Buffer);
        Buffer = 0;
        IsAllocated = false;
    }

    *(void**)this = (void*)&GG_VTABLE_FILECLASS_7F08BC;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// The base's default timestamp getter: no date is known.
// FUNCTION: GAMEMD 0x65C5F0
unsigned long FileClass::GetFileTime()
{
    return 0;
}

// The base's default timestamp setter fails. `XOR AL,AL` is the byte-wide
// false that separates it from the derived override's `MOV AL,1`.
// FUNCTION: GAMEMD 0x65C600
bool FileClass::SetFileTime(unsigned long)
{
    return false;
}

// The scalar deleting destructor for the abstract base: seat the base vtable,
// then free the object if asked.
// FUNCTION: GAMEMD 0x65C610
void* FileClass::DeletingDtor(unsigned int flags)
{
    this->FileClass::~FileClass();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
