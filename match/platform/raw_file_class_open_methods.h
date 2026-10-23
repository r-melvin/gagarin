// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x65CB50: `[ESI+0x8]` (the stored
//   access mode), `[ESI+0xC]` / `[ESI+0x10]` (file pointer / size, the seek
//   guard), `[ESI+0x14]` (the handle, INVALID_HANDLE_VALUE when closed),
//   `[ESI+0x18]` (the name); slots `CALL [EAX+0x34]` (Close),
//   `CALL [EDX+0x40]` (CDCheck, with 2), `CALL [EAX+0x28]` (Seek). The
//   hierarchy and slot order are the committed model in
//   match/platform/ccfile_class.h (not editable here, so the class is
//   redeclared locally with the Open override it lacks); YRpp
//   consulted for names only. YRpp binds 0x65CB50
//   to CCFileClass::Open; the bytes touch RawFileClass members and call
//   CreateFileA directly, and the committed model places CDFileClass::Open
//   at 0x47AAB0 and CCFileClass::Open at 0x473D10, so this is
//   RawFileClass::Open.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned int FileAccessMode;

// KERNEL32 CreateFileA through the IAT (retail: `CALL [0x7E11BC]`), so
// dllimport keeps the call indirect.
extern "C" __declspec(dllimport) void* __stdcall CreateFileA(
    const char* fileName, unsigned long desiredAccess, unsigned long shareMode,
    void* securityAttributes, unsigned long creationDisposition,
    unsigned long flagsAndAttributes, void* templateFile);

#include "ccfile_class.h"

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_OPEN_METHODS_H
