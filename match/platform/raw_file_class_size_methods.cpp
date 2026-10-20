// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65D0D0.
//   LIBRARY: IAT 0x7E1120 KERNEL32!GetFileSize, IAT 0x7E1200 KERNEL32!GetLastError.

#include "raw_file_class_size_methods.h"

// Win32 imports reached through the IAT (CALL dword ptr [0x7E1120] /
// [0x7E1200] in retail).
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
    void* hFile, unsigned long* lpFileSizeHigh);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

// FUNCTION: GAMEMD 0x65D0D0  RawFileClass::GetFileSize (__thiscall, slot 11)
//
// Lazily resolves the cached FileSize. While the file is open the size comes
// straight from the handle (a failure is reported through CDCheck with the
// Win32 error and the size left at -1); when it is closed the file is opened
// read-only just long enough to ask the (virtual) size and closed again. Either
// way the cached value is the raw size less the bias FilePointer, so a biased
// (MIX-embedded) file reports only its own extent.
//
// Phrasing note: the early `return this->FileSize;` right after the store is
// load-bearing. It makes the freshly computed value the return register
// (MOV ECX,[FilePointer]; MOV EAX,EDI; SUB EAX,ECX; MOV [FileSize],EAX) and
// duplicates the tail into the CDCheck branch exactly as retail does; a single
// trailing `return FileSize` instead folds to SUB EDI,[..] + a re-load (7.3%),
// and a `result` local sinks the store past the epilogue pops (76.4%).
int RawFileClass::GetFileSize()
{
    int size = 0;

    if (this->FileSize == -1) {
        if (this->HasHandle()) {
            size = ::GetFileSize(this->Handle, 0);
            if (size == -1) {
                this->CDCheck(::GetLastError(), false, this->FileName);
            }
        } else {
            if (this->Open(1)) {
                size = this->GetFileSize();
                this->Close();
            }
        }
        this->FileSize = size - this->FilePointer;
        return this->FileSize;
    }

    return this->FileSize;
}
