// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65CDD0.
//   LIBRARY: IAT 0x7E11A0 KERNEL32!WriteFile, IAT 0x7E1200
//   KERNEL32!GetLastError, IAT 0x7E11C0 KERNEL32!SetFilePointer.

#include "ccfile_class.h"

// Win32 imports reached through the IAT.
extern "C" __declspec(dllimport) int __stdcall WriteFile(
    void* hFile, const void* lpBuffer, unsigned long nNumberOfBytesToWrite,
    unsigned long* lpNumberOfBytesWritten, void* lpOverlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
    void* hFile, long lDistanceToMove, long* lpDistanceToMoveHigh,
    unsigned long dwMoveMethod);

inline int RawFileClass::RawSeek(int offset, int mode)
{
    if (!this->HasHandle()) {
        this->CDCheck(9, 0, this->FileName);
        return 0;
    }
    int pos = SetFilePointer(this->Handle, offset, 0, mode);
    if (pos == -1) {
        this->CDCheck(GetLastError(), 0, this->FileName);
        return 0;
    }
    return pos;
}

// FUNCTION: GAMEMD 0x65CDD0  RawFileClass::WriteBytes (__thiscall, slot 12)
//
// Writes `size` bytes from `buffer`. If the file is not open it is opened for
// writing for the duration and closed again at the end. A failed WriteFile
// raises CDCheck with the Win32 error. When the file carries a bias (a MIX
// sub-file extent) and the write ran past its end, the bias length is grown
// to the new raw position; both raw seeks are expanded inline.
int RawFileClass::WriteBytes(void* buffer, int size)
{
    int bytes_written = 0;
    int opened = 0;

    if (!this->HasHandle()) {
        if (!this->Open(2)) {
            return 0;
        }
        opened = 1;
    }

    if (!WriteFile(this->Handle, buffer, size, (unsigned long*)&bytes_written, 0)) {
        this->CDCheck(GetLastError(), 0, this->FileName);
    }

    if (this->FileSize != -1) {
        if (this->RawSeek(0, 1) > this->FilePointer + this->FileSize) {
            this->FileSize = this->RawSeek(0, 1) - this->FilePointer;
        }
    }

    if (opened) {
        this->Close();
    }
    return bytes_written;
}
