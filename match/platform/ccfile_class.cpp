// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// Translation unit: the FileClass-hierarchy file primitives (GetFileName,
// Exists, OpenEx, GetFileSize, the CCFileClass constructor, Close). Functions are ordered ascending by
// retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x401940   RawFileClass::GetFileName       (__thiscall)
//   FUNCTION: GAMEMD 0x401950   CDFileClass scalar deleting destructor
//   FUNCTION: GAMEMD 0x401980   CCFileClass::OpenEx             (__thiscall)
//   FUNCTION: GAMEMD 0x4019A0   CCFileClass scalar deleting destructor
//   FUNCTION: GAMEMD 0x431F10   BufferIOFileClass::Exists       (__thiscall)
//   FUNCTION: GAMEMD 0x431F50   BufferIOFileClass::OpenEx       (__thiscall)
//   FUNCTION: GAMEMD 0x4325A0   BufferIOFileClass::GetFileSize  (__thiscall)
//   FUNCTION: GAMEMD 0x4739F0   CCFileClass::CCFileClass        (__thiscall)
//   FUNCTION: GAMEMD 0x473CE0   CCFileClass::Close              (__thiscall)
//   FUNCTION: GAMEMD 0x65CBF0   RawFileClass::Exists       (callee; reloc)
//   FUNCTION: GAMEMD 0x65D0D0   RawFileClass::GetFileSize  (callee; reloc)
//   FUNCTION: GAMEMD 0x431F70   BufferIOFileClass::Open    (callee; reloc)
//   FUNCTION: GAMEMD 0x4325C0   BufferIOFileClass::Close   (callee; reloc)
//   FUNCTION: GAMEMD 0x43AD00   MemoryBuffer::MemoryBuffer (callee; reloc)

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

// Standard placement new: returns the placement pointer unchanged. Used by
// CCFileClass::Close to re-construct its MemoryBuffer in place (which is how
// retail emits LEA &Buffer / TEST / JZ / CALL ctor at 0x473CE0).
inline void* operator new(size_t, void* p) throw() { return p; }

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

// FUNCTION: GAMEMD 0x401940  (__thiscall)
// Return the stored file-name pointer (RawFileClass::FileName @ +0x18).
const char* RawFileClass::GetFileName() const
{
    return this->FileName;
}

// FUNCTION: GAMEMD 0x401950
// CDFileClass's scalar deleting destructor, slot 0 of vtable 0x7E1668,
// generated from the inline ~CDFileClass; emitted here with the vtable.

// FUNCTION: GAMEMD 0x401980  (__thiscall)
// CCFileClass::OpenEx — set the name then open. Both dispatched virtually:
//   this->SetFileName(name)   -> CALL [vtable+0x08]
//   return this->Open(access) -> CALL [vtable+0x1C]
int CCFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->SetFileName(pFileName);
    return this->Open(access);
}

// FUNCTION: GAMEMD 0x4019A0
// CCFileClass's scalar deleting destructor, slot 0 of vtable 0x7E16B0. The
// compiler generates it from the inline ~CCFileClass; this object emits it
// with the vtable, which the constructor below references.

// FUNCTION: GAMEMD 0x431E80  BufferIOFileClass::SetFileName (__thiscall, slot 2)
//
// Renames the file. If a name is already set and the buffer is live
// (unknown_bool_29), renaming to the same name is a no-op that just hands the
// current name back; renaming to a different one first commits the pending
// buffer and clears its dirty flag (unknown_bool_27). Either way the base
// RawFileClass::SetFileName does the actual (strdup'd) rename and the new name
// is fetched back through the virtual accessor.
const char* BufferIOFileClass::SetFileName(const char* pFileName)
{
    if (this->GetFileName() != 0 && this->unknown_bool_29) {
        if (strcmp(pFileName, this->GetFileName()) == 0) {
            return this->GetFileName();
        }
        this->Commit();
        this->unknown_bool_27 = false;
    }

    RawFileClass::SetFileName(pFileName);
    return this->GetFileName();
}


// FUNCTION: GAMEMD 0x431F10  (__thiscall)
// BufferIOFileClass::Exists — already-open shortcut, else defer to the raw file.
bool BufferIOFileClass::Exists(int writeShared)
{
    if (this->unknown_bool_29)
        return true;
    return this->RawFileClass::Exists(false);
}

