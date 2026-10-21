// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired probes: /GX adds EH setup to the ordinary destructor; no-GX
// reproduces its complete span. The other three bodies match both sets.
#include "../_layout/file_pipe.h"

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*).

// SYNTHETIC: GAMEMD 0x477790 -- compiler-generated scalar deleting
// destructor; its body calls the ordinary destructor at 0x7BA420.

// FUNCTION: GAMEMD 0x7BA420
FilePipe::~FilePipe()
{
    if (File != 0 && HasOpened != 0) {
        HasOpened = 0;
        File->FUN_slot34();
        File = 0;
    }
}

// FUNCTION: GAMEMD 0x7BA450
int FilePipe::FUN_00477740()
{
    int result = FUN_00631D30();
    if (File != 0 && HasOpened != 0) {
        HasOpened = 0;
        File->FUN_slot34();
    }
    return result;
}

// FUNCTION: GAMEMD 0x7BA480
int FilePipe::FUN_00631D10(int first, int second)
{
    if (File == 0 || first == 0 || second <= 0) {
        return 0;
    }

    if (!File->FUN_slot18()) {
        HasOpened = 1;
        File->FUN_slot1C(2);
    }
    return File->FUN_slot30(first, second);
}
