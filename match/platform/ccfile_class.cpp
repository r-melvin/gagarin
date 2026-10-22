// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   CCFileClass.h / YRAllocator.h (consult-only; reconfirmed from the disasm).
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
bool CCFileClass::OpenEx(const char* pFileName, FileAccessMode access)
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
bool BufferIOFileClass::OpenEx(const char* pFileName, FileAccessMode access)
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

// FUNCTION: GAMEMD 0x473CE0  (__thiscall)
// CCFileClass::Close — drop the in-memory buffer, reset Position, close the
// underlying buffered file.
void CCFileClass::Close()
{
    new (&this->Buffer) MemoryBuffer((void*)0, 0);
    this->Position = 0;
    this->BufferIOFileClass::Close();
}
