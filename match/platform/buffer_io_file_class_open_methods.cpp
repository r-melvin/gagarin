// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x431F70.
//   FUNCTION: GAMEMD 0x431DD0   BufferIOFileClass::Commit   (callee; reloc)
//   FUNCTION: GAMEMD 0x65CB50   RawFileClass::Open          (callee; reloc)
//   FUNCTION: GAMEMD 0x65CCA0   RawFileClass::Close         (callee; reloc)

#include "ccfile_class.h"

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


