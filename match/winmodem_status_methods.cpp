// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// WinModemClass slots 3, 8 and 9. The class, its vtable evidence and its
// size are in win_modem_class.h.
#include "win_modem_class.h"

// IAT 0x7E117C -- KERNEL32 GetCommModemStatus.
extern "C" __declspec(dllimport) int __stdcall GetCommModemStatus(void* file, unsigned long* status);

// The four modem-line bits GetCommModemStatus reports, passed through.
enum {
    MODEM_CTS  = 0x10,
    MODEM_DSR  = 0x20,
    MODEM_RING = 0x40,
    MODEM_RLSD = 0x80
};

// FUNCTION: GAMEMD 0x7748B0
int WinModemClass::Get_Modem_Status()
{
    unsigned long status = 0;
    int result = 0;

    GetCommModemStatus(PortHandle, &status);
    if (status & MODEM_CTS) {
        result = MODEM_CTS;
    }
    if (status & MODEM_DSR) {
        result |= MODEM_DSR;
    }
    if (status & MODEM_RING) {
        result |= MODEM_RING;
    }
    if (status & MODEM_RLSD) {
        result |= MODEM_RLSD;
    }
    return result;
}

// FUNCTION: GAMEMD 0x7754A0
void WinModemClass::Set_Value_64(int value)
{
    unknown_64 = value;
}

// FUNCTION: GAMEMD 0x7754B0
void WinModemClass::Set_Value_68(int value)
{
    unknown_68 = value;
}
