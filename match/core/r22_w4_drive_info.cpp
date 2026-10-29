// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Drive information query read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//   Address index: 0x751DD0.

#include <windows.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct DriveInfo_00751DD0
{
    UINT DriveType;            // +0x00
    char VolumeName[0x40];     // +0x04
    DWORD SerialNumber;        // +0x44
    char FileSystem[0x40];     // +0x48
    DWORD TotalSpace;          // +0x88
    DWORD FreeSpace;           // +0x8C
};
GG_STATIC_ASSERT(offsetof(DriveInfo_00751DD0, SerialNumber) == 0x44);
GG_STATIC_ASSERT(offsetof(DriveInfo_00751DD0, FileSystem) == 0x48);
GG_STATIC_ASSERT(sizeof(DriveInfo_00751DD0) == 0x90);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log.
void __cdecl FUN_004068E0(const char* format, int value);

// FUNCTION: GAMEMD 0x751DD0
// Fills `info` with the drive type, volume details and space figures for `root`; false when a
// query fails (or the free-cluster figure is nonzero).
bool __fastcall FUN_00751DD0(const char* root, DriveInfo_00751DD0* info)
{
    DWORD sectorsPerCluster;
    DWORD bytesPerSector;
    DWORD freeClusters;
    DWORD totalClusters;
    DWORD maxComponent;
    DWORD fsFlags;

    memset(info, 0, sizeof(*info));
    info->DriveType = GetDriveTypeA(root);
    BOOL ok = GetDiskFreeSpaceA(root, &sectorsPerCluster, &bytesPerSector, &freeClusters, &totalClusters);
    if (!ok) {
        FUN_004068E0("GetDiskFreeSpace() failed: %s\n", ok);
        return false;
    }
    info->TotalSpace = sectorsPerCluster * bytesPerSector * freeClusters;
    if (freeClusters != 0) {
        return false;
    }
    info->FreeSpace = sectorsPerCluster * bytesPerSector * totalClusters;
    ok = GetVolumeInformationA(root, info->VolumeName, 0x40, &info->SerialNumber, &maxComponent, &fsFlags,
                               info->FileSystem, 0x40);
    if (!ok) {
        FUN_004068E0("GetVolumeInformation() - failed: %s\n", ok);
        return false;
    }
    return true;
}
