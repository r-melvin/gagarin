// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// FileClass-hierarchy file primitives, split by original file so that a base
// class method is called, not expanded, from the derived class bodies:
//   ccfile_class.cpp            0x401940..0x4019A0, 0x4739F0..0x473CE0 (CCFileClass), 0x47AE10..0x47AF10 (CDFileClass)
//   ccfile_buffer_io_methods.cpp  0x431E80..0x4325A0 (BufferIOFileClass)
//   ccfile_raw_methods.cpp        0x65CAC0..0x65D2B0 (RawFileClass)
// Functions are ordered ascending by retail address.
//
#include "ccfile_class.h"
#include "../core/string_class.h"
#include <string.h>
#include "../_layout/cd_search_path.h"
#include <windows.h>
// Preserve the native RawFile method name; call the Win32 import explicitly.
#undef DeleteFile

#pragma function(memcpy)


// GLOBAL: GAMEMD 0xB04BEC
// Existing byte flag read at 0x65CD71 and cleared at 0x65CDB1; storage unowned.
extern bool IsReadingAudioFile;


// Native 0x65D240 local-frame and imported Win32 record layout.
GG_STATIC_ASSERT(sizeof(FILETIME) == 8);
GG_STATIC_ASSERT(offsetof(FILETIME, dwLowDateTime) == 0);
GG_STATIC_ASSERT(offsetof(FILETIME, dwHighDateTime) == 4);
GG_STATIC_ASSERT(sizeof(BY_HANDLE_FILE_INFORMATION) == 0x34);
GG_STATIC_ASSERT(offsetof(BY_HANDLE_FILE_INFORMATION, ftCreationTime) == 4);
// Native 0x65D20F addresses lastWriteTime; DOS outputs use WORDs.
GG_STATIC_ASSERT(offsetof(BY_HANDLE_FILE_INFORMATION, ftLastWriteTime) == 0x14);
GG_STATIC_ASSERT(sizeof(WORD) == 2);
GG_STATIC_ASSERT(sizeof(DWORD) == 4);

// RawFile name/size/bias methods. Provisional shared ownership, preserving
// the contributors' default VC6 flags and existing body spellings.
// LIBRARY: GAMEMD 0x007C93E8
// GameFree
void __cdecl GameFree(void* block);
// LIBRARY: GAMEMD 0x007D5408
// FUN_007D5408
char* __cdecl FUN_007D5408(const char* str);
// Win32 import: IAT 0x7E1120 (KERNEL32!GetFileSize).
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
    void* hFile, unsigned long* lpFileSizeHigh);
// Win32 import: IAT 0x7E1200 (KERNEL32!GetLastError).
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

// FUNCTION: GAMEMD 0x65CAC0  (__thiscall)
// RawFileClass::SetFileName — free any previously-allocated name, then (when a
// new name is given) reset the cursor/size, duplicate the string and store it;
// on allocation failure fault through CDCheck(0xC,...).
const char* RawFileClass::SetFileName(const char* pFileName)
{
    if (this->FileName && this->FileNameAllocated) {
        GameFree((void*)this->FileName);
        this->FileName = 0;
        this->FileNameAllocated = false;
    }

    if (!pFileName) {
        return 0;
    }

    this->FilePointer = 0;
    this->FileSize = -1;
    this->FileName = FUN_007D5408(pFileName);
    if (!this->FileName) {
        this->CDCheck(0xC, false, pFileName);
        return 0;
    }

    this->FileNameAllocated = true;
    return this->FileName;
}

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

// FUNCTION: GAMEMD 0x65D190  (__thiscall)
// RawFileClass::DeleteFile — close, validate the name, ensure the file exists,
// then ask Win32 to delete it. A null name or a Win32 failure routes through the
// CD/error virtual (CDCheck); only a successful DeleteFileA returns true.
int RawFileClass::DeleteFile()
{
    this->Close();
    if (this->FileName == 0) {
        this->CDCheck(2, false, 0);
        return 0;
    }
    if (!this->Exists(false)) {
        return 0;
    }
    BOOL ok = ::DeleteFileA(this->FileName);
    if (ok == 0) {
        this->CDCheck(GetLastError(), ok != 0, this->FileName);
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x65D1F0  (__thiscall)
// RawFileClass::GetFileTime — query the file's last-write time and fold it into
// a packed DOS date/time word: (FatDate << 16) | FatTime. Returns 0 when the
// handle cannot be queried.
unsigned long RawFileClass::GetFileTime()
{
    BY_HANDLE_FILE_INFORMATION info;
    unsigned short dosDate;
    unsigned short dosTime;

    if (GetFileInformationByHandle(this->Handle, &info)) {
        FileTimeToDosDateTime(&info.ftLastWriteTime, &dosDate, &dosTime);
        return (dosDate << 16) | dosTime;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x65D240  RawFileClass::SetFileTime (__thiscall, ret 0x4)
// Stamp a DOS date/time pair onto the open file, keeping whatever creation time
// the file already had — which is why the existing information is fetched first
// and its ftCreationTime handed straight back.
//
// The method shadows the Win32 API of the same name, hence the `::`. The return
// successful API result uses full-width NEG/SBB/NEG; the failure tail clears
// only AL. Keep the existing direct != 0 expression and bool return contract.
//
// All three failure paths share one trailing epilogue in retail, so the guards
// nest positively rather than returning early; the early-return spelling
// inlines three separate epilogues and scores 14.6%.
bool RawFileClass::SetFileTime(unsigned long fileTime)
{
    FILETIME                   ft;
    BY_HANDLE_FILE_INFORMATION info;

    if (Handle != (void*)-1) {
        if (GetFileInformationByHandle(Handle, &info)) {
            if (DosDateTimeToFileTime((unsigned short)(fileTime >> 16),
                                      (unsigned short)fileTime, &ft)) {
                return ::SetFileTime(Handle, &info.ftCreationTime, &ft, &ft) != 0;
            }
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x65D2B0  (__thiscall)
// RawFileClass::Bias — window the file to [offset, offset+length). A zero start
// clears the bias; otherwise advance the cursor, clamp the size to the file size
// and the requested length, floor it at zero, and rewind if the file is open.
void RawFileClass::Bias(int offset, int length)
{
    if (offset == 0) {
        this->FilePointer = 0;
        this->FileSize = -1;
        return;
    }

    this->FileSize = this->RawFileClass::GetFileSize();
    this->FilePointer += offset;

    if (length != -1) {
        this->FileSize = this->FileSize >= length ? length : this->FileSize;
    }

    this->FileSize = this->FileSize > 0 ? this->FileSize : 0;

    if (this->HasHandle()) {
        this->RawFileClass::Seek(0, 0);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB04BEC
bool IsReadingAudioFile;
// END defined globals
