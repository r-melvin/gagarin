// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x642C20 in the user's gamemd.exe v1.001.
//
// Address index: 0x642C20

#include "progress_screen_class.h"
#include "../platform/file_system_load_whole_methods.h"

// FUNCTION: GAMEMD 0x52FF90 (decl; reloc) -- clear the primary surface and show the named picture.
void __fastcall FUN_0052FF90(const char* name, bool refresh);

// FUNCTION: GAMEMD 0x642C20 (__thiscall, RET 0xC)
// Replace the screen's data file buffer with the named file, then optionally show its picture
// and remember the value.
void ProgressScreenClass::LoadBackground(const char* file, const char* picture, int value)
{
    if (file != 0) {
        if (Buffer != 0) {
            if (BufferOwned) {
                delete Buffer;
                BufferOwned = false;
            }
            Buffer = 0;
        }
        Buffer = (char*)FileSystem_LoadWholeFileEx(file, &BufferOwned);
        if (Buffer != 0) {
            if (picture != 0) {
                unknown_5C = picture;
                FUN_0052FF90(picture, false);
            }
            unknown_74 = value;
        }
    }
}
