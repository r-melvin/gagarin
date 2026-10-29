// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI.
// The ordinary destructor at 0x7BA590 matches with /GX omitted; /GX adds
// exception-handler setup. All three entry spans below match using this set.
#include "../_layout/file_straw.h"
#include "../platform/ccfile_class.h"

// The scalar deleting destructor 0x477770 is emitted by the stack-FileStraw
// user (INIClass::FUN_00525A10, platform/ini_class_stream_wrappers.cpp), where
// only the destructor declaration is visible; under /Ob2 it would otherwise
// inline the body below instead of calling it.

// FUNCTION: GAMEMD 0x7BA530
int FileStraw::FUN_006C98E0(void* buffer, int size)
{
    if (File == 0 || buffer == 0 || size <= 0) {
        return 0;
    }

    if (!File->HasHandle()) {
        HasOpened = 1;
        if (!File->Exists(0)) {
            return 0;
        }
        if (!File->Open(1)) {
            return 0;
        }
    }
    return File->ReadBytes(buffer, size);
}

// FUNCTION: GAMEMD 0x7BA590
FileStraw::~FileStraw()
{
    if (File != 0 && HasOpened != 0) {
        File->Close();
        HasOpened = 0;
        File = 0;
    }
}
