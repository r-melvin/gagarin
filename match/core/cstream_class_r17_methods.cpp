// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A3020 in the user's retail gamemd.exe v1.001.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /Ob2
//
// CStreamClass block writer (layout and tables in _layout/cstream_class.h).
// Address index: 0x4A3020.

#include "../_layout/cstream_class.h"
#include "lz_pipe.h"

// FUNCTION: GAMEMD 0x4A3020
// Compresses `count` bytes into the staging buffer and writes them to the wrapped
// stream as one block: the 8-byte header first, then the compressed bytes.
HRESULT CStreamClass::FUN_004A3020(char* buffer, int count)
{
    unsigned int compressed = count;
    lzo1x_1_compress((unsigned char*)buffer, count, (unsigned char*)InBuffer, &compressed, unknown_20);
    Header.UncompressedSize = 0x10000;
    ULONG written = 0;
    Header.CompressedSize = compressed;
    HRESULT hr = Stream->Write(&Header, 8, &written);
    if (hr >= 0) {
        if (written != 8)
            return E_FAIL;
        hr = Stream->Write(InBuffer, compressed, &written);
        if (hr >= 0)
            hr = written != compressed ? E_FAIL : S_OK;
    }
    return hr;
}
