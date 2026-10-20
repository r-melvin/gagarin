// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x67FD20.

#include "load_options_read_methods.h"

// FUNCTION: GAMEMD 0x67FD20
//
// Open a save file as a structured-storage document and let the information
// record read itself out of it. The name is widened first; the storage handle
// behaves like a smart pointer — released if set before the open (a check the
// compiler cannot fold because the handle's address escapes to StgOpenStorage),
// and released again on both the success and the failure exit, each with its
// own inline copy of the release.
//
// The two failure exits are two early `if (x < 0) return false;` statements,
// not one `&&`: VC6 lays each if-body out as the fall-through and jumps
// forward to the continuation, then cross-jumps the first body's release into
// the second's (`MOV EAX,[storage]; JMP`), which is the retail block order.
// A single `if (hr >= 0 && Read() >= 0)` inverts both branches (JL instead of
// JGE) and puts the success block first.
bool __fastcall LoadOptionsClass_ReadFromFile(const char* fileName,
                                              SavegameInfo_0067FD20* info)
{
    IStorage_0067FD20* storage = 0;
    unsigned short     wide[64];

    MultiByteToWideChar(0, 0, fileName, -1, wide, 64);

    if (storage != 0) {
        COM_RELEASE_0067FD20(storage);
    }
    storage = 0;

    long hr = StgOpenStorage(wide, 0, 0x12, 0, 0, &storage);
    if (hr < 0) {
        if (storage != 0) {
            COM_RELEASE_0067FD20(storage);
        }
        return false;
    }

    if (info->Read(storage) < 0) {
        if (storage != 0) {
            COM_RELEASE_0067FD20(storage);
        }
        return false;
    }

    if (storage != 0) {
        COM_RELEASE_0067FD20(storage);
    }
    return true;
}
