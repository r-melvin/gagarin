// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x776EB0.
//
// Address index: 0x776EB0

#include <windows.h>
#include <string.h>
#include "os_version_info.h"

// FUNCTION: GAMEMD 0x776EB0
// Fill the record from GetVersionEx: version numbers, the service pack text and the platform flags.
OSVersionRecord::OSVersionRecord()
{
    Major = 0;
    Minor = 0;
    Build = 0;
    IsWin9x = false;
    IsWinNT = false;
    OSVERSIONINFOA info;
    info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&info);
    Major = info.dwMajorVersion;
    Minor = info.dwMinorVersion;
    Build = info.dwBuildNumber;
    if (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        IsWin9x = true;
    } else if (info.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        IsWinNT = true;
    }
    strncpy(CSDVersion, info.szCSDVersion, 0x7F);
    CSDVersion[0x7F] = 0;
}
