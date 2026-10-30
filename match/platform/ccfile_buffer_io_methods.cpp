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
