// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65D240.

#include "raw_file_class_time_methods.h"

// Win32 imports reached through the IAT.
extern "C" __declspec(dllimport) int __stdcall GetFileInformationByHandle(
    void* hFile, Gg_BY_HANDLE_FILE_INFORMATION* lpFileInformation);
extern "C" __declspec(dllimport) int __stdcall DosDateTimeToFileTime(
    unsigned short wFatDate, unsigned short wFatTime, Gg_FILETIME* lpFileTime);
extern "C" __declspec(dllimport) int __stdcall SetFileTime(
    void* hFile, const Gg_FILETIME* lpCreationTime,
    const Gg_FILETIME* lpLastAccessTime, const Gg_FILETIME* lpLastWriteTime);

// FUNCTION: GAMEMD 0x65D240  RawFileClass::SetFileTime (__thiscall, ret 0x4)
// Stamp a DOS date/time pair onto the open file, keeping whatever creation time
// the file already had — which is why the existing information is fetched first
// and its ftCreationTime handed straight back.
//
// The method shadows the Win32 API of the same name, hence the `::`. The return
// is retail's full-width `NEG/SBB/NEG` form, so it must stay a direct
// `!= 0` rather than being bound to a bool local.
//
// All three failure paths share one trailing epilogue in retail, so the guards
// nest positively rather than returning early; the early-return spelling
// inlines three separate epilogues and scores 14.6%.
bool RawFileClass::SetFileTime(unsigned long fileTime)
{
    Gg_FILETIME                   ft;
    Gg_BY_HANDLE_FILE_INFORMATION info;

    if (Handle != (void*)-1) {
        if (GetFileInformationByHandle(Handle, &info)) {
            if (DosDateTimeToFileTime((unsigned short)(fileTime >> 16),
                                      (unsigned short)fileTime, &ft)) {
                return ::SetFileTime(Handle, &info.ftCreationTime, &ft, &ft) != 0;
            }
        }
    }

    return false;
}
