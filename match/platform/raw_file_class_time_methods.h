// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, frame layout and imports derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x65D240 (full derivation in the RE
//   dossier, docs/decomp_spec/re_findings/next_targets_2026-08-07.md §1).
//   Imports resolved from the binary's own labels: 0x007E1128
//   GetFileInformationByHandle, 0x007E1130 DosDateTimeToFileTime, 0x007E112C
//   SetFileTime.
//
// The 0x3C-byte local frame is what pins the two locals: a
// BY_HANDLE_FILE_INFORMATION (0x34) at frame+0x08 exactly fills the block with
// a FILETIME at frame+0x00, and retail's third LEA (frame+0x0C) lands on that
// struct's ftCreationTime at its own +0x04.
#ifndef GG_MATCH_PLATFORM_RAW_FILE_CLASS_TIME_METHODS_H
#define GG_MATCH_PLATFORM_RAW_FILE_CLASS_TIME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Win32 shapes declared locally rather than pulled from <windows.h>, so the
// layout the frame depends on is explicit and asserted.
struct Gg_FILETIME
{
    unsigned long dwLowDateTime;   // +0x00
    unsigned long dwHighDateTime;  // +0x04
};
GG_STATIC_ASSERT(sizeof(Gg_FILETIME) == 0x08);

struct Gg_BY_HANDLE_FILE_INFORMATION
{
    unsigned long dwFileAttributes;      // +0x00
    Gg_FILETIME   ftCreationTime;        // +0x04
    Gg_FILETIME   ftLastAccessTime;      // +0x0C
    Gg_FILETIME   ftLastWriteTime;       // +0x14
    unsigned long dwVolumeSerialNumber;  // +0x1C
    unsigned long nFileSizeHigh;         // +0x20
    unsigned long nFileSizeLow;          // +0x24
    unsigned long nNumberOfLinks;        // +0x28
    unsigned long nFileIndexHigh;        // +0x2C
    unsigned long nFileIndexLow;         // +0x30
};
GG_STATIC_ASSERT(offsetof(Gg_BY_HANDLE_FILE_INFORMATION, ftCreationTime) == 0x04);
GG_STATIC_ASSERT(sizeof(Gg_BY_HANDLE_FILE_INFORMATION) == 0x34);

struct RawFileClass
{
    char  _pad00[0x14];   // +0x0000
    void* Handle;         // +0x0014  INVALID_HANDLE_VALUE (-1) means closed

    bool SetFileTime(unsigned long fileTime);   // GAMEMD 0x65D240
};
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle) == 0x14);

#endif  // GG_MATCH_PLATFORM_RAW_FILE_CLASS_TIME_METHODS_H
