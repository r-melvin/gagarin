// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65CB50.

#include "raw_file_class_open_methods.h"

// FUNCTION: GAMEMD 0x65CB50  RawFileClass::Open (__thiscall, ret 0x4)
//
// Close whatever was open, refuse (through the CD-check hook, code 2) when no
// name is set, then open the named file for read, write or read/write with the
// matching Win32 disposition. A pending file pointer or a known size re-seeks
// to the start. The answer is whether a handle came back.
int RawFileClass::Open(FileAccessMode access)
{
    Close();

    const char* name = FileName;
    if (name == 0) {
        CDCheck(2, 0, 0);
        return 0;
    }

    FileAccess = access;

    switch (access) {
    case 1:
        Handle = CreateFileA(name, 0x80000000, 3, 0, 3, 0x8000080, 0);
        break;
    case 2:
        Handle = CreateFileA(name, 0x40000000, 0, 0, 2, 0x80, 0);
        break;
    case 3:
        Handle = CreateFileA(name, 0xC0000000, 0, 0, 4, 0x80, 0);
        break;
    }

    if (FilePointer != 0 || FileSize != -1) {
        Seek(0, 0);
    }

    return Handle != (void*)-1;
}