// FUNCTION: GAMEMD 0x431F30
bool BufferIOFileClass::HasHandle()
{
    if (unknown_bool_25 != 0) {
        if (unknown_bool_29 != 0) return true;
        return Handle != (void*)-1;
    }
    return Handle != (void*)-1;
}

// FUNCTION: GAMEMD 0x431F50  (__thiscall)
// BufferIOFileClass::OpenEx — set the name virtually, then open via the
// class-qualified (non-virtual, direct CALL) BufferIOFileClass::Open.
int BufferIOFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->SetFileName(pFileName);
    return this->BufferIOFileClass::Open(access);
}

// FUNCTION: GAMEMD 0x4324B0  BufferIOFileClass::Seek
//
// With no buffer in play this is the raw seek. Otherwise the buffered
// position is moved (absolute, relative, or from the end), an offset past
// the base at +0x50 is taken relative to it, and the position is clamped to
// [0, size]. When the file fits the buffer the window index just follows;
// otherwise a position inside the current window re-indexes it and one
// outside commits the buffer and re-seeks the underlying file (through the
// virtual Seek with buffering switched off while a base is set). The
// result is the position, re-based when the offset had been.
//
// Layout notes: the whole buffered path sits inside `if (unknown_bool_29)`
// so the raw seek is the trailing fall-through; the mode dispatch is a
// `switch` (retail's SUB/JZ chain); and the size test is written
// `size <= window` first so the simple index store falls through and the
// window/reload arms trail into the return tail.
int BufferIOFileClass::Seek(int offset, int mode)
{
    if (this->unknown_bool_29) {
        bool rebased = false;
        switch (mode) {
        case 0:
            this->unknown_4C = 0;
            break;
        case 2:
            this->unknown_4C = this->unknown_int_48;
            break;
        }

        if (this->unknown_50 != 0 && offset >= (int)this->unknown_50) {
            offset -= this->unknown_50;
            rebased = true;
        }

        this->unknown_4C += offset;
        if ((int)this->unknown_4C < 0)
            this->unknown_4C = 0;
        if ((int)this->unknown_4C > this->unknown_int_48)
            this->unknown_4C = this->unknown_int_48;

        if (this->unknown_int_48 <= (int)this->unknown_34) {
            this->unknown_38 = this->unknown_4C;
        } else if ((int)this->unknown_4C >= (int)this->unknown_3C
                   && (int)this->unknown_4C < (int)(this->unknown_34 + this->unknown_3C)) {
            this->unknown_38 = this->unknown_4C - this->unknown_3C;
        } else {
            this->Commit();
            if (this->unknown_50 != 0) {
                this->unknown_bool_29 = false;
                this->Seek(this->unknown_4C, 0);
                this->unknown_bool_29 = true;
            } else {
                RawFileClass::Seek(this->unknown_4C, 0);
            }
            this->unknown_bool_27 = false;
        }

        if (this->unknown_50 != 0 && rebased)
            return this->unknown_4C + this->unknown_50;
        return this->unknown_4C;
    }
    return RawFileClass::Seek(offset, mode);
}

// FUNCTION: GAMEMD 0x4325A0  (__thiscall)
// BufferIOFileClass::GetFileSize — buffered size when buffered & open, else the
// raw file size (tail call).
int BufferIOFileClass::GetFileSize()
{
    if (this->unknown_bool_25 && this->unknown_bool_29)
        return this->unknown_int_48;
    return this->RawFileClass::GetFileSize();
}

// FUNCTION: GAMEMD 0x473A30
CCFileClass::CCFileClass(const Wstring& name) : Buffer(0, 0), Position(0)
{
    Availability = 0;
    const char* filename = name.FUN_007B5440();
    Availability = 0;
    CDFileClass::SetFileName(filename);
}

// FUNCTION: GAMEMD 0x473A80
CCFileClass::CCFileClass() : Buffer(0, 0), Position(0)
{
    Availability = 0;
}

// FUNCTION: GAMEMD 0x473AE0  (__thiscall)
// CCFileClass::WriteBytes — when the file is buffered in memory, fire the
// CD-protection check (error 0xD) against the file name, then forward the write
// to the underlying buffered file.
int CCFileClass::WriteBytes(void* pBuffer, int nNumBytes)
{
    if (this->Buffer.Buffer) {
        this->CDCheck(0xD, false, this->GetFileName());
    }
    return this->BufferIOFileClass::WriteBytes(pBuffer, nNumBytes);
}


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

