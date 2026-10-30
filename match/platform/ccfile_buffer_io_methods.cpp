// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   (reconfirmed from the disasm).
//
// FileClass-hierarchy file primitives, kept in separate TUs so that a base
// class method is called, not expanded, from the derived class bodies:
//   ccfile_class.cpp            0x401940..0x4019A0, 0x4739F0..0x473CE0 (CCFileClass), 0x47AE10..0x47AF10 (CDFileClass)
//   ccfile_buffer_io_methods.cpp  0x431B80..0x432610 (BufferIOFileClass)
//   ccfile_raw_methods.cpp        0x65CAC0..0x65D2B0 (RawFileClass)
// Functions are ordered ascending by retail address.
//
#include "ccfile_class.h"
#include "buffer_io_file_class_dtor_methods.h"
#include "../core/string_class.h"
#include <string.h>
#include "../_layout/cd_search_path.h"
#include <windows.h>
// Preserve the native RawFile method name; call the Win32 import explicitly.
#undef DeleteFile



// Native 431FC6/432014 access +2C; 43202C/43202F write +40/+44.
// REA ev_68756c05fde955eb65b5a0f9185bc5bb2e6ac97fb97dff18f1e38b6dc49efffd.
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(sizeof(((BufferIOFileClass*)0)->unknown_2C) == 4);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(sizeof(((BufferIOFileClass*)0)->unknown_40) == 4);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_int_44) == 0x44);
GG_STATIC_ASSERT(sizeof(((BufferIOFileClass*)0)->unknown_int_44) == 4);

// FUNCTION: GAMEMD 0x431B80  BufferIOFileClass::~BufferIOFileClass (__thiscall)
//
// The buffer is only freed when this object allocated it; a caller-supplied
// buffer is dropped without being released, which is why the allocated flag is
// tested inside the non-null branch rather than alongside it.
BufferIOFileClass::~BufferIOFileClass()
{
    if (unknown_30) {
        if (unknown_bool_24) {
            FUN_007C8B3D(unknown_30);
            unknown_bool_24 = 0;
        }
        unknown_30 = 0;
    }

    unknown_34 = 0;
    unknown_bool_25 = 0;
    unknown_bool_27 = 0;
    unknown_bool_28 = 0;
    unknown_bool_29 = 0;

}

// FUNCTION: GAMEMD 0x431D90
// Close: release the buffer if owned, then reset every flag. The destructor at
// 0x431B80 is this plus the vtable install and the base call, and the two agree
// on the layout - which is the cross-check that makes both trustworthy.
void BufferIOFileClass::FUN_00431D90()
{
    if (unknown_30) {
        if (unknown_bool_24) {
            FUN_007C8B3D(unknown_30);
            unknown_bool_24 = 0;
        }
        unknown_30 = 0;
    }

    unknown_34 = 0;
    unknown_bool_25 = 0;
    unknown_bool_27 = 0;
    unknown_bool_28 = 0;
    unknown_bool_29 = 0;
}

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

// FUNCTION: GAMEMD 0x431F70  BufferIOFileClass::Open (__thiscall, slot 7)
//
// (Re)opens the file for the given access. Whatever was open is closed first
// (the inlined BufferIOFileClass::Close). Without a live buffer this is just
// the raw open. With one, the access is recorded; a read-only open whose
// buffer already holds the whole file needs no disk file at all (the open flag
// is cleared and only the position state is reset); a write open is turned
// into a read/write one after the raw layer has truncated the file and the
// attached buffer is dropped. Otherwise the file is opened through the virtual
// Open (buffer flag dropped around the call) when a buffer is attached, or
// through the raw base, and a write open restarts the buffered size. The
// position/dirty state is reset on every buffered path.
int BufferIOFileClass::Open(FileAccessMode access)
{
    BufferIOFileClass::Close();

    if (this->unknown_bool_29) {
        this->unknown_2C = access;
        if (access == 1) {
            if (this->unknown_int_48 <= (int)this->unknown_34) {
                this->unknown_bool_26 = false;
                goto reset;
            }
        } else if (access == 2) {
            RawFileClass::Open(access);
            RawFileClass::Close();
            access = 3;
            this->unknown_50 = 0;
        }

        if (this->unknown_50 != 0) {
            this->unknown_bool_29 = false;
            this->Open(access);
            this->unknown_bool_29 = true;
        } else {
            RawFileClass::Open(access);
        }
        this->unknown_bool_26 = true;
        if (this->unknown_2C == 2) {
            this->unknown_int_48 = 0;
        }

reset:
        this->unknown_38 = 0;
        this->unknown_3C = 0;
        this->unknown_40 = (unsigned int)-1;
        this->unknown_int_44 = -1;
        this->unknown_4C = 0;
        this->unknown_bool_25 = true;
        return 1;
    }

    return RawFileClass::Open(access);
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

// FUNCTION: GAMEMD 0x4325C0  (__thiscall)
// BufferIOFileClass::Close — flush the write buffer, then close the underlying
// raw file. When still buffered and the buffer carries a tail (unknown_50), the
// commit re-enters virtually (clearing unknown_bool_29 so the re-entry takes the plain
// raw-close path).
void BufferIOFileClass::Close()
{
    if (this->unknown_bool_29) {
        this->Commit();
        if (this->unknown_bool_26) {
            if (this->unknown_50 != 0) {
                this->unknown_bool_29 = false;
                this->Close();                 // virtual self-dispatch (slot 13)
                this->unknown_bool_29 = true;
            } else {
                this->RawFileClass::Close();
            }
            this->unknown_bool_26 = false;
        }
        this->unknown_bool_25 = false;
    } else {
        this->RawFileClass::Close();
    }
}

// SYNTHETIC: GAMEMD 0x432610 -- compiler-generated BufferIOFileClass scalar deleting destructor.
