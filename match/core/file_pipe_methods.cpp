// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI.
// Paired probes: /GX adds EH setup to the ordinary destructor; no-GX
// reproduces its complete span. The other three bodies match both sets.
#include "../_layout/file_pipe.h"
#include "../platform/ccfile_class.h"

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*).

// The scalar deleting destructor 0x477790 is emitted by the stack-FilePipe
// user (INIClass::FUN_00526420, platform/ini_class_stream_wrappers.cpp), where
// only the destructor declaration is visible; under /Ob2 it would otherwise
// inline the body below instead of calling it.

// FUNCTION: GAMEMD 0x7BA420
FilePipe::~FilePipe()
{
    if (File != 0 && HasOpened != 0) {
        HasOpened = 0;
        File->Close();
        File = 0;
    }
}

// FUNCTION: GAMEMD 0x7BA450
int FilePipe::FUN_00477740()
{
    int result = FUN_00631D30();
    if (File != 0 && HasOpened != 0) {
        HasOpened = 0;
        File->Close();
    }
    return result;
}

// FUNCTION: GAMEMD 0x7BA480
int FilePipe::FUN_00631D10(int first, int second)
{
    if (File == 0 || first == 0 || second <= 0) {
        return 0;
    }

    if (!File->HasHandle()) {
        HasOpened = 1;
        File->Open(2);
    }
    return File->WriteBytes((void*)first, second);
}
