// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473D10.

#include "ccfile_class_open_mix_methods.h"

// FUNCTION: GAMEMD 0x473D10
//
// Open a file that may live inside a MIX archive. Writing, or a name the
// buffered base already answers for, goes straight to the base open. A name
// the MIX index resolves either hands back an in-memory block (adopted into
// the buffer sub-object) or names the archive on disk, which is opened in
// its place and seeked to the entry.
//
int CCFileClass::Open(FileAccessMode mode)
{
    Close();

    if ((mode & 2) == 0 && !BufferIOFileClass::Exists(false)) {
        MixFileClass* mix = 0;
        void* data = 0;
        int size = 0;
        int offset = 0;
        if (MixFileClass_Offset(GetFileName(), &data,
                                         &mix, &offset, &size)) {
            if (data == 0 && mix != 0) {
                if (OpenEx(mix->FileName, 1)) {
                    char* dup = gg_strdup(GetFileName());
                    IsDisabled = 1;
                    SetFileName(dup);
                    IsDisabled = 0;
                    Bias(0, -1);
                    Bias(offset, size);
                    Seek(0, 0);
                    FUN_007C93E8(dup);
                    return 1;
                }
                return 0;
            }
            new (&Buffer) MemoryBuffer(data, size);
            Position = 0;
            return 1;
        }
        return CDFileClass::Open(mode);
    }
    return CDFileClass::Open(mode);
}
