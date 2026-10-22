// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//
// Removable-drive lock / eject helpers. The NT paths open "\\.\X:" and drive
// the FSCTL / IOCTL_STORAGE device controls; the 9x paths go through the
// VWIN32 DOS IOCTL (int 21h 440Dh) block. Each method logs its failures
// through the printf-style sink at 0x4068E0.
//
// LIBRARY: IAT 0x7E11B8 KERNEL32!DeviceIoControl, 0x7E11BC CreateFileA,
//   0x7E11E0 CloseHandle, 0x7E11F0 Sleep, 0x7E1200 GetLastError,
//   0x7E125C GetDriveTypeA.

#include <stddef.h>
#include <stdio.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef void* HANDLE;

extern "C" __declspec(dllimport) int __stdcall DeviceIoControl(
    HANDLE device, DWORD code, void* in, DWORD in_size, void* out,
    DWORD out_size, DWORD* returned, void* overlapped);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    char const* name, DWORD access, DWORD share, void* security,
    DWORD disposition, DWORD flags, HANDLE templ);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD ms);
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError(void);
extern "C" __declspec(dllimport) unsigned __stdcall GetDriveTypeA(char const* root);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0x887624 -- set when the 9x (VWIN32) path is used.
extern bool DAT_00887624;

// VWIN32 DIOC register block (0x1C bytes).
struct DiocRegisters
{
    DWORD EBX;     // +0x00
    DWORD EDX;     // +0x04
    DWORD ECX;     // +0x08
    DWORD EAX;     // +0x0C
    DWORD EDI;     // +0x10
    DWORD ESI;     // +0x14
    DWORD Flags;   // +0x18
};
GG_STATIC_ASSERT(offsetof(DiocRegisters, EAX) == 0x0C);
GG_STATIC_ASSERT(offsetof(DiocRegisters, Flags) == 0x18);
GG_STATIC_ASSERT(sizeof(DiocRegisters) == 0x1C);   // passed as the DIOC in/out size

// int 21h 440Dh/0848h parameter block.
struct LockParams
{
    BYTE Operation;   // +0x0
    BYTE NumLocks;    // +0x1
};

struct PreventRemoval
{
    BYTE Prevent;
};

#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))

class CDDriveControl
{
public:
    void FUN_00479740(char drive);
    bool FUN_00479ba0(char drive);
    bool FUN_00479d60(char drive);
    bool FUN_00479ef0(char drive);
    bool FUN_0047a080(char drive);
    bool FUN_0047a3f0(HANDLE device, char drive);
    static bool __stdcall FUN_0047a6f0(CDDriveControl* self, HANDLE device,
                                       BYTE drive, BYTE level, short permissions);
};

// FUNCTION: GAMEMD 0x479740
void CDDriveControl::FUN_00479740(char drive)
{
    if (DAT_00887624)
    {
        FUN_0047a080(drive);
        return;
    }
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return;
    }
    for (int i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            if (!DeviceIoControl(device, 0x90020, 0, 0, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
            }
            else
            {
                    removal.Prevent = 0;
                if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
                }
                else if (!DeviceIoControl(device, 0x2D4808, 0, 0, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to eject media. Error %d - %s\n", GetLastError(), 0);
                }
            }
            CloseHandle(device);
            return;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
}

// FUNCTION: GAMEMD 0x479BA0
bool CDDriveControl::FUN_00479ba0(char drive)
{
    bool ejected = false;
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    for (int i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            if (!DeviceIoControl(device, 0x90020, 0, 0, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
            }
            else
            {
                    removal.Prevent = 0;
                if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
                }
                else if (!DeviceIoControl(device, 0x2D4808, 0, 0, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to eject media. Error %d - %s\n", GetLastError(), 0);
                }
                else
                {
                    ejected = true;
                }
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return ejected;
}

// FUNCTION: GAMEMD 0x479D60
bool CDDriveControl::FUN_00479d60(char drive)
{
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    int i;
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            removal.Prevent = 1;
            if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x9001C, 0, 0, 0, 0, &returned, 0))
        {
            break;
        }
        FUN_004068E0("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return true;
}

// FUNCTION: GAMEMD 0x479EF0
bool CDDriveControl::FUN_00479ef0(char drive)
{
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    int i;
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            removal.Prevent = 0;
            if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x9001C, 0, 0, 0, 0, &returned, 0))
        {
            break;
        }
        FUN_004068E0("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return true;
}

// FUNCTION: GAMEMD 0x47A3F0
bool CDDriveControl::FUN_0047a3f0(HANDLE device, char drive)
{
    LockParams params;
    DiocRegisters regs = {0};
    DWORD returned;

    params.NumLocks = 0;
    regs.EDX = (DWORD)&params;
    params.Operation = 2;
    regs.EAX = 0x440D;
    regs.EBX = drive;
    regs.ECX = 0x848;
    bool result = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
    if (result)
    {
        if (regs.Flags & 1)
        {
            if (regs.EAX != 0xB0 && regs.EAX != 1)
            {
                return false;
            }
            result = true;
        }
        FUN_004068E0("Apparent number of locks to undo = %d\n", params.NumLocks);
        if (params.NumLocks == 0)
        {
            params.NumLocks = 1;
        }
        for (int i = 0; i < params.NumLocks; i++)
        {
            regs.EDX = (DWORD)&params;
            params.Operation = 1;
            regs.EAX = 0x440D;
            regs.EBX = drive;
            regs.ECX = 0x848;
            bool ok = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
            if (!ok)
            {
                FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
            }
            if (!ok || (regs.Flags & 1))
            {
                result = false;
                break;
            }
            result = true;
        }
    }
    else
    {
        FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
        return false;
    }
    return result;
}

// FUNCTION: GAMEMD 0x47A6F0
bool __stdcall CDDriveControl::FUN_0047a6f0(CDDriveControl* self, HANDLE device,
                                            BYTE drive, BYTE level, short permissions)
{
    DiocRegisters regs = {0};
    DWORD returned;
    int retries = 5;
    do
    {
        BYTE category = 0;
        do
        {
            category = category ? 0x08 : 0x48;
            regs.EDX = permissions;
            regs.ECX = MAKEWORD(0x4A, category);
            regs.EAX = 0x440D;
            regs.EBX = MAKEWORD(drive, level);
            bool ok = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
            if (!ok)
            {
                FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
            }
            if (ok && !(regs.Flags & 1))
            {
                return true;
            }
        } while (category != 0x08);
        retries--;
        switch (regs.EAX)
        {
            case 0x01:
                FUN_004068E0("LOCK return eax error 'Function not supported'\n");
                break;
            case 0xB0:
                FUN_004068E0("LOCK return eax error 'Volume not locked in drive'\n");
                break;
            case 0xB2:
                FUN_004068E0("LOCK return eax error 'Volume not removable'\n");
                break;
            case 0xB4:
                FUN_004068E0("LOCK return eax error 'Lock count exceeded'\n");
                break;
            default:
                FUN_004068E0("LOCK return eax error %d\n", regs.EAX);
                break;
        }
        Sleep(1000);
    } while (retries > 0);
    return false;
}
