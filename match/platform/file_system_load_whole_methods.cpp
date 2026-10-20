// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A38D0.

#include "file_system_load_whole_methods.h"

// FUNCTION: GAMEMD 0x4A38D0
//
// Fetch a whole file into memory. A hit in the MIX cache is returned as-is
// with the out-flag clear (the caller does not own it). Otherwise a stack file
// object is opened on the name; if it exists, a block of its size is allocated
// and the file read into it, and the out-flag records that the block was
// allocated. The file object is torn down inline: this class's vtable, the
// +0x64 reset, the +0x58 sub-object release, the base vtable, the base
// destructor.
void* __fastcall FileSystem_LoadWholeFileEx(const char* fileName, bool* allocated)
{
    *allocated = false;

    void* data = FUN_005B40B0(fileName, 0);
    if (data != 0) {
        return data;
    }

    File_004A38D0 file;
    file.FUN_004739F0(fileName);

    data = 0;
    if ((file.*file.Vtbl->At_14)(0)) {
        int size = (file.*file.Vtbl->At_2C)();
        data = FUN_007C8E17(size);
        if (data != 0) {
            (file.*file.Vtbl->At_24)(data, size);
        }
    }
    *allocated = data != 0;

    file.Vtbl    = (Vtbl_004A38D0*)&VT_007E16B0;
    file.Reset64 = 0;
    FUN_0043AE50(file.Sub58);
    file.Vtbl    = (Vtbl_004A38D0*)&VT_007E1668;
    FUN_00431B80(&file);

    return data;
}
