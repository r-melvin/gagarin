// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry-origin retail evidence at 0x4741F0 and 0x474320.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX

#include <string.h>
#include "ccini_class_read_ccfile_methods.h"
#include "../_layout/sha_pipe.h"

// FUNCTION: GAMEMD 0x4741F0
//
// Load an INI from a file through a FileStraw and, when asked, check its
// stored digest: the [Digest] block is read out and cleared, the rest of
// the file hashed through a SHAPipe into this object's digest, and a
// mismatch (or a missing block) reports status 2.
//
// The straw's members are assigned in retail's store order (links, file,
// flag, vtable) and every exit routes through one label so the explicit
// destructor call and the return value in ESI form one shared tail.
int CCINI_004741F0::ReadCCFile(File_004741F0* file, bool withDigest, bool flag)
{
    int rc;
    FileStraw_004741F0 straw;
    straw.ChainTo   = 0;
    straw.ChainFrom = 0;
    straw.File      = file;
    straw.HasOpened = 0;
    straw.Vtable    = &VT_007E4D90;

    int status = Load(&straw, flag);
    DigestValid = 0;
    if (status != 0 && withDigest) {
        unsigned char stored[0x14];
        int length = GetUUBlock(STR_0081BFE0, stored, 0x14);
        if (length == 0) {
            rc = 2;
            goto out;
        }
        if (length > 0) {
            Clear(STR_0081BFE0, 0);

            SHAPipe_004741F0 sha;
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

            Save((Pipe_004741F0*)&sha);
            ((SHAPipe*)&sha)->Result(Digest);
            DigestValid = 1;
            ((Pipe*)&sha)->Pipe::~Pipe();

            if (memcmp(stored, Digest, 0x14) != 0) {
                rc = 2;
                goto out;
            }
        }
    }
    rc = status;
out:
    straw.Destroy();
    return rc;
}

// FUNCTION: GAMEMD 0x474320
// Entry-origin bytes confirm the supplied stream call, +0x40/+0x41 digest
// fields, SHA stores and all return paths. Names and argument types retain
// this TU's call-view conventions; the original overload name is unknown.
int CCINI_004741F0::FUN_00474320(Pipe_004741F0* straw, bool withDigest, bool flag)
{
    int status = Load(straw, flag);
    DigestValid = 0;
    if (status != 0 && withDigest) {
        unsigned char stored[0x14];
        int length = GetUUBlock(STR_0081BFE0, stored, 0x14);
        if (length == 0) {
            return 2;
        }
        if (length > 0) {
            Clear(STR_0081BFE0, 0);

            SHAPipe_004741F0 sha;
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

            Save((Pipe_004741F0*)&sha);
            ((SHAPipe*)&sha)->Result(Digest);
            DigestValid = 1;
            ((Pipe*)&sha)->Pipe::~Pipe();

            if (memcmp(stored, Digest, 0x14) != 0) {
                return 2;
            }
        }
    }
    return status;
}
