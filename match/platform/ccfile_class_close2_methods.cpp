// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   address annotated below. Layout/vtable cross-checked against YRpp
//   (consult-only; reconfirmed from the disasm).
//
// Translation unit: RawFileClass::Close (the raw-file handle teardown).
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x65CCA0   RawFileClass::Close   (__thiscall)

#include "ccfile_class_close2_methods.h"

// FUNCTION: GAMEMD 0x65CCA0  (__thiscall)
// RawFileClass::Close — when the file holds an OS handle, close it; on a
// CloseHandle failure forward GetLastError() + the file name to CDCheck. The
// handle field is then poisoned to -1 regardless of the close result.
void RawFileClass::Close()
{
    if (this->HasHandle()) {
        BOOL result = CloseHandle(this->Handle);
        if (result == 0) {
            this->CDCheck(GetLastError(), result, this->FileName);
        }
        this->Handle = (HANDLE)-1;
    }
}
