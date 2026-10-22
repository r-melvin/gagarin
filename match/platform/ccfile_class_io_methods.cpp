// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below. Layout/vtable cross-checked against YRpp
//   CCFileClass.h / MixFileClass.h (consult-only; reconfirmed from the disasm).
//
// Translation unit: the CCFileClass buffered-IO virtual primitives. Functions
// are ordered ascending by retail address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x473AE0   CCFileClass::WriteBytes        (__thiscall)
//   FUNCTION: GAMEMD 0x473BA0   CCFileClass::Seek              (__thiscall)
//   FUNCTION: GAMEMD 0x473C00   CCFileClass::GetFileSize       (__thiscall)
//   FUNCTION: GAMEMD 0x432050   BufferIOFileClass::WriteBytes  (callee; reloc)
//   FUNCTION: GAMEMD 0x4324B0   BufferIOFileClass::Seek        (callee; reloc)
//   FUNCTION: GAMEMD 0x431F10   BufferIOFileClass::Exists      (callee; reloc)
//   FUNCTION: GAMEMD 0x4325A0   BufferIOFileClass::GetFileSize (callee; reloc)
//   FUNCTION: GAMEMD 0x5B4430   MixFileClass::Offset           (callee; reloc)

#include "ccfile_class_io_methods.h"

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
