// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: user's retail gamemd.exe v1.001 disassembly at 0x4A80D0-0x4A8265.
//
// Original translation unit placement is not attested by the binary (the
// function sits after the DiskLaser vector instantiations, with no alignment
// padding between its first bytes and the rest of the body), so it has a
// placeholder file of its own.
//
// CD::GetCDNumber: wait up to `timeout` ticks for the drive to have a readable
// volume, then check that the volume is labelled "YR1" and that "X:\YR1.dsk"
// can be opened. The retail image is the patched one: the original `sub esp,0x120`
// frame set-up (6 bytes) was overwritten with `mov eax,2 / ret`, so the function
// answers disc 2 at once. This body is the original and matches retail everywhere
// except those 6 bytes.

#include <windows.h>
#include <stddef.h>
#include "../_layout/elapsed_timer.h"

extern "C" int __cdecl _stricmp(const char*, const char*);

// FUNCTION: GAMEMD 0x4A80D0  CD::GetCDNumber (__fastcall)
// PARTIAL: first 6 bytes are the patch (see above).
int __fastcall CD_GetCDNumber(int drive, int timeout)
{
    ScenarioElapsedTimer timer;
    timer = ScenarioElapsedTimer(timeout);
    char path[0x80];
    char volume[0x80];
    DWORD maxComponent;
    DWORD flags;
    int letter = drive + 'A';

    wsprintfA(path, "%c:\\", letter);
    BOOL ok = GetVolumeInformationA(path, volume, 0x7F, 0, &maxComponent, &flags, 0, 0);
    while (!ok) {
        if (timer.GetTimeLeft() == 0) {
            return -1;
        }
        if (GetLastError() != ERROR_NOT_READY) {
            return -1;
        }
        wsprintfA(path, "%c:\\", letter);
        ok = GetVolumeInformationA(path, volume, 0x7F, 0, &maxComponent, &flags, 0, 0);
    }
    if (_stricmp("YR1", volume) != 0) {
        return -1;
    }
    for (int tries = 0;;) {
        wsprintfA(path, "%c:\\YR1.dsk", letter);
        HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL, 0);
        if (file != INVALID_HANDLE_VALUE) {
            CloseHandle(file);
            return 2;
        }
        if (++tries >= 2) {
            return -1;
        }
    }
}
