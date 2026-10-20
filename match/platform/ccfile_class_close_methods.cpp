// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   CCFileClass.h (consult-only; reconfirmed from the disasm).
//
// Translation unit: the FileClass-hierarchy close/file-time primitives.
// Functions are ordered ascending by retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4325C0   BufferIOFileClass::Close        (__thiscall)
//   FUNCTION: GAMEMD 0x65D1F0   RawFileClass::GetFileTime       (__thiscall)
//   FUNCTION: GAMEMD 0x431DD0   BufferIOFileClass::Commit  (callee; reloc)
//   FUNCTION: GAMEMD 0x65CCA0   RawFileClass::Close        (callee; reloc)

#include "ccfile_class_close_methods.h"

#include <windows.h>

// FUNCTION: GAMEMD 0x4325C0  (__thiscall)
// BufferIOFileClass::Close — flush the write buffer, then close the underlying
// raw file. When still buffered and the buffer carries a tail (unknown_50), the
// commit re-enters virtually (clearing flag_29 so the re-entry takes the plain
// raw-close path).
void BufferIOFileClass::Close()
{
    if (this->flag_29) {
        this->Commit();
        if (this->flag_26) {
            if (this->unknown_50 != 0) {
                this->flag_29 = false;
                this->Close();                 // virtual self-dispatch (slot 13)
                this->flag_29 = true;
            } else {
                this->RawFileClass::Close();
            }
            this->flag_26 = false;
        }
        this->flag_25 = false;
    } else {
        this->RawFileClass::Close();
    }
}

// FUNCTION: GAMEMD 0x65D1F0  (__thiscall)
// RawFileClass::GetFileTime — query the file's last-write time and fold it into
// a packed DOS date/time word: (FatDate << 16) | FatTime. Returns 0 when the
// handle cannot be queried.
unsigned long RawFileClass::GetFileTime()
{
    BY_HANDLE_FILE_INFORMATION info;
    unsigned short dosDate;
    unsigned short dosTime;

    if (GetFileInformationByHandle(this->Handle, &info)) {
        FileTimeToDosDateTime(&info.ftLastWriteTime, &dosDate, &dosTime);
        return (dosDate << 16) | dosTime;
    }
    return 0;
}
