// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473E50 (name from the
//   YRpp method map).

#include "ccfile_class_file_time_methods.h"

// FUNCTION: GAMEMD 0x473E50
//
// The file's timestamp. A real file on disk answers through the raw base. A
// file that only exists inside a MIX archive answers with the archive's own
// timestamp: the archive is located through MixFileClass::Offset, a stack
// file object is constructed on the archive's name (the 0x4739F0 constructor
// inlined), its virtual GetFileTime is taken, and the object is torn down
// inline: this class's vtable, the +0x64 reset, the buffer release, the base
// vtable, the base destructor.
unsigned long CCFileClass::GetFileTime()
{
    Mix_00473E50* mix = 0;
    unsigned long time = this->RawFileClass_GetFileTime();
    if (time == 0) {
        if (MixFileClass_Offset((this->*this->Vtbl->GetFileName)(), 0, &mix, 0, 0)) {
            const char* name = mix->FileName;
            CCFileClass file;
            file.Construct(name);

            time = (file.*file.Vtbl->GetFileTime)();

            file.Vtbl     = (Vtbl_00473E50*)&VT_007E16B0;
            file.Position = 0;
            FUN_0043AE50(&file.Buffer);
            file.Vtbl     = (Vtbl_00473E50*)&VT_007E1668;
            FUN_00431B80(&file);
            return time;
        }
    }
    return time;
}
