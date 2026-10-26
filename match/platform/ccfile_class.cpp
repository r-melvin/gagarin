// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// Translation unit: the FileClass-hierarchy file primitives (GetFileName,
// Exists, OpenEx, GetFileSize, the CCFileClass constructor, Close). Functions are ordered ascending by
// retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x401940   RawFileClass::GetFileName       (__thiscall)
//   FUNCTION: GAMEMD 0x401950   CDFileClass scalar deleting destructor
//   FUNCTION: GAMEMD 0x401980   CCFileClass::OpenEx             (__thiscall)
//   FUNCTION: GAMEMD 0x4019A0   CCFileClass scalar deleting destructor
//   FUNCTION: GAMEMD 0x431F10   BufferIOFileClass::Exists       (__thiscall)
//   FUNCTION: GAMEMD 0x431F50   BufferIOFileClass::OpenEx       (__thiscall)
//   FUNCTION: GAMEMD 0x4325A0   BufferIOFileClass::GetFileSize  (__thiscall)
//   FUNCTION: GAMEMD 0x4739F0   CCFileClass::CCFileClass        (__thiscall)
//   FUNCTION: GAMEMD 0x473CE0   CCFileClass::Close              (__thiscall)
//   FUNCTION: GAMEMD 0x65CBF0   RawFileClass::Exists       (callee; reloc)
//   FUNCTION: GAMEMD 0x65D0D0   RawFileClass::GetFileSize  (callee; reloc)
//   FUNCTION: GAMEMD 0x431F70   BufferIOFileClass::Open    (callee; reloc)
//   FUNCTION: GAMEMD 0x4325C0   BufferIOFileClass::Close   (callee; reloc)
//   FUNCTION: GAMEMD 0x43AD00   MemoryBuffer::MemoryBuffer (callee; reloc)

#include "ccfile_class.h"
#include "../core/string_class.h"
#include <string.h>

#pragma function(memcpy)

// Standard placement new: returns the placement pointer unchanged. Used by
// CCFileClass::Close to re-construct its MemoryBuffer in place (which is how
// retail emits LEA &Buffer / TEST / JZ / CALL ctor at 0x473CE0).
inline void* operator new(size_t, void* p) throw() { return p; }

// FUNCTION: GAMEMD 0x401940  (__thiscall)
// Return the stored file-name pointer (RawFileClass::FileName @ +0x18).
const char* RawFileClass::GetFileName() const
{
    return this->FileName;
}

// FUNCTION: GAMEMD 0x401950
// CDFileClass's scalar deleting destructor, slot 0 of vtable 0x7E1668,
// generated from the inline ~CDFileClass; emitted here with the vtable.

// FUNCTION: GAMEMD 0x401980  (__thiscall)
// CCFileClass::OpenEx — set the name then open. Both dispatched virtually:
//   this->SetFileName(name)   -> CALL [vtable+0x08]
//   return this->Open(access) -> CALL [vtable+0x1C]
int CCFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->SetFileName(pFileName);
    return this->Open(access);
}

// FUNCTION: GAMEMD 0x4019A0
// CCFileClass's scalar deleting destructor, slot 0 of vtable 0x7E16B0. The
// compiler generates it from the inline ~CCFileClass; this object emits it
// with the vtable, which the constructor below references.

// FUNCTION: GAMEMD 0x431F10  (__thiscall)
// BufferIOFileClass::Exists — already-open shortcut, else defer to the raw file.
bool BufferIOFileClass::Exists(bool writeShared)
{
    if (this->unknown_bool_29)
        return true;
    return this->RawFileClass::Exists(false);
}

// FUNCTION: GAMEMD 0x431F50  (__thiscall)
// BufferIOFileClass::OpenEx — set the name virtually, then open via the
// class-qualified (non-virtual, direct CALL) BufferIOFileClass::Open.
int BufferIOFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->SetFileName(pFileName);
    return this->BufferIOFileClass::Open(access);
}

// FUNCTION: GAMEMD 0x4325A0  (__thiscall)
// BufferIOFileClass::GetFileSize — buffered size when buffered & open, else the
// raw file size (tail call).
int BufferIOFileClass::GetFileSize()
{
    if (this->unknown_bool_25 && this->unknown_bool_29)
        return this->unknown_int_48;
    return this->RawFileClass::GetFileSize();
}

