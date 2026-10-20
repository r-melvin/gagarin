// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x47AE10.
//   The strcpy/strcat are the /O2 intrinsics (REPNE SCASB + REP MOVSD/MOVSB).

#include <string.h>
#include "ccfile_class_set_name_methods.h"

// FUNCTION: GAMEMD 0x47AE10  CDFileClass::SetFileName (__thiscall, slot 2)
//
// Binds the file name, then, unless CD searching is disabled for this file,
// there is no search path list, or the bare name already exists, tries the
// name under each search-path prefix in turn until one exists. If none does
// the bare name is restored. Either way the (virtual) bound name is returned.
const char* CDFileClass::SetFileName(const char* name)
{
    char buffer[260];

    BufferIOFileClass::SetFileName(name);

    if (this->IsDisabled || DAT_0089E410 == 0 || BufferIOFileClass::Exists(0)) {
        return this->GetFileName();
    }

    for (SearchPath_0047AE10* node = DAT_0089E410; node != 0; node = node->Next) {
        strcpy(buffer, node->Path);
        strcat(buffer, name);
        BufferIOFileClass::SetFileName(buffer);
        if (BufferIOFileClass::Exists(0)) {
            return this->GetFileName();
        }
    }
    BufferIOFileClass::SetFileName(name);

    return this->GetFileName();
}
