// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4799D0, 0x479A40, 0x479AB0 and 0x479B00 and the format
//   strings they pass to the debug log (0x81C40C, 0x81C4BC, 0x81C3D0, 0x81C390).
//
// Volume IOCTL helpers used while opening a CD drive. Each issues one DeviceIoControl on the
// volume handle and logs the system error text slot when it fails.
// Address index: 0x479900 open, 0x4799D0 lock, 0x479A40 unlock, 0x479AB0 dismount, 0x479B00 prevent removal.

#include <windows.h>
#include <stdio.h>

void FUN_004068E0(const char* format, ...);  // GAMEMD 0x4068E0, debug log (cdecl)

// FUNCTION: GAMEMD 0x479900
// Open the drive `drive` (0 = A:) as a raw volume: removable and CD drives only, the former
// for read and write, the latter read-only. Returns INVALID_HANDLE_VALUE on failure.
HANDLE __stdcall FUN_00479900(char drive)
{
    char root[8];
    char device[8];
    sprintf(root, "%c:\\", drive + 'A');
    UINT type = GetDriveTypeA(root);
    DWORD access;
    switch (type) {
    case 2:
        access = 0xC0000000;
        break;
    case 5:
        access = 0x80000000;
        break;
    default:
        FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
        return INVALID_HANDLE_VALUE;
    }
    sprintf(device, "\\\\.\\%c:", drive + 'A');
    HANDLE handle = CreateFileA(device, access, 3, 0, 3, 0, 0);
    if (handle == INVALID_HANDLE_VALUE)
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
    return handle;
}

// FUNCTION: GAMEMD 0x4799D0
// Lock the volume (FSCTL_LOCK_VOLUME), retrying up to twenty times half a second apart.
bool __stdcall FUN_004799D0(HANDLE volume)
{
    for (int attempt = 0; attempt < 20; attempt++) {
        DWORD returned;
        BOOL ok = DeviceIoControl(volume, 0x90018, 0, 0, 0, 0, &returned, 0);
        if (ok)
            return true;
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), ok);
        Sleep(500);
    }
    return false;
}

// FUNCTION: GAMEMD 0x479A40
// Unlock the volume (FSCTL_UNLOCK_VOLUME) with the same retry loop.
bool __stdcall FUN_00479A40(HANDLE volume)
{
    for (int attempt = 0; attempt < 20; attempt++) {
        DWORD returned;
        BOOL ok = DeviceIoControl(volume, 0x9001C, 0, 0, 0, 0, &returned, 0);
        if (ok)
            return true;
        FUN_004068E0("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), ok);
        Sleep(500);
    }
    return false;
}

// FUNCTION: GAMEMD 0x479AB0
// Dismount the volume (FSCTL_DISMOUNT_VOLUME); one attempt.
bool __stdcall FUN_00479AB0(HANDLE volume)
{
    DWORD returned;
    bool ok = DeviceIoControl(volume, 0x90020, 0, 0, 0, 0, &returned, 0) != 0;
    if (!ok)
        FUN_004068E0("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
    return ok;
}

// FUNCTION: GAMEMD 0x479B00
// Allow or prevent media removal (IOCTL_STORAGE_MEDIA_REMOVAL); one attempt.
bool __stdcall FUN_00479B00(HANDLE volume, bool prevent)
{
    DWORD returned;
    unsigned char request = prevent;
    bool ok = DeviceIoControl(volume, 0x2D4804, &request, 1, 0, 0, &returned, 0) != 0;
    if (!ok)
        FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
    return ok;
}
