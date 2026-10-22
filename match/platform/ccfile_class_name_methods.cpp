// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (consult-only; reconfirmed from the disasm).
//
// Translation unit: two RawFileClass name/bias primitives. Functions are
// ordered ascending by retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x65CAC0   RawFileClass::SetFileName   (__thiscall)
//   FUNCTION: GAMEMD 0x65D2B0   RawFileClass::Bias          (__thiscall)
//   FUNCTION: GAMEMD 0x65CF00   RawFileClass::Seek          (callee; reloc)
//   FUNCTION: GAMEMD 0x65D0D0   RawFileClass::GetFileSize   (callee; reloc)
//   FUNCTION: GAMEMD 0x7C93E8   GameFree                    (callee; reloc)
//   LIBRARY: GAMEMD 0x7D5408   GameStrdup                  (callee; reloc)

#include "ccfile_class_name_methods.h"

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
    this->FileName = GameStrdup(pFileName);
    if (!this->FileName) {
        this->CDCheck(0xC, false, pFileName);
        return 0;
    }

    this->FileNameAllocated = true;
    return this->FileName;
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
