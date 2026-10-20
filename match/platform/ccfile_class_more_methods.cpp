// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   CCFileClass.h / Memory.h (consult-only; reconfirmed from the disasm).
//
// Translation unit: two more FileClass-hierarchy primitives. Functions are
// ordered ascending by retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4A3890   FileClass::ReadWholeFile   (__thiscall)
//   FUNCTION: GAMEMD 0x65D150   RawFileClass::CreateFile   (__thiscall)

#include "ccfile_class_more_methods.h"

// FUNCTION: GAMEMD 0x4A3890  (__thiscall)
// FileClass::ReadWholeFile — if the file exists, allocate a block of its size
// and read the whole thing into it; return the block (or 0). Exists, GetFileSize
// and ReadBytes are dispatched virtually on `this`.
void* FileClass::ReadWholeFile()
{
    void* buffer = 0;
    if (this->Exists(false)) {
        int size = this->GetFileSize();
        buffer = GameAllocate(size);
        if (buffer) {
            this->ReadBytes(buffer, size);
        }
    }
    return buffer;
}

// FUNCTION: GAMEMD 0x65D150  (__thiscall)
// RawFileClass::CreateFile — close, open for write (access 2); on success seek to
// the start when the size is known (!= -1), close again and report success.
int RawFileClass::CreateFile()
{
    this->Close();
    if (this->Open(2)) {
        if (this->FileSize != -1) {
            this->Seek(0, 0);
        }
        this->Close();
        return 1;
    }
    return 0;
}
