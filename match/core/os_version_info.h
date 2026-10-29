// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001, constructor at 0x776EB0 and the static object at 0x887598.
//
// The OS version record filled by GetVersionEx: the DAT_00887598 static object.
#ifndef GG_MATCH_CORE_OS_VERSION_INFO_H
#define GG_MATCH_CORE_OS_VERSION_INFO_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class OSVersionRecord
{
public:
    unsigned long Major;        // +0x00
    unsigned long Minor;        // +0x04
    unsigned long Build;        // +0x08
    char CSDVersion[0x80];      // +0x0C
    bool IsWin9x;               // +0x8C
    bool IsWinNT;               // +0x8D
    char unknown_8E[2];         // +0x8E
    // FUNCTION: GAMEMD 0x776EB0 (decl; reloc)
    OSVersionRecord();
    ~OSVersionRecord() {}
};
GG_STATIC_ASSERT(offsetof(OSVersionRecord, Minor) == 0x04);
GG_STATIC_ASSERT(offsetof(OSVersionRecord, Build) == 0x08);
GG_STATIC_ASSERT(offsetof(OSVersionRecord, CSDVersion) == 0x0C);
GG_STATIC_ASSERT(offsetof(OSVersionRecord, IsWin9x) == 0x8C);
GG_STATIC_ASSERT(offsetof(OSVersionRecord, IsWinNT) == 0x8D);
GG_STATIC_ASSERT(sizeof(OSVersionRecord) == 0x90);

#endif
