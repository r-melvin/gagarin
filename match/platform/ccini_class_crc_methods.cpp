// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x476D80.

#include "ccini_class_crc_methods.h"
#include "../_layout/sha_pipe.h"

// FUNCTION: GAMEMD 0x476D80
//
// A 32-bit checksum of the INI. The 20-byte SHA-1 digest at +0x41 is computed
// once (a stack hash engine is seeded, fed the whole file, and asked for its
// result) and cached behind the flag at +0x40; the returned value is a CRC run
// over that digest by a freshly zeroed CRC engine.
int CCINI_00476D80::GetCRC()
{
    if (DigestValid == 0) {
        SHA_00476D80 sha;
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

        FUN_00526470(&sha);
        ((SHAPipe*)&sha)->Result(Digest);
        DigestValid = 1;
        ((Pipe*)&sha)->Pipe::~Pipe();
    }

    CRC_00476D80 crc;
    crc.CRC     = 0;
    crc.Staging = 0;
    crc.Index   = 0;
    return crc.FUN_004A1DE0(Digest, 0x14);
}
