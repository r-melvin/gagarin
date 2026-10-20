// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65CBF0 (name from
//   the YRpp method map, consult-only).

#include "ccfile_class_exists_methods.h"

// FUNCTION: GAMEMD 0x65CBF0  RawFileClass::Exists (__thiscall, ret 0x4)
//
// Does the named file exist? No name means no. An already-open handle means
// yes. When `forced`, the file is opened for read and closed again (the close
// is the inlined RawFileClass::Close) and the answer is yes regardless.
// Otherwise a read-only CreateFileA probe decides: an invalid handle is no,
// and a good one is closed (reporting a close failure through the CD-check
// hook) and forgotten before answering yes.
bool RawFileClass::Exists(int forced)
{
    if (FileName == 0) {
        return false;
    }
    if (HasHandle()) {
        return true;
    }
    if (forced) {
        RawFileClass::Open(1);
        RawFileClass::Close();
        return true;
    }

    void* handle = CreateFileA(FileName, 0x80000000, 1, 0, 3, 0x80, 0);
    Handle = handle;
    if (handle == (void*)-1) {
        return false;
    }
    if (!CloseHandle(handle)) {
        CDCheck(GetLastError(), 0, FileName);
    }
    Handle = (void*)-1;
    return true;
}
