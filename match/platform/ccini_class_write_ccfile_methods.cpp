// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474430.

#include "ccini_class_write_ccfile_methods.h"
#include "../_layout/sha_pipe.h"

// FUNCTION: GAMEMD 0x474430
//
// Write the INI out through a file pipe. Without the digest the file is simply
// saved. With it, the old [Digest] section is cleared, the whole INI is run
// through a stack SHA-1 pipe, the 20-byte digest is cached at +0x41 (flag at
// +0x40), stored back as a UU-encoded [Digest] block, the file is saved with
// it, and the section is cleared again so the in-memory copy stays clean.
// Either way the byte count of the file save comes back.
int CCINI_00474430::WriteCCFile(File_00474430* file, bool withDigest)
{
    int result;
    FilePipe_00474430 pipe;
    pipe.File      = file;
    pipe.ChainTo   = 0;
    pipe.ChainFrom = 0;
    pipe.HasOpened = 0;
    pipe.Vtable    = &VT_007E4DA0;

    if (!withDigest) {
        result = Save(&pipe);
    } else {
        Clear(STR_0081BFE0, 0);

        SHAPipe_00474430 sha;
        sha.ChainTo      = 0;
        sha.ChainFrom    = 0;
        sha.IsCached     = 0;
        sha.Length       = 0;
        sha.PartialCount = 0;
        sha.Acc[0] = 0x67452301;
        sha.Acc[1] = 0xEFCDAB89;
        sha.Acc[2] = 0x98BADCFE;
        sha.Acc[3] = 0x10325476;
        sha.Acc[4] = 0xC3D2E1F0;
        sha.Vtable = &VT_007E4D78;

        Save((Pipe_00474430*)&sha);
        ((SHAPipe*)&sha)->Result(Digest);
        DigestValid = 1;
        ((Pipe*)&sha)->Pipe::~Pipe();

        PutUUBlock(STR_0081BFE0, Digest, 0x14);
        result = Save(&pipe);
        Clear(STR_0081BFE0, 0);
    }

    pipe.Destroy();
    return result;
}