// FUNCTION: GAMEMD 0x473BA0  (__thiscall)
// CCFileClass::Seek — seek within the in-memory buffer (clamped to [0, Size]);
// otherwise defer to the buffered file.
//
// PARTIAL, 90.6% (29/32). Three transposed instructions in the clamp tail:
// retail stores the low-clamped position and only then loads Buffer.Size for
// the high clamp, while cl hoists the size load above the store. Writing both
// clamps as `if` statements scores 5.9%.
int CCFileClass::Seek(int offset, int mode)
{
    if (this->Buffer.Buffer) {
        switch (mode) {
        case 0:  // SEEK_SET
            this->Position = 0;
            break;
        case 2:  // SEEK_END
            this->Position = this->Buffer.Size;
            break;
        }
        this->Position += offset;
        this->Position = this->Position < 0 ? 0 : this->Position;
        this->Position = this->Position > this->Buffer.Size ? this->Buffer.Size : this->Position;
        return this->Position;
    }
    return this->BufferIOFileClass::Seek(offset, mode);
}


// FUNCTION: GAMEMD 0x473C00  (__thiscall)
// CCFileClass::GetFileSize — buffered size when loaded; else, if the underlying
// file isn't available, look the size up by name in the MIX index; otherwise
// return the buffered file's size.
int CCFileClass::GetFileSize()
{
    if (this->Buffer.Buffer) {
        return this->Buffer.Size;
    }
    if (!this->BufferIOFileClass::Exists(false)) {
        int length = 0;
        MixFileClass_Offset(this->GetFileName(), 0, 0, 0, &length);
        return length;
    }
    return this->BufferIOFileClass::GetFileSize();
}

// FUNCTION: GAMEMD 0x473CD0
bool CCFileClass::HasHandle()
{
    if (Buffer.Buffer != 0) return true;
    return BufferIOFileClass::HasHandle();
}

// FUNCTION: GAMEMD 0x473CE0  (__thiscall)
// CCFileClass::Close — drop the in-memory buffer, reset Position, close the
// underlying buffered file.
void CCFileClass::Close()
{
    new (&this->Buffer) MemoryBuffer((void*)0, 0);
    this->Position = 0;
    this->BufferIOFileClass::Close();
}

// FUNCTION: GAMEMD 0x47AE10  CDFileClass::SetFileName (__thiscall, slot 2)
//
// Binds the file name, then, unless CD searching is disabled for this file,
// there is no search path list, or the bare name already exists, tries the
// name under each search-path prefix in turn until one exists. If none does
// the bare name is restored. Either way the (virtual) bound name is returned.
const char* CDFileClass::SetFileName(const char* name)
{
    char buffer[260];

    BufferIOFileClass::SetFileName(name);

    if (this->IsDisabled || DAT_0089E410 == 0 || BufferIOFileClass::Exists(0)) {
        return this->GetFileName();
    }

    for (SearchPath_0047AE10* node = DAT_0089E410; node != 0; node = node->Next) {
        strcpy(buffer, node->Path);
        strcat(buffer, name);
        BufferIOFileClass::SetFileName(buffer);
        if (BufferIOFileClass::Exists(0)) {
            return this->GetFileName();
        }
    }
    BufferIOFileClass::SetFileName(name);

    return this->GetFileName();
}

// FUNCTION: GAMEMD 0x47AF10  (__thiscall)
// CDFileClass::OpenEx — close any open file, reject a null name via the CD
// error path, then bind the name + open. When the CD file is live (not disabled)
// and the request is read-only (access != write/2), the name is set virtually so
// a derived override can intercept; otherwise the buffered-file name is set
// directly. Either way the open forwards to BufferIOFileClass::Open.
int CDFileClass::OpenEx(const char* pFileName, FileAccessMode access)
{
    this->BufferIOFileClass::Close();
    if (pFileName == 0) {
        this->CDCheck(2, false, pFileName);
    }
    if (this->IsDisabled == false && access != 2) {
        this->SetFileName(pFileName);
        return this->BufferIOFileClass::Open(access);
    }
    this->BufferIOFileClass::SetFileName(pFileName);
    return this->BufferIOFileClass::Open(access);
}


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
