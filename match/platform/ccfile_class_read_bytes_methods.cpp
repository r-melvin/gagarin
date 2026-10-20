// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473B10.

#include "ccfile_class_read_bytes_methods.h"

#pragma function(memcpy)

// FUNCTION: GAMEMD 0x473B10
//
// Read from a MIX-resident file. If the file is not open it is opened for
// reading here and closed again on the way out. With an in-memory buffer the
// read is a bounded memcpy from the current position; without one it is handed
// to the BufferIOFileClass base.
int CCFileClass::ReadBytes(void* pBuffer, int nBytes)
{
    bool opened = false;

    if (!this->HasHandle()) {
        if (this->Open(1)) {
            opened = true;
        }
    }

    if (this->Buffer.Buffer != 0) {
        int available = this->Buffer.Size - this->Position;
        if (available < nBytes) {
            nBytes = available;
        }
        if (nBytes != 0) {
            memcpy(pBuffer, (char*)this->Buffer.Buffer + this->Position, nBytes);
            this->Position = this->Position + nBytes;
        }
        if (opened) {
            this->Close();
        }
        return nBytes;
    }

    nBytes = BufferIOFileClass::ReadBytes(pBuffer, nBytes);
    if (opened) {
        this->Close();
    }
    return nBytes;
}
