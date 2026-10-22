// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473F00. Names from
//   YRpp (consult-only).

#include "ccfile_class_set_file_time_methods.h"

// FUNCTION: GAMEMD 0x473F00
//
// Stamp a DOS date/time onto the file. The raw-file path is tried first; if
// the file is not a loose file on disk, the MIX archive that contains it is
// located and a temporary CCFileClass over that archive's own file name is
// asked to stamp the archive instead. The temporary is built and torn down
// through explicit Construct/Destruct calls (see the header for why).
bool CCFileClass::SetFileTime(unsigned long fileTime)
{
    Mix_00473F00* mix = 0;

    bool ok = this->FUN_0065D240(fileTime);
    if (!ok) {
        if (FUN_005B4430((this->*this->Vtbl->GetFileName)(), 0, &mix, 0, 0)) {
            CCFileClass file;
            file.Construct(mix->FileName);
            ok = (file.*file.Vtbl->SetFileTime)(fileTime);
            file.Destruct();
        }
    }
    return ok;
}