// FUNCTION: GAMEMD 0x4739F0  (__thiscall)
// Construct the CD-file base and an empty buffer, then name the file through
// CDFileClass's SetFileName (a direct call to 0x47AE10, not the slot).
CCFileClass::CCFileClass(const char* pFileName) :
    Buffer(0, 0),
    Position(0)
{
    Availability = 0;
    CDFileClass::SetFileName(pFileName);
}

// FUNCTION: GAMEMD 0x473A30
CCFileClass::CCFileClass(const Wstring& name) : Buffer(0, 0), Position(0)
{
    Availability = 0;
    const char* filename = name.FUN_007B5440();
    Availability = 0;
    CDFileClass::SetFileName(filename);
}

// FUNCTION: GAMEMD 0x473A80
CCFileClass::CCFileClass() : Buffer(0, 0), Position(0)
{
    Availability = 0;
}

// FUNCTION: GAMEMD 0x473AE0  (__thiscall)
// CCFileClass::WriteBytes — when the file is buffered in memory, fire the
// CD-protection check (error 0xD) against the file name, then forward the write
// to the underlying buffered file.
int CCFileClass::WriteBytes(void* pBuffer, int nNumBytes)
{
    if (this->Buffer.Buffer) {
        this->CDCheck(0xD, false, this->GetFileName());
    }
    return this->BufferIOFileClass::WriteBytes(pBuffer, nNumBytes);
}


// FUNCTION: GAMEMD 0x473B10
//
// Read from a MIX-resident file. If the file is not open it is opened for
// reading here and closed again on the way out. With an in-memory buffer the
// read is a bounded memcpy from the current position; without one it is handed
// to the BufferIOFileClass base.
int CCFileClass::ReadBytes(void* pBuffer, int nBytes)
{
    bool opened = false;

    if (!this->HasHandle()) {
        if (this->Open(1)) {
            opened = true;
        }
    }

    if (this->Buffer.Buffer != 0) {
        int available = this->Buffer.Size - this->Position;
        if (available < nBytes) {
            nBytes = available;
        }
        if (nBytes != 0) {
            memcpy(pBuffer, (char*)this->Buffer.Buffer + this->Position, nBytes);
            this->Position = this->Position + nBytes;
        }
        if (opened) {
            this->Close();
        }
        return nBytes;
    }

    nBytes = BufferIOFileClass::ReadBytes(pBuffer, nBytes);
    if (opened) {
        this->Close();
    }
    return nBytes;
}

// FUNCTION: GAMEMD 0x473BA0  (__thiscall)
// CCFileClass::Seek — seek within the in-memory buffer (clamped to [0, Size]);
// otherwise defer to the buffered file.
//
// PARTIAL, 90.6% (29/32). Three transposed instructions in the clamp tail:
// retail stores the low-clamped position and only then loads Buffer.Size for
// the high clamp, while cl hoists the size load above the store. Writing both
// clamps as `if` statements scores 5.9%.
int CCFileClass::Seek(int offset, int mode)
{
    if (this->Buffer.Buffer) {
        switch (mode) {
        case 0:  // SEEK_SET
            this->Position = 0;
            break;
        case 2:  // SEEK_END
            this->Position = this->Buffer.Size;
            break;
        }
        this->Position += offset;
        this->Position = this->Position < 0 ? 0 : this->Position;
        this->Position = this->Position > this->Buffer.Size ? this->Buffer.Size : this->Position;
        return this->Position;
    }
    return this->BufferIOFileClass::Seek(offset, mode);
}


// FUNCTION: GAMEMD 0x473C00  (__thiscall)
// CCFileClass::GetFileSize — buffered size when loaded; else, if the underlying
// file isn't available, look the size up by name in the MIX index; otherwise
// return the buffered file's size.
int CCFileClass::GetFileSize()
{
    if (this->Buffer.Buffer) {
        return this->Buffer.Size;
    }
    if (!this->BufferIOFileClass::Exists(false)) {
        int length = 0;
        MixFileClass_Offset(this->GetFileName(), 0, 0, 0, &length);
        return length;
    }
    return this->BufferIOFileClass::GetFileSize();
}

