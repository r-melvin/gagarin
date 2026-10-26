// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// The ordinary destructor at 0x7BA590 matches with /GX omitted; /GX adds
// exception-handler setup. All three entry spans below match using this set.
#include "../_layout/file_straw.h"
#include "../platform/ccfile_class.h"

// SYNTHETIC: GAMEMD 0x477770 -- compiler-generated FileStraw scalar deleting
// destructor. Full span 0x1E includes RET 4; its two call fields are COFF
// relocations to the ordinary destructor and operator delete.

// FUNCTION: GAMEMD 0x7BA530
int FileStraw::FUN_006C98E0(int buffer, int size)
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
    return File->ReadBytes((void*)buffer, size);
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
