// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6B5490.

#include "smudge_type_class_load_methods.h"
#include "../_layout/memory_buffer.h"

// FUNCTION: GAMEMD 0x6B5490
//
// Load the theater-specific smudge art. For every smudge type flagged as
// theater-dependent, the file name is the type's ID with the theater's
// extension, opened as a stack file object whose whole contents become the
// type's image. The file object is torn down inline: this class's vtable, the
// +0x64 reset, the +0x58 sub-object release, the base vtable, the base
// destructor.
void __fastcall SmudgeTypeClass::LoadFromIniList(int idxTheater)
{
    for (int i = 0; i < DAT_00A8EC28; ++i) {
        SmudgeTypeClass* type = DAT_00A8EC1C[i];
        if (type->Theater) {
            char path[0x200];
            _makepath(path, 0, 0, type->ID, DAT_007E1B78[idxTheater].Extension);

            File_006B5490 file;
            file.FUN_004739F0(path);
            type->Image = file.ReadWholeFile();

            file.Vtbl    = &VT_007E16B0;
            file.Reset64 = 0;
            ((MemoryBuffer*)file.Sub58)->Clear();
            file.Vtbl    = &VT_007E1668;
            FUN_00431B80(&file);
        }
    }
}
