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
// Load-bearing: the buffered probe, the position setter and the base open
// are all direct __thiscall calls with their arguments pushed, not
// __fastcall helpers — declaring them as members is what puts the zero in
// EBX for every store and compare, keeps the mode parameter in its home
// slot, and leaves the two fallback tails as separate copies. The buffer
// setter is reached through a pointer local that retail null-tests first,
// and the in-archive branch tests the open positively with its own
// `return 0` after the body.
int CCFile_00473D10::Open(unsigned int mode)
{
    (this->*Vtbl->Close)();

    if ((mode & 2) == 0 && !FUN_00431F10(0)) {
        Mix_00473D10* mix = 0;
        void* data = 0;
        int size = 0;
        int offset = 0;
        if (MixFileClass_Offset_00473D10((this->*Vtbl->GetFileName)(), &data,
                                         &mix, &offset, &size)) {
            if (data == 0 && mix != 0) {
                if ((this->*Vtbl->At_20)(mix->FileName, 1)) {
                    char* dup = gg_strdup((this->*Vtbl->GetFileName)());
                    IsDisabled = 1;
                    (this->*Vtbl->SetFileName)(dup);
                    IsDisabled = 0;
                    FUN_0065D2B0(0, -1);
                    FUN_0065D2B0(offset, size);
                    (this->*Vtbl->At_28)(0, 0);
                    gg_free(dup);
                    return 1;
                }
                return 0;
            }
            Buffer_00473D10* buffer = &Buffer;
            if (buffer != 0) {
                buffer->FUN_0043AD00(data, size);
            }
            Position = 0;
            return 1;
        }
        return FUN_0047AAB0(mode);
    }
    return FUN_0047AAB0(mode);
}
