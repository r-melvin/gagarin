// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// FileClass-hierarchy file primitives, split by original file so that a base
// class method is called, not expanded, from the derived class bodies:
//   ccfile_class.cpp            0x401940..0x4019A0, 0x4739F0..0x473CE0 (CCFileClass), 0x47AE10..0x47AF10 (CDFileClass)
//   ccfile_buffer_io_methods.cpp  0x431E80..0x4325A0 (BufferIOFileClass)
//   ccfile_raw_methods.cpp        0x65CAC0..0x65D2B0 (RawFileClass)
// Functions are ordered ascending by retail address.
//
#include "ccfile_class.h"
#include "../core/string_class.h"
#include <string.h>
#include "../_layout/cd_search_path.h"
#include <windows.h>
// Preserve the native RawFile method name; call the Win32 import explicitly.
#undef DeleteFile

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

// FUNCTION: GAMEMD 0x473CD0
bool CCFileClass::HasHandle()
{
    if (Buffer.Buffer != 0) return true;
    return BufferIOFileClass::HasHandle();
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

// FUNCTION: GAMEMD 0x47AE10  CDFileClass::SetFileName (__thiscall, slot 2)
//
// Binds the file name, then, unless CD searching is disabled for this file,
// there is no search path list, or the bare name already exists, tries the
// name under each search-path prefix in turn until one exists. If none does
// the bare name is restored. Either way the (virtual) bound name is returned.
const char* CDFileClass::SetFileName(const char* name)
{
    char buffer[260];

    BufferIOFileClass::SetFileName(name);

    if (this->IsDisabled || DAT_0089E410 == 0 || BufferIOFileClass::Exists(0)) {
        return this->GetFileName();
    }

    for (SearchPath_0047AE10* node = DAT_0089E410; node != 0; node = node->Next) {
        strcpy(buffer, node->Path);
        strcat(buffer, name);
        BufferIOFileClass::SetFileName(buffer);
        if (BufferIOFileClass::Exists(0)) {
            return this->GetFileName();
        }
    }
    BufferIOFileClass::SetFileName(name);

    return this->GetFileName();
}

// FUNCTION: GAMEMD 0x47AF10  (__thiscall)
// CDFileClass::OpenEx — close any open file, reject a null name via the CD
// error path, then bind the name + open. When the CD file is live (not disabled)
// and the request is read-only (access != write/2), the name is set virtually so
// a derived override can intercept; otherwise the buffered-file name is set
// directly. Either way the open forwards to BufferIOFileClass::Open.
int CDFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->BufferIOFileClass::Close();
    if (pFileName == 0) {
        this->CDCheck(2, false, pFileName);
    }
    if (this->IsDisabled == false && access != 2) {
        this->SetFileName(pFileName);
        return this->BufferIOFileClass::Open(access);
    }
    this->BufferIOFileClass::SetFileName(pFileName);
    return this->BufferIOFileClass::Open(access);
}
