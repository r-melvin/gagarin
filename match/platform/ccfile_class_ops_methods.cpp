// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// Translation unit: two FileClass-hierarchy file operations. Functions are
// ordered ascending by retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x47AF10   CDFileClass::OpenEx      (__thiscall)
//   FUNCTION: GAMEMD 0x65D190   RawFileClass::DeleteFile (__thiscall)
//   FUNCTION: GAMEMD 0x4325C0   BufferIOFileClass::Close       (callee; reloc)
//   FUNCTION: GAMEMD 0x431E80   BufferIOFileClass::SetFileName (callee; reloc)
//   FUNCTION: GAMEMD 0x431F70   BufferIOFileClass::Open        (callee; reloc)

#include "ccfile_class_ops_methods.h"

#include <windows.h>
// windows.h #defines DeleteFile -> DeleteFileA; that would rewrite the
// RawFileClass::DeleteFile method name. Drop the macro (the real Win32 entry
// point is reached explicitly as ::DeleteFileA below).
#undef DeleteFile

// FUNCTION: GAMEMD 0x47AF10  (__thiscall)
// CDFileClass::OpenEx — close any open file, reject a null name via the CD
// error path, then bind the name + open. When the CD file is live (not disabled)
// and the request is read-only (access != write/2), the name is set virtually so
// a derived override can intercept; otherwise the buffered-file name is set
// directly. Either way the open forwards to BufferIOFileClass::Open.
bool CDFileClass::OpenEx(const char* pFileName, FileAccessMode access)
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

// FUNCTION: GAMEMD 0x65D190  (__thiscall)
// RawFileClass::DeleteFile — close, validate the name, ensure the file exists,
// then ask Win32 to delete it. A null name or a Win32 failure routes through the
// CD/error virtual (CDCheck); only a successful DeleteFileA returns true.
int RawFileClass::DeleteFile()
{
    this->Close();
    if (this->FileName == 0) {
        this->CDCheck(2, false, 0);
        return 0;
    }
    if (!this->Exists(false)) {
        return 0;
    }
    BOOL ok = ::DeleteFileA(this->FileName);
    if (ok == 0) {
        this->CDCheck(GetLastError(), ok != 0, this->FileName);
        return 0;
    }
    return 1;
}