// FUNCTION: GAMEMD 0x473CE0  (__thiscall)
// CCFileClass::Close — drop the in-memory buffer, reset Position, close the
// underlying buffered file.
void CCFileClass::Close()
{
    new (&this->Buffer) MemoryBuffer((void*)0, 0);
    this->Position = 0;
    this->BufferIOFileClass::Close();
}

// RawFile name/size/bias methods. Provisional shared ownership, preserving
// the contributors' default VC6 flags and existing body spellings.
// LIBRARY: GAMEMD 0x007C93E8
// GameFree
void __cdecl GameFree(void* block);
// LIBRARY: GAMEMD 0x007D5408
// FUN_007D5408
char* __cdecl FUN_007D5408(const char* str);
// Win32 import: IAT 0x7E1120 (KERNEL32!GetFileSize).
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
    void* hFile, unsigned long* lpFileSizeHigh);
// Win32 import: IAT 0x7E1200 (KERNEL32!GetLastError).
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

// FUNCTION: GAMEMD 0x65CAC0  (__thiscall)
// RawFileClass::SetFileName — free any previously-allocated name, then (when a
// new name is given) reset the cursor/size, duplicate the string and store it;
// on allocation failure fault through CDCheck(0xC,...).
const char* RawFileClass::SetFileName(const char* pFileName)
{
    if (this->FileName && this->FileNameAllocated) {
        GameFree((void*)this->FileName);
        this->FileName = 0;
        this->FileNameAllocated = false;
    }

    if (!pFileName) {
        return 0;
    }

    this->FilePointer = 0;
    this->FileSize = -1;
    this->FileName = FUN_007D5408(pFileName);
    if (!this->FileName) {
        this->CDCheck(0xC, false, pFileName);
        return 0;
    }

    this->FileNameAllocated = true;
    return this->FileName;
}

// FUNCTION: GAMEMD 0x65D0D0  RawFileClass::GetFileSize (__thiscall, slot 11)
//
// Lazily resolves the cached FileSize. While the file is open the size comes
// straight from the handle (a failure is reported through CDCheck with the
// Win32 error and the size left at -1); when it is closed the file is opened
// read-only just long enough to ask the (virtual) size and closed again. Either
// way the cached value is the raw size less the bias FilePointer, so a biased
// (MIX-embedded) file reports only its own extent.
//
// Phrasing note: the early `return this->FileSize;` right after the store is
// load-bearing. It makes the freshly computed value the return register
// (MOV ECX,[FilePointer]; MOV EAX,EDI; SUB EAX,ECX; MOV [FileSize],EAX) and
// duplicates the tail into the CDCheck branch exactly as retail does; a single
// trailing `return FileSize` instead folds to SUB EDI,[..] + a re-load (7.3%),
// and a `result` local sinks the store past the epilogue pops (76.4%).
int RawFileClass::GetFileSize()
{
    int size = 0;

    if (this->FileSize == -1) {
        if (this->HasHandle()) {
            size = ::GetFileSize(this->Handle, 0);
            if (size == -1) {
                this->CDCheck(::GetLastError(), false, this->FileName);
            }
        } else {
            if (this->Open(1)) {
                size = this->GetFileSize();
                this->Close();
            }
        }
        this->FileSize = size - this->FilePointer;
        return this->FileSize;
    }

    return this->FileSize;
}

// FUNCTION: GAMEMD 0x65D2B0  (__thiscall)
// RawFileClass::Bias — window the file to [offset, offset+length). A zero start
// clears the bias; otherwise advance the cursor, clamp the size to the file size
// and the requested length, floor it at zero, and rewind if the file is open.
void RawFileClass::Bias(int offset, int length)
{
    if (offset == 0) {
        this->FilePointer = 0;
        this->FileSize = -1;
        return;
    }

    this->FileSize = this->RawFileClass::GetFileSize();
    this->FilePointer += offset;

    if (length != -1) {
        this->FileSize = this->FileSize >= length ? length : this->FileSize;
    }

    this->FileSize = this->FileSize > 0 ? this->FileSize : 0;

    if (this->HasHandle()) {
        this->RawFileClass::Seek(0, 0);
    }
}
