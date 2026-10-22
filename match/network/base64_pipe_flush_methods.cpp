// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Entry-origin span 0x42DF40..0x42DF8F (0x50 bytes), ending in RET. The
// candidate's compiled ABI symbol is ?FUN_00631D30@Base64Pipe@@UAEHXZ: public
// virtual member returning int, no explicit arguments. Raw calls at 0x42DF5D/6D
// target codec entries 0x42FD30/0x42FE50 (ECX receiver, EDX pending count, two stack
// arguments); calls at 0x42DF76/86 target Pipe methods 0x631D10/0x631D30.
// The 0x631D10 call is a direct base-qualified method target, not dispatch to
// the capped Base64Pipe::FUN_00631D10 entry. Retail reads Mode/Pending, clears
// Pending, and forms the two asserted buffer addresses. No full object-size
// or destructor/table claim is made.
// Paired /GX probe produced the same exact body and relocation targets.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
#include "base64_pipe_flush_methods.h"

// FUNCTION: GAMEMD 0x42FD30 (decl; reloc) -- external call target only.
int __fastcall FUN_0042FD30(void* state, int pending, void* buffer, int width);
// FUNCTION: GAMEMD 0x42FE50 (decl; reloc) -- external call target only.
int __fastcall FUN_0042FE50(void* state, int pending, void* buffer, int width);

// FUNCTION: GAMEMD 0x42DF40
int Base64Pipe::FUN_00631D30()
{
    int encoded = 0;

    if (Pending != 0) {
        unsigned char* buffer;
        int written;

        if (Mode == 0) {
            buffer = At_14;
            written = FUN_0042FD30(At_18, Pending, buffer, 4);
        } else {
            buffer = At_18;
            written = FUN_0042FE50(At_14, Pending, buffer, 3);
        }

        encoded = Pipe::FUN_00631D10((int)buffer, written);
        Pending = 0;
    }

    return Pipe::FUN_00631D30() + encoded;
}
