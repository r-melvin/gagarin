// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65CCE0.
//   LIBRARY: IAT 0x7E111C KERNEL32!ReadFile, IAT 0x7E1200 KERNEL32!GetLastError.

#include "raw_file_class_read_bytes_methods.h"

// Win32 imports reached through the IAT (CALL dword ptr [0x7E111C] /
// [0x7E1200] in retail).
extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void* hFile, void* lpBuffer, unsigned long nNumberOfBytesToRead,
    unsigned long* lpNumberOfBytesRead, void* lpOverlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

// FUNCTION: GAMEMD 0x65CCE0  RawFileClass::ReadBytes (__thiscall, slot 9)
//
// Reads up to `size` bytes into `buffer`. If the file is not open it is opened
// read-only for the duration and closed again at the end. When the cached
// FileSize is known the request is clipped to what remains past the current
// (virtual) seek position, so a biased MIX-embedded file cannot read past its
// own extent. Short reads loop until the request is satisfied or ReadFile
// returns zero bytes; a failed ReadFile raises CDCheck with the Win32 error
// unless the audio streamer owns the file, in which case the read stops
// quietly. The streamer flag is cleared on the way out.
//
// Phrasing note: `total` is declared after the size clip and the three
// pointer/size/total updates are written out in both the failure and the
// success arm (with `continue` on failure). That is what puts `total` in EBX
// (which also serves as the shared zero for the two frame slots and the Seek
// argument) and keeps the frame at two slots; a single update after the
// ReadFile test with `total` declared at the top leaves EBX as a persistent
// zero and spills `total` to a third slot (5.3%).
int RawFileClass::ReadBytes(void* buffer, int size)
{
    int bytes_read = 0;
    int opened = 0;

    if (!this->HasHandle()) {
        if (!this->Open(1)) {
            return 0;
        }
        opened = 1;
    }

    if (this->FileSize != -1) {
        int remaining = this->FileSize - this->Seek(0, 1);
        if (size >= remaining) {
            size = remaining;
        }
    }

    int total = 0;
    while (size > 0) {
        bytes_read = 0;
        if (!ReadFile(this->Handle, buffer, size, (unsigned long*)&bytes_read, 0)) {
            buffer = (char*)buffer + bytes_read;
            size -= bytes_read;
            total += bytes_read;
            if (IsReadingAudioFile) {
                break;
            }
            this->CDCheck(GetLastError(), 1, this->FileName);
            continue;
        }
        buffer = (char*)buffer + bytes_read;
        size -= bytes_read;
        total += bytes_read;
        if (bytes_read == 0) {
            break;
        }
    }

    bytes_read = total;
    IsReadingAudioFile = false;
    if (opened) {
        this->Close();
    }
    return bytes_read;
}
